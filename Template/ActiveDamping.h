/**** include files ********************************************************************************
* List of include files needed in this module.                                                    */

#include "application.h"
#include "api_lib_basic.h"
#include "api_lib_eepRc.h"

// use the following header of DIAG module, if support of BODAS-service is required
#include "api_lib_diag.h"
#include "math.h"
#include "stdlib.h"
#include "control_parameters.h"
#include "Pesudoinverse/funcpinv.c"


//------------------------Testing defines----------------------------


//Testing variables changeable through CAN message configuration

volatile uint8 SEND_SCALED_POS=1;
volatile uint8  ANALOG_OUTPUT_ON=1;			// Set to 1 when outputting values to pins


volatile sint16 FORCE_REF=0;

volatile uint8 CAN_TEST_ON=1;				// Set to 1 when outputting values to CAN
volatile uint8 SEND_ACTUAL_CURRENT_CAN=1; //Set to 1 to send read output current out through can
volatile uint8 SEND_PRESSURE=1;          // 1=Send  0= Do not send
volatile uint8 SEND_POS_AND_VEL=1;
volatile uint8 SEND_FORCE=1;
volatile uint8 SEND_FLOW=0;

//volatile uint8  Cyl_limit[INDEX_SIZE_WHEELS]={0,0,0,0,1,1};  //Individual cylinder limits  (Defined below so size is defined)





///////////////////////////////////////////////
#define CAN_3_CHANNEL						CAN_1
	#define CAN_ID_TEST_CYLINDERS_FRONT				0x17FE0001	//Made up for testing purposes
	#define CAN_ID_TEST_CYLINDERS_MID				0x17FE0002
	#define CAN_ID_TEST_CYLINDERS_REAR				0x17FE0003


	#define INDEX_CAN_TEST_CYLINDER_RIGHT_A_1		0
	#define INDEX_CAN_TEST_CYLINDER_RIGHT_A_2		1
	#define INDEX_CAN_TEST_CYLINDER_RIGHT_B_1		2
	#define INDEX_CAN_TEST_CYLINDER_RIGHT_B_2		3
	#define INDEX_CAN_TEST_CYLINDER_LEFT_A_1		4
	#define INDEX_CAN_TEST_CYLINDER_LEFT_A_2		5
	#define INDEX_CAN_TEST_CYLINDER_LEFT_B_1		6
	#define INDEX_CAN_TEST_CYLINDER_LEFT_B_2		7


/*** Reference input thorugh can messages ***************************************************************************************
*                                                     */
#define TESTING_COMMAND_ID             	    0x17FE0004
#define	TESTING_COMMAND_ID_ID_OUT			0x17FE0005
#define CAN_ID_REF_CURRENT_FRONT 			0x17FE0006
#define CAN_ID_REF_CURRENT_MID 				0x17FE0007
#define CAN_ID_REF_CURRENT_BACK 			0x17FE0008
#define CONF_MSG_ID				 			0x17FE0009
#define CONF_MSG_ID_2				 		0x17FE000A
#define CONF_MSG_ID_3				 		0x17FE000B
#define CONF_MSG_ID_4				 		0x17FE000C

#define INPUT_VALUE_POS_SENSOR_MIDPOINT     300
#define INPUT_VALUE_POS_SENSOR_OFFSET       300
#define MAXIMUM_VALUE						700
#define MINIMUM_VALUE						100

#define GYRO_FILTER_COUNTER					5
#define ANGLE_CONSTANT 						0.005455056

/*** Defines ***************************************************************************************
* List of defines needed only in this module.                                                     */

#define rMin_DU16    2000    /* [mOhm] */
#define rMax_DU16    19000

//BOSCH preferred
#define cfg_minLoad		5000//7400	/* [mOhm] */
#define cfg_maxLoad		30000//21700
#define cfg_frequency	f_200Hz_DU16		/* [Hz] */
#define cfg_debounce	100		/* [ms] */

/*** Defines for TASKS **************************************************************************** */
#define TASK_1_PRIO_DU8      				20
#define TASK_1_TIME_MS_DU32  				50
#define TASK_1_OFFS_MS_DU32   				0

#define MANUAL_CONTROl_TASK_PRIO_DU8      	10
#define MANUAL_CONTROl_TASK_TIME_MS_DU32  	6
#define MANUAL_CONTROl_TASK_OFFS_MS_DU32  	0

