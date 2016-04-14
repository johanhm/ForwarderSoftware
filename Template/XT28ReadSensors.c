/*
 * XT28ReadSensors.c
 *
 *  Created on: 23 nov. 2015
 *      Author: ladmin
 */

#include "ActiveDamping.h"

//#include "XT28ReadSensorsPrivate.h"

//private functions

// Used by pressure sensor task read
void lowPassFilterPressureSensor(void);
void calculateForceOnCylinderChambers(void);
void calculateLoadForceOnCylinderWheel(void);

// Sensor task 10ms i think
void uppdatePosSensorsData(void);
void uppdateIMUSensorData(void);

//IMU
void filterIMUSignals(void);

// Related to calculating the optimal reference force
void massCenterLocationAndSendOnCAN(void);
void calculateOptimalForceForAllWheelsAndSendOnCAN(void);
void calculateForceErrorPercentageAndSendOnCAN1(void);
void sendSupplyVoltageOnCAN1(void);

// RF,  LF,  RM,  LM,  RB,  LB
static uint16 minPos[INDEX_SIZE_WHEELS] = {1061, 1199, 1115, 1108, 1105, 1068}; //current mV
static uint16 maxPos[INDEX_SIZE_WHEELS] = {3864, 4200, 4126, 4039, 4096, 4046}; //current mV


// Pressure sensor task and related functions
void readPressureSensorsTask(void)  //Read Pressure sensors at 1000hz
{
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
	pressureData_mV[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_A]   = in(IN_17_AIV); //changed from 17
	pressureData_mV[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_B]   = in(IN_16_AIV); //changed from 18

	//Scale pressures into KiloPascals for sending  [KPa]
	uint8 x = 0;
	for(x = 0; x < INDEX_SIZE_PRESSURESENS; x++) {
		pressureData[x] = (float)pressureData_mV[x] * 6.25 - 3125;
	}


	//sl_debug_1 = pressureData[ANALOG_MID_LEFT_PENDULUM_PRESSURE_A];
	//sl_debug_3 = pressureData[ANALOG_MID_LEFT_PENDULUM_PRESSURE_B];

	//Low pass filter pressure signals
	lowPassFilterPressureSensor();

	//sl_debug_2 = pressureData[ANALOG_MID_LEFT_PENDULUM_PRESSURE_A];
	//sl_debug_4 = pressureData[ANALOG_MID_LEFT_PENDULUM_PRESSURE_B];

	//Calculate corresponding forces at cylinder chambers and total
	calculateForceOnCylinderChambers();

	//Calculate Load force Fa-Fb decaN  (N/10)
	calculateLoadForceOnCylinderWheel();

}//end read_Sensor_task

//Pos sensor task and related functions
void readPositionSensorsAndIMUTask(void)  //Read position sensors at 20hz
{
	uppdatePosSensorsData();
	uppdateIMUSensorData();
}

void lowPassFilterPressureSensor(void) {
	uint8 x = 0;
	for(x = 0; x < INDEX_SIZE_PRESSURESENS; x++) {
		pressureData[x]      = alpha * pressureData_last[x] + (1-alpha) * pressureData[x];
		pressureData_last[x] = pressureData[x];
	}
}

void calculateForceOnCylinderChambers(void) {
	uint8 x = 0;
	for(x = 0; x < INDEX_SIZE_PRESSURESENS; x++)
	{
		if(x % 2 == 0) {
			forceData[x] = 100 * pressureData[x] * (float)CYLINDER_PUSH_AREA_SIDE_A1_m2;
		}//100*KPa*m^2= deca N (N/10)
		else {
			forceData[x] = 100 * pressureData[x] * (float)CYLINDER_PUSH_AREA_SIDE_B2_m2;
		}//100*KPa*m^2= deca N  (N/10)
	}
}

void calculateLoadForceOnCylinderWheel(void) {
	uint8 x = 0;
	uint8 i = 0;
	for(x = 0; x <INDEX_SIZE_WHEELS; x++)
	{
		//Load_force[x] = (forceData[i] - forceData[i+1]);
		messuredForceCylinderLoad_deciN[x] = (forceData[i] - forceData[i+1]);
		i = i + 2;
	}
}

void uppdatePosSensorsData(void) {

	uint8 x = 0; //index used in FOR loops

	//////////////////////read Position sensors  and calculate velocities
	//Save Pos(k-1)
	for (x = 0; x < 6; x++) {
		posData_last[x] = posData[x];
	}

	//Get new sensor readings and scale from mV to mm
	posData_mV[ANALOG_RIGHT_FRONT_PENDULUMARM] = in(IN_1_AIV);
	posData_mV[ANALOG_LEFT_FRONT_PENDULUMARM]  = in(IN_2_AIV);
	posData_mV[ANALOG_RIGHT_MID_PENDULUMARM]   = in(IN_3_AIV);
	posData_mV[ANALOG_LEFT_MID_PENDULUMARM]    = in(IN_4_AIV);
	posData_mV[ANALOG_RIGHT_BACK_PENDULUMARM]  = in(IN_6_AIV);
	posData_mV[ANALOG_LEFT_BACK_PENDULUMARM]   = in(IN_5_AIV);

	for (x = 0; x < 6 ;x++) {
		posData[x] = (float)((float)(posData_mV[x] - minPos[x]) / (maxPos[x] - minPos[x])) * 500;
	} //scale to mm

	//Save Vel(k-1);
	for (x = 0; x < 6; x++) {
		velData_last[x] = velData[x];
	}
	//Calculate Vel(k)
	for (x = 0; x < 6; x++) {
		velData[x] = a_vel * velData_last[x] + a_vel * kf * Ts * (posData[x] - posData_last[x]) / Ts;
	}

	//Observer for average chassis height
	Zc = 0;
	for (x = 0; x < 6; x++) {
		Zc = Zc + posData[x];
	}
	Zc = Zc / 6;

	Zcdot = 0;
	for (x = 0; x < 6; x++) {
		Zcdot = Zcdot + velData[x];
	}
	Zcdot = Zcdot / 6;  //Observer for average chassis height

}

