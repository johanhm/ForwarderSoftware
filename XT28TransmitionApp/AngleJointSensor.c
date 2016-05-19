
#include "AngleJointSensor.h"

/* Private defines */
#define ANALOG_ANGLE_SENSOR_FRONT_1			0
#define ANALOG_ANGLE_SENSOR_FRONT_2			1
#define ANALOG_ANGLE_SENSOR_REAR_1			2
#define ANALOG_ANGLE_SENSOR_REAR_2			3
#define MDEG_ANGLE_SENSOR_FRONT_1			4
#define MDEG_ANGLE_SENSOR_FRONT_2			5
#define MDEG_ANGLE_SENSOR_REAR_1			6
#define MDEG_ANGLE_SENSOR_REAR_2			7
#define MDEG_ANGLE_ALPHA_FRONT				8
#define MDEG_ANGLE_ALPHA_REAR 				9
#define INDEX_SIZE_ANGLE					10

/* Public functions */
void AJSInitAngleJointSensors(void) {
	in_cfgVoltageInput(AIV_Angle_sensor_F_sig1, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(AIV_Angle_sensor_F_sig2, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(AIV_Angle_sensor_R_sig1, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(AIV_Angle_sensor_R_sig2, 1000, 4000, 100, 200, 4800, 200);
}

static int angleData[INDEX_SIZE_ANGLE] = {0};
static int Turning_sensors_status 	= 0;
static int Max_I_FRONT_cylinder 	= 0;
static int Min_I_FRONT_cylinder 	= 0;
static int Max_I_REAR_cylinder 		= 0;
static int Min_I_REAR_cylinder 		= 0;

void AJSUppdateAngleSensorData(void) {

	angleData[ANALOG_ANGLE_SENSOR_FRONT_1] = in(AIV_Angle_sensor_F_sig1);
	angleData[ANALOG_ANGLE_SENSOR_FRONT_2] = in(AIV_Angle_sensor_F_sig2);
	angleData[ANALOG_ANGLE_SENSOR_REAR_1] = in(AIV_Angle_sensor_R_sig1); //used
	angleData[ANALOG_ANGLE_SENSOR_REAR_2] = in(AIV_Angle_sensor_R_sig2);

	/* --Turning sensors calibrationdata-- */
	const int Front_zeroAngle_mV 		= 3296;//2204;
	const int Front_left_maxAngle_mV 	= 4509;//3098;
	const int Front_right_maxAngle_mV 	= 1727;//1108;
	const int Rear_zeroAngle_mV 		= 2244;//1105;
	const int Rear_left_maxAngle_mV 	= 3464;//1740;
	const int Rear_right_maxAngle_mV 	= 867;//395;

	const int Front_maxAngle_deg = 25;//395;
	const int Rear_maxAngle_deg  = 25;//1740;


	/*** ANGLE CONVERSION ***/
	/* Front signal */
	/* Turn - Left */
	bool turnLeft = (angleData[ANALOG_ANGLE_SENSOR_FRONT_1] > Front_zeroAngle_mV);
	if	(turnLeft) {
		int kvot = (angleData[ANALOG_ANGLE_SENSOR_FRONT_1] - Front_left_maxAngle_mV) / (Front_left_maxAngle_mV - Front_zeroAngle_mV);
		angleData[MDEG_ANGLE_SENSOR_FRONT_1] = (Front_maxAngle_deg * 100) * kvot + Front_maxAngle_deg * 100;
	} else { //Turn right and zero
		angleData[MDEG_ANGLE_SENSOR_FRONT_1] = (-Front_maxAngle_deg * 100) * (angleData[ANALOG_ANGLE_SENSOR_FRONT_1] - Front_right_maxAngle_mV) / (Front_right_maxAngle_mV - Front_zeroAngle_mV) - Front_maxAngle_deg * 100;
	}

	/* Saturation if exceeds values */
	if (angleData[ANALOG_ANGLE_SENSOR_FRONT_1] > Front_left_maxAngle_mV) {
		angleData[MDEG_ANGLE_SENSOR_FRONT_1] = Front_maxAngle_deg * 100;
	}
	else if (angleData[ANALOG_ANGLE_SENSOR_FRONT_1] < Front_right_maxAngle_mV) {
		angleData[MDEG_ANGLE_SENSOR_FRONT_1] = -Front_maxAngle_deg * 100;
	}

	/* Rear signal */
	//Turn- Left
	if	(angleData[ANALOG_ANGLE_SENSOR_REAR_1] > Rear_zeroAngle_mV) {
		angleData[MDEG_ANGLE_SENSOR_REAR_1] = (Rear_maxAngle_deg*100)*(angleData[ANALOG_ANGLE_SENSOR_REAR_1]-Rear_left_maxAngle_mV)/(Rear_left_maxAngle_mV-Rear_zeroAngle_mV)+Rear_maxAngle_deg*100;
	} else {		//Turn right and zero
		angleData[MDEG_ANGLE_SENSOR_REAR_1]=(-Rear_maxAngle_deg*100)*(angleData[ANALOG_ANGLE_SENSOR_REAR_1]-Rear_right_maxAngle_mV)/(Rear_right_maxAngle_mV-Rear_zeroAngle_mV)-Rear_maxAngle_deg*100;
	}

	/* Saturation if exceeds values */
	if (angleData[ANALOG_ANGLE_SENSOR_REAR_1] > Rear_left_maxAngle_mV) {
		angleData[MDEG_ANGLE_SENSOR_REAR_1] = Rear_maxAngle_deg * 100;
	}
	else if (angleData[ANALOG_ANGLE_SENSOR_REAR_1] < Rear_right_maxAngle_mV) {
		angleData[MDEG_ANGLE_SENSOR_REAR_1] = -Rear_maxAngle_deg * 100;
	}

	/* -- Signal check -- */
	if (Front_left_maxAngle_mV > Front_right_maxAngle_mV) {
		Max_I_FRONT_cylinder = Front_left_maxAngle_mV * 1.1;
		Min_I_FRONT_cylinder = Front_right_maxAngle_mV * 0.9;
	} else {
		Max_I_FRONT_cylinder = Front_right_maxAngle_mV * 1.1;
		Min_I_FRONT_cylinder = Front_left_maxAngle_mV * 0.9;
	}

	if (Rear_left_maxAngle_mV > Rear_right_maxAngle_mV){
		Max_I_REAR_cylinder = Rear_left_maxAngle_mV * 1.1;
		Min_I_REAR_cylinder = Rear_right_maxAngle_mV * 0.9;
	} else {
		Max_I_REAR_cylinder = Rear_right_maxAngle_mV * 1.1;
		Min_I_REAR_cylinder = Rear_left_maxAngle_mV * 0.9;
	}

	if (angleData[ANALOG_ANGLE_SENSOR_FRONT_1] > Max_I_FRONT_cylinder || angleData[ANALOG_ANGLE_SENSOR_REAR_1] < Min_I_FRONT_cylinder ) {
		Turning_sensors_status = 0;
	}
	else if (angleData[ANALOG_ANGLE_SENSOR_REAR_1] > Max_I_REAR_cylinder || angleData[ANALOG_ANGLE_SENSOR_REAR_1] < Min_I_REAR_cylinder ) {
		Turning_sensors_status = 0;
	} else {
		Turning_sensors_status = 1;
	}

}

static uint8 sensorCANChannel;
static int sensorDataboxNumber;
void AJSConfigureSendDatabox(uint8 CANChannel, int databoxNumber, uint32 AngleSensorID) {

	sensorCANChannel = CANChannel;
	sensorDataboxNumber = databoxNumber;
	can_cfgTxDatabox(CANChannel,
			databoxNumber,
			AngleSensorID,
			CAN_EXD_DU8
	);
}

void AJSSendAngleDataOnCAN(void) {
	/* Construct msg SENSOR DMS 3 */
	uint8 data_au8_sens_dms_3[8];
	data_au8_sens_dms_3[0] = 0;
	data_au8_sens_dms_3[1] = 0;
	data_au8_sens_dms_3[2] = 0;
	data_au8_sens_dms_3[3] = 0;
	data_au8_sens_dms_3[4] = angleData[MDEG_ANGLE_SENSOR_FRONT_1];
	data_au8_sens_dms_3[5] = angleData[MDEG_ANGLE_SENSOR_FRONT_1] >> 8;
	data_au8_sens_dms_3[6] = angleData[MDEG_ANGLE_SENSOR_REAR_1];
	data_au8_sens_dms_3[7] = angleData[MDEG_ANGLE_SENSOR_REAR_1] >> 8;

	can_sendDatabox(sensorCANChannel,
			sensorDataboxNumber,
			8,
			data_au8_sens_dms_3
	);
}

int AJSGetAngleFront(void) {
	return angleData[MDEG_ANGLE_SENSOR_FRONT_1];
}

int AJSGetAngleBack(void) {
	return angleData[MDEG_ANGLE_SENSOR_REAR_1];
}






