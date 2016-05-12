#include "Display.h"

/* Output CAN ID */
#define DISPLAY_ID					(0x18FE1040)
#define DISPLAY_POS_ID_MIDDLE_BACK	(0x18FE1041)
#define DISPLAY_POS_ID_FRONT		(0x18FE1042)

/* Input CAN ID */
#define STATUS_ID					(0x18FE1030)
#define STATUS_MSG_BUFF_LEN			(5)

/* Prototypes */
static void forwarderStatusMessageCallback(void);


/* Program start */

void DisplayConfigureCAN(uint8 CANChannel, int statusDataboxNr) {

	static can_DataboxData_ts statusMessageDataboxBuffer[STATUS_MSG_BUFF_LEN];
	int statusMessageNumOfBytes = 8;

	can_initRxDatabox(CANChannel,
			statusDataboxNr,
			STATUS_ID,
			CAN_EXD_DU8,
			statusMessageNumOfBytes,
			statusMessageDataboxBuffer,
			STATUS_MSG_BUFF_LEN,
			forwarderStatusMessageCallback
	);

}

static uint8 statusMessage[8] = {0};
static void forwarderStatusMessageCallback(void) {
	uint8 statusMsgNumBytes_u8;
	can_getDatabox(CAN_4, 1, statusMessage, &statusMsgNumBytes_u8);
}


chairPosition DisplayGetChairPosition(void) {
	if (statusMessage[3] == 0x01) {
		return CHAIR_IS_FRONT;
	}
	return CHAIR_IS_BACK;
}

handBreak DisplayGetHandBreakState(void) {
	g_debug3 = statusMessage[0];
	if (statusMessage[0] == 0x04) {
		return BREAK_IS_TRUE;
	}
	return BREAK_IS_FALSE;
}


static uint8 displayMessageArrayOut[8] = {0};
void DisplaySetADStateTo(bool state) {
	displayMessageArrayOut[7] = state;
}

void DisplaySetPDStateTo(bool state) {
	displayMessageArrayOut[6] = state;
}

void DisplaySetSensorAlertStateTo(bool state) {
	displayMessageArrayOut[0] = state;
}

void DisplaySetHeightReference(int offset) {
	displayMessageArrayOut[4] = offset;
	displayMessageArrayOut[5] = offset >> 8;
}

void DisplaySendLatestStatesOnCAN(void) {

	/* 1. AD states */
	can_sendData(CAN_4, DISPLAY_ID, CAN_EXD_DU8, 8, displayMessageArrayOut);

	/* 2. Cylinder position states */
	PAPOSSendPosDataOnCAN(CAN_4,
			DISPLAY_POS_ID_MIDDLE_BACK,
			DISPLAY_POS_ID_FRONT
	);
}



