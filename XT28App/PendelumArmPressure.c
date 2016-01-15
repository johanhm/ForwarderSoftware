#include "PendelumArmPressure.h"
#include "api_lib_basic.h"
#include <math.h>
#include "XT28CANSupport.h"
#include "PendelumArmPosition.h"
#include "XT28HardwareConstants.h"

// Pressure sensor index
#define ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_A		0
#define ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_B		1
#define ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_A		2
#define ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_B		3
#define ANALOG_MID_RIGHT_PENDULUM_PRESSURE_A		4
#define ANALOG_MID_RIGHT_PENDULUM_PRESSURE_B		5
#define ANALOG_MID_LEFT_PENDULUM_PRESSURE_A			6
#define ANALOG_MID_LEFT_PENDULUM_PRESSURE_B			7
#define ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_A		8
#define ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_B		9
#define ANALOG_REAR_LEFT_PENDULUM_PRESSURE_A		10
#define ANALOG_REAR_LEFT_PENDULUM_PRESSURE_B		11
#define INDEX_SIZE_PRESSURESENS						12

//Private prototytpes
static void lowPassFilterPressureSensor(void);
static void calculateForceOnCylinderChambers(void);
static void calculateLoadForceOnCylinder(void);
static void calculateVerticalForceOnWheelAndTotalMass(void);

static float forceRelationshipFromLoadToGround(uint16 cylinderPoss_mm);
static sint32 convertCylinderLoadForceToVericalOnWheel(uint16 cylinderPoss_mm, sint16 cylinderLoadForce);
static sint32 convertVerticalForceOnWheelToCylinderLoadForce(uint16 cylinderPoss_mm, sint32 verticalForce);

static void calculateMassCenterLocation(void);
static void calculateOptimalForceForAllWheels(void);

// Start of implementations
void PAPRConfigurePressureSensorsVoltageInput(void) {

	/*
    uint16 uLowerStateThreshold_u16 = 1000;
    uint16 uUpperStateThreshold_u16 = 4000;
    uint16 tiStateDebounce_u16      = 100;
    uint16 uLowerDiagThreshold_u16  = 200;
    uint16 uUpperDiagThreshold_u16  = 4800;
    uint16 tiDiagDebounce_u16       = 200;
	 */

	/* pressure sensors 7-18 */
	in_cfgVoltageInput(IN_7_AIV, 1000, 4000, 100, 200, 4800, 200); //Front right A
	in_cfgVoltageInput(IN_8_AIV, 1000, 4000, 100, 200, 4800, 200); //Front right B
	in_cfgVoltageInput(IN_9_AIV, 1000, 4000, 100, 200, 4800, 200); //Front left A
	in_cfgVoltageInput(IN_10_AIV, 1000, 4000, 100, 200, 4800, 200); //Front left B
	in_cfgVoltageInput(IN_11_AIV, 1000, 4000, 100, 200, 4800, 200); //Mid right A
	in_cfgVoltageInput(IN_12_AIV, 1000, 4000, 100, 200, 4800, 200); //Mid right B
	in_cfgVoltageInput(IN_13_AIV, 1000, 4000, 100, 200, 4800, 200); //Mid left A
	in_cfgVoltageInput(IN_14_AIV, 1000, 4000, 100, 200, 4800, 200); //Mid left B
	in_cfgVoltageInput(IN_15_AIV, 1000, 4000, 100, 200, 4800, 200); //Rear right A
	in_cfgVoltageInput(IN_16_AIV, 1000, 4000, 100, 200, 4800, 200); //Rear right B
	in_cfgVoltageInput(IN_17_AIV, 1000, 4000, 100, 200, 4800, 200); //Rear left A
	in_cfgVoltageInput(IN_18_AIV, 1000, 4000, 100, 200, 4800, 200); //Rear left B

}

static volatile uint16 pressureData_mV[INDEX_SIZE_PRESSURESENS]  = {0};
static volatile uint16 pressureData_Bar[INDEX_SIZE_PRESSURESENS] = {0};

