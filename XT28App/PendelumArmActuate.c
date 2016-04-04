#include "PendelumArmActuate.h"
#include "PendelumArmPosition.h"
#include "XT28HardwareConstants.h"


#define REFERENCE_CURRENT_MAXIMUM_B_mA   -400
#define REFERENCE_CURRENT_MAXIMUM_A_mA   400
#define DEADZONE_FOR_SOLEONID_CURRENT_mA 400

#define CYL_POS_MAX  490 			//Software cylinder position maximum limit (mm)
#define CYL_POS_MIN  100 			//Software cylinder minimum position limit (mm)

// setting current error codes
#define SUCESS_SETTING_CURRENT   0
#define CURRENT_SET_TO_MAXIMUM   1
#define ERROR_SETTING_CURRENT    2

// Private prototypes
static void checkCylinderPosLimit(void);
static void addDeadbandCurrentToOutputAndSplitIntoAB(int wheel);
static int convertFlowToCurrent(float requestedFlowPercentage);
static int convertVelocityToCurrent(float requestedVel_ms);


// Start of implementation
void PAAConfigurePendelumArmOutputs(void) {
	//BOSCH preferred
	uint32 cfg_minLoad   = 5000;			/* [mOhm] */
	uint16 cfg_maxLoad   = 30000;			/* 21700  */
	uint16 cfg_frequency = f_200Hz_DU16;	/* [Hz]   */
	uint32 cfg_debounce  = 100;				/* [ms]   */

	out_cfg(OUT_1_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_2_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_3_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_4_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_5_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_6_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_7_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_8_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_9_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_10_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_11_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_12_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);

	/* Set PI constants for all outputs */
	out_cfgPI(OUT_1_POH_CL, 157, 136);
	out_cfgPI(OUT_2_POH_CL, 157, 136);
	out_cfgPI(OUT_3_POH_CL, 157, 136);
	out_cfgPI(OUT_4_POH_CL, 157, 136);
	out_cfgPI(OUT_5_POH_CL, 157, 136);
	out_cfgPI(OUT_6_POH_CL, 157, 136);
	out_cfgPI(OUT_7_POH_CL, 157, 136);
	out_cfgPI(OUT_8_POH_CL, 157, 136);
	out_cfgPI(OUT_9_POH_CL, 157, 136);
	out_cfgPI(OUT_10_POH_CL, 157, 136);
	out_cfgPI(OUT_11_POH_CL, 157, 136);
	out_cfgPI(OUT_12_POH_CL, 157, 136);

	// Configure passive dampening outputs
	out_cfg(OUT_19_DOH, 100, f_100Hz_DU16, 4000, 18000);
	out_cfg(OUT_20_DOH, 100, f_100Hz_DU16, 4000, 18000);
	out_cfg(OUT_21_DOH, 100, f_100Hz_DU16, 4000, 18000);
	out_cfg(OUT_22_DOH, 100, f_100Hz_DU16, 4000, 18000);
	out_cfg(OUT_23_DOH, 100, f_100Hz_DU16, 4000, 18000);
	out_cfg(OUT_24_DOH, 100, f_100Hz_DU16, 4000, 18000);

}

void PAASetPassiveDampeningState(bool state) {
	uint16 passiveState = 0;
	switch (state) {
	case TRUE:
		passiveState = 1;
		break;
	case FALSE:
		passiveState = 0;
		break;
	default:
		break;
	}
	out(OUT_19_DOH, passiveState);
	out(OUT_20_DOH, passiveState);
	out(OUT_21_DOH, passiveState);
	out(OUT_22_DOH, passiveState);
	out(OUT_23_DOH, passiveState);
	out(OUT_24_DOH, passiveState);
}

static int referenceSoleonidOutputCurrent_ma[SUM_WHEELS];
int PAAGetReferenceCurrentForWheel(int wheel) {
	return referenceSoleonidOutputCurrent_ma[wheel];
}


void PAASetReferenceArrayWithUnit(float referenceArray[static SUM_WHEELS], PAAOutUnit unit)  {
	int wheel = 0;
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		PAASetReferenceForWheelWithUnit(wheel,
				unit,
				referenceArray[wheel]
		);
	}
}

