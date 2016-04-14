/***************************************************************************************************
*
*  FILENAME:                                                                                      */
/**\file                        eep_Func.h
*
*  \brief                       Header file for EEPROM C-API functions.
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                      API RC30 platform
*
* FILE VERSION INFORMATION:     $Revision: 5232 $
*                               $Date: 2013-01-23 10:29:06 +0100 (Mi, 23 Jan 2013) $
*                               $Author: gtg2si $
*
* REVISION HISTORY:
*
***************************************************************************************************/

#ifndef _EEP_FUNC_H_D
#define _EEP_FUNC_H_D


/**** include files ********************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

#include "common_api.h"

#ifdef _EEP_FUNC_D
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif  /* _EEP_FUNC_D */

/**** defines **************************************************************************************
* List of defines needed in this header file and defines to be made available to other modules.   */


/**** public data **********************************************************************************
* Declarations of variables to be made available to other modules. Use SCOPE in front of each      *
* line.                  */


/**** public functions *****************************************************************************
* Declarations of functions to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */
SCOPE_D sint16 ee_saveValue(sint16 page_s16, sint16 index_s16, sint16 val_s16);
SCOPE_D sint16 ee_saveArray(sint16 page_s16, sint16 index_s16, sint16 *data_ps16, sint16 len_s16);
SCOPE_D sint16 ee_savePage(sint16 page_s16);
SCOPE_D sint16 ree_getValue(sint16 page_s16, sint16 index_s16);
SCOPE_D sint16 ree_getArray(sint16 page_s16, sint16 index_s16, sint16 *data_ps16, sint16 len_s16);
SCOPE_D void ree_setValue(sint16 page_s16, sint16 index_s16, sint16 val_s16);
SCOPE_D void ree_setArray(sint16 page_s16, sint16 index_s16, sint16 *data_ps16, sint16 len_s16);
SCOPE_D sint16 ee_getStatus(void);


/**************************************************************************************************/

#undef SCOPE_D

/* Reseting definition, prevents double definition of a variable if includes are nested. Replace
*  it with the filename in capital letters. */

#undef _EEP_FUNC_D

#endif  /* _EEP_FUNC_H_D */

/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */

/* EOF ###########################################################################################*/
