#include "ADCConfigurations.h"

/* Defines */
#define CONF_MSG_ID_2			0x17FE000A
#define CONF_MSG_ID_3			0x17FE000B
#define CONF_MSG_ID_4			0x17FE000C
#define DATABOX_BUFFER_LENGTH 	5


/* Setup default parameter values */
static float heightReference = 250;
static float phiReference = 0;
static float thetaReference = 0;

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

void ADCFGConfigureParameterSettingsFromCAN(uint8 CANChannel, uint16 databoxNr1, uint16 databoxNr2, uint16 databoxNr3) {

	static can_DataboxData_ts heightParameters_Buffer[DATABOX_BUFFER_LENGTH];
	static can_DataboxData_ts thetaPhiProportionalParameters_Buffer[DATABOX_BUFFER_LENGTH];
	static can_DataboxData_ts integratorParameters_Buffer[DATABOX_BUFFER_LENGTH];

	int configMessageNumOfBytes = 8;

	can_initRxDatabox(CANChannel,
			databoxNr1,
			CONF_MSG_ID_2,
			CAN_EXD_DU8,
			configMessageNumOfBytes,
			heightParameters_Buffer,
			DATABOX_BUFFER_LENGTH,
			heightParametersCallback
	);

	can_initRxDatabox(CANChannel,
			databoxNr2,
			CONF_MSG_ID_3,
			CAN_EXD_DU8,
			configMessageNumOfBytes,
			thetaPhiProportionalParameters_Buffer,
			DATABOX_BUFFER_LENGTH,
			thetaPhiProportionalParametersCallback
	);

	can_initRxDatabox(CANChannel,
			databoxNr3,
			CONF_MSG_ID_4,
			CAN_EXD_DU8,
			configMessageNumOfBytes,
			integratorParameters_Buffer,
			DATABOX_BUFFER_LENGTH,
			integratorParametersCallback
	);

}

static void heightParametersCallback(void) {
	uint8 confData_au8[8] = {0};
	uint8 confNumBytes_u8;

	/* Databox Get Message data and assign to variables */
	if (0 == can_getDatabox(CAN_1, 3, confData_au8, &confNumBytes_u8)) {
		//sint16 forceRef 	= ((confData_au8[1] << 8) | (confData_au8[0]));   // Add two 8-bits to an unsigned 16-bit. Not sure what this dude was even used for
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

void ADCFGManualTestingPlayground(bool state) {
	if (state == FALSE) {
		return;
	}

	// Set parameters
	ADPIDSetHeightControlParametersPID(heightP, heightI, 0);
	ADPIDSetPhiControlParametersPID   (phiP,    phiI, 0);
	ADPIDSetThetaControlParametersPID (thetaP,  thetaI, 0);
	ADPIDSetForceControllerParametersPID(heightI, 0, 0);

	// Get signal and put in array
	float referenceCurrentArray[SUM_WHEELS] = {0};
	ADPIDGetPIDSignalsForHeightPhiAndThetaArray(referenceCurrentArray,
			(heightReference - 270), 	/* Error in Z */
			(phiReference    - 5),						/* Error in Phi */
			(thetaReference  - 5)						/* Error in Theta */
	);


	float forceControllerOut[SUM_WHEELS] = {0};
	int messuredCylinderForce[SUM_WHEELS] = {0};
	int cylinderReferenceForce[SUM_WHEELS] = {0};
	PAFGetMessuredCylinderLoadForceArray_dN(messuredCylinderForce);
	PAFGetOptimalReferenceForceArray_N(cylinderReferenceForce);

	ADPIDGetForceControllerReferenceSignalsArray(messuredCylinderForce,
			cylinderReferenceForce,
			forceControllerOut,
			TRUE
	);

	int wheel = 0;
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		PAASetReferenceForWheelWithUnit(wheel,
				CURRENT_MA,
				(referenceCurrentArray[wheel] + forceControllerOut[wheel])
		);
	}

	/* Set reference current and actuate */

	/*int wheel = 0;
	float forceControllerReferenceSingal = 0;
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		forceControllerReferenceSingal = ADCGetForceControllerReferenceSignals(wheel,
				PAFGetMessuredCylinderLoadForceForWheel_dN(wheel),
				PAFGetOptimalReferenceForceForWheel_N(wheel),
				TRUE
		);
		PAASetReferenceForWheelWithUnit(wheel,
				CURRENT_MA,
				(referenceCurrentArray[wheel] + forceControllerReferenceSingal)
		);
	}*/


	// Set reference current and actuate
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
