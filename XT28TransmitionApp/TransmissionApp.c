#include "api_lib_basic.h"

#include "AngleJointSensor.h"
#include "SystemPressureSensors.h"
#include "GasPedalSensor.h"
#include "CabinSensors.h"
#include "WheelMotorActuate.h"
#include "WheelMotorSensor.h"
#include "Excipad.h"
#include "AngleJointActuate.h"

#include "NinjaController.h"


#define CAN_ID_TX_SENSOR_INFO_DMS_1				0x18FE1010 	//Sensor data
#define CAN_ID_TX_SENSOR_INFO_DMS_2				0x18FE1011
#define CAN_ID_TX_SENSOR_INFO_DMS_3				0x18FE1012
#define CAN_ID_TX_SENSOR_INFO_DMS_4				0x18FE1020

#define DB_RX_INDEX_CAN_2					11
#define DB_RX_INDEX_CAN_3					10
#define DB_RX_INDEX_CAN_4					1

/* Private prototypes */
void sys_main(void);
static void mainTask_10ms(void);
static void setMachineState(void);


/* Start of program */
void sys_main(void) {

	/* Angle joint sensor and actuate */
	AJAInitAndSetupAngleJointActuate();
	AJSInitAngleJointSensors();
	AJSConfigureSendDatabox(CAN_1, 17, CAN_ID_TX_SENSOR_INFO_DMS_3);

	/* System pressure */
	SPSConfigureSystemPressureSensors();
	SPSConfigureSendSensorDatabox(CAN_1, 15, CAN_ID_TX_SENSOR_INFO_DMS_1);

	/* Gas pedal sensor and cabin sensor's */
	GPSConfigureGasPedalInputSensors();
	CSConfigureCabinSensors();

	/* Wheel motor sensor and actuate */
	WMASetupOutputToMotorsAndPumps();
	WMSInitAndConfigureSpeedSensors();

	sys_init("XT28-Transmission", "RC30-00D6"); /* RC28-14/30 */
	sys_initTC(0, 10);
	can_cfgBufs(CAN_1, 5, 5, 40, 40);
	can_cfgBufs(CAN_2, 5, 5, 20, DB_RX_INDEX_CAN_2);
	can_cfgBufs(CAN_3, 5, 5, 20, DB_RX_INDEX_CAN_3);
	can_cfgBufs(CAN_4, 5, 5, 20, DB_RX_INDEX_CAN_4);

	can_init(CAN_1, BAUD_1000K);
	can_init(CAN_2, BAUD_250K);
	can_init(CAN_3, BAUD_250K);
	can_init(CAN_4, BAUD_250K);

	sys_registerTask(mainTask_10ms, 10,	10, 0, 0);

}


static void mainTask_10ms(void) {
	sys_triggerTC(0);

	/* Update sensor stuff */
	AJSUppdateAngleSensorData();
	SPSUppdateSystemPressureSensors();
	GPSUppdatePedalSensorData();
	CSUpdateCabinSensor();
	WMSUpdateSensorValues();

	/* Set machine state and actuate */
	setMachineState();

	/* Send stuff on CAN */
	AJSSendAngleDataOnCAN();
	SPSSendSensorDataOnCAN();
	WMSSendSensorDataOnCAN();
	WMASendMotorPWNOnCAN(TRUE);

	/* Code generation test */
	float gg = NinjaController(10,10);
	gg = 0;
	/* End code generation test */

}

static void setMachineState(void) {


	/* Static states, initialized with default states */
	static driveState xt28DriveState 	= NEUTRAL_DRIVE;
	static turnState  xt28TurnState     = TURN_COMBINED;
	static bool 	  overdriveState    = FALSE;
	static bool 	  xt28BreakState 	= FALSE;

	/* Switch on user pressed button, change states accordingly. */
	exipadButton userPressedButton = EXPGetLastPressedButtonWithToggle();
	switch (userPressedButton) {
	case NONE:
		break;
	case BUTTON_1: /* Enable crane movment if char pos */
		/*! nyi */
		break;
	case BUTTON_2:
		break;
	case BUTTON_3:
		break;
	case BUTTON_4:
		break;
	case BUTTON_5:
		break;
	case BUTTON_6:
		break;
	case BUTTON_7:
		break;
	case BUTTON_8:
		break;
	case BUTTON_9:
		break;
	case BUTTON_10: /* Forward drive state */
		xt28DriveState = FORWARD_DRIVE;
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_11: /* Neutral drive state */
		xt28DriveState = NEUTRAL_DRIVE;
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_12: /* Backward drive state */
		xt28DriveState = BACKWARD_DRIVE;
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_13: /* Turn Front */
		xt28TurnState = TURN_FRONT;
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_14: /* Turn Rear */
		xt28TurnState = TURN_REAR;
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_15: /* Turn PID */
		xt28TurnState = TURN_PID;
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_16: { /* Enable break */
		xt28BreakState = TRUE;
		EXPSetButtonStateTo(NONE);
		break;
	}
	case BUTTON_17:
		break;
	case BUTTON_18:
		break;
	case BUTTON_19:
		break;
	case BUTTON_20:
		break;
	case BUTTON_21: /* Overdrive */
		overdriveState = TRUE;
		EXPSetButtonStateTo(NONE);
		break;
	}


	/* Drive state */
	if (xt28BreakState == TRUE) {
		WMASetBreakState(TRUE);
	} else {
		WMASetBreakState(FALSE);
		int gasPedalSignalIn = GPSGetBreakPedal( CSGetCharPosition() );
		bool slipState = TRUE;
		WMASetMotorReferenceAndActuate(xt28DriveState,
				overdriveState,
				slipState,
				10,
				gasPedalSignalIn
		);
	}

	/* Actuate turn state */
	int joystick = EXPGetJoystickXScaledValueLeftRight();
	AJAActuate( xt28TurnState,
			joystick,
			CSGetCharPosition(),
			WMSGetAvrageRPMForWheels()
	);

}

