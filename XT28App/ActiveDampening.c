#include "ActiveDampening.h"

// Private prototypes

static float hightPID(float refHeight);
static float phiPID  (float refPhi);
static float thetaPID(float refTheta);

// MARK: Height related signal calculations
float heightP = 0;
float heightI = 0;
float heightD = 0;
int ADCSetHeightControlParametersPID(float P, float I, float D) {
	heightP = P;
	heightI = I;
	heightD = D;
	return 1;
}

static float hightPID(float heightError) {

	float propTerm       = heightP * heightError;
	float integratorTerm = heightI * 0;
	float deriativeTerm  = heightD * 0;

	return propTerm + integratorTerm + deriativeTerm;
}


// MARK: Phi related signal stuff
float phiP = 0;
float phiI = 0;
float phiD = 0;
int ADCSetPhiControlParametersPID(float P, float I, float D) {
	phiP = P;
	phiI = I;
	phiD = D;
	return 1;
}

static float phiPID(float phiError) {

	float propTerm       = phiP * phiError;
	float integratorTerm = phiI * 0;
	float deriativeTerm  = phiD * 0;

	return propTerm + integratorTerm + deriativeTerm;
}
// MARK: Theta related stuff
float thetaP = 0;
float thetaI = 0;
float thetaD = 0;
int ADCSetThetaControlParametersPID(float P, float I, float D) {
	thetaP = P;
	thetaI = I;
	thetaD = D;
	return 1;
}

static float thetaPID(float thetaError) {

	float propTerm       = thetaP * thetaError;
	float integratorTerm = thetaI * 0;
	float deriativeTerm  = thetaD * 0;

	return propTerm + integratorTerm + deriativeTerm;
}

// MARK: Get PID signals
void ADCGetPIDSignalsForHeightPhiAndTheta(float signalArrayOut[static SUM_WHEELS], float heightError, float phiError, float thetaError) {
	float heightSignal = 0;
	heightSignal = hightPID( heightError);

	float phiSignal = 0;
	phiSignal = phiPID( phiError);

	float thetaSignal = 0;
	thetaSignal = thetaPID( thetaError);

	// Decouple and output by reference
	float zAllocationConstant = 0.1694;
	float phiAllocationConstant = (float) 1 / 3;

	signalArrayOut[FR] = zAllocationConstant * heightSignal - phiAllocationConstant * phiSignal + 0.1192 * thetaSignal;
	signalArrayOut[FL] = zAllocationConstant * heightSignal + phiAllocationConstant * phiSignal + 0.1192 * thetaSignal;
	signalArrayOut[MR] = zAllocationConstant * heightSignal - phiAllocationConstant * phiSignal - 0.0046 * thetaSignal;
	signalArrayOut[ML] = zAllocationConstant * heightSignal + phiAllocationConstant * phiSignal - 0.0046 * thetaSignal;
	signalArrayOut[BR] = zAllocationConstant * heightSignal - phiAllocationConstant * phiSignal - 0.1152 * thetaSignal;
	signalArrayOut[BL] = zAllocationConstant * heightSignal + phiAllocationConstant * phiSignal - 0.1152 * thetaSignal;
}

// MARK: Skyhook
static float chassiGain = 0, phiGain = 0, thetaGain = 0, wheelGain = 0;
void ADCSetSkyhookParameters(float wheelGainIn, float chassiGainIn, float phiGainIn, float thetaGainIn) {
	wheelGain  = wheelGainIn;
	chassiGain = chassiGainIn;
	phiGain    = phiGainIn;
	thetaGain  = thetaGainIn;
}

void ADCGetSkyhookSignals(float signalArrayOut[static SUM_WHEELS], float wheelVel[static SUM_WHEELS], float avrageVelocity, float gyroVelX, float gyroVelY) {

	float skyhookControlSignalHeight = - chassiGain * avrageVelocity;
	float skyhookSignalPhi 	         = phiGain      * gyroVelX;
	float skyhookSignalTheta 	     = thetaGain    * gyroVelY;

	// Add induvidual wheel skyhook to output
	int wheel = 0;
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		signalArrayOut[wheel] = (wheelGain * wheelVel[wheel]);
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

float ADCCalculateSlidingModeControllerForWheel(int wheel, float pesudoForce, float pressureA, float pressureB, float velocityWheel) {
	//create variables
	int deltaPressure8bar = 800000;
	float maximumFlow = 100/1000/60;
	float slidingModeControlParameterKt = 0.000077;
	static float sl_uold[SUM_WHEELS] = {0};

	// Frank and brunos implementation of this did not use vel wheel
	velocityWheel = 0;

	//Map Variables to latest cylinder values and scale
	int sl_P1 = pressureA; 		//KPa*1000=[Pa]
	int sl_P2 = pressureB;  	//Kpa*1000=[Pa]

	int sigma = -pesudoForce;
	sigma = sigma / 200;

	float sgnSigma = (float)sigma / (labs(sigma) + 1000.0);

	float L = 0;
	if (sl_uold[wheel] >= 0) {
		L = CYLINDER_PUSH_AREA_SIDE_A1_m2 * maximumFlow + CYLINDER_PUSH_AREA_SIDE_B2_m2 * sqrt(abs(sl_P2 - 0)) * maximumFlow / sqrt(deltaPressure8bar);
	} else {
		L = CYLINDER_PUSH_AREA_SIDE_B2_m2 * maximumFlow + CYLINDER_PUSH_AREA_SIDE_A1_m2 * sqrt(abs(sl_P1 - 0)) * maximumFlow / sqrt(deltaPressure8bar);
	}
	float slidingModeFlow = 1.0 / L * ( - slidingModeControlParameterKt * sgnSigma);  //Requested flow in percentage

	//Saturate requested flow % between -1 and 1  (100% full flow on both directions)
	if (slidingModeFlow > 1) {
		slidingModeFlow = 1;
	} else if (slidingModeFlow < -1) {
		slidingModeFlow = -1;
	}
	sl_uold[wheel] = slidingModeFlow;

	return slidingModeFlow;
}

