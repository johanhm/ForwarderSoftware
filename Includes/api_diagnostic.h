//**************************************************************************************************
//
//  FILENAME:    api_diagnostic.h
//
//  DESCRIPTION:
//! \file        api_diagnostic.h
//! \brief       header file for diagnostic functions
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_Plattform
//
// FILE VERSION INFORMATION:  $Revision: 5232 $
//                            $Date: 2013-01-23 10:29:06 +0100 (Mi, 23 Jan 2013) $
//                            $Author: gtg2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _API_DIAGNOSTIC_H_D
   #define _API_DIAGNOSTIC_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"     //standard type definitions

#ifdef _API_DIAGNOSTIC_D
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   // _API_DIAGNOSTIC_D

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.


//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.

//! typedef for the function pointer for the function to copy changed paramters to application
typedef void (*applCopyFunc_tpf)(void);


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.

//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.
SCOPE_D void   diag_initComm(uint8 canChnl_u8, uint16 txKwpDatabox_u16, uint16 rxKwpDatabox_u16,
                             uint16 rxScanDatabox_u16, uint8 priority_u8, uint8 cycleTime_u8);
SCOPE_D void   diag_setProcessVar(uint8 treeIdx_u8, uint8 parIdx_u8, sint32 value_s32);
SCOPE_D void   diag_setDefaultValues(void);
SCOPE_D void   diag_setMachineType(sint16 machineType_s16);
SCOPE_D void   diag_setVarsCallBack(applCopyFunc_tpf applCopyFunc_pf);
SCOPE_D void   diag_permitAccess(uint16 access_u16);

//**************************************************************************************************

#undef SCOPE_D

#undef _API_DIAGNOSTIC_D       // reseting definition, prevents double definition of a variable if
                               // includes are nested
#endif  // _API_DIAGNOSTIC_H_D

// EOF #############################################################################################
