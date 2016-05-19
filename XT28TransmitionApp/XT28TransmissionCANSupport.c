#include "XT28TransmissionCANSupport.h"

#define DB_RX_INDEX_CAN_2					11
#define DB_RX_INDEX_CAN_3					10
#define DB_RX_INDEX_CAN_4					1


void XT28TCANInitAndSetup(void) {

	can_cfgBufs(CAN_1, 5, 5, 40, 40);
	can_cfgBufs(CAN_2, 5, 5, 20, DB_RX_INDEX_CAN_2);
	can_cfgBufs(CAN_3, 5, 5, 20, DB_RX_INDEX_CAN_3);
	can_cfgBufs(CAN_4, 5, 5, 20, DB_RX_INDEX_CAN_4);

	can_init(CAN_1, BAUD_1000K);
	can_init(CAN_2, BAUD_250K);
	can_init(CAN_3, BAUD_250K);
	can_init(CAN_4, BAUD_250K);

}

/* Initialazation of global debug variabels */
sint32 g_debug1 = 0;
sint32 g_debug2 = 0;
sint32 g_debug3 = 0;
sint32 g_debug4 = 0;
sint32 g_debug5 = 0;
sint32 g_debug6 = 0;
void CANSendDebuggMessage(uint8 CANChannel) {
	//Debugging for force controller
	uint8 debug1msg[8] = {0}; //
	uint8 debug2msg[8] = {0}; //
	uint8 debug3msg[8] = {0}; //

	//Construct Debugmsg 1
	debug1msg[0] = g_debug1;
	debug1msg[1] = g_debug1 >> 8;
	debug1msg[2] = g_debug1 >> 16;
	debug1msg[3] = g_debug1 >> 24;
	debug1msg[4] = g_debug2;
	debug1msg[5] = g_debug2 >> 8;
	debug1msg[6] = g_debug2 >> 16;
	debug1msg[7] = g_debug2 >> 24;

	//Construct Debugmsg 2
	debug2msg[0] = g_debug3;
	debug2msg[1] = g_debug3 >> 8;
	debug2msg[2] = g_debug3 >> 16;
	debug2msg[3] = g_debug3 >> 24;
	debug2msg[4] = g_debug4;
	debug2msg[5] = g_debug4 >> 8;
	debug2msg[6] = g_debug4 >> 16;
	debug2msg[7] = g_debug4 >> 24;

	//Construct Debugmsg 3
	debug3msg[0] = g_debug5;
	debug3msg[1] = g_debug5 >> 8;
	debug3msg[2] = g_debug5 >> 16;
	debug3msg[3] = g_debug5 >> 24;
	debug3msg[4] = g_debug6;
	debug3msg[5] = g_debug6 >> 8;
	debug3msg[6] = g_debug6 >> 16;
	debug3msg[7] = g_debug6 >> 24;

	can_sendData(CANChannel, CAN_ID_DEBUG1, CAN_EXD_DU8, 8, debug1msg);
	can_sendData(CANChannel, CAN_ID_DEBUG2, CAN_EXD_DU8, 8, debug2msg);
	can_sendData(CANChannel, CAN_ID_DEBUG3, CAN_EXD_DU8, 8, debug3msg);
}
