
#include "WheelMotorActuate.h"

static int saturateAnInt(int signal, int maxValue, int setMaxValue, int minValue, int setMinvalue);
static void pumpActuate(driveState xt28DriveState);

//Pump/Motor
#define	cfg_PM_DEBOUNCE 			100					/* debounce time [ms] for error detection */
#define	cfg_PM_DITHER_FREQUENCY 	f_100Hz_DU16 		/* dither frequency [Hz]*/
#define	cfg_PM_RESISTANCE_MIN 		14700				/* min resistance of solenoid for error detection [mOhm]*/
#define	cfg_PM_RESISTANCE_MAX 		43400				/* max resistance of solenoid for error detection[mOhm] */
#define	cfg_PM_KP_PM 				367					/*Kp factor*/
#define	cfg_PM_KI_PM 				262					/*Ki factor*/
#define	cfg_PM_KP_PM2 				400					/*Kp factor*/
#define	cfg_PM_KI_PM2				262					/*Ki factor*/

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

void WMASetBreakState(bool state) {

	/* ------BREAK----- */
	if (state == TRUE) {
		out(DOH_PBRAKEVALVE1,TRUE);		//Pbrake valve 1 output
		out(DOH_PBRAKEVALVE2,TRUE);		//Pbrake valve 2 output
		out(DOH_PBRAKEVALVE3,TRUE);		//Pbrake valve 3 output
	} else {
		out(DOH_PBRAKEVALVE1,FALSE);	//Pbrake valve 1 output
		out(DOH_PBRAKEVALVE2,FALSE);	//Pbrake valve 2 output
		out(DOH_PBRAKEVALVE3,FALSE);	//Pbrake valve 3 output
	}
}

static uint8 msg_CAN_ALYZER_4[8] = {0};
static uint8 msg_CAN_ALYZER_2[8] = {0};

static uint16 Motor_1_PWM = 0;
static uint16 Motor_2_PWM = 0;
static uint16 Motor_3_PWM = 0;
static uint16 Motor_4_PWM = 0;
static uint16 Motor_5_PWM = 0;
static uint16 Motor_6_PWM = 0;

