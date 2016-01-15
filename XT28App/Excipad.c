#include "Excipad.h"
#include "XT28CANSupport.h"


/* Config */
#define EXIPAD_BUTTONS_DB_BUFF_LEN  	5
#define EXIPAD_JOYSTICK_DB_BUFF_LEN  	5

/* CAN message exipad */
#define BUTTON_ID_1		0x10 //16	 //Byte 4, bit 5
#define BUTTON_ID_3 	0x01 //1	 //Byte 4, bit 1
#define BUTTON_ID_4		0x04 //4     //Byte 5, bit 3
#define BUTTON_ID_6		0x40 //64	 //Byte 4, bit 7
#define BUTTON_ID_7		0x01 //1	 //Byte 6, bit 1
#define BUTTON_ID_9		0x10 //16	 //Byte 5, bit 5
#define BUTTON_ID_19	0x40 //64	 //Byte 3, bit 3
#define BUTTON_ID_20	0x04 //4	 //Byte 3, bit 7
#define BUTTON_ID_16	0x10 //16	 //Byte 2, bit 5
#define BUTTON_ID_17	0x40 //64	 //Byte 2, bit 7
#define BUTTON_ID_18	0x01 //1 	 //Byte 3, bit 1

/* Joystick */
#define JOYSTICK_Y_HIGH_POINT				4300
#define JOYSTICK_Y_MID_POINT				2350
#define JOYSTICK_Y_LOW_POINT				350
#define JOYSTICK_Y_DEADBAND					200
#define JOYSTICK_Y_HIGH_DEADBAND			JOYSTICK_Y_MID_POINT+JOYSTICK_Y_DEADBAND
#define JOYSTICK_Y_LOW_DEADBAND				JOYSTICK_Y_MID_POINT-JOYSTICK_Y_DEADBAND

/* Priave Prototypes */
static void exipadButtonsCallback(void);
static void exipadJoystickCallback(void);
//static int checkButtonState(uint8 message, uint8 buttonID, int currentState, int toggleIfThisState);

static int exipadCANChannel = 0;
static int exipadButtonDBNr = 0;
static int exipadJoystrickDBNr = 0;
void EXPConfigure(uint8 CANChannel, int buttonDataboxNr, int joystrickDataboxNr) {

	exipadCANChannel    = CANChannel;
	exipadButtonDBNr    = buttonDataboxNr;
	exipadJoystrickDBNr = joystrickDataboxNr;

	static can_DataboxData_ts exipadButtonsDataboxBuffer[EXIPAD_BUTTONS_DB_BUFF_LEN];
	static can_DataboxData_ts exipadJoystrickDataboxBuffer[EXIPAD_JOYSTICK_DB_BUFF_LEN];
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
			joystrickDataboxNr,
			CAN_ID_JOYSTICK_Y,
			CAN_EXD_DU8,
			exipadMessageNumOfBytes,
			exipadJoystrickDataboxBuffer,
			EXIPAD_JOYSTICK_DB_BUFF_LEN,
			exipadJoystickCallback
	);
}

static uint8 leftExcipadButtonsMessage[8];
static void exipadButtonsCallback(void) {
	uint8 LeftExcipadNumBytes_u8 = 0;
	can_getDatabox(exipadCANChannel, exipadButtonDBNr, leftExcipadButtonsMessage, &LeftExcipadNumBytes_u8);
}

static void exipadJoystickCallback(void) {
	// to be implemented
}


typedef enum {
	ACCEPT_NEW_MESSAGE,
	NOT_ACCEPT_NEW_MESSAGE
} exipadCANMessageState;

exipadButton EXPGetLastPressedButtonWithToggle(void) {
	static exipadCANMessageState exipadCANMessageState = ACCEPT_NEW_MESSAGE;
	static exipadButton lastPressedButton = NONE;
	static exipadButton lastPressedButtonOld = NONE;
	switch (exipadCANMessageState) {
	case ACCEPT_NEW_MESSAGE:
		if (EXPGetUserIsHoldingAButtonDown() == TRUE) {
			lastPressedButton = EXPGetCurrentlyPressedButton();
			if (lastPressedButton == lastPressedButtonOld) {
				lastPressedButton = NONE;
			}
			exipadCANMessageState = NOT_ACCEPT_NEW_MESSAGE;
		}
		break;
	case NOT_ACCEPT_NEW_MESSAGE:
		if (EXPGetUserIsHoldingAButtonDown() == FALSE) {
			exipadCANMessageState = ACCEPT_NEW_MESSAGE;
		}
		break;
	}
	lastPressedButtonOld = lastPressedButton;
	return lastPressedButton;
}

exipadButton EXPGetCurrentlyPressedButton(void) {
	static exipadButton exipadButtonPresed = NONE;
	if (leftExcipadButtonsMessage[3] == BUTTON_ID_1) {
		exipadButtonPresed = BUTTON_1;
	}
	if (leftExcipadButtonsMessage[3] == BUTTON_ID_3) {
		exipadButtonPresed = BUTTON_3;
	}
	if (leftExcipadButtonsMessage[4] == BUTTON_ID_4) {
		exipadButtonPresed = BUTTON_4;
	}
	if (leftExcipadButtonsMessage[3] == BUTTON_ID_6) {
		exipadButtonPresed = BUTTON_6;
	}
	if (leftExcipadButtonsMessage[5] == BUTTON_ID_7) {
		exipadButtonPresed = BUTTON_7;
	}
	if (leftExcipadButtonsMessage[4] == BUTTON_ID_9) {
		exipadButtonPresed = BUTTON_9;
	}
	if (leftExcipadButtonsMessage[2] == BUTTON_ID_19) {
		exipadButtonPresed = BUTTON_19;
	}
	if (leftExcipadButtonsMessage[2] == BUTTON_ID_20) {
		exipadButtonPresed = BUTTON_20;
	}
	if (leftExcipadButtonsMessage[1] == BUTTON_ID_16) {
		exipadButtonPresed = BUTTON_16;
	}
	if (leftExcipadButtonsMessage[1] == BUTTON_ID_17) {
		exipadButtonPresed = BUTTON_17;
	}
	if (leftExcipadButtonsMessage[2] == BUTTON_ID_18) {
		exipadButtonPresed = BUTTON_18;
	}
	return exipadButtonPresed;
}

bool EXPGetUserIsHoldingAButtonDown(void) {
	uint16 statusSum = 0;
	int i = 0;
	for (i = 0; i < 8; i++) {
		statusSum = statusSum + leftExcipadButtonsMessage[i];
	}
	if (statusSum == 0) {
		return FALSE;
	} else {
		return TRUE;
	}
}

/*
static int checkButtonState(uint8 message, uint8 buttonID, int currentState, int toggleIfThisState) {
	if (message == buttonID) {
		if (currentState == toggleIfThisState) {
			return 0;
		} else {
			return toggleIfThisState;
		}
	}
}
 */




