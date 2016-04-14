/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        intr_defs.h
*
*  \brief       Defines for intr.cfg.
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   RC30 platform
*                            Hardware: RC30-00D6
*
* FILE VERSION INFORMATION:  $Revision: 3067 $
*                            $Date: 2010-10-18 16:28:45 +0200 (Mo, 18 Okt 2010) $
*                            $Author: gtg2si $
*
* REVISION HISTORY:
*
***************************************************************************************************/

#ifndef _INTR_DEFS_H_D
#define _INTR_DEFS_H_D


//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

// This priority is used to have a protected access to global variables (disable nested interrups).
#define SYS_CRITSECT_USER_PRIO_DU8            11


//*** typedefs/ structures *************************************************************************
// typedefs/ structures to be made available to other modules.


//**************************************************************************************************


#endif // _INTR_DEFS_H_D

// EOF #############################################################################################
