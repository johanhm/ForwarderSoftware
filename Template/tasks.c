/*
 * tasks.c
 All periodic running tasks
 */



/*
  FUNCTION:      actuate

//brief         Unique actuation function, only function that control the solenoid current outputs
#define RefZero 0 //Number taken as valve closed Zero output on both solenoids
#define RefMin -400 //Min Ref Equivalent to Max output on Solenoid B Deadband+ -RefMin
#define RefMax 400 //Max Ref Equivalent to Max output on Solenoid A  Deadband+ Refmax
#define FR 0
#define FL 1
#define MR 2
#define ML 3
#define BR 4
#define BL 5
volatile sint16 Ref_out[6]={RefZero};
#define CAN_TEST_ON							1	// Set to 1 when outputting values to CAN
#define ANALOG_OUTPUT_ON					0	// Set to 1 when outputting values to pins

 */
void actuate(void){
	uint8 i=0;

	//Check global variables are within minimum and maximum range and limits
	for(i = 0; i < 6; i++) {
		if(referenceSoleonidOutputCurrent_ma[i] < REFERENCE_CURRENT_MAXIMUM_B_mA) {
			referenceSoleonidOutputCurrent_ma[i] = REFERENCE_CURRENT_MAXIMUM_B_mA;
		}
		else if(referenceSoleonidOutputCurrent_ma[i] > REFERENCE_CURRENT_MAXIMUM_A_mA) {
			referenceSoleonidOutputCurrent_ma[i] = REFERENCE_CURRENT_MAXIMUM_A_mA;
		}
	}

	//Compute scaled values for each cylinder's valves
	for(i = 0; i < 6; i++) {
		if(referenceSoleonidOutputCurrent_ma[i] == 0) {//both valves off
			Ref_A[i] = 0;
			Ref_B[i] = 0;}
		else if(referenceSoleonidOutputCurrent_ma[i] > 0) {//Output scaled on A  turn off B
			Ref_A[i] = referenceSoleonidOutputCurrent_ma[i] + DEADZONE_FOR_SOLEONID_CURRENT_mA;  //Out between 400 and 800
			Ref_B[i] = 0;}
		else if(referenceSoleonidOutputCurrent_ma[i] < 0) {//Output scaled on B  turn off A
			Ref_A[i] = 0;
			Ref_B[i] = (-1*referenceSoleonidOutputCurrent_ma[i]) + DEADZONE_FOR_SOLEONID_CURRENT_mA;	} //Out between 400 and 800
	}

	//Cylinder position limit control, does not let cylinder be actuated further in the direction that passed the limit
	if(CYL_POSITION_LIMIT_ON){

		for(i=0;i<6;i++){
			if(Cyl_limit[i]==1){
				if(posData[i]<CYL_POS_MIN){Ref_A[i]=0;}           //Assuming REF_A() makes the cylinder go to the positive (extending) direction
				else if(posData[i]>CYL_POS_MAX){Ref_B[i]=0;}     //Assuming REF_B() makes the cylinder go to the negative (retracting) direction
			}
		}
	}


	//If OUT_Analog then actuate solenoids with scaled values
	if(ANALOG_OUTPUT_ON==1){
		out(OUT_PENDELURM_FRONT_RIGHT_A, Ref_A[FR]);
		out(OUT_PENDELURM_FRONT_RIGHT_B, Ref_B[FR]);

		out(OUT_PENDELURM_FRONT_LEFT_A,  Ref_A[FL]);
		out(OUT_PENDELURM_FRONT_LEFT_B,  Ref_B[FL]);

		out(OUT_PENDELURM_MID_RIGHT_A,   Ref_A[MR]);
		out(OUT_PENDELURM_MID_RIGHT_B,   Ref_B[MR]);

		out(OUT_PENDELURM_MID_LEFT_A,    Ref_A[ML]);
		out(OUT_PENDELURM_MID_LEFT_B,    Ref_B[ML]);

		out(OUT_PENDELURM_REAR_RIGHT_A,  Ref_A[BR]);
		out(OUT_PENDELURM_REAR_RIGHT_B,  Ref_B[BR]);

		out(OUT_PENDELURM_REAR_LEFT_A,   Ref_A[BL]);
		out(OUT_PENDELURM_REAR_LEFT_B,   Ref_B[BL]);}


	defaultSafety++;
	if(defaultSafety>80){   //if no command has been received for 80*1ms out references to 0
		for(i=0;i<6;i++){
			referenceSoleonidOutputCurrent_ma[i]=0;}
		defaultSafety=82;
	}



}


