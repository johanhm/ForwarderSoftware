#include "WheelMotorActuate.h"

/* Private declerations */
static int saturateAnInt(int signal, int maxValue, int setMaxValue, int minValue, int setMinvalue);

/* Private defines unsed only in thos module */
//Pump/Motor
#define	cfg_PM_DEBOUNCE 			100					/* debounce time [ms] for error detection */
#define	cfg_PM_DITHER_FREQUENCY 	f_100Hz_DU16 		/* dither frequency [Hz]*/
#define	cfg_PM_RESISTANCE_MIN 		14700				/* min resistance of solenoid for error detection [mOhm]*/
#define	cfg_PM_RESISTANCE_MAX 		43400				/* max resistance of solenoid for error detection[mOhm] */
#define	cfg_PM_KP_PM 				367					/*Kp factor*/
#define	cfg_PM_KI_PM 				262					/*Ki factor*/
#define	cfg_PM_KP_PM2 				400					/*Kp factor*/
#define	cfg_PM_KI_PM2				262					/*Ki factor*/


/* Function implementations */
void WMASetupOutputToMotorsAndPumps(void) {

	/*****************PUMP1****************/
	out_cfg(POH_CL_PUMP_1_A_mA, 				//(* PWM output close loop *)
			cfg_PM_DEBOUNCE,				//(* debounce time [ms] for error detection *)
			cfg_PM_DITHER_FREQUENCY, 		//(* dither frequency [Hz]*)
			cfg_PM_RESISTANCE_MIN, 			//(* min resistance of solenoid for error detection [mOhm]*)
			cfg_PM_RESISTANCE_MAX );		//(* max resistance of solenoid for error detection[mOhm] *)
	out_cfgPI ( POH_CL_PUMP_1_A_mA,			//(* Channel*)
			cfg_PM_KP_PM,					//(*Kp factor*)
			cfg_PM_KI_PM );					//(*Ki factor*)

	out_cfg(POH_CL_PUMP_1_B_mA, 				//(* PWM output close loop *)
			cfg_PM_DEBOUNCE,				//(* debounce time [ms] for error detection *)
			cfg_PM_DITHER_FREQUENCY, 		//(* dither frequency [Hz]*)
			cfg_PM_RESISTANCE_MIN, 			//(* min resistance of solenoid for error detection [mOhm]*)
			cfg_PM_RESISTANCE_MAX );		//(* max resistance of solenoid for error detection[mOhm] *)
	out_cfgPI ( POH_CL_PUMP_1_B_mA,			//(* Channel*)
			cfg_PM_KP_PM,					//(*Kp factor*)
			cfg_PM_KI_PM );					//(*Ki factor*)

	/*****************PUMP2****************/
	out_cfg(POH_CL_PUMP_2_A_mA, 				//(* PWM output close loop *)
			cfg_PM_DEBOUNCE,				//(* debounce time [ms] for error detection *)
			cfg_PM_DITHER_FREQUENCY, 		//(* dither frequency [Hz]*)
			cfg_PM_RESISTANCE_MIN, 			//(* min resistance of solenoid for error detection [mOhm]*)
			cfg_PM_RESISTANCE_MAX );		//(* max resistance of solenoid for error detection[mOhm] *)
	out_cfgPI ( POH_CL_PUMP_2_A_mA,			//(* Channel*)
			cfg_PM_KP_PM,					//(*Kp factor*)
			cfg_PM_KI_PM );					//(*Ki factor*)

	out_cfg(POH_CL_PUMP_2_B_mA, 				//(* PWM output close loop *)
			cfg_PM_DEBOUNCE,				//(* debounce time [ms] for error detection *)
			cfg_PM_DITHER_FREQUENCY, 		//(* dither frequency [Hz]*)
			cfg_PM_RESISTANCE_MIN, 			//(* min resistance of solenoid for error detection [mOhm]*)
			cfg_PM_RESISTANCE_MAX );		//(* max resistance of solenoid for error detection[mOhm] *)
	out_cfgPI ( POH_CL_PUMP_2_B_mA,			//(* Channel*)
			cfg_PM_KP_PM,					//(*Kp factor*)
			cfg_PM_KI_PM );					//(*Ki factor*)

	/*****************MOTOR1****************/
	out_cfg(POH_CL_MOTOR_1_mA, 				//(* PWM output close loop *)
			cfg_PM_DEBOUNCE,				//(* debounce time [ms] for error detection *)
			cfg_PM_DITHER_FREQUENCY, 		//(* dither frequency [Hz]*)
			cfg_PM_RESISTANCE_MIN, 			//(* min resistance of solenoid for error detection [mOhm]*)
			cfg_PM_RESISTANCE_MAX );		//(* max resistance of solenoid for error detection[mOhm] *)
	out_cfgPI ( POH_CL_MOTOR_1_mA,			//(* Channel*)
			cfg_PM_KP_PM,					//(*Kp factor*)
			cfg_PM_KI_PM );					//(*Ki factor*)

	/*****************MOTOR2****************/
	out_cfg(POH_CL_MOTOR_2_mA, 				//(* PWM output close loop *)
			cfg_PM_DEBOUNCE,				//(* debounce time [ms] for error detection *)
			cfg_PM_DITHER_FREQUENCY, 		//(* dither frequency [Hz]*)
			cfg_PM_RESISTANCE_MIN, 			//(* min resistance of solenoid for error detection [mOhm]*)
			cfg_PM_RESISTANCE_MAX );		//(* max resistance of solenoid for error detection[mOhm] *)
	out_cfgPI ( POH_CL_MOTOR_2_mA,				//(* Channel*)
			cfg_PM_KP_PM,					//(*Kp factor*)
			cfg_PM_KI_PM );					//(*Ki factor*)

	/*****************MOTOR3****************/
	out_cfg(POH_CL_MOTOR_3_mA, 				//(* PWM output close loop *)
			cfg_PM_DEBOUNCE,				//(* debounce time [ms] for error detection *)
			cfg_PM_DITHER_FREQUENCY, 		//(* dither frequency [Hz]*)
			cfg_PM_RESISTANCE_MIN, 			//(* min resistance of solenoid for error detection [mOhm]*)
			cfg_PM_RESISTANCE_MAX );		//(* max resistance of solenoid for error detection[mOhm] *)
	out_cfgPI ( POH_CL_MOTOR_3_mA,				//(* Channel*)
			cfg_PM_KP_PM,					//(*Kp factor*)
			cfg_PM_KI_PM );					//(*Ki factor*)

	/*****************MOTOR4****************/
	out_cfg(POH_CL_MOTOR_4_mA, 				//(* PWM output close loop *)
			cfg_PM_DEBOUNCE,				//(* debounce time [ms] for error detection *)
			cfg_PM_DITHER_FREQUENCY, 		//(* dither frequency [Hz]*)
			cfg_PM_RESISTANCE_MIN, 			//(* min resistance of solenoid for error detection [mOhm]*)
			cfg_PM_RESISTANCE_MAX );		//(* max resistance of solenoid for error detection[mOhm] *)
	out_cfgPI ( POH_CL_MOTOR_4_mA,			//(* Channel*)
			cfg_PM_KP_PM,					//(*Kp factor*)
			cfg_PM_KI_PM );					//(*Ki factor*)

	/*****************MOTOR5****************/
	out_cfg(POH_CL_MOTOR_5_mA, 				//(* PWM output close loop *)
			cfg_PM_DEBOUNCE,				//(* debounce time [ms] for error detection *)
			cfg_PM_DITHER_FREQUENCY, 		//(* dither frequency [Hz]*)
			cfg_PM_RESISTANCE_MIN, 			//(* min resistance of solenoid for error detection [mOhm]*)
			cfg_PM_RESISTANCE_MAX );		//(* max resistance of solenoid for error detection[mOhm] *)
	out_cfgPI ( POH_CL_MOTOR_5_mA,			//(* Channel*)
			cfg_PM_KP_PM,					//(*Kp factor*)
			cfg_PM_KI_PM );					//(*Ki factor*)

	/*****************MOTOR6****************/
	out_cfg(POH_CL_MOTOR_6_mA, 				//(* PWM output close loop *)
			cfg_PM_DEBOUNCE,				//(* debounce time [ms] for error detection *)
			cfg_PM_DITHER_FREQUENCY, 		//(* dither frequency [Hz]*)
			cfg_PM_RESISTANCE_MIN, 			//(* min resistance of solenoid for error detection [mOhm]*)
			cfg_PM_RESISTANCE_MAX );		//(* max resistance of solenoid for error detection[mOhm] *)
	out_cfgPI ( POH_CL_MOTOR_6_mA,			//(* Channel*)
			cfg_PM_KP_PM,					//(*Kp factor*)
			cfg_PM_KI_PM );					//(*Ki factor*)


	/* DOH's */
	out_cfg(DOH_PBRAKEVALVE1, 100, 0, 0, 0);
	out_cfg(DOH_PBRAKEVALVE2, 100, 0, 0, 0);
	out_cfg(DOH_PBRAKEVALVE3, 100, 0, 0, 0);

}