void PAPRUppdatePressureData(void) {
	//read Pressure sensors and calculate Cylinder Forces
	pressureData_mV[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_A] = in(IN_8_AIV);
	pressureData_mV[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_B] = in(IN_7_AIV);
	pressureData_mV[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_A]  = in(IN_10_AIV);
	pressureData_mV[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_B]  = in(IN_9_AIV);
	pressureData_mV[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_A]   = in(IN_11_AIV);
	pressureData_mV[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_B]   = in(IN_14_AIV);
	pressureData_mV[ANALOG_MID_LEFT_PENDULUM_PRESSURE_A]    = in(IN_13_AIV);
	pressureData_mV[ANALOG_MID_LEFT_PENDULUM_PRESSURE_B]    = in(IN_12_AIV);
	pressureData_mV[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_A]  = in(IN_15_AIV);
	pressureData_mV[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_B]  = in(IN_18_AIV);
	pressureData_mV[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_A]   = in(IN_17_AIV);
	pressureData_mV[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_B]   = in(IN_16_AIV);

	//Scale pressures into KiloPascals for sending  [KPa]
	uint8 x = 0;
	for(x = 0; x < INDEX_SIZE_PRESSURESENS; x++) {
		pressureData_Bar[x] = (float)pressureData_mV[x] * 6.25 - 3125;
	}

	//Low pass filter pressure signals
	lowPassFilterPressureSensor();
}

static void lowPassFilterPressureSensor(void) {
	static uint32 pressureDataLast_Bar[INDEX_SIZE_PRESSURESENS];
	float alpha = 0.9938;

	uint8 x = 0;
	for (x = 0; x < INDEX_SIZE_PRESSURESENS; x++) {
		pressureData_Bar[x]      = alpha * pressureDataLast_Bar[x] + (1-alpha) * pressureData_Bar[x];
		pressureDataLast_Bar[x] = pressureData_Bar[x];
	}
}

void PAPRUppdateForceOnWheelsData(void) {

	//Calculate corresponding forces at cylinder chambers and total
	calculateForceOnCylinderChambers();

	//Calculate Load force Fa-Fb decaN  (N/10)
	calculateLoadForceOnCylinder();

	calculateVerticalForceOnWheelAndTotalMass();

	calculateMassCenterLocation();

	calculateOptimalForceForAllWheels();
}

static uint32 forceChamberData[INDEX_SIZE_PRESSURESENS] = {0};
static void calculateForceOnCylinderChambers(void) {
	uint8 x = 0;
	for(x = 0; x < INDEX_SIZE_PRESSURESENS; x++) {
		if(x % 2 == 0) {
			forceChamberData[x] = 100 * pressureData_Bar[x] * (float)CYLINDER_PUSH_AREA_SIDE_A1_m2;
		}//100*KPa*m^2= deca N (N/10)
		else {
			forceChamberData[x] = 100 * pressureData_Bar[x] * (float)CYLINDER_PUSH_AREA_SIDE_B2_m2;
		}//100*KPa*m^2= deca N  (N/10)
	}
}

static sint32 messuredForceCylinderLoad_deciN[SUM_WHEELS] = {0};
static void calculateLoadForceOnCylinder(void) {
	uint8 x = 0;
	uint8 i = 0;
	for(x = 0; x <SUM_WHEELS; x++) {
		//Load_force[x] = (forceData[i] - forceData[i+1]);
		messuredForceCylinderLoad_deciN[x] = (forceChamberData[i] - forceChamberData[i+1]);
		i = i + 2;
	}
}

static sint32 calculatedVerticalForceOnWheel[SUM_WHEELS] = {0};
static sint32 sumOfVerticalForce = 0;
static void calculateVerticalForceOnWheelAndTotalMass(void) {
	int wheel = 0;
	sumOfVerticalForce = 0;
	//Get vertical force depending on pendulum arm current position
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		calculatedVerticalForceOnWheel[wheel] = convertCylinderLoadForceToVericalOnWheel(PAPOSGetPosDataForWheel_mm(wheel), messuredForceCylinderLoad_deciN[wheel]);
		sumOfVerticalForce = sumOfVerticalForce + calculatedVerticalForceOnWheel[wheel];
	}  //Get vertical force depending on pendulum arm current position
}

