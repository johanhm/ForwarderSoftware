
#include "TransmistionControlSekvens.h"

/* Private function declerations */
static int calculateSlipOffsetController(int motorNumber, transmControlState DriveSTATE, int periodicCallTime_ms);
static float pumpRegulator(void);
static SRControlSignals sekvensRegulation(int pMilLowPassGasPedalSignal, int maxSpeed);
static SRControlSignals sekvensRegulationWithPumpRegulaton(int pMilLowPassGasPedalSignal, int maxSpeed);
static int saturateAnInt(int signal, int maxValue, int setMaxValue, int minValue, int setMinvalue);

/* Globals local */
static float integratedError = 0;




/* functions */
static driveState TCSSetDriveState = NEUTRAL_DRIVE;
driveState TCSAttemtToSetDriveStateTo(driveState attemtedDriveState) {

	//g_debug1_1 = 1337;
	//g_debug2_1 = CSGetDoorState();
	//g_debug2_2 = GPSGetGassPedalFilterdAndScaled();

	/*
	bool doorIsOpen_And_GasPedalIsNotPressed = (CSGetDoorState() == FALSE && GPSGetGassPedalFilterdAndScaled() < 150);
	if (doorIsOpen_And_GasPedalIsNotPressed) {
		TCSSetDriveState = NEUTRAL_DRIVE;
		g_debug1_2 = attemtedDriveState;
		return TCSSetDriveState;
	}
	*/
	if (GPSGetGassPedalFilterdAndScaled() > 150) {
		return TCSSetDriveState;
	}

	/* Door is closed, gaspedal is not pressed and the break state is not active */
	TCSSetDriveState = attemtedDriveState;

	//g_debug1_3 = doorIsOpen_And_GasPedalIsNotPressed;
	//g_debug1_2 = attemtedDriveState;


	return TCSSetDriveState;
}

driveState TCSGetSetDriveState(void) {
	return TCSSetDriveState;
}

bool TCSAttemtToSetBreakStateTo(bool breakState) {
	/* Can only leave or enter break sate if the gas pedal is NOT pressed */
	if (GPSGetGassPedalFilterdAndScaled() < 150) {
		WMASetBreakState(breakState);
	}
	return WMAGetBreakState();
}

void TCSActuate(int gasPedal, int maxSpeed, bool pumpRegulatorState) {

	/* 0. Check that the drive state is OK. */
	TCSAttemtToSetDriveStateTo(TCSSetDriveState);

	/* 1. Get control signals block from sequence regulator */
	SRControlSignals controlSignals;
	if (pumpRegulatorState == TRUE) {
		controlSignals = sekvensRegulationWithPumpRegulaton(gasPedal, maxSpeed);
	} else {
		integratedError = 0;
		controlSignals = sekvensRegulation(gasPedal, maxSpeed);
	}

	/* 2. Change the signals depending on control state */
	switch(TCSSetDriveState) {
	case NEUTRAL_DRIVE:
		controlSignals.pump_A_mEpsilon[0] = 0;
		controlSignals.pump_A_mEpsilon[1] = 0;
		controlSignals.pump_B_mEpsilon[0] = 0;
		controlSignals.pump_B_mEpsilon[1] = 0;
		controlSignals.motor_mEpsilon[0]  = 1000;
		controlSignals.motor_mEpsilon[1]  = 1000;
		controlSignals.motor_mEpsilon[2]  = 1000;
		controlSignals.motor_mEpsilon[3]  = 1000;
		controlSignals.motor_mEpsilon[4]  = 1000;
		controlSignals.motor_mEpsilon[5]  = 1000;
		break;
	case FORWARD_DRIVE:
		controlSignals.pump_A_mEpsilon[0] = 0;
		controlSignals.pump_A_mEpsilon[1] = 0;
		break;
	case BACKWARD_DRIVE:
		controlSignals.pump_B_mEpsilon[0] = 0;
		controlSignals.pump_B_mEpsilon[1] = 0;
		break;
	case FORWARD_OVERDRIVE:
		controlSignals.pump_A_mEpsilon[0] = 0;
		controlSignals.pump_A_mEpsilon[1] = 0;
		controlSignals.motor_mEpsilon[2]  = 0;
		controlSignals.motor_mEpsilon[3]  = 0;
		controlSignals.motor_mEpsilon[4]  = 0;
		controlSignals.motor_mEpsilon[5]  = 0;
		break;
	}
	/* 3. Actuate epsilon block signals */
	WMASaturateEpsilonAndActuateMotors(controlSignals);
}