/***************************************************************************************************
 *  FUNCTION:      read_Sensor_Task
 */
/**\brief         this function reads the position and pressure sensors as well as calculate velocity from the position and corresponding cylinder forces
 */
/**************************************************************************************************/
void read_Sensor_Task1(void)  //Read Pressure sensors at 1000hz
{
	uint8 x = 0; //index used in FOR loops

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
	for(x = 0; x < INDEX_SIZE_PRESSURESENS; x++) {
		pressureData[x] = (float)pressureData_mV[x] * 6.25-3125;
	}

	//Low pass filter pressure signals
	for(x = 0; x < INDEX_SIZE_PRESSURESENS; x++) {
		pressureData[x]      = alpha * pressureData_last[x] + (1-alpha) * pressureData[x];
		pressureData_last[x] = pressureData[x];
	}


	//Calculate corresponding forces at cylinder chambers and total
	for(x = 0; x < INDEX_SIZE_PRESSURESENS; x++)
	{
		if(x % 2 == 0) {
			forceData[x] = 100 * pressureData[x] * (float)CYLINDER_PUSH_AREA_SIDE_A1_m2;
		}//100*KPa*m^2= deca N (N/10)
		else {
			forceData[x] = 100 * pressureData[x] * (float)CYLINDER_PUSH_AREA_SIDE_B2_m2;
		}//100*KPa*m^2= deca N  (N/10)
	}


	uint8 i = 0;
	//Calculate Load force Fa-Fb decaN  (N/10)
	for(x = 0; x <INDEX_SIZE_WHEELS; x++)
	{
		//Load_force[x] = (forceData[i] - forceData[i+1]);
		messuredForceCylinderLoad_deciN[x] = (forceData[i] - forceData[i+1]);
		i = i + 2;
	}

}//end read_Sensor_task

void read_Sensor_Task2(void)  //Read position sensors at 20hz
{
	uint8 x=0; //index used in FOR loops

	//////////////////////read Position sensors  and calculate velocities
	//Save Pos(k-1)
	for(x = 0; x < 6; x++) {
		posData_last[x] = posData[x];
	}

	//Get new sensor readings and scale from mV to mm
	posData_mV[ANALOG_RIGHT_FRONT_PENDULUMARM] = in(IN_1_AIV);
	posData_mV[ANALOG_LEFT_FRONT_PENDULUMARM]  = in(IN_2_AIV);
	posData_mV[ANALOG_RIGHT_MID_PENDULUMARM]   = in(IN_3_AIV);
	posData_mV[ANALOG_LEFT_MID_PENDULUMARM]    = in(IN_4_AIV);
	posData_mV[ANALOG_RIGHT_BACK_PENDULUMARM]  = in(IN_6_AIV);
	posData_mV[ANALOG_LEFT_BACK_PENDULUMARM]   = in(IN_5_AIV);
	for(x = 0; x < 6;x++) {
		posData[x] = (float)((float)(posData_mV[x]-minPos[x])/(maxPos[x]-minPos[x]))*500;
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
		Zc = Zc+posData[x];
	}
	Zc = Zc / 6;
	Zcdot = 0;
	for (x = 0; x < 6; x++) {
		Zcdot = Zcdot + velData[x];
	}
	Zcdot = Zcdot / 6;  //Observer for average chassis height


	//Calculate estimate of velocity of Zi chassis mounting points (where the cylinder is attached) using the Gyro measurements
	//Calculate estimate of position of Zi chassis mounting points (where the cylinder is attached) using the Accelerometer measurements

	Theta_deg = (float)(ACCELY_RAW * 900) / 1800.0;  //ANgle in theta axis deg*10
	Phi_deg   = (float)(ACCELX_RAW * 900) / -1800.0;   //Angle in phi axis deg*10

	//Low pass filter
	Theta_deg      = alphapos * Theta_deg_last + (1-alphapos) * Theta_deg; //Low pass filter theta
	Theta_deg_last = Theta_deg;
	Phi_deg        = alphapos * Phi_deg_last + (1-alphapos) * Phi_deg; //Low pass filter phi
	Phi_deg_last   = Phi_deg;


	Theta_rad = (float)Theta_deg*pi/1800.0;		//Convert to radians
	Phi_rad   = (float)Phi_deg*pi/1800.0;			//Convert to radians

	Gyro_Phi_deg   = Gyro_Phi_RAW / 50;				//Angular velocity in deg/s from gyroscope  (Note:Divide RAW by 50 to get deg/s , negative sign to keep vehicle sign convention)
	Gyro_Theta_deg = Gyro_Theta_RAW / 50; 		//Angular velocity in deg/s from gyroscope
	Gyro_Phi_rad   = (float)Gyro_Phi_deg * pi / 180.0;				//convert to rad/s
	Gyro_Theta_rad = (float)Gyro_Theta_deg * pi / 180.0;	     	//convert to rad/s


	for (x = 0; x < 6; x++) {
		Zi_pos[x] = (float)(b_geo[x] * (sin(Phi_rad) * cos(Theta_rad)) + a_geo[x] * sin(Theta_rad));
		Zi_vel[x] = b_geo[x] * (sin(Gyro_Phi_rad) * cos(Gyro_Theta_rad)) + a_geo[x] * sin(Gyro_Theta_rad);
	}  //Calculate positions and velocities



	//Low pass filter chassiss velocities signals, low pass filter chassis position signals
	for(x = 0; x <INDEX_SIZE_WHEELS; x++) {
		//Zi_vel[x]=alphav*Zi_vel_last[x]+(1-alphav)*Zi_vel[x];  //Low pass filter vel
		//Zi_vel_last[x]=Zi_vel[x];

		Zi_pos[x]      = alphapos * Zi_pos_last[x] + (1-alphapos) * Zi_pos[x]; //Low pass filter positions
		Zi_pos_last[x] = Zi_pos[x];

	}



	///////////////////////////////////////////////////////
	//Calculate cylinder flows in L/min and send
	for (x = 0; x < 6; x++) {
		if (velData[x]>=0) {
			Cyl_flow[x] = velData[x] * CYLINDER_PUSH_AREA_SIDE_A1_m2 * 60;
		}
		else if (velData[x]<0) {
			Cyl_flow[x] = (-1 * velData[x]) * CYLINDER_PUSH_AREA_SIDE_B2_m2 * 60;
		}
	}
}