static uint16 Pump_1_A_mEpsilon = 0;
static uint16 Pump_1_B_mEpsilon = 0;
static uint16 Pump_2_A_mEpsilon = 0;
static uint16 Pump_2_B_mEpsilon = 0;
void WMASetMotorReferenceAndActuate(driveState machineDriveState, bool overideState, bool slipState, int periodicCallTime_ms, int pMilLowPassGasPedalSignal) {

	static uint16 Pump_OD_mEpsilon = 0;

	static uint16 Motor_OD_mEpsilon = 0;
	static uint16 Motor_1_mEpsilon = 0;
	static uint16 Motor_2_mEpsilon = 0;
	static uint16 Motor_3_mEpsilon = 0;
	static uint16 Motor_4_mEpsilon = 0;
	static uint16 Motor_5_mEpsilon = 0;
	static uint16 Motor_6_mEpsilon = 0;

	static sint16 Motor_1_mEpsilon_ns = 0;
	static sint16 Motor_2_mEpsilon_ns = 0;
	static sint16 Motor_3_mEpsilon_ns = 0;
	static sint16 Motor_4_mEpsilon_ns = 0;
	static sint16 Motor_5_mEpsilon_ns = 0;
	static sint16 Motor_6_mEpsilon_ns = 0;

	driveState DriveSTATE = machineDriveState;

	/* From drive task */
	/* Step 1 - Set Epsilons depending on drive state! */
	switch(DriveSTATE){
	case NEUTRAL_DRIVE:

		Pump_1_A_mEpsilon = 0;
		Pump_1_B_mEpsilon = 0;
		Pump_2_A_mEpsilon = 0;
		Pump_2_B_mEpsilon = 0;
		Motor_1_mEpsilon = 1000;
		Motor_2_mEpsilon = 1000;
		Motor_3_mEpsilon = 1000;
		Motor_4_mEpsilon = 1000;
		Motor_5_mEpsilon = 1000;
		Motor_6_mEpsilon = 1000;

		break;
	case FORWARD_DRIVE:
		/* Action in state forward*/
		if (pMilLowPassGasPedalSignal > 500){
			Pump_OD_mEpsilon = 1000;
			Motor_OD_mEpsilon = 1000 * 350 / (pMilLowPassGasPedalSignal / 2) - 400;
		} else {
			Pump_OD_mEpsilon = pMilLowPassGasPedalSignal * 2;
			Motor_OD_mEpsilon = 1000;
		}

		if (overideState) {
			Pump_1_B_mEpsilon = Pump_OD_mEpsilon;
			Pump_2_B_mEpsilon = Pump_OD_mEpsilon;
			Pump_1_A_mEpsilon = 0;
			Pump_2_A_mEpsilon = 0;
			Motor_1_mEpsilon = Motor_OD_mEpsilon;
			Motor_2_mEpsilon = Motor_OD_mEpsilon;
			Motor_3_mEpsilon = 0;
			Motor_4_mEpsilon = 0;
			Motor_5_mEpsilon = 0;
			Motor_6_mEpsilon = 0;
		}
		else {
			Pump_1_B_mEpsilon = Pump_OD_mEpsilon;
			Pump_2_B_mEpsilon = Pump_OD_mEpsilon;
			Pump_1_A_mEpsilon = 0;
			Pump_2_A_mEpsilon = 0;
			Motor_1_mEpsilon = Motor_OD_mEpsilon;
			Motor_2_mEpsilon = Motor_OD_mEpsilon;
			Motor_3_mEpsilon = Motor_OD_mEpsilon;
			Motor_4_mEpsilon = Motor_OD_mEpsilon;
			Motor_5_mEpsilon = Motor_OD_mEpsilon;
			Motor_6_mEpsilon = Motor_OD_mEpsilon;
		}

		break;
	case BACKWARD_DRIVE: /* Action in state Backward*/

		if (pMilLowPassGasPedalSignal > 500){
			Pump_1_B_mEpsilon = 0;
			Pump_2_B_mEpsilon = 0;
			Pump_1_A_mEpsilon = 1000;
			Pump_2_A_mEpsilon = 1000;
			Motor_1_mEpsilon = 1000 * 350 / (pMilLowPassGasPedalSignal / 2) - 400;
			Motor_2_mEpsilon = 1000 * 350 / (pMilLowPassGasPedalSignal / 2) - 400;
			Motor_3_mEpsilon = 1000 * 350 / (pMilLowPassGasPedalSignal / 2) - 400;
			Motor_4_mEpsilon = 1000 * 350 / (pMilLowPassGasPedalSignal / 2) - 400;
			Motor_5_mEpsilon = 1000 * 350 / (pMilLowPassGasPedalSignal / 2) - 400;
			Motor_6_mEpsilon = 1000 * 350 / (pMilLowPassGasPedalSignal / 2) - 400;
		}
		else {
			Pump_1_B_mEpsilon = 0;
			Pump_2_B_mEpsilon = 0;
			Pump_1_A_mEpsilon = pMilLowPassGasPedalSignal * 2;
			Pump_2_A_mEpsilon = pMilLowPassGasPedalSignal * 2;
			Motor_1_mEpsilon = 1000;
			Motor_2_mEpsilon = 1000;
			Motor_3_mEpsilon = 1000;
			Motor_4_mEpsilon = 1000;
			Motor_5_mEpsilon = 1000;
			Motor_6_mEpsilon = 1000;
		}
		break;
	case PID_DRIVE:
		/* NYI so much code, did not want to clean it all*/
		break;
	default:
		DriveSTATE = NEUTRAL_DRIVE;
		break;
	}

	/* FROM OUTPUT TASK */
	//--------MOTOR-----//
	static uint16 k1 = 0;
	static uint16 k2 = 0;
	static uint16 k3 = 0;
	static uint16 k4 = 0;
	static uint16 k5 = 0;
	static uint16 k6 = 0;

	/* Step 2 - Set k values depending on drive state or CAN */
	if (DriveSTATE == PID_DRIVE) {
		k1 = 14;;
		k2 = 14;
		k3 = 14;
		k4 = 14;
		k5 = 14;
		k6 = 14;
	}
	else if (DriveSTATE == FORWARD_DRIVE || DriveSTATE == BACKWARD_DRIVE) {
		k1 = 2.6;
		k2 = 2.6;
		k3 = 2.6;
		k4 = 2.6;
		k5 = 2.6;
		k6 = 2.6;
	}
	else if (msg_CAN_ALYZER_4[0] != 0) {
		k1 = msg_CAN_ALYZER_4[0] / 10;
		k2 = msg_CAN_ALYZER_4[1] / 10;
		k3 = msg_CAN_ALYZER_4[2] / 10;
		k4 = msg_CAN_ALYZER_4[3] / 10;
		k5 = msg_CAN_ALYZER_4[4] / 10;
		k6 = msg_CAN_ALYZER_4[5] / 10;
	}

	/* Step 3 -  Tune lowpass filter constants depending on avrage RPM*/
	/* low pass filter Sliping stuff */
	static float f_cutoff_ns;
	static float Tf_S_ns;
	static float alpha_S_ns;

	if (WMSGetAvrageRPMForWheels() > 500){
		f_cutoff_ns = 0.02;
	} else {
		f_cutoff_ns = 0.10;
	}

	Tf_S_ns = 1 / (2 * M_PI * f_cutoff_ns);
	alpha_S_ns = Tf_S_ns / (Tf_S_ns + (float)periodicCallTime_ms / 1000);

	/* Step 4 - Calculate slip offset, and lowpass filter this badboj */
	/* Slip */
	static sint16 slip1 		= 0;
	static sint16 slip1_old_lp 	= 0;
	static sint16 slip1_lp 		= 0;

	static sint16 slip2 		= 0;
	static sint16 slip2_old_lp 	= 0;
	static sint16 slip2_lp 		= 0;

	static sint16 slip3 		= 0;
	static sint16 slip3_old_lp 	= 0;
	static sint16 slip3_lp 		= 0;

	static sint16 slip4 		= 0;
	static double slip4_old_lp 	= 0;
	static double slip4_lp 		= 0;

	static sint16 slip5 		= 0;
	static sint16 slip5_old_lp 	= 0;
	static sint16 slip5_lp 		= 0;

	static sint16 slip6 		= 0;
	static sint16 slip6_old_lp 	= 0;
	static sint16 slip6_lp 		= 0;

	slip1 = k1 * (WMSGetRPMForWheel(1) - WMSGetAvrageRPMForWheels());
	slip1_old_lp = slip1_lp;
	slip1_lp = alpha_S_ns * slip1_old_lp + (1 - alpha_S_ns) * slip1;

	slip2 = k2 * (WMSGetRPMForWheel(2) - WMSGetAvrageRPMForWheels());
	slip2_old_lp = slip2_lp;
	slip2_lp = alpha_S_ns*slip2_old_lp + (1 - alpha_S_ns) * slip2;

	slip3=k3 * (WMSGetRPMForWheel(3) - WMSGetAvrageRPMForWheels());
	slip3_old_lp = slip3_lp;
	slip3_lp = alpha_S_ns*slip3_old_lp + (1 - alpha_S_ns) * slip3;

	slip4 = k4 * (WMSGetRPMForWheel(4) - WMSGetAvrageRPMForWheels());
	slip4_old_lp = slip4_lp;
	slip4_lp = alpha_S_ns * slip4_old_lp + (1 - alpha_S_ns) * slip4;

	slip5 = k5 * (WMSGetRPMForWheel(5) - WMSGetAvrageRPMForWheels());
	slip5_old_lp = slip5_lp;
	slip5_lp = alpha_S_ns * slip5_old_lp + (1 - alpha_S_ns) * slip5;

	slip6=k6 * (WMSGetRPMForWheel(6) - WMSGetAvrageRPMForWheels());
	slip6_old_lp = slip6_lp;
	slip6_lp = alpha_S_ns * slip6_old_lp + (1 - alpha_S_ns) * slip6;

	/* Step 5 - Substract the slip */
	Motor_1_mEpsilon_ns = Motor_1_mEpsilon - slip1_lp;
	Motor_2_mEpsilon_ns = Motor_2_mEpsilon - slip2_lp;
	Motor_3_mEpsilon_ns = Motor_3_mEpsilon - slip3_lp;
	Motor_4_mEpsilon_ns = Motor_4_mEpsilon - slip4_lp;
	Motor_5_mEpsilon_ns = Motor_5_mEpsilon - slip5_lp;
	Motor_6_mEpsilon_ns = Motor_6_mEpsilon - slip6_lp;

	/* Step 6 - Saftey saturate */
	Motor_1_mEpsilon_ns = saturateAnInt(Motor_1_mEpsilon_ns, 1000, 1000, 0, 0);
	Motor_2_mEpsilon_ns = saturateAnInt(Motor_2_mEpsilon_ns, 1000, 1000, 0, 0);
	Motor_3_mEpsilon_ns = saturateAnInt(Motor_3_mEpsilon_ns, 1000, 1000, 0, 0);
	Motor_4_mEpsilon_ns = saturateAnInt(Motor_4_mEpsilon_ns, 1000, 1000, 0, 0);
	Motor_5_mEpsilon_ns = saturateAnInt(Motor_5_mEpsilon_ns, 1000, 1000, 0, 0);
	Motor_6_mEpsilon_ns = saturateAnInt(Motor_6_mEpsilon_ns, 1000, 1000, 0, 0);

	/* Step 7 - Calculate the PWM signal from the given epsilon */
	const int m_imax = 650;
	const int m_imin = 150;
	/**! FIXME What is the point of this if case when its rewritten in the lines below anyway */
	if (slipState == TRUE) {
		Motor_1_PWM = (m_imin - m_imax) * Motor_1_mEpsilon_ns / 1000 + m_imax;
		Motor_2_PWM = (m_imin - m_imax) * Motor_2_mEpsilon_ns / 1000 + m_imax;
		Motor_3_PWM = (m_imin - m_imax) * Motor_3_mEpsilon_ns / 1000 + m_imax;
		Motor_4_PWM = (m_imin - m_imax) * Motor_4_mEpsilon_ns / 1000 + m_imax;
		Motor_5_PWM = (m_imin - m_imax) * Motor_5_mEpsilon_ns / 1000 + m_imax;
		Motor_6_PWM = (m_imin - m_imax) * Motor_6_mEpsilon_ns / 1000 + m_imax;
	}

	Motor_1_PWM = (m_imin - m_imax) * Motor_1_mEpsilon_ns / 1000 + m_imax;
	Motor_2_PWM = (m_imin - m_imax) * Motor_2_mEpsilon_ns / 1000 + m_imax;
	Motor_3_PWM = (m_imin - m_imax) * Motor_3_mEpsilon_ns / 1000 + m_imax;
	Motor_4_PWM = (m_imin - m_imax) * Motor_4_mEpsilon_ns / 1000 + m_imax;
	Motor_5_PWM = (m_imin - m_imax) * Motor_5_mEpsilon_ns / 1000 + m_imax;
	Motor_6_PWM = (m_imin - m_imax) * Motor_6_mEpsilon_ns / 1000 + m_imax;

	/* Step 8 - FIXME Saturate again? why signal is allready saturated and then a static calculation is made. I suggest removeing the first saturation and keep this one */
	Motor_1_PWM = saturateAnInt(Motor_1_PWM, 650, 650, 155, 0);
	Motor_2_PWM = saturateAnInt(Motor_2_PWM, 650, 650, 155, 0);
	Motor_3_PWM = saturateAnInt(Motor_3_PWM, 650, 650, 155, 0);
	Motor_4_PWM = saturateAnInt(Motor_4_PWM, 650, 650, 155, 0);
	Motor_5_PWM = saturateAnInt(Motor_5_PWM, 650, 650, 155, 0);
	Motor_6_PWM = saturateAnInt(Motor_6_PWM, 650, 650, 155, 0);

	/* Step 9 - Actuate finaly */
	out(POH_CL_MOTOR_1_mA, Motor_1_PWM);
	out(POH_CL_MOTOR_2_mA, Motor_2_PWM);
	out(POH_CL_MOTOR_3_mA, Motor_3_PWM);
	out(POH_CL_MOTOR_4_mA, Motor_4_PWM);
	out(POH_CL_MOTOR_5_mA, Motor_5_PWM);
	out(POH_CL_MOTOR_6_mA, Motor_6_PWM);

	/* Step 10 - Actuate pump */
	pumpActuate(DriveSTATE);

}

