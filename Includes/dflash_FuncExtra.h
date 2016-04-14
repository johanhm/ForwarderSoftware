/***************************************************************************************************
*
*  FILENAME:                                                                                      */
/**\file                    dflash_FuncExtra.c
*
*  \brief                   DFLASH C-API extra functions.
*
*  Extra C-API functions for an easily (comfortably) DFLASH access.
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

#ifndef _DFLASH_FUNCEXTRA_H_D
#define _DFLASH_FUNCEXTRA_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.

#include "common_api.h"

#ifdef _DFLASH_FUNCEXTRA_D
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif  /* _DFLASH_FUNCEXTRA_D */

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.


//**************************************************************************************************


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.


//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.
SCOPE_D uint16 dflash_reeGetApplVar(uint16 adrEep_u16, sint8 *adrVar_ps8, uint16 lenVar_u16);
SCOPE_D uint16 dflash_eeSaveApplVar(uint16 adrEep_u16, sint8 *adrVar_ps8, uint16 lenVar_u16);

#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _DFLASH_FUNCEXTRA_D

#endif  /* _DFLASH_FUNCEXTRA_H_D */

// EOF #############################################################################################