#define READ_SENSOR_TASK1_PRIO_DU8      		5
#define READ_SENSOR_TASK1_TIME_MS_DU32  		1   //READ_SENSOR_Task1 reads the pressure sensors at 1000hz
#define READ_SENSOR_TASK1_OFFS_MS_DU32  		0

#define READ_SENSOR_TASK2_PRIO_DU8      		5
#define READ_SENSOR_TASK2_TIME_MS_DU32  		20  //Read position sensors
#define READ_SENSOR_TASK2_OFFS_MS_DU32  		0

#define SEND_CAN_SENSORS_VALUES_TASK_PRIO_DU8      		5
#define SEND_CAN_SENSORS_VALUES_TASK_TIME_MS_DU32  		20
#define SEND_CAN_SENSORS_VALUES_TASK_OFFS_MS_DU32  		0

#define TEST_TASK_PRIO_DU8      		5
#define TEST_TASK_TIME_MS_DU32  		20
#define TEST_TASK_OFFS_MS_DU32  		0

#define FORCE_CONTROL_TASK_PRIO_DU8      	4
#define FORCE_CONTROL_TIME_MS_DU32  		1
#define FORCE_CONTROL_OFFS_MS_DU32  		0

#define DYNAMIC_TASK_PRIO_DU8      	5
#define DYNAMIC_TIME_MS_DU32  		10
#define DYNAMIC_OFFS_MS_DU32  		0

#define ACTUATE_TASK_PRIO_DU8      	6
#define ACTUATE_TIME_MS_DU32  		1
#define ACTUATE_OFFS_MS_DU32  		0

#define TASK_EMERGENCY_TIME_MS_DU32 		50

/*** Defines for CAN  init functions *************************************************************** */
//tx
#define CAN_1_TX_BUF_LEN_DU8            	500	//Buffer length for CAN1
#define CAN_1_NUM_TX_DATABOXES_DU16     	 500
//rx
#define CAN_1_RX_BUF_LEN_DU8            	5
#define CAN_1_NUM_RX_DATABOXES_DU16    		15

#define CAN_1_RX_DATABOX_1_BUF_LEN_DU8  	5
//tx
#define CAN_2_TX_BUF_LEN_DU8 				40
#define CAN_2_RX_BUF_LEN_DU8 				15
//rx
#define CAN_2_RX_BUF_LEN_DU8            	15
#define CAN_2_NUM_RX_DATABOXES_DU16    		100
#define CAN_2_RX_DATABOX_1_BUF_LEN_DU8  	5
#define CAN_2_RX_DATABOX_2_BUF_LEN_DU8  	25
//tx
#define CAN_3_TX_BUF_LEN_DU8            	25
#define CAN_3_NUM_TX_DATABOXES_DU16     	 6
//rx
#define CAN_3_RX_BUF_LEN_DU8            	15
#define CAN_3_NUM_RX_DATABOXES_DU16    		100
#define CAN_3_RX_DATABOX_3_BUF_LEN_DU8  	5
#define CAN_3_RX_DATABOX_4_BUF_LEN_DU8  	5

// CAN ID's retrieved
#define CAN_ID_LEFT_EXCIPAD_BUTTONS	 		0x18FE030B
#define CAN_ID_RIGHT_EXCIPAD_BUTTONS		0x18FE0315
#define CAN_ID_JOYSTICK_Y					0x18FE010B
#define CAN_ID_GYRODATA_DATA				0x1FD
#define CAN_ID_ACCELOMETER_DATA				0x2FD
#define DEFAULT_MODE						100
// CAN ID's send out
#define CAN_ID_SENSOR_INFO_SMS_1			0x18FE1020
#define CAN_ID_SENSOR_INFO_SMS_2		    0x18FE1021
#define CAN_ID_SENSOR_INFO_SMS_3			0x18FE1022
#define CAN_ID_SENSOR_INFO_SMS_4			0x18FE1025
#define CAN_ID_SENSOR_INFO_SMS_5			0x18FE1026

#define CAN_ID_SENSOR_INFO_SMS_6			0x18FE1027
#define CAN_ID_SENSOR_INFO_SMS_7			0x18FE1028


