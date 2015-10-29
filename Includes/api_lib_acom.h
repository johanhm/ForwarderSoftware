/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        api_lib_com.h
*
*  \brief       Summarisation of public defines of API library ACOM.
*               Application has to include only this file if this library should be used.
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   API RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 3395 $
*                            $Date: 2011-03-16 16:22:22 +0100 (Mi, 16 Mrz 2011) $
*                            $Author: gtg2si $
*
* REVISION HISTORY:
*
***************************************************************************************************/

#ifndef _API_LIB_ACOM_H_D      /* replace it with the filename in capital letters */
#define _API_LIB_ACOM_H_D      /* replace it with the filename in capital letters */

/**** include files *******************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

#include "acom.h"

#ifdef _API_LIB_ACOM_D     /* replace it with the filename in capital letters */
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
#undef _API_LIB_ACOM_D

#endif // _API_LIB_ACOM_H_D

/* EOF ########################################################################################## */
