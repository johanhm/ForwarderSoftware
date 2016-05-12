#include "api_lib_basic.h"
#include <XT28_api.h>

// Defines
#define READ_SENSORS_PRIO 			(5)
#define READ_SENSORS_TASK_TIME_MS 	(10)
#define READ_SENSORS_OFFSET_MS 		(0)

#define UPP 	(-1)
#define DOWN 	(1)

// Prototypes
void sys_main(void);
static void readSensorsTask_10ms(void);
static void checkSensorForErrors_50ms(void);

static void sendSensorDataOnCAN(void);
static void checkMachineStateAndActuate(void);
static void joystickControl(chairPosition chairPos, int wheelFR, int wheelFL, int wheelMR, int wheelML, int wheelBR, int wheelBL);
static void joystickTiltXY(chairPosition chairPos);
static void activeDampeningControl(float heightReferenceOffset);
static void buttonHoldControl(int wheelFR, int wheelFL, int wheelMR, int wheelML, int wheelBR, int wheelBL);
static float getBootupReference(float startingReference, float endReference, float maxTime_ms, int currentTime_ms);
static void setADRampToTrue(void);

/* Start of program */
void sys_main(void) {

	/* Sensor supply */
	sys_setVSS(VSS_2, OFF);

	/* CAN channels configuration */
	CANConfigureXT28CANChannels();

	int databoxNrGyro = 1;
	int databoxNrAcc = 2;
	IMUConfigureInertialMeasurementUnit(CAN_2,
			databoxNrGyro,
			databoxNrAcc
	);

	int databoxNrExipadButtons = 3;
	int databoxNrExipadJoystrick = 4;
	EXPConfigureExcipad(CAN_3,
			databoxNrExipadButtons,
			databoxNrExipadJoystrick,
			5
	);
	ADCFGConfigureParameterSettingsFromCAN(CAN_1,
			3,
			4,
			7,
			8
	);

	DisplayConfigureCAN(CAN_4,
			1
	);


	can_init(CAN_1, 1000000);
	can_init(CAN_2, 500000);
	can_init(CAN_3, 250000);
	can_init(CAN_4, 250000);

	IMUInit();

	/* Initialize RC/SRC */
	sys_init("SMS", "RC30-00D6"); // RC28-14/30
	emcy_disableInput(EMCY_DISABLE_KEY_DU32, ~EMCY_DISABLE_KEY_DU32);

	/* Configure analoge sensors */
	PAPRConfigurePressureSensorsVoltageInput();
	PAPOSConfigurePositionSensorsVoltageInput();
	PAAConfigurePendelumArmOutputs();

	sys_registerTask( &readSensorsTask_10ms,
			READ_SENSORS_PRIO,
			READ_SENSORS_TASK_TIME_MS,
			READ_SENSORS_OFFSET_MS,
			0
	);
	sys_registerTask( &checkSensorForErrors_50ms,
			4,
			50,
			5,
			0
	);
	sys_initTC(0, READ_SENSORS_TASK_TIME_MS);

	/* Enable actuation of pendelum arms and set that the arms should respect limits */
	PAASetPendelumArmActuateState(TRUE);
	PAASetPendelumArmPosLimitState(TRUE);

}