void PAPRSendPressureDataOnCAN(uint8 CANChannel, uint32 backID, uint32 middleID, uint32 frontID) {
	CANSend_uint16( CANChannel, backID,
			pressureData_Bar[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_A],
			pressureData_Bar[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_B],
			pressureData_Bar[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_A],
			pressureData_Bar[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_B]
	);
	CANSend_uint16( CANChannel, middleID,
			pressureData_Bar[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_A],
			pressureData_Bar[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_B],
			pressureData_Bar[ANALOG_MID_LEFT_PENDULUM_PRESSURE_A],
			pressureData_Bar[ANALOG_MID_LEFT_PENDULUM_PRESSURE_B]
	);
	CANSend_uint16( CANChannel, frontID,
			pressureData_Bar[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_A],
			pressureData_Bar[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_B],
			pressureData_Bar[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_A],
			pressureData_Bar[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_B]
	);
}

void PAPRSendCylinderForceOnCAN(uint8 CANChannel, uint32 backID, uint32 middleID, uint32 frontID) {
	CANSend_uint16( CANChannel, backID,
			forceChamberData[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_A],
			forceChamberData[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_B],
			forceChamberData[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_A],
			forceChamberData[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_B]
	);
	CANSend_uint16( CANChannel, middleID,
			forceChamberData[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_A],
			forceChamberData[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_B],
			forceChamberData[ANALOG_MID_LEFT_PENDULUM_PRESSURE_A],
			forceChamberData[ANALOG_MID_LEFT_PENDULUM_PRESSURE_B]
	);
	CANSend_uint16( CANChannel, frontID,
			forceChamberData[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_A],
			forceChamberData[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_B],
			forceChamberData[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_A],
			forceChamberData[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_B]
	);
}

void PAPRSendCylinderLoadForceOnCAN(uint8 CANChannel, uint32 middleAndBackID, uint32 frontID) {

	CANSend_sint16( CANChannel, middleAndBackID,
			messuredForceCylinderLoad_deciN[MR],
			messuredForceCylinderLoad_deciN[ML],
			messuredForceCylinderLoad_deciN[BR],
			messuredForceCylinderLoad_deciN[BL]
	);

	uint8 data_au8_sms_13[4] = {0}; //Load force
	//Construct msg SMS 13
	data_au8_sms_13[0] = messuredForceCylinderLoad_deciN[FR];
	data_au8_sms_13[1] = messuredForceCylinderLoad_deciN[FR] >> 8;
	data_au8_sms_13[2] = messuredForceCylinderLoad_deciN[FL];
	data_au8_sms_13[3] = messuredForceCylinderLoad_deciN[FL] >> 8;

	can_sendData(CANChannel, frontID, CAN_EXD_DU8, 4, data_au8_sms_13);
}

void PAPRSendVerticalWheelForceOnCAN(uint8 CANChannel, uint32 middleAndBackID, uint32 frontID) {

	CANSend_sint16( CANChannel, middleAndBackID,
			calculatedVerticalForceOnWheel[MR],
			calculatedVerticalForceOnWheel[ML],
			calculatedVerticalForceOnWheel[BR],
			calculatedVerticalForceOnWheel[BL]
	);

	uint8 data_au8_sms_13[4] = {0}; //Load force
	//Construct msg SMS 13
	data_au8_sms_13[0] = calculatedVerticalForceOnWheel[FR];
	data_au8_sms_13[1] = calculatedVerticalForceOnWheel[FR] >> 8;
	data_au8_sms_13[2] = calculatedVerticalForceOnWheel[FL];
	data_au8_sms_13[3] = calculatedVerticalForceOnWheel[FL] >> 8;

	can_sendData(CANChannel, frontID, CAN_EXD_DU8, 4, data_au8_sms_13);

}

