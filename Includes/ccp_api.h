//**************************************************************************************************
//
//  FILENAME:    ccp_api.h
//
//  DESCRIPTION:
//! \file        ccp_api.h
//! \brief       header file for ccp api functions
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_Plattform
//
// FILE VERSION INFORMATION:  $Revision: 5854 $
//                            $Date: 2013-05-21 16:21:57 +0200 (Di, 21 Mai 2013) $
//                            $Author: oub2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _CCP_API_H_D
  #define _CCP_API_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"         //standard type definitions

#ifdef _CCP_API_D
  #define SCOPE_D
#else
  #define SCOPE_D extern
#endif   // _CCP_API_D

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

#define DaqListEvent_DU8                  0
#define DaqList10ms_DU8                   1
#define DaqList100ms_DU8                  2
#define DaqListMaxNbr_DU8                 3   // CAUTION: this number must match with the nbr of
                                              // entries of the DAQ_Descritor[] within the core!

//--- return codes of ccp api functions
#define CCP_RC_NO_ERRORS_DU16             0   // ok
#define CCP_RC_INV_PARAM1_DU16            1   // invalid parameter 1
#define CCP_RC_INV_PARAM2_DU16            2   // invalid parameter 2
#define CCP_RC_INV_PARAM3_DU16            3   // invalid parameter 3
#define CCP_RC_INV_PARAM4_DU16            4   // invalid parameter 4
#define CCP_RC_INV_PARAM5_DU16            5   // invalid parameter 5
#define CCP_RC_INV_PARAM6_DU16            6   // invalid parameter 6

#define CCP_RC_BUFF_OVL_OTHER_START_DU16  10  // ODT buffer overlaps with another API buffer,
                                              // buffer has another start address
#define CCP_RC_BUFF_OVL_SAME_START_DU16   11  // ODT buffer overlaps with another API buffer,
                                              // buffer has the same start address

#define CCP_RC_INV_ODT_START_DU16         20  // ODT start is located in other DAQ list
#define CCP_RC_INV_ODT_END_DU16           21  // ODT end is located in other DAQ list

#define CCP_RC_INITCOMM_NOT_ALLOWED_DU16  30  // ccp_initComm is not allowed outside sys_main()/PLC
#define CCP_RC_INITCOMM_ALREADY_DONE_DU16 31  // ccp_initComm was already done
#define CCP_RC_INITCOMM_INIT_IDLE_DU16    32  // error during register of idle task
#define CCP_RC_INITCOMM_INIT_APPL_DU16    33  // error during register of appl task
#define CCP_RC_NO_DAQ_DEFINED_DU16        34  // there is no DAQ list defined

#define CCP_RC_TO_LESS_DATABOXES_DU16     40  // to less hw databoxes configured
#define CCP_RC_DATABOX_ALREADY_USED_DU16  41  // hw databox already used by canInitRxDatabox()

#define CCP_RC_UNDEFINED_ERROR_DU16       99  // undefined error should not occur


//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.

// from core header ccp_services_prot.h
#ifndef _CCP_SERVICES_PROT_H
// PRQA S 5001, 5003 ++
typedef struct
{
   uint8        *adOdtEntry_a[7];
   uint8         dMeasBuff_au8[8];
   uint8         ctElements_u8 ;
} Ccp_odt_t;
// PRQA S 5001, 5003 --
#endif

//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.


//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.

// register memory for all UDS protocol instances (1 array element per instance required)
SCOPE_D uint16 ccp_registerOdtBuf(Ccp_odt_t  *odt_pas,
                                  uint8      nbrOdt_u8);

SCOPE_D uint16 ccp_initDaqList(uint8  daqList_u8,
                               uint32 txCanId_u32,
                               uint8  txCanFormat_u8,
                               uint8  startOdt_u8,
                               uint8  nbrOdt_u8);

SCOPE_D uint16 ccp_initComm(uint8   canChnl_u8,
                            uint16  ecuAddr_u16,
                            uint32  txCanId_u32,
                            uint8   txCanFormat_u8,
                            uint32  rxCanId_u32,
                            uint8   rxCanFormat_u8,
                            uint8   priority_u8);

SCOPE_D void ccp_triggerDaqEvent(void);

//**************************************************************************************************

#undef SCOPE_D

#undef _CCP_API_D             // reseting definition, prevents double definition of a variable if
                              // includes are nested
#endif  // _CCP_API_H_D

// EOF #############################################################################################