int PAASetReferenceForWheelWithUnit(int wheel, PAAOutUnit unit, float referenceInput) {

	int referenceCurrentInput_ma = 0;
	if (unit == FLOW_PERCENTAGE) {
		referenceCurrentInput_ma = convertFlowToCurrent(referenceInput);
	} else if (unit == VELOCITY_MS) {
		referenceCurrentInput_ma = convertVelocityToCurrent(referenceInput);
	} else if (unit == CURRENT_MA) {
		referenceCurrentInput_ma = (int)referenceInput;
	} else {
		return ERROR_SETTING_CURRENT;
	}

	int errorMessage = 0;
	referenceSoleonidOutputCurrent_ma[wheel] = referenceCurrentInput_ma;
	if (referenceCurrentInput_ma < REFERENCE_CURRENT_MAXIMUM_B_mA) {
		referenceSoleonidOutputCurrent_ma[wheel] = REFERENCE_CURRENT_MAXIMUM_B_mA;
		errorMessage = CURRENT_SET_TO_MAXIMUM;
	}
	else if (referenceCurrentInput_ma > REFERENCE_CURRENT_MAXIMUM_A_mA) {
		referenceSoleonidOutputCurrent_ma[wheel] = REFERENCE_CURRENT_MAXIMUM_A_mA;
		errorMessage = CURRENT_SET_TO_MAXIMUM;
	}
	addDeadbandCurrentToOutputAndSplitIntoAB(wheel);
	errorMessage = SUCESS_SETTING_CURRENT;
	return errorMessage;
}

static int convertFlowToCurrent(float requestedFlowPercentage) {

	float cp1 = 0.0000117254976;
	float cp2 = -0.0020898157818;
	float cp3 = 0.1025966561449;
	float cp4 = 2.2459943305454;
	float cp5 = 0;
	int correspondingCurrent = 0;

	float absoluteFlowInPercent = fabs(requestedFlowPercentage * 100.0);
	if (requestedFlowPercentage < 0.025 && requestedFlowPercentage > -0.025) {
		correspondingCurrent = 0;
	} else if (fabs(requestedFlowPercentage) > 0.97) {
		correspondingCurrent = 400 * (requestedFlowPercentage / fabs(requestedFlowPercentage)); //changed from 600
	} else {
		correspondingCurrent = (requestedFlowPercentage / fabs(requestedFlowPercentage)) * (cp1 * pow(absoluteFlowInPercent,4) + cp2 * pow(absoluteFlowInPercent,3) + cp3 * pow(absoluteFlowInPercent,2) + cp4 * absoluteFlowInPercent + cp5);
	}
	return correspondingCurrent;
}

static int convertVelocityToCurrent(float requestedVel_ms) {
	/* Not yet implemented */
	requestedVel_ms = 0;
	return 0;
}

void PAASetReferenceCurrentSaturationLimit(int currentLimit) {
	/* Not implemented yet */
	currentLimit = 0;
}

bool actuateEnabled = FALSE;
void PAASetPendelumArmActuateState(bool state) {
	actuateEnabled = state;
}

bool pendelumArmPosLimit = 1;
void PAASetPendelumArmPosLimitState(bool state) {
	pendelumArmPosLimit = state;
}

static volatile sint16 referenceCurrentPortA[SUM_WHEELS] = {0};
static volatile sint16 referenceCurrentPortB[SUM_WHEELS] = {0};
void PAAActuatePendelumArms(void) {
	if (pendelumArmPosLimit) {
		checkCylinderPosLimit();
	}
	//If OUT_Analog then actuate solenoids with scaled values
	if (actuateEnabled == TRUE) {
		out(OUT_PENDELURM_FRONT_RIGHT_A, referenceCurrentPortA[FR]);
		out(OUT_PENDELURM_FRONT_RIGHT_B, referenceCurrentPortB[FR]);

		out(OUT_PENDELURM_FRONT_LEFT_A,  referenceCurrentPortA[FL]);
		out(OUT_PENDELURM_FRONT_LEFT_B,  referenceCurrentPortB[FL]);

		out(OUT_PENDELURM_MID_RIGHT_A,   referenceCurrentPortA[MR]);
		out(OUT_PENDELURM_MID_RIGHT_B,   referenceCurrentPortB[MR]);

		out(OUT_PENDELURM_MID_LEFT_A,    referenceCurrentPortA[ML]);
		out(OUT_PENDELURM_MID_LEFT_B,    referenceCurrentPortB[ML]);

		out(OUT_PENDELURM_REAR_RIGHT_A,  referenceCurrentPortA[BR]);
		out(OUT_PENDELURM_REAR_RIGHT_B,  referenceCurrentPortB[BR]);

		out(OUT_PENDELURM_REAR_LEFT_A,   referenceCurrentPortA[BL]);
		out(OUT_PENDELURM_REAR_LEFT_B,   referenceCurrentPortB[BL]);}
}

