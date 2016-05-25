#include "RightExcipad.h"

/* Config */
#define EXIPAD_BUTTONS_DB_BUFF_LEN  	(5)
#define EXIPAD_JOYSTICK_Y_DB_BUFF_LEN  	(5)
#define EXIPAD_JOYSTICK_X_DB_BUFF_LEN	(5)

#define CAN_ID_RIGHT_EXCIPAD_BUTTONS		(0x18FE0315)

/* From Excipad Transmission */
#define CAN_ID_RX_EXCIPAD_RSpeed				(0x18FE0115) // (*Excipad Right Speed Regulator mex ID hex 18FE0115 *)
#define CAN_ID_RX_EXCIPAD_RButton				(0x18FE0315) // (*Excipad Right Buttons mex ID hex 18FE0315*)
#define CAN_ID_RX_EXCIPAD_RMiniJoy_X			(0x18FE0015) // (*Excipad Right mini joystick x-axis*)


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

#define BUTTON_ID_10	(0x04) /* 1,  byte 0 */
#define BUTTON_ID_11	(0x10) /* 4,  byte 0 */
#define BUTTON_ID_12	(0x40) /* 16, byte 0 */
#define BUTTON_ID_13	(0x10) /* 64, byte 0 */

#define BUTTON_ID_14	(0x40) /* 1,  byte 1 */
#define BUTTON_ID_15	(0x01) /* 4,  byte 1 */
#define BUTTON_ID_16	(0x40) /* 16, byte 1 */
#define BUTTON_ID_17	(0x01) /* 64, byte 1 */

#define BUTTON_ID_18	(0x04) /* 1,  byte 2 */
#define BUTTON_ID_19	(0x01) /* 4,  byte 2 */
#define BUTTON_ID_20	(0x04) /* 16, byte 2 */
#define BUTTON_ID_21	(0x10) /* 64, byte 2 */


/* Joystick */
#define JOYSTICK_Y_HIGH_POINT		(4300)
#define JOYSTICK_Y_MID_POINT		(2350)
#define JOYSTICK_Y_LOW_POINT		(350)
#define JOYSTICK_Y_DEADBAND			(200)
#define JOYSTICK_Y_HIGH_DEADBAND	(JOYSTICK_Y_MID_POINT + JOYSTICK_Y_DEADBAND)
#define JOYSTICK_Y_LOW_DEADBAND		(JOYSTICK_Y_MID_POINT - JOYSTICK_Y_DEADBAND)

/* Priave Prototypes */
static void exipadButtonsCallback(void);
static void exipadScrollerCallback(void);
static void exipadJoystickXCallback(void);
//static int checkButtonState(uint8 message, uint8 buttonID, int currentState, int toggleIfThisState);

static int exipadCANChannel = 0;
static int exipadButtonDBNr = 0;
static int exipadScrollerDBNr = 0;
static int exipadJoystickXDBNr = 0;
void EXPConfigureExcipad(uint8 CANChannel, int buttonDataboxNr, int scrollerDataboxNr, int joystickXDataboxNr) {

	exipadCANChannel    = CANChannel;
	exipadButtonDBNr    = buttonDataboxNr;
	exipadScrollerDBNr = scrollerDataboxNr;
	exipadJoystickXDBNr = joystickXDataboxNr;

	static can_DataboxData_ts exipadButtonsDataboxBuffer[EXIPAD_BUTTONS_DB_BUFF_LEN];
	static can_DataboxData_ts exipadJoystickYDataboxBuffer[EXIPAD_JOYSTICK_Y_DB_BUFF_LEN];
	static can_DataboxData_ts exipadJoystickXDataboxBuffer[EXIPAD_JOYSTICK_X_DB_BUFF_LEN];
	int exipadMessageNumOfBytes = 8;

	can_initRxDatabox(CANChannel,
			buttonDataboxNr,
			CAN_ID_RIGHT_EXCIPAD_BUTTONS,
			CAN_EXD_DU8,
			exipadMessageNumOfBytes,
			exipadButtonsDataboxBuffer,
			EXIPAD_BUTTONS_DB_BUFF_LEN,
			exipadButtonsCallback
	);
	can_initRxDatabox(CANChannel,
			scrollerDataboxNr,
			CAN_ID_RX_EXCIPAD_RSpeed,
			CAN_EXD_DU8,
			exipadMessageNumOfBytes,
			exipadJoystickYDataboxBuffer,
			EXIPAD_JOYSTICK_Y_DB_BUFF_LEN,
			exipadScrollerCallback
	);
	can_initRxDatabox(CANChannel,
			joystickXDataboxNr,
			CAN_ID_RX_EXCIPAD_RMiniJoy_X,
			CAN_EXD_DU8,
			exipadMessageNumOfBytes,
			exipadJoystickXDataboxBuffer,
			EXIPAD_JOYSTICK_X_DB_BUFF_LEN,
			exipadJoystickXCallback
	);

}

