//**************************************************************************************************
//
//  FILENAME:    dst_parastructure.h
//
//  DESCRIPTION:
//! \file        dst_parastructure.h
//! \brief       parameter structure
//!
//! Parameter tree - variable count of parameter menues in the tree
//!
//! the parameter tree has the following structure:
//!
//! root
//!   |
//!   +-- parameter menu 1
//!   |     |
//!   |     +-- parameter group 1.1
//!   |     |     |
//!   |     |     +-- parameter 1.1.1
//!   |     |     |     |
//!   |     |     |     +-- property 1.1.1.1
//!   |     |     |     +-- property 1.1.1.2
//!   •     •     •     •
//!   |     |     |     +-- property 1.1.1.16
//!   |     |     |
//!   |     |     +-- parameter 1.1.2
//!   •     •     •
//!   |     |     +-- parameter 1.1.8
//!   |     |
//!   |     +-- parameter group 1.2
//!   •     •
//!   |     +-- parameter group 1.8
//!   |
//!   +-- parameter menu 2
//!   •
//!   +-- parameter menu n
//!
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

#ifndef _dst_parastructure_h_D
#define _dst_parastructure_h_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"           // standard type definitions
#include "dst_main.h"


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.

const HUGE ParameterMenu_ts ParameterMenus_as[] =
{

}; // end of parameter tree

// create pointer to this structure for diagnosis module
const HUGE ParameterMenu_ts *ParameterMenus_ps  = (const HUGE ParameterMenu_ts *)ParameterMenus_as;
// set size of this structure for diagnosis module
const uint8 NumberOfParameterMenus_cu8          = (uint8)(sizeof(ParameterMenus_as) /
                                                          sizeof(ParameterMenus_as[0]));
// set count of default values for every parameter for diagnosis module
const uint8 NumberOfDefaultValues_cu8           = NumberOfDefaultValues_DU8;
// set maximum string length for diagnosis module
const uint8 TextLength_cu8                      = TextLength_DU8;

//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.


//**************************************************************************************************

#endif  // _dst_parastructure_H_D

// EOF #############################################################################################
