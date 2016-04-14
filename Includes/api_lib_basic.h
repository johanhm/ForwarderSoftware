/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        api_lib_basic.h
*
*  \brief       Summarisation of public defines of API library basic.
*               Application has to include only this file if this library should be used.
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   API RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 5321 $
*                            $Date: 2013-02-06 15:36:57 +0100 (Mi, 06 Feb 2013) $
*                            $Author: gtg2si $
*
* REVISION HISTORY:
*
***************************************************************************************************/

#ifndef _API_LIB_BASIC_H_D      /* replace it with the filename in capital letters */
#define _API_LIB_BASIC_H_D      /* replace it with the filename in capital letters */

/**** include files *******************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

#include "common_api.h"
#include "cpu_inl_api.h"
#include "phase.h"

// *** can
#include "can_api.h"
#include "can_api_cfgEasy.h"

// *** common_include
#include "channels_comdef.h"
#include "numbers.h"
#include "types.h"

#include "channels.h"

// *** dflash
#include "api_dflash.h"

// *** emcy
#include "emcy_api.h"

// *** in
#include "in.h"
#include "dfi.h"

// *** main
#include "asw_version_info.h"

// *** mo
#include "mo_system.h"
#include "mo_defs.h"

// *** out
#include "out.h"

// *** safout
#include "safout.h"

// sys
#include "system.h"
#include "toolversion.h"    /* checking required compiler version, do not delete */

#endif // _API_LIB_BASIC_H_D

/* EOF ########################################################################################## */