static int exipadButtonsUpdateTime_ms = 0;
static uint8 rightExcipadButtonsMessage[8] = {0};
static void exipadButtonsCallback(void) {
	uint8 leftExcipadNumBytes_u8 = 0;
	can_getDatabox(exipadCANChannel, exipadButtonDBNr, rightExcipadButtonsMessage, &leftExcipadNumBytes_u8);
	/* Set timeout to zero */
	exipadButtonsUpdateTime_ms = 0;
}

static uint8 scrollerMessage[8] = {0};
static void exipadScrollerCallback(void) {
	uint8 scrollerNumBytes_u8;
	can_getDatabox(exipadCANChannel, exipadScrollerDBNr, scrollerMessage, &scrollerNumBytes_u8);
}

static uint8 joyStickXMessage[8] = {0};
static void exipadJoystickXCallback(void) {
	uint8 joystickXNumBytes_u8;
	can_getDatabox(exipadCANChannel, exipadJoystickXDBNr, joyStickXMessage, &joystickXNumBytes_u8);
}

bool EXPCheckTimeout(int callTime_ms, int timeoutTime_ms) {
	/* Check timeout error */
	if (exipadButtonsUpdateTime_ms > timeoutTime_ms) {
		return TRUE; /* timeout */
	}
	exipadButtonsUpdateTime_ms += callTime_ms;
	return FALSE; /* working */
}

int EXPGetJoystickXScaledValueLeftRight(void) {

	const int MINIJOYSTICK_HIGH_POINT		=	4230;
	//const int MINIJOYSTICK_MID_POINT		=	2482;
	const int MINIJOYSTICK_LOW_POINT		=	466;
	//const int MINIJOYSTICK_DEADBAND			=	200;
	const int MINIJOYSTICK_HIGH_DEADBAND	=   2484 + 200;//	MINIJOYSTICK_MID_POINT+MINIJOYSTICK_DEADBAND;
	const int MINIJOYSTICK_LOW_DEADBAND		=   2484 - 200;//	MINIJOYSTICK_MID_POINT-MINIJOYSTICK_DEADBAND;

	uint16 mVexcipad_joystick = 0;
	mVexcipad_joystick = (joyStickXMessage[7] << 8) + joyStickXMessage[6];
	uint32 yh = 0;
	uint32 yl = 0;

	yh = 1000 * mVexcipad_joystick / (MINIJOYSTICK_HIGH_POINT - MINIJOYSTICK_HIGH_DEADBAND) - 1000 * MINIJOYSTICK_HIGH_DEADBAND / (MINIJOYSTICK_HIGH_POINT - MINIJOYSTICK_HIGH_DEADBAND);
	yl = -1000 * mVexcipad_joystick / (MINIJOYSTICK_LOW_POINT - MINIJOYSTICK_LOW_DEADBAND) + 1000 * MINIJOYSTICK_LOW_DEADBAND / (MINIJOYSTICK_LOW_POINT - MINIJOYSTICK_LOW_DEADBAND);

	int MiniJoystick = 0;
	if (mVexcipad_joystick > MINIJOYSTICK_HIGH_DEADBAND && mVexcipad_joystick <= MINIJOYSTICK_HIGH_POINT) {
		MiniJoystick = yh;
	}
	else if (mVexcipad_joystick > MINIJOYSTICK_HIGH_POINT) {
		MiniJoystick = 1000;
	}
	else if (mVexcipad_joystick < MINIJOYSTICK_LOW_DEADBAND && mVexcipad_joystick >= MINIJOYSTICK_LOW_POINT) {
		MiniJoystick = yl;
	}
	else if (mVexcipad_joystick < MINIJOYSTICK_LOW_POINT && mVexcipad_joystick>0 ) {
		MiniJoystick = -1000;
	}
	else if (mVexcipad_joystick == 0) {
		MiniJoystick = 0;
	} else {
		MiniJoystick = 0;
	}
	return MiniJoystick;
}