static bool breakEnabled = TRUE;
void WMASetBreakState(bool state) {

	/* Break */
	if (state == TRUE) { /* Break state */

		/* 1. Shut pumps down */
		SRControlSignals actuateZeroBlock;
		actuateZeroBlock.pump_A_mEpsilon[0] = 0;
		actuateZeroBlock.pump_A_mEpsilon[1] = 0;
		actuateZeroBlock.pump_B_mEpsilon[0] = 0;
		actuateZeroBlock.pump_B_mEpsilon[1] = 0;
		actuateZeroBlock.motor_mEpsilon[0]  = 1000;
		actuateZeroBlock.motor_mEpsilon[1]  = 1000;
		actuateZeroBlock.motor_mEpsilon[2]  = 1000;
		actuateZeroBlock.motor_mEpsilon[3]  = 1000;
		actuateZeroBlock.motor_mEpsilon[4]  = 1000;
		actuateZeroBlock.motor_mEpsilon[5]  = 1000;
		WMASaturateEpsilonAndActuateMotors(actuateZeroBlock);
		/* 2. Disable actuation enableing */
		breakEnabled = TRUE;

		/* 3. Set the breaks */
		out(DOH_PBRAKEVALVE1, FALSE);		//Pbrake valve 1 output
		out(DOH_PBRAKEVALVE2, FALSE);		//Pbrake valve 2 output
		out(DOH_PBRAKEVALVE3, FALSE);		//Pbrake valve 3 output
	} else { /* Break disabled state */

		out(DOH_PBRAKEVALVE1, TRUE);	//Pbrake valve 1 output
		out(DOH_PBRAKEVALVE2, TRUE);	//Pbrake valve 2 output
		out(DOH_PBRAKEVALVE3, TRUE);	//Pbrake valve 3 output

		/* Enable actuate function */
		breakEnabled = FALSE;
	}
}

