//**************************************************************************************************
//
//  FILENAME: asw_version_info.h
//
//  DESCRIPTION:
//! \file    asw_version_info.h
//! \brief   definitions used to create version infomation inside the Application SoftWare image
//
// There is not asw version for this ECU. But this file is needed because of platform compatibility.
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_Plattform
//                            Hardware: RC30-00D6
//
// FILE VERSION INFORMATION:  $Revision: 2917 $
//                            $Date: 2010-08-31 14:06:18 +0200 (Di, 31 Aug 2010) $
//                            $Author: gtg2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _ASW_VERSION_INFO_H_D
#define _ASW_VERSION_INFO_H_D

#ifdef _ASW_VERSION_INFO_D
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   /* _ASW_VERSION_INFO_D */


//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.


//*** typedefs/ structures *************************************************************************
// typedefs/ structures to be made available to other modules.


//**************************************************************************************************

#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _ASW_VERSION_INFO_D

#endif // _ASW_VERSION_INFO_H_D

// EOF #############################################################################################
