

#include "XT28CANSupport.h"
#include "api_lib_basic.h"

#define CAN_1_TX_BUF_LEN_DU8            	(500)
#define CAN_2_TX_BUF_LEN_DU8            	(25)
#define CAN_3_TX_BUF_LEN_DU8            	(25)
#define CAN_4_TX_BUF_LEN_DU8            	(25)

#define CAN_1_RX_BUF_LEN_DU8            	(5)
#define CAN_2_RX_BUF_LEN_DU8            	(15)
#define CAN_3_RX_BUF_LEN_DU8            	(15)
#define CAN_4_RX_BUF_LEN_DU8            	(15)

#define CAN_1_NUM_RX_DATABOXES_DU16    		(100)
#define CAN_2_NUM_RX_DATABOXES_DU16    		(100)
#define CAN_3_NUM_RX_DATABOXES_DU16    		(100)
#define CAN_4_NUM_RX_DATABOXES_DU16    		(10)

void CANConfigureXT28CANChannels(void) {

	/* Register resive buffer */
	static can_Message_ts     can_1_RxBuf_as[CAN_1_RX_BUF_LEN_DU8];
	static can_Message_ts     can_2_RxBuf_as[CAN_2_RX_BUF_LEN_DU8];
	static can_Message_ts     can_3_RxBuf_as[CAN_3_RX_BUF_LEN_DU8];
	static can_Message_ts     can_4_RxBuf_as[CAN_4_RX_BUF_LEN_DU8];

	can_registerRxBuf(CAN_1, can_1_RxBuf_as, CAN_1_RX_BUF_LEN_DU8);
	can_registerRxBuf(CAN_2, can_2_RxBuf_as, CAN_2_RX_BUF_LEN_DU8);
	can_registerRxBuf(CAN_3, can_3_RxBuf_as, CAN_3_RX_BUF_LEN_DU8);
	can_registerRxBuf(CAN_4, can_4_RxBuf_as, CAN_4_RX_BUF_LEN_DU8);

	/* Register transive buffers */
	static can_Message_ts     can_1_TxBuf_as[CAN_1_TX_BUF_LEN_DU8];
	static can_Message_ts     can_2_TxBuf_as[CAN_2_TX_BUF_LEN_DU8];
	static can_Message_ts     can_3_TxBuf_as[CAN_3_TX_BUF_LEN_DU8];
	static can_Message_ts     can_4_TxBuf_as[CAN_4_TX_BUF_LEN_DU8];

	can_registerTxBuf(CAN_1, can_1_TxBuf_as, CAN_1_TX_BUF_LEN_DU8);
	can_registerTxBuf(CAN_2, can_2_TxBuf_as, CAN_3_TX_BUF_LEN_DU8);
	can_registerTxBuf(CAN_3, can_3_TxBuf_as, CAN_3_TX_BUF_LEN_DU8);
	can_registerTxBuf(CAN_4, can_4_TxBuf_as, CAN_4_TX_BUF_LEN_DU8);

	/* Register how many databoxed */
	static can_RxDatabox_ts   can_1_RxDataboxes_as[CAN_1_NUM_RX_DATABOXES_DU16];
	static can_RxDatabox_ts   can_2_RxDataboxes_as[CAN_2_NUM_RX_DATABOXES_DU16];
	static can_RxDatabox_ts   can_3_RxDataboxes_as[CAN_3_NUM_RX_DATABOXES_DU16];
	static can_RxDatabox_ts   can_4_RxDataboxes_as[CAN_4_NUM_RX_DATABOXES_DU16];

	can_registerRxDataboxes(CAN_1, can_1_RxDataboxes_as, CAN_1_NUM_RX_DATABOXES_DU16);
	can_registerRxDataboxes(CAN_2, can_2_RxDataboxes_as, CAN_2_NUM_RX_DATABOXES_DU16);
	can_registerRxDataboxes(CAN_3, can_3_RxDataboxes_as, CAN_3_NUM_RX_DATABOXES_DU16);
	can_registerRxDataboxes(CAN_4, can_4_RxDataboxes_as, CAN_4_NUM_RX_DATABOXES_DU16);
}

void CANSend_sint16(uint8 CANChannel, uint32 ID, sint16 A, sint16 B, sint16 C, sint16 D) {  //Send up to 4x16bit Variables on CAN1 msg
	uint8 data_au8_sms[8] = {0};
	data_au8_sms[0] = A;
	data_au8_sms[1] = A >> 8;
	data_au8_sms[2] = B;
	data_au8_sms[3] = B >> 8;
	data_au8_sms[4] = C;
	data_au8_sms[5] = C >> 8;
	data_au8_sms[6] = D;
	data_au8_sms[7] = D >> 8;

	can_sendData(CANChannel, ID, CAN_EXD_DU8, 8, data_au8_sms);
}

void CANSend_uint16(uint8 CANChannel, uint32 ID, uint16 A, uint16 B, uint16 C, uint16 D) {  //Send up to 4x16bit Variables on CAN1 msg
	uint8 data_au8_sms[8] = {0};
	data_au8_sms[0] = A;
	data_au8_sms[1] = A >> 8;
	data_au8_sms[2] = B;
	data_au8_sms[3] = B >> 8;
	data_au8_sms[4] = C;
	data_au8_sms[5] = C >> 8;
	data_au8_sms[6] = D;
	data_au8_sms[7] = D >> 8;

	can_sendData(CANChannel, ID, CAN_EXD_DU8, 8, data_au8_sms);
}

void CANSendSupplyVoltageOnCAN(uint8 CANChannel, uint32 ID) {
	sint16 batterySupplyVoltage = sys_getSupply(VB);
	sint16 sensorSupplyVoltage1 = sys_getSupply(VSS_1);
	sint16 sensorSupplyVoltage3 = sys_getSupply(VSS_3);

	g_debug6 = batterySupplyVoltage;
	CANSend_sint16(CANChannel, ID,
			batterySupplyVoltage,
			sensorSupplyVoltage1,
			sensorSupplyVoltage3,
			0
	);
}

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

		can_sendData(CANChannel, CAN_ID_DEBUG_MSG_1, CAN_EXD_DU8, 8, debug1msg);
		can_sendData(CANChannel, CAN_ID_DEBUG_MSG_2, CAN_EXD_DU8, 8, debug2msg);
		can_sendData(CANChannel, CAN_ID_DEBUG_MSG_3, CAN_EXD_DU8, 8, debug3msg);
}




