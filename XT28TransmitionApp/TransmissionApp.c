#include "api_lib_basic.h"

#include "AngleJointSensor.h"
#include "SystemPressureSensors.h"
#include "GasPedalSensor.h"
#include "CabinSensors.h"
#include "WheelMotorActuate.h"
#include "WheelMotorSensor.h"


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


/* Start of program */
void sys_main(void) {


	AJSInitAngleJointSensors();
	AJSConfigureSendDatabox(CAN_1, 17, CAN_ID_TX_SENSOR_INFO_DMS_3);

	SPSConfigureSystemPressureSensors();
	SPSConfigureSendSensorDatabox(CAN_1, 15, CAN_ID_TX_SENSOR_INFO_DMS_1);

	GPSConfigureGasPedalInputSensors();

	WMASetupOutputToMotors();

	CSConfigureCabinSensors();

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

	/* Uppdate sensor stuff */
	AJSUppdateAngleSensorData();
	SPSUppdateSystemPressureSensors();
	GPSUppdatePedalSensorData();
	CSUpdateCabinSensor();
	WMSUpdateSensorValues();

	/* Send stuff on CAN */
	AJSSendAngleDataOnCAN();
	SPSSendSensorDataOnCAN();
	WMSSendSensorDataOnCAN();

	WMASetMotorReferenceAndActuate(FORWARD_DRIVE, TRUE, 10);
	WMASetBreakState(FALSE);

}
