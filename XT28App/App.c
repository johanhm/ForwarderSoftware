#include "api_lib_basic.h"
//#include "XT28_api.h"
#include "IMU.h"
#include "PendelumArmPressure.h"
#include "PendelumArmPosition.h"
#include "XT28CANSupport.h"

// Defines
#define READ_SENSORS_PRIO 5
#define READ_SENSORS_TASK_TIME_MS 10
#define READ_SENSORS_OFFSET_MS 0

// Prototypes
void sys_main(void);
void readSensorsTask_10ms(void);


//Start of program
void sys_main(void) {

	// CAN channels configuration
	CANConfigureXT28CANChannels();

	int databoxNrGyro = 1;
	int databoxNrAcc = 2;
	IMUConfigure(CAN_2, databoxNrGyro, databoxNrAcc);

	can_init(CAN_1, 1000000);
	can_init(CAN_2, 500000);
	can_init(CAN_3, 250000);

	IMUInit();


	// Initialize RC/SRC.
	sys_init("SMS", "RC30-00D6"); // RC28-14/30
	emcy_disableInput(EMCY_DISABLE_KEY_DU32, ~EMCY_DISABLE_KEY_DU32);

	// Configure analoge sensors.
	PAPRConfigurePressureSensors();
	PAPOSConfigurePositionSensors();

	sys_registerTask( readSensorsTask_10ms,
			READ_SENSORS_PRIO,
			READ_SENSORS_TASK_TIME_MS,
			READ_SENSORS_OFFSET_MS,
			0
	);
	sys_initTC(0, READ_SENSORS_TASK_TIME_MS);

}

void readSensorsTask_10ms(void) {
	sys_triggerTC(0);
	CANSendSupplyVoltageOnCAN(CAN_1, 0x18FF1060);

	IMUSendIMURawValuesOnCAN( CAN_1,
			CAN_ID_GYRODATA_DATA,
			CAN_ID_ACCELOMETER_DATA
	);
	IMUSendFilterdAngleDataOnCAN(CAN_1, CAN_ID_SENSOR_INFO_SMS_16);

	// Uppdate presure and recalculate force data
	PAPRUppdatePressureData();
	PAPRUppdateForceOnWheelsData();
	PAPOSUppdatePosSensorsData(READ_SENSORS_TASK_TIME_MS);

	// Send data on CAN
	PAPRSendPressureDataOnCAN(CAN_1,
			CAN_ID_SENSOR_INFO_SMS_1,
			CAN_ID_SENSOR_INFO_SMS_2,
			CAN_ID_SENSOR_INFO_SMS_3
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

	PAPOSSendPosDataOnCAN(CAN_1,
			CAN_ID_SENSOR_INFO_SMS_4,
			CAN_ID_SENSOR_INFO_SMS_5
	);
	PAPOSSendVelDataOnCAN(CAN_1,
			CAN_ID_SENSOR_INFO_SMS_6,
			CAN_ID_SENSOR_INFO_SMS_7
	);
	PAPRSendOptimalForceRefOnCAN(CAN_1,
			0x123,
			0x1234
	);
	PAPRSendMassCenterLocationOnCAN(CAN_1,
			0x123
	);

}




