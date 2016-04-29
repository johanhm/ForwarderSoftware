#include "Excipad.h"


/* Config */
#define EXIPAD_BUTTONS_DB_BUFF_LEN  	(5)
#define EXIPAD_JOYSTICK_Y_DB_BUFF_LEN  	(5)
#define EXIPAD_JOYSTICK_X_DB_BUFF_LEN	(5)

#define CAN_ID_LEFT_EXCIPAD_BUTTONS	 		(0x18FE030B)
#define CAN_ID_RIGHT_EXCIPAD_BUTTONS		(0x18FE0315)
#define CAN_ID_JOYSTICK_Y					(0x18FE010B)
#define CAN_ID_JOYSTICK_X					(0x18FE000B)

/* CAN message exipad */
#define BUTTON_ID_1		(0x01) /* 1,  byte 3 */
#define BUTTON_ID_2	 	(0x04) /* 4,  byte 3 */
#define BUTTON_ID_3 	(0x10) /* 16, byte 3 */
#define BUTTON_ID_4		(0x40) /* 64, byte 3 */

#define BUTTON_ID_5	 	(0x01) /* 1,  byte 4 */
#define BUTTON_ID_6		(0x04) /* 4,  byte 4 */
#define BUTTON_ID_7		(0x10) /* 16, byte 4 */
#define BUTTON_ID_8	 	(0x40) /* 64, byte 4 */

#define BUTTON_ID_9		(0x01) /* 1,  byte 5 */

#define BUTTON_ID_10	(0x01) /* 1,  byte 0 */
#define BUTTON_ID_11	(0x04) /* 4,  byte 0 */
#define BUTTON_ID_12	(0x10) /* 16, byte 0 */
#define BUTTON_ID_13	(0x40) /* 64, byte 0 */

#define BUTTON_ID_14	(0x01) /* 1,  byte 1 */
#define BUTTON_ID_15	(0x04) /* 4,  byte 1 */
#define BUTTON_ID_16	(0x10) /* 16, byte 1 */
#define BUTTON_ID_17	(0x40) /* 64, byte 1 */

#define BUTTON_ID_18	(0x01) /* 1,  byte 2 */
#define BUTTON_ID_19	(0x04) /* 4,  byte 2 */
#define BUTTON_ID_20	(0x10) /* 16, byte 2 */
#define BUTTON_ID_21	(0x40) /* 64, byte 2 */


/* Joystick */
#define JOYSTICK_Y_HIGH_POINT		(4300)
#define JOYSTICK_Y_MID_POINT		(2350)
#define JOYSTICK_Y_LOW_POINT		(350)
#define JOYSTICK_Y_DEADBAND			(200)
#define JOYSTICK_Y_HIGH_DEADBAND	(JOYSTICK_Y_MID_POINT + JOYSTICK_Y_DEADBAND)
#define JOYSTICK_Y_LOW_DEADBAND		(JOYSTICK_Y_MID_POINT - JOYSTICK_Y_DEADBAND)

/* Priave Prototypes */
static void exipadButtonsCallback(void);
static void exipadJoystickYCallback(void);
static void exipadJoystickXCallback(void);
//static int checkButtonState(uint8 message, uint8 buttonID, int currentState, int toggleIfThisState);

static int exipadCANChannel = 0;
static int exipadButtonDBNr = 0;
static int exipadJoystickYDBNr = 0;
static int exipadJoystickXDBNr = 0;
void EXPConfigureExcipad(uint8 CANChannel, int buttonDataboxNr, int joystickYDataboxNr, int joystickXDataboxNr) {

	exipadCANChannel    = CANChannel;
	exipadButtonDBNr    = buttonDataboxNr;
	exipadJoystickYDBNr = joystickYDataboxNr;
	exipadJoystickXDBNr = joystickXDataboxNr;

	static can_DataboxData_ts exipadButtonsDataboxBuffer[EXIPAD_BUTTONS_DB_BUFF_LEN];
	static can_DataboxData_ts exipadJoystickYDataboxBuffer[EXIPAD_JOYSTICK_Y_DB_BUFF_LEN];
	static can_DataboxData_ts exipadJoystickXDataboxBuffer[EXIPAD_JOYSTICK_X_DB_BUFF_LEN];
	int exipadMessageNumOfBytes = 8;

	can_initRxDatabox(CANChannel,
			buttonDataboxNr,
			CAN_ID_LEFT_EXCIPAD_BUTTONS,
			CAN_EXD_DU8,
			exipadMessageNumOfBytes,
			exipadButtonsDataboxBuffer,
			EXIPAD_BUTTONS_DB_BUFF_LEN,
			exipadButtonsCallback
	);
	can_initRxDatabox(CANChannel,
			joystickYDataboxNr,
			CAN_ID_JOYSTICK_Y,
			CAN_EXD_DU8,
			exipadMessageNumOfBytes,
			exipadJoystickYDataboxBuffer,
			EXIPAD_JOYSTICK_Y_DB_BUFF_LEN,
			exipadJoystickYCallback
	);
	can_initRxDatabox(CANChannel,
			joystickXDataboxNr,
			CAN_ID_JOYSTICK_X,
			CAN_EXD_DU8,
			exipadMessageNumOfBytes,
			exipadJoystickXDataboxBuffer,
			EXIPAD_JOYSTICK_X_DB_BUFF_LEN,
			exipadJoystickXCallback
	);

}

