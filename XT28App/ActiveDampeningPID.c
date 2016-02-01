#include "ActiveDampeningPID.h"
#include "XT28CANSupport.h"

// Private prototypes

static float hightPID(float refHeight);
static float phiPID  (float refPhi);
static float thetaPID(float refTheta);
static float deadbandCheckForceError(float forceErrorPercentage, int wheel);

// MARK: Height related signal calculations
static float heightP = 0;
static float heightI = 0;
static float heightD = 0;
int ADPIDSetHeightControlParametersPID(float P, float I, float D) {
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
static float phiP = 0;
static float phiI = 0;
static float phiD = 0;
int ADPIDSetPhiControlParametersPID(float P, float I, float D) {
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
static float thetaP = 0;
static float thetaI = 0;
static float thetaD = 0;
int ADPIDSetThetaControlParametersPID(float P, float I, float D) {
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
void ADPIDGetPIDSignalsForHeightPhiAndThetaArray(float signalArrayOut[static SUM_WHEELS], float heightError, float phiError, float thetaError) {
	float heightSignal = 0;
	heightSignal = hightPID( heightError);

	float phiSignal = 0;
	phiSignal = phiPID( phiError);

	float thetaSignal = 0;
	thetaSignal = thetaPID( thetaError);

	// Decouple and output by reference
	float zAllocationConstant = -0.1694;
	float phiAllocationConstant = (float) 1 / 3;

	signalArrayOut[FR] = zAllocationConstant * heightSignal - phiAllocationConstant * phiSignal - 0.1192 * thetaSignal;
	signalArrayOut[FL] = zAllocationConstant * heightSignal + phiAllocationConstant * phiSignal - 0.1192 * thetaSignal;
	signalArrayOut[MR] = zAllocationConstant * heightSignal - phiAllocationConstant * phiSignal + 0.0046 * thetaSignal;
	signalArrayOut[ML] = zAllocationConstant * heightSignal + phiAllocationConstant * phiSignal + 0.0046 * thetaSignal;
	signalArrayOut[BR] = zAllocationConstant * heightSignal - phiAllocationConstant * phiSignal + 0.1152 * thetaSignal;
	signalArrayOut[BL] = zAllocationConstant * heightSignal + phiAllocationConstant * phiSignal + 0.1152 * thetaSignal;
}

static float forceP = 0.0;
static float forceI = 0.0;
static float forceD = 0.0;
int ADPIDSetForceControllerParametersPID(float P, float I, float D) {
	forceP = P;
	forceI = I;
	forceD = D;
	return 0;
}

void ADPIDGetForceControllerReferenceSignalsArray(int messuredForceCylinder[static SUM_WHEELS], int forceReferenceArray[static SUM_WHEELS], float signalArrayOut[static SUM_WHEELS], bool deadbandState) {
	float forceError = 0;

	int wheel = 0;
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		forceError = (float)( forceReferenceArray[wheel] - messuredForceCylinder[wheel] ) / forceReferenceArray[wheel];
		if (deadbandState == TRUE) {
			signalArrayOut[wheel] = -forceP * deadbandCheckForceError(forceError, wheel);
		} else {
			signalArrayOut[wheel] = -forceP * forceError;
		}
	}
}

static float deadbandCheckForceError(float forceErrorPercentage, int wheel) {
	static int errorSignOld[SUM_WHEELS] = {0};
	static int state[SUM_WHEELS] = {0};
	static float deadBandLimit = 0.10;
	int errorSign = 0;
	float returnForceError = 0;

	if (forceErrorPercentage > 0) {
		errorSign = 1;
	} else {
		errorSign = -1;
	}
	switch (state[wheel]) {
	case 0:
		if (fabs(forceErrorPercentage) > deadBandLimit) {
			state[wheel] = 1;
		}
		returnForceError = 0;
		break;
	case 1:
		if (errorSignOld[wheel] != errorSign) {
			state[wheel] = 0;
		}
		returnForceError = forceErrorPercentage;
		break;
	default:
		break;
	}
	errorSignOld[wheel] = errorSign;
	return returnForceError;
}

float ADPIDGetForceControllerReferenceSignals(int wheel, float messuredForce, float forceReference, bool deadbandState) {
	float forceError = 0;
	if (deadbandState == TRUE) {
		forceError = (forceReference - messuredForce) / forceReference;
		forceError = deadbandCheckForceError(forceError, wheel);
	} else {
		forceError = (forceReference - messuredForce) / forceReference;
	}
	return -(forceError * forceP);
}

