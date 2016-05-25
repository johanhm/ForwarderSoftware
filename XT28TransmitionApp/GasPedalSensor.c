
#include "GasPedalSensor.h"

#define	ANALOG_GASPEDAL_FRONT_A				0
#define	ANALOG_GASPEDAL_FRONT_B				1
#define	ANALOG_GASPEDAL_REAR_A				2
#define	ANALOG_GASPEDAL_REAR_B				3
#define	ANALOG_BRAKEPEDAL_FRONT_A			4
#define	ANALOG_BRAKEPEDAL_FRONT_B			5
#define	ANALOG_BRAKEPEDAL_REAR_A			6
#define	ANALOG_BRAKEPEDAL_REAR_B			7
#define	PMIL_GASPEDAL_FRONT_A				8
#define	PMIL_GASPEDAL_FRONT_B				9
#define	PMIL_GASPEDAL_REAR_A				10
#define	PMIL_GASPEDAL_REAR_B				11
#define	PMIL_BRAKEPEDAL_FRONT_A				12
#define	PMIL_BRAKEPEDAL_FRONT_B				13
#define	PMIL_BRAKEPEDAL_REAR_A				14
#define	PMIL_BRAKEPEDAL_REAR_B				15
#define	PMIL_GASPEDAL						16
#define	PMIL_BRAKEPEDAL						17
#define PMIL_PEDAL							18
#define PMIL_PEDAL_OLD						19
#define PMIL_LP_PEDAL						20
#define INDEX_SIZE_PEDALS					21

static void gasPedalLowPassFilter(chairPosition chairPos);