static float forceRelationshipFromLoadToGround(uint16 cylinderPoss_mm) {

	float bxy = 0.4991;
	float l1 = 1.008;
	float l3 = 1.211;
	float theta3 = 0.2983;
	float theta2 =  0.3370;
	float pi =  3.14159265358979323846;

	float stroke = 0.82 + (cylinderPoss_mm / 1000.0);
	float alpha  = acos( (pow(bxy,2) + pow(l3,2) - pow(stroke,2)) / (2 * bxy * l3) );
	float theta  = alpha + theta2 + theta3;
	float theta1 = theta - theta3;
	float beta1  = acos((pow(stroke,2) + pow(bxy,2) - pow(l3,2)) / (2 * stroke * bxy));
	float gamma  = 0;
	float Load_force  = 1;
	float forceGroundRelationshipConstant = 0;

	if (beta1 < pi / 2 + theta2) {
		gamma = pi / 2 - (beta1 - theta2);
	} else {
		gamma = -(beta1 - (pi / 2 + theta2));
	}

	if (theta1 > pi/2) {
		forceGroundRelationshipConstant = Load_force * l3 * ((sin(gamma) * cos(theta1 - pi / 2) - cos(gamma) * sin(theta1 - pi / 2)) / (l1 * cos(theta - pi / 2)));
	} else if (gamma > 0) {
		forceGroundRelationshipConstant = Load_force * l3 * ((sin(gamma) * cos(pi / 2 - theta1) + cos(gamma) * sin(pi / 2 - theta1)) / (l1 * cos(pi / 2 - theta)));
	} else {
		forceGroundRelationshipConstant = Load_force * l3 * ((sin(gamma) * cos(pi / 2 - theta1) + cos(gamma) * sin(pi / 2 - theta1)) / (l1 * cos(pi / 2 - theta)));
	}
	return forceGroundRelationshipConstant;  // FG/FL Relationship
}

static sint32 convertCylinderLoadForceToVericalOnWheel(uint16 cylinderPoss_mm, sint16 cylinderLoadForce) {
	float relativeConstant = forceRelationshipFromLoadToGround(cylinderPoss_mm);
	sint32 forceOnWheelVertical_N = relativeConstant * cylinderLoadForce;
	return forceOnWheelVertical_N;
}

static sint32 convertVerticalForceOnWheelToCylinderLoadForce(uint16 cylinderPoss_mm, sint32 verticalForce) {
	float relativeConstant = forceRelationshipFromLoadToGround(cylinderPoss_mm);
	sint32 forceOnCylinder_N = verticalForce / relativeConstant;
	return forceOnCylinder_N;
}

// MARK: Mass center functions
static float massCenterLocationX_m = 0;
static float massCenterLocationY_m = 0;
static void calculateMassCenterLocation(void) {
	float lengthOfForwarder_m = LENGTH_OF_FORWARDER_m;
	float lengthToMidOfForwarder_m = LENGTH_TO_MID_OFF_FORWARDER_m;
	float widthOfForwarder_m = WIDTH_OF_FORWARDER_m;

	float sumOfForcesOnWheels_N = sumOfVerticalForce;

	massCenterLocationX_m = 1 / sumOfForcesOnWheels_N * (calculatedVerticalForceOnWheel[FR] + calculatedVerticalForceOnWheel[MR] + calculatedVerticalForceOnWheel[BR]) * widthOfForwarder_m;
	massCenterLocationY_m = 1 / sumOfForcesOnWheels_N * ((calculatedVerticalForceOnWheel[ML] + calculatedVerticalForceOnWheel[MR]) * lengthToMidOfForwarder_m + (calculatedVerticalForceOnWheel[BL] + calculatedVerticalForceOnWheel[BR]) * lengthOfForwarder_m);

	//temporary remove when logic is working
	massCenterLocationX_m = 0.47 * widthOfForwarder_m;
	massCenterLocationY_m = 0.34 * lengthOfForwarder_m;
	//end of temporare to remove
}

void PAPRSendMassCenterLocationOnCAN(uint CANChannel, uint32 ID) {
	float lengthOfForwarder_m = LENGTH_OF_FORWARDER_m;
	float widthOfForwarder_m = WIDTH_OF_FORWARDER_m;
	int convertToPercent = 100;
	sint16 massCenterLocationX_s16_10m = (massCenterLocationX_m / widthOfForwarder_m  * convertToPercent);
	sint16 massCenterLocationY_s16_10m = (massCenterLocationY_m / lengthOfForwarder_m * convertToPercent);
	CANSend_sint16(CANChannel, ID,
			massCenterLocationX_s16_10m,
			massCenterLocationY_s16_10m,
			0,
			0
	);
}

