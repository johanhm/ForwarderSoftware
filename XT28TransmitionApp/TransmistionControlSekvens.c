
#include "TransmistionControlSekvens.h"

static int calculateSlipOffsetController(int motorNumber, transmControlState DriveSTATE, int periodicCallTime_ms);
static float pumpRegulator(void);
static SRControlSignals sekvensRegulation(int pMilLowPassGasPedalSignal, int maxSpeed);
static SRControlSignals sekvensRegulationWithPumpRegulaton(int pMilLowPassGasPedalSignal, int maxSpeed);
static int saturateAnInt(int signal, int maxValue, int setMaxValue, int minValue, int setMinvalue);


static driveState TCSSetDriveState = NEUTRAL_DRIVE;
driveState TCSAttemtToSetDriveStateTo(driveState attemtedDriveState) {

	bool doorIsOpen_And_GasPedalIsNotPressed = (CSGetDoorState() == FALSE && GPSGetGassPedalFilterdAndScaled() < 150);
	if (doorIsOpen_And_GasPedalIsNotPressed) {
		TCSSetDriveState = NEUTRAL_DRIVE;
		return TCSSetDriveState;
	}

	/* Door is closed, gaspedal is not pressed and the break state is not active */
	TCSSetDriveState = attemtedDriveState;
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

void TCSActuate(int gasPedal, int maxSpeed) {

	/* 0. Check that the drive state is OK. */
	TCSAttemtToSetDriveStateTo(TCSSetDriveState);

	/* 1. Get control signals block from sequence regulator */
	SRControlSignals controlSignals = sekvensRegulation(gasPedal, maxSpeed);

	/* TEST */
	SRControlSignals testControlSignals = sekvensRegulationWithPumpRegulaton(gasPedal, maxSpeed);
	testControlSignals.pump_A_mEpsilon[0] = 0;
	/* END TEST */

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

	/* 2. Set induvidual control ställtal for all wheels */
	int wheel = 0;
	for (wheel = 0; wheel < 6; wheel++) {
		controlSignals.motor_mEpsilon[wheel] = motorEpsilon; // + noSlip(wheel);
	}

	/* test */
	g_debug1_1 = calculateSlipOffsetController(0, REGULATOR_SEKVENS, 10);
	g_debug1_2 = calculateSlipOffsetController(1, REGULATOR_SEKVENS, 10);
	g_debug1_3 = calculateSlipOffsetController(2, REGULATOR_SEKVENS, 10);
	g_debug1_4 = calculateSlipOffsetController(3, REGULATOR_SEKVENS, 10);
	g_debug2_1 = calculateSlipOffsetController(4, REGULATOR_SEKVENS, 10);
	g_debug3_2 = calculateSlipOffsetController(5, REGULATOR_SEKVENS, 10);
	/* end test */

	/* 3. Set pump values */
	controlSignals.pump_A_mEpsilon[0] = pumpEpsilon;
	controlSignals.pump_A_mEpsilon[1] = pumpEpsilon; // + pumpRegulator();
	controlSignals.pump_B_mEpsilon[0] = pumpEpsilon;
	controlSignals.pump_B_mEpsilon[1] = pumpEpsilon; // + pumpRegulator();

	return controlSignals;
}

static SRControlSignals sekvensRegulationWithPumpRegulaton(int pMilLowPassGasPedalSignal, int maxSpeed) {
	SRControlSignals controlSignals;

	static int pumpEpsilonA = 0;
	static int motorEpsilonA = 0;
	static int pumpEpsilonB = 0;
	static int motorEpsilonB = 0;

	const float niva = 3.0;
	int speedControlA;
	int speedControlB;
	maxSpeed = saturateAnInt(maxSpeed, 1000, 1000, 100, 100);

	/* 1. A side */
	speedControlA = pMilLowPassGasPedalSignal * maxSpeed / 1000;
	if (speedControlA > 1000 / niva) {
		pumpEpsilonA = 1000;
		motorEpsilonA = 1000 * (1000 / niva) / (speedControlA);
	} else {
		pumpEpsilonA = speedControlA * niva;
		motorEpsilonA = 1000;
	}

	/* 2. Same thing B side */
	speedControlB = speedControlA + pumpRegulator();   /* <-------- NEW REGULATOR YOLO */
	if (speedControlB > 1000 / niva) {
		pumpEpsilonB = 1000;
		motorEpsilonB = 1000 * (1000 / niva) / (speedControlB);
	} else {
		pumpEpsilonB = speedControlB * niva;
		motorEpsilonB = 1000;
	}

	/* 3 . Set induvidual control ställtal for all wheels */
	controlSignals.motor_mEpsilon[0] = motorEpsilonA; //+ calculateSlipOffsetController(0, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[1] = motorEpsilonB; //+ calculateSlipOffsetController(1, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[2] = motorEpsilonB; //+ calculateSlipOffsetController(2, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[3] = motorEpsilonA; //+ calculateSlipOffsetController(3, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[4] = motorEpsilonB; //+ calculateSlipOffsetController(4, REGULATOR_SEKVENS, 10);
	controlSignals.motor_mEpsilon[5] = motorEpsilonA; //+ calculateSlipOffsetController(5, REGULATOR_SEKVENS, 10);

	/* 4. Set pump values */
	controlSignals.pump_A_mEpsilon[0] = pumpEpsilonA;
	controlSignals.pump_A_mEpsilon[1] = pumpEpsilonA;
	controlSignals.pump_B_mEpsilon[0] = pumpEpsilonB;
	controlSignals.pump_B_mEpsilon[1] = pumpEpsilonB;

	return controlSignals;
}

static float pumpRegulator(void) {

	const float sampelingTime = 0.01;
	const float proportionalConstant = 0;
	const float integralConstant = 0.00040;
	static float integratedError = 0;

	/* 1. Update error signals */
	float pumpPressureError = SPSGetPump1Pressure_mbar() - SPSGetPump2Pressure_mbar();
	integratedError = integratedError + pumpPressureError * sampelingTime;

	const float maxIntegrator = 250000.0f;
	if (integratedError > maxIntegrator) {
		integratedError = maxIntegrator;
	}
	else if (integratedError < -maxIntegrator) {
		integratedError = - maxIntegrator;
	}

	/* 2. Calculate PI signal */
	float PISignal = (proportionalConstant * pumpPressureError) + (integralConstant * integratedError);

	/* 3. Return signal */
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
	slip_old_lp[motorNumber] = slip_lp[motorNumber];
	slip_lp[motorNumber] = alpha_S_ns * slip_old_lp[motorNumber] + (1 - alpha_S_ns) * slip[motorNumber];

	/* Step 5 - Substract the slip */
	return slip_lp[motorNumber];
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