static void readSensorsTask_10ms(void) {
	/* 1. System checkpoint and enable sensor voltage */
	sys_triggerTC(0);
	sys_setVP(VP_1, ON);
	sys_setVP(VP_2, ON); /* fixme check if this power outpus is used, if not remove this line */

	/* 2.1 Uppdate presure and recalculate force data */
	IMUUppdateFilterdAngelsWithComplementaryFilter();
	PAPOSUppdatePosSensorsDataWithSampleTime( READ_SENSORS_TASK_TIME_MS );
	PAPRUppdatePressureDataWithSampleTime( READ_SENSORS_TASK_TIME_MS );

	/* 2.2 Get new valus for force calculations and update force data */
	int pressureData_Bar[INDEX_SIZE_PRESSURESENS] = {0};
	int posData_mm[SUM_WHEELS] = {0};
	PAPRGetPressureDataArray_bar(pressureData_Bar);
	PAPOSGetPosDataArray(posData_mm);
	PAFUppdateForceOnWheelsDataUsing(pressureData_Bar, posData_mm);

	/* 4. Check the machine state and actuate accordingly */
	checkMachineStateAndActuate();

	/* 5. Send all the sensor data on CAN */
	sendSensorDataOnCAN();

	/* testing */
	static float testOffset = 0;
	if (PAPOSIsStrokeLessThen(50) == TRUE) {
		testOffset = testOffset + 0.5;
	} else {
		testOffset = testOffset - 0.5;
	}
	if (testOffset < 0) {
		testOffset = 0;
	}
	//g_debug1 = testOffset;
	//g_debug2 = DisplayGetHandBreakState();

	/* end test */
}

static void checkSensorForErrors_50ms(void) {

	static bool sensorAlertState = FALSE;

	/* Sensor error and saturation check */
	bool exipadError = EXPCheckTimeout(50, 180);
	bool imuError = IMUCheckTimeout(0, 40);
	bool posError = PAPOSCheckPosSensorsForErrors();
	bool pressureError = PAPRCheckPressureSensorForErrors();
	bool sensorError = (imuError == TRUE) || (posError == TRUE) || (pressureError == TRUE) || (exipadError == TRUE);
	if (sensorError == TRUE ) {
		sensorAlertState = TRUE;
		DisplaySetSensorAlertStateTo(sensorAlertState);
	} else {
		sensorAlertState = FALSE;
		DisplaySetSensorAlertStateTo(sensorAlertState);
	}
	if (exipadError == TRUE) {
		EXPSetButtonStateTo(NONE);
	}

}

