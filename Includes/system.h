/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        system.h
*
*  \brief       Interface for system.c.
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   API RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 5900 $
*                            $Date: 2013-06-03 13:07:32 +0200 (Mo, 03 Jun 2013) $
*                            $Author: gtg2si $
*
* REVISION HISTORY:
*
***************************************************************************************************/

#ifndef _SYSTEM_H_D      /* replace it with the filename in capital letters */
#define _SYSTEM_H_D      /* replace it with the filename in capital letters */

/**** include files *******************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

#include "common_api.h"
#include "types.h"
#include "intr_defs.h"
#include "cpu_inl_api.h"

/* Include is necessary - the SCOPE declaration from the prototypes depends on CHECK_VSS_4_D */
#include "channels.h"

#ifdef _SYSTEM_D     /* replace it with the filename in capital letters */
  #define SCOPE_D
#else
  #define SCOPE_D extern
#endif   /* _SYSTEM_D */

/**** defines **************************************************************************************
* List of defines needed in this header file and defines to be made available to other modules.   */

//--- Error codes ---
// Return values of function sys_init2 (error codes)
#define SYSINIT_OK_DS16                   0x0000
#define SYSINIT_CYCLE_TIME_TO_LOW_DS16    0x0001
#define SYSINIT_CYCLE_TIME_TO_HIGH_DS16   0x0002
#define SYSINIT_EE_LOADING_ERROR_DS16     0x0008
#define SYSINIT_EE_INVALID_VERSION_DS16   0x0010
#define SYSINIT_EE_NOT_INITIALIZED_DS16   0x0020
#define SYSINIT_INVALID_HARDWARE_DS16     0x0040
#define SYSINIT_NEW_SOFTWARE_DS16         0x0080
#define SYSINIT_INVALID_SOFTWARE_DS16     0x0100
#define SYSINIT_CFG_NOT_ALLOWED_DS16      0x0200
//Invalid C-API library. It doesn't designed for the existing ECU.
#define SYSINIT_INVALID_API_DS16          0x0400

// Return values of function sys_registerTask (error codes)
#define SYSREGTASK_OK_DU16                0x0000
#define SYSREGTASK_INVALID_ADDR_DU16      0x0001
#define SYSREGTASK_CFG_NOT_ALLOWED_DU16   0x0002
#define SYSREGTASK_MAX_NUM_DU16           0x0003
#define SYSREGTASK_CYCLE_TIME_DU16        0x0004
#define SYSREGTASK_CYCLE_OFFSET_DU16      0x0005
#define SYSREGTASK_PRIORITY_DU16          0x0006
#define SYSREGTASK_REQ_OFFSET_0_DU16      0x0007

// Return values of function sys_registerIdletask (error codes)
#define SYSREGIDLETASK_OK_DU16                0x0000
#define SYSREGIDLETASK_INVALID_ADDR_DU16      0x0001
#define SYSREGIDLETASK_CFG_NOT_ALLOWED_DU16   0x0002
#define SYSREGIDLETASK_MAX_NUM_DU16           0x0003

// Return values of function sys_registerIdletask (error codes)
#define SYSREGAFTERRUN_OK_DU16                0x0000
#define SYSREGAFTERRUN_CFG_NOT_ALLOWED_DU16   0x0001
#define SYSREGAFTERRUN_INVALID_ADDR_DU16      0x0002
#define SYSREGAFTERRUN_MAX_NUM_DU16           0x0003

// Return values of function sys_setVP (error codes)
//ok
#define SYSSETVP_OK_DU16                0x0000
// invalid channel
#define SYSSETVP_INVALID_CHNL_DU16      0x0001
// hardware doesn't support switch on/off
#define SYSSETVP_NO_HW_SUPPORT_DU16     0x0002
// setting VP ON is locked (because of hardware monitor error)
#define SYSSETVP_ON_LOCKED_DU16         0x0004
// SOP test is running
#define SYSSETVP_SOP_TEST_RUNNING_DU16  0x0100
// INH/OE active
#define SYSSETVP_INH_ACTIVE_DU16        0x1000
// no UBATT
#define SYSSETVP_NOUBATT_DU16           0x2000
// no VP
#define SYSSETVP_NOVP_DU16              0x4000
// unexpected state of VP before switch-off test
#define SYSSETVP_UNEXPECTED_VP_DU16     0x8000

// Return values of function sys_setVSS (error codes)
//ok
#define SYSSETVSS_OK_DU16                0x0000
// invalid channel
#define SYSSETVSS_INVALID_CHNL_DU16      0x0001
// hardware doesn't support switch on/off
#define SYSSETVSS_NO_HW_SUPPORT_DU16     0x0002

