#include "EngineComunicationsCAN.h"

//CAN3 (*CAN Engine*)(*From Diesel*)
#define	DB_RX_ENGINE_TSC_EEC1 				3
#define	DB_RX_ENGINE_TEMP					4
#define	DB_RX_ENGINE_HOURS_STATUS			5
#define	DB_RX_ENGINE_FLUID_LEVEL_PRESSURE	6
#define	DB_RX_ENGINE_FUEL_ECONOMY			7
#define	DB_RX_ENGINE_INLET_EXHAUST			8
#define	DB_RX_ENGINE_ERROR					9

#define CAN_ENGINE		CAN_3

#define DB_TX_ENGINE 						1 		/*Transmit engine reference*/

//From Engine						//Transmission
#define CAN_ID_RX_ENGINE_TSC_EEC1				0xCF00400
#define CAN_ID_RX_ENGINE_TEMP					0x18FEEE00
#define CAN_ID_RX_ENGINE_HOURS_STATUS			0x18FF3500
#define CAN_ID_RX_ENGINE_FLUID_LEVEL_PRESSURE	0x18FEEF00
#define CAN_ID_RX_ENGINE_INLET_EXHAUST 			0x18FEF600
#define CAN_ID_RX_ENGINE_FUEL_ECONOMY 			0x18FEF200
#define CAN_ID_RX_ENGINE_ERROR 					0x18FF0000
#define CAN_ID_RX_EEC2							0xCF00300

		//Engine
#define CAN_ID_TX_ENGINE						0X1		  	//Sends engine speed ref to engine(*Engine ICE_TSC1_P1_Sisu_Proprietary mex ID hex 0;*)
		//System info
#define CAN_ID_TX_ENGINE_INLET_EXHAUST			0x18FEF600	//Engine data
#define CAN_ID_TX_ENGINE_FUEL_ECONOMY			0x18FEF200
#define CAN_ID_TX_ENGINE_TSC_EEC1 				0xCF00400
#define CAN_ID_TX_ENGINE_TEMP					0x18FEEE00
#define CAN_ID_TX_ENGINE_HOURS_STATUS			0x18FF3500
#define CAN_ID_TX_ENGINE_FLUID_LEVEL_PRESSURE	0x18FEEF00

/* Private decelerations */
static void engineTemperatureMessageCallback(void);
static void engineLoadMessageCallback(void);

/* Start of function implementation */
void ECCInitAndSetupEngineCANCommunications(void) {

	/* Engine temp message 2ms cycletime with callback */
	static can_DataboxData_ts statusMessageDataboxBuffer[5];
	can_initRxDatabox(CAN_ENGINE,
			DB_RX_ENGINE_TEMP,
			CAN_ID_RX_ENGINE_TEMP,
			CAN_EXD_DU8,
			8,
			statusMessageDataboxBuffer,
			5,
			engineTemperatureMessageCallback
	);

	static can_DataboxData_ts engineLoadDataboxBuffer[5];
	can_initRxDatabox(CAN_ENGINE,
			11,
			CAN_ID_RX_EEC2,
			CAN_EXD_DU8,
			8,
			engineLoadDataboxBuffer,
			5,
			engineLoadMessageCallback
	);


	/* Retrice databoxes */
	can_cfgRxDatabox(CAN_ENGINE, DB_RX_ENGINE_TSC_EEC1,
			CAN_ID_RX_ENGINE_TSC_EEC1,
			CAN_EXD_DU8
	);
	/*
	can_cfgRxDatabox(CAN_ENGINE,
			DB_RX_ENGINE_TEMP,
			CAN_ID_RX_ENGINE_TEMP,
			CAN_EXD_DU8
	);
	*/
	can_cfgRxDatabox(CAN_ENGINE,
			DB_RX_ENGINE_HOURS_STATUS,
			CAN_ID_RX_ENGINE_HOURS_STATUS,
			CAN_EXD_DU8
	);
	can_cfgRxDatabox(CAN_ENGINE,
			DB_RX_ENGINE_FLUID_LEVEL_PRESSURE,
			CAN_ID_RX_ENGINE_FLUID_LEVEL_PRESSURE,
			CAN_EXD_DU8);
	can_cfgRxDatabox(CAN_ENGINE,
			DB_RX_ENGINE_INLET_EXHAUST,
			CAN_ID_RX_ENGINE_INLET_EXHAUST,
			CAN_EXD_DU8);
	can_cfgRxDatabox(CAN_ENGINE,
			DB_RX_ENGINE_FUEL_ECONOMY,
			CAN_ID_RX_ENGINE_FUEL_ECONOMY,
			CAN_EXD_DU8
	);
	can_cfgRxDatabox(CAN_ENGINE,
			DB_RX_ENGINE_ERROR,
			CAN_ID_RX_ENGINE_ERROR,
			CAN_EXD_DU8
	);

	/* Send databoxes */
	//can_cfgTxDatabox(CAN_MESSAGES,DB_TX_ENGINE_FLUID_LEVEL_PRESSURE ,CAN_ID_TX_ENGINE_FLUID_LEVEL_PRESSURE, CAN_EXD_DU8);
	//can_cfgTxDatabox(CAN_MESSAGES,DB_TX_ENGINE_FUEL_ECONOMY ,CAN_ID_TX_ENGINE_FUEL_ECONOMY, CAN_EXD_DU8);
	//can_cfgTxDatabox(CAN_MESSAGES,DB_TX_ENGINE_HOURS_STATUS ,CAN_ID_TX_ENGINE_HOURS_STATUS, CAN_EXD_DU8);
	//can_cfgTxDatabox(CAN_MESSAGES,DB_TX_ENGINE_INLET_EXHAUST ,CAN_ID_TX_ENGINE_INLET_EXHAUST, CAN_EXD_DU8);
	//can_cfgTxDatabox(CAN_MESSAGES,DB_TX_ENGINE_TEMP ,CAN_ID_TX_ENGINE_TEMP, CAN_EXD_DU8);
	//can_cfgTxDatabox(CAN_MESSAGES, DB_TX_ENGINE_TSC_EEC1, CAN_ID_TX_ENGINE_TSC_EEC1, CAN_EXD_DU8);
	can_cfgTxDatabox(CAN_ENGINE, DB_TX_ENGINE , CAN_ID_TX_ENGINE, CAN_EXD_DU8);
}


