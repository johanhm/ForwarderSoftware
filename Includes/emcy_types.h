//**************************************************************************************************
//
//  FILENAME:    emcy_types.h
//
//  DESCRIPTION:
//! \file        emcy_types.h
//! \brief       Header file for public type definitions of Emergency module of the C-API.
//!
//!
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30 platform
//
// FILE VERSION INFORMATION:  $Revision: 5232 $
//                            $Date: 2013-01-23 10:29:06 +0100 (Mi, 23 Jan 2013) $
//                            $Author: gtg2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _EMCY_TYPES_H_D
#define _EMCY_TYPES_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"

#ifdef _EMCY_TYPES_D
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   // _EMCY_TYPES_D

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

//! security key for the deactivation of the emergency input
#define EMCY_DISABLE_KEY_DU32           (uint32)0x15A61959


//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.

//! typedef for the function pointer to the error callback function within the application
typedef void (*emcy_callback_tpf)(void);


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.


//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.


//**************************************************************************************************

#undef SCOPE_D
#undef _EMCY_TYPES_D     // reseting definition, prevents double definition of a variable if
                        // includes are nested
#endif  // _EMCY_TYPES_H_D

// EOF #############################################################################################
