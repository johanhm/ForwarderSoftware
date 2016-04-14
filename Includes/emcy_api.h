//**************************************************************************************************
//
//  FILENAME:    emcy_api.h
//
//  DESCRIPTION:
//! \file        emcy_api.h
//! \brief       Header file for API functions of Emergency module of the C-API.
//!
//!
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30 platform
//
// FILE VERSION INFORMATION:  $Revision: 5269 $
//                            $Date: 2013-01-29 13:52:04 +0100 (Di, 29 Jan 2013) $
//                            $Author: gtg2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _EMCY_API_H_D
#define _EMCY_API_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"         // standard type definitions from core
#include "emcy_types.h"         // public type definitions for emergency module

#ifdef _EMCY_API_D
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   // _EMCY_API_D

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.


//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.


//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.

SCOPE_D uint16 emcy_cfg(const uint16 debounceTime_cu16,
                      const uint16 debounceTimeInv_cu16,
                      const emcy_callback_tpf func_cpf);
SCOPE_D void   emcy_setPowerOff(void);
SCOPE_D void   emcy_setPowerOn(void);
SCOPE_D bool   emcy_getStatus(void);
SCOPE_D uint16 emcy_disableInput(const uint32 key_cu32, const uint32 keyInv_cu32);

//**************************************************************************************************

#undef SCOPE_D
#undef _EMCY_API_D      // reseting definition, prevents double definition of a variable if
                        // includes are nested
#endif  // _EMCY_API_H_D

// EOF #############################################################################################
