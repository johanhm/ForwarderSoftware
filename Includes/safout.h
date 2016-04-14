/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        safout.h
*
*  \brief       Interface for safout.h
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 5940 $
*                            $Date: 2013-06-10 09:46:04 +0200 (Mo, 10 Jun 2013) $
*                            $Author: ltm2si $
*
* REVISION HISTORY:
*
*
***************************************************************************************************/

#ifndef _SAFOUT_H_D     /* replace it with the filename in capital letters */
#define _SAFOUT_H_D     /* replace it with the filename in capital letters */

/**** include files ********************************************************************************
* List of include files needed in this module. DONT INCLUDE HEADER FILES WITH VARIABLE             *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */
#include "types.h"
#include "common_api.h"


#ifdef _SAFOUT_D        /* replace it with the filename in capital letters */
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   /* _SAFOUT_D */


/**** defines **************************************************************************************
* List of defines needed in this header file and defines to be made available to other modules.   */

/* status values */
// initialized_DB16                   0x0001u  /* see channels_comdef.h */
// configured_DB16                    0x0002u  /* see channels_comdef.h */
#define limitedAvailability_DB16      0x0004u
#define deactivated_DB16              0x0008u
#define deactivatedHS_1_DB16          0x0010u
#define deactivatedHS_2_DB16          0x0020u
#define deactivatedHS_3_DB16          0x0040u
#define deactivatedHS_4_DB16          0x0080u
#define activeHS_1_DB16               0x0100u
#define activeHS_2_DB16               0x0200u
#define activeHS_3_DB16               0x0400u
#define activeHS_4_DB16               0x0800u
#define toggleToHS_1_DB16             0x1000u
#define toggleToHS_2_DB16             0x2000u
#define pinging_DB16                  0x4000u
#define ignoreError_DB16              0x8000u

#define deactivatedHS_Mask_DB16       0x00F0u
#define activeHS_Mask_DB16            0x0F00u
#define toggleMask_DB16               0x3000u

/* status1 values */
#define testHS2_DB16                  0x0001u   /* test from HS2 in mode POL */

#define configuredHS_1_DB16           deactivatedHS_1_DB16
#define configuredHS_2_DB16           deactivatedHS_2_DB16
#define configuredHS_3_DB16           deactivatedHS_3_DB16
#define configuredHS_4_DB16           deactivatedHS_4_DB16

#define configuredHS_Mask_DB16       deactivatedHS_Mask_DB16

/* diagnosis codes */
#define NOFAILURE_DU16                0x0000u
#define SCGND_HS_DU16                 0x0001u   /* short circuit to GND from a high side output */
#define SCUBAT_HS_DU16                0x0002u   /* short circuit to UBAT from a high side output */
#define SCGND_LS_DU16                 0x0004u   /* short circuit to GND from a low side output */
#define SCUBAT_LS_DU16                0x0008u   /* short circuit to UBAT from a low side output */
#define OL_HS_DU16                    0x0010u   /* difference between HS current sum and current
                                                   setpoint sum */
#define OL_DU16                       0x0020u   /* no current flow through high and low side */
#define SCCOIL_DU16                   0x0040u   /* code is not used => detection is always SCGND or
                                                   SCUBAT */
#define CURRENT_HS_DU16               0x0100u   /* difference between current sum and current
                                                   setpoint sum */
#define INTERN_OL_HS_DU16             0x0200u   /* same as OL_DU16 */
#define INTERN_SC_HS_DU16             0x0400u   /* current sum is higher than current setpoint
                                                   sum in mode POH or current from LS is higher
                                                   than current sum from HS in mode DO */
#define CURRENT_LS_DU16               0x0800u   /* same as CURRENT_HS_DU16 */
#define INTERN_OL_LS_DU16             0x1000u   /* same as OL_DU16 */
#define INTERN_SC_LS_DU16             0x2000u   /* current from HS is and LS is too high in
                                                   mode POL */
