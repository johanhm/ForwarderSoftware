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

#define CAN_ID_TX_AKTUATOR_INFO_DMS_3			0x18FE1015
#define CAN_ID_TX_AKTUATOR_INFO_DMS_4			0x18FE1016
#define DB_TX_AKTUATOR_INFO_DMS_3			7
#define DB_TX_AKTUATOR_INFO_DMS_4			8


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

	out(POH_CL_PUMP_1_A_mA, Pump_1_A_PWM);
	out(POH_CL_PUMP_1_B_mA, Pump_1_B_PWM);
	out(POH_CL_PUMP_2_A_mA, Pump_2_A_PWM);
	out(POH_CL_PUMP_2_B_mA, Pump_2_B_PWM);
}

static uint8 sendCANChannel;
void WMACANConfigure(uint8 CANChannel) {
	sendCANChannel = CANChannel;
	can_cfgTxDatabox(CANChannel, DB_TX_AKTUATOR_INFO_DMS_3 ,CAN_ID_TX_AKTUATOR_INFO_DMS_3, CAN_EXD_DU8);
	can_cfgTxDatabox(CANChannel, DB_TX_AKTUATOR_INFO_DMS_4 ,CAN_ID_TX_AKTUATOR_INFO_DMS_4, CAN_EXD_DU8);
}


/* Turning cylinders, FOR MESSAGE; should probably move to the AJA module */
#define	POH_CL_TURN_FRONT_A_mA				OUT_13_POH_CL 	// (*FRONT*)
#define	POH_CL_TURN_FRONT_B_mA				OUT_14_POH_CL
#define	POH_CL_TURN_REAR_A_mA				OUT_15_POH_CL	//(*REAR*)
#define	POH_CL_TURN_REAR_B_mA				OUT_16_POH_CL
void WMASendCurrentReferenceOnCAN(void) {

		/* Pump message */
	{
		/* AJActuate */
		out_ts out_s1;
		out_ts out_s2;
		out_ts out_s3;
		out_ts out_s4;

		out_getStatusxt(POH_CL_TURN_FRONT_A_mA, &out_s1);
		out_getStatusxt(POH_CL_TURN_FRONT_B_mA, &out_s2);
		out_getStatusxt(POH_CL_TURN_REAR_A_mA, &out_s3);
		out_getStatusxt(POH_CL_TURN_REAR_B_mA, &out_s4);

		uint16 i_mA_Turn_Front_A = out_s1.out_po_s.i_mA_u16; /* actual current in mA */
		uint16 i_mA_Turn_Front_B = out_s2.out_po_s.i_mA_u16; /* actual current in mA */
		uint16 i_mA_Turn_Rear_A = out_s3.out_po_s.i_mA_u16; /* actual current in mA */
		uint16 i_mA_Turn_Rear_B = out_s4.out_po_s.i_mA_u16; /* actual current in mA */

		out_ts out_pa1;
		out_ts out_pa2;
		out_ts out_pb1;
		out_ts out_pb2;

		/* Pump currents */
		out_getStatusxt(POH_CL_PUMP_1_A_mA, &out_pa1);
		out_getStatusxt(POH_CL_PUMP_1_B_mA, &out_pb1);
		out_getStatusxt(POH_CL_PUMP_2_A_mA, &out_pa2);
		out_getStatusxt(POH_CL_PUMP_2_B_mA, &out_pb2);

		uint16 i_mA_Pump_1A_act = out_pa1.out_po_s.i_mA_u16; /* actual current in mA */
		uint16 i_mA_Pump_1B_act = out_pb1.out_po_s.i_mA_u16; /* actual current in mA */
		uint16 i_mA_Pump_2A_act = out_pa2.out_po_s.i_mA_u16; /* actual current in mA */
		uint16 i_mA_Pump_2B_act = out_pb2.out_po_s.i_mA_u16; /* actual current in mA */


		//Construct msg AKTUATOR DMS 3
		uint8 data_au8_akt_dms_3[8];
		data_au8_akt_dms_3[0] = i_mA_Pump_1A_act / 3;
		data_au8_akt_dms_3[1] = i_mA_Pump_1B_act / 3;
		data_au8_akt_dms_3[2] = i_mA_Pump_2A_act / 3;
		data_au8_akt_dms_3[3] = i_mA_Pump_2B_act / 3;
		data_au8_akt_dms_3[4] = i_mA_Turn_Front_A / 3;
		data_au8_akt_dms_3[5] = i_mA_Turn_Front_B / 3;
		data_au8_akt_dms_3[6] = i_mA_Turn_Rear_A / 3;
		data_au8_akt_dms_3[7] = i_mA_Turn_Rear_B / 3;

		can_sendDatabox(sendCANChannel,DB_TX_AKTUATOR_INFO_DMS_3, 8, data_au8_akt_dms_3);
	}
		/* Motor message */
	{
		out_ts out_m1;
		out_ts out_m2;
		out_ts out_m3;
		out_ts out_m4;
		out_ts out_m5;
		out_ts out_m6;

		out_getStatusxt(POH_CL_MOTOR_1_mA, &out_m1);
		out_getStatusxt(POH_CL_MOTOR_2_mA, &out_m2);
		out_getStatusxt(POH_CL_MOTOR_3_mA, &out_m3);
		out_getStatusxt(POH_CL_MOTOR_4_mA, &out_m4);
		out_getStatusxt(POH_CL_MOTOR_5_mA, &out_m5);
		out_getStatusxt(POH_CL_MOTOR_6_mA, &out_m6);


		uint16 i_mA_Motor_1_act = out_m1.out_po_s.i_mA_u16; /* actual current in mA */
		uint16 i_mA_Motor_2_act = out_m2.out_po_s.i_mA_u16; /* actual current in mA */
		uint16 i_mA_Motor_3_act = out_m3.out_po_s.i_mA_u16; /* actual current in mA */
		uint16 i_mA_Motor_4_act = out_m4.out_po_s.i_mA_u16; /* actual current in mA */
		uint16 i_mA_Motor_5_act = out_m5.out_po_s.i_mA_u16; /* actual current in mA */
		uint16 i_mA_Motor_6_act = out_m6.out_po_s.i_mA_u16; /* actual current in mA */

		//Construct msg AKTUATOR DMS 4
		uint8 data_au8_akt_dms_4[8];
		data_au8_akt_dms_4[0] = i_mA_Motor_1_act / 3;
		data_au8_akt_dms_4[1] = i_mA_Motor_2_act / 3;
		data_au8_akt_dms_4[2] = i_mA_Motor_3_act / 3;
		data_au8_akt_dms_4[3] = i_mA_Motor_4_act / 3;
		data_au8_akt_dms_4[4] = i_mA_Motor_5_act / 3;
		data_au8_akt_dms_4[5] = i_mA_Motor_6_act / 3;
		data_au8_akt_dms_4[6] = 0;
		data_au8_akt_dms_4[7] = 0;

		can_sendDatabox(sendCANChannel,DB_TX_AKTUATOR_INFO_DMS_4, 8, data_au8_akt_dms_4);
	}

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
