#include "ADCConfigurations.h"

static float heightReference = 250;
static float phiReference = 0;
static float thetaReference = 0;

void ADCFGNivPIDSetup(bool state) {
	if (state == FALSE) {
		return;
	}

	// Set parameters
	ADCSetHeightControlParametersPID(0, 0, 0);
	ADCSetPhiControlParametersPID(0, 0, 0);
	ADCSetThetaControlParametersPID(0, 0, 0);

	// Get signal and put in array
	float referenceCurrentArray[SUM_WHEELS] = {0};
	ADCGetPIDSignalsForHeightPhiAndTheta(referenceCurrentArray,
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

	// Set parameters
	ADCSetHeightControlParametersPID(0, 0, 0);
	ADCSetPhiControlParametersPID(0, 0, 0);
	ADCSetThetaControlParametersPID(0, 0, 0);
	ADCSetSkyhookParameters(0, 0, 0, 0);

	// PID Height Theta Phi
	float referenceCurrentArray[SUM_WHEELS] = {0};
	ADCGetPIDSignalsForHeightPhiAndTheta(referenceCurrentArray,
			(heightReference - PAPOSGetAvrageHeightOfForwarder()),
			(phiReference    - IMUGetPhi()),
			(thetaReference  - IMUGetTheta())
	);

	// Skyhook
	float skyhookSignalArray[SUM_WHEELS];
	float wheelVelArray[SUM_WHEELS] = {0};
	PAPOSGetVelDataArray(wheelVelArray);
	ADCGetSkyhookSignals(skyhookSignalArray,
			wheelVelArray,
			IMUGetAngleVelX(),
			IMUGetAngleVelY(),
			PAPOSGetAvrageHeightVelocityOfForwarder()
	);

	// Set reference current and actuate
	PAASetReferenceArrayWithUnit(referenceCurrentArray, CURRENT_MA);
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

	// Set parameters
	ADCSetHeightControlParametersPID(0, 0, 0);
	ADCSetPhiControlParametersPID(0, 0, 0);
	ADCSetThetaControlParametersPID(0, 0, 0);
	ADCSetSkyhookParameters(0, 0, 0, 0);

	// PID Height Theta Phi
	float pesudoZPhiThetaForceArray[SUM_WHEELS] = {0};
	ADCGetPIDSignalsForHeightPhiAndTheta(pesudoZPhiThetaForceArray,
			(heightReference - PAPOSGetAvrageHeightOfForwarder()),
			(phiReference    - IMUGetPhi()),
			(thetaReference  - IMUGetTheta())
	);

	// Skyhook
	float skyhookSignalArray[SUM_WHEELS];
	float wheelVelArray[SUM_WHEELS] = {0};
	PAPOSGetVelDataArray(wheelVelArray);
	ADCGetSkyhookSignals(skyhookSignalArray,
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
		// Convert pesudo vertical force into cylinder load
		pesudoForceArray[wheel] = PAFConvertVerticalForceOnWheelToCylinderLoadForce(PAPOSGetPosDataForWheel_mm(wheel), pesudoForceArray[wheel]);

		referenceFlow[wheel] = ADCCalculateSlidingModeControllerForWheel(wheel,
				pesudoForceArray[wheel],
				0,
				0,
				PAPOSGetVelDataForWheel(wheel)
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
	ADCSetHeightControlParametersPID(0, 0, 0);
	ADCSetPhiControlParametersPID(0, 0, 0);
	ADCSetThetaControlParametersPID(0, 0, 0);
	ADCSetSkyhookParameters(0, 0, 0, 0);

	// PID Height Theta Phi
	float pesudoZPhiThetaForceArray[SUM_WHEELS] = {0};
	ADCGetPIDSignalsForHeightPhiAndTheta(pesudoZPhiThetaForceArray,
			(heightReference - PAPOSGetAvrageHeightOfForwarder()),
			(phiReference    - IMUGetPhi()),
			(thetaReference  - IMUGetTheta())
	);

	// Skyhook
	float skyhookSignalArray[SUM_WHEELS];
	float wheelVelArray[SUM_WHEELS] = {0};
	PAPOSGetVelDataArray(wheelVelArray);
	ADCGetSkyhookSignals(skyhookSignalArray,
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
		// Convert pesudo vertical force into cylinder load
		pesudoForceArray[wheel] = PAFConvertVerticalForceOnWheelToCylinderLoadForce(PAPOSGetPosDataForWheel_mm(wheel), pesudoForceArray[wheel]);

		referenceFlow[wheel] = ADCCalculateSlidingModeControllerForWheel(wheel,
				(PAFGetOptimalReferenceForceForWheel_N(wheel) - (PAFGetOptimalReferenceForceForWheel_N(wheel) + pesudoForceArray[wheel])),
				0, //FIX
				0,
				PAPOSGetVelDataForWheel(wheel)
		);
		PAASetReferenceForWheelWithUnit(wheel,
				FLOW_PERCENTAGE,
				referenceFlow[wheel]
		);
	}
	/* Kaboom */
	PAAActuatePendelumArms();
}







