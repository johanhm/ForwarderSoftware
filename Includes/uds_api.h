//**************************************************************************************************
//
//  FILENAME:    uds_api.h
//
//  DESCRIPTION:
//! \file        uds_api.h
//! \brief       header file for uds api functions
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_Plattform
//
// FILE VERSION INFORMATION:  $Revision: 5371 $
//                            $Date: 2013-02-14 16:33:22 +0100 (Do, 14 Feb 2013) $
//                            $Author: oub2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _UDS_API_H_D
  #define _UDS_API_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"         //standard type definitions
#include "uds_types.h"          // UDS type definitions

#ifdef _UDS_API_D
  #define SCOPE_D
#else
  #define SCOPE_D extern
#endif   // _UDS_API_D

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

//--- return codes of uds api functions
#define UDS_RC_NO_ERRORS_DU16             0   // ok
#define UDS_RC_INV_PARAM1_DU16            1   // invalid parameter 1
#define UDS_RC_INV_PARAM2_DU16            2   // invalid parameter 2
#define UDS_RC_INV_PARAM3_DU16            3   // invalid parameter 3
#define UDS_RC_INV_PARAM4_DU16            4   // invalid parameter 4
#define UDS_RC_INV_PARAM5_DU16            5   // invalid parameter 5
#define UDS_RC_INV_PARAM6_DU16            6   // invalid parameter 6
#define UDS_RC_INV_PARAM7_DU16            7   // invalid parameter 7
#define UDS_RC_INV_PARAM8_DU16            8   // invalid parameter 8
#define UDS_RC_INV_PARAM9_DU16            9   // invalid parameter 9

#define UDS_RC_INITRXBOX_FAILED_DU16      20  // init can rx databox failed
#define UDS_RC_INITTXBOX_FAILED_DU16      21  // init can tx databox failed
#define UDS_RC_INITBCRXBOX_FAILED_DU16    22  // init can broadcast rx databox failed

#define UDS_RC_INIT_DONE_DU16             30  // initComm already done and not allowed any more
#define UDS_RC_REGTASK_FAILED_DU16        31  // register task failed (e.g. outside sys_main())
#define UDS_RC_REGINST_NOT_ALLOWED_DU16   32  // register instances not allowed outside sys_main()
#define UDS_RC_REGBUFF_NOT_ALLOWED_DU16   33  // register buffers not allowed outside sys_main()
#define UDS_RC_INITCOMM_NOT_ALLOWED_DU16  34  // initComm not allowed outside sys_main()

#define UDS_RC_UDSRXBUFF_MISSING_DU16     40  // UDS RX buffer required, but not yet registered
#define UDS_RC_UDSTXBUFF_MISSING_DU16     41  // UDS TX buffer required, but not yet registered

#define UDS_RC_UNDEFINED_ERROR_DU16       99  // undefined error should not occur

//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.


//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.

// register memory for all UDS protocol instances (1 array element per instance required)
SCOPE_D uint16 uds_registerInstances(uds_instance_ts *mem_pas,      // pointer to instance table
                                     uint16          num_u16);      // total amount of uds instances

// register a callback function for the evaluation of the received UDS message
SCOPE_D uint16 uds_registerRxCallback(uint8          instanceNum_u8,// number of uds instance
                                      rxCallback_tpf rxFunc_pf);    // pointer to RX routine

// register a callback function for run time errors
SCOPE_D uint16 uds_registerErrorCallback(uint8       instanceNum_u8,// number of uds instance
                                   errorCallback_tpf errorFunc_pf); // pointer to error routine

// register RX and TX UDS message buffers
SCOPE_D uint16 uds_registerBuffers(uint8  instanceNum_u8,           // number of uds instance
                                   uint8  *rxBuff_pau8,             // pointer to uds rx buffer
                                   uint16 rxBuffLen_u16,            // length of uds rx buffer
                                   uint8  *txBuff_pau8,             // pointer to uds tx buffer
                                   uint16 txBuffLen_u16);           // length of uds tx buffer

// initialize and start one UDS instance
SCOPE_D uint16 uds_initComm(uint8  instanceNum_u8,                  // number of uds instance
                            uint8  canChnl_u8,                      // can channel
                            uint16 rxDatabox_u16,                   // rx databox number
                            uint32 baseCanId_u32,                   // 13 MSB bits of CAN id
                            uint8  ownAddr_u8,                      // own address
                            uint8  toolAddr_u8,                     // tool address
                            uint8  priority_u8,                     // priority of uds system task
                            uint8  cycleTime_u8,                    // cycle time of uds task
                            uint8  comType_u8);                     // communication type

SCOPE_D uint16 uds_initBcRxDatabox(uint8  instanceNum_u8,
                                   uint16 bcRxDatabox_u16);

//**************************************************************************************************

#undef SCOPE_D

#undef _UDS_API_D             // reseting definition, prevents double definition of a variable if
                              // includes are nested
#endif  // _UDS_API_H_D

// EOF #############################################################################################
