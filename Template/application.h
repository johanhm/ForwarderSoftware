/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        application.h
*
*  \brief       Interface for application.c
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 2911 $
*                            $Date: 2010-08-30 17:57:10 +0200 (Mo, 30 Aug 2010) $
*                            $Author: gtg2si $
*
* REVISION HISTORY:
*
*
***************************************************************************************************/

#ifndef _APPLICATION_H_  /* replace it with the filename in capital letters */
#define _APPLICATION_H_  /* replace it with the filename in capital letters */


/**** include files ********************************************************************************
* List of include files needed in this module. DON’T INCLUDE HEADER FILES WITH VARIABLE            *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

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
void sys_main(void);

/**************************************************************************************************/


/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _APPLICATION_H_

#endif // _APPLICATION_H_

/* EOF ########################################################################################## */
