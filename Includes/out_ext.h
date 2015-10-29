//**************************************************************************************************
//
//  FILENAME:    out_ext.h
//
//  DESCRIPTION:
//! \file        out_ext.h
//! \brief       Header file for Output Extension module within the C-API.
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

#ifndef _OUT_EXT_H_D
#define _OUT_EXT_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"           // standard type definitions

#ifdef _OUT_EXT_D
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   // _OUT_EXT_D

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.


//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.


//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.

SCOPE_D void outext_setProp(uint32 chnl_u32, uint16 val_u16, uint16 iMin_u16, uint16 iMax_u16);
SCOPE_D uint16 outext_getProp(uint32 chnl_u32);
SCOPE_D uint16 outext_getPropSet(uint32 chnl_u32);

//**************************************************************************************************

#undef SCOPE_D
#undef _OUT_EXT_D       // reseting definition, prevents double definition of a variable if
                        // includes are nested
#endif  // _OUT_EXT_H_D

// EOF #############################################################################################