static void checkMachineStateAndActuate(void) {
	/*! Fixme
	 * Absolutli need to add a timeout for the excipad message, if timeout set reference to zero
	 */

	static exipadButton machineStateOld = NONE;
	static float heightReferenceOffset = 0;

	/* Uppdate state */
	exipadButton machineState = EXPGetLastPressedButtonWithToggle();

	if (machineState == BUTTON_18) {
		DisplaySetADStateTo(TRUE);
	} else {
		DisplaySetADStateTo(FALSE);
	}

	/* Switch on state */
	switch (machineState) {
	case NONE: /* All off */
		PAASetPAReferenceAndActuateToZero();
		break;
	case BUTTON_1: /* Front Left */
		joystickControl(DisplayGetChairPosition(),
				OFF, ON, OFF, OFF, OFF, OFF
		);
		break;
	case BUTTON_2: /* Nothing */

	{
		out(OUT_19_DOH, TRUE);
		out(OUT_20_DOH, TRUE);
		out(OUT_21_DOH, FALSE);
		out(OUT_22_DOH, FALSE);
		out(OUT_23_DOH, FALSE);
		out(OUT_24_DOH, FALSE);
	}

	EXPSetButtonStateTo(NONE);
	break;
	case BUTTON_3: /* Front Right */
		joystickControl(DisplayGetChairPosition(),
				ON, OFF, OFF, OFF, OFF, OFF
		);
		break;
	case BUTTON_4: /* Mid Left */
		joystickControl(DisplayGetChairPosition(),
				OFF, OFF, OFF, ON, OFF, OFF
		);
		break;
	case BUTTON_5: /* Nothing */

	{
		out(OUT_19_DOH, TRUE);
		out(OUT_20_DOH, TRUE);
		out(OUT_21_DOH, FALSE);
		out(OUT_22_DOH, FALSE);
		out(OUT_23_DOH, TRUE);
		out(OUT_24_DOH, TRUE);
	}

	EXPSetButtonStateTo(NONE);
	break;
	case BUTTON_6: /* Mid Right */
		joystickControl(DisplayGetChairPosition(),
				OFF, OFF, ON, OFF, OFF, OFF
		);
		break;
	case BUTTON_7: /* Back Left */
		joystickControl(DisplayGetChairPosition(),
				OFF, OFF, OFF, OFF, OFF, ON
		);
		break;
	case BUTTON_8: /* Nothing */
		ADCSetControlParametersWithCAN();
		g_debug1 = 4;
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_9: /* Back Right */
		joystickControl(
				DisplayGetChairPosition(),
				OFF, OFF, OFF, OFF, ON, OFF
		);
		break;
	case BUTTON_10: /* AD calm settings */
		ADCFGNivPIDAndForcePIDCfg(2, 100, 40, 0);
		g_debug1 = 1;
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_11: /* AD best settings so far */
		ADCFGNivPIDAndForcePIDCfg(10, 300, 80, 100);
		g_debug1 = 2;
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_12: /* AD update latest CAN settings */
		ADCFGNivPIDAndForcePIDCfg(11, 320, 100, 200);
		g_debug1 = 3;
		//ADCSetControlParametersWithCAN();
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_13: /* Incease height reference */
		if (machineStateOld == BUTTON_18) {
			EXPSetButtonStateTo(BUTTON_18);
			checkMachineStateAndActuate();
		} else {
			EXPSetButtonStateTo(NONE);
		}
		break;
	case BUTTON_14: /* Lower height reference */
		if (machineStateOld == BUTTON_18) {
			EXPSetButtonStateTo(BUTTON_18);
			checkMachineStateAndActuate();
		} else {
			EXPSetButtonStateTo(NONE);
		}
		break;
	case BUTTON_15: /* Nothing */
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_16: /* Tilt Phi and Theta */
		joystickTiltXY( DisplayGetChairPosition() );
		break;
	case BUTTON_17: { /* Passive on/off */
		static bool passiveState = FALSE;
		passiveState = !passiveState;

		PAASetPassiveDampeningState(passiveState);
		DisplaySetPDStateTo(passiveState);
		EXPSetButtonStateTo(NONE);

		break;
	}
	case BUTTON_18: { /* ADC Control */

		/* Startup phase check */
		bool shouldStartRampupPhase = EXPGetCurrentlyPressedButton() == BUTTON_18;
		if (shouldStartRampupPhase == TRUE) {
			setADRampToTrue();
		}

		/* Height reference user offset check */
		const float heightGrowth = 0.5;
		const float heightOffsetMinimum = -150.0;
		const float heightOffsetMaximum = 100.0;

		bool shouldDecreaseHeightReference = (EXPGetCurrentlyPressedButton() == BUTTON_13);
		if (shouldDecreaseHeightReference == TRUE) {
			heightReferenceOffset = heightReferenceOffset - heightGrowth;
			if (heightReferenceOffset < heightOffsetMinimum) {
				heightReferenceOffset = heightOffsetMinimum;
			}
		}
		bool shouldLowerHeightReference = (EXPGetCurrentlyPressedButton() == BUTTON_14);
		if (shouldLowerHeightReference == TRUE) {
			heightReferenceOffset = heightReferenceOffset + heightGrowth;
			if (heightReferenceOffset > heightOffsetMaximum) {
				heightReferenceOffset = heightOffsetMaximum;
			}
		}

		/* Sensor error and saturation check */
		bool imuError = IMUCheckTimeout(10, 40);
		bool posError = PAPOSCheckPosSensorsForErrors();
		bool pressureError = PAPRCheckPressureSensorForErrors();
		bool sensorError = (imuError == TRUE) || (posError == TRUE) || (pressureError == TRUE);
		if (sensorError == TRUE) {
			EXPSetButtonStateTo(NONE);
			break;
		}
		if (DisplayGetHandBreakState() == TRUE) {
			EXPSetButtonStateTo(NONE);
			break;
		}

		/* Do active dampening */
		bool sensorsFiltersHaveSaturated = (sys_getTime_us() > 5000000);
		if (sensorsFiltersHaveSaturated == TRUE) {
			activeDampeningControl(heightReferenceOffset);
		}
		break;
	}
	case BUTTON_19: /* All Upp */
		buttonHoldControl(UPP, UPP, UPP, UPP, UPP, UPP);
		break;
	case BUTTON_20: /* Nothing */
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_21: /* Front Down */
		buttonHoldControl(DOWN, DOWN, DOWN, DOWN, DOWN, DOWN);
		break;
	}
	machineStateOld = machineState;
}