static uint8 leftExcipadButtonsMessage[8] = {0};
static void exipadButtonsCallback(void) {
	uint8 leftExcipadNumBytes_u8 = 0;
	can_getDatabox(exipadCANChannel, exipadButtonDBNr, leftExcipadButtonsMessage, &leftExcipadNumBytes_u8);

	/* Debugg remove when done */
	//can_sendData(CAN_1, 0x18FE1050, CAN_EXD_DU8, 8, leftExcipadButtonsMessage);
	/* End debugg, remove when done */
}

static uint8 joyStickYMessage[8] = {0};
static void exipadJoystickYCallback(void) {
	uint8 joystickYNumBytes_u8;
	can_getDatabox(exipadCANChannel, exipadJoystickYDBNr, joyStickYMessage, &joystickYNumBytes_u8);
}

static uint8 joyStickXMessage[8] = {0};
static void exipadJoystickXCallback(void) {
	uint8 joystickXNumBytes_u8;
	can_getDatabox(exipadCANChannel, exipadJoystickXDBNr, joyStickXMessage, &joystickXNumBytes_u8);
}


float EXPGetJoystickXScaledValueLeftRight(void) {

	uint16 joystickXInputRaw = ((joyStickXMessage[7] << 8) | joyStickXMessage[6]);
	float joystickInput = (float)joystickXInputRaw;

	float joyRef = 0;
	if ((joystickInput < JOYSTICK_Y_HIGH_DEADBAND) && (joystickInput > JOYSTICK_Y_LOW_DEADBAND)) {
		joyRef = 0;
	}
	else if (joystickInput > JOYSTICK_Y_HIGH_DEADBAND) {
		joyRef = (float)(joystickInput - JOYSTICK_Y_HIGH_DEADBAND) / (4300 - JOYSTICK_Y_HIGH_DEADBAND) * (float)300;
	}  //Linear scaling
	else if (joystickInput < JOYSTICK_Y_LOW_DEADBAND) {
		joyRef = ((float)(joystickInput - JOYSTICK_Y_LOW_DEADBAND) / (JOYSTICK_Y_HIGH_DEADBAND - 350) * (float)300);
	}
	return joyRef;
}


float EXPGetJoystickScaledValueUppDown(void) {

	uint16 joystickInputRaw = ((joyStickYMessage[1] << 8) | joyStickYMessage[0]);		// Add the two 8bits byte0 and byte1 to a 16bit.
	float joystickInput = (float)joystickInputRaw;

	float joyRef = 0;
	if ((joystickInput < JOYSTICK_Y_HIGH_DEADBAND) && (joystickInput > JOYSTICK_Y_LOW_DEADBAND)) {
		joyRef = 0;
	}
	else if (joystickInput > JOYSTICK_Y_HIGH_DEADBAND) {
		joyRef = (float)(joystickInput - JOYSTICK_Y_HIGH_DEADBAND) / (4300 - JOYSTICK_Y_HIGH_DEADBAND) * (float)300;
	}  //Linear scaling
	else if (joystickInput < JOYSTICK_Y_LOW_DEADBAND) {
		joyRef = ((float)(joystickInput - JOYSTICK_Y_LOW_DEADBAND) / (JOYSTICK_Y_HIGH_DEADBAND - 350) * (float)300);
	}
	return joyRef;
}


typedef enum {
	ACCEPT_NEW_MESSAGE,
	NOT_ACCEPT_NEW_MESSAGE
} exipadCANMessageState;

