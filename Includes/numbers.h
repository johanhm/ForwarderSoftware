/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        numbers.h
*
*  \brief       Description of the modul numbers, function numbers and error codes in one place.
*
*
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   API RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 5259 $
*                            $Date: 2013-01-25 11:15:39 +0100 (Fr, 25 Jan 2013) $
*                            $Author: oub2si $
*
* REVISION HISTORY:
*
*
***************************************************************************************************/

#ifndef _NUMBERS_H_D     /* replace it with the filename in capital letters */
#define _NUMBERS_H_D     /* replace it with the filename in capital letters */


/* Definition of the modul numbers for the whole API */
#define SYS_DU16                                  (0x0100)
#define CAN_DU16                                  (0x0200)
#define IN_DU16                                   (0x0300)
#define OUT_DU16                                  (0x0400)
#define EEP_DU16                                  (0x0500)
#define DIAG_DU16                                 (0x0600)    // diagnosis module for BODAS-service
#define COS_DU16                                  (0x0700)    // canopen stack
#define POTI_DU16                                 (0x0800)    // input extension module (e.g. poti)
#define J1939_DU16                                (0x0900)    // J1939 communication stack
#define UDS_DU16                                  (0x0A00)    // UDS/KWP2000 communication stack
#define OUTEXT_DU16                               (0x0B00)    // output extension module
#define EMCY_DU16                                 (0x0C00)    // emergency module
#define MOC_DU16                                  (0x0D00)    // monitoring controller
#define MOF_DU16                                  (0x0E00)    // monitoring functions
#define SAFOUT_DU16                               (0x0F00)    // safout module
#define MO_DU16                                   (0x1000)    // monitoring general
#define RTS_DU16                                  (0x1100)    // run time system
#define RCE_DU16                                  (0x1200)    // RCE module
#define ACOM_DU16                                 (0x1300)    // ACOM module (UART)
#define DFLASH_DU16                               (0x1400)    // DFLASH module
                                                              // (EEP emulation in DFlash)
#define STM_DU16                                  (0x1500)    // Servo Motor (STM) module
#define RTM_DU16                                  (0x1600)    // Run Time Measurement module
#define BASICDIAG_DU16                            (0x1700)    // Basic diagnostic module
#define CCP_DU16                                  (0x1800)    // Can Calibration Protocol module
#define ISOBUS_DU16                               (0x1900)    // ISOBUS communication stack

/* error codes of application >= 0x8000 ! */
#define APPL_DU16                                 (0x8000)

/*** Definition of the error locations/codes for the SYS module ***********************************/
//--- sys_registerTask()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_REGISTERTASK_1_DU16                   (SYS_DU16 | 0x01)
// Calling of function is not allowed in that program state.
#define SYS_REGISTERTASK_2_DU16                   (SYS_DU16 | 0x02)
// Limit of task number is exceeded.
#define SYS_REGISTERTASK_3_DU16                   (SYS_DU16 | 0x03)

//--- sys_registerIdletask()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_REGISTERIDLETASK_1_DU16               (SYS_DU16 | 0x04)
// Calling of function is not allowed in that program state.
#define SYS_REGISTERIDLETASK_2_DU16               (SYS_DU16 | 0x05)
// Limit of idle task number is exceeded.
#define SYS_REGISTERIDLETASK_3_DU16               (SYS_DU16 | 0x06)

//--- sys_init2()
// Invalid EEPROM version.
#define SYS_INIT2_1_DU16                          (SYS_DU16 | 0x07)
// Invalid hardware.
#define SYS_INIT2_2_DU16                          (SYS_DU16 | 0x08)
// String softwarename is too long.
#define SYS_INIT2_3_DU16                          (SYS_DU16 | 0x09)
// New software version
#define SYS_INIT2_4_DU16                          (SYS_DU16 | 0x0A)
// Calling of function is not allowed in that program state.
#define SYS_INIT2_5_DU16                          (SYS_DU16 | 0x0B)

//--- sys_checkEepromVersion_l() (internal function)
// EEPROM is not yet initialised. (value = 0xFF)
#define SYS_CHECKEEPROMVERSION_DU16               (SYS_DU16 | 0x0C)

//--- sys_registerAfterRunFunction()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_REGISTERAFTERRUNFUNC_1_DU16           (SYS_DU16 | 0x0D)
// Calling of function is not allowed in that program state.
#define SYS_REGISTERAFTERRUNFUNC_2_DU16           (SYS_DU16 | 0x0E)
// An after run function is already registered.
#define SYS_REGISTERAFTERRUNFUNC_3_DU16           (SYS_DU16 | 0x0F)

//--- sys_getTaskLoad()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_GETTASKLOAD_1_DU16                    (SYS_DU16 | 0x10)
// range overflow
// <error parameter> = 0x40 : part
// <error parameter> = 0x41 : sum
#define SYS_GETTASKLOAD_2_DU16                    (SYS_DU16 | 0x11)

//--- sys_getAfterRunState_u16() (API internal)
// State of after run could not read successfully from device (CY320, CY141).
#define SYS_GETAFTERRUNSTATE_DU16                 (SYS_DU16 | 0x12)

//--- sys_getKL15_l()
// State of KL15 could not read successfully from device (CY320, CY141).
#define SYS_GETKL15_DU16                          (SYS_DU16 | 0x13)

//--- Mm_SetRespTime() (API internal)
// Setting response time in CY320 device was failed.
// It is not needed in API because hardware monitor but it is left here because
// downward compatibility of the API user!!!
#define SYS_WDE_SETRESPTIME_DU16                  (SYS_DU16 | 0x14)

//--- sys_getHwTemp()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_GETTEMPHW_DU16                        (SYS_DU16 | 0x15)

//--- sys_setVP()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_SETVP_1_DU16                          (SYS_DU16 | 0x16)
// Hardware doesn't support switch on/off.
#define SYS_SETVP_2_DU16                          (SYS_DU16 | 0x17)

//--- sys_setVSS()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_SETVSS_1_DU16                         (SYS_DU16 | 0x18)
// Hardware doesn't support switch on/off.
#define SYS_SETVSS_2_DU16                         (SYS_DU16 | 0x19)

