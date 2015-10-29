/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        mo_defs.h
*
*  \brief       Definitions of module mo.
* Only defines!
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   API RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 5850 $
*                            $Date: 2013-05-21 13:28:54 +0200 (Di, 21 Mai 2013) $
*                            $Author: rolaacke $
*
* REVISION HISTORY:
*
***************************************************************************************************/

#ifndef _MO_DEFS_H_D       /* replace it with the filename in capital letters */
#define _MO_DEFS_H_D       /* replace it with the filename in capital letters */

/**** include files *******************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */


/*** include files *********************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */


//*** defines **************************************************************************************

// PRQA S 5000 ++
//--- check on/off
#define MO_CHECK_ON    0xA55A5AA5U
#define MO_CHECK_OFF   0x5AA5AA5AU

//--- identifiers of hardware monitor checks
#define MO_VSS_1   0x00000001U
#define MO_VSS_2   0x00000002U
#define MO_VSS_3   0x00000003U
#define MO_VSS_4   0x00000004U


// number of TDOH classes which are saved in EEPROM
#define MO_TDOH_NUM_CLASSES_SAVED  7

// number of TDOH classes
#define MO_TDOH_NUM_CLASSES  (MO_TDOH_NUM_CLASSES_SAVED + 1)

//--- array index of TDOH data returned by mo_getTdoh()
// class 1: temperatur .. < 45 degree C
#define MO_TDOH_INDEX_CLASS_1        0
#define MO_TDOH_INDEX_TEMP_LOW_45    MO_TDOH_INDEX_CLASS_1

// class 2: temperatur  45 =< .. < 55 degree C
#define MO_TDOH_INDEX_CLASS_2        1
#define MO_TDOH_INDEX_TEMP_45_55     MO_TDOH_INDEX_CLASS_2

// class 3: temperatur  55 =< .. < 65 degree C
#define MO_TDOH_INDEX_CLASS_3        2
#define MO_TDOH_INDEX_TEMP_55_65     MO_TDOH_INDEX_CLASS_3

// class 4: temperatur  65 =< .. < 75 degree C
#define MO_TDOH_INDEX_CLASS_4        3
#define MO_TDOH_INDEX_TEMP_65_75     MO_TDOH_INDEX_CLASS_4

// class 5: temperatur  75 =< .. < 85 degree C
#define MO_TDOH_INDEX_CLASS_5        4
#define MO_TDOH_INDEX_TEMP_75_85     MO_TDOH_INDEX_CLASS_5

// class 6: temperatur  85 =< .. < 95 degree C
#define MO_TDOH_INDEX_CLASS_6        5
#define MO_TDOH_INDEX_TEMP_85_95     MO_TDOH_INDEX_CLASS_6

// class 7: temperatur  95 =< .. < 105 degree C
#define MO_TDOH_INDEX_CLASS_7        6
#define MO_TDOH_INDEX_TEMP_95_105    MO_TDOH_INDEX_CLASS_7

// class 8: temperatur  105 =< .. degree C
#define MO_TDOH_INDEX_CLASS_8        7
#define MO_TDOH_INDEX_TEMP_105_HIGH  MO_TDOH_INDEX_CLASS_8

// PRQA S 5000 --

//*** typdefs/structures ***************************************************************************

#endif  /* _MO_DEFS_H_D */

/* EOF ########################################################################################## */
