/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        mo_system.h
*
*  \brief       Interface (public) for mo_system.c
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

#ifndef _MO_SYSTEM_H_D   /* replace it with the filename in capital letters */
#define _MO_SYSTEM_H_D   /* replace it with the filename in capital letters */

/**** include files ********************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */
#include "common_api.h"

#ifdef _MO_SYSTEM_D     /* replace it with the filename in capital letters */
  #define SCOPE_D
#else
  #define SCOPE_D extern
#endif   /* _MO_SYSTEM_D */


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
SCOPE_D uint16 mo_getError(void);
SCOPE_D void   mo_resetErrorReply(void);
SCOPE_D void   mo_ignoreError(void);
SCOPE_D void   mo_cfgCheck(uint32 check_u32, uint32 state_u32);

/**************************************************************************************************/

#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _MO_SYSTEM_D

#endif /* _MO_SYSTEM_H_D */

/* EOF ########################################################################################## */