static void pumpActuate(driveState xt28DriveState) {
	/* Pumps */
	static uint16 Pump_1_A_PWM = 0;
	static uint16 Pump_1_B_PWM = 0;
	static uint16 Pump_2_A_PWM = 0;
	static uint16 Pump_2_B_PWM = 0;

	//--Pump calibrationdata--//
	const uint16 Pump_1_MinA = 195;//185;
	const uint16 Pump_1_MaxA = 605;
	const uint16 Pump_2_MinA = 195;//185;//195;
	const uint16 Pump_2_MaxA = 605;//660;

	if (xt28DriveState == NEUTRAL_DRIVE) {
		Pump_1_A_PWM = 0;
		Pump_1_B_PWM = 0;
		Pump_2_A_PWM = 0;
		Pump_2_B_PWM = 0;
	} else {
		Pump_1_A_PWM = Pump_1_A_mEpsilon * (Pump_1_MaxA - Pump_1_MinA) / (1000) + Pump_1_MinA;
		Pump_1_B_PWM = Pump_1_B_mEpsilon * (Pump_1_MaxA - Pump_1_MinA) / (1000) + Pump_1_MinA;
		Pump_2_A_PWM = Pump_2_A_mEpsilon * (Pump_2_MaxA - Pump_2_MinA) / (1000) + Pump_2_MinA;
		Pump_2_B_PWM = Pump_2_B_mEpsilon * (Pump_2_MaxA - Pump_2_MinA) / (1000) + Pump_2_MinA;
	}

	Pump_1_A_PWM = saturateAnInt(Pump_1_A_PWM, 650, 650, 155, 0);
	Pump_1_B_PWM = saturateAnInt(Pump_1_B_PWM, 650, 650, 150, 0);
	Pump_2_A_PWM = saturateAnInt(Pump_2_A_PWM, 650, 650, 155, 0);
	Pump_2_B_PWM = saturateAnInt(Pump_2_B_PWM, 650, 650, 155, 0);

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

void WMASendMotorPWNOnCAN(bool buttonCANSendState) {
	if (buttonCANSendState == TRUE && msg_CAN_ALYZER_2[0] > 0){
		Motor_1_PWM = msg_CAN_ALYZER_2[0] * 3;
		Motor_2_PWM = msg_CAN_ALYZER_2[1] * 3;
		Motor_3_PWM = msg_CAN_ALYZER_2[2] * 3;
		Motor_4_PWM = msg_CAN_ALYZER_2[3] * 3;
		Motor_5_PWM = msg_CAN_ALYZER_2[4] * 3;
		Motor_6_PWM = msg_CAN_ALYZER_2[5] * 3;
	}
	/*! fixme eh add CAN */

}


