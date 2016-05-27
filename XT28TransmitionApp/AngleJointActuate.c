#include "AngleJointActuate.h"

#define PT 0.40
#define IT 0.05
#define WINDUP 3500

/* Decleration */
static void rearPIDControl(int avrageWheelSpeed);
static void saturateAndActuateAngleJoint(void);

void AJAInitAndSetupAngleJointActuate(void) {

	/*****************TURNINGVALVE1****************/
	out_cfg(POH_CL_TURN_FRONT_A_mA, 			//(* PWM output close loop *)
			cfg_T_DEBOUNCE,					//(* debounce time [ms] for error detection *)
			cfg_T_DITHER_FREQUENCY, 		//(* dither frequency [Hz]*)
			cfg_T_RESISTANCE_MIN, 			//(* min resistance of solenoid for error detection [mOhm]*)
			cfg_T_RESISTANCE_MAX );			//(* max resistance of solenoid for error detection[mOhm] *)
	// out_cfgPI ( POH_CL_TURN_FRONT_A_mA,		//(* Channel*)
	//		    cfg_T_KP_PM,					//(*Kp factor*)
	//     		cfg_T_KI_PM );					//(*Ki factor*)

	out_cfg(POH_CL_TURN_FRONT_B_mA, 			//(* PWM output close loop *)
			cfg_T_DEBOUNCE,					//(* debounce time [ms] for error detection *)
			cfg_T_DITHER_FREQUENCY, 		//(* dither frequency [Hz]*)
			cfg_T_RESISTANCE_MIN, 			//(* min resistance of solenoid for error detection [mOhm]*)
			cfg_T_RESISTANCE_MAX );			//(* max resistance of solenoid for error detection[mOhm] *)

	/*****************TURNINGVALVE2****************/
	out_cfg(POH_CL_TURN_REAR_A_mA, 			//(* PWM output close loop *)
			cfg_T_DEBOUNCE,					//(* debounce time [ms] for error detection *)
			cfg_T_DITHER_FREQUENCY, 		//(* dither frequency [Hz]*)
			cfg_T_RESISTANCE_MIN, 			//(* min resistance of solenoid for error detection [mOhm]*)
			cfg_T_RESISTANCE_MAX);			//(* max resistance of solenoid for error detection[mOhm] *)

	out_cfg(POH_CL_TURN_REAR_B_mA, 			//(* PWM output close loop *)
			cfg_T_DEBOUNCE,					//(* debounce time [ms] for error detection *)
			cfg_T_DITHER_FREQUENCY, 		//(* dither frequency [Hz]*)
			cfg_T_RESISTANCE_MIN, 			//(* min resistance of solenoid for error detection [mOhm]*)
			cfg_T_RESISTANCE_MAX);			//(* max resistance of solenoid for error detection[mOhm] *)
}

static turnState AJACurrentTurnState = TURN_FRONT;
turnState AJAAttemtToSetTurnStateTo(turnState attemtedState) {
	AJACurrentTurnState = attemtedState;
	return AJACurrentTurnState;
}

turnState AJAGetTurnState(void) {
	return AJACurrentTurnState;
}

//--Turning Valves current--//
const uint16 TurningValve_Imin = 415;
const uint16 TurningValve_Imax = 730;
const uint16 TurningValve_Imed = 500; /* 580 */

static uint16 PWM_turn_front_A = 0;
static uint16 PWM_turn_front_B = 0;
static uint16 PWM_turn_rear_A  = 0;
static uint16 PWM_turn_rear_B  = 0;
void AJAActuate(int joystickValue, bool chairPosition, int avrageWheelSpeed) {

	static sint32 joystick_pos = 0;
	static sint32 joystick_neg = 0;

	/* 1. Convert excipad joystick signal */
	sint16 MiniJoystick = joystickValue;
	if (chairPosition == TRUE) {
		if (MiniJoystick > 0) {
			joystick_pos = abs(MiniJoystick);
			joystick_neg = 0;
		}
		else if (MiniJoystick < 0) {
			joystick_neg = abs(MiniJoystick);
			joystick_pos = 0;
		} else {
			joystick_neg = 0;
			joystick_pos = 0;
		}
	} else { /* charPosition == FALSE */
		if (MiniJoystick < 0) {
			joystick_pos = abs(MiniJoystick);
			joystick_neg = 0;
		}
		else if (MiniJoystick > 0) {
			joystick_neg = abs(MiniJoystick);
			joystick_pos = 0;
		} else {
			joystick_neg = 0;
			joystick_pos = 0;
		}
	}

	/* 2. Calculate signals depending on state */
	switch(AJACurrentTurnState){
	case TURN_COMBINED:
		PWM_turn_front_A = joystick_pos * (TurningValve_Imax - TurningValve_Imin) / 1000 + TurningValve_Imin;//415-730
		PWM_turn_front_B = joystick_neg * (TurningValve_Imax - TurningValve_Imin) / 1000 + TurningValve_Imin;//415-730
		PWM_turn_rear_A  = joystick_pos * (TurningValve_Imed - TurningValve_Imin) / 1000 + TurningValve_Imin;//415-580
		PWM_turn_rear_B  = joystick_neg * (TurningValve_Imed - TurningValve_Imin) / 1000 + TurningValve_Imin;//415-580
		break;

	case TURN_FRONT:
		PWM_turn_front_A = joystick_pos * (TurningValve_Imax-TurningValve_Imin) / 1000 + TurningValve_Imin;
		PWM_turn_front_B = joystick_neg * (TurningValve_Imax-TurningValve_Imin) / 1000 + TurningValve_Imin;
		PWM_turn_rear_A  = 0;
		PWM_turn_rear_B  = 0;
		break;

	case TURN_REAR:
		PWM_turn_front_A = 0;
		PWM_turn_front_B = 0;
		PWM_turn_rear_A  = joystick_pos * (TurningValve_Imax-TurningValve_Imin) / 1000 + TurningValve_Imin;
		PWM_turn_rear_B  = joystick_neg * (TurningValve_Imax-TurningValve_Imin) / 1000 + TurningValve_Imin;
		break;

	case TURN_PID:

		PWM_turn_front_A = joystick_pos * (TurningValve_Imax-TurningValve_Imin) / 1000 + TurningValve_Imin;
		PWM_turn_front_B = joystick_neg * (TurningValve_Imax-TurningValve_Imin) / 1000 + TurningValve_Imin;
		rearPIDControl( avrageWheelSpeed );
		/* This function sets the last two pwn, with the use of globals */
	}

	/* 3. Actuate */
	saturateAndActuateAngleJoint();
}

