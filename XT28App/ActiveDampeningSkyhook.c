#include "ActiveDampeningSkyhook.h"



// MARK: Skyhook
static float skyChassiGain = 0;
static float skyPhiGain    = 0;
static float skyThetaGain  = 0;
static float skyWheelGain  = 0;
void ADSHSetSkyhookParameters(float wheelGainIn, float chassiGainIn, float phiGainIn, float thetaGainIn) {
	skyWheelGain  = wheelGainIn;
	skyChassiGain = chassiGainIn;
	skyPhiGain    = phiGainIn;
	skyThetaGain  = thetaGainIn;
}

void ADSHGetSkyhookSignals(float signalArrayOut[static SUM_WHEELS], float wheelVel[static SUM_WHEELS], float avrageVelocity, float gyroVelX, float gyroVelY) {

	float skyhookControlSignalHeight = - skyChassiGain * avrageVelocity;
	float skyhookSignalPhi 	         = skyPhiGain      * gyroVelX;
	float skyhookSignalTheta 	     = skyThetaGain    * gyroVelY;

	// Add induvidual wheel skyhook to output
	int wheel = 0;
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		signalArrayOut[wheel] = (skyWheelGain * wheelVel[wheel]);
	}

	// Decouple and output by reference
	float zAllocationConstant = 0.1694;
	float phiAllocationConstant = (float) 1 / 3;
	signalArrayOut[FR] += zAllocationConstant * skyhookControlSignalHeight - phiAllocationConstant * skyhookSignalPhi + 0.1192 * skyhookSignalTheta;
	signalArrayOut[FL] += zAllocationConstant * skyhookControlSignalHeight + phiAllocationConstant * skyhookSignalPhi + 0.1192 * skyhookSignalTheta;
	signalArrayOut[MR] += zAllocationConstant * skyhookControlSignalHeight - phiAllocationConstant * skyhookSignalPhi - 0.0046 * skyhookSignalTheta;
	signalArrayOut[ML] += zAllocationConstant * skyhookControlSignalHeight + phiAllocationConstant * skyhookSignalPhi - 0.0046 * skyhookSignalTheta;
	signalArrayOut[BR] += zAllocationConstant * skyhookControlSignalHeight - phiAllocationConstant * skyhookSignalPhi - 0.1152 * skyhookSignalTheta;
	signalArrayOut[BL] += zAllocationConstant * skyhookControlSignalHeight + phiAllocationConstant * skyhookSignalPhi - 0.1152 * skyhookSignalTheta;
}