#define CAN_ID_SENSOR_INFO_SMS_8			0x18FE1029
#define CAN_ID_SENSOR_INFO_SMS_9			0x18FE102A
#define CAN_ID_SENSOR_INFO_SMS_10			0x18FE102B
#define CAN_ID_SENSOR_INFO_SMS_11			0x18FE102C
#define CAN_ID_SENSOR_INFO_SMS_12			0x18FE102D
#define CAN_ID_SENSOR_INFO_SMS_13			0x18FE102E
#define CAN_ID_SENSOR_INFO_SMS_14			0x18FE2020
#define CAN_ID_SENSOR_INFO_SMS_15			0x18FE202A
#define CAN_ID_SENSOR_INFO_SMS_16			0x18FE202B
#define CAN_ID_SENSOR_INFO_SMS_17			0x18FE202C
#define CAN_ID_SENSOR_INFO_SMS_18			0x18FE202D
#define CAN_ID_SENSOR_INFO_SMS_19			0x18FE202E
#define CAN_ID_SENSOR_INFO_SMS_20			0x18FE202F

#define CAN_ID_DEBUG_MSG_1					0x18FE1050
#define CAN_ID_DEBUG_MSG_2					0x18FE1051
#define CAN_ID_DEBUG_MSG_3					0x18FE1052

#define CAN_ID_DEBUG_MSG_4					0x18FE1053
#define CAN_ID_DEBUG_MSG_5					0x18FE1054
#define CAN_ID_DEBUG_MSG_6					0x18FE1055


//---------------CAN MESSAGE IDENTIFIER IN HEX-------------
#define MSG_ENABLE_PENDULUM_ARM_FRONT_RIGHT 0x10 //16	 //Byte 4, bit 5
#define MSG_ENABLE_PENDULUM_ARM_FRONT_LEFT 	0x01 //1	 //Byte 4, bit 1
#define MSG_ENABLE_PENDULUM_ARM_MID_RIGHT	0x04 //4     //Byte 5, bit 3
#define MSG_ENABLE_PENDULUM_ARM_MID_LEFT	0x40 //64	 //Byte 4, bit 7
#define MSG_ENABLE_PENDULUM_ARM_REAR_RIGHT	0x01 //1	 //Byte 6, bit 1
#define MSG_ENABLE_PENDULUM_ARM_REAR_LEFT	0x10 //16	 //Byte 5, bit 5
#define MSG_ENABLE_PENDULUM_ARM_ALL_DOWN	0x40 //64	 //Byte 3, bit 3
#define MSG_ENABLE_PENDULUM_ARM_ALL_UP		0x04 //4	 //Byte 3, bit 7
#define MSG_ENABLE_PENDULUM_ARM_TILT_Y		0x10 //16	 //Byte 2, bit 5
#define MSG_ENABLE_PENDULUM_ARM_TILT_X		0x40 //64	 //Byte 2, bit 7
#define MSG_ENABLE_SIMPLE_CONTROL			0x01 //1 	 //Byte 3, bit 1

/*** Defines for manual functions *************************************************************** */
//----------------------JOYSTICK CONTROL----------------------
#define JOYSTICK_Y_HIGH_POINT				4300
#define JOYSTICK_Y_MID_POINT				2350
#define JOYSTICK_Y_LOW_POINT				350
#define JOYSTICK_Y_DEADBAND					200
#define JOYSTICK_Y_HIGH_DEADBAND			JOYSTICK_Y_MID_POINT+JOYSTICK_Y_DEADBAND
#define JOYSTICK_Y_LOW_DEADBAND				JOYSTICK_Y_MID_POINT-JOYSTICK_Y_DEADBAND

//---------------------DEFINES FOR buttonStatus------------------
// Index_Cylinder_Left/Right_Front/Mid/Rear
#define INDEX_CYLINDER_FRONT_RIGHT 			0
#define INDEX_CYLINDER_FRONT_LEFT			1
#define INDEX_CYLINDER_MID_RIGHT	 		2
#define INDEX_CYLINDER_MID_LEFT 			3
#define INDEX_CYLINDER_REAR_RIGHT	 		4
#define INDEX_CYLINDER_REAR_LEFT	 		5
#define INDEX_CYLINDER_ALL_DOWN				6
#define INDEX_CYLINDER_ALL_UP				7
#define INDEX_CYLINDER_TILT_Y				8
#define INDEX_CYLINDER_TILT_X				9
#define INDEX_SIMPLE_CONTROL		        10
#define INDEX_SIZE_BUTTONSTATUS				11

//------------------------Solenoids----------------------------
#define SOLENOID_OFF						0	//Used for solenoid valve (off)

