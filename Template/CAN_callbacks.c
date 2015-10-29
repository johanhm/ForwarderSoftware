/*
 * CAN_callbacks.c
 *
 *  Created on: 29 apr 2015
 *      Author: ladmin
 */

void can_1_RxCallback(uint8 format_u8, uint32 id_u32, uint8 numBytes_u8, uint8 *data_pu8)
{
	static uint8 tempFormat_u8;
	static uint32 tempId_u32;
	static uint8 tempNumBytes_u8;
	static uint8 tempData_u8;

	tempFormat_u8   = format_u8;
	tempId_u32      = id_u32;
	tempNumBytes_u8 = numBytes_u8;
	tempData_u8     = data_pu8[0];
} // can_1_RxCallback

void can_3_RxCallback(uint8 format_u8, uint32 id_u32, uint8 numBytes_u8, uint8 *data_pu8)
{
	static uint8  tempFormat_u8;
	static uint32 tempId_u32;
	static uint8  tempNumBytes_u8;
	static uint8  tempData_u8;

	tempFormat_u8   = format_u8;
	tempId_u32      = id_u32;
	tempNumBytes_u8 = numBytes_u8;
	tempData_u8     = data_pu8[0];
} // can_3_RxCallback

/**************************************************************************************************/


/***************************************************************************************************
 *  FUNCTION:      can_1_RxDatabox_1_Callback
 */
/**\brief         Callback of CAN_1 Receive-Databox_1.  For sending solenoid reference values from CAN interface
 *
 * \return         -
 */
/**************************************************************************************************/

void can_1_RxDatabox_1_Callback(void)
{
	defaultSafety = 0; //Record a command was sent through CAN, reset safety shut off counter

	uint8 i    = 0; //loop index
	uint8 mode = 0;
	uint8 posSensTestData_au8[8] = {0};
	uint8 posSensTestNumBytes_u8;
	// Databox Get Message data and assign to variables
	if (0 == can_getDatabox(CAN_1, 1, posSensTestData_au8, &posSensTestNumBytes_u8)){}

	mode = posSensTestData_au8[6];   //Specify which cylinders we want to move
	//uint8 FR_REF = posSensTestData_au8[0];  //Reference for each cylinder 0 to 200    100 is midpoint  (closed valve)
	//uint8 FL_REF = posSensTestData_au8[1];
	//uint8 MR_REF = posSensTestData_au8[2];
	//uint8 ML_REF = posSensTestData_au8[3];
	//uint8 BR_REF = posSensTestData_au8[4];
	//uint8 BL_REF = posSensTestData_au8[5];
	sint16 Ref_CYL[6]={0};
	//Double check that we assign non-zero value only to cylinders which were specified
	for(i = 0; i < 6; i++) {

		//Ref_CYL[i]=(posSensTestData_au8[i]-100)*4;
		if((mode & 1 << i) >= 1) {
			Ref_CYL[i] = (posSensTestData_au8[i] -100) * 1;
		}  //Scale to -400 to 400
	}
	//Call function to update global reference variables
	for(i = 0; i < 6; i++) {
		referenceSoleonidOutputCurrent_ma[i] = Ref_CYL[i];
	}

} // can_1_RxDatabox_1_Callback

void can_1_RxDatabox_2_Callback(void)
{
	// uint8 i=0; //loop index
	uint8 confData_au8[8];
	uint8 confNumBytes_u8;

	// Databox Get Message data and assign to variables
	if (0 == can_getDatabox(CAN_1, 2, confData_au8, &confNumBytes_u8)){}
	uint8 i = 0;
	uint8 ACTIVE_CHANGE_1 = (confData_au8[7] & 1);

	if(ACTIVE_CHANGE_1 == 1) {

		uint16 cyl_max = ((confData_au8[1] << 8) | (confData_au8[0]));   // Add two 8-bits to an unsigned 16-bit.
		uint16 cyl_min = ((confData_au8[3] << 8) | (confData_au8[2]));   // Add two 8-bits to an unsigned 16-bit.

		//Change global variables
		CYL_POS_MAX = cyl_max; 			//Software cylinder position maximum limit (mm)
		CYL_POS_MIN = cyl_min; 			//Software cylinder minimum position limit (mm)

		uint8 LIMITS = confData_au8[5];         //All limits info
		CYL_POSITION_LIMIT_ON = (LIMITS & 1);

		//Individual Cylinder limits
		for(i = 0; i < 6; i++){
			Cyl_limit[i] = ((LIMITS >> (i+1)) & 1);
		}


		SEND_SCALED_POS         = (confData_au8[4] & 1);
		CAN_TEST_ON             = ((confData_au8[4] >> 1) & 1);
		ANALOG_OUTPUT_ON        = ((confData_au8[4] >> 2) & 1);
		SEND_ACTUAL_CURRENT_CAN = ((confData_au8[4] >> 3) & 1);
		SEND_FLOW               = ((confData_au8[4] >> 4) & 1);
		SEND_PRESSURE           = ((confData_au8[4] >> 5) & 1);
		SEND_POS_AND_VEL        = ((confData_au8[4] >> 6) & 1);
		SEND_FORCE              = ((confData_au8[4] >> 7) & 1);


		/* Uncomment to turn force control via CAN message
	ACTIVE_FORCE_CONTROL=((confData_au8[7]>>3) & 1);

	if(ACTIVE_FORCE_CONTROL != CONTROL_STATUS){
		Z_I=0; //Reset integrator when control status changes
		Phi_I=0;
		Theta_I=0;
	}

	CONTROL_STATUS=ACTIVE_FORCE_CONTROL;
		 */

		ACTIVE_HEIGHT_CONTROL = ((confData_au8[6]) & 1);
		ACTIVE_ZSKY_CONTROL   = ((confData_au8[6]>>1) & 1);
		ACTIVE_THETA_CONTROL  = ((confData_au8[6]>>2) & 1);
		ACTIVE_PHI_CONTROL    = ((confData_au8[6]>>3) & 1);
		ACTIVE_HEIGHT_DAMPING = ((confData_au8[6]>>4) & 1);

	}

} // can_1_RxDatabox_2_Callback