//--- sys_getVP()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_GETVP_DU16                            (SYS_DU16 | 0x1A)

//--- sys_getSupply()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_GETSUPPLY_DU16                        (SYS_DU16 | 0x1B)

//--- gap (0x1C)

//--- sys_cfgVSS()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_CFGVSS_1_DU16                         (SYS_DU16 | 0x1D)
// Hardware doesn't support configuration.
#define SYS_CFGVSS_2_DU16                         (SYS_DU16 | 0x1E)

//--- sys_getVersion()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_GETVERSION_DU16                       (SYS_DU16 | 0x1F)

//--- sys_initTC()
// Function was called with an invalid parameter. <error parameter> = number of parameter
#define SYS_INITTC_1_DU16                         (SYS_DU16 | 0x20)
// Calling function is not allowed in that program state.
// <error parameter> = number of check point
#define SYS_INITTC_2_DU16                         (SYS_DU16 | 0x21)
// The check point was already initialised and reinitialisation is not allowed.
// <error parameter> = number of check point
#define SYS_INITTC_3_DU16                         (SYS_DU16 | 0x22)

//--- sys_setNumberTC_RTS_u16() (API internal for run time system (RTS))
// Invalid parameter 1.  <error parameter> = parameter 1
#define SYS_SETNUMBERTC_RTS_1_DU16                (SYS_DU16 | 0x23)
// Calling the function is not allowed in that program state. <error parameter> = parameter 1
#define SYS_SETNUMBERTC_RTS_2_DU16                (SYS_DU16 | 0x24)

//--- sys_triggerTC()
// Function was called with an invalid parameter 1.  <error parameter> = parameter 1
#define SYS_TRIGGERTC_DU16                        (SYS_DU16 | 0x25)

//--- sys_checkTC() (API internal)
// The check of a check point was faulty.
// <error parameter> = the first check point which check was faulty.
#define SYS_CHECKTC_DU16                          (SYS_DU16 | 0x26)

//--- API internal check after init. (after sys_main() was called) and before
//    API operating system was started.
// No check point was initialised but at least one check point has to be initialised.
#define SYS_NOCHECKPOINTINIT_DU16                 (SYS_DU16 | 0x27)

//--- sys_setAfterRun_u16() (API internal)
// Function returns an error.
// <error parameter> = 0 : sys_setAfterRun_u16(OFF)
//                     1 : sys_setAfterRun_u16(ON)
#define SYS_SETAFTERRUN_DU16                      (SYS_DU16 | 0x28)

//--- State of after run  (API internal)
// Wrong state of after run was read. The target value is saved in <error parameter>:
// 0 = OFF, 1 = ON
#define SYS_AFTERRUNSTATE_DU16                    (SYS_DU16 | 0x29)

//--- sys_registerEmergencytask()
// Function was called with an invalid parameter. <error parameter> = number of parameter
#define SYS_REGISTEREMERGENCYTASK_1_DU16          (SYS_DU16 | 0x2A)
// Calling the function is not allowed in that program state.
#define SYS_REGISTEREMERGENCYTASK_2_DU16          (SYS_DU16 | 0x2B)

//--- sys_checkResetInfo() (API internal)
// Group: Hardware reset.
// At the moment only: Controller Watchdog Reset.
// <error parameter> = software reset id
#define SYS_CHECK_RESET_INFO_1_DU16               (SYS_DU16 | 0x2C)
// Group: Trap reset.
// <error parameter> = software reset id
#define SYS_CHECK_RESET_INFO_2_DU16               (SYS_DU16 | 0x2D)

//--- sys_getLibFunc()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_GETLIBFUNC_DU16                       (SYS_DU16 | 0x2E)

//--- sys_getActiveErrors()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_GETACTIVEERRORS_DU16                  (SYS_DU16 | 0x2F)

//--- sys_getResetInfo()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_GETRESETINFO_DU16                     (SYS_DU16 | 0x30)

//--- sys_getSavedErrors()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_GETSAVEDERRORS_DU16                   (SYS_DU16 | 0x31)

//--- sys_registerSetDefaultsFunction()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_REGISTERSETDEFAULTSFUNCTION_DU16      (SYS_DU16 | 0x32)

//--- sys_registerErrorCallback()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_REGISTERERRORCALLBACK_DU16            (SYS_DU16 | 0x33)

//--- extension to sys_registerTask()
// Registration of a task was made outside of sys_main() and cycle offset is not zero.
// That is only allowed for RTS!
// <error parameter> = parameter Priority_u8
#define SYS_REGISTERTASK_4_DU16                   (SYS_DU16 | 0x34)

// Invalid priority (BODAS-design)
#define SYS_REGISTERTASK_5_DU16                   (SYS_DU16 | 0x35)

//--- sys_suspendTasks_l()
// Calling of function is not allowed because RTS library is not implemented.
#define SYS_SUSPENDTASKS_1_DU16                   (SYS_DU16 | 0x36)
// Calling of function is not allowed because there are already suspended tasks.
#define SYS_SUSPENDTASKS_2_DU16                   (SYS_DU16 | 0x37)
// Invalid parameter. <error parameter> = number of parameter
#define SYS_SUSPENDTASKS_3_DU16                   (SYS_DU16 | 0x38)

//--- sys_resumeTasks_l()
// Calling of function is not allowed because RTS library is not implemented.
#define SYS_RESUMETASKS_1_DU16                    (SYS_DU16 | 0x39)

//--- sys_suspendIdleTasks_l()
// Calling of function is not allowed because RTS library is not implemented.
#define SYS_SUSPENDIDLETASKS_1_DU16               (SYS_DU16 | 0x3A)
// Calling of function is not allowed because there are already suspended idle tasks.
#define SYS_SUSPENDIDLETASKS_2_DU16               (SYS_DU16 | 0x3B)
// Invalid parameter. <error parameter> = number of parameter
#define SYS_SUSPENDIDLETASKS_3_DU16               (SYS_DU16 | 0x3C)

