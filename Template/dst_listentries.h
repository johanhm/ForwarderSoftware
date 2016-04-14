//**************************************************************************************************
//
//  FILENAME:    dst_listentries.h
//
//  DESCRIPTION:
//! \file        dst_listentries.h
//! \brief       error structure
//!
//
// *************************************************************************************************
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC36-20/30
//
// FILE VERSION INFORMATION:  $Revision: 5232 $
//                            $Date: 2013-01-23 10:29:06 +0100 (Mi, 23 Jan 2013) $
//                            $Author: gtg2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _dst_listentries_h_D
#define _dst_listentries_h_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"           // standard type definitions
#include "dst_main.h"


//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.

//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.

// first index means the list index, second index means the list entry index
const HUGE ParaListEntry_ts ParaLists_as[][MaxNumberOfListEntries_DU8] =
{
   // **********************************************************************************************
   // ParaList0 - brief description
   // **********************************************************************************************

   {
      // *******************************************************************************************
      // ParaList0 - Entry0
      // *******************************************************************************************
      {  /****|****|****|****|****|****|**/
         {
           "", // language 1
           "", // language 2
           "", // language 3
           "", // language 4
         }
      },
   },
};

// create pointer to this structure for diagnosis module
const HUGE ParaListEntry_ts * ParaLists_ps = (const HUGE ParaListEntry_ts *)ParaLists_as;
// get the maximum count of list entries in one list for diagnosis module
const uint8 MaxNumberOfListEntries_cu8     = (uint8)(sizeof(ParaLists_as[0]) /
                                                     sizeof(ParaLists_as[0][0]));

//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.


//**************************************************************************************************

#endif  // _dst_listentries_h_D

// EOF #############################################################################################
