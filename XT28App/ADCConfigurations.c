#include "ADCConfigurations.h"
#include "XT28CANSupport.h"

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
		/* debugg */
		//g_debug1 = phiReference;
		//g_debug2 = thetaReference;
		/* end debugg */
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

		/* debugg */
		//g_debug3 = forceReference;
		/* end debugg */
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

void ADCFGManualTestingPlayground(bool state) {
	if (state == FALSE) {
		return;
	}

	// Set parameters
	ADPIDSetHeightControlParametersPID(heightP, heightI, 0);
	ADPIDSetPhiControlParametersPID   (phiP,    phiI, 0);
	ADPIDSetThetaControlParametersPID (thetaP,  thetaI, 0);
	ADSHSetSkyhookParameters         (0, 0, 0, 0);

	// PID Height Theta Phi
	float pesudoZPhiThetaForceArray[SUM_WHEELS] = {0};
	ADPIDGetPIDSignalsForHeightPhiAndThetaArray(pesudoZPhiThetaForceArray,
			(heightReference - 230),
			(phiReference    - 0),
			(thetaReference  - 0)
	);

	// Skyhook
	float skyhookSignalArray[SUM_WHEELS];
	float wheelVelArray[SUM_WHEELS] = {0};
	PAPOSGetVelDataArray(wheelVelArray);
	ADSHGetSkyhookSignals(skyhookSignalArray,
			wheelVelArray,
			IMUGetAngleVelX(),
			IMUGetAngleVelY(),
			PAPOSGetAvrageHeightVelocityOfForwarder()
	);

	// Add to get the pesudo force
	int wheel = 0;
	float pesudoForceArray[SUM_WHEELS];
	float referenceFlow[SUM_WHEELS];

	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		pesudoForceArray[wheel] = (pesudoZPhiThetaForceArray[wheel] + skyhookSignalArray[wheel]);

		/* Convert pesudo vertical force into cylinder load */
		pesudoForceArray[wheel] = PAFConvertVerticalForceOnWheelToCylinderLoadForce(PAPOSGetPosDataForWheel_mm(wheel), pesudoForceArray[wheel]);

		/* Calculate reference flow using the pesudo Force with optimal reference */
		referenceFlow[wheel] = ADSMCalculateSlidingModeControllerForWheel(wheel,
				PAFGetMessuredCylinderLoadForceForWheel_dN(wheel) * 10,
				(PAFGetOptimalReferenceForceForWheel_N(wheel) * 10 + pesudoForceArray[wheel]),
				(PAPRGetPressureForChamber_bar(wheel * 2)     * 1000),
				(PAPRGetPressureForChamber_bar(wheel * 2 + 1) * 1000),
				PAPOSGetVelDataForWheel(wheel),
				TRUE
		);

		/* DEBUGG */
		/*
		g_debug1 = referenceFlow[0] * 100;
		g_debug2 = referenceFlow[1] * 100;
		g_debug3 = referenceFlow[2] * 100;
		g_debug4 = referenceFlow[3] * 100;
		g_debug5 = referenceFlow[4] * 100;
		g_debug6 = referenceFlow[5] * 100;
		*/
		/* END DEBUG */

		/* Set reference to actuate module with unit flow percentage */
		PAASetReferenceForWheelWithUnit(wheel,
				FLOW_PERCENTAGE,
				referenceFlow[wheel]
		);
	}
}

void ADCFGNivPIDSetup(bool state) {
	if (state == FALSE) {
		return;
	}

	// Set parameters
	ADPIDSetHeightControlParametersPID(heightP, heightI, 0);
	ADPIDSetPhiControlParametersPID   (phiP,    phiI, 0);
	ADPIDSetThetaControlParametersPID (thetaP,  thetaI, 0);

	// Get signal and put in array
	float referenceCurrentArray[SUM_WHEELS] = {0};
	ADPIDGetPIDSignalsForHeightPhiAndThetaArray(referenceCurrentArray,
			(heightReference - PAPOSGetAvrageHeightOfForwarder()), 	/* Error in Z */
			(phiReference    - IMUGetPhi()),						/* Error in Phi */
			(thetaReference  - IMUGetTheta())						/* Error in Theta */
	);

	// Set reference current and actuate
	PAASetReferenceArrayWithUnit(referenceCurrentArray, CURRENT_MA);
	PAAActuatePendelumArms();
}

