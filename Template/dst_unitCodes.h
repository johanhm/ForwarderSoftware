//**************************************************************************************************
//
//  FILENAME:    dst_unitCodes.h
//
//  DESCRIPTION:
//! \file        dst_unitCodes.h
//! \brief       unit code constants (strings)
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

#ifndef _dst_unitcodes_h_D
#define _dst_unitcodes_h_D

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
const HUGE sint8 UnitCodes_cas8[][UnitCodeLength_DU8] =
{
  "",
};

// create pointer to this structure for diagnosis module
const HUGE uint8 * UnitCodes_ps = (const HUGE uint8 *)UnitCodes_cas8;
// set size of this structure for diagnosis module
const uint8 UnitCodeLength_cu8  = (uint8)(sizeof(UnitCodes_cas8[0]));

//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.


//**************************************************************************************************

#endif  // _dst_unitcodes_h_D

// EOF #############################################################################################
