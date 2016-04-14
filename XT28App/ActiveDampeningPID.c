#include "ActiveDampeningPID.h"
#include "XT28CANSupport.h"

// Private prototypes

static float hightPID(float refHeight);
static float phiPID  (float refPhi);
static float thetaPID(float refTheta);
static float deadbandCheckForceError(float forceErrorPercentage, int wheel);

static float sampleTime = 0.01; /* [s] */

// MARK: Height related signal calculations
static float heightP = 0.0;
static float heightI = 0.0;
static float heightD = 0.0;
int ADPIDSetHeightControlParametersPID(float P, float I, float D) {
	heightP = P;
	heightI = I;
	heightD = D;
	return 1;
}

static float hightPID(float heightError) {
	static float previousHeightError = 0.0;
	static float deriativeTermFilterd = 0.0;
	static float alpha = 0.99;

	float propTerm       = heightP * heightError;
	//float integratorTerm = heightI * 0;

	/* D part with low pass filter */
	float deriativeTermRaw  = heightD * (heightError - previousHeightError) / sampleTime;
	previousHeightError = heightError;
	deriativeTermFilterd = deriativeTermFilterd * alpha + (1-alpha) * deriativeTermRaw;

	return propTerm;
}


// MARK: Phi related signal stuff
static float phiP = 0.0;
static float phiI = 0.0;
static float phiD = 0.0;
int ADPIDSetPhiControlParametersPID(float P, float I, float D) {
	phiP = P;
	phiI = I;
	phiD = D;
	return 1;
}

static float phiPID(float phiError) {
	static float previousPhiError = 0.0;
	static float deriativeTermFilterd = 0.0;
	static float alpha = 0.97;

	float propTerm       = phiP * phiError;
	//float integratorTerm = phiI * 0;

	/* D part with low pass filter */
	float deriativeTermRaw  = phiD * (phiError - previousPhiError) / sampleTime;
	previousPhiError = phiError;
	deriativeTermFilterd = deriativeTermFilterd * alpha + (1-alpha) * deriativeTermRaw;

	/* Debugg remove qwhen done */
	float mult = 10.0;
	g_debug1 = mult * deriativeTermRaw;
	g_debug2 = mult * deriativeTermFilterd;
	g_debug3 = mult * propTerm;
	g_debug4 = mult * (propTerm + deriativeTermFilterd);
	/* emd debugg */

	return propTerm;
}

// MARK: Theta related stuff
static float thetaP = 0.0;
static float thetaI = 0.0;
static float thetaD = 0.0;
int ADPIDSetThetaControlParametersPID(float P, float I, float D) {
	thetaP = P;
	thetaI = I;
	thetaD = D;
	return 1;
}

static float thetaPID(float thetaError) {
	static float previousThetaError = 0.0;
	static float deriativeTermFilterd = 0.0;
	static float alpha = 0.99;

	float propTerm       = thetaP * thetaError;

	/* Not implemented */
	//float integratorTerm = thetaI * 0;

	/* D part with low pass filter */
	/* Pls Johan why retarded??? maby use IMU gyro */
	float deriativeTermRaw  = phiD * (thetaError - previousThetaError) / sampleTime;
	previousThetaError = thetaError;
	deriativeTermFilterd = deriativeTermFilterd * alpha + (1-alpha) * deriativeTermRaw;

	return propTerm;
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
	/* This functions should use "ADPIDGetForceControllerReferenceSignals" to calculate contol signal for consitensy */

	int wheel = 0;
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		signalArrayOut[wheel] = ADPIDGetForceControllerReferenceSignalForWheel(wheel,
				messuredForceCylinder[wheel],
				forceReferenceArray[wheel],
				deadbandState
		);
	}
}

float ADPIDGetForceControllerReferenceSignalForWheel(int wheel, float messuredForce, float forceReference, bool deadbandState) {

	float forceError = (forceReference - messuredForce) / forceReference;
	if (deadbandState == TRUE) {
		forceError = deadbandCheckForceError(forceError, wheel);
	}
	return -(forceError * forceP);
}

typedef enum {
	DEADBAND_STATE_ACTIVE,
	DEADBAND_STATE_INACTIVE
} deadbandStateEnum;

static float deadbandCheckForceError(float forceErrorPercentage, int wheel) {
	static int errorSignOld[SUM_WHEELS] = {0};
	static deadbandStateEnum state[SUM_WHEELS] = {DEADBAND_STATE_ACTIVE};

	/* Limit for state change, constant */
	const float deadBandLimit = 0.10;

	/* Check if the error have reached zero or changed sign */
	int errorSign = 0;
	float returnForceError = 0;

	if (forceErrorPercentage > 0) {
		errorSign = 1;
	} else {
		errorSign = -1;
	}
	const bool errorChangedSignOrReachedZero = (errorSignOld[wheel] != errorSign);

	/* Switch on state */
	switch (state[wheel]) {
	case DEADBAND_STATE_ACTIVE:
		if (fabs(forceErrorPercentage) > deadBandLimit) {
			state[wheel] = DEADBAND_STATE_INACTIVE;
		}
		returnForceError = 0;
		break;
	case DEADBAND_STATE_INACTIVE:
		if (errorChangedSignOrReachedZero) {
			state[wheel] = DEADBAND_STATE_ACTIVE;
		}
		returnForceError = forceErrorPercentage;
		break;
	default:
		break;
	}
	errorSignOld[wheel] = errorSign;
	return returnForceError;
}