// Return values of function sys_cfgVSS (error codes)
//ok
#define SYSCFGVSS_OK_DU16                0x0000
// invalid channel
#define SYSCFGVSS_INVALID_CHNL_DU16      0x0001
// invalid voltage
#define SYSCFGVSS_INVALID_VOLTAGE_DU16   0x0002
// Hardware doesn't support configuration.
#define SYSCFGVSS_NO_HW_SUPPORT_DU16     0x0003

// Return values of function sys_cfgVSS (error codes)
//ok
#define SYSGETVERSION_OK_DU16                    0x0000
// Buffer length is undersized.
#define SYSGETVERSION_BUFLEN_UNDERSIZE_DU16      0x0001
// Invalid software part.
#define SYSGETVERSION_SW_PART_INVALID_DU16       0x0002
// Software part is not implemented.
#define SYSGETVERSION_SW_PART_NO_IMPLEMENT_DU16  0x0003
// Invalid pointer for buffer.
#define SYSGETVERSION_BUF_INVALID_DU16           0x0004
// Invalid pointer for copied bytes.
#define SYSGETVERSION_COPIEDBYTES_INVALID_DU16   0x0005


// Possible Value of parameter SW_part_u16 of function sys_getVersion().
// application
#define VERSION_SW_PART_APPL_DU8               0x00
// startup block
#define VERSION_SW_PART_SB_DU8                 0x01
// customer block
#define VERSION_SW_PART_CB_DU8                 0x02
// All used API libraries
#define VERSION_SW_PART_API_ALL_DU8            0x03
// API library (platform) basic
#define VERSION_SW_PART_API_BASIC_DU8          0x04
// API SRC/RC specific library basic
#define VERSION_SW_PART_API_SRC_RC_BASIC_DU8   0x05
// API library EEPROM (data)
#define VERSION_SW_PART_API_EEPROM_DU8         0x06
// API library diagnostics
#define VERSION_SW_PART_API_DIAG_DU8           0x07
// API library INPUT EXTENSION
#define VERSION_SW_PART_API_INEXT_DU8          0x08
// API library servo motor (STM = Stellmotor)
#define VERSION_SW_PART_API_STM_DU8            0x09
// API library CANopen
#define VERSION_SW_PART_API_CANOPEN_DU8        0x0A
// API library J1939 protocol
#define VERSION_SW_PART_API_J1939_DU8          0x0B
// API library run time system (RTS)
#define VERSION_SW_PART_API_RTS_DU8            0x0C
// API library CANopen_RCE
#define VERSION_SW_PART_API_CANOPEN_RCE_DU8    0x0D
// API library UDS protocol
#define VERSION_SW_PART_API_UDS_DU8            0x0E
// API library OUTPUT EXTENSION
#define VERSION_SW_PART_API_OUTEXT_DU8         0x0F
// API library ACOM (asynchronous communication via UART)
#define VERSION_SW_PART_API_ACOM_DU8           0x10
// API library RTM (real time measurement)
#define VERSION_SW_PART_API_RTM_DU8            0x11
// API library CCP communication
#define VERSION_SW_PART_API_CCP_DU8            0x12
// API library ISOBUS communication
#define VERSION_SW_PART_API_ISOBUS_DU8         0x13


//--- defines for sys_permitAfterRun
// API does not enter the AfterRun mode; all registered application tasks will be processed.
#define SYS_AFTERRUN_PREVENT_DU16              0u
// API enters the AfterRun mode after ignition set to off (default)
#define SYS_AFTERRUN_PERMIT_DU16               1u
// API enters the AfterRun mode if the ignition line was at least once OFF during this
// ignition phase
#define SYS_AFTERRUN_PERMIT_IGNITIONOFF_DU16   2u

/**************************************************************************************************/

/***************************************************************************************************
*  FUNCTION:      sys_enterCriticalSection
*/
/**\brief         Enter into an user critical section.
* That means nested interrups are not possible and access to global var's is safe.
* This macro stores the actual interrupt piority and then it will be set to a special/higher value.
* See also sys_leaveCriticalSection().
*
* Note SYS_CRITSECT_USER_PRIO = 13
*/
/**************************************************************************************************/

