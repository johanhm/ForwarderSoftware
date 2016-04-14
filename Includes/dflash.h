//**************************************************************************************************
//
//  FILENAME:    dflash.h
//
//  DESCRIPTION:
///! \brief       Interface for dflash.c
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_Plattform
//
// FILE VERSION INFORMATION:  $Revision: 3819 $
//                            $Date: 2011-09-21 10:57:30 +0200 (Mi, 21 Sep 2011) $
//                            $Author: gtg2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _DFLASH_H_D
  #define _DFLASH_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.


#ifdef _DFLASH_D
  #define SCOPE_D
#else
  #define SCOPE_D extern
#endif   // _DFLASH_D

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

/*** Definition of the error locations/codes of DFlash module *************************************/

//--- internal block read errors
/* There is a failure in reading data (checksum error), replacement values are given.
  <error parameter> = block number
*/
#define DFLASHERR_RDBLOCK_REPLVALUES_DU16     (DFLASH_DU16 | 0x01)

/* There is a failure in reading data (checksum error), history values are given.
  <error parameter> = block number
*/
#define DFLASHERR_RDBLOCK_HISTVALUES_DU16     (DFLASH_DU16 | 0x02)

/* There is a failure in reading data (checksum error), inconsistent data will be given
   if no replacement values defined.
  <error parameter> = block number
*/
#define DFLASHERR_RDBLOCK_INVALIDVALUES_DU16  (DFLASH_DU16 | 0x03)

/* An internal error occurs, the order is aborted.
  <error parameter> = block number
*/
#define DFLASHERR_RDBLOCK_ABORTED_DU16        (DFLASH_DU16 | 0x04)

/*--- ee_saveSysValue_s16()
   <error parameter> = number of parameter
                       0xFF: buffer (queue) overflow of eeprom server
*/
#define DFLASH_EESAVESYSVALUE_DU16     (DFLASH_DU16 | 0x0A)

/*--- ee_saveSysArray_s16()
   <error parameter> = number of parameter
                       0xFF: buffer (queue) overflow of eeprom server
*/
#define DFLASH_EESAVESYSARRAY_DU16     (DFLASH_DU16 | 0x0B)

/*--- ee_saveSysPage_s16()
   <error parameter> = number of parameter
                       0xFF: buffer (queue) overflow of eeprom server
*/
#define DFLASH_EESAVESYSPAGE_DU16      (DFLASH_DU16 | 0x0C)

/*--- ree_setSysValue()
   <error parameter> = number of parameter
*/
#define DFLASH_REESETSYSVALUE_DU16     (DFLASH_DU16 | 0x0D)

/*--- ree_setSysArray()
   <error parameter> = number of parameter
*/
#define DFLASH_REESETSYSARRAY_DU16     (DFLASH_DU16 | 0x0E)

/*--- ee_saveValue()
   <error parameter> = number of parameter
                       0xFF: buffer (queue) overflow of eeprom server
*/
#define DFLASH_EESAVEVALUE_DU16        (DFLASH_DU16 | 0x0F)

/*--- ee_saveArray()
   <error parameter> = number of parameter
                       0xFF: buffer (queue) overflow of eeprom server
*/
#define DFLASH_EESAVEARRAY_DU16        (DFLASH_DU16 | 0x10)

/*--- ee_savePage()
   <error parameter> = number of parameter
                       0xFF: buffer (queue) overflow of eeprom server
*/
#define DFLASH_EESAVEPAGE_DU16         (DFLASH_DU16 | 0x11)

/*--- ree_setValue()
   <error parameter> = number of parameter
*/
#define DFLASH_REESETVALUE_DU16        (DFLASH_DU16 | 0x12)

/*--- ree_setArray()
   <error parameter> = number of parameter
*/
#define DFLASH_REESETARRAY_DU16        (DFLASH_DU16 | 0x13)

/*--- ree_getValue()
   <error parameter> = number of parameter
*/
#define DFLASH_REEGETVALUE_DU16        (DFLASH_DU16 | 0x14)

/*--- ree_getArray()
   <error parameter> = number of parameter
*/
#define DFLASH_REEGETARRAY_DU16        (DFLASH_DU16 | 0x15)

/*--- eeprom server
   write error, order is aborted (could not finished successfully).
   <error parameter> =
   0 : Eep_Write return value = EEP_WRITE_E_WRG_PARAM :
                                                    The given parameter list of Eep_Write is wrong.
   1 : Eep_Write order status returned: EEP_ORDSTAT_E_ABORTED:
                                                     An internal error occurs, the order is aborted.
*/
#define DFLASH_EESERV_WRITE_DU16       (DFLASH_DU16 | 0x16)

/*--- dflash_eeSaveBlock()
  <error parameter> = number of parameter
                      0xFF: buffer (queue) overflow of eeprom server
*/
#define DFLASH_EESAVEBLOCK_DU16        (DFLASH_DU16 | 0x17)

/*--- dflash_eeSaveSysBlock()
  <error parameter> = number of parameter
                      0xFF: buffer (queue) overflow of eeprom server
*/
#define DFLASH_EESAVESYSBLOCK_DU16     (DFLASH_DU16 | 0x18)

#undef SCOPE_D

#undef _DFLASH_D             // reseting definition, prevents double definition of a variable if
                             // includes are nested
#endif  // _DFLASH_H_D

// EOF #############################################################################################
