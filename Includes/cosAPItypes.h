//**************************************************************************************************
//
//  FILENAME:    cosAPItypes.h
//
//  DESCRIPTION:
//! \file        cosAPItypes.h
//! \brief       CANopen C-API type definitions
//!
//! Type definitions for the CANopen C-API.
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   CANopen for RC
//
// FILE VERSION INFORMATION:  $Revision: 5404 $
//                            $Date: 2013-02-18 15:12:44 +0100 (Mo, 18 Feb 2013) $
//                            $Author: rpc2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _COSAPITYPES_H_
#define _COSAPITYPES_H_

#ifdef _COSAPITYPES_
   #define SCOPE
#else
   #define SCOPE extern
#endif   // _COSAPITYPES_

#include "common.h"             // core include with standard type definitions
#include "types.h"              // further rc30 specific common definitions

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.
#define boolean bool

// error control status for NMT master
#define NoMonitoring_DU8    0       // no error control
#define NodeGuarding_DU8    1       // master functions for Node Guarding activated
#define Heartbeat_DU8       2       // master functions for Heartbeat activated

// CIA405 error codes
#define CIA405_NO_ERROR_DU8           0     // no error
#define CIA405_OTHER_ERROR_DU8        1     // general error
#define CIA405_DATA_OVERFLOW_DU8      2     // internal queue overflow (too much data)
#define CIA405_TIME_OUT_DU8           3     // no answer (request timeout)
#define CIA405_CAN_BUS_OFF_DU8        16    // bus off
#define CIA405_CAN_ERROR_PASSIVE_DU8  17    // error passive

// local access error codes
#define LOCAL_READOBJECT_ERROR_DU8    33    // error by reading a local object
#define LOCAL_WRITEOBJECT_ERROR_DU8   34    // error by writing a local object

// sdo transfer error codes
#define NO_FREE_SLOT_DU8              35    // no free slots for SDO communication available
#define SDO_TRANSFER_FAILED_DU8       36    // SDO transfer failed
#define DEVICE_NOT_ALLOWED_DU8        39    // device currently not allowed because request(s)
                                            // to another device are still pending

// emcy error codes
#define EMCY_FOUND_DU8                37    // EMCY object found

// nmt error codes
#define NMT_MASTER_NOT_ACTIVE_DU8     38    // no NMT master active (Object 0x1F80)

// general error flags
#define NO_ERROR_DU8        0x00            // error
#define ERROR_DU8           0xFF            // no error

// BODAS needs huge pointer     //not required for BR30
#ifdef BODAS_RTS
  #define PHUGE
#else
  #define PHUGE
#endif

//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.

//--- CIA 405 TYPES: -------------------------------------------------------------------------------

// the following data types are specified in CiA DS-405
typedef uint8    CIA405_Device_tu8;
typedef uint16   CIA405_CANOpen_Kernel_Error_tu16;
typedef uint32   CIA405_SDO_Error_tu32;

typedef enum
{
  INIT_E,
  RESET_COMM_E,
  RESET_APP_E,
  PRE_OPERATIONAL_E,
  STOPPED_E,
  OPERATIONAL_E,
  UNKNOWN_E,
  NOT_AVAIL_E
} CIA405_State_te;

typedef enum
{
  START_REMOTE_NODE_E = 1,
  STOP_REMOTE_NODE_E = 2,
  ENTER_PRE_OPERATIONAL_E = 128,
  RESET_NODE_E = 129,
  RESET_COMMUNICATION_E = 130
} CIA405_Transition_State_te;

typedef struct
{
  uint16 ErrorCode_u16;
  uint8  ErrorRegister_u8;
  uint8  ErrorField_au8[5];
} CIA405_EMCY_Error_ts;

typedef struct
{
  uint16 ErrorCode_u16;
  boolean EnableEMCY_l;
  uint8  ErrorField_au8[5];
} CIA405_EMCY_ts;


//--- RCE LIBRARY TYPES: ---------------------------------------------------------------------------

typedef struct
{
  uint32  Object_u32;
  uint32  Value_u32;
} CANopenParameter_ts;


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.


//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.


//**************************************************************************************************

#undef SCOPE
#undef _COSAPITYPES_  // reseting definition, prevents double definition of a variable if
                      // includes are nested
#endif  // _COSAPITYPES_H_

// EOF #############################################################################################