void ADCFGNivPIDAndSkyhookSetup(bool state) {
	if (state == FALSE) {
		return;
	}

	/* Set parameters */
	ADPIDSetHeightControlParametersPID(heightP, heightI, 0);
	ADPIDSetPhiControlParametersPID   (phiP,    phiI, 0);
	ADPIDSetThetaControlParametersPID (thetaP,  thetaI, 0);
	ADSHSetSkyhookParameters         (skyWheelGain, skyChassiGain, skyPhiGain, skyThetaGain);

	/* PID Height Theta Phi */
	float referenceCurrentArray[SUM_WHEELS] = {0};
	ADPIDGetPIDSignalsForHeightPhiAndThetaArray(referenceCurrentArray,
			(heightReference - PAPOSGetAvrageHeightOfForwarder()),
			(phiReference    - IMUGetPhi()),
			(thetaReference  - IMUGetTheta())
	);

	/* Skyhook */
	float skyhookSignalArray[SUM_WHEELS];
	float wheelVelArray[SUM_WHEELS] = {0};
	PAPOSGetVelDataArray(wheelVelArray);
	ADSHGetSkyhookSignals(skyhookSignalArray,
			wheelVelArray,
			IMUGetAngleVelX(),
			IMUGetAngleVelY(),
			PAPOSGetAvrageHeightVelocityOfForwarder()
	);

	/* Set reference current and actuate */
	int wheel = 0;
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		PAASetReferenceForWheelWithUnit(wheel,
				CURRENT_MA,
				(referenceCurrentArray[wheel] + skyhookSignalArray[wheel])
		);
	}
	// Kaboom
	PAAActuatePendelumArms();
}

void ADCFGPesudoForcePIDSkyhookSlidingMode(bool state) {
	if (state == FALSE) {
		return;
	}

	/* Set parameters */
	ADPIDSetHeightControlParametersPID(heightP, heightI, 0);
	ADPIDSetPhiControlParametersPID   (phiP,    phiI, 0);
	ADPIDSetThetaControlParametersPID (thetaP,  thetaI, 0);
	ADSHSetSkyhookParameters         (skyWheelGain, skyChassiGain, skyPhiGain, skyThetaGain);

	/* PID Height Theta Phi */
	float pesudoZPhiThetaForceArray[SUM_WHEELS] = {0};
	ADPIDGetPIDSignalsForHeightPhiAndThetaArray(pesudoZPhiThetaForceArray,
			(heightReference - PAPOSGetAvrageHeightOfForwarder()),
			(phiReference    - IMUGetPhi()),
			(thetaReference  - IMUGetTheta())
	);

	/* Skyhook */
	float skyhookSignalArray[SUM_WHEELS];
	float wheelVelArray[SUM_WHEELS] = {0};
	PAPOSGetVelDataArray(wheelVelArray);
	ADSHGetSkyhookSignals(skyhookSignalArray,
			wheelVelArray,
			IMUGetAngleVelX(),
			IMUGetAngleVelY(),
			PAPOSGetAvrageHeightVelocityOfForwarder()
	);

	/* Add to get the pesudo force */
	int wheel = 0;
	float pesudoForceArray[SUM_WHEELS];
	float referenceFlow[SUM_WHEELS];
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		pesudoForceArray[wheel] = (pesudoZPhiThetaForceArray[wheel] + skyhookSignalArray[wheel]);

		/* Convert pesudo vertical force into cylinder load */
		pesudoForceArray[wheel] = PAFConvertVerticalForceOnWheelToCylinderLoadForce(PAPOSGetPosDataForWheel_mm(wheel), pesudoForceArray[wheel]);

		referenceFlow[wheel] = ADSMCalculateSlidingModeControllerForWheel(wheel,
				0,
				pesudoForceArray[wheel],
				(PAPRGetPressureForChamber_bar(wheel * 2)     * 1000),
				(PAPRGetPressureForChamber_bar(wheel * 2 + 1) * 1000),
				PAPOSGetVelDataForWheel(wheel),
				FALSE
		);
		PAASetReferenceForWheelWithUnit(wheel,
				FLOW_PERCENTAGE,
				referenceFlow[wheel]
		);
	}
	/* Kaboom */
	PAAActuatePendelumArms();
}