/*** Defines for global variables *************************************************************** */
//---------------------DEFINES index for the global variable angleData -------------------
#define ANALOG_RIGHT_FRONT_PENDULUMARM	 	0
#define ANALOG_LEFT_FRONT_PENDULUMARM	 	1
#define ANALOG_RIGHT_MID_PENDULUMARM	 	2
#define ANALOG_LEFT_MID_PENDULUMARM 		3
#define ANALOG_RIGHT_BACK_PENDULUMARM 		4
#define ANALOG_LEFT_BACK_PENDULUMARM		5
#define INDEX_SIZE_WHEELS				    6

//---------------------DEFINES index for the global variable pressure sensors ------------
#define ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_A			0
#define ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_B			1
#define ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_A			2
#define ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_B			3
#define ANALOG_MID_RIGHT_PENDULUM_PRESSURE_A			4
#define ANALOG_MID_RIGHT_PENDULUM_PRESSURE_B			5
#define ANALOG_MID_LEFT_PENDULUM_PRESSURE_A				6
#define ANALOG_MID_LEFT_PENDULUM_PRESSURE_B				7
#define ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_A			8
#define ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_B			9
#define ANALOG_REAR_LEFT_PENDULUM_PRESSURE_A			10
#define ANALOG_REAR_LEFT_PENDULUM_PRESSURE_B			11
#define INDEX_SIZE_PRESSURESENS							12

//-----------------------Defines for pendelurm outputs --------------------------------------
#define OUT_PENDELURM_FRONT_RIGHT_A		OUT_1_POH_CL
#define OUT_PENDELURM_FRONT_RIGHT_B		OUT_2_POH_CL
#define OUT_PENDELURM_FRONT_LEFT_A		OUT_3_POH_CL
#define OUT_PENDELURM_FRONT_LEFT_B		OUT_4_POH_CL
#define OUT_PENDELURM_MID_RIGHT_A		OUT_5_POH_CL
#define OUT_PENDELURM_MID_RIGHT_B		OUT_6_POH_CL
#define OUT_PENDELURM_MID_LEFT_A		OUT_7_POH_CL
#define OUT_PENDELURM_MID_LEFT_B		OUT_8_POH_CL
#define OUT_PENDELURM_REAR_RIGHT_A		OUT_9_POH_CL
#define OUT_PENDELURM_REAR_RIGHT_B		OUT_10_POH_CL
#define OUT_PENDELURM_REAR_LEFT_A		OUT_11_POH_CL
#define OUT_PENDELURM_REAR_LEFT_B		OUT_12_POH_CL

//------------------------- Simple Controll -----------------------------------------
#define FRONT_RIGHT_PENDULUM_A			0
#define FRONT_RIGHT_PENDULUM_B			1
#define FRONT_LEFT_PENDULUM_A			2
#define FRONT_LEFT_PENDULUM_B			3
#define MID_RIGHT_PENDULUM_A			4
#define MID_RIGHT_PENDULUM_B			5
#define MID_LEFT_PENDULUM_A				6
#define MID_LEFT_PENDULUM_B				7
#define REAR_RIGHT_PENDULUM_A			8
#define REAR_RIGHT_PENDULUM_B			9
#define REAR_LEFT_PENDULUM_A			10
#define REAR_LEFT_PENDULUM_B			11
#define SUM_VALVES   					12
#define SUM_PENDELURM_ARMS				6



//Valve flow curve parameters
#define VALVE_FLOW_FIT_PARAMETER_CP1  0.0000117254976
#define VALVE_FLOW_FIT_PARAMETER_CP2  -0.0020898157818
#define VALVE_FLOW_FIT_PARAMETER_CP3  0.1025966561449
#define VALVE_FLOW_FIT_PARAMETER_CP4  2.2459943305454
#define VALVE_FLOW_FIT_PARAMETER_CP5  410  //416.9941090504642

//Force relationship constants
#define bx 0.165
#define by 0.471
#define bxy 0.4991
#define l1 1.008
#define l2 0.386
#define l3 1.211
#define theta3 .2983
#define theta2 .3370
#define pi 3.14159265358979323846
/**** data global variabels *****************************************************************************************
* Definitions of variables used only in this module. Memory class "static" has to be used for      *
* each variable.                                                                                  */
//--- Manual control----------------------------
volatile bool buttonStatus[INDEX_SIZE_BUTTONSTATUS] = {0};

