#include "ADCConfigurations.h"
#include "XT28CANSupport.h"

/*
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
*/


void ADCFGNivPIDAndSkyhookSetup(bool state) {
	if (state == FALSE) {
		return;
	}

	/* Set parameters */
	/*
	ADPIDSetHeightControlParametersPID(heightP, heightI, 0);
	ADPIDSetPhiControlParametersPID   (phiP,    phiI, 0);
	ADPIDSetThetaControlParametersPID (thetaP,  thetaI, 0);
	ADSHSetSkyhookParameters         (skyWheelGain, skyChassiGain, skyPhiGain, skyThetaGain);
	*/

	/* PID Height Theta Phi */
	float referenceCurrentArray[SUM_WHEELS] = {0};
	ADPIDGetPIDSignalsForHeightPhiAndThetaArray(referenceCurrentArray,
			(250 - PAPOSGetAvrageHeightOfForwarder()),
			(0    - IMUGetPhi()),
			(0  - IMUGetTheta())
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
	/*
	ADPIDSetHeightControlParametersPID(heightP, heightI, 0);
	ADPIDSetPhiControlParametersPID   (phiP,    phiI, 0);
	ADPIDSetThetaControlParametersPID (thetaP,  thetaI, 0);
	ADSHSetSkyhookParameters         (skyWheelGain, skyChassiGain, skyPhiGain, skyThetaGain);
	*/

	/* PID Height Theta Phi */
	float pesudoZPhiThetaForceArray[SUM_WHEELS] = {0};
	ADPIDGetPIDSignalsForHeightPhiAndThetaArray(pesudoZPhiThetaForceArray,
			(250 - PAPOSGetAvrageHeightOfForwarder()),
			(0    - IMUGetPhi()),
			(0  - IMUGetTheta())
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
	/*
	ADPIDSetHeightControlParametersPID(heightP, heightI, 0);
	ADPIDSetPhiControlParametersPID   (phiP,    phiI, 0);
	ADPIDSetThetaControlParametersPID (thetaP,  thetaI, 0);
	ADSHSetSkyhookParameters         (skyWheelGain, skyChassiGain, skyPhiGain, skyThetaGain);
	*/

	// PID Height Theta Phi
	float pesudoZPhiThetaForceArray[SUM_WHEELS] = {0};
	ADPIDGetPIDSignalsForHeightPhiAndThetaArray(pesudoZPhiThetaForceArray,
			(250 - PAPOSGetAvrageHeightOfForwarder()),
			(0    - IMUGetPhi()),
			(0  - IMUGetTheta())
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

void ADCFGNivPIDAndForcePIDCfg(float heightGain, float thetaGain, float phiGain, float forceGain) {
	/* 1. Set parameters */
	ADPIDSetHeightControlParametersPID(heightGain, 0, 0);
	ADPIDSetPhiControlParametersPID   (phiGain,    0, 0);
	ADPIDSetThetaControlParametersPID (thetaGain,  0, 0);
	ADPIDSetForceControllerParametersPID(forceGain, 0, 0);
}

void ADCFGNivPIDAndForcePID(float setHeightRef, float setPhiRef, float setThetaRef) {

	/* 2. Get signal and put in array */
	float heightPhiThetaSignalArray[SUM_WHEELS] = {0};
	ADPIDGetPIDSignalsForHeightPhiAndThetaArray(heightPhiThetaSignalArray,
			(setHeightRef - PAPOSGetAvrageHeightOfForwarder()),
			(setPhiRef    - IMUGetPhi()),
			(setThetaRef  - IMUGetTheta())
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


/*!
 * This function was used to step test the force proportional controller on one wheel.
 * @param state
 */
/*
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
			(250 - PAPOSGetAvrageHeightOfForwarder()),
			(0    - IMUGetPhi()),
			(0  - IMUGetTheta())
	);


	float forceControllerOut[SUM_WHEELS] = {0};
	int messuredCylinderForce[SUM_WHEELS] = {0};
	int cylinderReferenceForce[SUM_WHEELS] = {0};
	PAFGetMessuredCylinderLoadForceArray_dN(messuredCylinderForce);
	PAFGetOptimalReferenceForceArray_N(cylinderReferenceForce);


	if (forceReference == 0) {
		cylinderReferenceForce[0] = messuredCylinderForce[0];
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
*/