void ADCFGPesudoForceWithOptimalForceRefPIDSkyhookSlidingMode(bool state) {
	if (state == FALSE) {
		return;
	}

	// Set parameters
	ADPIDSetHeightControlParametersPID(heightP, heightI, 0);
	ADPIDSetPhiControlParametersPID   (phiP,    phiI, 0);
	ADPIDSetThetaControlParametersPID (thetaP,  thetaI, 0);
	ADSHSetSkyhookParameters         (skyWheelGain, skyChassiGain, skyPhiGain, skyThetaGain);

	// PID Height Theta Phi
	float pesudoZPhiThetaForceArray[SUM_WHEELS] = {0};
	ADPIDGetPIDSignalsForHeightPhiAndThetaArray(pesudoZPhiThetaForceArray,
			(heightReference - PAPOSGetAvrageHeightOfForwarder()),
			(phiReference    - IMUGetPhi()),
			(thetaReference  - IMUGetTheta())
	);

	// Skyhook
	float skyhookSignalArray[SUM_WHEELS];
	float wheelVelArray[SUM_WHEELS] = {0};
	PAPOSGetVelDataArray(wheelVelArray);
	ADSHGetSkyhookSignals(skyhookSignalArray,
			wheelVelArray,
			IMUGetAngleVelX(),
			IMUGetAngleVelY(),
			PAPOSGetAvrageHeightVelocityOfForwarder()
	);

	// Add to get the pesudo force
	int wheel = 0;
	float pesudoForceArray[SUM_WHEELS];
	float referenceFlow[SUM_WHEELS];

	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		pesudoForceArray[wheel] = (pesudoZPhiThetaForceArray[wheel] + skyhookSignalArray[wheel]);

		/* Convert pesudo vertical force into cylinder load */
		pesudoForceArray[wheel] = PAFConvertVerticalForceOnWheelToCylinderLoadForce(PAPOSGetPosDataForWheel_mm(wheel), pesudoForceArray[wheel]);

		/* Calculate reference flow using the pesudo Force with optimal reference */
		referenceFlow[wheel] = ADSMCalculateSlidingModeControllerForWheel(wheel,
				PAFGetMessuredCylinderLoadForceForWheel_dN(wheel),
				(PAFGetOptimalReferenceForceForWheel_N(wheel) + pesudoForceArray[wheel]),
				(PAPRGetPressureForChamber_bar(wheel * 2)     * 1000),
				(PAPRGetPressureForChamber_bar(wheel * 2 + 1) * 1000),
				PAPOSGetVelDataForWheel(wheel),
				TRUE
		);

		/* Set reference to actuate module with unit flow percentage */
		PAASetReferenceForWheelWithUnit(wheel,
				FLOW_PERCENTAGE,
				referenceFlow[wheel]
		);
	}
	/* Kaboom baby, this is it the arms reference is set and now it will be set as the actual output with no regrets. */
	PAAActuatePendelumArms();
}