//--- sys_resumeIdleTasks_l()
// Calling of function is not allowed because RTS library is not implemented.
#define SYS_RESUMEIDLETASKS_1_DU16                (SYS_DU16 | 0x3D)

// task registration not allowed for stopped BODAS-design applications (STOP or BP)
#define SYS_REGISTERTASK_6_DU16                   (SYS_DU16 | 0x3E)

// task registration not allowed for stopped BODAS-design applications (STOP or BP)
#define SYS_REGISTERIDLETASK_4_DU16               (SYS_DU16 | 0x3F)

//---
// Invalid C-API library. It doesn't designed for the existing hardware (ECU).
#define SYS_CHECKAPILIBRARY_DU16                  (SYS_DU16 | 0x40)

//--- sys_getINH()
// No hardware support
#define SYS_GETINH_DU16                           (SYS_DU16 | 0x41)

//--- sys_checkCalib()
// Invalid calibration data
#define SYS_CHECKCALIB_DU16                       (SYS_DU16 | 0x42)

//--- sys_checkVP()
// short circuit dedection from main relay 1..3
#define SYS_CHECK_HR1_DU16                        (SYS_DU16 | 0x43)
#define SYS_CHECK_HR2_DU16                        (SYS_DU16 | 0x44)
#define SYS_CHECK_HR3_DU16                        (SYS_DU16 | 0x45)

/*--- sys_setError() */
/* Invalid parameter. <error parameter> = number of parameter */
#define SYS_SETERROR_DU16                         (SYS_DU16 | 0x46)

/*--- sys_deactivateWDAoutput_u16() */
/* Deactivate WDA output
 * Communication with CY320 (monitoring modul = external watchdog)
 * <error parameter> =
 * bit 0 : set response time: failed to pass SPI request (timeout Mm_SetRespTime)
 * bit 1 : get request: no valid data could received from CY320 (timeout Mm_GetRequest)
 * bit 2 : set response: failed to pass SPI request (timeout Mm_Transmit)
 * bit 4 : like bit 0 but for the second call of the function
 * bit 5 : like bit 1 but for the second call of the function*
 * bit 6 : like bit 2 but for the second call of the function
 */
#define SYS_DEACTIVATE_WDA_OUTPUT_DU16            (SYS_DU16 | 0x47)

//--- sys_setErrorExtTime()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_SETERROREXTTIME_DU16                  (SYS_DU16 | 0x48)

//--- sys_checkVP()
// short circuit dedection from main relay 4
#define SYS_CHECK_HR4_DU16                        (SYS_DU16 | 0x49)

//---
#define SYS_AFTERRUN_ENDLESS_LOOP_DU16            (SYS_DU16 | 0x4A)

//--- sys_permitAfterRun()
// Invalid parameter. <error parameter> = number of parameter
#define SYS_PERMIT_AFTERRUN_1_DU16                (SYS_DU16 | 0x4B)

/* sys_diagVSS_4() */
/* short circuit dedection from VSS_4 */
#define SYS_CHECK_VSS_4_DU16                      (SYS_DU16 | 0x4C)

/* sys_procDiagSUV() */
/* Startup voltage is switched OFF after Timout because at least one sensor supply voltages was
 * not available */
#define SYS_CHECK_SUV_DU16                        (SYS_DU16 | 0x4D)

//--- sys_setEcu()
// Feature is not supported by this ECU.
#define SYS_SETECU_1_DU16                         (SYS_DU16 | 0x4E)
// Invalid parameter. <error parameter> = number of parameter
#define SYS_SETECU_2_DU16                         (SYS_DU16 | 0x4F)

/*** Definition of the error locations/codes for the CAN module ***********************************/
//--- can_init()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_INIT_DU16                             (CAN_DU16 | 0x01)

//--- can_sendData()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_SENDDATA_1_DU16                       (CAN_DU16 | 0x02)
// Buffer overflow. <error parameter> = CAN channel
#define CAN_SENDDATA_2_DU16                       (CAN_DU16 | 0x03)

//--- can_registerTxBuf()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_REGISTERTXBUF_1_DU16                  (CAN_DU16 | 0x04)
// Calling the function is not allowed in that program state.
#define CAN_REGISTERTXBUF_2_DU16                  (CAN_DU16 | 0x05)

//--- can_registerRxCallback()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_REGISTERRXCALLBACK_1_DU16             (CAN_DU16 | 0x06)
// Calling the function is not allowed in that program state.
#define CAN_REGISTERRXCALLBACK_2_DU16             (CAN_DU16 | 0x07)

//--- can_registerBusOffCallback()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_REGISTERBUSOFFCALLBACK_1_DU16         (CAN_DU16 | 0x08)
// Calling the function is not allowed in that program state.
#define CAN_REGISTERBUSOFFCALLBACK_2_DU16         (CAN_DU16 | 0x09)

//--- can_registerRxDataboxes()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_REGISTERRXDATABOXES_1_DU16            (CAN_DU16 | 0x0A)
// Calling the function is not allowed in that program state.
#define CAN_REGISTERRXDATABOXES_2_DU16            (CAN_DU16 | 0x0B)

//--- can_registerRxBuf()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_REGISTERRXBUF_1_DU16                  (CAN_DU16 | 0x0C)
// Calling the function is not allowed in that program state.
#define CAN_REGISTERRXBUF_2_DU16                  (CAN_DU16 | 0x0D)

//--- can_initRxDatabox()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_INITRXDATABOX_DU16                    (CAN_DU16 | 0x0E)

//--- can_getData()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_GETDATA_1_DU16                        (CAN_DU16 | 0x0F)
// Receive buffer length is zero.
#define CAN_GETDATA_2_DU16                        (CAN_DU16 | 0x10)

//--- can_getDatabox()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_GETDATABOX_1_DU16                     (CAN_DU16 | 0x11)
// Databox is not initialised. <error parameter> = number of databox
#define CAN_GETDATABOX_2_DU16                     (CAN_DU16 | 0x12)

//--- can_initTxDatabox()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_INITTXDATABOX_DU16                    (CAN_DU16 | 0x13)

