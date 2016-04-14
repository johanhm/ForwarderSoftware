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
static void sendSensorDataOnCAN(void);
//static void sendSensorDataOnCAN_1ms(void);
static void checkMachineStateAndActuate(void);
static void joystickControl(int wheelFR, int wheelFL, int wheelMR, int wheelML, int wheelBR, int wheelBL);
static void activeDampeningControl(int timeSinceActivated_ms);
static void buttonHoldControl(int wheelFR, int wheelFL, int wheelMR, int wheelML, int wheelBR, int wheelBL);
static float getBootupAngle(float startingAngle, float endAngle, float maxTime, int currentTime_ms);

/* Start of program */
void sys_main(void) {

	// CAN channels configuration
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
			databoxNrExipadJoystrick
	);
	ADCFGConfigureParameterSettingsFromCAN(CAN_1,
			3,
			4,
			7,
			8
	);

	can_init(CAN_1, 1000000);
	can_init(CAN_2, 500000);
	can_init(CAN_3, 250000);

	IMUInit();


	// Initialize RC/SRC.
	sys_init("SMS", "RC30-00D6"); // RC28-14/30
	emcy_disableInput(EMCY_DISABLE_KEY_DU32, ~EMCY_DISABLE_KEY_DU32);

	// Configure analoge sensors.
	PAPRConfigurePressureSensorsVoltageInput();
	PAPOSConfigurePositionSensorsVoltageInput();
	PAAConfigurePendelumArmOutputs();

	sys_registerTask( &readSensorsTask_10ms,
			READ_SENSORS_PRIO,
			READ_SENSORS_TASK_TIME_MS,
			READ_SENSORS_OFFSET_MS,
			0
	);
	/*
	sys_registerTask( &sendSensorDataOnCAN_1ms,
			4,
			1,
			0,
			0
	);
	 */
	sys_initTC(0, READ_SENSORS_TASK_TIME_MS);

}

static void readSensorsTask_10ms(void) {
	/* System checkpoint and enable sensor voltage */
	sys_triggerTC(0);
	sys_setVP(VP_1, ON);
	sys_setVP(VP_2, ON);

	/* Enable actuation of pendelum arms and set that the arms should respect limits */
	PAASetPendelumArmActuateState(TRUE);
	PAASetPendelumArmPosLimitState(FALSE);

	/* Uppdate presure and recalculate force data */
	int imuError 	  = IMUUppdateFilterdAngelsWithComplementaryFilter();
	int posError  	  = PAPOSUppdatePosSensorsDataWithSampleTime( READ_SENSORS_TASK_TIME_MS );
	int pressureError = PAPRUppdatePressureDataWithSampleTime( READ_SENSORS_TASK_TIME_MS );

	bool sensorError = (imuError == TRUE) || (posError == TRUE) || (pressureError == TRUE);
	if (sensorError == TRUE) {
		/*!
		 * do some sort of logic with disabeling PAAD.
		 * add comment for fun
		 * new commentfor fun
		 */
	}

	/* Get new valus for force calculations and update force data */
	int pressureData_Bar[INDEX_SIZE_PRESSURESENS] = {0};
	int posData_mm[SUM_WHEELS] = {0};
	PAPRGetPressureDataArray_bar(pressureData_Bar);
	PAPOSGetPosDataArray(posData_mm);
	PAFUppdateForceOnWheelsDataUsing(pressureData_Bar, posData_mm);

	/* Check the machine state and actuate accordingly */
	checkMachineStateAndActuate();

	/* Send all the sensor data on CAN */
	sendSensorDataOnCAN();
}

