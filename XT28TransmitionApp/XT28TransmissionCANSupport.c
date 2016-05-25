#include "XT28TransmissionCANSupport.h"

#define DB_RX_INDEX_CAN_2					11
#define DB_RX_INDEX_CAN_3					10
#define DB_RX_INDEX_CAN_4					1

#define CAN_1_NUM_RX_DATABOXES_DU16    		(100)
#define CAN_2_NUM_RX_DATABOXES_DU16    		(100)
#define CAN_3_NUM_RX_DATABOXES_DU16    		(100)
#define CAN_4_NUM_RX_DATABOXES_DU16    		(10)


void XT28TCANInitAndSetup(void) {

	can_cfgBufs(CAN_1, 50, 50, 40, 40);
	can_cfgBufs(CAN_2, 50, 50, 20, DB_RX_INDEX_CAN_2);
	can_cfgBufs(CAN_3, 50, 50, 20, DB_RX_INDEX_CAN_3);
	can_cfgBufs(CAN_4, 50, 50, 20, DB_RX_INDEX_CAN_4);

	/* Register how many databoxed */
	static can_RxDatabox_ts   can_1_RxDataboxes_as[CAN_1_NUM_RX_DATABOXES_DU16];
	static can_RxDatabox_ts   can_2_RxDataboxes_as[CAN_2_NUM_RX_DATABOXES_DU16];
	static can_RxDatabox_ts   can_3_RxDataboxes_as[CAN_3_NUM_RX_DATABOXES_DU16];
	static can_RxDatabox_ts   can_4_RxDataboxes_as[CAN_4_NUM_RX_DATABOXES_DU16];

	can_registerRxDataboxes(CAN_1, can_1_RxDataboxes_as, CAN_1_NUM_RX_DATABOXES_DU16);
	can_registerRxDataboxes(CAN_2, can_2_RxDataboxes_as, CAN_2_NUM_RX_DATABOXES_DU16);
	can_registerRxDataboxes(CAN_3, can_3_RxDataboxes_as, CAN_3_NUM_RX_DATABOXES_DU16);
	can_registerRxDataboxes(CAN_4, can_4_RxDataboxes_as, CAN_4_NUM_RX_DATABOXES_DU16);

	can_init(CAN_1, BAUD_1000K);
	can_init(CAN_2, BAUD_250K);
	can_init(CAN_3, BAUD_250K);
	can_init(CAN_4, BAUD_250K);
}

/* Initialazation of global debug variabels */
sint16 g_debug1_1 = 0;
sint16 g_debug1_2 = 0;
sint16 g_debug1_3 = 0;
sint16 g_debug1_4 = 0;
sint16 g_debug2_1 = 0;
sint16 g_debug2_2 = 0;
sint16 g_debug2_3 = 0;
sint16 g_debug2_4 = 0;
sint16 g_debug3_1 = 0;
sint16 g_debug3_2 = 0;
sint16 g_debug3_3 = 0;
sint16 g_debug3_4 = 0;
void CANSendDebuggMessage(uint8 CANChannel) {
	/* Debugging for force controller */
	uint8 debug1msg[8] = {0}; //
	uint8 debug2msg[8] = {0}; //
	uint8 debug3msg[8] = {0}; //

	/* Construct Debugmsg 1 */
	debug1msg[0] = g_debug1_1;
	debug1msg[1] = g_debug1_1 >> 8;
	debug1msg[2] = g_debug1_2;
	debug1msg[3] = g_debug1_2 >> 8;
	debug1msg[4] = g_debug1_3;
	debug1msg[5] = g_debug1_3 >> 8;
	debug1msg[6] = g_debug1_4;
	debug1msg[7] = g_debug1_4 >> 8;

	/* Construct Debugmsg 2 */
	debug2msg[0] = g_debug2_1;
	debug2msg[1] = g_debug2_1 >> 8;
	debug2msg[2] = g_debug2_2;
	debug2msg[3] = g_debug2_2 >> 8;
	debug2msg[4] = g_debug2_3;
	debug2msg[5] = g_debug2_3 >> 8;
	debug2msg[6] = g_debug2_4;
	debug2msg[7] = g_debug2_4 >> 8;

	/* Construct Debugmsg 3 */
	debug3msg[0] = g_debug3_1;
	debug3msg[1] = g_debug3_1 >> 8;
	debug3msg[2] = g_debug3_2;
	debug3msg[3] = g_debug3_2 >> 8;
	debug3msg[4] = g_debug3_3;
	debug3msg[5] = g_debug3_3 >> 8;
	debug3msg[6] = g_debug3_4;
	debug3msg[7] = g_debug3_4 >> 8;

	can_sendData(CANChannel, CAN_ID_DEBUG1, CAN_EXD_DU8, 8, debug1msg);
	can_sendData(CANChannel, CAN_ID_DEBUG2, CAN_EXD_DU8, 8, debug2msg);
	can_sendData(CANChannel, CAN_ID_DEBUG3, CAN_EXD_DU8, 8, debug3msg);
}