bool rampUp = TRUE;
static void setADRampToTrue(void) {
	rampUp = TRUE;
}

static void activeDampeningControl(float heightReferenceOffset) {

	/* FIXME This function should also ramp up the force constant.
	 * Think about the constraints we want on the force functionality
	 *  so its implemented in a good way */

	const  float MaximumTime_ms = 5000;

	static float startValueHeight_mm 	    = 0;
	static float startValuePhi_deg 		    = 0;
	static float startValueTheta_deg 	    = 0;
	const float  startValueForceGainPercent = 0;

	static float endRefHeight_mm 		  = 250;
	static float endRefPhi_deg 			  = 0;
	static float endRefTheta_deg 		  = -1; /* -1 becouse the IMU is mounted wrong by -1.25 deg */
	static float endRefThetaStatic_deg 	  = 0;
	const float  endValueForceGainPercent = 1;

	static int timeSinceActivated_ms = 0;
	timeSinceActivated_ms = timeSinceActivated_ms + 10;

	if (rampUp == TRUE) { /* Set start and end points of logistic curve */

		rampUp = FALSE;
		timeSinceActivated_ms = 0;

		startValueHeight_mm = PAPOSGetAvrageHeightOfForwarder();
		startValuePhi_deg 	= IMUGetPhi();
		startValueTheta_deg = IMUGetTheta();

		endRefHeight_mm 		= ADCFGetCANHeightRef() + heightReferenceOffset;
		endRefPhi_deg 			= ADCFGetCANPhiRef();
		endRefThetaStatic_deg 	= ADCGetCANThetaRef();
		endRefTheta_deg 		= IMUGetTheta() - PAPOSGetBeta() + endRefThetaStatic_deg; /* Temp while evauating this method of beta; Using beta as reference then the error input to the control function is -beta only. Theta takes it self out so the error is not dependent on theta */
	}
	else if (timeSinceActivated_ms < MaximumTime_ms) { /* Ramping up following the logistic curve */
		endRefHeight_mm = ADCFGetCANHeightRef() + heightReferenceOffset;
		endRefTheta_deg = IMUGetTheta() - PAPOSGetBeta() + endRefThetaStatic_deg;

		float startupHeightRef = getBootupReference(startValueHeight_mm, endRefHeight_mm, MaximumTime_ms, timeSinceActivated_ms);
		float startupPhiRef = getBootupReference(startValuePhi_deg, endRefPhi_deg, MaximumTime_ms, timeSinceActivated_ms);
		float startupThetaRef = getBootupReference(startValueTheta_deg, endRefTheta_deg, MaximumTime_ms, timeSinceActivated_ms);
		float startupForceGain = getBootupReference( startValueForceGainPercent, endValueForceGainPercent, MaximumTime_ms, timeSinceActivated_ms);

		ADCFGNivPIDAndForcePID(startupHeightRef, startupPhiRef, startupThetaRef, startupForceGain);
	} else { /* Normal mode */
		endRefTheta_deg = IMUGetTheta() - PAPOSGetBeta() + endRefThetaStatic_deg;
		endRefHeight_mm = ADCFGetCANHeightRef() + heightReferenceOffset;
		ADCFGNivPIDAndForcePID(endRefHeight_mm, endRefPhi_deg, endRefTheta_deg, 1);
	}

	DisplaySetHeightReference(endRefHeight_mm);

}

static float getBootupReference(float startingReference, float endReference, float maxTime_ms, int currentTime_ms) {

	maxTime_ms = maxTime_ms / 1000;
	float timeInSec = (float)currentTime_ms / 1000;
	/* S curve logistic function: https://en.wikipedia.org/wiki/Logistic_function */
	float calculatedStartupReference = startingReference - ( (startingReference - endReference) / (1 + exp(-(9.5 / maxTime_ms) * (timeInSec - (maxTime_ms / 2))) ) );
	return calculatedStartupReference;

}

