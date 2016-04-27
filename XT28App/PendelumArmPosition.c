#include "PendelumArmPosition.h"

/* Private prototypes */
static void uppdateForwarderAvrageHeightAndVelocity(void);
static float getVerticalHeightForWheel_m(int wheel);

/* Publick functions */
void PAPOSConfigurePositionSensorsVoltageInput(void) {
	/* Configure pos sensors */
	in_cfgVoltageInput(IN_1_AIV, 500, 4500, 100, 200, 4800, 200); //angle sensor Front right
	in_cfgVoltageInput(IN_2_AIV, 500, 4500, 100, 200, 4800, 200); //angle sensor Front left
	in_cfgVoltageInput(IN_3_AIV, 500, 4500, 100, 200, 4800, 200); //angle sensor Mid right
	in_cfgVoltageInput(IN_4_AIV, 500, 4500, 100, 200, 4800, 200); //angle sensor Mid left
	in_cfgVoltageInput(IN_5_AIV, 500, 4500, 100, 200, 4800, 200); //angle sensor Rear right
	in_cfgVoltageInput(IN_6_AIV, 500, 4500, 100, 200, 4800, 200); //angle sensor Rear left
}

static uint16 posData_mm[SUM_WHEELS] = {0};
static sint16 velData[SUM_WHEELS] = {0};
void PAPOSUppdatePosSensorsDataWithSampleTime(int sampleTime_ms) {

	sampleTime_ms = 0; /* Fixme Not used rigtht now , uppdate so the filters depend on this and remove this comment !!! */

	static uint16 minPos[SUM_WHEELS] = {500, 500, 500, 500, 500, 500}; //current mV
	static uint16 maxPos[SUM_WHEELS] = {4500, 4500, 4500, 4500, 4500, 4500}; //current mV

	static uint16 posData_last[SUM_WHEELS] = {0};
	static sint16 velData_last[SUM_WHEELS] = {0};

	uint8 x = 0; /* Index used in FOR loops */

	/* Read Position sensors  and calculate velocities */

	/* Save Pos(k-1) */
	for (x = 0; x < SUM_WHEELS; x++) {
		posData_last[x] = posData_mm[x];
	}

	uint16 posData_mV[SUM_WHEELS] = {0};

	/* Get new sensor readings and scale from mV to mm */
	posData_mV[FR] = in(IN_1_AIV);
	posData_mV[FL] = in(IN_2_AIV);
	posData_mV[MR] = in(IN_3_AIV);
	posData_mV[ML] = in(IN_4_AIV);
	posData_mV[BR] = in(IN_5_AIV);
	posData_mV[BL] = in(IN_6_AIV);

	/* Scale to [mm] */
	for (x = 0; x < SUM_WHEELS; x++) {
		posData_mm[x] = (float)((float)(posData_mV[x] - minPos[x]) / (maxPos[x] - minPos[x])) * 485;
	}

	/* Save Vel(k-1); */
	for (x = 0; x < SUM_WHEELS; x++) {
		velData_last[x] = velData[x];
	}

	/* Calculate Vel(k) */
	int velocityFilterCoficient = 5; /* Filter coefficient for velocity calculation lower value is more filtering */
	float Ts = 0.02;
	float a_vel = 1 / (1 + velocityFilterCoficient * Ts);
	for (x = 0; x < 6; x++) {
		velData[x] = a_vel * velData_last[x] + a_vel * velocityFilterCoficient * (Ts) * (posData_mm[x] - posData_last[x]) / (Ts);
	}

	uppdateForwarderAvrageHeightAndVelocity();

}

