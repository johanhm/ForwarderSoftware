
#include "WheelMotorActuate.h"

static int saturateMotorSignal(int motorSignal);

//Pump/Motor
#define	cfg_PM_DEBOUNCE 			100					/* debounce time [ms] for error detection */
#define	cfg_PM_DITHER_FREQUENCY 	f_100Hz_DU16 		/* dither frequency [Hz]*/
#define	cfg_PM_RESISTANCE_MIN 		14700				/* min resistance of solenoid for error detection [mOhm]*/
#define	cfg_PM_RESISTANCE_MAX 		43400				/* max resistance of solenoid for error detection[mOhm] */
#define	cfg_PM_KP_PM 				367					/*Kp factor*/
#define	cfg_PM_KI_PM 				262					/*Ki factor*/
#define	cfg_PM_KP_PM2 				400					/*Kp factor*/
#define	cfg_PM_KI_PM2				262					/*Ki factor*/

void WMASetupOutputToMotors(void) {

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
	if (state == FALSE) {
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
void WMASetMotorReferenceAndActuate(driveState machineDriveState, bool slipState, int periodicCallTime_ms) {

	driveState DriveSTATE = machineDriveState;

	//static uint16 Motor_OD_mEpsilon = 0;
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

	//--------MOTOR-----//
	static uint16 k1 = 0;
	static uint16 k2 = 0;
	static uint16 k3 = 0;
	static uint16 k4 = 0;
	static uint16 k5 = 0;
	static uint16 k6 = 0;

	/* Set k values depending on state or CAN */
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

	Motor_1_mEpsilon_ns = Motor_1_mEpsilon - slip1_lp;
	Motor_2_mEpsilon_ns = Motor_2_mEpsilon - slip2_lp;
	Motor_3_mEpsilon_ns = Motor_3_mEpsilon - slip3_lp;
	Motor_4_mEpsilon_ns = Motor_4_mEpsilon - slip4_lp;
	Motor_5_mEpsilon_ns = Motor_5_mEpsilon - slip5_lp;
	Motor_6_mEpsilon_ns = Motor_6_mEpsilon - slip6_lp;


	if (Motor_1_mEpsilon_ns > 1000) {
		Motor_1_mEpsilon_ns = 1000;
	}
	if (Motor_2_mEpsilon_ns > 1000) {
		Motor_2_mEpsilon_ns = 1000;
	}
	if (Motor_3_mEpsilon_ns > 1000) {
		Motor_3_mEpsilon_ns = 1000;
	}
	if (Motor_4_mEpsilon_ns > 1000) {
		Motor_4_mEpsilon_ns = 1000;
	}
	if (Motor_5_mEpsilon_ns > 1000) {
		Motor_5_mEpsilon_ns = 1000;
	}
	if (Motor_6_mEpsilon_ns > 1000) {
		Motor_6_mEpsilon_ns = 1000;
	}

	if (Motor_1_mEpsilon_ns < 0) {
		Motor_1_mEpsilon_ns = 0;
	}
	if (Motor_2_mEpsilon_ns < 0) {
		Motor_2_mEpsilon_ns = 0;
	}
	if (Motor_3_mEpsilon_ns < 0) {
		Motor_3_mEpsilon_ns = 0;
	}
	if (Motor_4_mEpsilon_ns < 0) {
		Motor_4_mEpsilon_ns = 0;
	}
	if (Motor_5_mEpsilon_ns < 0) {
		Motor_5_mEpsilon_ns = 0;
	}
	if (Motor_6_mEpsilon_ns < 0) {
		Motor_6_mEpsilon_ns = 0;
	}


	const int m_imax = 650;
	const int m_imin = 150;

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

	Motor_1_PWM = saturateMotorSignal(Motor_1_PWM);
	Motor_2_PWM = saturateMotorSignal(Motor_2_PWM);
	Motor_3_PWM = saturateMotorSignal(Motor_3_PWM);
	Motor_4_PWM = saturateMotorSignal(Motor_4_PWM);
	Motor_5_PWM = saturateMotorSignal(Motor_5_PWM);
	Motor_6_PWM = saturateMotorSignal(Motor_6_PWM);

	out(POH_CL_MOTOR_1_mA,Motor_1_PWM);
	out(POH_CL_MOTOR_2_mA,Motor_2_PWM);
	out(POH_CL_MOTOR_3_mA,Motor_3_PWM);
	out(POH_CL_MOTOR_4_mA,Motor_4_PWM);
	out(POH_CL_MOTOR_5_mA,Motor_5_PWM);
	out(POH_CL_MOTOR_6_mA,Motor_6_PWM);

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

}

static int saturateMotorSignal(int motorSignal) {
	if	(motorSignal>650) {
		motorSignal=650;
	}
	else if (motorSignal < 155) {
		motorSignal = 0;
	}
	return motorSignal;
}