void uppdateIMUSensorData(void) {

	// Filter IMU
	filterIMUSignals();

	// Some other stuff
	uint8 x = 0; //index used in FOR loops

	//Calculate estimate of velocity of Zi chassis mounting points (where the cylinder is attached) using the Gyro measurements
	//Calculate estimate of position of Zi chassis mounting points (where the cylinder is attached) using the Accelerometer measurements

	for (x = 0; x < 6; x++) {
		Zi_pos[x] = (float)(b_geo[x] * (sin(Phi_rad) * cos(Theta_rad)) + a_geo[x] * sin(Theta_rad));
		Zi_vel[x] = b_geo[x] * (sin(Gyro_Phi_rad) * cos(Gyro_Theta_rad)) + a_geo[x] * sin(Gyro_Theta_rad);
	}  //Calculate positions and velocities



	//Low pass filter chassiss velocities signals, low pass filter chassis position signals
	for (x = 0; x < INDEX_SIZE_WHEELS; x++) {
		Zi_pos[x]      = alphapos * Zi_pos_last[x] + (1 - alphapos) * Zi_pos[x]; //Low pass filter positions
		Zi_pos_last[x] = Zi_pos[x];
	}

	//Calculate cylinder flows in L/min and send
	for (x = 0; x < 6; x++) {
		if (velData[x] >= 0) {
			Cyl_flow[x] = velData[x] * CYLINDER_PUSH_AREA_SIDE_A1_m2 * 60;
		}
		else if (velData[x] < 0) {
			Cyl_flow[x] = (-1 * velData[x]) * CYLINDER_PUSH_AREA_SIDE_B2_m2 * 60;
		}
	}
}

void filterIMUSignals(void) {

	// Franks and brunos calculation and filter of angle, still here for reference on CAN
	Theta_deg = (float)(ACCELY_RAW * 900) / 1800.0;  //ANgle in theta axis deg*10
	Phi_deg   = (float)(ACCELX_RAW * 900) / -1800.0;   //Angle in phi axis deg*10

	//Low pass filter
	Theta_deg      = alphapos * Theta_deg_last + (1-alphapos) * Theta_deg; //Low pass filter theta
	Theta_deg_last = Theta_deg;
	Phi_deg        = alphapos * Phi_deg_last + (1-alphapos) * Phi_deg; //Low pass filter phi
	Phi_deg_last   = Phi_deg;
	// end Frank and Bruno angle calc


	// Complementary filter variabels Static
	static volatile sint32 filterAnglePhi = 0;
	static volatile sint32 filterAngleOldPhi = 0;
	//static volatile sint32 integratedGyroAngleCalcPhi = 0; /* This variable is/was for debugging / control angle. */

	static volatile sint32 filterAngleTheta = 0;
	static volatile sint32 filterAngleOldTheta = 0;
	static volatile sint32 integratedGyroAngleCalcTheta = 0;

	int multConstantForFilter = 1000;
	float readSensorTaskPeriodTime = 0.01;

	// Update angle raw values, Complementary filter

	// Phi
	float volatile accAnglePhi = atan((float)ACCELX_RAW / ACCELZ_RAW) * 180 / M_PI * multConstantForFilter;
	float volatile gyroAnglePhi = (float)Gyro_Phi_RAW / 50 * readSensorTaskPeriodTime * multConstantForFilter;
	//integratedGyroAngleCalcPhi = integratedGyroAngleCalcPhi + gyroAnglePhi;

	filterAnglePhi    = (filterAngleOldPhi + gyroAnglePhi) * 0.99 + 0.01 * accAnglePhi;
	filterAngleOldPhi = filterAnglePhi;

	// Theta
	float volatile accAngleTheta = -atan((float)ACCELY_RAW / ACCELZ_RAW) * 180 / M_PI * multConstantForFilter;
	float volatile gyroAngleTheta = (float)Gyro_Theta_RAW / 50 * readSensorTaskPeriodTime * multConstantForFilter; // 50 is the convert from whatever to degre/s
	integratedGyroAngleCalcTheta = integratedGyroAngleCalcTheta + gyroAngleTheta;

	filterAngleTheta    = (filterAngleOldTheta + gyroAngleTheta) * 0.99 + 0.01 * accAngleTheta;
	filterAngleOldTheta = filterAngleTheta;

	// Uppdate from old Theta_deg to the new one, the old one should be removed but is keept for now for future reference and showof
	//sint32 Theta_degOLD = Theta_deg;
	//sint32 Phi_degOLD = Phi_deg;

	// Uppdating angles to the new filter calculated angle.
	Theta_deg = filterAngleTheta * 10 / multConstantForFilter;
	Phi_deg = filterAnglePhi * 10 / multConstantForFilter;

	//debugg variaqbels

	sl_debug_1 = filterAnglePhi;
	sl_debug_2 = accAnglePhi;
	sl_debug_3 = gyroAnglePhi;
	sl_debug_4 = Phi_deg * 1000 / 10;

	// end debugging filter testing

	Theta_rad = (float)Theta_deg * pi / 1800.0;			//Convert to radians
	Phi_rad   = (float)Phi_deg   * pi / 1800.0;			//Convert to radians

	// Gyro, this signal dosent occilate so no filter needed.
	Gyro_Phi_deg   = Gyro_Phi_RAW / 50;				//Angular velocity in deg/s from gyroscope  (Note:Divide RAW by 50 to get deg/s , negative sign to keep vehicle sign convention)
	Gyro_Theta_deg = Gyro_Theta_RAW / 50; 			//Angular velocity in deg/s from gyroscope
	Gyro_Phi_rad   = (float)Gyro_Phi_deg * pi / 180.0;				//convert to rad/s
	Gyro_Theta_rad = (float)Gyro_Theta_deg * pi / 180.0;	     	//convert to rad/s

}

