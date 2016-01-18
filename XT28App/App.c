#include "api_lib_basic.h"
//#include "XT28_api.h"
#include "IMU.h"
#include "PendelumArmPressure.h"
#include "PendelumArmPosition.h"
#include "XT28CANSupport.h"
#include "PendelumArmActuate.h"
#include "Excipad.h"
#include "XT28HardwareConstants.h"

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
static void checkMachineStateAndActuate(void);
static void joystickControl(int wheelFR, int wheelFL, int wheelMR, int wheelML, int wheelBR, int wheelBL);
static void activeDampeningControl(void);
static void buttonHoldControl(int wheelFR, int wheelFL, int wheelMR, int wheelML, int wheelBR, int wheelBL);

//Start of program
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
	EXPConfigureExcipad(CAN_1,
			databoxNrExipadButtons,
			databoxNrExipadJoystrick
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

	sys_registerTask( readSensorsTask_10ms,
			READ_SENSORS_PRIO,
			READ_SENSORS_TASK_TIME_MS,
			READ_SENSORS_OFFSET_MS,
			0
	);
	sys_initTC(0, READ_SENSORS_TASK_TIME_MS);

}

static void readSensorsTask_10ms(void) {
	sys_triggerTC(0);
	sys_setVP(VP_1, ON); // This could maby be intergrated into PAActuate module with logic that check the return values.
	sys_setVP(VP_2, ON);
	PAASetPendelumArmActuateState(TRUE);
	PAASetPendelumArmPosLimitState(TRUE);

	// Uppdate presure and recalculate force data
	PAPOSUppdatePosSensorsDataWithSampleTime(READ_SENSORS_TASK_TIME_MS);
	PAPRUppdatePressureData();
	PAPRUppdateForceOnWheelsData();

	checkMachineStateAndActuate();
	sendSensorDataOnCAN();
}

static void checkMachineStateAndActuate(void) {
	exipadButton machineState = EXPGetLastPressedButtonWithToggle();
	switch (machineState) {
	case NONE: /* All off */
		joystickControl(OFF, OFF, OFF, OFF, OFF, OFF);
		break;
	case BUTTON_1: /* Front Right */
		joystickControl(ON, OFF, OFF, OFF, OFF, OFF);
		PAASetPassiveDampeningState(TRUE);
		break;
	case BUTTON_3: /* Front Left */
		joystickControl(OFF, ON, OFF, OFF, OFF, OFF);
		PAASetPassiveDampeningState(FALSE);
		break;
	case BUTTON_4: /* Mid Right */
		joystickControl(OFF, OFF, ON, OFF, OFF, OFF);
		break;
	case BUTTON_6: /* Mid Left */
		joystickControl(OFF, OFF, OFF, ON, OFF, OFF);
		break;
	case BUTTON_7: /* Back Right */
		joystickControl(OFF, OFF, OFF, OFF, ON, OFF);
		break;
	case BUTTON_9: /* Back Left */
		joystickControl(OFF, OFF, OFF, OFF, OFF, ON);
		break;
	case BUTTON_16: /* Tilt Phi */
		joystickControl(UPP, DOWN, UPP, DOWN, UPP, DOWN);
		break;
	case BUTTON_17: /* Tilt Theta */
		joystickControl(UPP, UPP, OFF, OFF, DOWN, DOWN);
		break;
	case BUTTON_18: /* ADC Control */
		activeDampeningControl();
		break;
	case BUTTON_19: /* All Upp */
		buttonHoldControl(UPP, UPP, UPP, UPP, UPP, UPP);
		break;
	case BUTTON_20: /* Front Down */
		buttonHoldControl(DOWN, DOWN, DOWN, DOWN, DOWN, DOWN);
		break;
	}
}

static void joystickControl(int wheelFR, int wheelFL, int wheelMR, int wheelML, int wheelBR, int wheelBL) {
	int joystrickReferenceCurrent = EXPGetJoystickScaledValue();
	PAASetReferenceCurrentForWheel(FR, wheelFR * joystrickReferenceCurrent);
	PAASetReferenceCurrentForWheel(FL, wheelFL * joystrickReferenceCurrent);
	PAASetReferenceCurrentForWheel(MR, wheelMR * joystrickReferenceCurrent);
	PAASetReferenceCurrentForWheel(ML, wheelML * joystrickReferenceCurrent);
	PAASetReferenceCurrentForWheel(BR, wheelBR * joystrickReferenceCurrent);
	PAASetReferenceCurrentForWheel(BL, wheelBL * joystrickReferenceCurrent);

	PAAActuatePendelumArms();
}

static void activeDampeningControl(void) {
	int wheel = 0;
	for (wheel = 0; wheel < 6; wheel++) {
		PAASetReferenceCurrentForWheel(wheel,
				0//ADCGetReferenceCurForWheel(wheel)
		);
	}
	//PAAActuatePendelumArms();
}

static void buttonHoldControl(int wheelFR, int wheelFL, int wheelMR, int wheelML, int wheelBR, int wheelBL) {
	static float rampCurrentReference = 0;
	float growth = 0.1;
	rampCurrentReference = rampCurrentReference + growth;
	int curSaturation = 50;
	if (rampCurrentReference > curSaturation) {
		rampCurrentReference = curSaturation;
	}
	if (EXPGetUserIsHoldingAButtonDown() == FALSE) {
		rampCurrentReference = 0;
		EXPSetLastPressedButtonToNone();
	}
	int rampRef = (int)rampCurrentReference;
	PAASetReferenceCurrentForWheel(FR, wheelFR * rampRef);
	PAASetReferenceCurrentForWheel(FL, wheelFL * rampRef);
	PAASetReferenceCurrentForWheel(MR, wheelMR * rampRef);
	PAASetReferenceCurrentForWheel(ML, wheelML * rampRef);
	PAASetReferenceCurrentForWheel(BR, wheelBR * rampRef);
	PAASetReferenceCurrentForWheel(BL, wheelBL * rampRef);

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
	PAPRSendCylinderForceOnCAN(CAN_1,
			CAN_ID_SENSOR_INFO_SMS_8,
			CAN_ID_SENSOR_INFO_SMS_9,
			CAN_ID_SENSOR_INFO_SMS_10
	);
	PAPRSendCylinderLoadForceOnCAN(CAN_1,
			CAN_ID_SENSOR_INFO_SMS_12,
			CAN_ID_SENSOR_INFO_SMS_13
	);
	PAPRSendVerticalWheelForceOnCAN(CAN_1,
			CAN_ID_SENSOR_INFO_SMS_14,
			CAN_ID_SENSOR_INFO_SMS_15
	);
	PAPRSendMassCenterLocationOnCAN(CAN_1,
			0x18FF1001
	);
	PAPRSendOptimalForceRefOnCAN(CAN_1,
			0x18FF1002,
			0x18FF1003
	);
	PAPRSendForceErrorPercentageOnCAN(CAN_1,
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
}