const uint8 sizeofButtonStatus = sizeof(buttonStatus)/sizeof(buttonStatus[0]);
volatile uint16 zButtonCounter = 1;
volatile uint8 zButton = 0;
volatile uint16 zRampUp = 20;
volatile uint16 preStatusExcipad = 0;

//--- Global sensor variabels control----------------------------
volatile uint16 angleData[INDEX_SIZE_WHEELS] = {0};
volatile uint16 posData_mV[INDEX_SIZE_WHEELS] = {0};
volatile uint16 posData[INDEX_SIZE_WHEELS] = {0};
											//Max and min voltage limits for cylinder stroke
											// RF,  LF,  RM,  LM,  RB,  LB
static uint16 minPos[INDEX_SIZE_WHEELS] = {1061,1199,1115,1108,1105,1068}; //current mV
static uint16 maxPos[INDEX_SIZE_WHEELS] = {3864,4200,4126,4039,4096,4046}; //current mV
volatile uint8  Cyl_limit[INDEX_SIZE_WHEELS]={1,1,1,1,1,1};  //Individual cylinder limits
volatile uint8  Force_control_cylinders[INDEX_SIZE_WHEELS]={1,1,1,1,1,1};  //Individual cylinder limits

volatile uint16 posData_last[INDEX_SIZE_WHEELS] = {0};
volatile uint16 Zc=0; //Avg chassis height from arms average
volatile sint16 Zcdot=0; //Avg chassis velocity from arms average
volatile sint16 velData[INDEX_SIZE_WHEELS] = {0};
volatile sint16 velData_last[INDEX_SIZE_WHEELS] = {0};
volatile uint8 Cyl_flow[INDEX_SIZE_WHEELS] = {0};
volatile sint16 Zi_pos[INDEX_SIZE_WHEELS] = {0}; //Position estimated of each cylinder mounting chassis point FR_FL_MR_ML_BR_BL
volatile sint16 Zi_pos_last[INDEX_SIZE_WHEELS] = {0}; //Position last of each cylinder mounting chassis point FR_FL_MR_ML_BR_BL
volatile sint16 Zi_vel[INDEX_SIZE_WHEELS] = {0}; //Velocity estimated of each cylinder mounting chassis point FR_FL_MR_ML_BR_BL
volatile sint16 Zi_vel_last[INDEX_SIZE_WHEELS] = {0}; //Velocity estimated of each cylinder mounting chassis point FR_FL_MR_ML_BR_BL
static sint16 a_geo[INDEX_SIZE_WHEELS] = {1000, 1000, -1000, -1000, -3200, -3200};    //{1000,1000,-1000,-1000,-2225,-2225};
static sint16 b_geo[INDEX_SIZE_WHEELS] = {500, -500, 500, -500, 500, -500};
#define kf 5//Filter coefficient for velocity calculation lower value is more filtering
#define Ts .02// x mS sensor read sampling time


float a_vel = 1 / (1 + kf * Ts);

volatile uint8 TEST_MODE=0;
volatile uint16 anglevel[INDEX_SIZE_WHEELS] = {0};
volatile uint16 pressureData_mV[INDEX_SIZE_PRESSURESENS] = {0};  //Presure in each cylinder chamber, direct sensor reading  [mV]
volatile uint16 pressureData[INDEX_SIZE_PRESSURESENS] = {0};  //Presure in each cylinder chamber scaled to  [BAR]
volatile uint16 pressureData_last[INDEX_SIZE_PRESSURESENS] = {0};  //Presure in each cylinder chamber scaled to  [BAR]
volatile uint16 forceData[INDEX_SIZE_PRESSURESENS] = {0};   //force per cylinder chamber (A and B of every cylinder  6x2=12 values)
//volatile sint16 Load_force[INDEX_SIZE_WHEELS] = {0};   //Force balance per cylinder  ForceA -Force B (newtons/10)
volatile sint16 messuredForceCylinderLoad_deciN[INDEX_SIZE_WHEELS] = {0}; //Load_force renamed
volatile sint16 Ref_ground_force[INDEX_SIZE_WHEELS] = {0};   //Force balance per cylinder  ForceA -Force B (newtons/10)
volatile sint16 Ref_balance_force[INDEX_SIZE_WHEELS] = {0};
volatile sint16 forceVertical[INDEX_SIZE_WHEELS] = {0};   //Ground reaction force vertical direction (newtons/10)
volatile sint16 Weight=0; //Calculated unsprung mass weight
volatile uint8 In_ground[INDEX_SIZE_WHEELS] = {0};
volatile uint8 ARM_ACTIVE[INDEX_SIZE_WHEELS] = {1};
volatile float ARM_ACTIVE_F[INDEX_SIZE_WHEELS] = {1};
volatile uint8 In_ground_decoupling[INDEX_SIZE_WHEELS] = {0};