//--- can_isDataboxFree()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_ISDATABOXFREE_1_DU16                  (CAN_DU16 | 0x14)
// Databox is not initialised. <error parameter> = number of databox
#define CAN_ISDATABOXFREE_2_DU16                  (CAN_DU16 | 0x15)

//--- can_sendDatabox()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_SENDDATABOX_1_DU16                    (CAN_DU16 | 0x16)
// Data box is not initialised. <error parameter> = number of data box
#define CAN_SENDDATABOX_2_DU16                    (CAN_DU16 | 0x17)

//--- can_registerTxDataboxes()
// Invalid parameter. <error parameter> = number of parameter
// and additionaly 0x23 = Configuration is not allowed in that program state
#define CAN_REGISTERTXDATABOXES_DU16              (CAN_DU16 | 0x18)

//--- can_isTxEmpty()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_ISTXEMPTY_DU16                        (CAN_DU16 | 0x19)

//--- can_registerTxBuf()
// Too less buffer registered for diagnosis (BODAS-design)
#define CAN_REGISTERTXBUF_3_DU16                  (CAN_DU16 | 0x1A)

//--- can_registerRxBuf()
// Too less buffer registered for diagnosis (BODAS-design)
#define CAN_REGISTERRXBUF_3_DU16                  (CAN_DU16 | 0x1B)

//--- can_registerRxDataboxes()
// Too less databoxes registered for diagnosis (BODAS-design)
#define CAN_REGISTERRXDATABOXES_3_DU16            (CAN_DU16 | 0x1C)

//--- can_registerTxDataboxes()
// Too less databoxes registered for diagnosis (BODAS-design)
#define CAN_REGISTERTXDATABOXES_3_DU16            (CAN_DU16 | 0x1D)

//--- extension to can_registerRxDataboxes()
// Number of Rx data boxes registered already is greater than the new number.
// This error is only possible if RTS library is implemented.
#define CAN_REGISTERRXDATABOXES_4_DU16            (CAN_DU16 | 0x1E)

//--- extension to can_registerTxDataboxes()
// Number of Tx data boxes registered already is greater than the new number.
// This error is only possible if RTS library is implemented.
#define CAN_REGISTERTXDATABOXES_4_DU16            (CAN_DU16 | 0x1F)

//--- can_getStatus()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_GETSTATUS_DU16                        (CAN_DU16 | 0x20)

/*--- can_getTxBufStatus() */
/* Invalid parameter. <error parameter> = number of parameter */
#define CAN_GETTXBUFSTATUS_DU16                   (CAN_DU16 | 0x21)

/*--- can_resetTxBuf() */
/* Invalid parameter. <error parameter> = number of parameter */
#define CAN_RESETTXBUF_DU16                       (CAN_DU16 | 0x22)

/*--- can_stop() */
/* Invalid parameter. <error parameter> = number of parameter */
#define CAN_STOP_DU16                             (CAN_DU16 | 0x23)

/*--- can_start() */
/* Invalid parameter. <error parameter> = number of parameter */
#define CAN_START_DU16                            (CAN_DU16 | 0x24)

//--- can_registerRxBuf()
// New buffer overlaps with a buffer registered already.
// <error parameter>
// 0 : Buffers have not the same start adress.
// 1 : Buffers have the same start address (speculation: application has used the same var. twice).
#define CAN_REGISTERRXBUF_4_DU16                  (CAN_DU16 | 0x25)

//--- can_registerTxBuf()
// New buffer overlaps with a buffer registered already.
// <error parameter>
// 0 : Buffers have not the same start adress.
// 1 : Buffers have the same start address (speculation: application has used the same var. twice).
#define CAN_REGISTERTXBUF_4_DU16                  (CAN_DU16 | 0x26)

//--- can_registerTxDataboxes()
// New buffer overlaps with a buffer registered already.
// <error parameter>
// 0 : Buffers have not the same start adress.
// 1 : Buffers have the same start address (speculation: application has used the same var. twice).
#define CAN_REGISTERTXDATABOXES_5_DU16            (CAN_DU16 | 0x27)

//--- can_registerRxDataboxes()
// New buffer overlaps with a buffer registered already.
// <error parameter>
// 0 : Buffers have not the same start adress.
// 1 : Buffers have the same start address (speculation: application has used the same var. twice).
#define CAN_REGISTERRXDATABOXES_5_DU16            (CAN_DU16 | 0x28)

//--- can_initRxDatabox()
// New buffer overlaps with a buffer registered already.
// <error parameter>
// 0 : Buffers have not the same start adress.
// 1 : Buffers have the same start address (speculation: application has used the same var. twice).
#define CAN_INITRXDATABOX_2_DU16                  (CAN_DU16 | 0x29)

//--- can_setRxFilter()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_SETRXFILTER_DU16                      (CAN_DU16 | 0x2A)

//--- can_setTxCycle()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_SETTXCYCLE_DU16                       (CAN_DU16 | 0x2B)

//--- can_cfgHwBoxes()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_CFGHWBOXES_1_DU16                     (CAN_DU16 | 0x2C)
// Wrong total nbr of data boxes. Sum of all parameters is invalid.
#define CAN_CFGHWBOXES_2_DU16                     (CAN_DU16 | 0x2D)
// Function must be executed before can_init().
#define CAN_CFGHWBOXES_3_DU16                     (CAN_DU16 | 0x2E)

//--- can_initRxHwDatabox()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_INITRXHWDATABOX_DU16                  (CAN_DU16 | 0x2F)

//--- can_getErrCounter()
// Invalid parameter. <error parameter> = number of parameter
#define CAN_GETERRCOUNTER_DU16                    (CAN_DU16 | 0x30)

/*--- can_getRxBufStatus() */
/* Invalid parameter. <error parameter> = number of parameter */
#define CAN_GETRXBUFSTATUS_DU16                   (CAN_DU16 | 0x31)

/*** Definition of the error locations/codes for the IN module ************************************/
//--- in()
// Invalid parameter. <error parameter> = number of parameter
#define IN_FUNC_DU16                              (IN_DU16 | 0x01)

