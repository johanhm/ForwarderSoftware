#include "PendelumArmPosition.h"
#include "api_lib_basic.h"
#include "XT28CANSupport.h"

//private prototypes
static void uppdateForwarderAvrageHeightAndVelocity(void);


void PAPOSConfigurePositionSensorsVoltageInput(void) {
	// configure pos sensors
	in_cfgVoltageInput(IN_1_AIV, 1000, 4000, 100, 200, 4800, 200); //angle sensor Front right
	in_cfgVoltageInput(IN_2_AIV, 1000, 4000, 100, 200, 4800, 200); //angle sensor Front left
	in_cfgVoltageInput(IN_3_AIV, 1000, 4000, 100, 200, 4800, 200); //angle sensor Mid right
	in_cfgVoltageInput(IN_4_AIV, 1000, 4000, 100, 200, 4800, 200); //angle sensor Mid left
	in_cfgVoltageInput(IN_5_AIV, 1000, 4000, 100, 200, 4800, 200); //angle sensor Rear right
	in_cfgVoltageInput(IN_6_AIV, 1000, 4000, 100, 200, 4800, 200); //angle sensor Rear left
}

static uint16 posData_mm[SUM_WHEELS] = {0};
static sint16 velData[SUM_WHEELS] = {0};
void PAPOSUppdatePosSensorsDataWithSampleTime(int sampleTime_ms) {

	sampleTime_ms = 0; /* Not used rigtht now */

	static uint16 minPos[SUM_WHEELS] = {1061, 1199, 1115, 1108, 1105, 1068}; //current mV
	static uint16 maxPos[SUM_WHEELS] = {3864, 4200, 4126, 4039, 4096, 4046}; //current mV
	static uint16 posData_last[SUM_WHEELS] = {0};
	static sint16 velData_last[SUM_WHEELS] = {0};

	uint8 x = 0; //index used in FOR loops


	//////////////////////read Position sensors  and calculate velocities
	//Save Pos(k-1)
	for (x = 0; x < SUM_WHEELS; x++) {
		posData_last[x] = posData_mm[x];
	}

	uint16 posData_mV[SUM_WHEELS] = {0};
	//Get new sensor readings and scale from mV to mm
	posData_mV[FR] = in(IN_1_AIV);
	posData_mV[FL] = in(IN_2_AIV);
	posData_mV[MR] = in(IN_3_AIV);
	posData_mV[ML] = in(IN_4_AIV);
	posData_mV[BR] = in(IN_6_AIV);
	posData_mV[BL] = in(IN_5_AIV);

	for (x = 0; x < SUM_WHEELS; x++) {
		posData_mm[x] = (float)((float)(posData_mV[x] - minPos[x]) / (maxPos[x] - minPos[x])) * 500;
	} //scale to mm

	//Save Vel(k-1);
	for (x = 0; x < SUM_WHEELS; x++) {
		velData_last[x] = velData[x];
	}


	//Calculate Vel(k)
	int velocityFilterCoficient = 5; //Filter coefficient for velocity calculation lower value is more filtering
	float Ts = 0.02;
	float a_vel = 1 / (1 + velocityFilterCoficient * Ts);
	for (x = 0; x < 6; x++) {
		velData[x] = a_vel * velData_last[x] + a_vel * velocityFilterCoficient * (Ts) * (posData_mm[x] - posData_last[x]) / (Ts);
	}

	uppdateForwarderAvrageHeightAndVelocity();
}

static uint16 forwarderAvrageHeightZc = 0;
static sint16 forwarderAvrageVelZc = 0;
static void uppdateForwarderAvrageHeightAndVelocity(void) {
	uint8 x = 0; //index used in FOR loops
	//Observer for average chassis height
	forwarderAvrageHeightZc = 0;
	for (x = 0; x < SUM_WHEELS; x++) {
		forwarderAvrageHeightZc = forwarderAvrageHeightZc + posData_mm[x];
	}
	forwarderAvrageHeightZc = forwarderAvrageHeightZc / SUM_WHEELS;

	forwarderAvrageVelZc = 0;
	for (x = 0; x < SUM_WHEELS; x++) {
		forwarderAvrageVelZc = forwarderAvrageVelZc + velData[x];
	}
	forwarderAvrageVelZc = forwarderAvrageVelZc / SUM_WHEELS;  //Observer for average chassis height velocity
}

int PAPOSGetPosDataForWheel_mm(int wheel) {
	return (int)posData_mm[wheel];
}

void PAPOSGetPosDataArray(int posDataOutput[static SUM_WHEELS]) {
	int wheel = 0;
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		posDataOutput[wheel] = (int)posData_mm[wheel];
	}
}

int PAPOSGetVelDataForWheel(int wheel) {
	return (int)velData[wheel];
}

void PAPOSGetVelDataArray(float velDataOutput[static SUM_WHEELS]) {
	int wheel = 0;
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		velDataOutput[wheel] = (float)velData[wheel];
	}
}

float PAPOSGetAvrageHeightOfForwarder(void) {
	return forwarderAvrageHeightZc;
}

float PAPOSGetAvrageHeightVelocityOfForwarder(void) {
	return forwarderAvrageVelZc;
}

void PAPOSSendPosDataOnCAN(uint CANChannel, uint32 middleAndBackID, uint32 frontID) {

	CANSend_uint16(CANChannel, middleAndBackID,
			posData_mm[MR],
			posData_mm[ML],
			posData_mm[BR],
			posData_mm[BL]
	);

	uint8 data_au8_sms_5[4];
	//Construct msg
	data_au8_sms_5[0] = posData_mm[FR];
	data_au8_sms_5[1] = posData_mm[FR] >> 8;
	data_au8_sms_5[2] = posData_mm[FL];
	data_au8_sms_5[3] = posData_mm[FL] >> 8;
	can_sendData(CANChannel, frontID, CAN_EXD_DU8, 4, data_au8_sms_5);
}

void PAPOSSendVelDataOnCAN(uint CANChannel, uint32 middleAndBackID, uint32 frontID) {

	CANSend_uint16(CANChannel, middleAndBackID,
			velData[MR],
			velData[ML],
			velData[BR],
			velData[BL]
	);

	uint8 data_au8_sms_5[4];

	//Construct msg
	data_au8_sms_5[0] = velData[FR];
	data_au8_sms_5[1] = velData[FR] >> 8;
	data_au8_sms_5[2] = velData[FL];
	data_au8_sms_5[3] = velData[FL] >> 8;
	can_sendData(CANChannel, frontID, CAN_EXD_DU8, 4, data_au8_sms_5);
}