// PRQA S 3411,3412,5000 ++
#define sys_enterCriticalSection()                                                                 \
{                                                                                                  \
  /* It is used a very long name in order to reduce the chance that an var. of application has */  \
  /* the same name.                                                                            */  \
  uint32 sys_previousValueOfIcrCcpnUser_u32;                                                       \
                                                                                                   \
  sys_previousValueOfIcrCcpnUser_u32 = Cpu_GetCPUPrioApi();                                        \
  Cpu_SetCPUPrioApi(SYS_CRITSECT_USER_PRIO_DU8);                                                   \
  do { } while(0) /* this ugly statement is necessary to cheat MISRA checker */
// PRQA S 3411,3412 --

/**************************************************************************************************/


/***************************************************************************************************
*  FUNCTION:      sys_leaveCriticalSection
*/
/**\brief         Leave API critical section..
* See also sys_enterCriticalSection().
*/
/**************************************************************************************************/

// PRQA S 3411,3412,5000 ++
#define sys_leaveCriticalSection()                                                                 \
  Cpu_SetCPUPrioApi(sys_previousValueOfIcrCcpnUser_u32);                                           \
} do { } while(0) /* this ugly statement is necessary to cheat MISRA checker */
// PRQA S 3411,3412 --

/**************************************************************************************************/


/**** typdefs/structures ***************************************************************************
* Typedefs/structures to be made available to other modules.                                      */

/* Structure of error data for error handler, containing error code, occurrence counter and
   timestamp.
   Note: The sequence in struct and the data types are important and have not to be changed.
         reasons: a) It correspons with the layout of error data in EEPROM.
                  b) There are no gaps in memory layout (RAM) because 32 bit alignment. This
                     is important for loading errors from EEPROM or RAM mirror (see also a))!!!
*/
// PRQA S 5001 ++
// This structure name was already published.
typedef struct ErrorData_t
// PRQA S 5001 --
{
  uint16 Code_u16;      // Error code (module + function + type).
  uint8 Param_u8;       // Error parameter.
  uint8 Occurrence_u8;  // Error occurrence counter.
  uint32 Timestamp_u32; // Timestamp of the last occurrence in operating hours
                        // (min).
} __attribute__((packed)) ErrorData_ts;

// typedef for a task
typedef void (*Task_tpf) (void);

// typedef for an idle task
typedef void (*IdleTask_tpf) (void);

// typedef for an after run function
typedef void (*AfterRunFunction_tpf) (void);

// typedef for a set defaults function
typedef void (*SetDefaultsFunction_tpf) (void);

// typedef for an emergency task
typedef void (*EmergencyTask_tpf) (void);

typedef void (*VoidFunction_tpf) (void);

// typedef for an error (callback) function
typedef void(*FuncError_tpf) (uint16 errCode_u16, uint8 errParam_u8);

// PRQA S 5001 ++
// This structure name was already published.
typedef struct resetInfo_t
// PRQA S 5001 --
{
  uint32 adLocation_u32;          /* location where SoftwareReset is issued */
  uint16 id_u16;                  /* SoftwareReset Type (ID) */
  uint8  couReset_u8;             /* SoftwareReset counter */
  uint64 tiStampCurr_u64;         /* timestamp of current SoftwareReset */
  uint64 tiStampLast_u64;         /* timestamp of last SoftwareReset */
  uint32 dUserDefined_u32;        /* user specific data */
  uint8  dResetGrp_u8;            /* Reset-group (HW,WDT,SB,... */
  uint16 errCode_u16;             /* Error code (module + function + type). */
                                  /* See list with error codes in API manual */
  uint8 errParam_u8;              /* Error parameter. */
} resetInfo_ts;

// API library version information
// It must be 16 bytes and corresponds with memory layout fixed in linker.inv!
// PRQA S 5001 ++
// This structure name was already published.
typedef struct LibVersion_t
// PRQA S 5001 --
{
  uint8 LibName_au8[10];   // API library name (ASCII)
  uint8 LibVersion_au8[6]; // API library version (ASCII)
} __attribute__((packed)) LibVersion_ts;

// ECU information (in data system page 0)
// PRQA S 5001 ++
// This structure name was already published.
typedef struct EcuInfo_t
// PRQA S 5001 --
{
  uint8 IdNr_Custom_au8[20]; // identifier number custom
  uint8 IdNr_BR_au8[12]; // identifier number BR (Bosch Rexroth)
  uint8 ChangeRev_AE_au8[10]; // change revision AE (Automotive Electronics)
  uint8 SerialNr_au8[4]; // serial number
  uint8 FactoryCode_au8[2]; // factory code
  uint16 HwType_u16; // hardware type
  uint8 ProdDate_au8[3]; // production date (yy-mm-dd)
#ifdef BODAS_RTS
  uint8 dummy_au8[2]; // special handling is needed to have the same size in C and BODAS-design
#endif
} EcuInfo_ts;

/**** public data **********************************************************************************
* Declarations of variables to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */

/**** public functions *****************************************************************************
* Declarations of functions to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */
/**************************************************************************************************/

SCOPE_D uint32  sys_getAge(void);
SCOPE_D uint32  sys_getStartCounter(void);

