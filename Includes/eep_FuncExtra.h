/***************************************************************************************************
*
*  FILENAME:                                                                                      */
/**\file                        eep_FuncExtra.h
*
*  \brief                       Header file for EEPROM C-API extra functions.
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

#ifndef _EEP_FUNCEXTRA_H_D
#define _EEP_FUNCEXTRA_H_D


/**** include files ********************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

#include "common_api.h"

#ifdef _EEP_FUNCEXTRA_D
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif  /* _EEP_FUNCEXTRA_D */

/**** defines **************************************************************************************
* List of defines needed in this header file and defines to be made available to other modules.   */


/**** public data **********************************************************************************
* Declarations of variables to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */


/**** public functions *****************************************************************************
* Declarations of functions to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */
SCOPE_D uint16 ee_saveApplVar(uint16 adrEep_u16, sint8 *adrVar_ps8, uint16 lenVar_u16);
SCOPE_D uint16 ree_getApplVar(uint16 adrEep_u16, sint8 *adrVar_ps8, uint16 lenVar_u16);

/**************************************************************************************************/

#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _EEP_FUNCEXTRA_D

#endif  /* _EEP_FUNCEXTRA_H_D */


/* EOF ###########################################################################################*/