void ADCFGNivPIDAndForcePID(bool state) {

	if (state == FALSE) {
		return;
	}

	/* 1. Set parameters */
	ADPIDSetHeightControlParametersPID(heightP, 0, 0);
	ADPIDSetPhiControlParametersPID   (phiP,    0, 0);
	ADPIDSetThetaControlParametersPID (thetaP,  0, 0);
	ADPIDSetForceControllerParametersPID(heightI, 0, 0); /* if parameters is heigfht I, fix and remove this comment. if fixed remove comment */

	/* 2. Get signal and put in array */
	float heightPhiThetaSignalArray[SUM_WHEELS] = {0};
	ADPIDGetPIDSignalsForHeightPhiAndThetaArray(heightPhiThetaSignalArray,
			(heightReference - PAPOSGetAvrageHeightOfForwarder()),
			(phiReference    - IMUGetPhi()),
			(thetaReference  - IMUGetTheta())
	);

	/* 3. Get force signals and put in array */
	float forceControllerOut[SUM_WHEELS] = {0};
	int messuredCylinderForce[SUM_WHEELS] = {0};
	int cylinderReferenceForce[SUM_WHEELS] = {0};
	PAFGetMessuredCylinderLoadForceArray_dN(messuredCylinderForce);
	PAFGetOptimalReferenceForceArray_N(cylinderReferenceForce);

	ADPIDGetForceControllerReferenceSignalsArray(messuredCylinderForce, /* Messured force array  */
			cylinderReferenceForce,										/* reference force array */
			forceControllerOut,											/* output array          */
			TRUE														/* Deadband              */
	);

	/* 4. Set reference current */
	int wheel = 0;
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		PAASetReferenceForWheelWithUnit(wheel,
				CURRENT_MA,
				(heightPhiThetaSignalArray[wheel] + forceControllerOut[wheel])
		);
	}

	/* 5. Actuate */
	PAAActuatePendelumArms();
}

void ADCFGForceControllerTest(bool state) {
	if (state == FALSE) {
		return;
	}

	// Set parameters
	ADPIDSetHeightControlParametersPID(heightP, 0, 0);
	ADPIDSetPhiControlParametersPID   (phiP,    0, 0);
	ADPIDSetThetaControlParametersPID (thetaP,  0, 0);
	ADPIDSetForceControllerParametersPID(heightI, 0, 0);

	// Get signal and put in array
	float heightPhiThetaSignalArray[SUM_WHEELS] = {0};
	ADPIDGetPIDSignalsForHeightPhiAndThetaArray(heightPhiThetaSignalArray,
			(heightReference - PAPOSGetAvrageHeightOfForwarder()),
			(phiReference    - IMUGetPhi()),
			(thetaReference  - IMUGetTheta())
	);


	float forceControllerOut[SUM_WHEELS] = {0};
	int messuredCylinderForce[SUM_WHEELS] = {0};
	int cylinderReferenceForce[SUM_WHEELS] = {0};
	PAFGetMessuredCylinderLoadForceArray_dN(messuredCylinderForce);
	PAFGetOptimalReferenceForceArray_N(cylinderReferenceForce);


	if (forceReference == 0) {
		cylinderReferenceForce[0] = messuredCylinderForce[0];
		/* deubgg */
		//g_debug4 = (forceReference - messuredCylinderForce[0]) / (forceReference) * 100;
		/* end debugg */
	} else {
		cylinderReferenceForce[0] = forceReference;
	}
	cylinderReferenceForce[1] = messuredCylinderForce[1];
	cylinderReferenceForce[2] = messuredCylinderForce[2];
	cylinderReferenceForce[3] = messuredCylinderForce[3];
	cylinderReferenceForce[4] = messuredCylinderForce[4];
	cylinderReferenceForce[5] = messuredCylinderForce[5];

	ADPIDGetForceControllerReferenceSignalsArray(messuredCylinderForce,
			cylinderReferenceForce,
			forceControllerOut,
			TRUE
	);

	int wheel = 0;
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		PAASetReferenceForWheelWithUnit(wheel,
				CURRENT_MA,
				(heightPhiThetaSignalArray[wheel] + forceControllerOut[wheel])
		);
	}

	PAAActuatePendelumArms();

}