/***************************************************************************************************
 *  FUNCTION:      send_CAN_sensors_values_Task
 */
/**\brief         Sends sensor values on CAN
 */
/**************************************************************************************************/

void sendSupplyVoltageOnCAN(void) {
	sint16 batterySupplyVoltage = sys_getSupply(VB);
	sint16 sensorSupplyVoltage1 = sys_getSupply(VSS_1);
	sint16 sensorSupplyVoltage3 = sys_getSupply(VSS_3);

	sendCAN1_sint16(0x18FF1060, batterySupplyVoltage, sensorSupplyVoltage1, sensorSupplyVoltage3, 0);
}


void send_CAN_sensors_values_Task(void)
{

	//sendSupplyVoltageOnCAN();

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

	uint8 i=0;
	uint8 data_au8_sms_11[6]={0};   //Flow in cylinder L/min
	for(i=0;i<6;i++){
		data_au8_sms_11[i]=Cyl_flow[i];
	}

	uint8 data_au8_sms_12[8]={0}; //Load force
	uint8 data_au8_sms_13[4]={0}; //Load force
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
	uint8 debug1[8]={0}; //
	uint8 debug2[8]={0}; //
	uint8 debug3[8]={0}; //
	//Construct Debugmsg 1

	debug1[0] =sl_debug_1;
	debug1[1] =sl_debug_1>>8;
	debug1[2] =sl_debug_1>>16;
	debug1[3] =sl_debug_1>>24;
	debug1[4] =sl_debug_2;
	debug1[5] =sl_debug_2>>8;
	debug1[6] =sl_debug_2>>16;
	debug1[7] =sl_debug_2>>24;

	//Construct Debugmsg 2
	debug2[0] =sl_debug_3;
	debug2[1] =sl_debug_3>>8;
	debug2[2] =sl_debug_3>>16;
	debug2[3] =sl_debug_3>>24;
	debug2[4] =sl_debug_4;
	debug2[5] =sl_debug_4>>8;
	debug2[6] =sl_debug_4>>16;
	debug2[7] =sl_debug_4>>24;

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
		if (0 == can_sendData(CAN_1,CAN_ID_REF_CURRENT_FRONT, CAN_EXD_DU8, 8, data_au8_currentCylinders)) {}

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
		data_au8_currentCylinders[1] = i_mA_LeftA>>8;
		data_au8_currentCylinders[2] = i_mA_LeftB;
		data_au8_currentCylinders[3] = i_mA_LeftB>>8;
		data_au8_currentCylinders[4] = i_mA_RightA;
		data_au8_currentCylinders[5] = i_mA_RightA>>8;
		data_au8_currentCylinders[6] = i_mA_RightB;
		data_au8_currentCylinders[7] = i_mA_RightB>>8;
		if (0 == can_sendData(CAN_1, CAN_ID_REF_CURRENT_BACK, CAN_EXD_DU8, 8, data_au8_currentCylinders)) {}
	}

	//CAlculate and send vertical load force for every cylinder
	uint8 data_au8_sms_FORCE_VERTICAL1[8]={0}; //Vertical force
	uint8 data_au8_sms_FORCE_VERTICAL2[4]={0}; //Vertical force
	Weight = 0;
	for(i = 0; i < 6; i++) {
		forceVertical[i] = forceOnWheelVerticalFromCylinderLoad(posData[i], messuredForceCylinderLoad_deciN[i]);
		if(forceVertical[i] > 0) {
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

	uint8 data_au8_sms_OBS[8]={0}; //State observers
	data_au8_sms_OBS[0]=Zc;
	data_au8_sms_OBS[1]=Zc>>8;
	data_au8_sms_OBS[2]=Zcdot;
	data_au8_sms_OBS[3]=Zcdot>>8;
	data_au8_sms_OBS[4]=Theta_deg;
	data_au8_sms_OBS[5]=Theta_deg>>8;
	data_au8_sms_OBS[6]=Phi_deg;
	data_au8_sms_OBS[7]=Phi_deg>>8;

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

	sendCAN1_sint16(CAN_ID_DEBUG_MSG_4, F_matrix[0], F_matrix[0] >> 16, F_matrix[1], F_matrix[1]>>16);
	sendCAN1_sint16(CAN_ID_DEBUG_MSG_5, F_matrix[2], F_matrix[2] >> 16 ,0 ,0);

	massCenterLocationAndSendOnCAN();
	calculateOptimalForceForAllWheelsAndSendOnCAN();

}
/***************************************************************************************************
  FUNCTION:      Function for controller allocation and supervisor
      Allocation

 **************************************************************************************************/


//Ground contact controller
void test_Task(void) {

	uint8 x = 0,j = 0;
	for(x = 0; x < 6; x++) {  //Supervisor condition monitoring

		//Check which wheels are not in the ground
		if(messuredForceCylinderLoad_deciN[x] < air_limit / 10) {
			Ref_ground_force[x] = Ground_ref_force; //How fast to reach ground
			In_ground[x]        = 0;
		} else if (messuredForceCylinderLoad_deciN[x] > GROUND_P / 10) {   //Load limit
			Ref_ground_force[x] = 0;
			In_ground[x]        = 1;
		}

		//Arm position monitoring
		ARM_ACTIVE[x] = 1;  //Start active
		//if(posData[x]<CYL_POS_MIN){ARM_ACTIVE[x]=0;}           //Arms outside the position limits then disable
		//if(posData[x]>CYL_POS_MAX){ARM_ACTIVE[x]=0;}

		//Pressure condition monitoring
		if((pressureData[j] < 200) && (pressureData[j+1] < 200)) {
			ARM_ACTIVE[x] = 0;
		}  //If both sensors measure less than 1 bar, then either faulty sensor or hydraulic circuit
		j = j + 2;

		ARM_ACTIVE[x] = ARM_ACTIVE[x] && In_ground[x];   //Deactivate also if wheel is in the air


		if (ARM_ACTIVE[x] == 1) {
			count_active[x]++;
			ARM_ACTIVE_F[x] = count_active[x] / (float)MAX_COUNT;
		}
		if (ARM_ACTIVE[x] == 0) {
			count_active[x]--;
			ARM_ACTIVE_F[x] = count_active[x] / (float)MAX_COUNT;
		}

		if (ARM_ACTIVE_F[x] > 1) {
			ARM_ACTIVE_F[x] = 1;
		    count_active[x] = MAX_COUNT;
		}  //Limit between 0 and 1
		if (ARM_ACTIVE_F[x] < 0) {
			ARM_ACTIVE_F[x] = 0;
		    count_active[x] = 0;
		}
	}






	/*
//Balance side to side
sint16 Back_diff=0;
sint16 Front_diff=0;
sint16 Mid_diff=0;
Back_diff=abs(Load_force[BL]-Load_force[BR]);
Mid_diff=abs(Load_force[ML]-Load_force[MR]);
Front_diff=abs(Load_force[FL]-Load_force[FR]);

Ref_balance_force[BL]=0;
Ref_balance_force[BR]=0;
if(Back_diff>500){  //If difference is higher than 10000 N

	if(Load_force[BL]>Load_force[BR]) {
		Ref_balance_force[BL]=-balance_force;
		Ref_balance_force[BR]=balance_force;
	}
	else{
		Ref_balance_force[BL]=balance_force;
		Ref_balance_force[BR]=-balance_force;
	}}


Ref_balance_force[ML]=0;
Ref_balance_force[MR]=0;
if(Mid_diff>500){  //If difference is higher than 10000 N

	if(Load_force[ML]>Load_force[MR]) {
		Ref_balance_force[ML]=-balance_force;
		Ref_balance_force[MR]=balance_force;
	}
	else{
		Ref_balance_force[ML]=balance_force;
		Ref_balance_force[MR]=-balance_force;
	}}

Ref_balance_force[FL]=0;
Ref_balance_force[FR]=0;
if(Front_diff>500){  //If difference is higher than 10000 N

	if(Load_force[FL]>Load_force[FR]) {
		Ref_balance_force[FL]=-balance_force;
		Ref_balance_force[FR]=balance_force;
	}
	else{
		Ref_balance_force[FL]=balance_force;
		Ref_balance_force[FR]=-balance_force;
	}}

	 */

	double a[18]={1.0,1.0,1.0,1.0,1.0,1.0,0.5,-0.5,0.5,-0.5,0.5,-0.5,1.5,1.5,-0.5,-0.5,-2.75,-2.75};
	double a_modified[18]={0};
	uint i=0;
	/*
for(i=0;i<6;i++){                    //Change Geometry matrix depending on unavailable actuators (Off the ground, not responding, saturated)
a_modified[i]=a[i]*ARM_ACTIVE[i];
a_modified[i+6]=a[i+6]*ARM_ACTIVE[i];
a_modified[i+12]=a[i+12]*ARM_ACTIVE[i];
}
	 */


	for(i=0;i<6;i++){                    //Change Geometry matrix depending on unavailable actuators (Off the ground, not responding, saturated)
		a_modified[i]    = a[i]    * ARM_ACTIVE_F[i];
		a_modified[i+6]  = a[i+6]  * ARM_ACTIVE_F[i];
		a_modified[i+12] = a[i+12] * ARM_ACTIVE_F[i];
	}

	double b[18] = {0};
	funcpinv(a_modified,b);  //Calculate pseudo inverse

	//Change new inverse matrix from array[18] into 6x3 format
	uint8 index_1 = 0;
	for(i = 0; i < 6; i++) {
		for(x = 0; x < 3; x++) {
			moore_inverse_modified[i][x] = b[index_1];
			index_1++;
		}
	}
	sint16 i9=0;
	sint16 i10=0;
	for(i=0;i<6;i++){
		i9=((In_ground[i]<<i)| i9 );
		i10=((ARM_ACTIVE[i]<<i)| i10 );
	}
	sendCAN1_sint16(CAN_ID_DEBUG_MSG_6	,i9,i10,ACTIVE_FORCE_CONTROL,0);
}

void massCenterLocationAndSendOnCAN(void) {
	float lengthOfForwarder_m = 5.70;
	float lengthToMidOfForwarder_m = 3.50;
	float widthOfForwarder_m = 2.35;

	float sumOfForcesOnWheels_N = Weight;

	massCenterLocationX_m = 1 / sumOfForcesOnWheels_N * (forceVertical[1] + forceVertical[3] + forceVertical[5]) * widthOfForwarder_m;

	float forceML = forceVertical[2];
	float forceMR = forceVertical[3];
	float forceBL = forceVertical[4];
	float forceBR = forceVertical[5];

	massCenterLocationY_m = 1 / sumOfForcesOnWheels_N * ((forceML + forceMR) * lengthToMidOfForwarder_m + (forceBL + forceBR) * lengthOfForwarder_m);

	sint16 massCenterLocationX_sint16_10m = (massCenterLocationX_m / widthOfForwarder_m  * 100);
	sint16 massCenterLocationY_sint16_10m = (massCenterLocationY_m / lengthOfForwarder_m * 100);

	sendCAN1_sint16(0x18FF1001, massCenterLocationX_sint16_10m, massCenterLocationY_sint16_10m, 0, 0);

	//temporary remove when logic is working
	massCenterLocationX_m = 0.51 * widthOfForwarder_m;
	massCenterLocationY_m = 0.32 * lengthOfForwarder_m;
	//end of temporare to remove

}


void calculateOptimalForceForAllWheelsAndSendOnCAN(void) {
	float lengthOfForwarder_m      = 5.70;
	float lengthToMidOfForwarder_m = 3.50;
	float widthOfForwarder_m       = 2.35;

	float kMidScalingConstant = 0.33333333333;

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
	for (wheel = 0; wheel < 5; wheel++) {
		forceReferenceDispSum_N = forceReferenceDispSum_N + forceReferenceOptimalDistrubution_N[wheel];
		forceReferenceOptimalDistrubution_N[wheel] = forceCylinderLoadFromForceOnWheel(posData[wheel], forceReferenceOptimalDistrubution_N[wheel]);
	}

	sendCAN1_sint16(0x18FF1002, forceReferenceOptimalDistrubution_N[FL], forceReferenceOptimalDistrubution_N[FR], forceReferenceOptimalDistrubution_N[ML], forceReferenceOptimalDistrubution_N[MR]);
	sendCAN1_sint16(0x18FF1003, forceReferenceOptimalDistrubution_N[BL], forceReferenceOptimalDistrubution_N[BR], Weight, forceReferenceDispSum_N);
}

void hightControllSkyhookForceAddition(void) {
	uint8 x = 0;
	if(ACTIVE_ZSKY_CONTROL==1) {
		for(x = 0; x < 6; x++) {
			F_Z_sky[x] = -BSky_Z*Zi_vel[x];     //Skyhook damping force per chassis wheel point [N]
			F_Z_sky[x] = forceCylinderLoadFromForceOnWheel(posData[x], F_Z_sky[x]); //Transform vertical force into cylinder force
		}
	}
	else {
		for(x = 0; x < 6; x++) {
			F_Z_sky[x] = 0;
		}
	}
}

void heightControllAddToAllocationMatrix(void) {
	//Chassis Height control Zc
	if(ACTIVE_HEIGHT_CONTROL == 1){
		//P(Stiffness) I control
		Zc_error=Zc_ref-Zc;   //Zc between is average of all arm positions, between (0 and 500) mm
		if(Zc_error <5 && Zc_error >-5){
			Z_I = 0;   //If we reach almost zero error, reset integrator
			Zc_error = 0;
		}
		Z_k = Zc_error * K_z;
		Z_I = (Zc_error+Z_I) * I_z;

		if(Z_I > MAX_ZI) {
			Z_I = MAX_ZI;
		}  //Clamp integrator to max
		if(Z_I < -MAX_ZI) {
			Z_I = -MAX_ZI;
		}  //Clamp integrator to min

		F_Z_damp = -B_Zc*Zcdot;
		F_REF_Z = Z_k+Z_I+F_Z_damp; //Sum vertical forces
		F_matrix[0] = F_REF_Z; //Include in Force matrix for decoupling
	}
	else {
		F_matrix[0] = 0;
	}
}

void rollPhiControllAddToAllocationMatrix(void) {
	if(ACTIVE_PHI_CONTROL == 1) {
		Phi_error = 0 - Phi_deg; //Reference is 0

		if(Phi_error < 5 && Phi_error > -5) {  //Error tolerance of 1 degree
			Phi_I = 0;   //If we reach almost zero error, reset integrator
			Phi_error = 0;
		}

		Phi_k = Phi_error * K_phi;
		Phi_I = Phi_error + Phi_I;
		if(Phi_I > MAX_PHI_I) {
			Phi_I = MAX_PHI_I;
		}  //Clamp integrator to max
		if(Phi_I < -MAX_PHI_I) {
			Phi_I = -MAX_PHI_I;
		}  //Clamp integrator to min

		Phi_sky = -BSky_phi * Gyro_Phi_deg;
		F_REF_Phi = Phi_k + Phi_sky + Phi_I; //Sum phi moment
		F_matrix[1] = F_REF_Phi;  //Assign to force vector
	}
	else {
		F_matrix[1] = 0;
	}

}

void pitchThetaControllAddToAllocationMatrix(void) {
	if(ACTIVE_THETA_CONTROL == 1){

		Theta_error = 0 - Theta_deg; //Reference is 0
		if(Theta_error < 5 && Theta_error > -5){  //Error tolerance of 1 degree
			Theta_I = 0;   //If we reach almost zero error, reset integrator
			Theta_error = 0;
		}

		Theta_k = Theta_error * K_theta;  //Ref=0  Error=(0-Thetadeg)

		Theta_I = -Theta_deg + Theta_I;
		if(Theta_I > MAX_THETA_I) {
			Theta_I = MAX_THETA_I;
		}  //Clamp integrator to max
		if(Theta_I < -MAX_THETA_I) {
			Theta_I = -MAX_THETA_I;
		}  //Clamp integrator to min

		Theta_sky = -BSky_theta * Gyro_Theta_deg;
		F_REF_Theta = Theta_k + Theta_sky + Theta_I; //Sum theta moment
		F_matrix[2] = F_REF_Theta;  //Assign to force vector
	}
	else {
		F_matrix[2]=0;
	}
}

void decoupleHightRollPitchAndConvertToCylinderForceForAllWheels(void) {
	uint8 i = 0;
	uint8 k = 0;

	for (i = 0; i <= 5; i++) {  //Moore row counter
		sum = 0;
		for (k = 0; k <= 2; k++) {  //Moore column counter
			if (Control_allocation_on==0) {
				sum = sum + (float)moore_inverse[i][k] * F_matrix[k];
			}
			if (Control_allocation_on==1) {
				sum = sum + (float)moore_inverse_modified[i][k] * F_matrix[k];
			}
		}
		F_REF[i] = sum;  //Vertical reference force for each cylinder
		F_REF_CYL[i] = forceCylinderLoadFromForceOnWheel(posData[i], F_REF[i]);  //Calculate needed cylinder force according to arm position
	}
}

void calculateForceReferenceForAllWheels(void) {
	uint8 x = 0;
	for(x = 0; x <= 5; x++){
		if (To_ground_active == 0) {
			Ref_ground_force[x] = 0;
		}

		//change between optimal dispribuiton or not
		F_REF_CYL[x] = forceReferenceOptimalDistrubution_N[x] * 10 + F_REF_CYL[x] + F_Z_sky[x] + Ref_ground_force[x];
		//F_REF_CYL[x] = messuredForceCylinderLoad_deciN[x] * 10 + F_REF_CYL[x] + F_Z_sky[x] + Ref_ground_force[x];

		//if(F_REF_CYL[x]<GROUND_P){F_REF_CYL[x]=Load_force[x]*10+Ref_ground_force[x];}
		if(F_REF_CYL[x] < GROUND_P) {
			F_REF_CYL[x] = GROUND_P;
		}
	}
}

void Dynamic_control_Task(void){

	//Zc damping individual chassis point skyhook damping implementation
	hightControllSkyhookForceAddition();

	//Chassis Height control Zc
	heightControllAddToAllocationMatrix();

	//Roll (Phi) control    P (Stiffness) I (integrator)  Skyhook damping (D)
	rollPhiControllAddToAllocationMatrix();

	//Pitch (Theta) control   P (Stiffness) I (integrator) Skyhook damping (D)
	pitchThetaControllAddToAllocationMatrix();

	//Decoupling of forces and assign to individual cylinders
	//Multiply 6x3 moore inverse times 3x1 Force_reference matrix
	decoupleHightRollPitchAndConvertToCylinderForceForAllWheels();

	//ADD current Load force, calculated cylinder force needed and individual skyhook damping forces
	calculateForceReferenceForAllWheels();

	//Debugging variables, global and will send out on CAN sometime
	sl_debug_1 = F_REF_CYL[0];
	sl_debug_2 = F_REF_CYL[1];
	sl_debug_3 = F_REF_CYL[2];
	sl_debug_4 = F_REF_CYL[3];
	sl_debug_5 = F_REF_CYL[4];
	sl_debug_6 = F_REF_CYL[5];
}

void mapErestimatedFlowToCurrentOutputOnWheelWithNumber(uint8 wheelCounter) {
	float absoluteFlowInPercent = fabs(sl_u * 100.0);
	if(sl_u < 0.015 && sl_u > -0.015) {
		sl_current = 400;
	}
	else if(fabs(sl_u) > 0.97) {
		sl_current = 600 * (sl_u / fabs(sl_u));
	}
	else{
		sl_current = (sl_u/fabs(sl_u)) * (VALVE_FLOW_FIT_PARAMETER_CP1*pow(absoluteFlowInPercent,4) + VALVE_FLOW_FIT_PARAMETER_CP2*pow(absoluteFlowInPercent,3) + VALVE_FLOW_FIT_PARAMETER_CP3*pow(absoluteFlowInPercent,2) + VALVE_FLOW_FIT_PARAMETER_CP4 * absoluteFlowInPercent + VALVE_FLOW_FIT_PARAMETER_CP5);
	}

	sl_debug_current = sl_current - (sl_current / labs(sl_current)) * 400;  //Valve current to output in CAN for debugging

	//Set reference to valves only if control is active generally and per cylinder
	if((ACTIVE_FORCE_CONTROL == 1) & (Force_control_cylinders[wheelCounter] == 1)) {
		referenceSoleonidOutputCurrent_ma[wheelCounter] = -1 * sl_debug_current - To_ground_ref[wheelCounter];
		defaultSafety = 0;
	}
}

void calculateErestimatedFlowForWheelWithNumber(uint8 cylinderCounter) {

	//create variables
	uint32 sl_P1 = 0; //KPa*1000=[Pa]
	uint32 sl_P2 = 0;  //Kpa*1000=[Pa]
	sint32 sl_Fl = 0; //Load force in [N]
	sint32 sl_Vel = 0;  //Cylinder velocity in mm/s
	sint32 sigma = 0;

	float L = 0;
	float sgn = 0;

	//Map Variables to latest cylinder values and scale
	sl_P1 = pressureData[cylinderCounter*2] * 1000; //KPa*1000=[Pa]
	sl_P2 = pressureData[(cylinderCounter*2)+1] * 1000;  //Kpa*1000=[Pa]
	sl_Fl = messuredForceCylinderLoad_deciN[cylinderCounter] * 10; //Load force in [N]

	if((velData[cylinderCounter] > -10) || (velData[cylinderCounter] < 10)) {
		sl_Vel=0;
	}
	else {
		sl_Vel = velData[cylinderCounter];
	} //Cylinder velocity in mm/s
	//sigma=sl_Fl-sl_Ref[x];
	sigma = sl_Fl - F_REF_CYL[cylinderCounter];
	sigma = sigma / 500;

	sgn = ((float)sigma / (labs(sigma) + 1000.0));   //	sgn=((float)sigma/((float)labs(sigma)+1000.0));

	if (sl_uold[cylinderCounter] >= 0) {
		L = CYLINDER_PUSH_AREA_SIDE_A1_m2 * MAXIMUM_FLOW_QMAX_m3s + CYLINDER_PUSH_AREA_SIDE_B2_m2 * sqrt(abs(sl_P2 - 0)) * MAXIMUM_FLOW_QMAX_m3s / sqrt(DELTA_PRESSURE_8bar);
	}
	else {
		L = CYLINDER_PUSH_AREA_SIDE_A1_m2 * sqrt(abs(sl_P1 - 0)) * MAXIMUM_FLOW_QMAX_m3s / sqrt(DELTA_PRESSURE_8bar) + CYLINDER_PUSH_AREA_SIDE_B2_m2 * MAXIMUM_FLOW_QMAX_m3s;
	}

	sl_u = 1.0 / L * ((pow(CYLINDER_PUSH_AREA_SIDE_A1_m2,2) + pow(CYLINDER_PUSH_AREA_SIDE_B2_m2,2)) * ((float)sl_Vel/1000.0) - SLIDING_MODE_CONTROL_PARAMETER_Kt * sgn);  //Requested flow in percentage
	if (sl_u > 1) {
		sl_u = 1;
	}  //Saturate requested flow % between -1 and 1  (100% full flow on both directions)
	else if (sl_u < -1) {
		sl_u = -1;
	}

	sl_uold[cylinderCounter] = sl_u;
}

void FORCE_ControlTask(void)  //Sliding mode
{
	uint8 wheelCounter = 0; //Loop counter
	for(wheelCounter = 0; wheelCounter < 6; wheelCounter++){  //ALL
		//Calculate erestimated flow with sliding mode controll structure
		calculateErestimatedFlowForWheelWithNumber(wheelCounter);

		//Calculate corresponding valve current for requested flow using fitted flow curve
		mapErestimatedFlowToCurrentOutputOnWheelWithNumber(wheelCounter);
	}//end for
}
