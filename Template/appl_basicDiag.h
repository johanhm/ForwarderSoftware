/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        appl_basicDiag.h
*
*  \brief       Interface for appl_basicDiag.c
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 4742 $
*                            $Date: 2012-09-17 15:24:36 +0200 (Mo, 17 Sep 2012) $
*                            $Author: oub2si $
*
* REVISION HISTORY:
*
*
***************************************************************************************************/

#ifndef _APPL_BASICDIAG_H_D
#define _APPL_BASICDIAG_H_D

#ifdef _APPL_BASICDIAG_D
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif

/**** include files ********************************************************************************
* List of include files needed in this module. DON’T INCLUDE HEADER FILES WITH VARIABLE            *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

/**** defines **************************************************************************************
* List of defines needed in this header file and defines to be made available to other modules.   */

/**** typdefs/structures ***************************************************************************
* Typedefs/structures to be made available to other modules.                                      */

/**** public data **********************************************************************************
* Declarations of variables to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */

/**** public functions *****************************************************************************
* Declarations of functions to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */

SCOPE_D void basicDiag_initComm(uint8 canChnl_u8, uint16 rxDatabox_u16, uint8 ecuAddr_u8,
                                uint8 toolAddr_u8, uint8 priority_u8, uint8 cycleTime_u8);
SCOPE_D void basicDiag_setProcessVar(uint8 procIdx_u8, sint32 value_s32);


/**************************************************************************************************/

#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _APPL_BASICDIAG_D

#endif