void can_1_RxDatabox_3_Callback(void)
{
	uint8 confData_au8[8];
	uint8 confNumBytes_u8;

	// Databox Get Message data and assign to variables
	if (0 == can_getDatabox(CAN_1, 3, confData_au8, &confNumBytes_u8)) {}

	FORCE_REF = ((confData_au8[1] << 8) | (confData_au8[0]));   // Add two 8-bits to an unsigned 16-bit.
	K_z       = ((confData_au8[3] << 8) | (confData_au8[2]));
	BSky_Z    = ((confData_au8[5] << 8) | (confData_au8[4]));
	Zc_ref    = ((confData_au8[7] << 8) | (confData_au8[6]));

	sl_Ref[0] = FORCE_REF * 100;
	sl_Ref[1] = FORCE_REF * 100;
	sl_Ref[2] = FORCE_REF * 100;
	sl_Ref[3] = FORCE_REF * 100;
	sl_Ref[4] = FORCE_REF * 100;
	sl_Ref[5] = FORCE_REF * 100;

}

void can_1_RxDatabox_4_Callback(void)
{
	uint8 confData_au8[8];
	uint8 confNumBytes_u8;

	// Databox Get Message data and assign to variables
	//i changed that the variabels should be inside the if case here johan
	if (0 == can_getDatabox(CAN_1, 4, confData_au8, &confNumBytes_u8)) {
		K_theta    = ((confData_au8[1] << 8) | (confData_au8[0]));
		K_phi      = ((confData_au8[3] << 8) | (confData_au8[2]));
		BSky_theta = ((confData_au8[5] << 8) | (confData_au8[4]));
		BSky_phi   = ((confData_au8[7] << 8) | (confData_au8[6]));
	}



}

void can_1_RxDatabox_7_Callback(void)
{
	uint8 i = 0;
	uint8 confData_au8[8];
	uint8 confNumBytes_u8;
	// Databox Get Message data and assign to variables
	if (0 == can_getDatabox(CAN_1, 7, confData_au8, &confNumBytes_u8)){}

	//Individual Cylinder force control on or off
	for(i = 0; i < 6; i++) {
		Force_control_cylinders[i] = ((confData_au8[0] >> (i)) & 1);
	}
	To_ground_active      = ((confData_au8[0] >> (6)) & 1);
	Control_allocation_on = ((confData_au8[0] >> (7)) & 1);

	I_z     = confData_au8[1];
	I_phi   = confData_au8[2];
	I_theta = confData_au8[3];
	B_Zc    = confData_au8[4];
}



void can_2_RxDatabox_1_Callback(void)
{
	//Save gyro data

	uint8 angleMessageData_au8[6];
	uint8 angleMessageNumBytes_u8;

	can_getDatabox(CAN_2, 1, angleMessageData_au8, &angleMessageNumBytes_u8);
	Gyro_Theta_RAW = (angleMessageData_au8[1] << 8 | angleMessageData_au8[0]);  //Gyro around IMU x axis
	Gyro_Phi_RAW   = (angleMessageData_au8[3] << 8 | angleMessageData_au8[2]); //Gyro around IMU y axis

}
void can_2_RxDatabox_2_Callback(void)
{
	//Save accelerometer data
	uint8 angleMessageData_au8[6];
	uint8 angleMessageNumBytes_u8;
	can_getDatabox(CAN_2, 2, angleMessageData_au8, &angleMessageNumBytes_u8);

	ACCELY_RAW = (angleMessageData_au8[1] << 8 | angleMessageData_au8[0]);
	ACCELX_RAW = (angleMessageData_au8[3] << 8 | angleMessageData_au8[2]);
	ACCELZ_RAW = (angleMessageData_au8[5] << 8 | angleMessageData_au8[4]);
}

void can_3_RxDatabox_3_Callback(void)
{
	// ...
} // can_3_RxDatabox_1_Callback

/**************************************************************************************************/
