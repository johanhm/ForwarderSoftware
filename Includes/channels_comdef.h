/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        channels_comdef.h
*
*  \brief       Common channel definitions.
*
*  Includes all commmon definitions for the channel specification like:
*  - modul definitions
*  - function definitions
*  - channel structures
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   RC30-platform
*
* FILE VERSION INFORMATION:  $Revision: 5772 $
*                            $Date: 2013-04-25 09:18:14 +0200 (Do, 25 Apr 2013) $
*                            $Author: sru2abt $
*
* REVISION HISTORY:
*
*
***************************************************************************************************/

#ifndef _CHANNELS_COMDEF_H__D      /* replace it with the filename in capital letters */
#define _CHANNELS_COMDEF_H__D      /* replace it with the filename in capital letters */

#ifdef _CHANNELS_COMDEF_D        /* replace it with the filename in capital letters */
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   /* _CHANNELS_COMDEF_D */


/**** include files ********************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

#include "common_api.h"
#include "types.h"

/**** defines **************************************************************************************
* List of defines needed in this header file and defines to be made available to other modules.   */

/* mask definitions for output channels */
#define CHNL_MASK_DU32                      0x000000FFu    /* channel mask - Bit  7 downto  0 */
#define MOD_MASK_DU32                       0x0000FF00u    /* modul mask   - Bit 15 downto  8 */
#define FUNC_MASK_DU32                      0x00FF0000u    /* group mask   - Bit 23 downto 16 */
#define VAR_MASK_DU32                       0xFF000000u    /* variant mask - Bit 31 downto 24 */

/* up to three variants (one per group) are per module possible */
#define VAR_INS_MASK_DU32                   0x0F000000u    /* 15 insertion variants */
#define VAR_CUR_MASK_DU32                   0x30000000u    /*  3 current variants */


/* modul definitions */
#define MOD_IN_AIV5V_DU32                   0x00000100u
#define MOD_IN_AIV5V_PU_DU32                0x00000200u
#define MOD_IN_AIV5V_VAR_DU32               0x00000300u
#define MOD_IN_AIV10V_DU32                  0x00000400u
#define MOD_IN_AIV10V_PU_DU32               0x00000500u
#define MOD_IN_AIV10V_PUPD_DU32             0x00000600u
#define MOD_IN_AIV32V_DU32                  0x00000700u
#define MOD_IN_AIV10V_CNH_DU32              0x00000800u
#define MOD_IN_AIV10V_PUPD_CNH_DU32         0x00000900u
#define MOD_IN_CPLD_DU32                    0x00000A00u
#define MOD_IN_DI_DU32                      0x00000B00u
#define MOD_IN_AIV15V_PU_DU32               0x00000C00u

#define MOD_IN_FI_DU32                      0x00001000u
#define MOD_IN_FI_DSM_DU32                  0x00001100u
#define MOD_IN_FI_DSM_ANA_DU32              0x00001200u
#define MOD_IN_FI_IND_DU32                  0x00001300u
#define MOD_IN_FI_ACTIV_DU32                0x00001400u
#define MOD_IN_FI_ACTIV_DSM_DU32            0x00001500u
#define MOD_IN_FI_ACTIV_IND_DU32            0x00001600u
#define MOD_IN_AIC_DU32                     0x00001700u
#define MOD_IN_AIC_AI10V_DU32               0x00001800u
#define MOD_IN_TEMP_PTC_DU32                0x00001900u
#define MOD_IN_TEMP_PTC_SISU_DU32           0x00001A00u
/* gap (TEMP_PTC_5V removed) */
#define MOD_IN_TEMP_PTC_FTG_DU32            0x00001C00u
#define MOD_IN_TEMP_PTC_00D9_DU32           0x00001D00u
#define MOD_IN_TEMP_PTC_00DA_DU32           0x00001E00u

#define MOD_IN_FI_DSM_00DA_DU32             0x00006000u
#define MOD_IN_FI_00DA_DU32                 0x00006100u