#define FAILED_DU16                   0x4000u   /* failed shut down test through an
                                                   internal or external short circuit */
#define TIMEOUT_DU16                  0x8000u   /* current timeout during shut down test */

/* internal status from the shut down test */
#define CURRENT_TIMEOUT_DU8           0x01u
#define CURRENT_TIMEOUT_HS2_DU8       0x02u
#define FAILED_DU8                    0x10u
#define FAILED_HS2_DU8                0x20u
#define EXECUTE_DU8                   0x80u

/* status codes (return value from safout_getStatusxt()) */
#define NO_STATUS_DU16                0x0000u     /* no status existing */
#define LIMITED_AVAILABILITY_DU16     0x0001u     /* at least one output is deactivated */
#define NO_AVAILABILITY_DU16          0x0002u     /* safout channel is deactivated */
#define TOTAL_CURRENT_EXCEEDED_DU16   0x0010u     /* warning that the total current limit
                                                     is exceeded */
#define PINGING_DU16                  0x0020u     /* pinging is activ */
#define SDT_CURRENT_TIMEOUT_DU16      0x0040u     /* no current flow through the shut down switch
                                                     within the time stated */
#define SDT_CURRENT_TIMEOUT_HS2_DU16  0x0080u     /* no current flow through the second shut down
                                                     switch within the time stated (only in mode
                                                     POL with two configured HS)*/
#define SDT_EXECUTE_DU16              0x0100u     /* execution from a shut down test - pending or
                                                     running*/
#define SDT_FAILED_DU16               0x0400u     /* shut down test failed */
#define SDT_FAILED_HS2_DU16           0x0800u     /* shut down test failed from the second shut
                                                     downswitch (only in mode POL with two
                                                     configured HS)*/
#define EMERGENCY_STOP_DU16           0x1000u     /* emergency stop has been activated */
#define DIAG_OUTPUTS_DU16             0x2000u     /* diagnosis error from at least one of the
                                                     configured outputs  */

/**** typdefs/structures ***************************************************************************
* Typedefs/structures to be made available to other modules.                                      */

// PRQA S 5001 ++
// wrong naming convention accepted

typedef struct
{
  bit16  status_b16;                      /* channel status */
  uint16 diag_u16;
  uint16 diagDebounced_u16;
  uint8  diagLS_u8;                       /* diagnosis from the channel outputs */
  uint8  diagHS_1_u8;
  uint8  diagHS_2_u8;
  uint8  diagHS_3_u8;
  uint8  diagHS_4_u8;
  uint8  statusSDT_u8;                    /* internal status from the shut down test */
  uint16 iSet_u16;                        /* current setpoint from the channel */
  uint16 iHS_u16;                         /* current from high side(s) */
  uint16 iLS_u16;                         /* current from low side */
  bool   iTotalExceeded_l;                /* total current from the channel is exceeded */
} safout_ts;

// PRQA S 5001 --

/**** public data **********************************************************************************
* Declarations of variables to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */

/**** public functions *****************************************************************************
* Declarations of functions to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */

SCOPE_D void safout (uint16 chnl_u16,
                     uint32 hs_u32,
                     uint16 value_u16);

SCOPE_D void safout_cfg (uint16 chnl_u16,
                         uint32 hs_1_u32,
                         uint32 hs_2_u32,
                         uint32 hs_3_u32,
                         uint32 hs_4_u32,
                         uint16 tiDiagDebounce_u16,
                         bool   pinging_l);

SCOPE_D void safout_resetError (uint16 chnl_u16);
SCOPE_D void safout_ignoreError (uint16 chnl_u16);

SCOPE_D uint16 safout_getStatusxt (uint16 chnl_u16, safout_ts *safout_ps);

// PRQA S 5000 ++
// API functions
#define safout_getStatus(CHNL_U16)   safout_getStatusxt(CHNL_U16, (NULL))
// PRQA S 5000 --

/**************************************************************************************************/


#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _SAFOUT_D

#endif  /* _SAFOUT_H_D */
