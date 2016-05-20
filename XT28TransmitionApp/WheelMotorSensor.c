
#include "WheelMotorSensor.h"

		//defines index for global frequency motor
#define FREQUENCY_MOTOR_1					0
#define FREQUENCY_MOTOR_2					1
#define FREQUENCY_MOTOR_3					2
#define FREQUENCY_MOTOR_4					3
#define FREQUENCY_MOTOR_5					4
#define FREQUENCY_MOTOR_6					5
#define RPM_MOTOR_1							6
#define RPM_MOTOR_2							7
#define RPM_MOTOR_3							8
#define RPM_MOTOR_4							9
#define RPM_MOTOR_5							10
#define RPM_MOTOR_6							11
#define RPM_WHEEL_1							12
#define RPM_WHEEL_2							13
#define RPM_WHEEL_3							14
#define RPM_WHEEL_4							15
#define RPM_WHEEL_5							16
#define RPM_WHEEL_6							17
#define RPM_WHEEL_AVG						18
#define RPM_WHEEL_AVG_LP					19
#define RPM_WHEEL_AVG_OLD_LP				20
#define INDEX_SIZE_FREQUENCY_MOTOR			21
static int speedData[INDEX_SIZE_FREQUENCY_MOTOR] = {0};

// defines index for global Motor Angle count
#define MOTOR_1					0
#define MOTOR_2					1
#define MOTOR_3					2
#define MOTOR_4					3
#define MOTOR_5					4
#define MOTOR_6					5
#define WHEEL_1					6
#define WHEEL_2					7
#define WHEEL_3					8
#define WHEEL_4					9
#define WHEEL_5					10
#define WHEEL_6					11
#define INDEX_SIZE_MOTOR		12
static int revCount[INDEX_SIZE_MOTOR] = {0};
//static int cm_wheeldistance_sint32[INDEX_SIZE_MOTOR] = {0};


/* Public Functions */
void WMSInitAndConfigureSpeedSensors(void) {

	in_cfgVoltageInput(FI_Motor_1_hz, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(FI_Motor_2_hz, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(FI_Motor_3_hz, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(FI_Motor_4_hz, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(FI_Motor_5_hz, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(FI_Motor_6_hz, 1000, 4000, 100, 200, 4800, 200);

}


void WMSUpdateSensorValues(void) {

	speedData[FREQUENCY_MOTOR_1] = in(FI_Motor_1_hz);
	speedData[FREQUENCY_MOTOR_2] = in(FI_Motor_2_hz);
	speedData[FREQUENCY_MOTOR_3] = in(FI_Motor_3_hz);
	speedData[FREQUENCY_MOTOR_4] = in(FI_Motor_4_hz);
	speedData[FREQUENCY_MOTOR_5] = in(FI_Motor_6_hz);
	speedData[FREQUENCY_MOTOR_6] = in(FI_Motor_5_hz);

	revCount[MOTOR_1]=in(CI_Motor_1);
	revCount[MOTOR_1]=in(CI_Motor_2);
	revCount[MOTOR_1]=in(CI_Motor_3);
	revCount[MOTOR_1]=in(CI_Motor_4);
	revCount[MOTOR_1]=in(CI_Motor_6);
	revCount[MOTOR_1]=in(CI_Motor_5);

	/**********SPEED CONVERSION*********/

	const int Motor_teeth = 67;
	speedData[RPM_MOTOR_1] = (speedData[FREQUENCY_MOTOR_1] * 60 * 10) / Motor_teeth;
	speedData[RPM_MOTOR_2] = (speedData[FREQUENCY_MOTOR_2] * 60 * 10) / Motor_teeth;
	speedData[RPM_MOTOR_3] = (speedData[FREQUENCY_MOTOR_3] * 60 * 10) / Motor_teeth;
	speedData[RPM_MOTOR_4] = (speedData[FREQUENCY_MOTOR_4] * 60 * 10) / Motor_teeth;
	speedData[RPM_MOTOR_5] = (speedData[FREQUENCY_MOTOR_5] * 60 * 10) / Motor_teeth;
	speedData[RPM_MOTOR_6] = (speedData[FREQUENCY_MOTOR_6] * 60 * 10) / Motor_teeth;

	speedData[RPM_WHEEL_1] = speedData[RPM_MOTOR_1] / 48.3;
	speedData[RPM_WHEEL_2] = speedData[RPM_MOTOR_2] / 48.3;
	speedData[RPM_WHEEL_3] = speedData[RPM_MOTOR_3] / 48.3;
	speedData[RPM_WHEEL_4] = speedData[RPM_MOTOR_4] / 48.3;
	speedData[RPM_WHEEL_5] = speedData[RPM_MOTOR_5] / 48.3;
	speedData[RPM_WHEEL_6] = speedData[RPM_MOTOR_6] / 48.3;

}


void WMSSendSensorDataOnCAN(void) {
	/** fixme Implement */
}

int WMSGetRPMForWheel(int wheel) {
	wheel = 0;
	/*!
	 * fixme ret
	 */
	return speedData[RPM_WHEEL_4];
}

int WMSGetAvrageRPMForWheels(void) {
	return speedData[RPM_WHEEL_AVG];
}


