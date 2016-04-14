/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        rtm_api.h
*
*  \brief       Header file for the run time measuring system.
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   API RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 5232 $
*                            $Date: 2013-01-23 10:29:06 +0100 (Mi, 23 Jan 2013) $
*                            $Author: gtg2si $
*
* REVISION HISTORY:
*
***************************************************************************************************/

#ifndef _RTM_API_H_D
#define _RTM_API_H_D


/**** include files ********************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

#ifdef _RTM_API_D    /* replace it with the filename in capital letters */
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   /* _RTM_API_D */

#include "common_api.h"

/**** defines **************************************************************************************
* List of defines needed in this header file and defines to be made available to other modules.   */

#define RTM_AUTOCALC_ENDADDRESS_DU32  0

// defines for measurement type gross (inclusive interruptions) or net (exclusiv interruptions)
#define RTM_TYPE_INCL_DU16            0x0000  // gross (brutto)
#define RTM_TYPE_EXCL_DU16            0x0001  // net (netto)

#define RTM_UNIT_MASK_DU16            0x0F00
#define RTM_UNIT_US_DU16              0x0000
#define RTM_UNIT_TICKS_DU16           0x0100
#define RTM_UNIT_CYCLES_DU16          0x0200

#define RTM_MIN_RUNTIME_DU16          0x0001
#define RTM_MAX_RUNTIME_DU16          0x0002
#define RTM_AVG_RUNTIME_DU16          0x0004
#define RTM_LAST_RUNTIME_DU16         0x0008
#define RTM_MIN_INTERVAL_DU16         0x0011
#define RTM_MAX_INTERVAL_DU16         0x0012
#define RTM_AVG_INTERVAL_DU16         0x0014
#define RTM_LAST_INTERVAL_DU16        0x0018

#define RTM_MIN_RUNTIME_US_DU16       (RTM_MIN_RUNTIME_DU16   | RTM_UNIT_US_DU16)
#define RTM_MAX_RUNTIME_US_DU16       (RTM_MAX_RUNTIME_DU16   | RTM_UNIT_US_DU16)
#define RTM_AVG_RUNTIME_US_DU16       (RTM_AVG_RUNTIME_DU16   | RTM_UNIT_US_DU16)
#define RTM_LAST_RUNTIME_US_DU16      (RTM_LAST_RUNTIME_DU16  | RTM_UNIT_US_DU16)
#define RTM_MIN_INTERVAL_US_DU16      (RTM_MIN_INTERVAL_DU16  | RTM_UNIT_US_DU16)
#define RTM_MAX_INTERVAL_US_DU16      (RTM_MAX_INTERVAL_DU16  | RTM_UNIT_US_DU16)
#define RTM_AVG_INTERVAL_US_DU16      (RTM_AVG_INTERVAL_DU16  | RTM_UNIT_US_DU16)
#define RTM_LAST_INTERVAL_US_DU16     (RTM_LAST_INTERVAL_DU16 | RTM_UNIT_US_DU16)

#define RTM_MIN_RUNTIME_TICKS_DU16    (RTM_MIN_RUNTIME_DU16   | RTM_UNIT_TICKS_DU16)
#define RTM_MAX_RUNTIME_TICKS_DU16    (RTM_MAX_RUNTIME_DU16   | RTM_UNIT_TICKS_DU16)
#define RTM_AVG_RUNTIME_TICKS_DU16    (RTM_AVG_RUNTIME_DU16   | RTM_UNIT_TICKS_DU16)
#define RTM_LAST_RUNTIME_TICKS_DU16   (RTM_LAST_RUNTIME_DU16  | RTM_UNIT_TICKS_DU16)
#define RTM_MIN_INTERVAL_TICKS_DU16   (RTM_MIN_INTERVAL_DU16  | RTM_UNIT_TICKS_DU16)
#define RTM_MAX_INTERVAL_TICKS_DU16   (RTM_MAX_INTERVAL_DU16  | RTM_UNIT_TICKS_DU16)
#define RTM_AVG_INTERVAL_TICKS_DU16   (RTM_AVG_INTERVAL_DU16  | RTM_UNIT_TICKS_DU16)
#define RTM_LAST_INTERVAL_TICKS_DU16  (RTM_LAST_INTERVAL_DU16 | RTM_UNIT_TICKS_DU16)

#define RTM_NBR_MEAS_CYCLES_DU16      RTM_UNIT_CYCLES_DU16

// function return codes
#define RTM_RETCODE_INV_PAR1_DS32     ((sint32)-1)
#define RTM_RETCODE_NO_RESULT_DS32    ((sint32)-2)
#define RTM_RETCODE_OVERFLOW_DS32     ((sint32)-3)


/**** typdefs/structures ***************************************************************************
* Typedefs/structures to be made available to other modules.                                      */


/**** public data **********************************************************************************
* Declarations of variables to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */


/**** public functions *****************************************************************************
* Declarations of functions to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */

SCOPE_D void rtm_startRunTimeMeas(uint32 startAddress_u32,
                                  uint32 endAddress_u32,
                                  uint16 measureType_u16);

SCOPE_D void rtm_stopRunTimeMeas(void);

SCOPE_D sint32 rtm_getRunTime(uint16 resultType_u16);

/**************************************************************************************************/

#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _RTM_API_D

#endif // _RTM_API_H_D

/* EOF ########################################################################################## */

