
#include "IMU.h"
#include "api_lib_basic.h"
#include <math.h>
#include "XT28CANSupport.h"

// Private prototypes
static void IMUUppdateGyroDataCANCallback(void);
static void IMUAcceleometerUppdateDataCANCallback(void);
static void uppdateFilterdAngelsWithComplementaryFilter(void);

// Databox defines
#define GYRO_RX_DATABOX_BUFFER_LEN_DU8  	5
#define ACCE_RX_DATABOX_BUFFER_LEN_DU8  	5

// -------------------------------------------------
//Public functions

static uint8  IMUCANChannel       = 0;
static uint16 gyroDatabox         = 0;
static uint16 acceleometerDatabox = 0;

void IMUConfigureInertialMeasurementUnit(uint8 CANChannel, uint16 gyroDataboxNumber, uint16 acceleometerDataboxNumber) {

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

uint16 IMUInit(void) {
	uint8 data_au8[2];
	data_au8[0] = 0x01;
	data_au8[1] = 0x7F;

	uint16 initStatus = can_sendData(CAN_2, 0x0, CAN_EXD_DU8, 2, data_au8);
	return initStatus;
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

	uppdateFilterdAngelsWithComplementaryFilter();
}

static float phiAngleInDegree = 0;
static float thetaAngleInDegree = 0;
/*!
 *  This function is called in the callback of 'IMUAcceleometerUppdateDataCANCallback'
 *  and uppdates the local global variabels 'phiAngleInDegree' and 'thetaAngleInDegree'.
 */
static void uppdateFilterdAngelsWithComplementaryFilter(void) {

	int multConstantForFilter = 1000;
	float IMUSensorSampleTime = 0.01;
	int convertToDegreePerSecConstant = 50;
	float alpha = 0.99;

	//Phi (to avoid hazzle with static i did this copyphasta.)
	static int oldFilterdPhiAngle = 0;

	float accAnglePhi = atan((float)accelometerXRaw / accelometerZRaw) * 180 / M_PI * multConstantForFilter;
	float gyroAnglePhi = (float)gyroPhiRaw / convertToDegreePerSecConstant * IMUSensorSampleTime * multConstantForFilter;

	float filterdAnglePhi  = (oldFilterdPhiAngle + gyroAnglePhi) * alpha + (1 - alpha) * accAnglePhi;
	oldFilterdPhiAngle = filterdAnglePhi;

	phiAngleInDegree = filterdAnglePhi / multConstantForFilter;

	//Theta
	static int oldFilterdThetaAngle = 0;

	float accAngleTheta = -atan((float)accelometerYRaw / accelometerZRaw) * 180 / M_PI * multConstantForFilter;
	float gyroAngleTheta = (float)gyroThetaRaw / convertToDegreePerSecConstant * IMUSensorSampleTime * multConstantForFilter;

	float filterdAngleTheta  = (oldFilterdThetaAngle + gyroAngleTheta) * alpha + (1 - alpha) * accAngleTheta;
	oldFilterdThetaAngle = filterdAngleTheta;

	thetaAngleInDegree = filterdAngleTheta / multConstantForFilter;
}


float IMUGetPhi(void) {
	return phiAngleInDegree;
}

float IMUGetTheta(void) {
	return thetaAngleInDegree;
}

float IMUGetAngleVelX(void) {
	int convertToDegreePerSecConstant = 50;
	return (gyroPhiRaw / convertToDegreePerSecConstant);
}

float IMUGetAngleVelY(void) {
	int convertToDegreePerSecConstant = 50;
	return (gyroThetaRaw / convertToDegreePerSecConstant);
}

void IMUSendIMURawValuesOnCAN(uint8 CANChannel, uint32 gyroID, uint32 accID) {

	uint8 angleData_au8[6];
	angleData_au8[0] = accelometerXRaw;
	angleData_au8[1] = accelometerXRaw >> 8;
	angleData_au8[2] = accelometerYRaw;
	angleData_au8[3] = accelometerYRaw >> 8;
	angleData_au8[4] = accelometerZRaw;
	angleData_au8[5] = accelometerZRaw >> 8;

	can_sendData(CANChannel, accID, CAN_STD_DU8, 6, angleData_au8);

	angleData_au8[0] = gyroThetaRaw;
	angleData_au8[1] = gyroThetaRaw >> 8;
	angleData_au8[2] = gyroPhiRaw;
	angleData_au8[3] = gyroPhiRaw >> 8;

	can_sendData(CANChannel, gyroID, CAN_STD_DU8, 4, angleData_au8);
}

void IMUSendFilterdAngleDataOnCAN(uint CANChannel, sint32 ID) {

	sint32 Theta_deg = thetaAngleInDegree;
	sint32 Phi_deg = phiAngleInDegree;

	uint8 data_au8_sms_OBS[8] = {0};
	data_au8_sms_OBS[0] = 0;
	data_au8_sms_OBS[1] = 0;
	data_au8_sms_OBS[2] = 0;
	data_au8_sms_OBS[3] = 0;
	data_au8_sms_OBS[4] = Theta_deg;
	data_au8_sms_OBS[5] = Theta_deg >> 8;
	data_au8_sms_OBS[6] = Phi_deg;
	data_au8_sms_OBS[7] = Phi_deg >> 8;

	can_sendData(CANChannel, ID, CAN_EXD_DU8, 8, data_au8_sms_OBS);
}
