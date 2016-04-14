//**************************************************************************************************
//
//  FILENAME:    dst_passwords.h
//
//  DESCRIPTION:
//! \file        dst_passwords.h
//! \brief       implements diagnostic accesslevel passwords
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

#ifndef _dst_passwords_h_D
#define _dst_passwords_h_D

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

//! the password for the lowest access - DO NOT CHANGE THIS PASSWORD - the tool will use it
//! to initialize demo access after scanning
const HUGE sint8 dia_PasswordDemo_cas8[PasswordLength_DU8] = "oNlY dEmO aCcEsS";
//! the password for service access level - DO NOT CHANGE THIS PASSWORD - this password will be
//! read from the BODAS service copy protection dongle internal data
const HUGE sint8 dia_PasswordServ_cas8[PasswordLength_DU8] = "sErViCeTeChNiKeR";
//! here you can define the third level password
const HUGE sint8 dia_PasswordAdju_cas8[PasswordLength_DU8] = "";
//! here you can define the highest level password
const HUGE sint8 dia_PasswordDeve_cas8[PasswordLength_DU8] = "";

// create pointer to this structure for diagnosis module
const HUGE sint8 *dia_PasswordDemo_ps8 = dia_PasswordDemo_cas8;
// create pointer to this structure for diagnosis module
const HUGE sint8 *dia_PasswordServ_ps8 = dia_PasswordServ_cas8;
// create pointer to this structure for diagnosis module
const HUGE sint8 *dia_PasswordAdju_ps8 = dia_PasswordAdju_cas8;
// create pointer to this structure for diagnosis module
const HUGE sint8 *dia_PasswordDeve_ps8 = dia_PasswordDeve_cas8;
// set size of these structures for diagnosis module
const uint8 PasswordLength_cu8 = PasswordLength_DU8;

//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.


//**************************************************************************************************

#endif  // _dst_passwords_h_D

// EOF #############################################################################################