/* Engine messages */
static uint8 msg_ENGINE_FLUID_LEVEL_PRESSURE[8] = {0};
static uint8 msg_ENGINE_FUEL_ECONOMY[8] = {0};
static uint8 msg_ENGINE_HOURS_STATUS[8] = {0};
static uint8 msg_ENGINE_INLET_EXHAUST[8] = {0};
static uint8 msg_ENGINE_TSC_EEC1[8] = {0};
static uint8 msg_ENGINE_ERROR[8] = {0};

static int Engine_ref_speed = 800;
void ECCUpdateDataFromCAN(void) {

	/* Get new data */
	uint8 DataboxNumBytes_u8 = 8;
	can_getDatabox(CAN_ENGINE, DB_RX_ENGINE_FLUID_LEVEL_PRESSURE, msg_ENGINE_FLUID_LEVEL_PRESSURE, &DataboxNumBytes_u8);
	can_getDatabox(CAN_ENGINE, DB_RX_ENGINE_FUEL_ECONOMY, msg_ENGINE_FUEL_ECONOMY, &DataboxNumBytes_u8);
	can_getDatabox(CAN_ENGINE, DB_RX_ENGINE_HOURS_STATUS, msg_ENGINE_HOURS_STATUS, &DataboxNumBytes_u8);
	can_getDatabox(CAN_ENGINE, DB_RX_ENGINE_INLET_EXHAUST, msg_ENGINE_INLET_EXHAUST, &DataboxNumBytes_u8);
	can_getDatabox(CAN_ENGINE, DB_RX_ENGINE_TSC_EEC1, msg_ENGINE_TSC_EEC1, &DataboxNumBytes_u8);
	can_getDatabox(CAN_ENGINE, DB_RX_ENGINE_ERROR, msg_ENGINE_ERROR, &DataboxNumBytes_u8);

	/* Send data to the Engine */
	//Construct msg ENGINE
	uint8 data_au8_engine[8];
	data_au8_engine[0] = 1;
	data_au8_engine[1] = Engine_ref_speed * 8;
	data_au8_engine[2] = Engine_ref_speed * 8 >> 8;
	data_au8_engine[3] = 0;
	data_au8_engine[4] = 255;
	data_au8_engine[5] = 0;
	data_au8_engine[6] = 255;
	data_au8_engine[7] = 255;

	//Engine
	if (0 == can_sendDatabox(CAN_ENGINE, DB_TX_ENGINE, 8, data_au8_engine)) {}

}

static uint8 msg_EngineLoad[8] = {0};
static void engineLoadMessageCallback(void) {
	uint8 DataboxNumBytes_u8 = 8;
	can_getDatabox(CAN_ENGINE,
			11,
			msg_EngineLoad,
			&DataboxNumBytes_u8
	);

	//g_debug2_4 = msg_EngineLoad[2];
}

static uint8 msg_ENGINE_TEMP[8] = {0};
static void engineTemperatureMessageCallback(void) {
	uint8 DataboxNumBytes_u8 = 8;
	can_getDatabox(CAN_ENGINE,
			DB_RX_ENGINE_TEMP,
			msg_ENGINE_TEMP,
			&DataboxNumBytes_u8
	);
	g_debug3_2 = g_debug3_2 + msg_ENGINE_TEMP[0] + 1;
}

void ECCSetEngineRPMReference(int RPMReference) {
	/* Saturate just in case */
	if (RPMReference < 800) {
		RPMReference = 800;
	}
	else if (RPMReference > 1800) {
		RPMReference = 1800;
	}
	/* Set engine reference variable */
	Engine_ref_speed = RPMReference;
}

EngineData ECCGetEngineData(void) {

	EngineData engineData;

	engineData.engineTemperature = msg_ENGINE_TEMP[0] - 40;

	g_debug3_1 = engineData.engineTemperature;

	engineData.engineSpeedActual = (msg_ENGINE_TSC_EEC1[3] + (msg_ENGINE_TSC_EEC1[4] << 8)) / 8;
	engineData.engineLoad = msg_EngineLoad[2];

	return engineData;
}