int EXPGetScrollerValue(void) {

	const int Excipad_wheel_mV_max = 4500;
	const int Excipad_wheel_mV_min = 202;

	const int Engine_speed_max = 2000;
	const int Engine_speed_min = 800;

	uint16 mVexcipad_wheel = 0;
	mVexcipad_wheel = (scrollerMessage[3] << 8) + scrollerMessage[2];

	static enum scrollerStates {SCROLLER_START, SCROLLER_NORMAL} scrollerState = SCROLLER_START;

	switch (scrollerState) {
	case SCROLLER_START: {
		bool sensorHaveVoltageAndIsAtMinimumScrollPosition = ((mVexcipad_wheel < (Excipad_wheel_mV_min + 20)) && (sys_getTime_us() > 2000000) );
		if (sensorHaveVoltageAndIsAtMinimumScrollPosition) {
			scrollerState = SCROLLER_NORMAL;
		}
		break;
	}
	case SCROLLER_NORMAL:
		break;
	}
	if (scrollerState == SCROLLER_START) {
		return 800;
	}

	int Engine_ref_speed = 0;
	Engine_ref_speed = (mVexcipad_wheel - Excipad_wheel_mV_max) * (Engine_speed_max - Engine_speed_min) / (Excipad_wheel_mV_max - Excipad_wheel_mV_min) + Engine_speed_max;

	if (Engine_ref_speed > Engine_speed_max) {
		Engine_ref_speed = Engine_speed_max;
	}
	else if (Engine_ref_speed < Engine_speed_min) {
		Engine_ref_speed = Engine_speed_min;
	}
	return Engine_ref_speed;
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

	g_debug1_2 = rightExcipadButtonsMessage[0];
	g_debug1_3 = rightExcipadButtonsMessage[1];
	g_debug1_4 = rightExcipadButtonsMessage[2];
	g_debug2_1 = rightExcipadButtonsMessage[3];
	g_debug2_2 = rightExcipadButtonsMessage[4];
	g_debug2_3 = rightExcipadButtonsMessage[5];
	g_debug2_4 = rightExcipadButtonsMessage[6];
	g_debug3_1 = rightExcipadButtonsMessage[7];

	exipadButton exipadButtonPresed = NONE;

	/* byte 3 */
	if (rightExcipadButtonsMessage[3] == BUTTON_ID_1) {
		exipadButtonPresed = BUTTON_1;
	}
	if (rightExcipadButtonsMessage[3] == BUTTON_ID_2) {
		exipadButtonPresed = BUTTON_2;
	}
	if (rightExcipadButtonsMessage[3] == BUTTON_ID_3) {
		exipadButtonPresed = BUTTON_3;
	}
	if (rightExcipadButtonsMessage[3] == BUTTON_ID_4) {
		exipadButtonPresed = BUTTON_4;
	}
	/* byte 4 */
	if (rightExcipadButtonsMessage[4] == BUTTON_ID_5) {
		exipadButtonPresed = BUTTON_5;
	}
	if (rightExcipadButtonsMessage[4] == BUTTON_ID_6) {
		exipadButtonPresed = BUTTON_6;
	}
	if (rightExcipadButtonsMessage[4] == BUTTON_ID_7) {
		exipadButtonPresed = BUTTON_7;
	}
	if (rightExcipadButtonsMessage[4] == BUTTON_ID_8) {
		exipadButtonPresed = BUTTON_8;
	}
	/* byte 5 */
	if (rightExcipadButtonsMessage[5] == BUTTON_ID_9) {
		exipadButtonPresed = BUTTON_9;
	}
	/* byte 0 */
	if (rightExcipadButtonsMessage[2] == BUTTON_ID_10) {
		exipadButtonPresed = BUTTON_10;
	}
	if (rightExcipadButtonsMessage[2] == BUTTON_ID_11) {
		exipadButtonPresed = BUTTON_11;
	}
	if (rightExcipadButtonsMessage[2] == BUTTON_ID_12) {
		exipadButtonPresed = BUTTON_12;
	}
	if (rightExcipadButtonsMessage[1] == BUTTON_ID_13) {
		exipadButtonPresed = BUTTON_13;
	}
	/* byte 1 */
	if (rightExcipadButtonsMessage[1] == BUTTON_ID_14) {
		exipadButtonPresed = BUTTON_14;
	}
	if (rightExcipadButtonsMessage[2] == BUTTON_ID_15) {
		exipadButtonPresed = BUTTON_15;
	}
	if (rightExcipadButtonsMessage[0] == BUTTON_ID_16) {
		exipadButtonPresed = BUTTON_16;
	}
	if (rightExcipadButtonsMessage[1] == BUTTON_ID_17) {
		exipadButtonPresed = BUTTON_17;
	}
	/* byte 2 */
	if (rightExcipadButtonsMessage[1] == BUTTON_ID_18) {
		exipadButtonPresed = BUTTON_18;
	}
	if (rightExcipadButtonsMessage[0] == BUTTON_ID_19) {
		exipadButtonPresed = BUTTON_19;
	}
	if (rightExcipadButtonsMessage[0] == BUTTON_ID_20) {
		exipadButtonPresed = BUTTON_20;
	}
	if (rightExcipadButtonsMessage[0] == BUTTON_ID_21) {
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
		statusSum = statusSum + rightExcipadButtonsMessage[i];
	}
	if (statusSum == 0) {
		return FALSE;
	} else {
		return TRUE;
	}
}
