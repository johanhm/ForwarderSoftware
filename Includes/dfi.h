/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        dfi.h
*
*  \brief       Interface for dfi.c
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 5321 $
*                            $Date: 2013-02-06 15:36:57 +0100 (Mi, 06 Feb 2013) $
*                            $Author: gtg2si $
*
* REVISION HISTORY:
*
*
***************************************************************************************************/

#ifndef _DFI_H_D      /* replace it with the filename in capital letters */
#define _DFI_H_D      /* replace it with the filename in capital letters */

/**** include files ********************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

#include "phase.h"


#ifdef _DFI_D     /* replace it with the filename in capital letters */
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   /* _DFI_D */

/**** defines **************************************************************************************
* List of defines needed in this header file and defines to be made available to other modules.   */


/**** typdefs/structures ***************************************************************************
* Typedefs/structures to be made available to other modules.                                      */

/*
 * Structure of buffer info for API. The buffer itself is located API-external. The application
 * has to declare the buffer
 */
typedef struct in_freqAcqCopyBufInfo_t
{
  uint8 lengthCopyBuf_u8;       /* length of copy buffer */
  in_freqAcq_ts *start_pas;     /* pointer to copy buffer */

  uint8 length_u8;              /* actual length of buffer */
  uint8 index_u8;               /* actual index of buffer (corresponding to the write pointer) */
  bool  full_l;                 /* This flag shows if the buffer is completly filled
                                 * FALSE: until now the buffer is not full
                                 * TRUE : buffer is full */
  uint16 counter_u16;           /* This counter will be incremented if a new period is saved into
                                   the acquisition buffer.
                                   It has a wrap around capability.
                                   The counter is set to zero if a zero frequency
                                   (period > max. period) was detected. */
} in_freqAcqCopyBufInfo_ts;


/**** public functions *****************************************************************************
* Declarations of functions to be made available to other modules. Use SCOPE_D in front of each    *
* line.                                                                                           */
#ifdef NUM_CHANNEL_FREQ_ACQ
#if (NUM_CHANNEL_FREQ_ACQ != 0)
SCOPE_D uint16 in_registerFreqAcqBuf(uint8 chnl_u8,
                                     in_freqAcq_ts *buf_pas,
                                     uint8 numFreqAcq_u8);

SCOPE_D uint16 in_registerFreqAcqCopyBuf(in_freqAcqCopyBufInfo_ts *in_freqAcqCopyBufInfo_ps,
                                         in_freqAcq_ts *buf_pas,
                                         uint8 numFreqAcq_u8);

SCOPE_D uint16 in_getFreqAcq(uint8 chnl_u8,
                             in_freqAcqCopyBufInfo_ts *in_freqAcqCopyBufInfo_ps);
#endif
#endif

#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _DFI_D

#endif // DFI_H_D