static SRControlSignals sekvensRegulation(int pMilLowPassGasPedalSignal, int maxSpeed) {
	SRControlSignals controlSignals;

	static int pumpEpsilon = 0;
	static int motorEpsilon = 0;

	float niva = 3.0;
	int speedControl;
	maxSpeed = saturateAnInt(maxSpeed, 1000, 1000, 100, 100);
	speedControl = pMilLowPassGasPedalSignal * maxSpeed / 1000;

	/* 1. Calculate a ställtal linarely from gaspedal */
	if (speedControl > 1000 / niva) {
		pumpEpsilon = 1000;
		motorEpsilon = 1000 * (1000 / niva) / (speedControl);
	} else {
		pumpEpsilon = speedControl * niva;
		motorEpsilon = 1000;
	}

	/* 2 . Set induvidual control ställtal for all wheels */
	controlSignals.motor_mEpsilon[0] = motorEpsilon - calculateSlipOffsetController(0, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[1] = motorEpsilon - calculateSlipOffsetController(1, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[2] = motorEpsilon - calculateSlipOffsetController(2, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[3] = motorEpsilon - calculateSlipOffsetController(3, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[4] = motorEpsilon - calculateSlipOffsetController(4, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[5] = motorEpsilon - calculateSlipOffsetController(5, REGULATOR_SEKVENS, 10);

	/* 3. Set pump values */
	controlSignals.pump_A_mEpsilon[0] = pumpEpsilon;
	controlSignals.pump_A_mEpsilon[1] = pumpEpsilon;
	controlSignals.pump_B_mEpsilon[0] = pumpEpsilon;
	controlSignals.pump_B_mEpsilon[1] = pumpEpsilon;

	return controlSignals;
}

static SRControlSignals sekvensRegulationWithPumpRegulaton(int pMilLowPassGasPedalSignal, int maxSpeed) {
	SRControlSignals controlSignals;

	static int pumpEpsilon1 = 0;
	static int motorEpsilon1 = 0;
	static int pumpEpsilon2 = 0;
	static int motorEpsilon2 = 0;

	const float niva = 3.0;
	int speedControl1 = 0;
	int speedControl2 = 0;
	maxSpeed = saturateAnInt(maxSpeed, 1000, 1000, 100, 100);

	/* 1. 1st pump side */
	speedControl1 = pMilLowPassGasPedalSignal * maxSpeed / 1000;

	g_debug1_3 = speedControl1;

	if (speedControl1 > 1000 / niva) {
		pumpEpsilon1 = 1000;
		motorEpsilon1 = 1000 * (1000 / niva) / (speedControl1);
	} else {
		pumpEpsilon1 = speedControl1 * niva;
		motorEpsilon1 = 1000;
	}

	/* 2. Same thing B side */
	int regulatedGaspedal = pMilLowPassGasPedalSignal + pumpRegulator();
	regulatedGaspedal = saturateAnInt(regulatedGaspedal, 1000, 1000, 0, 0);
	speedControl2 = (regulatedGaspedal) * maxSpeed / 1000;

	g_debug1_4 = speedControl2;

	if (speedControl2 > 1000 / niva) {
		pumpEpsilon2 = 1000;
		motorEpsilon2 = 1000 * (1000 / niva) / (speedControl2);
	} else {
		pumpEpsilon2 = speedControl2 * niva;
		motorEpsilon2 = 1000;
	}

	/* 3 . Set induvidual control ställtal for all wheels */
	controlSignals.motor_mEpsilon[0] = motorEpsilon1; //- calculateSlipOffsetController(0, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[1] = motorEpsilon2; //- calculateSlipOffsetController(1, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[2] = motorEpsilon2; //- calculateSlipOffsetController(2, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[3] = motorEpsilon1; //- calculateSlipOffsetController(3, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[4] = motorEpsilon2; //- calculateSlipOffsetController(4, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[5] = motorEpsilon1; //- calculateSlipOffsetController(5, REGULATOR_SEKVENS, 10);

	/* 4. Set pump values */
	controlSignals.pump_A_mEpsilon[0] = pumpEpsilon1;
	controlSignals.pump_A_mEpsilon[1] = pumpEpsilon2;
	controlSignals.pump_B_mEpsilon[0] = pumpEpsilon1;
	controlSignals.pump_B_mEpsilon[1] = pumpEpsilon2;

	g_debug1_1 = pumpEpsilon1;
	g_debug1_2 = pumpEpsilon2;

	return controlSignals;
}

static float pumpRegulator(void) {

	const float sampelingTime = 0.01;
	const float proportionalConstant = 0.0;
	const float integralConstant = 0.00040 * 1.0;
	const float maxIntegrator = 50 / integralConstant;

	/* 1. Update error signals */
	float pumpPressureError = SPSGetPump1Pressure_mbar() - SPSGetPump2Pressure_mbar();
	integratedError = integratedError + pumpPressureError * sampelingTime;

	if (integratedError > maxIntegrator) {
		integratedError = maxIntegrator;
	}
	else if (integratedError < -maxIntegrator) {
		integratedError = - maxIntegrator;
	}

	/* 2. Calculate PI signal */
	float PISignal = (proportionalConstant * pumpPressureError) + (integralConstant * integratedError);

	/* 3. Return signal */

	//g_debug1_1 = pumpPressureError;
	//g_debug1_2 = integratedError;
	//g_debug1_3 = PISignal;

	return PISignal;
}


/* Local globals */
static uint8 msg_CAN_ALYZER_4[8] = {0};
static uint8 msg_CAN_ALYZER_2[8] = {0};
static int calculateSlipOffsetController(int motorNumber, transmControlState DriveSTATE, int periodicCallTime_ms) {

	static int k[6] = {0};

	/* Step 2 - Set k values depending on drive state or CAN */
	if (DriveSTATE == REGULAOR_SECOUNDARY) {
		k[motorNumber] = 14;
	}
	else if (DriveSTATE == REGULATOR_SEKVENS) {
		k[motorNumber] = 2.6;
	}
	else if (msg_CAN_ALYZER_4[0] != 0) {
		k[0] = msg_CAN_ALYZER_4[0] / 10;
		k[1] = msg_CAN_ALYZER_4[1] / 10;
		k[2] = msg_CAN_ALYZER_4[2] / 10;
		k[3] = msg_CAN_ALYZER_4[3] / 10;
		k[4] = msg_CAN_ALYZER_4[4] / 10;
		k[5] = msg_CAN_ALYZER_4[5] / 10;
	}

	/* Step 3 -  Tune lowpass filter constants depending on avrage RPM*/
	/* low pass filter Sliping stuff */
	static float f_cutoff_ns;
	static float Tf_S_ns;
	static float alpha_S_ns;

	if (WMSGetAvrageRPMForWheels() > 500) {
		f_cutoff_ns = 0.02;
	} else {
		f_cutoff_ns = 0.10;
	}

	Tf_S_ns = 1 / (2 * M_PI * f_cutoff_ns);
	alpha_S_ns = Tf_S_ns / (Tf_S_ns + (float)periodicCallTime_ms / 1000);

	/* Step 4 - Calculate slip offset, and lowpass filter this badboj */
	/* Slip */
	static int slip[6] 			= {0};
	static int slip_old_lp[6] 	= {0};
	static int slip_lp[6] 		= {0};

	slip[motorNumber] = k[motorNumber] * (WMSGetRPMForWheel(motorNumber) - WMSGetAvrageRPMForWheels());
/*
		g_debug1_1 = slip[0];
		g_debug1_2 = slip[1];
		g_debug1_3 = slip[2];
		g_debug1_4 = slip[3];
		g_debug2_1 = slip[4];
		g_debug2_2 = slip[5];

*/
	//slip[motorNumber] = saturateAnInt(slip[motorNumber], 1000, 1000, 0, 0);
	slip_old_lp[motorNumber] = slip_lp[motorNumber];
	slip_lp[motorNumber] = alpha_S_ns * slip_old_lp[motorNumber] + (1 - alpha_S_ns) * slip[motorNumber];

	/* Step 5 - Substract the slip */

	return (int)slip_lp[motorNumber];
}


void TCSSendMotorPWNOnCAN(bool buttonCANSendState) {
	if (buttonCANSendState == TRUE && msg_CAN_ALYZER_2[0] > 0) {
		/*
		Motor_1_PWM = msg_CAN_ALYZER_2[0] * 3;
		Motor_2_PWM = msg_CAN_ALYZER_2[1] * 3;
		Motor_3_PWM = msg_CAN_ALYZER_2[2] * 3;
		Motor_4_PWM = msg_CAN_ALYZER_2[3] * 3;
		Motor_5_PWM = msg_CAN_ALYZER_2[4] * 3;
		Motor_6_PWM = msg_CAN_ALYZER_2[5] * 3;
		 */
	}
	/*! fixme eh add CAN send stupid */
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

