//**************************************************************************************************
//
//  FILENAME:    dflash_Func.h
//
//  DESCRIPTION:
//! \brief       Interface for dflash_Func.c
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

#ifndef _DFLASH_FUNC_H_D
  #define _DFLASH_FUNC_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"

#ifdef _DFLASH_FUNC_D
  #define SCOPE_D
#else
  #define SCOPE_D extern
#endif   // _DFLASH_FUNC_D

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.


//**************************************************************************************************


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.


//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.
SCOPE_D sint16 dflash_eeSaveValue(sint16 page_s16, sint16 index_s16, sint16 val_s16);
SCOPE_D sint16 dflash_eeSaveValue(sint16 page_s16, sint16 index_s16, sint16 val_s16);
SCOPE_D sint16 dflash_eeSaveArray(sint16 page_s16, sint16 index_s16, sint16 *data_ps16,
                                  sint16 len_s16);
SCOPE_D sint16 dflash_eeSavePage(sint16 page_s16);
SCOPE_D sint16 dflash_reeGetValue(sint16 page_s16, sint16 index_s16);
SCOPE_D sint16 dflash_reeGetArray(sint16 page_s16, sint16 index_s16, sint16 *data_ps16,
                                  sint16 len_s16);
SCOPE_D void dflash_reeSetValue(sint16 page_s16, sint16 index_s16, sint16 val_s16);
SCOPE_D void dflash_reeSetArray(sint16 page_s16, sint16 index_s16, sint16 *data_ps16,
                                sint16 len_s16);
SCOPE_D sint16 dflash_eeGetStatus(void);

#undef SCOPE_D

#undef _DFLASH_FUNC_D      // reseting definition, prevents double definition of a variable if
                           // includes are nested
#endif  // _DFLASH_FUNC_H_D

// EOF #############################################################################################
