/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        application.h
*
*  \brief       Interface for application.c
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 2911 $
*                            $Date: 2010-08-30 17:57:10 +0200 (Mo, 30 Aug 2010) $
*                            $Author: gtg2si $
*
* REVISION HISTORY:
*
*
***************************************************************************************************/

#ifndef _APPLICATION_H_  /* replace it with the filename in capital letters */
#define _APPLICATION_H_  /* replace it with the filename in capital letters */

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

#define FORCE_CONTROL_TASK_PRIO_DU8      	1
#define FORCE_CONTROL_TIME_MS_DU32  		10
#define FORCE_CONTROL_OFFS_MS_DU32  		1

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


/**** include files ********************************************************************************
* List of include files needed in this module. DON’T INCLUDE HEADER FILES WITH VARIABLE            *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

/**** defines **************************************************************************************
* List of defines needed in this header file and defines to be made available to other modules.   */

/**** typdefs/structures ***************************************************************************
* Typedefs/structures to be made available to other modules.                                      */

/**** public data **********************************************************************************
* Declarations of variables to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */

/**** public functions *****************************************************************************
* Declarations of functions to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */
void sys_main(void);

/**************************************************************************************************/


/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _APPLICATION_H_

#endif // _APPLICATION_H_

/* EOF ########################################################################################## */