static void addDeadbandCurrentToOutputAndSplitIntoAB(int wheel) {
	if (referenceSoleonidOutputCurrent_ma[wheel] == 0) {//both valves off
		referenceCurrentPortA[wheel] = 0;
		referenceCurrentPortB[wheel] = 0;
	}
	else if (referenceSoleonidOutputCurrent_ma[wheel] > 0) {//Output scaled on A  turn off B
		referenceCurrentPortA[wheel] = referenceSoleonidOutputCurrent_ma[wheel] + DEADZONE_FOR_SOLEONID_CURRENT_mA;  //Out between 400 and 800
		referenceCurrentPortB[wheel] = 0;
	}
	else if (referenceSoleonidOutputCurrent_ma[wheel] < 0) {//Output scaled on B  turn off A
		referenceCurrentPortA[wheel] = 0;
		referenceCurrentPortB[wheel] = (-1 * referenceSoleonidOutputCurrent_ma[wheel]) + DEADZONE_FOR_SOLEONID_CURRENT_mA;	} //Out between 400 and 800
}

static void checkCylinderPosLimit(void) {
	uint8 wheel = 0;

	//Cylinder position limit control, does not let cylinder be actuated further in the direction that passed the limit
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		if (PAPOSGetPosDataForWheel_mm(wheel) < CYL_POS_MIN) { //Assuming REF_A() makes the cylinder go to the positive (extending) direction
			referenceCurrentPortA[wheel] = 0;
		} else if (PAPOSGetPosDataForWheel_mm(wheel) > CYL_POS_MAX) {
			referenceCurrentPortB[wheel] = 0;
		}     //Assuming REF_B() makes the cylinder go to the negative (retracting) direction
	}
}


//MARK: CAN functions
void PAASendReferenceCurrentOnCAN(uint8 CANChannel, uint32 frontID, uint32 middleID, uint32 backID) {

	// Motorola standard bifshift tt, every other messages uses INTEL.
	uint8 data_au8_cylinders_front[8] = {0};
	data_au8_cylinders_front[0] = referenceCurrentPortA[FR] >> 8;
	data_au8_cylinders_front[1] = referenceCurrentPortA[FR];
	data_au8_cylinders_front[2] = referenceCurrentPortB[FR] >>8;
	data_au8_cylinders_front[3] = referenceCurrentPortB[FR];
	data_au8_cylinders_front[4] = referenceCurrentPortA[FL] >> 8;
	data_au8_cylinders_front[5] = referenceCurrentPortA[FL];
	data_au8_cylinders_front[6] = referenceCurrentPortB[FL] >>8;
	data_au8_cylinders_front[7] = referenceCurrentPortB[FL];
	can_sendData(CANChannel, frontID, CAN_EXD_DU8, 8, data_au8_cylinders_front);

	uint8 data_au8_cylinders_mid[8]   = {0};
	data_au8_cylinders_mid[0] = referenceCurrentPortA[MR] >> 8;
	data_au8_cylinders_mid[1] = referenceCurrentPortA[MR];
	data_au8_cylinders_mid[2] = referenceCurrentPortB[MR] >> 8;
	data_au8_cylinders_mid[3] = referenceCurrentPortB[MR];
	data_au8_cylinders_mid[4] = referenceCurrentPortA[ML] >> 8;
	data_au8_cylinders_mid[5] = referenceCurrentPortA[ML];
	data_au8_cylinders_mid[6] = referenceCurrentPortB[ML] >> 8;
	data_au8_cylinders_mid[7] = referenceCurrentPortB[ML];
	can_sendData(CANChannel, middleID, CAN_EXD_DU8, 8, data_au8_cylinders_mid);

	uint8 data_au8_cylinders_rear[8]  = {0};
	data_au8_cylinders_rear[0] = referenceCurrentPortA[BR] >>8;
	data_au8_cylinders_rear[1] = referenceCurrentPortA[BR];
	data_au8_cylinders_rear[2] = referenceCurrentPortB[BR] >>8;
	data_au8_cylinders_rear[3] = referenceCurrentPortB[BR];
	data_au8_cylinders_rear[4] = referenceCurrentPortA[BL] >> 8;
	data_au8_cylinders_rear[5] = referenceCurrentPortA[BL];
	data_au8_cylinders_rear[6] = referenceCurrentPortB[BL] >>8;
	data_au8_cylinders_rear[7] = referenceCurrentPortB[BL];
	can_sendData(CANChannel, backID, CAN_EXD_DU8, 8, data_au8_cylinders_rear);

}