/*
 * f_L  %Cutoff frequency of low pass filter
Tf = 1/(2*pi*f_L);
 */
//Pressure filtering
#define Tfp 1.0/(2.0*3.1415)
float alpha = Tfp/(Tfp + 0.001);

//Chassis velocity filtering
#define Tfv 1.0/(2.0*3.1415)
float alphav = Tfv/(Tfv + 0.02);

//Chassis position filtering
#define Tfpos 1.0/(2.0*3.1415)
float alphapos = Tfpos/(Tfpos + 0.02);


volatile uint16 angle_acc_counter = 0;
volatile sint32 angleDataX = 0;
volatile sint32 angleDataY = 0;
volatile sint32 angleDataZ = 0;
volatile sint16 Theta_deg  = 0;
volatile sint16 Theta_deg_last = 0;

volatile float Theta_rad = 0;
volatile sint16 Phi_deg  = 0;
volatile sint16 Phi_deg_last = 0;
volatile float Phi_rad       = 0;
volatile sint16 Gyro_Phi_deg = 0;
volatile float Gyro_Phi_rad  = 0;
volatile sint16 Gyro_Theta_deg = 0;
volatile float Gyro_Theta_rad  = 0;

volatile sint16 Gyro_Phi_RAW   = 0;
volatile sint16 Gyro_Theta_RAW = 0;

volatile sint16 ACCELX_RAW = 0;
volatile sint16 ACCELY_RAW = 0;
volatile sint16 ACCELZ_RAW = 0;

//#define Area_A 0.00785 // Cylinder push area (m^2) A side
//#define Area_B 0.00589 // Cylinder pull area (m^2) B side
#define CYLINDER_PUSH_AREA_SIDE_A1_m2 0.00785 // Cylinder push area (m^2) A side
#define CYLINDER_PUSH_AREA_SIDE_B2_m2 0.00589 // Cylinder pull area (m^2) B side



//Hydraulic Force Controller defines and variables

#define DELTA_PRESSURE_8bar 800000  //8 bar pressure compensator setting
#define MAXIMUM_FLOW_QMAX_m3s  100/1000/60  // maximum flow  (m^3/s)
#define SLIDING_MODE_CONTROL_PARAMETER_Kt 0.000077
volatile sint32 sl_Ref[INDEX_SIZE_WHEELS] = {0};
volatile float sl_uold[INDEX_SIZE_WHEELS] = {0};
volatile float sl_u = 0;
volatile sint16 sl_current = 0;
//Variables for debugging
volatile sint32 sl_debug_current = 0;

volatile sint32 sl_debug_1 = 0;
volatile sint32 sl_debug_2 = 0;
volatile sint32 sl_debug_3 = 0;
volatile sint32 sl_debug_4 = 0;
volatile sint32 sl_debug_5 = 0;
volatile sint32 sl_debug_6 = 0;
volatile sint32 F_Z_sky[INDEX_SIZE_WHEELS]   = {0};  //Vertical Force reference calculated by the dynamic controllers
volatile sint32 F_REF_CYL[INDEX_SIZE_WHEELS] = {0};  //Force reference needed at cylinder to produce needed force at ground

volatile sint32 F_REF_Z   = 0;
volatile sint32 F_REF_Phi = 0;
volatile sint32 F_REF_Theta = 0;
volatile sint32 F_REF[INDEX_SIZE_WHEELS] = {0};  //Vertical Force reference calculated by the dynamic controllers
volatile sint32 F_matrix[3] = {0,0,0};
volatile sint32 sum=0;

volatile sint16 Zc_error  = 0;
volatile sint32 Z_k       = 0;
volatile sint32 F_Z_damp  = 0;
volatile sint32 Z_I       = 0;
volatile sint32 Phi_error = 0;
volatile sint32 Phi_k     = 0;
volatile sint32 Phi_I     = 0;
volatile sint32 Phi_sky   = 0;
volatile sint32 Theta_error = 0;
volatile sint32 Theta_k   = 0;
volatile sint32 Theta_I   = 0;
volatile sint32 Theta_sky = 0;
volatile uint8 CONTROL_STATUS = 0;