static void checkMachineStateAndActuate(void) {
	/*! Fixme
	 * Absolutli need to add a timeout for the excipad message, if timeout set reference to zero
	 */
	exipadButton machineState = EXPGetLastPressedButtonWithToggle();
	static exipadButton machineStateOld = NONE;
	static int timeSinceChangedState_ms = 0;

	bool newMachineStateHasBeenSet = machineState != machineStateOld;
	if (newMachineStateHasBeenSet) {
		timeSinceChangedState_ms = 0;
		/*!
		 * Set output for all wheels to zero.
		 */
		joystickControl(OFF, OFF, OFF, OFF, OFF, OFF); /* temporary set all to zero */
	}

	switch (machineState) {
	case NONE: /* All off */
		joystickControl(OFF, OFF, OFF, OFF, OFF, OFF);
		break;
	case BUTTON_1: /* Front Left */
		joystickControl(OFF, ON, OFF, OFF, OFF, OFF);
		break;
	case BUTTON_2: /* Passive dampening activated */
		PAASetPassiveDampeningState(TRUE);
		break;
	case BUTTON_3: /* Front Right */
		joystickControl(ON, OFF, OFF, OFF, OFF, OFF);
		break;
	case BUTTON_4: /* Mid Left */
		joystickControl(OFF, OFF, OFF, ON, OFF, OFF);
		break;
	case BUTTON_5: /* Passive dampening deactivated */
		PAASetPassiveDampeningState(FALSE);
		break;
	case BUTTON_6: /* Mid Right */
		joystickControl(OFF, OFF, ON, OFF, OFF, OFF);
		break;
	case BUTTON_7: /* Back Left */
		joystickControl(OFF, OFF, OFF, OFF, OFF, ON);
		break;
	case BUTTON_8: /* Nothing */
		break;
	case BUTTON_9: /* Back Right */
		joystickControl(OFF, OFF, OFF, OFF, ON, OFF);
		break;
	case BUTTON_10: /* Nothing */
		break;
	case BUTTON_11: /* Nothing */
		break;
	case BUTTON_12: /* Nothing */
		break;
	case BUTTON_13: /* Nothing */
		break;
	case BUTTON_14: /* Nothing */
		break;
	case BUTTON_15: /* Nothing */
		break;
	case BUTTON_16: /* Tilt Phi */
		joystickControl(UPP, DOWN, UPP, DOWN, UPP, DOWN);
		break;
	case BUTTON_17: /* Tilt Theta */
		joystickControl(UPP, UPP, OFF, OFF, DOWN, DOWN);
		break;
	case BUTTON_18: /* ADC Control */
		timeSinceChangedState_ms = timeSinceChangedState_ms + (READ_SENSORS_TASK_TIME_MS);
		activeDampeningControl(
				timeSinceChangedState_ms
		);
		break;
	case BUTTON_19: /* All Upp */
		buttonHoldControl(UPP, UPP, UPP, UPP, UPP, UPP);
		break;
	case BUTTON_20:
		/* Nothing */
		break;
	case BUTTON_21: /* Front Down */
		buttonHoldControl(DOWN, DOWN, DOWN, DOWN, DOWN, DOWN);
		break;
	}
	machineStateOld = machineState;
}

static void activeDampeningControl(int timeSinceActivated_ms) {

	ADCFGNivPIDAndForcePID(TRUE);

	//g_debug1 = timeSinceActivated_ms;
	//g_debug2 = PAPOSGetBeta() * 1000;
	//g_debug3 = getBootupAngle(-4.2f, 9.6f, 5, timeSinceActivated_ms) * 1000;


/*
	if (timeSinceActivated_ms < 5) {
		//float thetaRef = 0.0; //get boot angle theta
		//float phiRef = 0.0; //get boot angle phi
		//ADFGSetReferencePhiAndTheta();
		//ADCFGNivPIDAndForcePID(TRUE);
	} else {
		//ADCFGNivPIDAndForcePID(TRUE);
	}
*/

	//ADCFGNivPIDSetup(TRUE);
	//ADCFGForceControllerTest(TRUE);

	/* Temporary commeted */
	//ADCFGNivPIDAndForcePID(TRUE);
	/* end temp comment */

	//ADCFGManualTestingPlayground(FALSE);
	//ADCFGNivPIDAndSkyhookSetup(FALSE);
	//ADCFGPesudoForcePIDSkyhookSlidingMode(FALSE);
	//ADCFGPesudoForceWithOptimalForceRefPIDSkyhookSlidingMode(FALSE);
}

static float getBootupAngle(float startingAngle, float endAngle, float maxTime, int currentTime_ms) {

	float timeInSec = (float)currentTime_ms / 1000;
	/* S curve logistic function: https://en.wikipedia.org/wiki/Logistic_function */
	float angleReference = startingAngle - ( (startingAngle - endAngle) / (1 + exp(-(9.5 / maxTime) * (timeInSec - (maxTime / 2))) ) );
	return angleReference;

}


static void joystickControl(int wheelFR, int wheelFL, int wheelMR, int wheelML, int wheelBR, int wheelBL) {

	int joystrickReferenceCurrent = EXPGetJoystickScaledValue();
	PAASetReferenceForWheelWithUnit(FR, CURRENT_MA, wheelFR * joystrickReferenceCurrent);
	PAASetReferenceForWheelWithUnit(FL, CURRENT_MA, wheelFL * joystrickReferenceCurrent);
	PAASetReferenceForWheelWithUnit(MR, CURRENT_MA, wheelMR * joystrickReferenceCurrent);
	PAASetReferenceForWheelWithUnit(ML, CURRENT_MA, wheelML * joystrickReferenceCurrent);
	PAASetReferenceForWheelWithUnit(BR, CURRENT_MA, wheelBR * joystrickReferenceCurrent);
	PAASetReferenceForWheelWithUnit(BL, CURRENT_MA, wheelBL * joystrickReferenceCurrent);

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
		EXPSetLastPressedButtonToNone();
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
	// Send data on CAN
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
}

/*
static void sendSensorDataOnCAN_1ms(void) {
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
}
 */
