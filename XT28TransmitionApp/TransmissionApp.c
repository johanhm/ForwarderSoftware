#include "api_lib_basic.h"
#include "XT28TransmissitionAPI.h"


#include "NinjaController.h"

/* Private prototypes */
void sys_main(void);
static void mainTask_10ms(void);
static void setMachineState(void);


/* Start of program */
void sys_main(void) {

	/* Setup CAN */
	XT28TCANInitAndSetup();

	/* Engine CAN Communications */
	ECCInitAndSetupEngineCANCommunications();

	/* Excipad configure */
	EXPConfigureExcipad(CAN_2, 1, 2, 3);

	sys_init("XT28-Transmission", "RC30-00D6"); /* RC28-14/30 */
	emcy_disableInput(EMCY_DISABLE_KEY_DU32, ~EMCY_DISABLE_KEY_DU32);

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

	sys_initTC(0, 10);

	sys_registerTask(mainTask_10ms, 10,	10, 0, 0);

	/* init breakState */
	WMASetBreakState(FALSE);

}


static void mainTask_10ms(void) {
	sys_triggerTC(0);
	sys_setVP(VP_1, ON);
	sys_setVP(VP_2, ON);

	/* Update sensor stuff */
	AJSUppdateAngleSensorData();
	SPSUppdateSystemPressureSensors();
	CSUpdateCabinSensor();
	GPSUppdatePedalSensorData( CSGetCharPosition() );
	WMSUpdateSensorValues();

	/* Update RPM Reference and engine data */
	ECCSetEngineRPMReference( EXPGetScrollerValue());
	ECCUpdateDataFromCAN();

	/* Set machine state and actuate */
	setMachineState();

	/* Send stuff on CAN */
	CANSendDebuggMessage( CAN_1 );
	AJSSendAngleDataOnCAN();
	SPSSendSensorDataOnCAN();
	WMSSendSensorDataOnCAN();
	CANSendDebuggMessage(CAN_1);
	DTSendDMSOnCAN(CAN_1);
	DTSendDMSOnCAN(CAN_4);

	/* Code generation test */
	float gg = NinjaController(10,10);
	gg = 0;
	/* End code generation test */

}

static void setMachineState(void) {


	/* Static states, initialized with default states */
	static driveState xt28DriveState 	= NEUTRAL_DRIVE;
	static turnState  xt28TurnState     = TURN_COMBINED;

	/* Switch on user pressed button, change states accordingly. */
	exipadButton userPressedButton = EXPGetLastPressedButtonWithToggle();

	/*
	g_debug1_1 = userPressedButton;
	g_debug1_2 = EXPGetJoystickXScaledValueLeftRight();
	g_debug1_3 = EXPGetScrollerValue();

	g_debug2_1 = CSGetCharPosition();
	g_debug2_2 = GPSGetGassPedalFilterdAndScaled();
	g_debug2_3 = GPSGetBreakPedal();
	g_debug2_4 = WMSGetAvrageRPMForWheels();
	 */

	static int userMaxSpeedReference = 500;

	switch (userPressedButton) {
	case NONE:
		break;
	case BUTTON_1: /* Enable crane movement if char position */
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
	case BUTTON_10: /* Backward drive state */
		xt28DriveState = TCSAttemtToSetDriveStateTo(BACKWARD_DRIVE);
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_11: /* Neutral drive state */
		xt28DriveState = TCSAttemtToSetDriveStateTo(NEUTRAL_DRIVE);
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_12: /* Forward drive state */
		xt28DriveState = TCSAttemtToSetDriveStateTo(FORWARD_DRIVE);
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_13: /* Turn Front */
		xt28TurnState = AJAAttemtToSetTurnStateTo(TURN_FRONT);
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_14: /* Turn Rear */
		xt28TurnState = AJAAttemtToSetTurnStateTo(TURN_REAR);
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_15: /* Turn PID or Combined, toggle when pressed */
		if (xt28TurnState != TURN_COMBINED) {
			xt28TurnState = AJAAttemtToSetTurnStateTo(TURN_COMBINED);
		} else {
			xt28TurnState = AJAAttemtToSetTurnStateTo(TURN_PID);
		}
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_16: /* Enable break */
		TCSAttemtToSetBreakStateTo( !WMAGetBreakState() );
		EXPSetButtonStateTo(NONE);
		break;
	case BUTTON_17:
		break;
	case BUTTON_18:
		break;
	case BUTTON_19:
		if (EXPGetUserIsHoldingAButtonDown()) {
			userMaxSpeedReference = userMaxSpeedReference + 1;
			if (userMaxSpeedReference > 1000) {
				userMaxSpeedReference = 1000;
			}
		} else {
			EXPSetButtonStateTo(NONE);
		}
		break;
	case BUTTON_20:
		if (EXPGetUserIsHoldingAButtonDown()) {
			userMaxSpeedReference = userMaxSpeedReference - 1;
			if (userMaxSpeedReference < 100) {
				userMaxSpeedReference = 100;
			}
		} else {
			EXPSetButtonStateTo(NONE);
		}
		break;
	case BUTTON_21: /* Overdrive */
		xt28DriveState = TCSAttemtToSetDriveStateTo(FORWARD_OVERDRIVE);
		EXPSetButtonStateTo(NONE);
		break;
	}

	/* Drive state */
	//g_debug2_3 = maxSpeed;
	static float regulatorOffset = 0;
	if (ECCGetEngineData().engineLoad > 60) {
		regulatorOffset = regulatorOffset - 2.0f;
	} else {
		regulatorOffset = regulatorOffset + 0.5f;
		if (regulatorOffset > 0) {
			regulatorOffset = 0;
		}
	}
	static int maxSpeed = 0;
	maxSpeed = userMaxSpeedReference + regulatorOffset;
	if (maxSpeed < 100) {
		maxSpeed = 100;
	}

	TCSActuate( GPSGetGassPedalFilterdAndScaled() , maxSpeed);
	DTSetMaxValueToDisplay(maxSpeed);

	/* Actuate turn state */
	int joystick = EXPGetJoystickXScaledValueLeftRight();
	AJAActuate(
			joystick,
			CSGetCharPosition(),
			WMSGetAvrageRPMForWheels()
	);
}

