

#include "XT28CANSupport.h"
#include "api_lib_basic.h"

#define CAN_1_TX_BUF_LEN_DU8            	500
#define CAN_2_TX_BUF_LEN_DU8            	25
#define CAN_3_TX_BUF_LEN_DU8            	25

#define CAN_1_RX_BUF_LEN_DU8            	5
#define CAN_2_RX_BUF_LEN_DU8            	15
#define CAN_3_RX_BUF_LEN_DU8            	15

#define CAN_1_NUM_RX_DATABOXES_DU16    		100
#define CAN_2_NUM_RX_DATABOXES_DU16    		100
#define CAN_3_NUM_RX_DATABOXES_DU16    		100

void CANConfigureXT28CANChannels(void) {

	// register restrive buffer
	static can_Message_ts     can_1_RxBuf_as[CAN_1_RX_BUF_LEN_DU8];
	static can_Message_ts     can_2_RxBuf_as[CAN_2_RX_BUF_LEN_DU8];
	static can_Message_ts     can_3_RxBuf_as[CAN_3_RX_BUF_LEN_DU8];

	can_registerRxBuf(CAN_1, can_1_RxBuf_as, CAN_1_RX_BUF_LEN_DU8);
	can_registerRxBuf(CAN_2, can_2_RxBuf_as, CAN_2_RX_BUF_LEN_DU8);
	can_registerRxBuf(CAN_3, can_3_RxBuf_as, CAN_3_RX_BUF_LEN_DU8);

	// Registrer transive buffers
	static can_Message_ts     can_1_TxBuf_as[CAN_1_TX_BUF_LEN_DU8];
	static can_Message_ts     can_2_TxBuf_as[CAN_2_TX_BUF_LEN_DU8];
	static can_Message_ts     can_3_TxBuf_as[CAN_3_TX_BUF_LEN_DU8];

	can_registerTxBuf(CAN_1, can_1_TxBuf_as, CAN_1_TX_BUF_LEN_DU8);
	can_registerTxBuf(CAN_2, can_2_TxBuf_as, CAN_3_TX_BUF_LEN_DU8);
	can_registerTxBuf(CAN_3, can_3_TxBuf_as, CAN_3_TX_BUF_LEN_DU8);

	//Register how many databoxed
	static can_RxDatabox_ts   can_1_RxDataboxes_as[CAN_1_NUM_RX_DATABOXES_DU16];
	static can_RxDatabox_ts   can_2_RxDataboxes_as[CAN_2_NUM_RX_DATABOXES_DU16];
	static can_RxDatabox_ts   can_3_RxDataboxes_as[CAN_3_NUM_RX_DATABOXES_DU16];

	can_registerRxDataboxes(CAN_1, can_1_RxDataboxes_as, CAN_1_NUM_RX_DATABOXES_DU16);
	can_registerRxDataboxes(CAN_2, can_2_RxDataboxes_as, CAN_2_NUM_RX_DATABOXES_DU16);
	can_registerRxDataboxes(CAN_3, can_3_RxDataboxes_as, CAN_3_NUM_RX_DATABOXES_DU16);
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
	CANSend_sint16(CANChannel, ID,
			batterySupplyVoltage,
			sensorSupplyVoltage1,
			sensorSupplyVoltage3,
			0
	);
}




