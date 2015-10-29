//**************************************************************************************************
//
//  FILENAME:    dst_funcParams.h
//
//  DESCRIPTION:
//! \file        dst_funcParams.h
//! \brief       function handover parameter names (strings)
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
// FILE VERSION INFORMATION:  $Revision: 5232 $
//                            $Date: 2013-01-23 10:29:06 +0100 (Mi, 23 Jan 2013) $
//                            $Author: gtg2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _dst_funcparams_h_D
#define _dst_funcparams_h_D

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

// first index means the function index, second index means the parameter index
const HUGE FuncParams_ts FuncParams_as[][MaxFuncParams_DU8] =
{
   // **********************************************************************************************
   // function 0 (RC_diagTestFunction_pau8) parameter description
   // **********************************************************************************************

   {
      // *******************************************************************************************
      // function 0 parameter description 0
      // *******************************************************************************************
      { //****|****|****|****|****|****|**
         {
           "",
           "",
           "",
           "",
         }
      },
   },
};

// create pointer to this structure for diagnosis module
const HUGE FuncParams_ts * FuncParams_ps = (const HUGE FuncParams_ts *)FuncParams_as;
// get the maximum count of function parameters of one function for diagnosis module
const uint8 MaxNumberOfFuncParams_cu8    = (uint8)(sizeof(FuncParams_as[0]) /
                                                   sizeof(FuncParams_as[0][0]));

//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.


//**************************************************************************************************

#endif  // _dst_funcparams_h_D

// EOF #############################################################################################