#define MOD_OUT_POL_DU32                    0x00002000u
#define MOD_OUT_POH_DU32                    0x00002100u
#define MOD_OUT_POL_CS_DU32                 0x00002200u
#define MOD_OUT_POH_CS_DU32                 0x00002300u
#define MOD_OUT_DOL_DU32                    0x00002400u
#define MOD_OUT_DOH_DU32                    0x00002500u
#define MOD_OUT_AOV_DU32                    0x00002600u
#define MOD_OUT_AOC_DU32                    0x00002700u
#define MOD_OUT_POL_LED_DU32                0x00002800u
#define MOD_OUT_POH_LED_DU32                0x00002900u
#define MOD_OUT_POL_EHR_DU32                0x00002A00u
#define MOD_OUT_POH_VND_DU32                0x00002B00u
#define MOD_OUT_POH_VND_CS_DU32             0x00002C00u
#define MOD_OUT_POL_DO_DU32                 0x00002D00u
/* gap (POH_VND_CS_MPU removed) */
#define MOD_OUT_POH_VND_DO_DU32             0x00002F00u
#define MOD_OUT_PVG_DU32                    0x00003000u
#define MOD_OUT_ISOK_LED_DU32               0x00003100u
#define MOD_OUT_POH_VNDD_DU32               0x00003200u
#define MOD_OUT_POH_VNDD_CS_DU32            0x00003300u

#define MOD_SUPPLY_DU32                     0x00004000u
#define MOD_SUPPLY_SENS_DU32                0x00004100u
#define MOD_INH_DU32                        0x00004200u
#define MOD_INH_SIMPLE_DU32                 0x00004300u
#define MOD_TEMP_HW_DU32                    0x00004400u

#define MOD_COM_CAN_DU32                    0x00005000u
#define MOD_COM_LIN_DU32                    0x00005100u


/* function definitions */
#define FUNC_AI_DU32                        0x00010000u
#define FUNC_DI_DU32                        0x00020000u
#define FUNC_FI_DU32                        0x00030000u
#define FUNC_CI_DU32                        0x00040000u

#define FUNC_AIV_DU32                       0x00080000u
#define FUNC_AIR_DU32                       0x00090000u
#define FUNC_AIC_DU32                       0x000A0000u
#define FUNC_AID_DU32                       0x000B0000u
#define FUNC_AIT_DU32                       0x000C0000u
#define FUNC_FIHT_DU32                      0x000D0000u
#define FUNC_FIDC_DU32                      0x000E0000u
#define FUNC_PIC_DU32                       0x000F0000u
#define FUNC_PHASE_DU32                     0x00100000u
#define FUNC_DSM_DU32                       0x00110000u

#define FUNC_DOL_DU32                       0x00200000u
#define FUNC_DOH_DU32                       0x00210000u
#define FUNC_POL_DU32                       0x00220000u
#define FUNC_POH_DU32                       0x00230000u
#define FUNC_POL_CL_DU32                    0x00240000u
#define FUNC_POH_CL_DU32                    0x00250000u
#define FUNC_AOV_DU32                       0x00260000u
#define FUNC_AOC_DU32                       0x00270000u
#define FUNC_FO_DU32                        0x00280000u

#define FUNC_STM_DU32                       0x00300000u

#define FUNC_VB_DU32                        0x00400000u
#define FUNC_VB_V1_DU32                     0x00410000u    /* additonal voltage divider for Ubatt */
#define FUNC_VB_V2_DU32                     0x00420000u    /* additonal voltage divider for Ubatt */
#define FUNC_VCTRL_DU32                     0x00430000u
#define FUNC_VPO_DU32                       0x00440000u
#define FUNC_VDO_DU32                       0x00450000u
#define FUNC_VSS3V3_DU32                    0x00460000u
#define FUNC_VSS5V_DU32                     0x00470000u
#define FUNC_VSS5V_V1_DU32                  0x00480000u    /* additonal voltage divider for VSS5V */
#define FUNC_VSS8V5_DU32                    0x00490000u
#define FUNC_VSS10V_DU32                    0x004A0000u
#define FUNC_VREF_DU32                      0x004B0000u
#define FUNC_VDD5V_OUT_DU32                 0x004C0000u
#define FUNC_V12V_DU32                      0x004D0000u
#define FUNC_VREF_2V54_DU32                 0x004E0000u
#define FUNC_V3V3_EXT_DU32                  0x004F0000u
#define FUNC_VD_DU32                        0x00500000u
#define FUNC_VSS5V_V2_DU32                  0x00510000u    /* additonal voltage divider for VSS5V */

#define FUNC_CAN_DU32                       0x00580000u
#define FUNC_RS232_DU32                     0x00590000u
#define FUNC_LIN_DU32                       0x005A0000u
#define FUNC_UDS_DU32                       0x005B0000u

/* variants definitions */