static void joystickControl(chairPosition chairPos, int wheelFR, int wheelFL, int wheelMR, int wheelML, int wheelBR, int wheelBL) {

	int joystrickReferenceCurrent = EXPGetJoystickScaledValueUppDown();

	if (chairPos == CHAIR_IS_FRONT) {
		PAASetReferenceForWheelWithUnit(FR, CURRENT_MA, wheelFR * joystrickReferenceCurrent);
		PAASetReferenceForWheelWithUnit(FL, CURRENT_MA, wheelFL * joystrickReferenceCurrent);
		PAASetReferenceForWheelWithUnit(MR, CURRENT_MA, wheelMR * joystrickReferenceCurrent);
		PAASetReferenceForWheelWithUnit(ML, CURRENT_MA, wheelML * joystrickReferenceCurrent);
		PAASetReferenceForWheelWithUnit(BR, CURRENT_MA, wheelBR * joystrickReferenceCurrent);
		PAASetReferenceForWheelWithUnit(BL, CURRENT_MA, wheelBL * joystrickReferenceCurrent);
	}
	else if (chairPos == CHAIR_IS_BACK) {
		PAASetReferenceForWheelWithUnit(FR, CURRENT_MA, wheelBL * joystrickReferenceCurrent);
		PAASetReferenceForWheelWithUnit(FL, CURRENT_MA, wheelBR * joystrickReferenceCurrent);
		PAASetReferenceForWheelWithUnit(MR, CURRENT_MA, wheelML * joystrickReferenceCurrent);
		PAASetReferenceForWheelWithUnit(ML, CURRENT_MA, wheelMR * joystrickReferenceCurrent);
		PAASetReferenceForWheelWithUnit(BR, CURRENT_MA, wheelFL * joystrickReferenceCurrent);
		PAASetReferenceForWheelWithUnit(BL, CURRENT_MA, wheelFR * joystrickReferenceCurrent);
	}
	PAAActuatePendelumArms();
}

static void joystickTiltXY(chairPosition chairPos) {

	int joystickY = EXPGetJoystickScaledValueUppDown();
	int joystickX = EXPGetJoystickXScaledValueLeftRight();

	/* fixme refactor this and just pass a sign that change depending on char pos */
	if (chairPos == CHAIR_IS_FRONT) {
		PAASetReferenceForWheelWithUnit(FR, CURRENT_MA, ( joystickX  + joystickY) );
		PAASetReferenceForWheelWithUnit(FL, CURRENT_MA, (-joystickX  + joystickY) );
		PAASetReferenceForWheelWithUnit(MR, CURRENT_MA,  joystickX );
		PAASetReferenceForWheelWithUnit(ML, CURRENT_MA, -joystickX );
		PAASetReferenceForWheelWithUnit(BR, CURRENT_MA, ( joystickX - joystickY) );
		PAASetReferenceForWheelWithUnit(BL, CURRENT_MA, (-joystickX - joystickY) );
	}
	else if (chairPos == CHAIR_IS_BACK) {
		PAASetReferenceForWheelWithUnit(FR, CURRENT_MA, (-joystickX  - joystickY) );
		PAASetReferenceForWheelWithUnit(FL, CURRENT_MA, ( joystickX  - joystickY) );
		PAASetReferenceForWheelWithUnit(MR, CURRENT_MA,  -joystickX );
		PAASetReferenceForWheelWithUnit(ML, CURRENT_MA,   joystickX );
		PAASetReferenceForWheelWithUnit(BR, CURRENT_MA, (-joystickX + joystickY) );
		PAASetReferenceForWheelWithUnit(BL, CURRENT_MA, ( joystickX + joystickY) );
	}
	PAAActuatePendelumArms();
}


