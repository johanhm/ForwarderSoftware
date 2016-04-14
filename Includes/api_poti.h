//**************************************************************************************************
//
//  FILENAME:    api_poti.h
//
//  DESCRIPTION:
//! \file        api_poti.h
//! \brief       Header file for the Poti devive module within the C-API.
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

#ifndef _API_POTI_H_D
#define _API_POTI_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"           // standard type definitions

#ifdef _API_POTI_D
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   // _API_POTI_D

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.


//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.


//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.

SCOPE_D sint16 inext_getPotiMin(sint16 memVal_s16);
SCOPE_D sint16 inext_getPotiMax(sint16 memVal_s16);
SCOPE_D sint16 inext_getPotiMid(sint16 memVal_s16);
SCOPE_D sint16 inext_getPoti(uint32 chnl_u32, sint16 potiMin_s16, sint16 potiMax_s16,
                             sint16 errMin_s16, sint16 errMax_s16);
SCOPE_D sint16 inext_getPotiDir(uint32 chnl_u32, sint16 potiMin_s16,
                                sint16 potiMax_s16, sint16 potiMid_s16,
                                sint16 errMin_s16, sint16 errMax_s16);
SCOPE_D sint16 inext_getPotiStatus(uint32 chnl_u32);
SCOPE_D void   inext_cfgPoti(uint32 chnl_u32, uint16 maxVal_u16);

//**************************************************************************************************

#undef SCOPE_D
#undef _API_POTI_D       // reseting definition, prevents double definition of a variable if
                         // includes are nested
#endif  // _API_POTI_H_D

// EOF #############################################################################################