void sendSupplyVoltageOnCAN1(void) {
	sint16 batterySupplyVoltage = sys_getSupply(VB);
	sint16 sensorSupplyVoltage1 = sys_getSupply(VSS_1);
	sint16 sensorSupplyVoltage3 = sys_getSupply(VSS_3);
	sendCAN1_sint16(0x18FF1060, batterySupplyVoltage, sensorSupplyVoltage1, sensorSupplyVoltage3, 0);
}

// Send all sensor values on CAN
void send_CAN_sensors_values_Task(void)
{

	sendSupplyVoltageOnCAN1();

	//Construct msg SMS 1
	uint8 data_au8_sms_1[8];
	data_au8_sms_1[0] = pressureData[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_A];
	data_au8_sms_1[1] = pressureData[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_A]>>8;
	data_au8_sms_1[2] = pressureData[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_B];
	data_au8_sms_1[3] = pressureData[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_B]>>8;
	data_au8_sms_1[4] = pressureData[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_A];
	data_au8_sms_1[5] = pressureData[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_A]>>8;
	data_au8_sms_1[6] = pressureData[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_B];
	data_au8_sms_1[7] = pressureData[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_B]>>8;

	//Construct msg SMS 2
	uint8 data_au8_sms_2[8];
	data_au8_sms_2[0] = pressureData[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_A];
	data_au8_sms_2[1] = pressureData[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_A]>>8;
	data_au8_sms_2[2] = pressureData[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_B];
	data_au8_sms_2[3] = pressureData[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_B]>>8;
	data_au8_sms_2[4] = pressureData[ANALOG_MID_LEFT_PENDULUM_PRESSURE_A];
	data_au8_sms_2[5] = pressureData[ANALOG_MID_LEFT_PENDULUM_PRESSURE_A]>>8;
	data_au8_sms_2[6] = pressureData[ANALOG_MID_LEFT_PENDULUM_PRESSURE_B];
	data_au8_sms_2[7] = pressureData[ANALOG_MID_LEFT_PENDULUM_PRESSURE_B]>>8;

	//Construct msg SMS 3
	uint8 data_au8_sms_3[8];
	data_au8_sms_3[0] = pressureData[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_A];
	data_au8_sms_3[1] = pressureData[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_A]>>8;
	data_au8_sms_3[2] = pressureData[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_B];
	data_au8_sms_3[3] = pressureData[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_B]>>8;
	data_au8_sms_3[4] = pressureData[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_A];
	data_au8_sms_3[5] = pressureData[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_A]>>8;
	data_au8_sms_3[6] = pressureData[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_B];
	data_au8_sms_3[7] = pressureData[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_B]>>8;

	/// Send though CAN either scaled position (mm) or Raw (mv) Value
	uint8 data_au8_sms_4[8];
	uint8 data_au8_sms_5[4];

	if(SEND_SCALED_POS==1) {   //Send scaled value
		//Construct msg SMS 4
		data_au8_sms_4[0] = posData[ANALOG_RIGHT_MID_PENDULUMARM];
		data_au8_sms_4[1] = posData[ANALOG_RIGHT_MID_PENDULUMARM]>>8;
		data_au8_sms_4[2] = posData[ANALOG_LEFT_MID_PENDULUMARM];
		data_au8_sms_4[3] = posData[ANALOG_LEFT_MID_PENDULUMARM]>>8;
		data_au8_sms_4[4] = posData[ANALOG_RIGHT_BACK_PENDULUMARM];
		data_au8_sms_4[5] = posData[ANALOG_RIGHT_BACK_PENDULUMARM]>>8;
		data_au8_sms_4[6] = posData[ANALOG_LEFT_BACK_PENDULUMARM];
		data_au8_sms_4[7] = posData[ANALOG_LEFT_BACK_PENDULUMARM]>>8;

		//Construct msg SMS 5
		data_au8_sms_5[0] = posData[ANALOG_RIGHT_FRONT_PENDULUMARM];
		data_au8_sms_5[1] = posData[ANALOG_RIGHT_FRONT_PENDULUMARM]>>8;
		data_au8_sms_5[2] = posData[ANALOG_LEFT_FRONT_PENDULUMARM];
		data_au8_sms_5[3] = posData[ANALOG_LEFT_FRONT_PENDULUMARM]>>8;
	}
	else  {  //Send mV value
		data_au8_sms_4[0] = posData_mV[ANALOG_RIGHT_MID_PENDULUMARM];
		data_au8_sms_4[1] = posData_mV[ANALOG_RIGHT_MID_PENDULUMARM]>>8;
		data_au8_sms_4[2] = posData_mV[ANALOG_LEFT_MID_PENDULUMARM];
		data_au8_sms_4[3] = posData_mV[ANALOG_LEFT_MID_PENDULUMARM]>>8;
		data_au8_sms_4[4] = posData_mV[ANALOG_RIGHT_BACK_PENDULUMARM];
		data_au8_sms_4[5] = posData_mV[ANALOG_RIGHT_BACK_PENDULUMARM]>>8;
		data_au8_sms_4[6] = posData_mV[ANALOG_LEFT_BACK_PENDULUMARM];
		data_au8_sms_4[7] = posData_mV[ANALOG_LEFT_BACK_PENDULUMARM]>>8;

		//Construct msg SMS 5
		data_au8_sms_5[0] = posData_mV[ANALOG_RIGHT_FRONT_PENDULUMARM];
		data_au8_sms_5[1] = posData_mV[ANALOG_RIGHT_FRONT_PENDULUMARM]>>8;
		data_au8_sms_5[2] = posData_mV[ANALOG_LEFT_FRONT_PENDULUMARM];
		data_au8_sms_5[3] = posData_mV[ANALOG_LEFT_FRONT_PENDULUMARM]>>8;
	}

	//Construct msg SMS 6
	uint8 data_au8_sms_6[8];
	data_au8_sms_6[0] = velData[ANALOG_RIGHT_MID_PENDULUMARM];
	data_au8_sms_6[1] = velData[ANALOG_RIGHT_MID_PENDULUMARM]>>8;
	data_au8_sms_6[2] = velData[ANALOG_LEFT_MID_PENDULUMARM];
	data_au8_sms_6[3] = velData[ANALOG_LEFT_MID_PENDULUMARM]>>8;
	data_au8_sms_6[4] = velData[ANALOG_RIGHT_BACK_PENDULUMARM];
	data_au8_sms_6[5] = velData[ANALOG_RIGHT_BACK_PENDULUMARM]>>8;
	data_au8_sms_6[6] = velData[ANALOG_LEFT_BACK_PENDULUMARM];
	data_au8_sms_6[7] = velData[ANALOG_LEFT_BACK_PENDULUMARM]>>8;

	//Construct msg SMS 7
	uint8 data_au8_sms_7[4];
	data_au8_sms_7[0] = velData[ANALOG_RIGHT_FRONT_PENDULUMARM];
	data_au8_sms_7[1] = velData[ANALOG_RIGHT_FRONT_PENDULUMARM]>>8;
	data_au8_sms_7[2] = velData[ANALOG_LEFT_FRONT_PENDULUMARM];
	data_au8_sms_7[3] = velData[ANALOG_LEFT_FRONT_PENDULUMARM]>>8;

	//Construct SMS 8,9,10
	uint8 data_au8_sms_8[8]={0};  //forceCylindersFront
	uint8 data_au8_sms_9[8]={0};    //forceCylindersMid
	uint8 data_au8_sms_10[8]={0};   //forceCylindersRear

	data_au8_sms_8[0]=forceData[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_A];
	data_au8_sms_8[1]=forceData[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_A]>>8;
	data_au8_sms_8[2]=forceData[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_B];
	data_au8_sms_8[3]=forceData[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_B]>>8;
	data_au8_sms_8[4]=forceData[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_A];
	data_au8_sms_8[5]=forceData[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_A]>>8;
	data_au8_sms_8[6]=forceData[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_B];
	data_au8_sms_8[7]=forceData[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_B]>>8;

	data_au8_sms_9[0]=forceData[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_A];
	data_au8_sms_9[1]=forceData[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_A]>>8;
	data_au8_sms_9[2]=forceData[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_B];
	data_au8_sms_9[3]=forceData[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_B]>>8;
	data_au8_sms_9[4]=forceData[ANALOG_MID_LEFT_PENDULUM_PRESSURE_A];
	data_au8_sms_9[5]=forceData[ANALOG_MID_LEFT_PENDULUM_PRESSURE_A]>>8;
	data_au8_sms_9[6]=forceData[ANALOG_MID_LEFT_PENDULUM_PRESSURE_B];
	data_au8_sms_9[7]=forceData[ANALOG_MID_LEFT_PENDULUM_PRESSURE_B]>>8;

	data_au8_sms_10[0]=forceData[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_A];
	data_au8_sms_10[1]=forceData[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_A]>>8;
	data_au8_sms_10[2]=forceData[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_B];
	data_au8_sms_10[3]=forceData[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_B]>>8;
	data_au8_sms_10[4]=forceData[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_A];
	data_au8_sms_10[5]=forceData[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_A]>>8;
	data_au8_sms_10[6]=forceData[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_B];
	data_au8_sms_10[7]=forceData[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_B]>>8;

	uint8 i = 0;
	uint8 data_au8_sms_11[6] = {0};   //Flow in cylinder L/min
	for (i = 0; i < 6; i++) {
		data_au8_sms_11[i] = Cyl_flow[i];
	}

	uint8 data_au8_sms_12[8] = {0}; //Load force
	uint8 data_au8_sms_13[4] = {0}; //Load force
	//Construct msg SMS 12
	data_au8_sms_12[0] = messuredForceCylinderLoad_deciN[ANALOG_RIGHT_MID_PENDULUMARM];
	data_au8_sms_12[1] = messuredForceCylinderLoad_deciN[ANALOG_RIGHT_MID_PENDULUMARM]>>8;
	data_au8_sms_12[2] = messuredForceCylinderLoad_deciN[ANALOG_LEFT_MID_PENDULUMARM];
	data_au8_sms_12[3] = messuredForceCylinderLoad_deciN[ANALOG_LEFT_MID_PENDULUMARM]>>8;
	data_au8_sms_12[4] = messuredForceCylinderLoad_deciN[ANALOG_RIGHT_BACK_PENDULUMARM];
	data_au8_sms_12[5] = messuredForceCylinderLoad_deciN[ANALOG_RIGHT_BACK_PENDULUMARM]>>8;
	data_au8_sms_12[6] = messuredForceCylinderLoad_deciN[ANALOG_LEFT_BACK_PENDULUMARM];
	data_au8_sms_12[7] = messuredForceCylinderLoad_deciN[ANALOG_LEFT_BACK_PENDULUMARM]>>8;

	//Construct msg SMS 13
	data_au8_sms_13[0] = messuredForceCylinderLoad_deciN[ANALOG_RIGHT_FRONT_PENDULUMARM];
	data_au8_sms_13[1] = messuredForceCylinderLoad_deciN[ANALOG_RIGHT_FRONT_PENDULUMARM]>>8;
	data_au8_sms_13[2] = messuredForceCylinderLoad_deciN[ANALOG_LEFT_FRONT_PENDULUMARM];
	data_au8_sms_13[3] = messuredForceCylinderLoad_deciN[ANALOG_LEFT_FRONT_PENDULUMARM]>>8;

	//Debugging for force controller
	uint8 debug1[8] = {0}; //
	uint8 debug2[8] = {0}; //
	uint8 debug3[8] = {0}; //
	//Construct Debugmsg 1

	debug1[0] = sl_debug_1;
	debug1[1] = sl_debug_1 >> 8;
	debug1[2] = sl_debug_1>>16;
	debug1[3] = sl_debug_1>>24;
	debug1[4] = sl_debug_2;
	debug1[5] = sl_debug_2>>8;
	debug1[6] = sl_debug_2>>16;
	debug1[7] = sl_debug_2>>24;

	//Construct Debugmsg 2
	debug2[0] = sl_debug_3;
	debug2[1] = sl_debug_3>>8;
	debug2[2] = sl_debug_3>>16;
	debug2[3] = sl_debug_3>>24;
	debug2[4] = sl_debug_4;
	debug2[5] = sl_debug_4>>8;
	debug2[6] = sl_debug_4>>16;
	debug2[7] = sl_debug_4>>24;

	//Construct Debugmsg 3
	debug3[0] =sl_debug_5;
	debug3[1] =sl_debug_5>>8;
	debug3[2] =sl_debug_5>>16;
	debug3[3] =sl_debug_5>>24;
	debug3[4] =sl_debug_6;
	debug3[5] =sl_debug_6>>8;
	debug3[6] =sl_debug_6>>16;
	debug3[7] =sl_debug_6>>24;

	if(0 == can_sendData(CAN_1,CAN_ID_DEBUG_MSG_1, CAN_EXD_DU8, 8,debug1)){}
	if(0 == can_sendData(CAN_1,CAN_ID_DEBUG_MSG_2, CAN_EXD_DU8, 8,debug2)){}
	if(0 == can_sendData(CAN_1,CAN_ID_DEBUG_MSG_3, CAN_EXD_DU8, 8,debug3)){}



	//send msg,
	//pressure on can3 for Transmission control

	if (0 == can_sendData(CAN_3, CAN_ID_SENSOR_INFO_SMS_1, CAN_EXD_DU8, 8, data_au8_sms_1)) {}
	if (0 == can_sendData(CAN_3, CAN_ID_SENSOR_INFO_SMS_2, CAN_EXD_DU8, 8, data_au8_sms_2)) {}
	if (0 == can_sendData(CAN_3, CAN_ID_SENSOR_INFO_SMS_3, CAN_EXD_DU8, 8, data_au8_sms_3)) {}

	if(SEND_PRESSURE == 1) {
		//pressure
		if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_1, CAN_EXD_DU8, 8, data_au8_sms_1)) {}
		if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_2, CAN_EXD_DU8, 8, data_au8_sms_2)) {}
		if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_3, CAN_EXD_DU8, 8, data_au8_sms_3)) {}

		sendCAN1_uint16(0x18FF1050,pressureData_mV[0],pressureData_mV[1],pressureData_mV[2],pressureData_mV[3]);
		sendCAN1_uint16(0x18FF1051,pressureData_mV[4],pressureData_mV[5],pressureData_mV[6],pressureData_mV[7]);
		sendCAN1_uint16(0x18FF1052,pressureData_mV[8],pressureData_mV[9],pressureData_mV[10],pressureData_mV[11]);
	}

	if(SEND_POS_AND_VEL == 1) {
		//Position data
		if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_4, CAN_EXD_DU8, 8, data_au8_sms_4)) {}
		if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_5, CAN_EXD_DU8, 4, data_au8_sms_5)) {}
		//vel data
		if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_6, CAN_EXD_DU8, 8, data_au8_sms_6)) {}
		if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_7, CAN_EXD_DU8, 4, data_au8_sms_7)) {}
	}

	if(SEND_FLOW==1) {
		//Cyl flow data
		if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_11, CAN_EXD_DU8, 6, data_au8_sms_11)) {}
	}

	if(SEND_FORCE==1){
		//Force Data
		// if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_8, CAN_EXD_DU8, 8, data_au8_sms_8)) {}
		// if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_9, CAN_EXD_DU8, 8, data_au8_sms_9)) {}
		// if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_10, CAN_EXD_DU8, 8, data_au8_sms_10)) {}

		//Load force
		if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_12, CAN_EXD_DU8, 8, data_au8_sms_12)) {}
		if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_13, CAN_EXD_DU8, 4, data_au8_sms_13)) {}
	}


	//IF CAN_TEST_ON then send scaled values on CAN MSGs
	if(CAN_TEST_ON==1){
		//Arrays for CAN msg sending
		uint8 data_au8_cylinders_front[8] = {0};
		uint8 data_au8_cylinders_mid[8]   = {0};
		uint8 data_au8_cylinders_rear[8]  = {0};

		data_au8_cylinders_front[INDEX_CAN_TEST_CYLINDER_RIGHT_A_1] = Ref_A[FR] >> 8;
		data_au8_cylinders_front[INDEX_CAN_TEST_CYLINDER_RIGHT_A_2] = Ref_A[FR];
		data_au8_cylinders_front[INDEX_CAN_TEST_CYLINDER_RIGHT_B_1] = Ref_B[FR] >>8;
		data_au8_cylinders_front[INDEX_CAN_TEST_CYLINDER_RIGHT_B_2] = Ref_B[FR];
		data_au8_cylinders_front[INDEX_CAN_TEST_CYLINDER_LEFT_A_1] 	= Ref_A[FL] >> 8;
		data_au8_cylinders_front[INDEX_CAN_TEST_CYLINDER_LEFT_A_2] 	= Ref_A[FL];
		data_au8_cylinders_front[INDEX_CAN_TEST_CYLINDER_LEFT_B_1] 	= Ref_B[FL] >>8;
		data_au8_cylinders_front[INDEX_CAN_TEST_CYLINDER_LEFT_B_2] 	= Ref_B[FL];

		if (0 == can_sendData(CAN_1, CAN_ID_TEST_CYLINDERS_FRONT, CAN_EXD_DU8, 8, data_au8_cylinders_front)) {}

		data_au8_cylinders_mid[INDEX_CAN_TEST_CYLINDER_LEFT_A_1]  = Ref_A[ML] >> 8;
		data_au8_cylinders_mid[INDEX_CAN_TEST_CYLINDER_LEFT_A_2]  = Ref_A[ML];
		data_au8_cylinders_mid[INDEX_CAN_TEST_CYLINDER_LEFT_B_1]  = Ref_B[ML] >> 8;
		data_au8_cylinders_mid[INDEX_CAN_TEST_CYLINDER_LEFT_B_2]  = Ref_B[ML];
		data_au8_cylinders_mid[INDEX_CAN_TEST_CYLINDER_RIGHT_A_1] = Ref_A[MR] >> 8;
		data_au8_cylinders_mid[INDEX_CAN_TEST_CYLINDER_RIGHT_A_2] = Ref_A[MR];
		data_au8_cylinders_mid[INDEX_CAN_TEST_CYLINDER_RIGHT_B_1] = Ref_B[MR] >> 8;
		data_au8_cylinders_mid[INDEX_CAN_TEST_CYLINDER_RIGHT_B_2] = Ref_B[MR];
		if (0 == can_sendData(CAN_1, CAN_ID_TEST_CYLINDERS_MID, CAN_EXD_DU8, 8, data_au8_cylinders_mid)) {}

		data_au8_cylinders_rear[INDEX_CAN_TEST_CYLINDER_LEFT_A_1]  = Ref_A[BL] >> 8;
		data_au8_cylinders_rear[INDEX_CAN_TEST_CYLINDER_LEFT_A_2]  = Ref_A[BL];
		data_au8_cylinders_rear[INDEX_CAN_TEST_CYLINDER_LEFT_B_1]  = Ref_B[BL] >>8;
		data_au8_cylinders_rear[INDEX_CAN_TEST_CYLINDER_LEFT_B_2]  = Ref_B[BL];
		data_au8_cylinders_rear[INDEX_CAN_TEST_CYLINDER_RIGHT_A_1] = Ref_A[BR] >>8;
		data_au8_cylinders_rear[INDEX_CAN_TEST_CYLINDER_RIGHT_A_2] = Ref_A[BR];
		data_au8_cylinders_rear[INDEX_CAN_TEST_CYLINDER_RIGHT_B_1] = Ref_B[BR] >>8;
		data_au8_cylinders_rear[INDEX_CAN_TEST_CYLINDER_RIGHT_B_2] = Ref_B[BR];
		if (0 == can_sendData(CAN_1, CAN_ID_TEST_CYLINDERS_REAR, CAN_EXD_DU8, 8, data_au8_cylinders_rear)) {}

	}


	//Send actual current via CAN
	//added stuff for the current send
	if(SEND_ACTUAL_CURRENT_CAN){
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
		data_au8_currentCylinders[1] = i_mA_LeftA>>8;
		data_au8_currentCylinders[2] = i_mA_LeftB;
		data_au8_currentCylinders[3] = i_mA_LeftB>>8;
		data_au8_currentCylinders[4] = i_mA_RightA;
		data_au8_currentCylinders[5] = i_mA_RightA>>8;
		data_au8_currentCylinders[6] = i_mA_RightB;
		data_au8_currentCylinders[7] = i_mA_RightB>>8;
		if (0 == can_sendData(CAN_1, CAN_ID_REF_CURRENT_FRONT, CAN_EXD_DU8, 8, data_au8_currentCylinders)) {}

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
		data_au8_currentCylinders[1] = i_mA_LeftA>>8;
		data_au8_currentCylinders[2] = i_mA_LeftB;
		data_au8_currentCylinders[3] = i_mA_LeftB>>8;
		data_au8_currentCylinders[4] = i_mA_RightA;
		data_au8_currentCylinders[5] = i_mA_RightA>>8;
		data_au8_currentCylinders[6] = i_mA_RightB;
		data_au8_currentCylinders[7] = i_mA_RightB>>8;
		if (0 == can_sendData(CAN_1, CAN_ID_REF_CURRENT_MID, CAN_EXD_DU8, 8, data_au8_currentCylinders)) {}

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
		if (0 == can_sendData(CAN_1, CAN_ID_REF_CURRENT_BACK, CAN_EXD_DU8, 8, data_au8_currentCylinders)) {}
	}

	//CAlculate and send vertical load force for every cylinder
	uint8 data_au8_sms_FORCE_VERTICAL1[8] = {0}; //Vertical force
	uint8 data_au8_sms_FORCE_VERTICAL2[4] = {0}; //Vertical force
	Weight = 0;
	for (i = 0; i < 6; i++) {
		forceVertical[i] = forceOnWheelVerticalFromCylinderLoad(posData[i], messuredForceCylinderLoad_deciN[i]);
		if (forceVertical[i] > 0) {
			Weight = Weight + forceVertical[i];
		}
	}  //Get vertical force depending on pendulum arm current position


	data_au8_sms_FORCE_VERTICAL1[0] = forceVertical[ANALOG_RIGHT_MID_PENDULUMARM];
	data_au8_sms_FORCE_VERTICAL1[1] = forceVertical[ANALOG_RIGHT_MID_PENDULUMARM]>>8;
	data_au8_sms_FORCE_VERTICAL1[2] = forceVertical[ANALOG_LEFT_MID_PENDULUMARM];
	data_au8_sms_FORCE_VERTICAL1[3] = forceVertical[ANALOG_LEFT_MID_PENDULUMARM]>>8;
	data_au8_sms_FORCE_VERTICAL1[4] = forceVertical[ANALOG_RIGHT_BACK_PENDULUMARM];
	data_au8_sms_FORCE_VERTICAL1[5] = forceVertical[ANALOG_RIGHT_BACK_PENDULUMARM]>>8;
	data_au8_sms_FORCE_VERTICAL1[6] = forceVertical[ANALOG_LEFT_BACK_PENDULUMARM];
	data_au8_sms_FORCE_VERTICAL1[7] = forceVertical[ANALOG_LEFT_BACK_PENDULUMARM]>>8;

	data_au8_sms_FORCE_VERTICAL2[0] = forceVertical[ANALOG_RIGHT_FRONT_PENDULUMARM];
	data_au8_sms_FORCE_VERTICAL2[1] = forceVertical[ANALOG_RIGHT_FRONT_PENDULUMARM]>>8;
	data_au8_sms_FORCE_VERTICAL2[2] = forceVertical[ANALOG_LEFT_FRONT_PENDULUMARM];
	data_au8_sms_FORCE_VERTICAL2[3] = forceVertical[ANALOG_LEFT_FRONT_PENDULUMARM]>>8;

	//Vertical force
	if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_14, CAN_EXD_DU8, 8, data_au8_sms_FORCE_VERTICAL1)) {}
	if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_15, CAN_EXD_DU8, 4, data_au8_sms_FORCE_VERTICAL2)) {}

	uint8 data_au8_sms_OBS[8] = {0}; //State observers
	data_au8_sms_OBS[0] = Zc;
	data_au8_sms_OBS[1] = Zc>>8;
	data_au8_sms_OBS[2] = Zcdot;
	data_au8_sms_OBS[3] = Zcdot >>8;
	data_au8_sms_OBS[4] = Theta_deg;
	data_au8_sms_OBS[5] = Theta_deg >> 8;
	data_au8_sms_OBS[6] = Phi_deg;
	data_au8_sms_OBS[7] = Phi_deg >> 8;

	if (0 == can_sendData(CAN_1, CAN_ID_SENSOR_INFO_SMS_16, CAN_EXD_DU8, 8, data_au8_sms_OBS)) {}

	//Send Zi chassis point vel data
	SEND_ARRAY_CAN1(CAN_ID_SENSOR_INFO_SMS_17,CAN_ID_SENSOR_INFO_SMS_18,Zi_vel,6);
	//Send Zi chassis point position data
	SEND_ARRAY_CAN1(CAN_ID_SENSOR_INFO_SMS_19,CAN_ID_SENSOR_INFO_SMS_20,Zi_pos,6);

	uint8 angleData_au8[6];
	angleData_au8[0] = ACCELX_RAW;
	angleData_au8[1] = ACCELX_RAW>>8;
	angleData_au8[2] = ACCELY_RAW;
	angleData_au8[3] = ACCELY_RAW>>8;
	angleData_au8[4] = ACCELZ_RAW;
	angleData_au8[5] = ACCELZ_RAW>>8;

	if (0 == can_sendData(CAN_1, 0x2FD, CAN_STD_DU8, 6, angleData_au8)) {}

	angleData_au8[0] = Gyro_Theta_RAW;
	angleData_au8[1] = Gyro_Theta_RAW>>8;
	angleData_au8[2] = Gyro_Phi_RAW;
	angleData_au8[3] = Gyro_Phi_RAW>>8;

	if (0 == can_sendData(CAN_1, 0x1FD, CAN_STD_DU8, 4, angleData_au8)) {}

	sendCAN1_sint16(CAN_ID_DEBUG_MSG_4, F_matrix[0], F_matrix[0] >> 16, F_matrix[1], F_matrix[1] >> 16);
	sendCAN1_sint16(CAN_ID_DEBUG_MSG_5, F_matrix[2], F_matrix[2] >> 16 ,0 ,0);

	massCenterLocationAndSendOnCAN();
	calculateOptimalForceForAllWheelsAndSendOnCAN();
}

