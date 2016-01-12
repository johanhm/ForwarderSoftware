
#include "IMU.h"
#include "api_lib_basic.h"
#include <math.h>

// Private prototypes
static void IMUUppdateGyroDataCANCallback(void);
static void IMUAcceleometerUppdateDataCANCallback(void);
static float calculateAngleWithComplementaryFilter(sint16 rawAccXY, sint16 gyroRaw, float alpha, int oldFilterdAngle);

//CAN ID for IMU message
#define CAN_ID_GYRODATA_DATA				0x1FD
#define CAN_ID_ACCELOMETER_DATA				0x2FD

#define GYRO_RX_DATABOX_BUFFER_LEN_DU8  	5
#define ACCE_RX_DATABOX_BUFFER_LEN_DU8  	5

// -------------------------------------------------
//Public functions

static uint8  IMUCANChannel       = 0;
static uint16 gyroDatabox         = 0;
static uint16 acceleometerDatabox = 0;

void IMUConfigure(uint8 CANChannel, uint16 gyroDataboxNumber, uint16 acceleometerDataboxNumber) {

	static can_DataboxData_ts gyroCanDataboxBuffer[GYRO_RX_DATABOX_BUFFER_LEN_DU8];
	static can_DataboxData_ts acceCanDataboxBuffer[ACCE_RX_DATABOX_BUFFER_LEN_DU8];

	// Set module constants settings
	IMUCANChannel       = CANChannel;
	gyroDatabox         = gyroDataboxNumber;
	acceleometerDatabox = acceleometerDataboxNumber;

	can_initRxDatabox(IMUCANChannel,
			gyroDatabox,
			CAN_ID_GYRODATA_DATA,
			CAN_STD_DU8,
			4,
			gyroCanDataboxBuffer,
			GYRO_RX_DATABOX_BUFFER_LEN_DU8,
			IMUUppdateGyroDataCANCallback
			);

	can_initRxDatabox(IMUCANChannel,
			acceleometerDatabox,
			CAN_ID_ACCELOMETER_DATA,
			CAN_STD_DU8,
			6,
			acceCanDataboxBuffer,
			ACCE_RX_DATABOX_BUFFER_LEN_DU8,
			IMUAcceleometerUppdateDataCANCallback
			);
}

// --------------------------------------------------
// Private

static sint16 gyroThetaRaw = 0;
static sint16 gyroPhiRaw   = 0;

static void IMUUppdateGyroDataCANCallback(void) {
	//Save gyro data

	uint8 angleMessageData_au8[6];
	uint8 angleMessageNumBytes_u8;
	can_getDatabox(IMUCANChannel,
			gyroDatabox,
			angleMessageData_au8,
			&angleMessageNumBytes_u8
			);

	gyroThetaRaw = (angleMessageData_au8[1] << 8 | angleMessageData_au8[0]);  //Gyro around IMU x axis
	gyroPhiRaw   = (angleMessageData_au8[3] << 8 | angleMessageData_au8[2]);  //Gyro around IMU y axis

}

static sint16 accelometerXRaw = 0;
static sint16 accelometerYRaw = 0;
static sint16 accelometerZRaw = 0;

static void IMUAcceleometerUppdateDataCANCallback(void) {

	//Save accelerometer data
	uint8 angleMessageData_au8[6];
	uint8 angleMessageNumBytes_u8;
	can_getDatabox(IMUCANChannel,
			acceleometerDatabox,
			angleMessageData_au8,
			&angleMessageNumBytes_u8
			);

	accelometerYRaw = (angleMessageData_au8[1] << 8 | angleMessageData_au8[0]);
	accelometerXRaw = (angleMessageData_au8[3] << 8 | angleMessageData_au8[2]);
	accelometerZRaw = (angleMessageData_au8[5] << 8 | angleMessageData_au8[4]);

}


static float calculateAngleWithComplementaryFilter(sint16 rawAccXY, sint16 gyroRaw, float alpha, int oldFilterdAngle) {

	int multConstantForFilter = 1000;
	float IMUSensorSampleTime = 0.01;
	int convertToDegreePerSecConstant = 50;

	float accAngle = atan((float)rawAccXY / accelometerZRaw) * 180 / M_PI * multConstantForFilter;
	float gyroAngle = (float)gyroRaw / convertToDegreePerSecConstant * IMUSensorSampleTime * multConstantForFilter;

	oldFilterdAngle = oldFilterdAngle * multConstantForFilter;
	float filterdAngle  = (oldFilterdAngle + gyroAngle) * alpha + (1 - alpha) * accAngle;
	return (filterdAngle / multConstantForFilter);
}

float IMUGetPhi(void) {
	static int oldPhiAngle = 0;

	float phiInDegree = calculateAngleWithComplementaryFilter(accelometerXRaw, gyroPhiRaw, 0.99, oldPhiAngle);
	oldPhiAngle = phiInDegree;

	return phiInDegree;
}

float IMUGetTheta(void) {
	static int oldThetaAngle = 0;

	float thetaInDegree = calculateAngleWithComplementaryFilter(accelometerYRaw, gyroThetaRaw, 0.99, oldThetaAngle);
	oldThetaAngle = thetaInDegree;

	return thetaInDegree;
}




