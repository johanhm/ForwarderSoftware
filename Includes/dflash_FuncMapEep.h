//**************************************************************************************************
//
//  FILENAME:    dflash_FuncMapEep.h
//
//  DESCRIPTION:
//! \brief       mapping functions of DFLASH to EEPROM
//
// Mapping is needed if there is no EEPROM on ECU. In this case dflash functions should be
// called with the names of EEPROM module.
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_Plattform
///                           Hardware: RC30-00D6
//
// FILE VERSION INFORMATION:  $Revision: 5862 $
//                            $Date: 2013-05-27 16:40:45 +0200 (Mo, 27 Mai 2013) $
//                            $Author: ltm2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _DFLASH_FUNCMAPEEP_H_D
  #define _DFLASH_FUNCMAPEEP_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.


//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

// PRQA S 5000 ++
// API functions

// no mapping !!!
#if(0)
//#define ee_saveValue(a,b,c)   dflash_eeSaveValue(a,b,c)
//#define ee_saveArray(a,b,c,d) dflash_eeSaveArray(a,b,c,d)
//#define ee_savePage(a)        dflash_eeSavePage(a)
//#define ree_getValue(a,b)     dflash_reeGetValue(a,b)
//#define ree_getArray(a,b,c,d) dflash_reeGetArray(a,b,c,d)
//#define ree_setValue(a,b,c)   dflash_reeSetValue(a,b,c)
//#define ree_setArray(a,b,c,d) dflash_reeSetArray(a,b,c,d)
//#define ee_getStatus          dflash_eeGetStatus
#endif

// PRQA S 5000 --

//**************************************************************************************************


#undef _DFLASH_FUNCMAPEEP_D    // reseting definition, prevents double definition of a variable if
                               // includes are nested
#endif  // _DFLASH_FUNCMAPEEP_H_D

// EOF #############################################################################################
