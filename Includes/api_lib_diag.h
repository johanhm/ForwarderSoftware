/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        api_lib_diag.h
*
*  \brief       Summarisation of public defines of API library DIAG.
*               Application has to include only this file if this library should be used.
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   API RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 2237 $
*                            $Date: 2009-12-17 10:45:34 +0100 (Do, 17 Dez 2009) $
*                            $Author: gtg2si $
*
* REVISION HISTORY:
*
***************************************************************************************************/

#ifndef _API_LIB_DIAG_H_D       /* replace it with the filename in capital letters */
#define _API_LIB_DIAG_H_D       /* replace it with the filename in capital letters */

/**** include files *******************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

#include "dia_constants.h"
#include "dia_channels.h"
#include "api_diagnostic.h"
#include "dst_main.h"
#include "dst_parastructure.h"
#include "dst_procstructure.h"
#include "dst_applErrors.h"
#include "dst_listentries.h"
#include "dst_ecuLanguage.h"
#include "dst_unitCodes.h"
#include "dst_funcParams.h"
#include "dst_passwords.h"

#ifdef _API_LIB_DIAG_D      /* replace it with the filename in capital letters */
  #define SCOPE_D
#else
  #define SCOPE_D extern
#endif

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
/**************************************************************************************************/


#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _API_LIB_DIAG_D

#endif // _API_LIB_DIAG_H_D

/* EOF ########################################################################################## */
