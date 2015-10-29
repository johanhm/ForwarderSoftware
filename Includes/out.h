/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        out.h
*
*  \brief       Interface for out.c.
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 5862 $
*                            $Date: 2013-05-27 16:40:45 +0200 (Mo, 27 Mai 2013) $
*                            $Author: ltm2si $
*
* REVISION HISTORY:
*
*
***************************************************************************************************/

#ifndef _OUT_H_D     /* replace it with the filename in capital letters */
#define _OUT_H_D     /* replace it with the filename in capital letters */

/**** include files ********************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */
#include "common_api.h"


#ifdef _OUT_D        /* replace it with the filename in capital letters */
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   /* _OUT_D */


/**** defines **************************************************************************************
* List of defines needed in this header file and defines to be made available to other modules.   */

/* possible dither frequency values */
#define fDither_0Hz_DU8               0u
#define fDither_83Hz_DU8              83u
#define fDither_90Hz_DU8              90u
#define fDither_100Hz_DU8             100u
#define fDither_111Hz_DU8             111u
#define fDither_125Hz_DU8             125u
#define fDither_142Hz_DU8             142u
#define fDither_166Hz_DU8             166u
#define fDither_200Hz_DU8             200u
#define fDither_250Hz_DU8             250u

/* possible period respective frequency values [125us] */
#define tiPeriod_1ms_DU16               8u  /* period from 1ms is necessary for the dither  */
#define tiPeriod_2ms_DU16              16u  /* period from 2ms is necessary for the dither  */
#define tiPeriod_4ms_DU16              32u
#define tiPeriod_5ms_DU16              40u
#define tiPeriod_6ms_DU16              48u
#define tiPeriod_7ms_DU16              56u
#define tiPeriod_8ms_DU16              64u
#define tiPeriod_9ms_DU16              72u
#define tiPeriod_10ms_DU16             80u
#define tiPeriod_11ms_DU16             88u
#define tiPeriod_12ms_DU16             96u
#define tiPeriod_13ms_DU16            104u
#define tiPeriod_14ms_DU16            112u
#define tiPeriod_15ms_DU16            120u
#define tiPeriod_16ms_DU16            128u
#define tiPeriod_17ms_DU16            136u
#define tiPeriod_18ms_DU16            144u
#define tiPeriod_19ms_DU16            152u
#define tiPeriod_20ms_DU16            160u

#define f_1000Hz_DU16                 tiPeriod_1ms_DU16
#define f_500Hz_DU16                  tiPeriod_2ms_DU16
#define f_250Hz_DU16                  tiPeriod_4ms_DU16
#define f_200Hz_DU16                  tiPeriod_5ms_DU16
#define f_166Hz_DU16                  tiPeriod_6ms_DU16
#define f_143Hz_DU16                  tiPeriod_7ms_DU16
#define f_125Hz_DU16                  tiPeriod_8ms_DU16
#define f_111Hz_DU16                  tiPeriod_9ms_DU16
#define f_100Hz_DU16                  tiPeriod_10ms_DU16
#define f_91Hz_DU16                   tiPeriod_11ms_DU16
#define f_83Hz_DU16                   tiPeriod_12ms_DU16
#define f_77Hz_DU16                   tiPeriod_13ms_DU16
#define f_71Hz_DU16                   tiPeriod_14ms_DU16
#define f_67Hz_DU16                   tiPeriod_15ms_DU16
#define f_63Hz_DU16                   tiPeriod_16ms_DU16
#define f_59Hz_DU16                   tiPeriod_17ms_DU16
#define f_56Hz_DU16                   tiPeriod_18ms_DU16
#define f_53Hz_DU16                   tiPeriod_19ms_DU16
#define f_50Hz_DU16                   tiPeriod_20ms_DU16

#define out_tiMinDiagDebounce_DU16    50u
#define out_tiMaxDiagDebounce_DU16    250u

/**** typdefs/structures ***************************************************************************
* Typedefs/structures to be made available to other modules.                                      */

/**** public data **********************************************************************************
* Declarations of variables to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */

/**** public functions *****************************************************************************
* Declarations of functions to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */

SCOPE_D void out(uint32 chnl_u32, uint16 value_u16);
SCOPE_D void out_cfgxt (uint32 chnl_u32,
                        uint16 tiDiagDebounce_u16,
                        uint16 freq_u16,
                        uint32 rMinLoad_u32,
                        uint32 rMaxLoad_u32,
                        uint16 iDeviation_u16);

SCOPE_D void out_cfgDither (uint32 chnl_u32, uint8 freq_u8, uint16 ampl_u16);
SCOPE_D void out_cfgPI (uint32 chnl_u32, uint16 kp_u16, uint16 ki_u16);
SCOPE_D void out_resetError (uint32 chnl_u32);

SCOPE_D uint8 out_getStatusxt(uint32 chnl_u32, out_ts *out_ps);

SCOPE_D uint16 out_cfgPulse (uint32 chnl_u32,
                             uint8 numPulse_u8,
                             uint8 numDecPulse_u8);

SCOPE_D uint16 out_cfgSlopext (uint32 chnl_u32,
                               uint16 iSlope_u16,
                               uint8 numSlope_u8,
                               uint8 numDecSlope_u8);

SCOPE_D uint16 out_setPullup(uint8 group_u8, bool state_l);

// PRQA S 5000 ++
// API functions
#define out_getStatus(CHNL_U32)               out_getStatusxt(CHNL_U32, (NULL))
#define out_cfgSlope(CHNL_U32, SLOPE_U16)     out_cfgSlopext(CHNL_U32, SLOPE_U16,(NULL), (NULL))

#define out_cfg(CHNL_U32, TI_DIAG_U16, FREQ_U16, RMIN_U32, RMAX_U32)\
        out_cfgxt(CHNL_U32, TI_DIAG_U16, FREQ_U16, RMIN_U32, RMAX_U32, (NULL))

/* redefines from the function names */
#define out_getState(CHNL_U32)                out_getStatusxt(CHNL_U32, (NULL))
#define out_getStatext(CHNL_U32, OUT_PS)      out_getStatusxt(CHNL_U32, OUT_PS)
// PRQA S 5000 --

/* prototypes for hidden functions */
/* extern declaration due to the handling from the functions in po.c -> avoids OAC errors */

#ifdef POH_VNDD_NUM_DU8
#if POH_VNDD_NUM_DU8 != 0
extern void out_setImmediate_POH_VNDD (uint32 chnl_u32, bool immediate_l);
#endif
#endif

#ifdef POH_VNDD_CS_NUM_DU8
#if POH_VNDD_CS_NUM_DU8 != 0
extern void out_setImmediate_POH_VNDD_CS (uint32 chnl_u32, bool immediate_l);
#endif
#endif

#ifdef POL_NUM_DU8
#if POL_NUM_DU8 != 0
extern void out_setImmediate_POL (uint32 chnl_u32, bool immediate_l);
#endif
#endif

#ifdef POL_EHR_NUM_DU8
#if POL_EHR_NUM_DU8 != 0
extern void out_setImmediate_POL_EHR (uint32 chnl_u32, bool immediate_l);
#endif
#endif


/**************************************************************************************************/



#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _OUT_D

#endif  /* _OUT_H_D */

/* EOF ###########################################################################################*/
