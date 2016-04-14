//**************************************************************************************************
//
//  FILENAME: toolversion.h
//
//  DESCRIPTION:
//! \file    toolversion.h
//! \brief   check using fo  correct compiler tool version
//
// This file generates a compiler warning if the defined version is not used.
// This file must be included by a  public header, which is to be used by the application programm.
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_Plattform
//                            Hardware: RC30
//
// FILE VERSION INFORMATION:  $Revision: 2853 $
//                            $Date: 2010-07-22 09:45:21 +0200 (Do, 22 Jul 2010) $
//                            $Author: roe2si $
//
// REVISION HISTORY: 
// see history log of version management system
//
//**************************************************************************************************

#if (__TOOL_VERSION__ != 210 )
   #warning The actual running HighTec Tool Version differs from version which was used for creating \
and testing C-API. The Tool Version 2.10 is comming with the TriCore Development Platform Release 3.4.6. \
If using a different version unexpected behavior might happen.
#endif 

// EOF #############################################################################################