void GPSConfigureGasPedalInputSensors(void) {
	/****Pedals****/
	in_cfgVoltageInput(AIV_GAS_F_A, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(AIV_GAS_F_B, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(AIV_GAS_R_A, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(AIV_GAS_R_B, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(AIV_BRAKE_F_A, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(AIV_BRAKE_F_B, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(AIV_BRAKE_R_A, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(AIV_BRAKE_R_B, 1000, 4000, 100, 200, 4800, 200);
}

static int pedalData[INDEX_SIZE_PEDALS] = {0};
void GPSUppdatePedalSensorData(chairPosition chairPos) {

	/* Transmission */
	pedalData[ANALOG_GASPEDAL_FRONT_A] = in(AIV_GAS_F_A);
	pedalData[ANALOG_GASPEDAL_FRONT_B] = in(AIV_GAS_F_B);
	pedalData[ANALOG_GASPEDAL_REAR_A] = in(AIV_GAS_R_A);
	pedalData[ANALOG_GASPEDAL_REAR_B] = in(AIV_GAS_R_B);

	pedalData[ANALOG_BRAKEPEDAL_FRONT_A] = in(AIV_BRAKE_F_A);
	pedalData[ANALOG_BRAKEPEDAL_FRONT_B] = in(AIV_BRAKE_F_B);
	pedalData[ANALOG_BRAKEPEDAL_REAR_A] = in(AIV_BRAKE_R_A);
	pedalData[ANALOG_BRAKEPEDAL_REAR_B] = in(AIV_BRAKE_R_B);

	/**********PEDAL CONVERSION*********/

	/* Calibrated min max volt */
	const int GAS_F_A_Umin = 535;
	const int GAS_F_A_Umax = 4532;
	const int GAS_F_B_Umax = 535;
	const int GAS_F_B_Umin = 4532;

	const int GAS_R_A_Umin = 535;
	const int GAS_R_A_Umax = 4518;
	const int GAS_R_B_Umax = 542;
	const int GAS_R_B_Umin = 4529;

	const int BRAKE_F_A_Umin = 538;
	const int BRAKE_F_A_Umax = 4535;
	const int BRAKE_F_B_Umax = 532;
	const int BRAKE_F_B_Umin = 4518;

	const int BRAKE_R_A_Umin = 532;
	const int BRAKE_R_A_Umax = 4525;
	const int BRAKE_R_B_Umax = 537;
	const int BRAKE_R_B_Umin = 4536;

	/* Front GasPedal conversion */
	/* A signal */
	pedalData[PMIL_GASPEDAL_FRONT_A] = 1000 * (pedalData[ANALOG_GASPEDAL_FRONT_A] - GAS_F_A_Umin) / (GAS_F_A_Umax - GAS_F_A_Umin);
	if (pedalData[ANALOG_GASPEDAL_FRONT_A] > GAS_F_A_Umax) {
		pedalData[PMIL_GASPEDAL_FRONT_A] = 1000;
	}
	else if (pedalData[ANALOG_GASPEDAL_FRONT_A] < GAS_F_A_Umin) {
		pedalData[PMIL_GASPEDAL_FRONT_A] = 0;
	}

	/* B signal */
	pedalData[PMIL_GASPEDAL_FRONT_B] = 1000 * (pedalData[ANALOG_GASPEDAL_FRONT_B] - GAS_F_B_Umin) / (GAS_F_B_Umax - GAS_F_B_Umin);
	if (pedalData[ANALOG_GASPEDAL_FRONT_B] > GAS_F_B_Umin) {
		pedalData[PMIL_GASPEDAL_FRONT_B] = 0;
	}
	else if (pedalData[ANALOG_GASPEDAL_FRONT_B] < GAS_F_B_Umax) {
		pedalData[PMIL_GASPEDAL_FRONT_B] = 1000;
	}

	/* Rear GasPedal conversion */
	/* A signal */
	pedalData[PMIL_GASPEDAL_REAR_A] = 1000 * (pedalData[ANALOG_GASPEDAL_REAR_A] - GAS_R_A_Umin) / (GAS_R_A_Umax - GAS_R_A_Umin);
	if (pedalData[ANALOG_GASPEDAL_REAR_A] > GAS_R_A_Umax) {
		pedalData[PMIL_GASPEDAL_REAR_A] = 1000;
	}
	else if (pedalData[ANALOG_GASPEDAL_REAR_A] < GAS_R_A_Umin) {
		pedalData[PMIL_GASPEDAL_REAR_A] = 0;
	}
	/* B signal */
	pedalData[PMIL_GASPEDAL_REAR_B] = 1000 * (pedalData[ANALOG_GASPEDAL_REAR_B] - GAS_R_B_Umin) / (GAS_R_B_Umax - GAS_R_B_Umin);
	if (pedalData[ANALOG_GASPEDAL_REAR_B] > GAS_R_B_Umin) {
		pedalData[PMIL_GASPEDAL_REAR_B] = 0;
	}
	else if (pedalData[ANALOG_GASPEDAL_REAR_B] < GAS_R_B_Umax) {
		pedalData[PMIL_GASPEDAL_REAR_B] = 1000;
	}

	/* Front BrakePedal conversion */
	/* A signal */
	pedalData[PMIL_BRAKEPEDAL_FRONT_A] = 1000 * (pedalData[ANALOG_BRAKEPEDAL_FRONT_A] - BRAKE_F_A_Umin) / (BRAKE_F_A_Umax - BRAKE_F_A_Umin);
	if (pedalData[ANALOG_BRAKEPEDAL_FRONT_A] > BRAKE_F_A_Umax) {
		pedalData[PMIL_BRAKEPEDAL_FRONT_A] = 1000;
	}
	else if (pedalData[ANALOG_BRAKEPEDAL_FRONT_A] < BRAKE_F_A_Umin) {
		pedalData[PMIL_BRAKEPEDAL_FRONT_A] = 0;
	}
	/* B signal */
	pedalData[PMIL_BRAKEPEDAL_FRONT_B] = 1000 * (pedalData[ANALOG_BRAKEPEDAL_FRONT_B] - BRAKE_F_B_Umin) / (BRAKE_F_B_Umax - BRAKE_F_B_Umin);
	if (pedalData[ANALOG_BRAKEPEDAL_FRONT_B] > BRAKE_F_B_Umin) {
		pedalData[PMIL_BRAKEPEDAL_FRONT_B] = 0;
	}
	else if (pedalData[ANALOG_BRAKEPEDAL_FRONT_B] < BRAKE_F_B_Umax) {
		pedalData[PMIL_BRAKEPEDAL_FRONT_B] = 1000;
	}
	/* Rear BrakePedal conversion */
	/* A signal */
	pedalData[PMIL_BRAKEPEDAL_REAR_A] = 1000 * (pedalData[ANALOG_BRAKEPEDAL_REAR_A] - BRAKE_R_A_Umin) / (BRAKE_R_A_Umax - BRAKE_R_A_Umin);
	if (pedalData[ANALOG_BRAKEPEDAL_REAR_A] > BRAKE_R_A_Umax) {
		pedalData[PMIL_BRAKEPEDAL_REAR_A] = 1000;
	}
	else if (pedalData[ANALOG_BRAKEPEDAL_REAR_A] < BRAKE_R_A_Umin) {
		pedalData[PMIL_BRAKEPEDAL_REAR_A] = 0;
	}
	/* B signal */
	pedalData[PMIL_BRAKEPEDAL_REAR_B] = 1000 * (pedalData[ANALOG_BRAKEPEDAL_REAR_B] - BRAKE_R_B_Umin) / (BRAKE_R_B_Umax - BRAKE_R_B_Umin);
	if (pedalData[ANALOG_BRAKEPEDAL_REAR_B]>BRAKE_R_B_Umin) {
		pedalData[PMIL_BRAKEPEDAL_REAR_B] = 0;
	}
	else if (pedalData[ANALOG_BRAKEPEDAL_REAR_B] < BRAKE_R_B_Umax) {
		pedalData[PMIL_BRAKEPEDAL_REAR_B] = 1000;
	}

	/* Redundance */
	/*
	bool GAS_F_NO   = (abs(pedalData[ANALOG_GASPEDAL_FRONT_A]   + pedalData[ANALOG_GASPEDAL_FRONT_B] - 5000) < 500);
	bool GAS_R_NO   = (abs(pedalData[ANALOG_GASPEDAL_REAR_A]    + pedalData[ANALOG_GASPEDAL_REAR_B] - 5000) < 500);
	bool BRAKE_F_NO = (abs(pedalData[ANALOG_BRAKEPEDAL_FRONT_A] + pedalData[ANALOG_BRAKEPEDAL_FRONT_B] - 5000) < 500);
	bool BRAKE_R_NO = (abs(pedalData[ANALOG_BRAKEPEDAL_REAR_A]  + pedalData[ANALOG_BRAKEPEDAL_REAR_B] - 5000) < 500);
	 */

	gasPedalLowPassFilter(chairPos);
}

static void gasPedalLowPassFilter(chairPosition chairPos) {

	if (chairPos == CHAIR_IS_FRONT) {
		pedalData[PMIL_GASPEDAL] = pedalData[PMIL_GASPEDAL_FRONT_A];
		pedalData[PMIL_BRAKEPEDAL] = pedalData[PMIL_BRAKEPEDAL_FRONT_A];
	} else { /* CHAIR_IS_BACK */
		pedalData[PMIL_GASPEDAL] = pedalData[PMIL_GASPEDAL_REAR_A];
		pedalData[PMIL_BRAKEPEDAL] = pedalData[PMIL_BRAKEPEDAL_REAR_A];
	}

	/* Low pass filter */
	pedalData[PMIL_PEDAL_OLD] = pedalData[PMIL_LP_PEDAL];
	pedalData[PMIL_PEDAL] 	  = pedalData[PMIL_GASPEDAL] - pedalData[PMIL_BRAKEPEDAL];

	const double T_s = 0.020;
	const double f_cutoff_pedal=0.3;

	/* LOW PASS FILTER OF SIGNALS */
	const double Tf = 1 / (2 * M_PI * f_cutoff_pedal);
	const double alpha = Tf / (Tf + T_s);

	pedalData[PMIL_LP_PEDAL] = alpha * pedalData[PMIL_PEDAL_OLD] + (1 - alpha) * pedalData[PMIL_PEDAL];

	if (pedalData[PMIL_LP_PEDAL] > 1000) {
		pedalData[PMIL_LP_PEDAL] = 1000;
	}
	if (pedalData[PMIL_LP_PEDAL] < 0) {
		pedalData[PMIL_LP_PEDAL] = 0;
	}
}


int GPSGetGassPedalFilterdAndScaled(void) {
	return pedalData[PMIL_LP_PEDAL];
}

int GPSGetBreakPedal(void) {
	return pedalData[PMIL_BRAKEPEDAL];
}