// MARK: Mass center functions
volatile float massCenterLocationX_m = 0;
volatile float massCenterLocationY_m = 0;
volatile sint16 forceReferenceOptimalDistrubution_N[INDEX_SIZE_WHEELS] = {0};

void massCenterLocationAndSendOnCAN(void) {
	float lengthOfForwarder_m = 6.05;
	float lengthToMidOfForwarder_m = 3.70;
	float widthOfForwarder_m = 2.35;

	float sumOfForcesOnWheels_N = Weight;

	massCenterLocationX_m = 1 / sumOfForcesOnWheels_N * (forceVertical[FR] + forceVertical[MR] + forceVertical[BR]) * widthOfForwarder_m;
	massCenterLocationY_m = 1 / sumOfForcesOnWheels_N * ((forceVertical[ML] + forceVertical[MR]) * lengthToMidOfForwarder_m + (forceVertical[BL] + forceVertical[BR]) * lengthOfForwarder_m);

	sint16 massCenterLocationX_sint16_10m = (massCenterLocationX_m / widthOfForwarder_m  * 100);
	sint16 massCenterLocationY_sint16_10m = (massCenterLocationY_m / lengthOfForwarder_m * 100);

	sendCAN1_sint16(0x18FF1001, massCenterLocationX_sint16_10m, massCenterLocationY_sint16_10m, 0, 0);

	//temporary remove when logic is working
	massCenterLocationX_m = 0.47 * widthOfForwarder_m;
	massCenterLocationY_m = 0.34 * lengthOfForwarder_m;
	//end of temporare to remove
}

