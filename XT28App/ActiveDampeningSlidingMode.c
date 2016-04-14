#include "ActiveDampeningSlidingMode.h"

static float deadBandCheckForceReferenceError(float currentCylinderForce, float forceReferenceCylinder, int wheelCounter);


float ADSMCalculateSlidingModeControllerForWheel(int wheel, float messuredCylinderForce, float pesudoForceReference_N, float pressureA_Pa, float pressureB_Pa, float velocityWheel_ms, bool deadbandState) {
	//create variables
	int deltaPressure8bar = 800000;
	float maximumFlow = 100 / 1000 / 60;
	float slidingModeControlParameterKt = 0.000077;
	static float slidingModeFlowOld[SUM_WHEELS] = {0};

	// Frank and brunos implementation of this did not use vel wheel
	velocityWheel_ms = 0;

	float sigma = 0;
	if (deadbandState == TRUE) {
		sigma = deadBandCheckForceReferenceError(messuredCylinderForce , pesudoForceReference_N, wheel);
	} else {
		sigma = (messuredCylinderForce - pesudoForceReference_N);
	}
	sigma = sigma / 200;

	float sgnSigma = (float)sigma / (labs(sigma) + 1000.0);

	float L = 0;
	if (slidingModeFlowOld[wheel] >= 0) {
		L = CYLINDER_PUSH_AREA_SIDE_A1_m2 * maximumFlow + CYLINDER_PUSH_AREA_SIDE_B2_m2 * sqrt(abs(pressureB_Pa - 0)) * maximumFlow / sqrt(deltaPressure8bar);
	} else {
		L = CYLINDER_PUSH_AREA_SIDE_B2_m2 * maximumFlow + CYLINDER_PUSH_AREA_SIDE_A1_m2 * sqrt(abs(pressureA_Pa - 0)) * maximumFlow / sqrt(deltaPressure8bar);
	}
	float slidingModeFlow = 1.0 / L * ( - slidingModeControlParameterKt * sgnSigma);  //Requested flow in percentage

	//Saturate requested flow % between -1 and 1  (100% full flow on both directions)
	if (slidingModeFlow > 1) {
		slidingModeFlow = 1;
	} else if (slidingModeFlow < -1) {
		slidingModeFlow = -1;
	}
	slidingModeFlowOld[wheel] = slidingModeFlow;

	return slidingModeFlow;
}


static float deadBandCheckForceReferenceError(float currentCylinderForce, float forceReferenceCylinder, int wheelCounter) {

	static int  errorSignOld[6]              = {0};
	static int  forceControllerWindowCase[6] = {0};

	float errorForce = currentCylinderForce - forceReferenceCylinder;

	int errorSign = 0;
	if (errorForce > 0) {
		errorSign = 1;
	} else {
		errorSign = -1;
	}

	switch (forceControllerWindowCase[wheelCounter]) {
	case 0:
		if (fabs(errorForce / forceReferenceCylinder) > 0.15 ) {
			forceControllerWindowCase[wheelCounter] = 1;
		}
		errorForce = 0.0;
		break;

	case 1:
		if (errorSign != errorSignOld[wheelCounter]) {
			forceControllerWindowCase[wheelCounter] = 0;
		}
		break;
	}
	errorSignOld[wheelCounter] = errorForce;
	return errorForce;
}