#define VAR_INS1_DU32                       0x01000000u     /* insertion variants for  */
#define VAR_INS2_DU32                       0x02000000u     /* voltage dividers,       */
#define VAR_INS3_DU32                       0x03000000u     /* missing pullups etc.    */

#define VAR_CUR1_DU32                       0x10000000u     /* current variants */


/* mask definitions for safety channels */
#define SAFOUT_CHNL_MASK_DU16               0x00FFu
#define SAFOUT_MODE_MASK_DU16               0xFF00u

/* safety modes */
#define MODE_POH_DU16                       0x0100u
#define MODE_POL_DU16                       0x0200u
#define MODE_DO_DU16                        0x0300u

#define MODE_MASK_DU16                      0x0700u


/**************************************************************************************************/
/* global defines                                                                                 */
/**************************************************************************************************/

#define maxDutyCycle_DU16                   10000   /* 1/100% */

/* temperatur sensor type numbers */
#define RD95180                             0x01
#define RD95181                             0x02
#define RESISTANCE                          0xFF

/**************************************************************************************************/
/* channel dependend defines                                                                      */
/**************************************************************************************************/

/* Definition of the codes for electrical diagnosis for all inputs and outputs. */
#define DIAG_NOFAILURE_DU8                  0x00    /* no failure */
#define DIAG_SCGND_DU8                      0x01    /* short circuit to ground */
#define DIAG_SCUBAT_DU8                     0x02    /* short circuit to battery */
#define DIAG_OL_DU8                         0x04    /* open load */
#define DIAG_DEVIATION_DU8                  0x08    /* deviation from setpoint */
#define DIAG_RANGE_DU8                      0x10    /* outside from the configured voltage range */
#define DIAG_EMERGENCY_STOP_DU8             0x40    /* emergency stop has been activated */
#define DIAG_PARAMETER_DU8                  0x80    /* function was called with an invalid
                                                       parameter */

#define DIAG_SCGND_OR_OL_DU8                (DIAG_SCGND_DU8 | DIAG_OL_DU8)
#define DIAG_SCUBAT_OR_OL_DU8               (DIAG_SCUBAT_DU8 | DIAG_OL_DU8)

/* DSM sensor direction */
#define stand_DU8                   0x00    /* stand */
#define dirLeft_DU8                 0x01    /* direction left */
#define dirRight_DU8                0x02    /* direction right */
#define dirUnknown_DU8              0x04    /* direction not known for sure
                                               (e.g. after standstill) */

/* DSM sensor status */
#define noError_DU8                 0x00    /* error free */
#define airGabError_DU8             0x01    /* air gab error (puls is lower than 64us) */
#define mountError_DU8              0x02    /* mounting error (puls is greater than 254us) */
#define signalLengthError_DU8       0x04    /* undefined signal length - should not occur (puls is
                                               greater than 1785us) */
#define signalError_DU8             0x08    /* period too long or measured period exceeds
                                               maximum period */
#define noStatusAvailable_DU8       0x10    /* no status signal available (frequency to high) */
#define diagSCUBAT_DU8              0x20    /* SCUBAT detected, see also system error 030C */
#define diagSCGND_OR_OL_DU8         0x40    /* SCGND or OL detected */

/* mask to get the frequency out of the return value from in() */
#define maskFrequency_DU32          0x001FFFFF

/* mask and number to get the direction out of the return value from in() */
#define maskDirection_DU32          0x00E00000
#define numShiftDirection_DU32      21

/* mask and number to get the status out of the return value from in() */
#define maskStatus_DU32             0xFF000000
#define numShiftStatus_DU32         24


/* common status for inputs and outputs */
#define initialized_DB16                    0x0001u
#define configured_DB16                     0x0002u

/* status for the outputs */
#define invalidCalibData_DB16               0x0010u
#define closedLoopControl_DB16              0x0020u
#define configuredDither_DB16               0x0040u
#define configuredForSafetyChannel_DB16     0x0080u
#define disableFiltering_DU16               0x0100u
#define previousStateOn_DU16                0x0200u

/*
 * EOS2 means "Equal Or Smaller than 2ms" - the flag is necessary for the immediate output, see
 * also the preconfiguration values in out_po.cfg and the hidden out_setImmedate_x() functions.
 */
#define immediateEOS2_DB16                  0x0400u

#define errorDiag_DB16                      0x1000u
#define errorSlope_DB16                     0x2000u
#define errorPulse_DB16                     0x4000u