static void rearPIDControl(int avrageWheelSpeed) {

	//--Turning PID parameters --//
	static sint32 TurningData = 0;
	static float errorAccT = 0;

	sint32 Front_angle = 0;

	Front_angle = AJSGetAngleFront();
	TurningData = (Front_angle - AJSGetAngleBack());

	if (TurningData > 10) {
		errorAccT = errorAccT + TurningData * 0.01;
	}
	else if (TurningData < -10)	{
		errorAccT = errorAccT + TurningData * 0.01;
	}
	else if (TurningData >= -10 && TurningData <= 10) {
		errorAccT = 0;
	}

	static sint16 PID_TURN_P = 0;
	static sint16 PID_TURN_I = 0;

	float Speed_dependancy = 0;

	Speed_dependancy = abs(avrageWheelSpeed) / 50;
	if (Speed_dependancy > 1) {
		Speed_dependancy = 1;
	}

	PID_TURN_P = TurningData * PT * Speed_dependancy;
	PID_TURN_I = errorAccT * IT;

	if (PID_TURN_I > 500)	{
		errorAccT = 500 / IT;
	}
	else if (PID_TURN_I < -500)	{
		errorAccT = -500 / IT;
	}

	sint32 PID_TURN = PID_TURN_P + PID_TURN_I;

	static enum {DEADBAND_STATE,
		TURN_A_STATE,
		TURN_B_STATE
	} Turn_AB_switch = DEADBAND_STATE;

	switch(Turn_AB_switch) {
	case DEADBAND_STATE:
		errorAccT = 0;
		if (TurningData > 50) {
			Turn_AB_switch = TURN_A_STATE;
			break;
		}
		if (TurningData < -50) {
			Turn_AB_switch = TURN_B_STATE;
			break;
		}
		break;

	case TURN_A_STATE:
		if ( (TurningData) < 0) {
			Turn_AB_switch = DEADBAND_STATE;
		}
		PWM_turn_rear_A = PID_TURN * (TurningValve_Imed - TurningValve_Imin) / 1000 + TurningValve_Imin;
		PWM_turn_rear_B = 0;
		break;

	case TURN_B_STATE:
		if ( (TurningData) > 0) {
			Turn_AB_switch = DEADBAND_STATE;
		}
		PWM_turn_rear_A = 0;
		PWM_turn_rear_B = -PID_TURN * (TurningValve_Imed - TurningValve_Imin) / 1000 + TurningValve_Imin;
		break;
	}
}

static void saturateAndActuateAngleJoint(void) {
	/** fixme Change this function so it works on arguments inputs and not globals? */

	if (PWM_turn_front_A > TurningValve_Imin) {
		out(POH_CL_TURN_FRONT_A_mA, PWM_turn_front_A);
	} else {
		out(POH_CL_TURN_FRONT_A_mA, 0);
	}

	if (PWM_turn_front_B > TurningValve_Imin){
		out(POH_CL_TURN_FRONT_B_mA, PWM_turn_front_B);
	} else {
		out(POH_CL_TURN_FRONT_B_mA, 0);
	}

	if (PWM_turn_rear_A > TurningValve_Imin) {
		out(POH_CL_TURN_REAR_A_mA, PWM_turn_rear_A);
	} else {
		out(POH_CL_TURN_REAR_A_mA, 0);
	}

	if (PWM_turn_rear_B > TurningValve_Imin) {
		out(POH_CL_TURN_REAR_B_mA, PWM_turn_rear_B);
	} else {
		out(POH_CL_TURN_REAR_B_mA, 0);
	}
}
