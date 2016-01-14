
#include "XT28ManualControlPrivate.h"

//--- Manual control private global variabels
volatile bool buttonStatus[INDEX_SIZE_BUTTONSTATUS] = {0};
const 	 uint8 sizeofButtonStatus = sizeof(buttonStatus) / sizeof(buttonStatus[0]);
volatile uint16 zButtonCounter = 1;
volatile uint8 zButton = 0;
volatile uint16 zRampUp = 20;
volatile uint16 preStatusExcipad = 0;


void manual_Control_Task(void)
{
	setXT28ControllState();
	actuateXT28CurrentControlState();
}

void setXT28ControllState(void) {
	// Temporary CAN message structs.
	can_Message_ts msg_s_Excipad;		// create a struct called msg_s containing the CAN msg

	//mirrorCANMessageForDebug();

	uint8 LeftExcipad_au8[8];
	uint8 LeftExcipadNumBytes_u8 = 0;
	uint8 statusExcipad = can_getDatabox(CAN_3, 3, LeftExcipad_au8, &LeftExcipadNumBytes_u8);

	if (0 == statusExcipad) {	// Databox 3 = CAN ID for Left excipad buttons
		uint8 i = 0;
		//Construct the fake msg to be sent to switchCase function
		for (i = 0; i < 8; i++) {
			msg_s_Excipad.data_au8[i] = LeftExcipad_au8[i];
		}
		msg_s_Excipad.id_u32 = CAN_ID_LEFT_EXCIPAD_BUTTONS;
		//end constuck the fake msg.

		//start of checking logic for messages
		uint16 statusSum = 0;
		for (i = 0; i < 8; i++) {
			statusSum = statusSum + LeftExcipad_au8[i];
		}
		if (statusSum >= 1) {
			if (LeftExcipad_au8[2] == MSG_ENABLE_PENDULUM_ARM_ALL_DOWN) {
				caseSwitch(&msg_s_Excipad);
			}
			else if (LeftExcipad_au8[2] == MSG_ENABLE_PENDULUM_ARM_ALL_UP) {
				caseSwitch(&msg_s_Excipad);
			}
			else if (preStatusExcipad >= 1) {
				//do nothing
			} else {
				caseSwitch(&msg_s_Excipad);
			}
		}
		preStatusExcipad = statusSum; //global variable
		//end of checking logic
	}
}

void actuateXT28CurrentControlState(void) {
	can_Message_ts msg_s_joystick;		// create a struct called msg_s containing the CAN msg
	uint8 JoystickY_au8[8];
	uint8 JoystickYNumBytes_u8;

	//store the data from the right Excipad
	//removed address from JoystickY_au8
	if (0 == can_getDatabox(CAN_3, 4, JoystickY_au8, &JoystickYNumBytes_u8)) {	// DATABOX FOR CAN_ID_JOYSTICK_Y
		//sned debugg msg
		//if (0 == can_sendData(CAN_1, 0xffffff, CAN_EXD_DU8, 8, JoystickY_au8)) {}
		//end send debugg msg
		//start of fake msg construktion for the modes function
		uint8 i = 0;
		for (i = 0; i < 8; i++) {
			msg_s_joystick.data_au8[i] = JoystickY_au8[i];
		}
		msg_s_joystick.id_u32 = CAN_ID_JOYSTICK_Y;
		modes(&msg_s_joystick);
		//end of fake msg construktion for the modes function
	}

	if (zButton==1) {
		++zButtonCounter;
	}
	if ((zButtonCounter > 5) && (zButton == 1) ) {
		--zRampUp;
		if(zRampUp < 2) {
			setVariablesZero();
			zRampUp = 2;
			zButton = 0;
			zButtonCounter = 0;
		}
	}
}

void mirrorCANMessageForDebug(void) {
	can_Message_ts msg_s;
	uint8 can_status3 = can_getData(CAN_3, &msg_s);
	if (can_status3 == 30 || can_status3 == 0) {
		if (0 == can_sendData(CAN_1, msg_s.id_u32, CAN_EXD_DU8, 8, msg_s.data_au8)){}
		if (0 == can_sendData(CAN_1, 0x565660, CAN_EXD_DU8, 8, msg_s.data_au8)){}
	} else {
		uint8 status_msg[8] = {0};
		status_msg[0] = can_status3;
		if (0 == can_sendData(CAN_1, 0x565661, CAN_EXD_DU8, 8, status_msg)){}
	}
}

void setPassiveDampeningState(uint16 passiveState) {
	out(OUT_19_DOH, passiveState);
	out(OUT_20_DOH, passiveState);
	out(OUT_21_DOH, passiveState);
	out(OUT_22_DOH, passiveState);
	out(OUT_23_DOH, passiveState);
	out(OUT_24_DOH, passiveState);
}