#define errorMask_DU16                      (errorDiag_DB16 | errorSlope_DB16 | errorPulse_DB16)

/* status for the inputs */
#define pullUpOn_DB16                       0x0010u
#define currentMeasurementOn_DB16           0x0020u
#define temperatureMeasurementOn_DB16       0x0040u

/**** typdefs/structures ***************************************************************************
* Typedefs/structures to be made available to other modules.                                      */

/*
 * This is the description of all input channels
 */

/* DI channel */
typedef struct
{
  bit16   status_b16;               /* channel status */
  bool    state_l;                  /* input state */
  bool    stateDebounced_l;         /* input state debounced */
} in_di_ts;

/* AIV channel */
typedef struct
{
  bit16   status_b16;               /* channel status */
  uint16  digits_u16;               /* adc digits, range from 0..16500 */
  uint16  u_mV_u16;                 /* input voltage in mV */
  bool    state_l;                  /* input state */
  bool    stateDebounced_l;         /* input state debounced */
  uint8   diag_u8;                  /* diagnosis eg. DIAG_SCGND_DU8 */
  uint8   diagDebounced_u8;         /* diagnosis debounced eg. DIAG_SCGND_DU8 */
} in_aiv_ts;


/* AIC channel */
typedef struct
{
  bit16   status_b16;               /* channel status */
  uint16  digits_u16;               /* adc digits, range from 0..16500 */
  uint16  u_mV_u16;                 /* input voltage in mV */
  uint16  i_uA_u16;                 /* input current in uA */
  uint8   diag_u8;                  /* diagnosis eg. DIAG_SCGND_DU8 */
  uint8   diagDebounced_u8;         /* diagnosis debounced eg. DIAG_SCGND_DU8 */
} in_aic_ts;


/* AIT channel */
typedef struct
{
  uint8   sensorType_u8;            /* selected sensor type */
  uint16  digits_u16;               /* adc digits, range from 0..16500 */
  uint16  u_mV_u16;                 /* input voltage in mV */
  sint16  t_C_s16;                  /* input temperature in Celcius */
  uint16  rSensor_u16;              /* sensor resistance in Ohm */
} in_ait_ts;


/* PIC channel */
typedef struct
{
  uint16  digits_u16;               /* adc digits, range from 0..16500 */
  uint16  i_mA_u16;                 /* input current in mA */
} in_pic_ts;


/* FI channel */
typedef struct
{
  /* signal info */
  uint32  tiHighDur_u32;            /* high time duration */
  uint32  tiPeriod_u32;             /* periode in us */
  uint32  couPeriod_u32;            /* counter period (31Bit resolution) */
  uint32  f_Hz_u32;                 /* frequency in 1/10 Hz */
  uint16  dc_u16;                   /* dutycycle in 1/10 % */
                                    /* Attention:
                                     * The DSM sensor generates a puls on every edge - the
                                     * frequency from the DSM is the half from the measured
                                     * frequency */
  uint8   stSignal_u8;              /* signal state */
                                    /* - Bit0   state at function call time ("1" for high or
                                     *          "0" for low */
                                    /* - Bit1   no update available (request within the same
                                     *          period) */
                                    /* - Bit2   period too long (timer overflow) */
                                    /* - Bit3   measured period exceeds given maximum length */
  /* DSM info */
  uint32  tiPeriodDSM_u32;          /* DSM periode in us */
  uint32  fDSM_Hz_u32;              /* DSM frequency in 1/10 Hz */
  uint8   dsmDir_u8;                /* direction (see defines above) */
  uint8   dsmState_u8;              /* state info (see defines above) */
} in_fi_ts;


/* all IN channels */
typedef struct
{
  in_di_ts   in_di_s INSERT_PADDING_D;               /* one DI channel */
  in_aiv_ts  in_aiv_s INSERT_PADDING_D;              /* one AIV channel */
  in_aic_ts  in_aic_s INSERT_PADDING_D;              /* one AIC channel */
  in_ait_ts  in_ait_s INSERT_PADDING_D;              /* one AIT channel */
  in_pic_ts  in_pic_s INSERT_PADDING_D;              /* one PIC channel */
  in_fi_ts   in_fi_s INSERT_PADDING_D;               /* one FI channel */
} in_ts;