static exipadButton pressedButtonOld = NONE;
static exipadButton pressedButton = NONE;
exipadButton EXPGetLastPressedButtonWithToggle(void) {
	static exipadCANMessageState exipadCANMessageState = ACCEPT_NEW_MESSAGE;

	switch (exipadCANMessageState) {
	case ACCEPT_NEW_MESSAGE:
		if (EXPGetUserIsHoldingAButtonDown() == TRUE) {
			pressedButton = EXPGetCurrentlyPressedButton();
			if (pressedButton == pressedButtonOld) {
				pressedButton = NONE;
			}
			exipadCANMessageState = NOT_ACCEPT_NEW_MESSAGE;
		}
		break;
	case NOT_ACCEPT_NEW_MESSAGE:
		if (EXPGetUserIsHoldingAButtonDown() == FALSE) {
			pressedButtonOld = pressedButton;
			exipadCANMessageState = ACCEPT_NEW_MESSAGE;
		}
		break;
	}
	return pressedButton;
}

void EXPSetButtonStateTo(exipadButton setButtonState) {
	pressedButton = setButtonState;
}

exipadButton EXPGetCurrentlyPressedButton(void) {
	exipadButton exipadButtonPresed = NONE;
	/* byte 3 */
	if (leftExcipadButtonsMessage[3] == BUTTON_ID_1) {
		exipadButtonPresed = BUTTON_1;
	}
	if (leftExcipadButtonsMessage[3] == BUTTON_ID_2) {
		exipadButtonPresed = BUTTON_2;
	}
	if (leftExcipadButtonsMessage[3] == BUTTON_ID_3) {
		exipadButtonPresed = BUTTON_3;
	}
	if (leftExcipadButtonsMessage[3] == BUTTON_ID_4) {
		exipadButtonPresed = BUTTON_4;
	}
	/* byte 4 */
	if (leftExcipadButtonsMessage[4] == BUTTON_ID_5) {
		exipadButtonPresed = BUTTON_5;
	}
	if (leftExcipadButtonsMessage[4] == BUTTON_ID_6) {
		exipadButtonPresed = BUTTON_6;
	}
	if (leftExcipadButtonsMessage[4] == BUTTON_ID_7) {
		exipadButtonPresed = BUTTON_7;
	}
	if (leftExcipadButtonsMessage[4] == BUTTON_ID_8) {
		exipadButtonPresed = BUTTON_8;
	}
	/* byte 5 */
	if (leftExcipadButtonsMessage[5] == BUTTON_ID_9) {
		exipadButtonPresed = BUTTON_9;
	}
	/* byte 0 */
	if (leftExcipadButtonsMessage[0] == BUTTON_ID_10) {
		exipadButtonPresed = BUTTON_10;
	}
	if (leftExcipadButtonsMessage[0] == BUTTON_ID_11) {
		exipadButtonPresed = BUTTON_11;
	}
	if (leftExcipadButtonsMessage[0] == BUTTON_ID_12) {
		exipadButtonPresed = BUTTON_12;
	}
	if (leftExcipadButtonsMessage[0] == BUTTON_ID_13) {
		exipadButtonPresed = BUTTON_13;
	}
	/* byte 1 */
	if (leftExcipadButtonsMessage[1] == BUTTON_ID_14) {
		exipadButtonPresed = BUTTON_14;
	}
	if (leftExcipadButtonsMessage[1] == BUTTON_ID_15) {
		exipadButtonPresed = BUTTON_15;
	}
	if (leftExcipadButtonsMessage[1] == BUTTON_ID_16) {
		exipadButtonPresed = BUTTON_16;
	}
	if (leftExcipadButtonsMessage[1] == BUTTON_ID_17) {
		exipadButtonPresed = BUTTON_17;
	}
	/* byte 2 */
	if (leftExcipadButtonsMessage[2] == BUTTON_ID_18) {
		exipadButtonPresed = BUTTON_18;
	}
	if (leftExcipadButtonsMessage[2] == BUTTON_ID_19) {
		exipadButtonPresed = BUTTON_19;
	}
	if (leftExcipadButtonsMessage[2] == BUTTON_ID_20) {
		exipadButtonPresed = BUTTON_20;
	}
	if (leftExcipadButtonsMessage[2] == BUTTON_ID_21) {
		exipadButtonPresed = BUTTON_21;
	}
	return exipadButtonPresed;
}

bool EXPGetUserIsHoldingAButtonDown(void) {
	/* Using local global "leftExcipadButtonsMessage" */
	uint16 statusSum = 0;
	int i = 0;
	int sumBytes = 8;
	for (i = 0; i < sumBytes; i++) {
		statusSum = statusSum + leftExcipadButtonsMessage[i];
	}
	if (statusSum == 0) {
		return FALSE;
	} else {
		return TRUE;
	}
}