volatile float massCenterLocationX_m = 0;
volatile float massCenterLocationY_m = 0;
volatile sint16 forceReferenceOptimalDistrubution_N[INDEX_SIZE_WHEELS] = {0};


volatile uint16 ARM_REF   = 200;
volatile sint16 ARM_ERROR = 0;

volatile sint16 ARM_SET_REF[INDEX_SIZE_WHEELS]   = {0};
volatile sint16 To_ground_ref[INDEX_SIZE_WHEELS] = {0};

//Decoupling matrix 1.5m .5m 2.75m

float moore_inverse[6][3] = { {0.2339, 0.3333, 0.1152},  //Startup moore inverse assuming 6 wheels in contacts with ground
							  {0.2339,-0.3333, 0.1152},
							  { 0.1694 , 0.3333, 0.0046},
							  { 0.1694 ,-0.3333, 0.0046 },
							  { 0.0968, 0.3333,-0.1198 },
							  { 0.0968,-0.3333,-0.1198} };
/*
float moore_inverse[6][3] = { {0.0, 0.0, 0.0},  //Startup moore inverse assuming FR doesnt work wheels in contacts with ground
							  {0.3654,-0.1458, 0.1800},
							  {0.3573  ,  0.6013, 0.0972},
							  {0.1746 ,-0.3258, 0.0072 },
							  { 0.1427 , 0.3987,-0.0972 },
							  { -0.0401,-0.5284,-0.1872} };
*/



//volatile float moore_inverse_modified[6][3] = { {0.2339, 0.3333, 0.1152},  //Startup moore inverse assuming 6 wheels in contacts with ground
	//						  {0.2339,-0.3333, 0.1152},
	//						  { 0.1694 , 0.3333, 0.0046},
	//						  { 0.1694 ,-0.3333, 0.0046 },
	//						  { 0.0968, 0.3333,-0.1198 },
	//						  { 0.0968,-0.3333,-0.1198} };

// I hcanged to constnat on z for better control behavior johan
volatile float moore_inverse_modified[6][3] = { {0.1694, 0.3333, 0.1152},  //Startup moore inverse assuming 6 wheels in contacts with ground
							  {0.1694,-0.3333, 0.1152},
							  { 0.1694 , 0.3333, 0.0046},
							  { 0.1694 ,-0.3333, 0.0046 },
							  { 0.1694, 0.3333,-0.1198 },
							  { 0.1694,-0.3333,-0.1198} };

/*1m 1m 3.25

float moore_inverse[6][3] = { {0.2915, 0.3333, 0.1152},
							  {0.2915,-0.3333, 0.1152},
							  {0.1717, 0.3333, 0.0046},
							  {0.1717,-0.3333, 0.0046 },
							  {0.0369, 0.3333,-0.1198 },
							  {0.0369,-0.3333,-0.1198} };
*/
/*  Inverse with  a_geo[]={1000,1000,-1000,-1000,-3200,-3200};
					b_geo[]={500,-500,500,-500,500,-500};
   0.2915    0.3333    0.1152
   0.2915   -0.3333    0.1152
   0.1717    0.3333    0.0046
   0.1717   -0.3333    0.0046
   0.0369    0.3333   -0.1198
   0.0369   -0.3333   -0.1198
*/
volatile uint16 BS = 0;
volatile uint16 KS = 0;
//PI controller variables and defines
#define kp 0.0001
#define ki 0.005
#define T 0.005
volatile sint32 error_old = 0;
volatile float u_old = 0;



// --- test sensor stuff ---
volatile uint8 defaultSafety = 0;

///Global actuation task defines and variables
#define REFERENCE_CURRENT_ZERO 0 //Number taken as valve closed Zero output on both solenoids
#define REFERENCE_CURRENT_MAXIMUM_B_mA -100 //Min Ref Equivalent to Max output on Solenoid B Deadband+ -RefMin
#define REFERENCE_CURRENT_MAXIMUM_A_mA 100 //400 //Max Ref Equivalent to Max output on Solenoid A  Deadband+ Refmax
#define DEADZONE_FOR_SOLEONID_CURRENT_mA 400
#define FR 0
#define FL 1
#define MR 2
#define ML 3
#define BR 4
#define BL 5

volatile sint16 referenceSoleonidOutputCurrent_ma[6] = {REFERENCE_CURRENT_ZERO};
volatile sint16 Ref_A[6] = {REFERENCE_CURRENT_ZERO};
volatile sint16 Ref_B[6] = {REFERENCE_CURRENT_ZERO};