static int forceReferenceOptimalDistrubutionVertical_N[SUM_WHEELS] = {0};
static int forceRefOptDispForCylinderLoad_N[SUM_WHEELS] = {0};
static void calculateOptimalForceForAllWheels(void) {
	float lengthOfForwarder_m = LENGTH_OF_FORWARDER_m;
	float lengthToMidOfForwarder_m = LENGTH_TO_MID_OFF_FORWARDER_m;
	float widthOfForwarder_m = WIDTH_OF_FORWARDER_m;

	float kMidScalingConstant = (float)1 / 3;

	float kFront = (lengthOfForwarder_m - massCenterLocationY_m - (lengthOfForwarder_m - lengthToMidOfForwarder_m) * kMidScalingConstant) / lengthOfForwarder_m;
	float kLeft  = 1 - massCenterLocationX_m / widthOfForwarder_m;
	float kMid   = kMidScalingConstant;
	float kRear  = (massCenterLocationY_m - lengthToMidOfForwarder_m * kMidScalingConstant) / lengthOfForwarder_m;
	float kRight = massCenterLocationX_m / widthOfForwarder_m;

	//Optimal force ref vector vertical
	forceReferenceOptimalDistrubutionVertical_N[FL]  = kFront * kLeft  * sumOfVerticalForce;
	forceReferenceOptimalDistrubutionVertical_N[FR]  = kFront * kRight * sumOfVerticalForce;
	forceReferenceOptimalDistrubutionVertical_N[ML]  = kMid   * kLeft  * sumOfVerticalForce;
	forceReferenceOptimalDistrubutionVertical_N[MR]  = kMid   * kRight * sumOfVerticalForce;
	forceReferenceOptimalDistrubutionVertical_N[BL]  = kRear  * kLeft  * sumOfVerticalForce;
	forceReferenceOptimalDistrubutionVertical_N[BR]  = kRear  * kRight * sumOfVerticalForce;

	sint16 wheel = 0;
	//convert to optimalFOrceRef on cylinder. The check of calculations is corret calculate sum of vertical ref and compare to weight
	for (wheel = 0; wheel < 6; wheel++) {
		forceRefOptDispForCylinderLoad_N[wheel] = convertVerticalForceOnWheelToCylinderLoadForce(PAPOSGetPosDataForWheel_mm(wheel), forceReferenceOptimalDistrubutionVertical_N[wheel]);
	}
}

void PAPRSendOptimalForceRefOnCAN(uint8 CANChannel, uint32 frontAndMiddleID, uint32 backID) {
	sint16 forceReferenceDispSum_N = 0;
	sint16 wheel = 0;
	//convert to optimalFOrceRef on cylinder.
	for (wheel = 0; wheel < 6; wheel++) {
		forceReferenceDispSum_N = forceReferenceDispSum_N + forceReferenceOptimalDistrubutionVertical_N[wheel];
	}

	CANSend_sint16(CANChannel, frontAndMiddleID,
			forceRefOptDispForCylinderLoad_N[FL],
			forceRefOptDispForCylinderLoad_N[FR],
			forceRefOptDispForCylinderLoad_N[ML],
			forceRefOptDispForCylinderLoad_N[MR]
	);
	CANSend_sint16(CANChannel, backID,
			forceRefOptDispForCylinderLoad_N[BL],
			forceRefOptDispForCylinderLoad_N[BR],
			sumOfVerticalForce,
			forceReferenceDispSum_N
	);
}

void PAPRSendForceErrorPercentageOnCAN(uint8 CANChannel, uint32 frontAndMiddleID, uint32 backID) {
	sint32 wheel = 0;
	sint32 forceErrorInPercent[SUM_WHEELS] = {0};
	int convertToPercent = 100;
	for (wheel = 0; wheel < SUM_WHEELS; wheel++) {
		forceErrorInPercent[wheel] = (float)( (float)(forceRefOptDispForCylinderLoad_N[wheel] - messuredForceCylinderLoad_deciN[wheel]) / (float)forceRefOptDispForCylinderLoad_N[wheel] );
		forceErrorInPercent[wheel] = forceErrorInPercent[wheel] * convertToPercent;
	}
	CANSend_sint16(CANChannel, frontAndMiddleID,
			forceErrorInPercent[FL],
			forceErrorInPercent[FR],
			forceErrorInPercent[ML],
			forceErrorInPercent[MR]
	);
	CANSend_sint16(CANChannel, backID,
			forceErrorInPercent[BL],
			forceErrorInPercent[BR],
			0,
			0
	);
}

int PAPRGetOptimalReferenceForceForWheel_N(uint8 wheelNumber) {
	return forceRefOptDispForCylinderLoad_N[wheelNumber];
}