//--- inxt()
// Invalid parameter. <error parameter> = number of parameter
#define IN_FUNC_XT_DU16                           (IN_DU16 | 0x02)

//--- in_cfgVoltageInput()
// Invalid parameter. <error parameter> = number of parameter
#define IN_CFG_VOLTAGE_INPUT_DU16                 (IN_DU16 | 0x03)

//--- in_getPhase()
// Invalid parameter. <error parameter> = number of parameter
#define IN_GETPHASE_DU16                          (IN_DU16 | 0x04)

//--- in_setPullup()
// Invalid parameter. <error parameter> = number of parameter
#define IN_SET_PULLUP_1_DU16                      (IN_DU16 | 0x05)
// Hardware doesn't support configuration.
#define IN_SET_PULLUP_2_DU16                      (IN_DU16 | 0x06)

//--- in_setCurrentMeasurement()
// Invalid parameter. <error parameter> = number of parameter
#define IN_SET_CURRENT_MEASUREMENT_1_DU16         (IN_DU16 | 0x07)
// Hardware doesn't support configuration.
#define IN_SET_CURRENT_MEASUREMENT_2_DU16         (IN_DU16 | 0x08)

//--- in_setDSM()
// Invalid parameter. <error parameter> = number of parameter
#define IN_SET_DSM_1_DU16                         (IN_DU16 | 0x09)
// Hardware doesn't support configuration.
#define IN_SET_DSM_2_DU16                         (IN_DU16 | 0x0A)

//--- in_cfgTempSensorType()
// Invalid parameter. <error parameter> = number of parameter
#define IN_CFG_TEMP_SENSOR_TYPE_DU16              (IN_DU16 | 0x0B)

//--- in_procDiagFI_ACTIV_DSM()
// shunt protection activated
#define IN_DIAG_DSM_PROTECTION_DU16               (IN_DU16 | 0x0C)

//--- in_getState()
// Invalid parameter. <error parameter> = number of parameter
#define IN_GET_STATE_DU16                         (IN_DU16 | 0x0D)

//--- in_cfgCurrentInput()
// Invalid parameter. <error parameter> = number of parameter
#define IN_CFG_CURRENT_INPUT_DU16                 (IN_DU16 | 0x0E)

//--- in_setPeriod()
// Invalid parameter. <error parameter> = number of parameter
#define IN_SET_PERIOD_DU16                        (IN_DU16 | 0x0F)

//--- in_enablePhase()
// Invalid parameter. <error parameter> = number of parameter
#define IN_ENABLE_PHASE_DU16                      (IN_DU16 | 0x10)

//--- in_resetPhase()
// Invalid parameter. <error parameter> = number of parameter
#define IN_RESET_PHASE_DU16                       (IN_DU16 | 0x11)

//--- in_cfgDigitalInput()
// Invalid parameter. <error parameter> = number of parameter
#define IN_CFG_DIGITAL_INPUT_DU16                 (IN_DU16 | 0x12)

//--- in_enablePhase()
// At least one of the frequency inputs is used for freqency measurement
#define IN_ENABLE_PHASE_1_DU16                    (IN_DU16 | 0x13)

//--- in_resetPhase()
// Phase measurement is not enabled
#define IN_RESET_PHASE_1_DU16                     (IN_DU16 | 0x14)

//--- in_registerFreqAcqBuf()
// Invalid parameter. <error parameter> = number of parameter
#define IN_REGISTER_FREQACQBUF_1_DU16             (IN_DU16 | 0x15)
// New buffer overlaps with a buffer registered already.
// <error parameter> =
// 0 : Buffers have not the same start adress.
// 1 : Buffers have the same start address (speculation: application has used the same var. twice).
#define IN_REGISTER_FREQACQBUF_2_DU16             (IN_DU16 | 0x16)
// Phase measurment is enabled
#define IN_REGISTER_FREQACQBUF_3_DU16             (IN_DU16 | 0x17)

//--- in_registerFreqAcqCopyBuf()
// Invalid parameter. <error parameter> = number of parameter
#define IN_REGISTER_FREQACQCOPYBUF_1_DU16         (IN_DU16 | 0x18)
// New buffer overlaps with a buffer registered already.
// <error parameter> =
// 0 : Buffers have not the same start adress.
// 1 : Buffers have the same start address (speculation: application has used the same var. twice).
#define IN_REGISTER_FREQACQCOPYBUF_2_DU16         (IN_DU16 | 0x19)

//--- in_getFreqAcq()
// Invalid parameter. <error parameter> = number of parameter
#define IN_GET_FREQACQ_1_DU16                     (IN_DU16 | 0x1A)
// Copy buffer is not registered
#define IN_GET_FREQACQ_2_DU16                     (IN_DU16 | 0x1B)
// Copy buffer is to small
#define IN_GET_FREQACQ_3_DU16                     (IN_DU16 | 0x1C)
// Buffer is not registered
#define IN_GET_FREQACQ_4_DU16                     (IN_DU16 | 0x1D)

/*** Definition of the error locations/codes for the OUT module. **********************************/
//--- out()
// Invalid parameter. <error parameter> = number of parameter
#define OUT_FUNC_DU16                             (OUT_DU16 | 0x01)

//--- out_cfg()
// Invalid parameter. <error parameter> = number of parameter
#define OUT_CFG_DU16                              (OUT_DU16 | 0x02)

//--- out_cfgDither()
// Invalid parameter. <error parameter> = number of parameter
#define OUT_CFG_DITHER_1_DU16                     (OUT_DU16 | 0x03)
// Invalid period for dither function.
#define OUT_CFG_DITHER_2_DU16                     (OUT_DU16 | 0x04)

//--- out_getStatus()
// Invalid parameter. <error parameter> = number of parameter
#define OUT_GETSTATUS_DU16                        (OUT_DU16 | 0x05)

//--- out_getStatusxt()
// Invalid parameter. <error parameter> = number of parameter
#define OUT_GETSTATUSXT_DU16                      (OUT_DU16 | 0x06)