// Legasy code from HK project
void modes(can_Message_ts* msg_s)
{
	volatile uint8 mode = DEFAULT_MODE;
	uint8 i       = 0;
	uint8 counter = 0;

	for (i = 0; i < sizeofButtonStatus; i++) {
		if (buttonStatus[i]) {
			mode = i;
			++counter;
		}
	}
	if (counter == 0) {
		mode = DEFAULT_MODE;
	}

	uint16 joystickInput = JOYSTICK_Y_MID_POINT;
	if(msg_s->id_u32 == CAN_ID_JOYSTICK_Y) {
		joystickInput = ((msg_s->data_au8[1] << 8) | msg_s->data_au8[0]);		// Add the two 8bits byte0 and byte1 to a 16bit.
	}

	sint16 JoyREF=0;
	//Scale Joystick input for new actuate function Joystick 350 to 4300  to -300 to 300 signal
	if ((joystickInput < JOYSTICK_Y_HIGH_DEADBAND) && (joystickInput > JOYSTICK_Y_LOW_DEADBAND)) {
		JoyREF = 0;
	}
	else if (joystickInput > JOYSTICK_Y_HIGH_DEADBAND) {
		JoyREF = ((float)(joystickInput-JOYSTICK_Y_HIGH_DEADBAND) / (4300-JOYSTICK_Y_HIGH_DEADBAND) * (float)300);
	}  //Linear scaling
	else if (joystickInput < JOYSTICK_Y_LOW_DEADBAND) {
		JoyREF = ((float)(joystickInput - JOYSTICK_Y_LOW_DEADBAND) / (JOYSTICK_Y_HIGH_DEADBAND - 350) * (float)300);
	}

	sint16 REFINV = 0;
	REFINV = JoyREF - (2 * JoyREF);

	switch(mode) {
	case INDEX_CYLINDER_FRONT_RIGHT:								//----1----
		defaultSafety = 0;
		referenceSoleonidOutputCurrent_ma[FR] = JoyREF;
		// passiveDampening special test onlt for FL and FR
		uint16 passiveStateOn = 1;
		setPassiveDampeningState(passiveStateOn);
		break;

	case INDEX_CYLINDER_FRONT_LEFT:								    //----2----
		defaultSafety = 0;
		referenceSoleonidOutputCurrent_ma[FL] = JoyREF;
		// passiveDampening special test only for FR and FR
		uint16 passiveStateOff = 0;
		setPassiveDampeningState(passiveStateOff);
		break;

	case INDEX_CYLINDER_MID_RIGHT:									//----3----
		defaultSafety=0;
		referenceSoleonidOutputCurrent_ma[MR] = JoyREF;
		break;

	case INDEX_CYLINDER_MID_LEFT:									//----4----
		defaultSafety=0;
		referenceSoleonidOutputCurrent_ma[ML] = JoyREF;
		break;

	case INDEX_CYLINDER_REAR_RIGHT:									//----5----
		defaultSafety=0;
		referenceSoleonidOutputCurrent_ma[BR] = JoyREF;
		break;

	case INDEX_CYLINDER_REAR_LEFT:									//----6----
		defaultSafety=0;
		referenceSoleonidOutputCurrent_ma[BL] = JoyREF;
		break;

	case INDEX_CYLINDER_ALL_DOWN:									//----7----
		defaultSafety=0;
		referenceSoleonidOutputCurrent_ma[FR] = zRampUp;
		referenceSoleonidOutputCurrent_ma[MR] = zRampUp;
		referenceSoleonidOutputCurrent_ma[BR] = zRampUp;
		referenceSoleonidOutputCurrent_ma[FL] = zRampUp;
		referenceSoleonidOutputCurrent_ma[ML] = zRampUp;
		referenceSoleonidOutputCurrent_ma[BL] = zRampUp;
		break;

	case INDEX_CYLINDER_ALL_UP:										//----8----

		defaultSafety=0;
		referenceSoleonidOutputCurrent_ma[FR] = -zRampUp;
		referenceSoleonidOutputCurrent_ma[MR] = -zRampUp;
		referenceSoleonidOutputCurrent_ma[BR] = -zRampUp;
		referenceSoleonidOutputCurrent_ma[FL] = -zRampUp;
		referenceSoleonidOutputCurrent_ma[ML] = -zRampUp;
		referenceSoleonidOutputCurrent_ma[BL] = -zRampUp;
		break;

	case INDEX_CYLINDER_TILT_Y:										//----9---- (Pitch)

		if(joystickInput > JOYSTICK_Y_HIGH_DEADBAND) {				//Low signal
			defaultSafety = 0;
			referenceSoleonidOutputCurrent_ma[FR] = JoyREF;
			referenceSoleonidOutputCurrent_ma[FL] = JoyREF;
			referenceSoleonidOutputCurrent_ma[BR] = REFINV;
			referenceSoleonidOutputCurrent_ma[BL] = REFINV;

		}
		else if(joystickInput < JOYSTICK_Y_LOW_DEADBAND) {			//High signal
			defaultSafety = 0;
			referenceSoleonidOutputCurrent_ma[FR] = JoyREF;
			referenceSoleonidOutputCurrent_ma[FL] = JoyREF;
			referenceSoleonidOutputCurrent_ma[BR] = REFINV;
			referenceSoleonidOutputCurrent_ma[BL] = REFINV;
		}
		else if(joystickInput < JOYSTICK_Y_HIGH_DEADBAND && joystickInput > JOYSTICK_Y_LOW_DEADBAND) {
			for(i=0;i<6;i++){
				referenceSoleonidOutputCurrent_ma[i]=0;}
		}
		break;

	case INDEX_CYLINDER_TILT_X:										//----9---- (roll)
		if(joystickInput > JOYSTICK_Y_HIGH_DEADBAND) {			//Low signal
			defaultSafety = 0;
			referenceSoleonidOutputCurrent_ma[FR] = JoyREF;
			referenceSoleonidOutputCurrent_ma[MR] = JoyREF;
			referenceSoleonidOutputCurrent_ma[BR] = JoyREF;
			referenceSoleonidOutputCurrent_ma[FL] = REFINV;
			referenceSoleonidOutputCurrent_ma[ML] = REFINV;
			referenceSoleonidOutputCurrent_ma[BL] = REFINV;

		}
		else if(joystickInput < JOYSTICK_Y_LOW_DEADBAND) {			//High signal

			defaultSafety = 0;
			referenceSoleonidOutputCurrent_ma[FR] = JoyREF;
			referenceSoleonidOutputCurrent_ma[MR] = JoyREF;
			referenceSoleonidOutputCurrent_ma[BR] = JoyREF;
			referenceSoleonidOutputCurrent_ma[FL] = REFINV;
			referenceSoleonidOutputCurrent_ma[ML] = REFINV;
			referenceSoleonidOutputCurrent_ma[BL] = REFINV;
		}
		else if(joystickInput < JOYSTICK_Y_HIGH_DEADBAND && joystickInput > JOYSTICK_Y_LOW_DEADBAND) {
			for(i = 0; i < 6; i++) {
				referenceSoleonidOutputCurrent_ma[i] = 0;
			}
		}
		break;

	case INDEX_SIMPLE_CONTROL:
		//Simple control enabeld
		break;
	}
}

