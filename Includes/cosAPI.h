//**************************************************************************************************
//
//  FILENAME:    cosAPI.h
//
//  DESCRIPTION:
//! \file        cosAPI.h
//! \brief       CANopen C-API
//!
//! This module implements the C-API for the Project CANopen for RC. The functions based on the
//! CiA DS-405 spezification. They can be used by customers withon their own applications.
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

#ifndef _COSAPI_H_
#define _COSAPI_H_

//*** include files ********************************************************************************
// List of include files needed in this module.

#include "cosAPItypes.h"


#ifdef _COSAPI_
   #define SCOPE
#else
   #define SCOPE extern
#endif   // _COSAPI_

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

// ---------- Error codes used within canopen stack --------------
//! no error
#define COS_ERR_NO_ERROR_DU16                  (uint16)(0)
//! parameter <nbr> within function call canopen_init() out of range
#define COS_ERR_CANOPEN_INIT_DU16              (COS_DU16 | 0x0001u)
//! canopen_init() was not executed within sys_main()
#define COS_ERR_CANOPEN_INIT_NOT_ALLOWED_DU16  (COS_DU16 | 0x0002u)
//! canopen_init() was already executed
#define COS_ERR_CANOPEN_INIT_ALREADY_DONE_DU16 (COS_DU16 | 0x0003u)

//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.

SCOPE uint8   cos_apiMonitoringMode_u8;
SCOPE uint8   cos_apiChannel_u8;
SCOPE uint16  cos_apiTxBox_u16;

//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.

SCOPE void canopen_init(uint8  channel_u8, uint8  priority_u8, uint16 txCosDatabox_u16);


//--- CIA 405 FUNCTIONS: ---------------------------------------------------------------------------

SCOPE void CIA405_SDO_WRITE4( CIA405_Device_tu8                       device_u8,
                              uint16                                  index_u16,
                              uint8                                   subindex_u8,
                              boolean                                 enable_l,
                              uint8 PHUGE                             *data_pau8,
                              uint8                                   datalength_u8,
                              boolean PHUGE                           *confirm_pl,
                              CIA405_CANOpen_Kernel_Error_tu16 PHUGE  *error_pu16,
                              CIA405_SDO_Error_tu32 PHUGE             *errorinfo_pu32 );


SCOPE void CIA405_SDO_WRITE512( CIA405_Device_tu8                       device_u8,
                                uint16                                  index_u16,
                                uint8                                   subindex_u8,
                                boolean                                 enable_l,
                                uint8 PHUGE                             *data_pau8,
                                uint16                                  datalength_u16,
                                boolean PHUGE                           *confirm_pl,
                                CIA405_CANOpen_Kernel_Error_tu16 PHUGE  *error_pu16,
                                CIA405_SDO_Error_tu32 PHUGE             *errorinfo_pu32 );


SCOPE void CIA405_SDO_READ4( CIA405_Device_tu8                       device_u8,
                             uint16                                  index_u16,
                             uint8                                   subindex_u8,
                             boolean                                 enable_l,
                             uint8 PHUGE                             *data_pau8,
                             uint8 PHUGE                             *datalength_pu8,
                             boolean PHUGE                           *confirm_pl,
                             CIA405_CANOpen_Kernel_Error_tu16 PHUGE  *error_pu16,
                             CIA405_SDO_Error_tu32 PHUGE             *errorinfo_pu32 );


SCOPE void CIA405_SDO_READ512( CIA405_Device_tu8                      device_u8,
                               uint16                                 index_u16,
                               uint8                                  subindex_u8,
                               boolean                                enable_l,
                               uint8 PHUGE                            *data_pau8,
                               uint16 PHUGE                           *datalength_pu16,
                               boolean PHUGE                          *confirm_pl,
                               CIA405_CANOpen_Kernel_Error_tu16 PHUGE *error_pu16,
                               CIA405_SDO_Error_tu32 PHUGE            *errorinfo_pu32 );


SCOPE void CIA405_GET_LOCAL_NODE_ID( boolean                  enable_l,
                                     boolean PHUGE            *confirm_pl,
                                     CIA405_Device_tu8 PHUGE  *device_pu8 );


SCOPE void CIA405_GET_STATE( CIA405_Device_tu8      device_u8,
                             boolean                enable_l,
                             boolean PHUGE          *confirm_pl,
                             CIA405_State_te PHUGE  *state_pe );


SCOPE void CIA405_GET_CANOPEN_KERNEL_STATE( boolean                                 enable_l,
                                            boolean PHUGE                           *confirm_pl,
                                            CIA405_CANOpen_Kernel_Error_tu16 PHUGE  *error_pu16 );


SCOPE void CIA405_NMT( CIA405_Device_tu8                      device_u8,
                       CIA405_Transition_State_te             state_e,
                       boolean                                enable_l,
                       boolean PHUGE                          *confirm_pl,
                       CIA405_CANOpen_Kernel_Error_tu16 PHUGE *error_pu16 );


SCOPE void CIA405_SEND_EMCY( boolean              enable_l,
                             CIA405_EMCY_ts PHUGE *emcy_ps,
                             boolean PHUGE        *confirm_pl );


SCOPE void CIA405_RECV_EMCY_DEV( CIA405_Device_tu8                      device_u8,
                                 boolean                                enable_l,
                                 boolean PHUGE                          *confirm_pl,
                                 CIA405_CANOpen_Kernel_Error_tu16 PHUGE *error_pu16,
                                 CIA405_EMCY_Error_ts PHUGE             *errorinfo_ps );


SCOPE void CIA405_RECV_EMCY( boolean                                enable_l,
                             boolean PHUGE                          *confirm_pl,
                             CIA405_Device_tu8 PHUGE                *device_pu8,
                             CIA405_CANOpen_Kernel_Error_tu16 PHUGE *error_pu16,
                             CIA405_EMCY_Error_ts PHUGE             *errorinfo_ps );


SCOPE void CIA405_TRIGGER_EVENT( uint8 sendpdo_u8 );


//**************************************************************************************************

#undef SCOPE
#undef _COSAPI_  // reseting definition, prevents double definition of a variable if
                 // includes are nested
#endif  // _COSAPI_H_

// EOF #############################################################################################
