//**************************************************************************************************
//
//  FILENAME:    dst_ecuLanguage.h
//
//  DESCRIPTION:
//! \file        dst_ecuLanguage.h
//! \brief       definition of supported ecu languages
//!
//
// *************************************************************************************************
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC36-20/30
//
// FILE VERSION INFORMATION:  $Revision: 5282 $
//                            $Date: 2013-01-30 17:14:15 +0100 (Mi, 30 Jan 2013) $
//                            $Author: gtg2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _dst_eculanguage_h_D
#define _dst_eculanguage_h_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"           // standard type definitions
#include "dst_main.h"


//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.

//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.

// first index means the list index, second index means the list entry index
const HUGE sint8 Languages_as8[NumberOfLanguages_DU8][TextLength_DU8] =
{
  // language 0
  "",
  // language 1
  "",
  // language 2
  "",
  // language 3
  "",
};

// create pointer to this structure for diagnosis module
const HUGE uint8 * Languages_ps   = (const HUGE uint8 *)Languages_as8;
// set count of languages for diagnosis module
const uint8 NumberOfLanguages_cu8 = (uint8)(sizeof(Languages_as8) / sizeof(Languages_as8[0]));

//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.


//**************************************************************************************************

#endif  // _dst_eculanguage_h_D

// EOF #############################################################################################