SCOPE_D uint16  sys_getStartInfo(void);

SCOPE_D sint16  sys_getHwTemp(uint32 chnl_u32);
SCOPE_D sint16  sys_init(sint8 *swId_pas8,
                         sint8 *hwId_pas8);
SCOPE_D FuncError_tpf sys_registerErrorCallback(FuncError_tpf errHandler_pf);

SCOPE_D sint16  sys_getTaskLoad(uint16 timeMode_u16);
SCOPE_D sint32  sys_getTaskRunTime(uint8 taskId_u8,
                                   uint16 timeMode_u16);
SCOPE_D void    sys_resetTaskRunTime(void);

SCOPE_D sint32  sys_getTime(void);
SCOPE_D uint64  sys_getTime_us(void);

SCOPE_D uint16  sys_registerTask(Task_tpf func_pf,
                                 uint8 priority_u8,
                                 uint32 cycleTime_ms_u32,
                                 uint32 cycleOffset_ms_u32,
                                 uint8 *taskHandle_pu8);
SCOPE_D uint16  sys_registerIdleTask(IdleTask_tpf func_pf,
                                     uint8 *taskHandle_pu8);
SCOPE_D uint16  sys_registerSetDefaultsFunction(SetDefaultsFunction_tpf func_pf);
SCOPE_D uint16  sys_registerAfterRunFunction(AfterRunFunction_tpf func_pf);
SCOPE_D uint16  sys_registerEmergencyTask(EmergencyTask_tpf func_pf,
                                          uint32 cycleTime_ms_u32);

/*
see section with defines!
SCOPE_D void    sys_enterCriticalSection(void);
SCOPE_D void    sys_leaveCriticalSection(void);
*/

SCOPE_D void    sys_setError(uint16 errCode_u16,
                             uint8 errParam_u8,
                             bool errSaveEeprom_l);
SCOPE_D void    sys_setErrorExtTime(uint16 errCode_u16,
                                    uint8 errParam_u8,
                                    bool errSaveEeprom_l,
                                    uint32 errTimestamp_u32);
SCOPE_D uint16  sys_testError(uint16 errCode_u16,
                              uint8 errParam_u8);
SCOPE_D uint16  sys_getNumActiveErrors(void);
SCOPE_D uint16  sys_getNumSavedErrors(void);
SCOPE_D void    sys_delActiveError(uint16 errCode_u16,
                                   uint16 errParam_u16);
SCOPE_D void    sys_delActiveErrors(void);
SCOPE_D void    sys_delSavedErrors(void);
SCOPE_D uint16  sys_getActiveErrors(ErrorData_ts *errData_pas,
                                    uint16 startIndexErrors_u16,
                                    uint16 maxNumErrors_u16);
SCOPE_D uint16  sys_getSavedErrors(ErrorData_ts *errData_pas,
                                   uint16 startIndexErrors_u16,
                                   uint16 maxNumErrors_u16);

SCOPE_D bool    sys_getINH(void);

SCOPE_D uint16  sys_setVP(uint32 chnl_u32,
                          bool state_l);
SCOPE_D bool    sys_getVP(uint32 chnl_u32);
SCOPE_D uint16  sys_getSupply(uint32 chnl_u32);

SCOPE_D uint16  sys_setVSS(uint32 chnl_u32,
                           bool state_l);
SCOPE_D uint16  sys_cfgVSS(uint32 chnl_u32,
                           uint8 cfgVSS_u8);

SCOPE_D uint16  sys_getVersion(uint8 swPart_u8,
                               uint8 *buf_pau8,
                               uint16 bufLen_u16,
                               uint16 *copiedBytes_pu16);

SCOPE_D uint16  sys_getEcuInfo(EcuInfo_ts *EcuInfo_ps);

SCOPE_D void    sys_getResetInfo(resetInfo_ts *resetInfo_ps);
SCOPE_D void    sys_resetEcu(uint32 value_u32,
                             bool eepWait_l);
SCOPE_D void    sys_setEcu(uint16 state_u16);

SCOPE_D void    sys_startLoader(bool eepWait_l,
                                uint32 loaderExtCanTxId_u32,
                                uint8 chnl_u8);

SCOPE_D uint16  sys_initTC(uint8 checkPoint_u8,
                           uint8 interval_u8);
SCOPE_D uint16  sys_triggerTC(uint8 checkPoint_u8);

SCOPE_D void    sys_permitAfterRun(uint16 state_u16);
SCOPE_D bool    sys_getIgnition(void);
SCOPE_D void    sys_getTempProfile(uint32 *data_pau32);

#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _SYSTEM_D

#endif // _SYSTEM_H_D

/* EOF ########################################################################################## */