void PAASendRealCurrentOnCAN(uint8 CANChannel, uint32 frontID, uint32 middleID, uint32 backID) {
	out_ts out_s1;
	out_ts out_s2;
	out_ts out_s3;
	out_ts out_s4;
	uint16 i_mA_LeftA;
	uint16 i_mA_LeftB;
	uint16 i_mA_RightA;
	uint16 i_mA_RightB;

	//FRONT
	out_getStatusxt(OUT_3_POH, &out_s1); // obtain the data in output port 11 and save it to pointer out_s1
	out_getStatusxt(OUT_4_POH, &out_s2);
	i_mA_LeftA = out_s1.out_po_s.i_mA_u16;  //actual current in mA
	i_mA_LeftB = out_s2.out_po_s.i_mA_u16; //actual current in mA
	out_getStatusxt(OUT_1_POH, &out_s3); // obtain the data in output port 11 and save it to pointer out_s1
	out_getStatusxt(OUT_2_POH, &out_s4);
	i_mA_RightA = out_s3.out_po_s.i_mA_u16;  //actual current in mA
	i_mA_RightB = out_s4.out_po_s.i_mA_u16; //actual current in mA
	uint8 data_au8_currentCylinders[8];
	data_au8_currentCylinders[0] = i_mA_LeftA;
	data_au8_currentCylinders[1] = i_mA_LeftA >> 8;
	data_au8_currentCylinders[2] = i_mA_LeftB;
	data_au8_currentCylinders[3] = i_mA_LeftB >> 8;
	data_au8_currentCylinders[4] = i_mA_RightA;
	data_au8_currentCylinders[5] = i_mA_RightA >> 8;
	data_au8_currentCylinders[6] = i_mA_RightB;
	data_au8_currentCylinders[7] = i_mA_RightB >> 8;
	if (0 == can_sendData(CANChannel, frontID, CAN_EXD_DU8, 8, data_au8_currentCylinders)) {}

	//MID
	out_getStatusxt(OUT_7_POH, &out_s1); // obtain the data in output port 11 and save it to pointer out_s1
	out_getStatusxt(OUT_8_POH, &out_s2);
	i_mA_LeftA = out_s1.out_po_s.i_mA_u16;  //actual current in mA
	i_mA_LeftB = out_s2.out_po_s.i_mA_u16; //actual current in mA
	out_getStatusxt(OUT_5_POH, &out_s3); // obtain the data in output port 11 and save it to pointer out_s1
	out_getStatusxt(OUT_6_POH, &out_s4);
	i_mA_RightA = out_s3.out_po_s.i_mA_u16;  //actual current in mA
	i_mA_RightB = out_s4.out_po_s.i_mA_u16; //actual current in mA
	// uint8 data_au8_currentCylinders[8];
	data_au8_currentCylinders[0] = i_mA_LeftA;
	data_au8_currentCylinders[1] = i_mA_LeftA >> 8;
	data_au8_currentCylinders[2] = i_mA_LeftB;
	data_au8_currentCylinders[3] = i_mA_LeftB >> 8;
	data_au8_currentCylinders[4] = i_mA_RightA;
	data_au8_currentCylinders[5] = i_mA_RightA >> 8;
	data_au8_currentCylinders[6] = i_mA_RightB;
	data_au8_currentCylinders[7] = i_mA_RightB >> 8;
	if (0 == can_sendData(CANChannel, middleID, CAN_EXD_DU8, 8, data_au8_currentCylinders)) {}

	//BACK
	out_getStatusxt(OUT_11_POH, &out_s1); // obtain the data in output port 11 and save it to pointer out_s1
	out_getStatusxt(OUT_12_POH, &out_s2);
	i_mA_LeftA = out_s1.out_po_s.i_mA_u16;  //actual current in mA
	i_mA_LeftB = out_s2.out_po_s.i_mA_u16; //actual current in mA
	out_getStatusxt(OUT_9_POH, &out_s3); // obtain the data in output port 11 and save it to pointer out_s1
	out_getStatusxt(OUT_10_POH, &out_s4);
	i_mA_RightA = out_s3.out_po_s.i_mA_u16;  //actual current in mA
	i_mA_RightB = out_s4.out_po_s.i_mA_u16; //actual current in mA
	// uint8 data_au8_currentCylinders[8];
	data_au8_currentCylinders[0] = i_mA_LeftA;
	data_au8_currentCylinders[1] = i_mA_LeftA >> 8;
	data_au8_currentCylinders[2] = i_mA_LeftB;
	data_au8_currentCylinders[3] = i_mA_LeftB >> 8;
	data_au8_currentCylinders[4] = i_mA_RightA;
	data_au8_currentCylinders[5] = i_mA_RightA >> 8;
	data_au8_currentCylinders[6] = i_mA_RightB;
	data_au8_currentCylinders[7] = i_mA_RightB >> 8;
	if (0 == can_sendData(CANChannel, backID, CAN_EXD_DU8, 8, data_au8_currentCylinders)) {}
}