bool WMAGetBreakState(void) {
	return breakEnabled;
}

void WMASaturateEpsilonAndActuateMotors(SRControlSignals controlSignals) {

	if (breakEnabled == TRUE) {
		return;
	}

	/* Step 1 - Calculate the PWM signal from the given epsilon */
	const int m_imax = 650;
	const int m_imin = 150;

	uint16 Motor_1_PWM = (m_imin - m_imax) * controlSignals.motor_mEpsilon[0] / 1000 + m_imax;
	uint16 Motor_2_PWM = (m_imin - m_imax) * controlSignals.motor_mEpsilon[1] / 1000 + m_imax;
	uint16 Motor_3_PWM = (m_imin - m_imax) * controlSignals.motor_mEpsilon[2] / 1000 + m_imax;
	uint16 Motor_4_PWM = (m_imin - m_imax) * controlSignals.motor_mEpsilon[3] / 1000 + m_imax;
	uint16 Motor_5_PWM = (m_imin - m_imax) * controlSignals.motor_mEpsilon[4] / 1000 + m_imax;
	uint16 Motor_6_PWM = (m_imin - m_imax) * controlSignals.motor_mEpsilon[5] / 1000 + m_imax;

	/* Step 2 - FIXME Saturate again? why signal is allready saturated and then a static calculation is made. I suggest removeing the first saturation and keep this one */
	Motor_1_PWM = saturateAnInt(Motor_1_PWM, 650, 650, 155, 0);
	Motor_2_PWM = saturateAnInt(Motor_2_PWM, 650, 650, 155, 0);
	Motor_3_PWM = saturateAnInt(Motor_3_PWM, 650, 650, 155, 0);
	Motor_4_PWM = saturateAnInt(Motor_4_PWM, 650, 650, 155, 0);
	Motor_5_PWM = saturateAnInt(Motor_5_PWM, 650, 650, 155, 0);
	Motor_6_PWM = saturateAnInt(Motor_6_PWM, 650, 650, 155, 0);

/*
	g_debug1_1 = Motor_1_PWM;
	g_debug1_2 = Motor_2_PWM;
	g_debug1_3 = Motor_3_PWM;
	g_debug1_4 = Motor_4_PWM;
	g_debug2_1 = Motor_5_PWM;
	g_debug2_2 = Motor_5_PWM;
*/

	/* Step 3 - Actuate finaly */

	out(POH_CL_MOTOR_1_mA, Motor_1_PWM);
	out(POH_CL_MOTOR_2_mA, Motor_2_PWM);
	out(POH_CL_MOTOR_3_mA, Motor_3_PWM);
	out(POH_CL_MOTOR_4_mA, Motor_4_PWM);
	out(POH_CL_MOTOR_5_mA, Motor_5_PWM);
	out(POH_CL_MOTOR_6_mA, Motor_6_PWM);


	/* Pump calibrationdata */
	const uint16 Pump_1_MinA = 195;//185;
	const uint16 Pump_1_MaxA = 605;
	const uint16 Pump_2_MinA = 195;//185;//195;
	const uint16 Pump_2_MaxA = 605;//660;

	uint16 Pump_1_A_PWM = controlSignals.pump_A_mEpsilon[0] * (Pump_1_MaxA - Pump_1_MinA) / (1000) + Pump_1_MinA;
	uint16 Pump_1_B_PWM = controlSignals.pump_B_mEpsilon[0] * (Pump_1_MaxA - Pump_1_MinA) / (1000) + Pump_1_MinA;
	uint16 Pump_2_A_PWM = controlSignals.pump_A_mEpsilon[1] * (Pump_2_MaxA - Pump_2_MinA) / (1000) + Pump_2_MinA;
	uint16 Pump_2_B_PWM = controlSignals.pump_B_mEpsilon[1] * (Pump_2_MaxA - Pump_2_MinA) / (1000) + Pump_2_MinA;

	Pump_1_A_PWM = saturateAnInt(Pump_1_A_PWM, 605, 605, 197, 0);
	Pump_1_B_PWM = saturateAnInt(Pump_1_B_PWM, 605, 605, 197, 0);
	Pump_2_A_PWM = saturateAnInt(Pump_2_A_PWM, 605, 605, 197, 0);
	Pump_2_B_PWM = saturateAnInt(Pump_2_B_PWM, 605, 605, 197, 0);

/*
	g_debug3_1 = Pump_1_A_PWM;
	g_debug3_2 = Pump_1_B_PWM;
	g_debug3_3 = Pump_2_A_PWM;
	g_debug3_4 = Pump_2_B_PWM;
*/

	out(POH_CL_PUMP_1_A_mA, Pump_1_A_PWM);
	out(POH_CL_PUMP_1_B_mA, Pump_1_B_PWM);
	out(POH_CL_PUMP_2_A_mA, Pump_2_A_PWM);
	out(POH_CL_PUMP_2_B_mA, Pump_2_B_PWM);
}

static int saturateAnInt(int signal, int maxValue, int setMaxValue, int minValue, int setMinvalue) {
	if	(signal > maxValue) {
		signal = setMaxValue;
	}
	else if (signal < minValue) {
		signal = setMinvalue;
	}
	return signal;
}