//--- out_cfgPI()
// Invalid parameter. <error parameter> = number of parameter
#define OUT_CFGPI_DU16                            (OUT_DU16 | 0x07)

//--- out_resetError()
// Invalid parameter. <error parameter> = number of parameter
#define OUT_RESET_ERROR_DU16                      (OUT_DU16 | 0x08)

//--- out_cfgSlope()
// Invalid parameter. <error parameter> = number of parameter
#define OUT_CFGSLOPE_DU16                         (OUT_DU16 | 0x09)

//--- out_cfgSafety()
// Invalid parameter. <error parameter> = number of parameter
#define OUT_CFGSAFETY_DU16                        (OUT_DU16 | 0x0A)

//--- out_cfgPulse()
// Invalid parameter. <error parameter> = number of parameter
#define OUT_CFGPULSE_DU16                         (OUT_DU16 | 0x0B)

//--- out_cfgSlopext()
// Invalid parameter. <error parameter> = number of parameter
#define OUT_CFGSLOPEXT_DU16                       (OUT_DU16 | 0x0C)

//--- out_setPullup()
// Invalid parameter. <error parameter> = number of parameter
#define OUT_SETPULLUP_1_DU16                      (OUT_DU16 | 0x0D)
// Hardware doesn't support configuration.
#define OUT_SETPULLUP_2_DU16                      (OUT_DU16 | 0x0E)


/*** Definition of the error codes for the EMERGENCY module. **************************************/

//! parameter <nbr> within function call emcy_cfg() out of range
#define EMCY_ERR_EMCYCFG_PARA_DU16                (EMCY_DU16 | 0x0001)
//! parameter <nbr> within function call emcy_disableInput() invalid
#define EMCY_ERR_EMCYDISABLE_PARA_DU16            (EMCY_DU16 | 0x0003)
//! emcy_setPowerOn() was called although the emergency input is still active
#define EMCY_ERR_SETON_NOT_ALLOWED_DU16           (EMCY_DU16 | 0x0005)

//! wrong input level detected at EMERGENCY input
#define EMCY_ERR_INPUT_FAILURE_DU16               (EMCY_DU16 | 0x0011)
//! wrong input level detected at INHIBIT pin
#define EMCY_ERR_INHIBIT_FAILURE_DU16             (EMCY_DU16 | 0x0012)
//! failure detected at output of main switch <VP_x>
#define EMCY_ERR_MAINSWITCH_FAILURE_DU16          (EMCY_DU16 | 0x0013)
//! failure detected during sys_setVP <VP_x>
#define EMCY_ERR_SETVP_FAILURE_DU16               (EMCY_DU16 | 0x0014)
//! Vss voltage is switched off, but is required for emcy input
#define EMCY_ERR_VSS_OFF_FAILURE_DU16             (EMCY_DU16 | 0x0015)
//! failure within cpu HW path (EMCY stop in CPU) of emcy input
#define EMCY_ERR_CPU_PATH_FAILURE_DU16            (EMCY_DU16 | 0x0016)
//! failure detected within HW path at output of main switch <VP_x>
#define EMCY_ERR_HW_PATH_FAILURE_DU16             (EMCY_DU16 | 0x0017)

//! warning to inform about deactivation of emcy input
#define EMCY_WARN_EMCY_DISABLED_DU16              (EMCY_DU16 | 0x0080)


/*** Definition of the error locations/codes for module of monitoring functions (MOF) *************/

//--- VSS_1 (sensor supply 1) out of range
// <error parameter> 0 = too low, 1 = too high, 2 = too high in off state
#define MOF_VSS_1_DU16                            (MOF_DU16 | 0x01)
//--- VSS_2 (sensor supply 2) out of range
// <error parameter> 0 = too low, 1 = too high, 2 = too high in off state
#define MOF_VSS_2_DU16                            (MOF_DU16 | 0x02)
//--- VSS_3 (sensor supply 3) out of range
// <error parameter> 0 = too low, 1 = too high, 2 = too high in off state
#define MOF_VSS_3_DU16                            (MOF_DU16 | 0x03)

//--- VREF (ECU internal reference voltage) is too high
// <error parameter>:
// 0 = warning (voltage greater than warning limit but lower than error limit)
#define MOF_VREF_DU16                             (MOF_DU16 | 0x04)

//--- V12V (ECU internal voltage 12 V) out of range
// <error parameter>:
// 0 = too low
// 1 = too high (but lower than error limit for pre-existing defect)
#define MOF_V12V_DU16                             (MOF_DU16 | 0x05)

//--- monitoring module check at startup
// It is checked at startup.
// Power supply voltage is disabled!
// <error parameter> = error code
// bit position : meaning
// 0 : VP_1 can not be switched on
// 1 : VP_2 can not be switched on
// 2 : timeout request to monitoring module
// 3 : data read from monitoring module are invalid (that means status of read = invalid data)
//     -> so error counter could not be checked
// 4 : error counter of monitoring module is too low (must be > 4)
// 5 : VP_1 was not switched off by WDA output of monitoring module
// 6 : VP_2 was not switched off by WDA output of monitoring module
// 7 : Error setting of response time during mm check
#define MOF_MM_STARTUP_DU16                       (MOF_DU16 | 0x06)

//--- setting of response time in monitoring module was faulty
// It is checked at startup.
// Power supply voltage is disabled!
// <error parameter> = 0
#define MOF_MM_SET_RESP_TIME_DU16                 (MOF_DU16 | 0x07)

//--- Cut off power supply by sys_setVP() works faulty
// It is checked at startup.
// Power supply voltage is disabled!
// <error parameter> = error code
// bit position : meaning
// 0 : VP_1 can not be switched on
// 1 : VP_2 can not be switched on
// 2 : VP_1 is not switched off by sys_setVP()
// 3 : VP_2 is not switched off by sys_setVP()
#define MOF_VP_CUTOFF_SYSSETVP_DU16               (MOF_DU16 | 0x08)