void calculateForceErrorPercentageAndSendOnCAN1(void) {
	sint16 wheel = 0;
	sint16 forceErrorInPercent[INDEX_SIZE_WHEELS] = {0};
	for (wheel = 0; wheel < INDEX_SIZE_WHEELS; wheel++) {
		forceErrorInPercent[wheel] = (float)( (float)(forceReferenceOptimalDistrubution_N[wheel] - messuredForceCylinderLoad_deciN[wheel]) / (float)forceReferenceOptimalDistrubution_N[wheel] ) * 100;
	}
	sendCAN1_sint16(0x18FF1004, forceErrorInPercent[FL], forceErrorInPercent[FR], forceErrorInPercent[ML], forceErrorInPercent[MR]);
	sendCAN1_sint16(0x18FF1005, forceErrorInPercent[BL], forceErrorInPercent[BR], 0, 0);
}

void calculateOptimalForceForAllWheelsAndSendOnCAN(void) {
	float lengthOfForwarder_m      = 6.05;
	float lengthToMidOfForwarder_m = 3.70;
	float widthOfForwarder_m       = 2.35;

	float kMidScalingConstant = (float)1/3;

	float kFront = (lengthOfForwarder_m - massCenterLocationY_m - (lengthOfForwarder_m - lengthToMidOfForwarder_m) * kMidScalingConstant) / lengthOfForwarder_m;
	float kLeft  = 1 - massCenterLocationX_m / widthOfForwarder_m;
	float kMid   = kMidScalingConstant;
	float kRear  = (massCenterLocationY_m - lengthToMidOfForwarder_m * kMidScalingConstant) / lengthOfForwarder_m;
	float kRight = massCenterLocationX_m / widthOfForwarder_m;

	//Optimal force ref vector vertical
	forceReferenceOptimalDistrubution_N[FL]  = kFront * kLeft  * Weight;
	forceReferenceOptimalDistrubution_N[FR]  = kFront * kRight * Weight;
	forceReferenceOptimalDistrubution_N[ML]  = kMid   * kLeft  * Weight;
	forceReferenceOptimalDistrubution_N[MR]  = kMid   * kRight * Weight;
	forceReferenceOptimalDistrubution_N[BL]  = kRear  * kLeft  * Weight;
	forceReferenceOptimalDistrubution_N[BR]  = kRear  * kRight * Weight;

	sint16 forceReferenceDispSum_N = 0;
	sint16 wheel = 0;
	//convert to optimalFOrceRef on cylinder. The check of calculations is corret calculate sum of vertical ref and compare to weight
	for (wheel = 0; wheel < 6; wheel++) {
		forceReferenceDispSum_N = forceReferenceDispSum_N + forceReferenceOptimalDistrubution_N[wheel];
		forceReferenceOptimalDistrubution_N[wheel] = forceCylinderLoadFromForceOnWheel(posData[wheel], forceReferenceOptimalDistrubution_N[wheel]);
	}
	sendCAN1_sint16(0x18FF1002, forceReferenceOptimalDistrubution_N[FL], forceReferenceOptimalDistrubution_N[FR], forceReferenceOptimalDistrubution_N[ML], forceReferenceOptimalDistrubution_N[MR]);
	sendCAN1_sint16(0x18FF1003, forceReferenceOptimalDistrubution_N[BL], forceReferenceOptimalDistrubution_N[BR], Weight, forceReferenceDispSum_N);

	calculateForceErrorPercentageAndSendOnCAN1();
}

sint16 getOptimalReferenceForceForWheel(uint8 wheelNumber) {
	return forceReferenceOptimalDistrubution_N[wheelNumber];
}