/**** prototypes ***********************************************************************************
* Prototypes of functions defined and used only in this module. Memory class "static" has to be    *
* used for each function.                                                                         */

void sys_main(void);

void appl_ErrorHandler(uint16 errorCode_u16, uint8 errorParam_u8);
void appl_setDefaults(void);
void appl_AfterRunFunc(void);
void appl_updateDiagData(void);
bool appl_setVpOnFirst(void);

//--- Tasks prototypes ----------------------------
void appl_Task_1(void);
void manual_Control_Task(void);
void read_Sensor_Task1(void);  //Read pressure sensors
void read_Sensor_Task2(void);  //Read position sensors
void send_CAN_sensors_values_Task(void);
void test_Task(void);
void massCenterLocationDataToCAN(void);
void FORCE_ControlTask(void);
void Dynamic_control_Task(void);

void appl_EmergencyTask(void);
void appl_IdleTask_1(void);
void actuate(void);

//---- Control Prototypes
void massCenterLocationAndSendOnCAN(void);
void calculateOptimalForceForAllWheelsAndSendOnCAN(void);

void heightControllAddToAllocationMatrix(void);
void hightControllSkyhookForceAddition(void);
void rollPhiControllAddToAllocationMatrix(void);
void pitchThetaControllAddToAllocationMatrix(void);
void decoupleHightRollPitchAndConvertToCylinderForceForAllWheels(void);
void calculateForceReferenceForAllWheels(void);
void mapErestimatedFlowToCurrentOutputOnWheelWithNumber(uint8 wheelCounter);
void calculateErestimatedFlowForWheelWithNumber(uint8 cylinderCounter);
void sendSupplyVoltageOnCAN(void);

//--- CAN prototypes ----------------------------
void can_1_RxCallback(uint8 format_u8, uint32 id_u32, uint8 numBytes_u8, uint8 *data_pu8);
void can_1_RxDatabox_1_Callback(void);
void can_1_RxDatabox_2_Callback(void);
void can_1_RxDatabox_3_Callback(void);
void can_1_RxDatabox_4_Callback(void);
void can_1_RxDatabox_7_Callback(void);


void can_2_RxDatabox_1_Callback(void);
void can_2_RxDatabox_2_Callback(void);
void can_1_BusOffCallback(uint16 status_u16);
void can_3_RxCallback(uint8 format_u8, uint32 id_u32, uint8 numBytes_u8, uint8 *data_pu8);
void can_3_RxDatabox_3_Callback(void);
void can_1_BusOffCallback(uint16 status_u16);
void can_3_BusOffCallback(uint16 status_u16);

//--- In / Out ----------------------------
void appl_configOutputs(void);
void appl_configInputs(void);


//Supporting functions prototypes
//float F_REL(uint16 x); //Calculate force relationship Fg/Fl for a certain cylinder position
float forceRelationshipFromLoadToGround(uint16 cylinderPoss_mm);
//sint16 Force_Vertical(uint16 x,sint16 Load_force);  //Return the vertical tire force corresponding to the load force in the cylynder
sint16 forceOnWheelVerticalFromCylinderLoad(uint16 cylinderPoss_mm, sint16 Load_force);
//sint32 Force_Load(uint16 x,sint32 Vertical_force);  //Calculates the load force needed for a desired vetical force
sint32 forceCylinderLoadFromForceOnWheel(uint16 cylinderPoss_mm, sint32 Vertical_force);
void SEND_ARRAY_CAN1(uint32 ID1,uint32 ID2,volatile sint16 data[],uint8 size_array); //Send whole 6x16bit array on two CAN messages
void SENDCAN1(uint32 ID,sint16 A,sint16 B,sint16 C,sint16 D);  //Send up to 4x16bit Variables on CAN1 msg
void sendCan1UnsignInt(uint32 ID,uint16 A,uint16 B,uint16 C,uint16 D);



//--Manual controll prototypes ----------------
bool toggleVariable(bool toggleTarget);
void setVariablesZero(void);
void caseSwitch(can_Message_ts* msg_s);
void modes(can_Message_ts* msg_s);
void turnOffSolenoids(void);
void solenoidDown(uint16 solenoidOnValue);
void solenoidUp(uint16 solenoidOnValue);
void rampDownSolenoids(void);