//--- Cut off power supply by 3V3 overvoltage detection works faulty
// (3V3 = ECU internal voltage 3,3V)
// It is checked at startup.
// Power supply voltage is disabled!
// <error parameter> = error code
// bit position : meaning
// 0 : VP_1 can not be switched on at the beginning of test
// 1 : VP_2 can not be switched on at the beginning of test
// 2 : VP_1 is not switched off by test after test was enabled
// 3 : VP_2 is not switched off by test after test was enabled
// 4 : VP_1 is not switched off by test after test was disabled
// 5 : VP_2 is not switched off by test after test was disabled
// 6 : Error during test of overvoltage detection
// 7 : Error during test of undervoltage detection
// Note: If there are errors during test of both overvoltage and undervoltage detection
//       (bit 6 and 7 are set) than bit 0 - 5 are related to test of overvoltage detection.
#define MOF_VP_CUTOFF_3V3_DU16                    (MOF_DU16 | 0x09)

//--- Cut off power supply by 1V5 overvoltage detection works faulty
// (1V5 = ECU internal voltage 1,5V)
// It is checked at startup.
// Power supply voltage is disabled!
// <error parameter> = error code
// bit position : meaning
// 0 : VP_1 can not be switched on at the beginning of test
// 1 : VP_2 can not be switched on at the beginning of test
// 2 : VP_1 is not switched off by test after test was enabled
// 3 : VP_2 is not switched off by test after test was enabled
// 4 : VP_1 is not switched off by test after test was disabled
// 5 : VP_2 is not switched off by test after test was disabled
// 6 : Error during test of overvoltage detection
// 7 : Error during test of undervoltage detection
// Note: If there are errors during test of both overvoltage and undervoltage detection
//       (bit 6 and 7 are set) than bit 0 - 5 are related to test of overvoltage detection.
#define MOF_VP_CUTOFF_1V5_DU16                    (MOF_DU16 | 0x0A)

//--- Limit of operating hours is achieved
#define MOF_OP_HOURS_LIMIT_DU16                   (MOF_DU16 | 0x0B)

//--- pre-existing error of VREF (ECU internal reference voltage)
// It is checked at startup.
// Power supply voltage is disabled!
#define MOF_VREF_PRE_EXIST_DU16                   (MOF_DU16 | 0x0C)

//--- pre-existing error of V12V (ECU internal voltage 12V)
// It is checked at startup.
// Power supply voltage is disabled!
#define MOF_V12V_PRE_EXIST_DU16                   (MOF_DU16 | 0x0D)

//--- error on EEPROM page 0 (system) which can not be repaired.
#define MOF_EEPPAGE_SYSTEM_DU16                   (MOF_DU16 | 0x0E)

//--- error on EEPROM page 15 (API) which can not be repaired.
#define MOF_EEPPAGE_API_DU16                      (MOF_DU16 | 0x0F)

//--- error on EEPROM page of application which can not be repaired.
#define MOF_EEPPAGE_APPLICATION_DU16              (MOF_DU16 | 0x10)

//--- V3V3_ext (3,3V for external use: pullup of inputs) out of range
// <error parameter> 0 = too low, 1 = too high
#define MOF_V3V3_EXT_DU16                         (MOF_DU16 | 0x11)

//--- ECU internal temperature sensors
// warning hardware temperature is too high: temperature greater than warning limit
// <error parameter>: 0
#define MOF_TEMPHW_WARNING_DU16                   (MOF_DU16 | 0x12)

//--- ECU internal temperature sensors
// error hardware temperature is too high: temperature greater than error limit
// <error parameter>: 0
#define MOF_TEMPHW_ERROR_DU16                     (MOF_DU16 | 0x13)

//--- error on EEPROM page 15 (API) which can not be repaired AND
//    comparation of only range for saving pre-existing errors is faulty (at least one byte is
//    different in original and shadow page!)
// <error parameter>: 0
#define MOF_EEP_PRE_EXIST_DEFECTS_DU16            (MOF_DU16 | 0x14)

//--- error on EEPROM page for saving errors which can not be repaired.
// <error parameter>: 0
#define MOF_EEPPAGE_ERRORS_DU16                   (MOF_DU16 | 0x15)

//--- switch-off path test of CPLD failed
// It is checked at startup.
// <error parameter> = error code
// bit position : meaning
// 0 : VP_1 can not be switched on
// 1 : VP_2 can not be switched on
// 2 : VP_1 is not switched off via CPLD()
// 3 : VP_2 is not switched off via CPLD()
#define MOF_VP_CUTOFF_CPLD_DU16                   (MOF_DU16 | 0x16)

//--- stack overflow
// <error parameter>: 0
#define MOF_STACK_OVERFLOW_DU16                   (MOF_DU16 | 0x17)

//--- External RAM error detected
// <error parameter>: 0
#define MOF_EXT_RAM_HW_DU16                       (MOF_DU16 | 0x18)

//--- 3V3-/1V5- over-/under-voltage detected
// <error parameter>: 0
#define MOF_3V3_1V5_HW_DU16                       (MOF_DU16 | 0x19)

//--- VSS_4 (sensor supply 4) out of range
// <error parameter> 0 = too low, 1 = too high, 2 = too high in off state
#define MOF_VSS_4_DU16                            (MOF_DU16 | 0x1A)

/* number of _USED_ errors codes related to MoF unit */
#define MOF_ERROR_NUM_D                           (MOF_VSS_4_DU16 & 0xFFu)


/*** Definition of error locations/codes for module of controller monitoring functions (MOC) ****/

#define MOC_ROM_SINGLEBITERR_DU16                 (MOC_DU16 | 0x01)
#define MOC_ROM_DOUBLEBITERR_DU16                 (MOC_DU16 | 0x02)
#define MOC_WDA_THRESHOLD_VIOLATION_DU16          (MOC_DU16 | 0x03)
#define MOC_RAM_CONTENT_ERROR_DU16                (MOC_DU16 | 0x04)
#define MOC_RAM_NOT_WRITABLE_DU16                 (MOC_DU16 | 0x05)
#define MOC_GNRL_UNDEFINED_STATE_DU16             (MOC_DU16 | 0x06)
#define MOC_COM_SPI_MALFUNCTION_DU16              (MOC_DU16 | 0x07)
#define MOC_PCP_CHECKSUMERR_DU16                  (MOC_DU16 | 0x08)
#define MOC_GPTA_TIMERERR_DU16                    (MOC_DU16 | 0x09)
#define MOC_RAM_EXTRAM_STUCK_DU16                 (MOC_DU16 | 0x0A)

