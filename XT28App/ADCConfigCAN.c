#include "ADCConfigCAN.h"


/* Defines */
#define CONF_MSG_ID_2			0x17FE000A
#define CONF_MSG_ID_3			0x17FE000B
#define CONF_MSG_ID_4			0x17FE000C
#define CONF_MSG_ID_5			0x17FE000D
#define DATABOX_BUFFER_LENGTH 	5

/* Setup default parameter values */
static float heightReference = 250;
static float phiReference = 0;
static float thetaReference = 0;
static float forceReference = 0;

/* Controll parameters set thouth CAN */
static float heightP = 0;
static float heightI = 0;

static float phiP = 0;
static float phiI = 0;

static float thetaP = 0;
static float thetaI = 0;

static float skyChassiGain = 0;
static float skyPhiGain    = 0;
static float skyThetaGain  = 0;
static float skyWheelGain  = 0;


/* Private prototypes */
static void heightParametersCallback(void);
static void thetaPhiProportionalParametersCallback(void);
static void integratorParametersCallback(void);
static void referenceParametersCallback(void);

void ADCFGConfigureParameterSettingsFromCAN(uint8 CANChannel, uint16 databoxNr1, uint16 databoxNr2, uint16 databoxNr3, uint16 databoxNr4) {

	int configMessageNumOfBytes = 8;

	static can_DataboxData_ts heightParameters_Buffer[DATABOX_BUFFER_LENGTH];
	can_initRxDatabox(CANChannel,
			databoxNr1,
			CONF_MSG_ID_2,
			CAN_EXD_DU8,
			configMessageNumOfBytes,
			heightParameters_Buffer,
			DATABOX_BUFFER_LENGTH,
			heightParametersCallback
	);

	static can_DataboxData_ts thetaPhiProportionalParameters_Buffer[DATABOX_BUFFER_LENGTH];
	can_initRxDatabox(CANChannel,
			databoxNr2,
			CONF_MSG_ID_3,
			CAN_EXD_DU8,
			configMessageNumOfBytes,
			thetaPhiProportionalParameters_Buffer,
			DATABOX_BUFFER_LENGTH,
			thetaPhiProportionalParametersCallback
	);

	static can_DataboxData_ts integratorParameters_Buffer[DATABOX_BUFFER_LENGTH];
	can_initRxDatabox(CANChannel,
			databoxNr3,
			CONF_MSG_ID_4,
			CAN_EXD_DU8,
			configMessageNumOfBytes,
			integratorParameters_Buffer,
			DATABOX_BUFFER_LENGTH,
			integratorParametersCallback
	);

	static can_DataboxData_ts referenceParameters_Buffer[DATABOX_BUFFER_LENGTH];
	can_initRxDatabox(CANChannel,
			databoxNr4,
			CONF_MSG_ID_5,
			CAN_EXD_DU8,
			configMessageNumOfBytes,
			referenceParameters_Buffer,
			DATABOX_BUFFER_LENGTH,
			referenceParametersCallback
	);
}

static void referenceParametersCallback(void) {
	sint8 confData_au8[8] = {0};
	sint8 confNumBytes_u8;

	/* Databox Get Message data and assign to variables */
	if (0 == can_getDatabox(CAN_1, 8, confData_au8, &confNumBytes_u8)) {
		phiReference 			= confData_au8[0];
		thetaReference     		= confData_au8[1];
	}
}

static void heightParametersCallback(void) {
	uint8 confData_au8[8] = {0};
	uint8 confNumBytes_u8;

	/* Databox Get Message data and assign to variables */
	if (0 == can_getDatabox(CAN_1, 3, confData_au8, &confNumBytes_u8)) {
		forceReference	 	= ((confData_au8[1] << 8) | (confData_au8[0])) / 10;   // Add two 8-bits to an unsigned 16-bit. Not sure what this dude was even used for
		heightP       		= ((confData_au8[3] << 8) | (confData_au8[2]));
		skyWheelGain    	= ((confData_au8[5] << 8) | (confData_au8[4]));
		heightReference 	= ((confData_au8[7] << 8) | (confData_au8[6]));
	}
}

static void thetaPhiProportionalParametersCallback(void) {
	uint8 confData_au8[8] = {0};
	uint8 confNumBytes_u8;

	/* Databox Get Message data and assign to variables */
	if (0 == can_getDatabox(CAN_1, 4, confData_au8, &confNumBytes_u8)) {
		thetaP    	 = ((confData_au8[1] << 8) | (confData_au8[0]));
		phiP      	 = ((confData_au8[3] << 8) | (confData_au8[2]));
		skyThetaGain = ((confData_au8[5] << 8) | (confData_au8[4]));
		skyPhiGain   = ((confData_au8[7] << 8) | (confData_au8[6]));
	}
}

static void integratorParametersCallback(void) {
	uint8 confData_au8[8];
	uint8 confNumBytes_u8;

	/* Databox Get Message data and assign to variables */
	if (0 == can_getDatabox(CAN_1, 7, confData_au8, &confNumBytes_u8)){
		heightI       = confData_au8[1];
		phiI   		  = confData_au8[2];
		thetaI 		  = confData_au8[3];
		skyChassiGain = confData_au8[4];
	}
}


void ADCSetControlParametersWithCAN(void) {
	ADPIDSetHeightControlParametersPID(heightP, 0, 0);
	ADPIDSetPhiControlParametersPID   (phiP,    0, 0);
	ADPIDSetThetaControlParametersPID (thetaP,  0, 0);
	ADPIDSetForceControllerParametersPID(heightI, 0, 0);
}

/* Get functions */
float ADCFGetCANHeightRef(void) {
	return heightReference;
}
float ADCFGetCANPhiRef(void) {
	return phiReference;
}
float ADCGetCANThetaRef(void) {
	return thetaReference;
}
float ADCGetCANForcePGain(void) {
	return heightI;
}
/* end get functions */