/* PHASE channel */
typedef struct
{
  uint32  tPrimSig_u32;                 /* primary signal time stamp [us] */
  uint32  tSecSig_u32;                  /* secondary signal time stamp [us] */
  uint32  tShift_u32;                   /* signal phase shift [us] */
  sint32  couPulse_s32;                 /* pulse counter - direction of counting depend on phase
                                         * position (stSecSig_l) */
  bool    stSecSig_l;                   /* phase position from the second signal state at the
                                         * rising edge ofprimary signal */
  uint32  tPeriodePrimSig_u32;          /* periode primary signal [us] */
  uint32  tPeriodeSecSig_u32;           /* periode secondary signal[us] */
  uint8   stErrorPrimSig_u8;            /* error state primary signal */
                                        /* - Bit0   state at function call time ("1" for high or
                                         *          "0" for low */
                                        /* - Bit1   no update available (request within the same
                                         *          period) */
                                        /* - Bit2   period too long (timer overflow) */
                                        /* - Bit3   measured period exceeds given maximum length */
  uint8   stErrorSecSig_u8;             /* error state secondary signal */
                                        /* - Bit0   state at function call time ("1" for
                                         *          high or "0" for low */
                                        /* - Bit1   no update available (request within the
                                         *          same period) */
                                        /* - Bit2   period too long (timer overflow) */
                                        /* - Bit3   measured period exceeds given maximum
                                         *          length */
                                        /* 32Bit alignment for BODAS */
} phaseDep_ts;


/* holds the data about the period from a frequency input */
typedef struct
{
  uint32 tiMaxPeriod_u32;       /* configured maximal period from core */
  uint32 tiSetPeriod_u32;       /* setpoint period */
} in_fi_per_ts;


/****
 * This is the description of all output channels
 */

/* DO channel */
typedef struct
{
  bit16   status_b16;               /* channel status */
  bool    on_l;                     /* last value written from the application */
  bool    state_l;                  /* state value from output */
  uint8   diag_u8;                  /* diagnosis */
  uint8   diagDebounced_u8;         /* diagnosis debounced */
} out_do_ts;


/* PO channel */
typedef struct
{
  bit16   status_b16;               /* channel status */
  uint16  dc_u16;                   /* last duty cycle value written from the application */
  uint16  iSet_u16;                 /* setpoint current in mA */
  uint16  digits_u16;               /* actual current */
  uint16  i_mA_u16;                 /* actual current in mA */
  uint32  rLoad_u32;                /* actual load in mOhm */
  bool    state_l;                  /* state value from output */
  uint8   diag_u8;                  /* diagnosis */
  uint8   diagDebounced_u8;         /* diagnosis debounced */
  uint16  iMaxSlope_u16;            /* current value in digits for maximal slope */
} out_po_ts;


/* AOC channel */
typedef struct
{
  bit16   status_b16;               /* channel status */
  uint16  dc_u16;                   /* last duty cycle value written from the application */
  uint16  iSet_u16;                 /* setpoint current in uA */
  uint16  uSet_u16;                 /* setpoint voltage in mV */
  uint16  digits_u16;               /* actual current in digits */
  uint16  digitsAOV_u16;            /* actual voltage in digits */
  uint16  i_uA_u16;                 /* actual current in uA */
  uint16  u_mV_u16;                 /* actual voltage in mV */
  uint8   diag_u8;                  /* diagnosis */
  uint8   diagDebounced_u8;         /* diagnosis debounced */
} out_aoc_ts;


/* AOV channel */
typedef struct
{
  bit16   status_b16;               /* channel status */
  uint16  dc_u16;                   /* last duty cycle value written from the application */
  uint16  uSet_u16;                 /* setpoint voltage in mV */
  uint16  digits_u16;               /* actual voltage in digits */
  uint16  u_mV_u16;                 /* actual voltage in mV */
  uint8   diag_u8;                  /* diagnosis */
  uint8   diagDebounced_u8;         /* diagnosis debounced */
} out_aov_ts;


/* all OUT channels */
typedef struct
{
  out_do_ts  out_do_s INSERT_PADDING_D;              /* one DO channel */
  out_po_ts  out_po_s INSERT_PADDING_D;              /* one PO channel */
  out_aoc_ts out_aoc_s INSERT_PADDING_D;             /* one AOC channel */
  out_aov_ts out_aov_s INSERT_PADDING_D;             /* one AOV channel */
} out_ts;


#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _CHANNELS_COMDEF_D

#endif  /* _CHANNELS_COMDEF_H__D */