static void buttonHoldControl(int wheelFR, int wheelFL, int wheelMR, int wheelML, int wheelBR, int wheelBL) {

	static float rampCurrentReference = 0;
	float growth = 0.4;
	rampCurrentReference = rampCurrentReference + growth;
	int curSaturation = 80;
	if (rampCurrentReference > curSaturation) {
		rampCurrentReference = curSaturation;
	}
	if (EXPGetUserIsHoldingAButtonDown() == FALSE) {
		rampCurrentReference = 0;
		EXPSetButtonStateTo(NONE);
	}
	int rampRef = (int)rampCurrentReference;

	PAASetReferenceForWheelWithUnit(FR, CURRENT_MA, wheelFR * rampRef);
	PAASetReferenceForWheelWithUnit(FL, CURRENT_MA, wheelFL * rampRef);
	PAASetReferenceForWheelWithUnit(MR, CURRENT_MA, wheelMR * rampRef);
	PAASetReferenceForWheelWithUnit(ML, CURRENT_MA, wheelML * rampRef);
	PAASetReferenceForWheelWithUnit(BR, CURRENT_MA, wheelBR * rampRef);
	PAASetReferenceForWheelWithUnit(BL, CURRENT_MA, wheelBL * rampRef);

	PAAActuatePendelumArms();
}

static void sendSensorDataOnCAN(void) {
	/* Send data on CAN */
	CANSendSupplyVoltageOnCAN(CAN_1, 0x18FF1060);

	IMUSendIMURawValuesOnCAN( CAN_1,
			CAN_ID_GYRODATA_DATA,
			CAN_ID_ACCELOMETER_DATA
	);

	IMUSendFilterdAngleDataOnCAN(CAN_1, CAN_ID_SENSOR_INFO_SMS_16);

	PAPRSendPressureDataOnCAN(CAN_1,
			CAN_ID_SENSOR_INFO_SMS_1,
			CAN_ID_SENSOR_INFO_SMS_2,
			CAN_ID_SENSOR_INFO_SMS_3
	);

	PAPOSSendPosDataOnCAN(CAN_1,
			CAN_ID_SENSOR_INFO_SMS_4,
			CAN_ID_SENSOR_INFO_SMS_5
	);

	PAPOSSendVelDataOnCAN(CAN_1,
			CAN_ID_SENSOR_INFO_SMS_6,
			CAN_ID_SENSOR_INFO_SMS_7
	);

	PAFSendCylinderChamberForceOnCAN(CAN_1,
			CAN_ID_SENSOR_INFO_SMS_8,
			CAN_ID_SENSOR_INFO_SMS_9,
			CAN_ID_SENSOR_INFO_SMS_10
	);

	PAFSendCylinderLoadForceOnCAN(CAN_1,
			CAN_ID_SENSOR_INFO_SMS_12,
			CAN_ID_SENSOR_INFO_SMS_13
	);

	PAFSendVerticalWheelForceOnCAN(CAN_1,
			CAN_ID_SENSOR_INFO_SMS_14,
			CAN_ID_SENSOR_INFO_SMS_15
	);

	PAFSendMassCenterLocationOnCAN(CAN_1,
			0x18FF1001
	);

	PAFSendOptimalForceRefOnCAN(CAN_1,
			0x18FF1002,
			0x18FF1003
	);

	PAFSendForceErrorPercentageOnCAN(CAN_1,
			0x18FF1004,
			0x18FF1005
	);

	PAASendRealCurrentOnCAN(CAN_1,
			CAN_ID_REAL_CURRENT_FRONT,
			CAN_ID_REAL_CURRENT_MID,
			CAN_ID_REAL_CURRENT_BACK
	);

	PAASendReferenceCurrentOnCAN(CAN_1,
			CAN_ID_REFERENCE_CURRENT_FRONT,
			CAN_ID_REFERENCE_CURRENT_MID,
			CAN_ID_REFERENCE_CURRENT_BACK
	);

	CANSendDebuggMessage(CAN_1);

	DisplaySendLatestStatesOnCAN();
}
