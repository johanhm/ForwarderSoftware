//**************************************************************************************************
//
//  FILENAME:    dst_procstructure.h
//
//  DESCRIPTION:
//! \file        dst_procstructure.h
//! \brief       process variable structure
//!
//
//  process variable tree - variable count of process variable groups in the tree
//
//
//  the process variable tree has the following structure:
//
//  root
//    |
//    +-- process variable group 1
//    |     |
//    |     +-- process variable 1.1
//    |     |     |
//    |     |     +-- property 1.1.1
//    |     |     +-- property 1.1.2
//    •     •     •
//    |     |     +-- property 1.1.16
//    |     |
//    |     +-- process variable 1.2
//    •     •
//    |     +-- process variable 1.8
//    |
//    +-- process variable group 2
//    •
//    +-- process variable group n
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

#ifndef _dst_procstructure_h_D
#define _dst_procstructure_h_D

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

const HUGE ProcessVariableGroup_ts ProcessVarGroups_as[] =
{

}; // end of process variable tree

// create pointer to this structure for diagnosis module
const HUGE ProcessVariableGroup_ts * ProcessVarGroups_ps = ProcessVarGroups_as;
// set size of this structure for diagnosis module
const uint8 NumberOfProcessVariableGroups_cu8            = (uint8)(sizeof(ProcessVarGroups_as) /
                                                                   sizeof(ProcessVarGroups_as[0]));

//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.


//**************************************************************************************************

#endif  // _dst_procstructure_h_D

// EOF #############################################################################################