bool PAPOSCheckPosSensorsForErrors(void) {
	uint32 sensorPorts[6] = {IN_1_AIV,
			IN_2_AIV,
			IN_3_AIV,
			IN_4_AIV,
			IN_5_AIV,
			IN_6_AIV
	};
	int sensor = 0;
	for (sensor = 0; sensor < 6; sensor ++) {

		uint8 error = in_getStatus(sensorPorts[sensor]);
		switch (error) {
		case DIAG_NOFAILURE_DU8:
			return FALSE;
		case DIAG_RANGE_DU8:
			return FALSE;
		case DIAG_SCGND_DU8:
			return TRUE;
		case DIAG_SCUBAT_DU8:
			return TRUE;
		case DIAG_OL_DU8:
			return TRUE;
		case DIAG_SCGND_OR_OL_DU8:
			return TRUE;
		case DIAG_SCUBAT_OR_OL_DU8:
			return TRUE;
		}
	}
	return TRUE; /* this should never happen, here to make the compuler shutup */
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
		posDataOutput[wheel] = PAPOSGetPosDataForWheel_mm(wheel);
	}
}

int PAPOSGetVelDataForWheel(int wheel) {
	return (int)velData[wheel];
}

void PAPOSGetVelDataArray(float velDataOutput[static SUM_WHEELS]) {
	int wheel = 0;
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		velDataOutput[wheel] = PAPOSGetVelDataForWheel(wheel);
	}
}

float PAPOSGetAvrageHeightOfForwarder(void) {
	return forwarderAvrageHeightZc;
}

float PAPOSGetAvrageHeightVelocityOfForwarder(void) {
	return forwarderAvrageVelZc;
}

/* Needs to be debugged */
float PAPOSGetBeta(void) {

	/* Calculate angle between front and back pendelumj arms */
	float hFrontAvg  = (getVerticalHeightForWheel_m(FR) + getVerticalHeightForWheel_m(FL) ) / 2;
	float hMiddleAvg = (getVerticalHeightForWheel_m(MR) + getVerticalHeightForWheel_m(ML) ) / 2;
	float hBackAvg   = (getVerticalHeightForWheel_m(BR) + getVerticalHeightForWheel_m(BL) ) / 2;

	float betaMiddle = atan( (hFrontAvg - hMiddleAvg) / LENGTH_TO_MID_OFF_FORWARDER_m );
	float betaBack = atan( (hFrontAvg - hBackAvg) / LENGTH_OF_FORWARDER_m );
	float betaAvg = (betaMiddle + betaBack) / 2;

	float betaAvgRawDeg = betaAvg * 180 / M_PI; /* raw value, it works! */

	/* Low pass filter */
	static float betaAvgFilterdOld = 0;
	const float alpha = 0.995;

	float betaFilterd = betaAvgFilterdOld * alpha + betaAvgRawDeg * (1 - alpha);
	betaAvgFilterdOld = betaFilterd;

	return betaFilterd;
}

static float getVerticalHeightForWheel_m(int wheel) {
	/* Meter [m] */
	const float bCylArm = 0.4991;
	const float lengthArmWheel = 1.008;
	const float lengtharmCyl = 1.211;
	const float cylinderLengthOfsett = 0.85;

	/* Randians [rad] */
	const float theta3 = 0.2983;
	const float theta2 =  0.3370;

	/* Estimate beta */
	int cylinderExtraction = PAPOSGetPosDataForWheel_mm(wheel);
	float lengthMessured = (float)cylinderExtraction / 1000 + cylinderLengthOfsett;
	float alpha = acos( (pow(lengthMessured, 2) - pow(bCylArm, 2) - pow(lengtharmCyl, 2)) / (-2 * bCylArm * lengtharmCyl) );
	float gamma = (alpha + theta2 + theta3) - M_PI / 2;

	float estimatedHeightVertical = lengthArmWheel * sin(gamma);

	return estimatedHeightVertical;
}

void PAPOSSendPosDataOnCAN(uint CANChannel, uint32 middleAndBackID, uint32 frontID) {

	CANSend_uint16(CANChannel, middleAndBackID,
			posData_mm[MR],
			posData_mm[ML],
			posData_mm[BR],
			posData_mm[BL]
	);

	uint8 data_au8_sms_5[4];
	/* Construct msg */
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

	/* Construct msg for front wheels */
	data_au8_sms_5[0] = velData[FR];
	data_au8_sms_5[1] = velData[FR] >> 8;
	data_au8_sms_5[2] = velData[FL];
	data_au8_sms_5[3] = velData[FL] >> 8;
	can_sendData(CANChannel, frontID, CAN_EXD_DU8, 4, data_au8_sms_5);
}


