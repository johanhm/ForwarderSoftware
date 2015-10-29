//**************************************************************************************************
//
//  FILENAME:    dst_applErrors.h
//
//  DESCRIPTION:
//! \file        dst_applErrors.h
//! \brief       application error structure
//!
//! the error arrays have the following structure: \n
//!
//! application errors                 \n
//!   |                                \n
//!   +-- error 1                      \n
//!   |     |                          \n
//!   |     +-- error code             \n
//!   |     +-- error text language 1  \n
//!   |     +-- error text language 2  \n
//!   |     •                          \n
//!   |     +-- error text language n  \n
//!   |                                \n
//!   +-- error 2                      \n
//!   •                                \n
//!   +-- error n                      \n
//
// *************************************************************************************************
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC36-20/30
//
// FILE VERSION INFORMATION:  $Revision: 5232 $
//                            $Date: 2013-01-23 10:29:06 +0100 (Mi, 23 Jan 2013) $
//                            $Author: gtg2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _dst_applerrors_h_D
#define _dst_applerrors_h_D

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
const HUGE ApplError_ts ApplError_as[] =
{
  // **********************************************************************************************
  // application error 0x8000 - brief description
  // **********************************************************************************************
  {
    0x8000,  // error code (16 bit) for application errors has to be larger or equal 0x8000
    {  /****|****|****|****|****|****|**/
      "", // language 1
      "", // language 2
      "", // language 3
      ""  // language 4
    }
  },
  // **********************************************************************************************
  // application error table end flag - DO NOT MODIFY THE CODE 0xFFFF!
  // **********************************************************************************************
  {
    0xFFFF,  // no error code, this is the error table end flag
    {  /****|****|****|****|****|****|**/
      "Sorry, no comment available.", // language 1
      "Sorry, no comment available.", // language 2
      "Sorry, no comment available.", // language 3
      "Sorry, no comment available."  // language 4
    }
  },
};

// create pointer to this structure for diagnosis module
const HUGE ApplError_ts *ApplError_ps = ApplError_as;

//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.


//**************************************************************************************************

#endif  // _dst_applerrors_h_D

// EOF #############################################################################################
