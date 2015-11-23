/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        application.c
*
*  \brief       Implementation of the suspension management system

* REVISION HISTORY:

***************************************************************************************************/

#define _APPLICATION_         /* replace it with the filename in capital letters */

// The forwarder software drivers
#include "ActiveDamping.h"  /* Function Definitions */

#include "XT28ActiveDampeningController.h"
#include "XT28ActiveDampeningController.c"
#include "XT28ReadSensors.h"
#include "XT28ReadSensors.c"
#include "XT28ManualControl.h"
#include "XT28ManualControl.c"  /*Manual pendulum arm control functions */

#include "applicationSystemIncludes.h"
#include "applicationSystemIncludes.c"
#include "application.h"

#include "tasks.c"			/*Periodic tasks */
#include "CAN_callbacks.c"	/*CAN receive callback functions */
#include "functions.c"		/*Extra user support functions */

/***************************************************************************************************
*  FUNCTION:      sys_main
*/
/**\brief         Configuration of application tasks.
*/
/**************************************************************************************************/




void sys_main(void)
{
  // Defined here because access to these var's is allowed only by API !
  static can_Message_ts     can_1_TxBuf_as[CAN_1_TX_BUF_LEN_DU8];

//  static can_TxDatabox_ts   can_1_TxDataboxes_as[CAN_1_NUM_TX_DATABOXES_DU16];
  static can_Message_ts     can_1_RxBuf_as[CAN_1_RX_BUF_LEN_DU8];
  static can_RxDatabox_ts   can_1_RxDataboxes_as[CAN_1_NUM_RX_DATABOXES_DU16];
  static can_DataboxData_ts can_1_RxDatabox_1_Buf_as[CAN_1_RX_DATABOX_1_BUF_LEN_DU8];
  static can_DataboxData_ts can_1_RxDatabox_2_Buf_as[CAN_1_RX_DATABOX_1_BUF_LEN_DU8];
  static can_DataboxData_ts can_1_RxDatabox_3_Buf_as[CAN_1_RX_DATABOX_1_BUF_LEN_DU8];
  static can_DataboxData_ts can_1_RxDatabox_4_Buf_as[CAN_1_RX_DATABOX_1_BUF_LEN_DU8];
  static can_DataboxData_ts can_1_RxDatabox_7_Buf_as[CAN_1_RX_DATABOX_1_BUF_LEN_DU8];

  static can_Message_ts     can_2_TxBuf_as[CAN_2_TX_BUF_LEN_DU8];
  static can_Message_ts     can_2_RxBuf_as[CAN_2_RX_BUF_LEN_DU8];
  static can_RxDatabox_ts   can_2_RxDataboxes_as[CAN_2_NUM_RX_DATABOXES_DU16];
  static can_DataboxData_ts can_2_RxDatabox_1_Buf_as[CAN_2_RX_DATABOX_1_BUF_LEN_DU8];
  static can_DataboxData_ts can_2_RxDatabox_2_Buf_as[CAN_2_RX_DATABOX_2_BUF_LEN_DU8];

  static can_Message_ts     can_3_TxBuf_as[CAN_3_TX_BUF_LEN_DU8];
  static can_Message_ts     can_3_RxBuf_as[CAN_3_RX_BUF_LEN_DU8];
  static can_RxDatabox_ts   can_3_RxDataboxes_as[CAN_3_NUM_RX_DATABOXES_DU16];
  static can_DataboxData_ts can_3_RxDatabox_3_Buf_as[CAN_3_RX_DATABOX_3_BUF_LEN_DU8];
  static can_DataboxData_ts can_3_RxDatabox_4_Buf_as[CAN_3_RX_DATABOX_4_BUF_LEN_DU8];

  resetInfo_ts ResetInfo_s;

  // Register application error handler. At first!
  sys_registerErrorCallback(appl_ErrorHandler);
  // get reset information
  sys_getResetInfo(&ResetInfo_s);

  // Register application function for setting default values.
  // Note: This function has to be called before sys_init() will be called.
  sys_registerSetDefaultsFunction(appl_setDefaults);

  // Initialize RC/SRC.
  sys_init("SMS", "RC30-00D6"); // RC28-14/30

  // This function disables the reading of the software inhibit input. The input signal will be not evaluated.
  emcy_disableInput(EMCY_DISABLE_KEY_DU32, ~EMCY_DISABLE_KEY_DU32);

  //---> Configure inputs + outputs.
  // Configure all inputs.
  appl_configInputs();

  // Configure all outputs.
  appl_configOutputs();
  //<--- Configure inputs + outputs.

  // Register all application tasks.
  sys_registerTask(appl_Task_1, TASK_1_PRIO_DU8, TASK_1_TIME_MS_DU32, TASK_1_OFFS_MS_DU32, 0);

  sys_registerTask(manual_Control_Task, MANUAL_CONTROl_TASK_PRIO_DU8, MANUAL_CONTROl_TASK_TIME_MS_DU32, MANUAL_CONTROl_TASK_OFFS_MS_DU32, 0);
  sys_registerTask(read_Sensor_Task1, READ_SENSOR_TASK1_PRIO_DU8, READ_SENSOR_TASK1_TIME_MS_DU32, READ_SENSOR_TASK1_OFFS_MS_DU32, 0);
  sys_registerTask(read_Sensor_Task2, READ_SENSOR_TASK2_PRIO_DU8, READ_SENSOR_TASK2_TIME_MS_DU32, READ_SENSOR_TASK2_OFFS_MS_DU32, 0);
  sys_registerTask(send_CAN_sensors_values_Task, SEND_CAN_SENSORS_VALUES_TASK_PRIO_DU8, SEND_CAN_SENSORS_VALUES_TASK_TIME_MS_DU32, SEND_CAN_SENSORS_VALUES_TASK_OFFS_MS_DU32, 0);
  //sys_registerTask(test_Task,TEST_TASK_PRIO_DU8, TEST_TASK_TIME_MS_DU32, TEST_TASK_OFFS_MS_DU32, 0);

  sys_registerTask(FORCE_ControlTask,FORCE_CONTROL_TASK_PRIO_DU8, FORCE_CONTROL_TIME_MS_DU32, FORCE_CONTROL_OFFS_MS_DU32, 0);
  sys_registerTask(Dynamic_control_Task, DYNAMIC_TASK_PRIO_DU8, DYNAMIC_TIME_MS_DU32, DYNAMIC_OFFS_MS_DU32, 0);
  sys_registerTask(actuate, ACTUATE_TASK_PRIO_DU8, ACTUATE_TIME_MS_DU32, ACTUATE_OFFS_MS_DU32, 0);

  // Register emergency task.
  sys_registerEmergencyTask(appl_EmergencyTask, TASK_EMERGENCY_TIME_MS_DU32);

  // Register all application idle tasks.
  sys_registerIdleTask(appl_IdleTask_1, 0);
  // ...

  // Register application after run (power down) function.
  sys_registerAfterRunFunction(appl_AfterRunFunc);

  // Register all check points.
  // At least one check point has to be initialised.
  sys_initTC(0, TASK_1_TIME_MS_DU32); // It is prepared for triggering in appl_Task_1().
  // ...

  //----> Configure CAN 1.
  //---> For each CAN channel.
  //--> Transmit (send).
  // Register transmit buffer (optional).
  can_registerTxBuf(CAN_1, can_1_TxBuf_as, CAN_1_TX_BUF_LEN_DU8);
  can_registerTxBuf(CAN_2, can_2_TxBuf_as, CAN_3_TX_BUF_LEN_DU8);
  can_registerTxBuf(CAN_3, can_3_TxBuf_as, CAN_3_TX_BUF_LEN_DU8);

  //-> Transmit databoxes (optional).
  // Register transmit databoxes. (Application has to allocate memory so that C-API can use this
  // memory to manage the given number of transmit databoxes for this CAN channel.)
  //can_registerTxDataboxes(CAN_1, can_1_TxDataboxes_as, CAN_1_NUM_TX_DATABOXES_DU16);

  // Initialize all transmit databoxes of this CAN channel.
  //can_initTxDatabox(CAN_1, 1, 0x34, CAN_STD);

    // ...
  //<- Transmit databoxes.
  //<-- Transmit.

  //--> Receive.
  // Register receive buffer (optional).
  can_registerRxBuf(CAN_1, can_1_RxBuf_as, CAN_1_RX_BUF_LEN_DU8);
  can_registerRxBuf(CAN_2, can_2_RxBuf_as, CAN_2_RX_BUF_LEN_DU8);
  can_registerRxBuf(CAN_3, can_3_RxBuf_as, CAN_3_RX_BUF_LEN_DU8);

  // Register appliction function which will be called if a CAN message is received (optional).
  can_registerRxCallback(CAN_1, can_1_RxCallback);
  can_registerRxCallback(CAN_3, can_3_RxCallback);

  //-> Receive databoxes (optional).
  // Register receive databoxes. (Application has to allocate memory so that C-API can use this
  // memory to manage the given number of receive databoxes for this CAN channel.)
  can_registerRxDataboxes(CAN_1, can_1_RxDataboxes_as, CAN_1_NUM_RX_DATABOXES_DU16);

  //CAN 2 databoxes
  can_registerRxDataboxes(CAN_2, can_2_RxDataboxes_as, CAN_2_NUM_RX_DATABOXES_DU16);
  //CAN 3 databoxes.
  can_registerRxDataboxes(CAN_3, can_3_RxDataboxes_as, CAN_3_NUM_RX_DATABOXES_DU16);

  // Initialize all receive databoxes of this CAN 1 channel.
  can_initRxDatabox(CAN_1, 1,TESTING_COMMAND_ID, CAN_EXD_DU8, 8, can_1_RxDatabox_1_Buf_as,
                    CAN_1_RX_DATABOX_1_BUF_LEN_DU8, can_1_RxDatabox_1_Callback);

  can_initRxDatabox(CAN_1, 2, CONF_MSG_ID, CAN_EXD_DU8, 8, can_1_RxDatabox_2_Buf_as,
                    CAN_1_RX_DATABOX_1_BUF_LEN_DU8, can_1_RxDatabox_2_Callback);

  can_initRxDatabox(CAN_1, 3, CONF_MSG_ID_2, CAN_EXD_DU8, 8, can_1_RxDatabox_3_Buf_as,
                      CAN_1_RX_DATABOX_1_BUF_LEN_DU8, can_1_RxDatabox_3_Callback);

  can_initRxDatabox(CAN_1, 4, CONF_MSG_ID_3, CAN_EXD_DU8, 8, can_1_RxDatabox_4_Buf_as,
                        CAN_1_RX_DATABOX_1_BUF_LEN_DU8, can_1_RxDatabox_4_Callback);

  can_initRxDatabox(CAN_1, 7, CONF_MSG_ID_4, CAN_EXD_DU8, 8, can_1_RxDatabox_7_Buf_as,
                        CAN_1_RX_DATABOX_1_BUF_LEN_DU8, can_1_RxDatabox_7_Callback);

  //Init the databoxes for can 3
  can_initRxDatabox(CAN_3, 3,CAN_ID_LEFT_EXCIPAD_BUTTONS, CAN_EXD_DU8, 8, can_3_RxDatabox_3_Buf_as,
                      CAN_3_RX_DATABOX_3_BUF_LEN_DU8, can_3_RxDatabox_3_Callback);
  can_initRxDatabox(CAN_3, 4,CAN_ID_JOYSTICK_Y, CAN_EXD_DU8, 8, can_3_RxDatabox_4_Buf_as,
                      CAN_3_RX_DATABOX_3_BUF_LEN_DU8, can_3_RxDatabox_3_Callback);
  //for CAN 2 gyro
  can_initRxDatabox(CAN_2, 1,CAN_ID_GYRODATA_DATA, CAN_STD_DU8, 4, can_2_RxDatabox_1_Buf_as,
                      CAN_2_RX_DATABOX_1_BUF_LEN_DU8, can_2_RxDatabox_1_Callback);
  can_initRxDatabox(CAN_2, 2,CAN_ID_ACCELOMETER_DATA, CAN_STD_DU8, 6, can_2_RxDatabox_2_Buf_as,
                      CAN_2_RX_DATABOX_2_BUF_LEN_DU8, can_2_RxDatabox_2_Callback);


  //<- Receive databoxes.
  //<-- Receive.
   can_registerBusOffCallback(CAN_1, can_1_BusOffCallback);  // Register application bus off callback.

  // Initialize CAN channel (including setting the baud rate).
  can_init(CAN_1, 1000000);
  can_init(CAN_2, 500000);
  can_init(CAN_3, 250000);

  //init IMU
  uint8 data_au8[2];
  data_au8[0] = 0x01;
  data_au8[1] = 0x7F;
  if (0 == can_sendData(CAN_2, 0x0, CAN_EXD_DU8, 2, data_au8)){}

  // initialize the DIAG module, if support of BODAS-service is required
  diag_initComm(CAN_1,          // can channel for diagnosis
                1,              // tx data box for kwp msg's
                5,              // rx data box for kwp msg's
                6,              // rx data box for scanning
                50,             // communication task priority, can be lower than application
                10);            // communication cycle time [ms]

  // register a function to inform the application about data changes by BODAS-service
  diag_setVarsCallBack(appl_updateDiagData);

} // sys_main





/* EOF ########################################################################################## */