void caseSwitch(can_Message_ts* msg_s) {
	volatile bool status = 0;
	uint8 i = 0;
	if (msg_s->id_u32 == CAN_ID_LEFT_EXCIPAD_BUTTONS) {						//Check CAN ID
		if (msg_s->data_au8[3] == MSG_ENABLE_PENDULUM_ARM_FRONT_RIGHT) {		//MSG_ENABLE_PENDULUM_ARM_FRONT_RIGHT
			status = toggleVariable(INDEX_CYLINDER_FRONT_RIGHT);
			for (i = 0; i < 6; i++) {
				referenceSoleonidOutputCurrent_ma[i] = 0;
			}					//Set all PWM-outputs (to solenoids) to zero
			setVariablesZero();												//Reset buttonStatus to ensure only one is active
			buttonStatus[INDEX_CYLINDER_FRONT_RIGHT] = status;				//Set active bit for buttonStatus
			ACTIVE_FORCE_CONTROL = 0; //disable controller
		}
		else if (msg_s->data_au8[3] == MSG_ENABLE_PENDULUM_ARM_FRONT_LEFT)	//MSG_ENABLE_PENDULUM_ARM_FRONT_LEFT
		{
			status = toggleVariable(INDEX_CYLINDER_FRONT_LEFT);
			for(i=0;i<6;i++){
				referenceSoleonidOutputCurrent_ma[i]=0;
			}
			setVariablesZero();
			buttonStatus[INDEX_CYLINDER_FRONT_LEFT] = status;
			ACTIVE_FORCE_CONTROL=0; //disable controller
		}
		else if (msg_s->data_au8[4] == MSG_ENABLE_PENDULUM_ARM_MID_RIGHT)	//MSG_ENABLE_PENDULUM_ARM_MID_RIGHT
		{
			status = toggleVariable(INDEX_CYLINDER_MID_RIGHT);
			for(i=0;i<6;i++){
				referenceSoleonidOutputCurrent_ma[i]=0;}
			setVariablesZero();
			buttonStatus[INDEX_CYLINDER_MID_RIGHT] = status;
			ACTIVE_FORCE_CONTROL=0; //disable controller
		}
		else if (msg_s->data_au8[3] == MSG_ENABLE_PENDULUM_ARM_MID_LEFT)		//MSG_ENABLE_PENDULUM_ARM_MID_LEFT
		{
			status = toggleVariable(INDEX_CYLINDER_MID_LEFT);
			for(i=0;i<6;i++){
				referenceSoleonidOutputCurrent_ma[i]=0;}
			setVariablesZero();
			buttonStatus[INDEX_CYLINDER_MID_LEFT] = status;
			ACTIVE_FORCE_CONTROL=0; //disable controller
		}

		else if (msg_s->data_au8[5] == MSG_ENABLE_PENDULUM_ARM_REAR_RIGHT)	//MSG_ENABLE_PENDULUM_ARM_REAR_RIGHT
		{
			status = toggleVariable(INDEX_CYLINDER_REAR_RIGHT);
			for(i=0;i<6;i++){
				referenceSoleonidOutputCurrent_ma[i]=0;}
			setVariablesZero();
			buttonStatus[INDEX_CYLINDER_REAR_RIGHT] = status;
			ACTIVE_FORCE_CONTROL=0; //disable controller
		}
		else if (msg_s->data_au8[4] == MSG_ENABLE_PENDULUM_ARM_REAR_LEFT) {	//MSG_ENABLE_PENDULUM_ARM_REAR_LEFT
			status = toggleVariable(INDEX_CYLINDER_REAR_LEFT);
			for (i = 0; i < 6; i++) {
				referenceSoleonidOutputCurrent_ma[i] = 0;
			}
			setVariablesZero();
			buttonStatus[INDEX_CYLINDER_REAR_LEFT] = status;
			ACTIVE_FORCE_CONTROL=0; //disable controller
		}
		else if (msg_s->data_au8[2] == MSG_ENABLE_PENDULUM_ARM_ALL_DOWN) {		//MSG_ENABLE_PENDULUM_ARM_ALL_DOWN
			setVariablesZero();
			ACTIVE_FORCE_CONTROL=0; //disable controller
			buttonStatus[INDEX_CYLINDER_ALL_DOWN] = 1;
			zButton = 1;
			zButtonCounter = 0;
			++zRampUp;
			if(zRampUp > 50) {
				zRampUp = 50;
			}
		}
		else if (msg_s->data_au8[2] == MSG_ENABLE_PENDULUM_ARM_ALL_UP) {		//MSG_ENABLE_PENDULUM_ARM_ALL_UP
			setVariablesZero();
			ACTIVE_FORCE_CONTROL = 0; //disable controller
			buttonStatus[INDEX_CYLINDER_ALL_UP] = 1;
			zButton = 1;
			zButtonCounter = 0;
			++zRampUp;
			if(zRampUp > 50) {
				zRampUp = 50;
			}
		}
		else if (msg_s->data_au8[1] == MSG_ENABLE_PENDULUM_ARM_TILT_Y) {		//MSG_ENABLE_PENDULUM_ARM_MID_LEFT
			status = toggleVariable(INDEX_CYLINDER_TILT_Y);
			for ( i = 0; i < 6; i++) {
				referenceSoleonidOutputCurrent_ma[i]=0;
			}
			setVariablesZero();
			ACTIVE_FORCE_CONTROL=0; //disable controller
			buttonStatus[INDEX_CYLINDER_TILT_Y] = status;
		}
		else if (msg_s->data_au8[1] == MSG_ENABLE_PENDULUM_ARM_TILT_X) {		//MSG_ENABLE_PENDULUM_ARM_MID_LEFT
			status = toggleVariable(INDEX_CYLINDER_TILT_X);
			for (i = 0; i < 6; i++) {
				referenceSoleonidOutputCurrent_ma[i] = 0;
			}
			setVariablesZero();
			ACTIVE_FORCE_CONTROL = 0; //disable controller
			buttonStatus[INDEX_CYLINDER_TILT_X] = status;
		}
		else if (msg_s->data_au8[2] == MSG_ENABLE_SIMPLE_CONTROL) {		//MSG_ENABLE_PENDULUM_simple controll
			status = toggleVariable(INDEX_SIMPLE_CONTROL);
			ACTIVE_FORCE_CONTROL = status;  //Enable or disable force control
			for (i = 0 ; i < 6; i++) {
				referenceSoleonidOutputCurrent_ma[i] = 0;
			}
			setVariablesZero();
			buttonStatus[INDEX_SIMPLE_CONTROL] = status;
		}
	}
}

bool toggleVariable(bool toggleTarget) {
	if (buttonStatus[toggleTarget]) {
		return 0;
	} else {
		return 1;
	}
}

void setVariablesZero(void) {
	uint8 i;
	for( i = 0; i < sizeofButtonStatus; i++) {
		buttonStatus[i] = 0;
	}
}