/* number of _USED_ errors codes related to MoC unit */
#define MOC_ERROR_NUM_D                           (MOC_RAM_EXTRAM_STUCK_DU16 & 0xFFu)

/* total number of _USED_ errors codes related to whole Mo unit (MoC and MoF) */
#define MO_ERROR_NUM_D                            (MOF_ERROR_NUM_D + MOC_ERROR_NUM_D)


/*** Definition of the error locations/codes for the SAFOUT module. **********************************/
//--- safout()
// Invalid parameter. <error parameter> = number of parameter
#define SAFOUT_FUNC_DU16                          (SAFOUT_DU16 | 0x01)

//--- safout_cfg()
// Invalid parameter. <error parameter> = number of parameter
#define SAFOUT_CFG_DU16                           (SAFOUT_DU16 | 0x02)

//--- safout_getState()
// Invalid parameter. <error parameter> = number of parameter
#define SAFOUT_GETSTATE_DU16                      (SAFOUT_DU16 | 0x03)

//--- safout_getStatext()
// Invalid parameter. <error parameter> = number of parameter
#define SAFOUT_GETSTATEXT_DU16                    (SAFOUT_DU16 | 0x04)

//--- safout_resetError()
// Invalid parameter. <error parameter> = number of parameter
#define SAFOUT_RESET_ERROR_DU16                   (SAFOUT_DU16 | 0x05)

//--- safout_ignoreError()
// Invalid parameter. <error parameter> = number of parameter
#define SAFOUT_IGNORE_ERROR_DU16                  (SAFOUT_DU16 | 0x06)


/*** Definition of the error locations/codes for MO module - general ******************************/
//--- mo_cfgCheck()
// Invalid parameter. <error parameter> = number of parameter
#define MO_CFG_CHECK_DU16                         (MO_DU16 | 0x01)

//--------------------------------------------------------------------------------------------------
// Definition of the error numbers (parameter values) used by the error handler. */
//---> Common for all modules
#define ERR_NOFAILURE_DU16                          (0x0000)
#define ERR_PARAMETER1_DU16                         (0x0001)
#define ERR_PARAMETER2_DU16                         (0x0002)
#define ERR_PARAMETER3_DU16                         (0x0003)
#define ERR_PARAMETER4_DU16                         (0x0004)
#define ERR_PARAMETER5_DU16                         (0x0005)
#define ERR_PARAMETER6_DU16                         (0x0006)
#define ERR_PARAMETER7_DU16                         (0x0007)
#define ERR_PARAMETER8_DU16                         (0x0008)

#define ERR_INVALID_CHNL_NB_DU16                    (0x000A)

#define ERR_NOAFTERRUN_DU16                         (0x0010)
#define ERR_NOAFTERRUNSTATE_DU16                    (0x0011)
#define ERR_NOKL15STATE_DU16                        (0x0012)
#define ERR_PERIOD_FOR_DITHER_DU16                  (0x0013)
#define ERR_UNVALID_FUNCTION_CALL_DU16              (0x0014)

#define ERR_SWIDENTIFY_DU16                         (0x0020)
#define ERR_HWIDENTIFY_DU16                         (0x0021)
#define ERR_SETRESPTIME_DU16                        (0x0022)
#define ERR_CFG_NOT_ALLOWED_DU16                    (0x0023)
//<--- Common for all modules

//---------------
//---> Module sys
// SYS_GETTASKLOAD_DU16
#define ERRSYS_GETTASKLOAD_OVFLPART_DU16            (0x0040)
#define ERRSYS_GETTASKLOAD_OVFLSUM_DU16             (0x0041)
//<--- Module sys
//---------------

//--------------------------------------------------------------------------------------------------

//--- (application) task priority numbers
#define TASK_PRIO_CAT1_MIN_DU8    0  // priority category 1 min. priority
#define TASK_PRIO_CAT1_MAX_DU8   63  // priority category 1 max. priority
#define TASK_PRIO_CAT2_MIN_DU8   64  // priority category 2 min. priority
#define TASK_PRIO_CAT2_MAX_DU8  127  // priority category 2 max. priority
#define TASK_PRIO_CAT3_MIN_DU8  128  // priority category 3 min. priority
#define TASK_PRIO_CAT3_MAX_DU8  191  // priority category 3 max. priority
#define TASK_PRIO_CAT4_MIN_DU8  192  // priority category 4 min. priority
#define TASK_PRIO_CAT4_MAX_DU8  255  // priority category 4 max. priority


//--- Time Modes for functions sys_getTaskRunTime and sys_getIdleTaskRunTime
/* inclusive task interrupts */
#define PTIME_MIN_INCL         1 /* min. time */
#define PTIME_MAX_INCL         2 /* max. time */
#define PTIME_AVERAGE_INCL     3 /* average time */
#define PTIME_LAST_INCL        4 /* time of last cycle */
#define PTIME_OVFLCOUNT_INCL   5 /* number of cycle time overflows */
/* exclusive task interrupts */
#define PTIME_MIN_EXCL         6 /* min. time */
#define PTIME_MAX_EXCL         7 /* max. time */
#define PTIME_AVERAGE_EXCL     8 /* average time */
#define PTIME_LAST_EXCL        9 /* time of last cycle */
#define PTIME_OVFLCOUNT_EXCL  10 /* number of cycle time overflows */

//--- Configuration values for sensor supplies voltages (VSS)
#define CFG_VSS_3V3_DU8   1u
#define CFG_VSS_5V_DU8    2u
#define CFG_VSS_10V_DU8   3u


#endif  /* _NUMBERS_H_D */


/* EOF ########################################################################################## */
