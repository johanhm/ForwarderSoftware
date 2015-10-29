/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        channels.h
*
*  \brief       Channel definitions.
*
*  A channel definition looks like:\n
*  \n
*  31              24 23             16 15              8 7               0
*  +-----------------+-----------------+----------------------------------+\n
*  | reserved        | function        | modul           | number       |\n
*  +-----------------+-----------------+----------------------------------+\n
*  \n
*  A group is the summary of all inputs or outputs with the same behavior. Inside the group all
*  inputs or outputs are numbered in an ascending order. \n
*  \n
*  Example: A group with analog inputs are numbered with AIV_1, AIV_2 et cetera.
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   RC30 plattform
*                            Hardware: RC30/28-14 (RC30-00D6)
*
* FILE VERSION INFORMATION:  $Revision: 5944 $
*                            $Date: 2013-06-10 15:18:24 +0200 (Mo, 10 Jun 2013) $
*                            $Author: gtg2si $
*
* REVISION HISTORY:
*
*
***************************************************************************************************/

#ifndef _CHANNELS_H_D        /* replace it with the filename in capital letters */
#define _CHANNELS_H_D        /* replace it with the filename in capital letters */

#include "channels_comdef.h"

#ifdef _CHANNELS_D       /* replace it with the filename in capital letters */
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   /* _CHANNELS_D */

/**** include files ********************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

/**** defines **************************************************************************************
* List of defines needed in this header file and defines to be made available to other modules.   */

/* average adc reference voltage is 3333mV  */
#define resolutionPerDigit_DU8              202     /* 202uV per digit */

/**************************************************************************************************/
/* number of modul inputs and modul outputs                                                       */
/**************************************************************************************************/

#define CPLD_NUM_DU8                        (10)

/* not available */
#define AIV5V_NUM_DU8                       (0)
#define AIV5V_PU_NUM_DU8                    (0)
#define AIV5V_VAR_NUM_DU8                   (0)
#define AIV10V_PU_NUM_DU8                   (0)
#define AIV10V_PUPD_NUM_DU8                 (0)

#define AIV10V_NUM_DU8                      (7)
#define AIV32V_NUM_DU8                      (2)
#define AIV10V_CNH_NUM_DU8                  (8)
#define AIV10V_PUPD_CNH_NUM_DU8             (24)

#define AIC_AI10V_NUM_DU8                   (10)

/* not available */
#define FI_NUM_DU8                          (0)
#define FI_ACTIV_DSM_NUM_DU8                (0)
#define FI_ACTIV_IND_NUM_DU8                (0)
#define FI_DSM_ANA_NUM_DU8                  (0)

#define FI_ACTIV_NUM_DU8                    (3)
#define FI_DSM_NUM_DU8                      (5)
#define FI_IND_NUM_DU8                      (2)

/* not available */
#define FI_PHASE_NUM_DU8                    (0)
#define FI_PHASE_DSM_ANA_NUM_DU8            (0)

#define FI_PHASE_ACTIV_NUM_DU8              (1)
#define FI_PHASE_DSM_NUM_DU8                (2)
#define FI_PHASE_IND_NUM_DU8                (1)

/* not available */
#define TEMP_PTC_NUM_DU8                    (0)
#define TEMP_PTC_SISU_NUM_DU8               (0)
#define TEMP_PTC_00D9_NUM_DU8               (0)

#define TEMP_PTC_FTG_NUM_DU8                (4)

/* not available */
#define POH_NUM_DU8                         (0)
#define POH_CS_NUM_DU8                      (0)
#define POH_LED_NUM_DU8                     (0)
#define POH_VND_DO_NUM_DU8                  (0)

#define POH_VND_NUM_DU8                     (18)
#define POH_VND_CS_NUM_DU8                  (14)

/* not available */
#define POL_DO_NUM_DU8                      (0)
#define POL_LED_NUM_DU8                     (0)

#define POL_NUM_DU8                         (8)
#define POL_EHR_NUM_DU8                     (2)

/* not available */
#define DOH_NUM_DU8                         (0)

#define AOC_NUM_DU8                         (1)

#define PVG_NUM_DU8                         (4)

/* not available */
#define AOV_NUM_DU8                         (0)


/**************************************************************************************************/
/* number of safety channels (depend on number of LS)                                           */
/**************************************************************************************************/

#define SAFOUT_NUM_DU8                      (POL_NUM_DU8 + POL_EHR_NUM_DU8)


/**************************************************************************************************/
/* start address (16 Bit) for the calibration date inside the EEPROM system page                  */
/**************************************************************************************************/

/* not available */
#define adrEepromPOH_DU16                   (0)
#define adrEepromPOH_CS_DU16                (0)

/* not available */
#define adrEepromAOV_DU16                   (0)
#define adrEepromTEMP_PTC_DU16              (0)
#define adrEepromTEMP_PTC_SISU_DU16         (0)
#define adrEepromTEMP_PTC_5V_DU16           (0)
#define adrEepromTEMP_PTC_00D9_DU16         (0)

#define adrEepromPOH_VND_DU16               (0)
#define adrEepromPOH_VND_CS_DU16            (36)
#define adrEepromPVG_DU16                   (64)
#define adrEepromPOL_EHR_DU16               (72)
#define adrEepromPOL_DU16                   (76)
#define adrEepromAOC_DU16                   (92)

#define adrEepromTEMP_PTC_FTG_DU16          (180)


/**************************************************************************************************/
/* inputs                                                                                         */
/**************************************************************************************************/

/*** digital inputs *******************************************************************************/

#define IN_42_DI                  (FUNC_DI_DU32 | MOD_IN_CPLD_DU32 | 0x00000000)
#define IN_43_DI                  (FUNC_DI_DU32 | MOD_IN_CPLD_DU32 | 0x00000001)
#define IN_44_DI                  (FUNC_DI_DU32 | MOD_IN_CPLD_DU32 | 0x00000002)
#define IN_45_DI                  (FUNC_DI_DU32 | MOD_IN_CPLD_DU32 | 0x00000003)
#define IN_46_DI                  (FUNC_DI_DU32 | MOD_IN_CPLD_DU32 | 0x00000004)
#define IN_47_DI                  (FUNC_DI_DU32 | MOD_IN_CPLD_DU32 | 0x00000005)
#define IN_48_DI                  (FUNC_DI_DU32 | MOD_IN_CPLD_DU32 | 0x00000006)
#define IN_49_DI                  (FUNC_DI_DU32 | MOD_IN_CPLD_DU32 | 0x00000007)
#define IN_50_DI                  (FUNC_DI_DU32 | MOD_IN_CPLD_DU32 | 0x00000008)
#define IN_51_DI                  (FUNC_DI_DU32 | MOD_IN_CPLD_DU32 | 0x00000009)

#define IN_71_DI                  (FUNC_DI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000000)
#define IN_72_DI                  (FUNC_DI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000001)
#define IN_73_DI                  (FUNC_DI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000002)
#define IN_74_DI                  (FUNC_DI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000003)
#define IN_75_DI                  (FUNC_DI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000004)

/*** analog inputs ********************************************************************************/

/*** digits *************************************/

/* voltage moduls */
#define IN_1_AI                   (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000000)
#define IN_2_AI                   (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000001)
#define IN_3_AI                   (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000002)
#define IN_4_AI                   (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000003)
#define IN_5_AI                   (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000004)
#define IN_6_AI                   (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000005)
#define IN_7_AI                   (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000006)
#define IN_8_AI                   (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000007)
#define IN_9_AI                   (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000008)
#define IN_10_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000009)
#define IN_11_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000A)
#define IN_12_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000B)
#define IN_13_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000C)
#define IN_14_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000D)
#define IN_15_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000E)
#define IN_16_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000F)
#define IN_17_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000010)
#define IN_18_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000011)
#define IN_19_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000012)
#define IN_20_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000013)
#define IN_21_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000014)
#define IN_22_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000015)
#define IN_23_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000016)
#define IN_24_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000017)

#define IN_25_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000000)
#define IN_26_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000001)
#define IN_27_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000002)
#define IN_28_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000003)
#define IN_29_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000004)
#define IN_30_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000005)
#define IN_31_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000006)
#define IN_32_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000007)

#define IN_33_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_DU32 | 0x00000000)
#define IN_34_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_DU32 | 0x00000001)
#define IN_35_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_DU32 | 0x00000002)
#define IN_36_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_DU32 | 0x00000003)
#define IN_37_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_DU32 | 0x00000004)
#define IN_38_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_DU32 | 0x00000005)
#define IN_39_AI                  (FUNC_AI_DU32 | MOD_IN_AIV10V_DU32 | 0x00000006)

#define IN_40_AI                  (FUNC_AI_DU32 | MOD_IN_AIV32V_DU32 | 0x00000000)
#define IN_41_AI                  (FUNC_AI_DU32 | MOD_IN_AIV32V_DU32 | 0x00000001)

/* current moduls */
#define IN_52_AI                  (FUNC_AI_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000000)
#define IN_53_AI                  (FUNC_AI_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000001)
#define IN_54_AI                  (FUNC_AI_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000002)
#define IN_55_AI                  (FUNC_AI_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000003)
#define IN_56_AI                  (FUNC_AI_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000004)
#define IN_57_AI                  (FUNC_AI_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000005)
#define IN_58_AI                  (FUNC_AI_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000006)
#define IN_59_AI                  (FUNC_AI_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000007)
#define IN_60_AI                  (FUNC_AI_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000008)
#define IN_61_AI                  (FUNC_AI_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000009)

/* temperature moduls */
#define IN_62_AI                  (FUNC_AI_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000000)
#define IN_63_AI                  (FUNC_AI_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000001)
#define IN_64_AI                  (FUNC_AI_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000002)
#define IN_65_AI                  (FUNC_AI_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000003)

/* frequency moduls */
#define IN_66_AI                  (FUNC_AI_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000000)
#define IN_67_AI                  (FUNC_AI_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000001)

#define IN_69_AI                  (FUNC_AI_DU32 | MOD_IN_FI_IND_DU32 | 0x00000000)
#define IN_70_AI                  (FUNC_AI_DU32 | MOD_IN_FI_IND_DU32 | 0x00000001)


/*** voltage ************************************/

/* voltage moduls */
#define IN_1_AIV                  (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000000)
#define IN_2_AIV                  (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000001)
#define IN_3_AIV                  (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000002)
#define IN_4_AIV                  (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000003)
#define IN_5_AIV                  (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000004)
#define IN_6_AIV                  (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000005)
#define IN_7_AIV                  (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000006)
#define IN_8_AIV                  (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000007)
#define IN_9_AIV                  (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000008)
#define IN_10_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000009)
#define IN_11_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000A)
#define IN_12_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000B)
#define IN_13_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000C)
#define IN_14_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000D)
#define IN_15_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000E)
#define IN_16_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000F)
#define IN_17_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000010)
#define IN_18_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000011)
#define IN_19_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000012)
#define IN_20_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000013)
#define IN_21_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000014)
#define IN_22_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000015)
#define IN_23_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000016)
#define IN_24_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000017)

#define IN_25_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000000)
#define IN_26_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000001)
#define IN_27_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000002)
#define IN_28_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000003)
#define IN_29_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000004)
#define IN_30_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000005)
#define IN_31_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000006)
#define IN_32_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000007)

#define IN_33_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_DU32 | 0x00000000)
#define IN_34_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_DU32 | 0x00000001)
#define IN_35_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_DU32 | 0x00000002)
#define IN_36_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_DU32 | 0x00000003)
#define IN_37_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_DU32 | 0x00000004)
#define IN_38_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_DU32 | 0x00000005)
#define IN_39_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV10V_DU32 | 0x00000006)

#define IN_40_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV32V_DU32 | 0x00000000)
#define IN_41_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIV32V_DU32 | 0x00000001)

/* current moduls */
#define IN_52_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000000)
#define IN_53_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000001)
#define IN_54_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000002)
#define IN_55_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000003)
#define IN_56_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000004)
#define IN_57_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000005)
#define IN_58_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000006)
#define IN_59_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000007)
#define IN_60_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000008)
#define IN_61_AIV                 (FUNC_AIV_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000009)

/* temperature moduls */
#define IN_62_AIV                 (FUNC_AIV_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000000)
#define IN_63_AIV                 (FUNC_AIV_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000001)
#define IN_64_AIV                 (FUNC_AIV_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000002)
#define IN_65_AIV                 (FUNC_AIV_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000003)

/* frequency moduls */
#define IN_66_AIV                 (FUNC_AIV_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000000)
#define IN_67_AIV                 (FUNC_AIV_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000001)

#define IN_69_AIV                 (FUNC_AIV_DU32 | MOD_IN_FI_IND_DU32 | 0x00000000)
#define IN_70_AIV                 (FUNC_AIV_DU32 | MOD_IN_FI_IND_DU32 | 0x00000001)

/*** digital ************************************/

#define IN_1_AID                  (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000000)
#define IN_2_AID                  (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000001)
#define IN_3_AID                  (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000002)
#define IN_4_AID                  (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000003)
#define IN_5_AID                  (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000004)
#define IN_6_AID                  (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000005)
#define IN_7_AID                  (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000006)
#define IN_8_AID                  (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000007)
#define IN_9_AID                  (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000008)
#define IN_10_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000009)
#define IN_11_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000A)
#define IN_12_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000B)
#define IN_13_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000C)
#define IN_14_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000D)
#define IN_15_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000E)
#define IN_16_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x0000000F)
#define IN_17_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000010)
#define IN_18_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000011)
#define IN_19_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000012)
#define IN_20_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000013)
#define IN_21_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000014)
#define IN_22_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000015)
#define IN_23_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000016)
#define IN_24_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_PUPD_CNH_DU32 | 0x00000017)

#define IN_25_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000000)
#define IN_26_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000001)
#define IN_27_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000002)
#define IN_28_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000003)
#define IN_29_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000004)
#define IN_30_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000005)
#define IN_31_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000006)
#define IN_32_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_CNH_DU32 | 0x00000007)

#define IN_33_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_DU32 | 0x00000000)
#define IN_34_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_DU32 | 0x00000001)
#define IN_35_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_DU32 | 0x00000002)
#define IN_36_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_DU32 | 0x00000003)
#define IN_37_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_DU32 | 0x00000004)
#define IN_38_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_DU32 | 0x00000005)
#define IN_39_AID                 (FUNC_AID_DU32 | MOD_IN_AIV10V_DU32 | 0x00000006)

#define IN_40_AID                 (FUNC_AID_DU32 | MOD_IN_AIV32V_DU32 | 0x00000000)
#define IN_41_AID                 (FUNC_AID_DU32 | MOD_IN_AIV32V_DU32 | 0x00000001)

/* current moduls */
#define IN_52_AID                 (FUNC_AID_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000000)
#define IN_53_AID                 (FUNC_AID_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000001)
#define IN_54_AID                 (FUNC_AID_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000002)
#define IN_55_AID                 (FUNC_AID_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000003)
#define IN_56_AID                 (FUNC_AID_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000004)
#define IN_57_AID                 (FUNC_AID_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000005)
#define IN_58_AID                 (FUNC_AID_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000006)
#define IN_59_AID                 (FUNC_AID_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000007)
#define IN_60_AID                 (FUNC_AID_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000008)
#define IN_61_AID                 (FUNC_AID_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000009)

/* temperature moduls */
#define IN_62_AID                 (FUNC_AID_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000000)
#define IN_63_AID                 (FUNC_AID_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000001)
#define IN_64_AID                 (FUNC_AID_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000002)
#define IN_65_AID                 (FUNC_AID_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000003)

/* frequency moduls */
#define IN_66_AID                 (FUNC_AID_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000000)
#define IN_67_AID                 (FUNC_AID_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000001)

#define IN_69_AID                 (FUNC_AID_DU32 | MOD_IN_FI_IND_DU32 | 0x00000000)
#define IN_70_AID                 (FUNC_AID_DU32 | MOD_IN_FI_IND_DU32 | 0x00000001)

/*** current ************************************/

#define IN_52_AIC                 (FUNC_AIC_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000000)
#define IN_53_AIC                 (FUNC_AIC_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000001)
#define IN_54_AIC                 (FUNC_AIC_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000002)
#define IN_55_AIC                 (FUNC_AIC_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000003)
#define IN_56_AIC                 (FUNC_AIC_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000004)
#define IN_57_AIC                 (FUNC_AIC_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000005)
#define IN_58_AIC                 (FUNC_AIC_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000006)
#define IN_59_AIC                 (FUNC_AIC_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000007)
#define IN_60_AIC                 (FUNC_AIC_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000008)
#define IN_61_AIC                 (FUNC_AIC_DU32 | MOD_IN_AIC_AI10V_DU32 | 0x00000009)

/*** temperature ********************************/

#define IN_62_AIT                 (FUNC_AIT_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000000)
#define IN_63_AIT                 (FUNC_AIT_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000001)
#define IN_64_AIT                 (FUNC_AIT_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000002)
#define IN_65_AIT                 (FUNC_AIT_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000003)

/*** resistance *********************************/

#define IN_62_AIR                 (FUNC_AIR_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000000)
#define IN_63_AIR                 (FUNC_AIR_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000001)
#define IN_64_AIR                 (FUNC_AIR_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000002)
#define IN_65_AIR                 (FUNC_AIR_DU32 | MOD_IN_TEMP_PTC_FTG_DU32 | 0x00000003)

/*** frequency inputs *****************************************************************************/

#define IN_66_FI                  (FUNC_FI_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000000)
#define IN_67_FI                  (FUNC_FI_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000001)
#define IN_68_FI                  (FUNC_FI_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000002)

#define IN_69_FI                  (FUNC_FI_DU32 | MOD_IN_FI_IND_DU32 | 0x00000000)
#define IN_70_FI                  (FUNC_FI_DU32 | MOD_IN_FI_IND_DU32 | 0x00000001)

#define IN_71_FI                  (FUNC_FI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000000)
#define IN_72_FI                  (FUNC_FI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000001)
#define IN_73_FI                  (FUNC_FI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000002)
#define IN_74_FI                  (FUNC_FI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000003)
#define IN_75_FI                  (FUNC_FI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000004)

/*** FIHT ***************************************/

#define IN_66_FIHT                (FUNC_FIHT_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000000)
#define IN_67_FIHT                (FUNC_FIHT_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000001)
#define IN_68_FIHT                (FUNC_FIHT_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000002)

#define IN_69_FIHT                (FUNC_FIHT_DU32 | MOD_IN_FI_IND_DU32 | 0x00000000)
#define IN_70_FIHT                (FUNC_FIHT_DU32 | MOD_IN_FI_IND_DU32 | 0x00000001)

#define IN_71_FIHT                (FUNC_FIHT_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000000)
#define IN_72_FIHT                (FUNC_FIHT_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000001)
#define IN_73_FIHT                (FUNC_FIHT_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000002)
#define IN_74_FIHT                (FUNC_FIHT_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000003)
#define IN_75_FIHT                (FUNC_FIHT_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000004)

/*** FIDC ***************************************/

#define IN_66_FIDC                (FUNC_FIDC_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000000)
#define IN_67_FIDC                (FUNC_FIDC_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000001)
#define IN_68_FIDC                (FUNC_FIDC_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000002)

#define IN_69_FIDC                (FUNC_FIDC_DU32 | MOD_IN_FI_IND_DU32 | 0x00000000)
#define IN_70_FIDC                (FUNC_FIDC_DU32 | MOD_IN_FI_IND_DU32 | 0x00000001)

#define IN_71_FIDC                (FUNC_FIDC_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000000)
#define IN_72_FIDC                (FUNC_FIDC_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000001)
#define IN_73_FIDC                (FUNC_FIDC_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000002)
#define IN_74_FIDC                (FUNC_FIDC_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000003)
#define IN_75_FIDC                (FUNC_FIDC_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000004)

/*** CI *****************************************/

#define IN_66_CI                  (FUNC_CI_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000000)
#define IN_67_CI                  (FUNC_CI_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000001)
#define IN_68_CI                  (FUNC_CI_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000002)

#define IN_69_CI                  (FUNC_CI_DU32 | MOD_IN_FI_IND_DU32 | 0x00000000)
#define IN_70_CI                  (FUNC_CI_DU32 | MOD_IN_FI_IND_DU32 | 0x00000001)

#define IN_71_CI                  (FUNC_CI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000000)
#define IN_72_CI                  (FUNC_CI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000001)
#define IN_73_CI                  (FUNC_CI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000002)
#define IN_74_CI                  (FUNC_CI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000003)
#define IN_75_CI                  (FUNC_CI_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000004)

/*** DSM ****************************************/

#define IN_71_DSM                 (FUNC_DSM_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000000)
#define IN_72_DSM                 (FUNC_DSM_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000001)
#define IN_73_DSM                 (FUNC_DSM_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000002)
#define IN_74_DSM                 (FUNC_DSM_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000003)
#define IN_75_DSM                 (FUNC_DSM_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000004)

/*** PHASE **************************************/

#define IN_66_PHASE               (FUNC_PHASE_DU32 | MOD_IN_FI_ACTIV_DU32 | 0x00000000)

#define IN_69_PHASE               (FUNC_PHASE_DU32 | MOD_IN_FI_IND_DU32 | 0x00000000)

#define IN_71_PHASE               (FUNC_PHASE_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000000)
#define IN_73_PHASE               (FUNC_PHASE_DU32 | MOD_IN_FI_DSM_DU32 | 0x00000001)

/*** EXTENDED FREQUENCY ACQUISITION **********************/

#define IN_66_FREQ_ACQ            (0x08)
#define IN_67_FREQ_ACQ            (0x09)
#define IN_68_FREQ_ACQ            (0x05)

#define IN_69_FREQ_ACQ            (0x06)
#define IN_70_FREQ_ACQ            (0x07)

#define IN_71_FREQ_ACQ            (0x00)
#define IN_72_FREQ_ACQ            (0x01)
#define IN_73_FREQ_ACQ            (0x02)
#define IN_74_FREQ_ACQ            (0x03)
#define IN_75_FREQ_ACQ            (0x04)

/**************************************************************************************************/
/* outputs                                                                                        */
/**************************************************************************************************/

/*** high side ************************************************************************************/

/*** digital ************************************/

/* high side moduls */
#define OUT_1_DOH                 (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000000)
#define OUT_2_DOH                 (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000001)
#define OUT_3_DOH                 (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000002)
#define OUT_4_DOH                 (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000003)
#define OUT_5_DOH                 (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000004)
#define OUT_6_DOH                 (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000005)
#define OUT_7_DOH                 (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000006)
#define OUT_8_DOH                 (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000007)
#define OUT_9_DOH                 (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000008)
#define OUT_10_DOH                (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000009)
#define OUT_11_DOH                (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000A)
#define OUT_12_DOH                (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000B)
#define OUT_13_DOH                (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000C)
#define OUT_14_DOH                (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000D)
#define OUT_15_DOH                (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000E)
#define OUT_16_DOH                (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000F)
#define OUT_17_DOH                (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000010)
#define OUT_18_DOH                (FUNC_DOH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000011)

#define OUT_19_DOH            (VAR_CUR1_DU32 | FUNC_DOH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000000)
#define OUT_20_DOH            (VAR_CUR1_DU32 | FUNC_DOH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000001)
#define OUT_21_DOH                            (FUNC_DOH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000002)
#define OUT_22_DOH                            (FUNC_DOH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000003)
#define OUT_23_DOH                            (FUNC_DOH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000004)
#define OUT_24_DOH                            (FUNC_DOH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000005)
#define OUT_25_DOH                            (FUNC_DOH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000006)
#define OUT_26_DOH                            (FUNC_DOH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000007)
#define OUT_27_DOH            (VAR_CUR1_DU32 | FUNC_DOH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000008)
#define OUT_28_DOH            (VAR_CUR1_DU32 | FUNC_DOH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000009)
#define OUT_29_DOH                            (FUNC_DOH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000A)
#define OUT_30_DOH                            (FUNC_DOH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000B)
#define OUT_31_DOH                            (FUNC_DOH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000C)
#define OUT_32_DOH                            (FUNC_DOH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000D)

/* low side moduls */
#define OUT_37_DOL               (VAR_CUR1_DU32 | FUNC_DOL_DU32 | MOD_OUT_POL_EHR_DU32 | 0x00000000)
#define OUT_41_DOL               (VAR_CUR1_DU32 | FUNC_DOL_DU32 | MOD_OUT_POL_EHR_DU32 | 0x00000001)

#define OUT_38_DOL               (FUNC_DOL_DU32 | MOD_OUT_POL_DU32 | 0x00000000)
#define OUT_39_DOL               (FUNC_DOL_DU32 | MOD_OUT_POL_DU32 | 0x00000001)
#define OUT_40_DOL               (FUNC_DOL_DU32 | MOD_OUT_POL_DU32 | 0x00000002)
#define OUT_42_DOL               (FUNC_DOL_DU32 | MOD_OUT_POL_DU32 | 0x00000003)
#define OUT_43_DOL               (FUNC_DOL_DU32 | MOD_OUT_POL_DU32 | 0x00000004)
#define OUT_44_DOL               (FUNC_DOL_DU32 | MOD_OUT_POL_DU32 | 0x00000005)
#define OUT_45_DOL               (FUNC_DOL_DU32 | MOD_OUT_POL_DU32 | 0x00000006)
#define OUT_46_DOL               (FUNC_DOL_DU32 | MOD_OUT_POL_DU32 | 0x00000007)

/*** proportional *******************************/

/* high side moduls */
#define OUT_1_POH                 (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000000)
#define OUT_2_POH                 (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000001)
#define OUT_3_POH                 (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000002)
#define OUT_4_POH                 (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000003)
#define OUT_5_POH                 (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000004)
#define OUT_6_POH                 (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000005)
#define OUT_7_POH                 (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000006)
#define OUT_8_POH                 (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000007)
#define OUT_9_POH                 (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000008)
#define OUT_10_POH                (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000009)
#define OUT_11_POH                (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000A)
#define OUT_12_POH                (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000B)
#define OUT_13_POH                (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000C)
#define OUT_14_POH                (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000D)
#define OUT_15_POH                (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000E)
#define OUT_16_POH                (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000F)
#define OUT_17_POH                (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000010)
#define OUT_18_POH                (FUNC_POH_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000011)

/* not used, only predefined !!! */
//#define OUT_19_POH         ((VAR_CUR1_DU32 | FUNC_POH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000000)
//#define OUT_20_POH         ((VAR_CUR1_DU32 | FUNC_POH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000001)
//#define OUT_21_POH                          (FUNC_POH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000002)
//#define OUT_22_POH                          (FUNC_POH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000003)
//#define OUT_23_POH                          (FUNC_POH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000004)
//#define OUT_24_POH                          (FUNC_POH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000005)
//#define OUT_25_POH                          (FUNC_POH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000006)
//#define OUT_26_POH                          (FUNC_POH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000007)
//#define OUT_27_POH         ((VAR_CUR1_DU32 | FUNC_POH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000008)
//#define OUT_28_POH         ((VAR_CUR1_DU32 | FUNC_POH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000009)
//#define OUT_29_POH                          (FUNC_POH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000A)
//#define OUT_30_POH                          (FUNC_POH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000B)
//#define OUT_31_POH                          (FUNC_POH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000C)
//#define OUT_32_POH                          (FUNC_POH_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000D)

/* PVG modul */
#define OUT_33_POH                (FUNC_POH_DU32 | MOD_OUT_PVG_DU32 | 0x00000000)
#define OUT_34_POH                (FUNC_POH_DU32 | MOD_OUT_PVG_DU32 | 0x00000001)
#define OUT_35_POH                (FUNC_POH_DU32 | MOD_OUT_PVG_DU32 | 0x00000002)
#define OUT_36_POH                (FUNC_POH_DU32 | MOD_OUT_PVG_DU32 | 0x00000003)

/* low side moduls */
#define OUT_37_POL               (VAR_CUR1_DU32 | FUNC_POL_DU32 | MOD_OUT_POL_EHR_DU32 | 0x00000000)
#define OUT_41_POL               (VAR_CUR1_DU32 | FUNC_POL_DU32 | MOD_OUT_POL_EHR_DU32 | 0x00000001)

#define OUT_38_POL                (FUNC_POL_DU32 | MOD_OUT_POL_DU32 | 0x00000000)
#define OUT_39_POL                (FUNC_POL_DU32 | MOD_OUT_POL_DU32 | 0x00000001)
#define OUT_40_POL                (FUNC_POL_DU32 | MOD_OUT_POL_DU32 | 0x00000002)
#define OUT_42_POL                (FUNC_POL_DU32 | MOD_OUT_POL_DU32 | 0x00000003)
#define OUT_43_POL                (FUNC_POL_DU32 | MOD_OUT_POL_DU32 | 0x00000004)
#define OUT_44_POL                (FUNC_POL_DU32 | MOD_OUT_POL_DU32 | 0x00000005)
#define OUT_45_POL                (FUNC_POL_DU32 | MOD_OUT_POL_DU32 | 0x00000006)
#define OUT_46_POL                (FUNC_POL_DU32 | MOD_OUT_POL_DU32 | 0x00000007)

/*** closed loop control ************************/

/* high side moduls */
#define OUT_1_POH_CL              (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000000)
#define OUT_2_POH_CL              (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000001)
#define OUT_3_POH_CL              (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000002)
#define OUT_4_POH_CL              (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000003)
#define OUT_5_POH_CL              (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000004)
#define OUT_6_POH_CL              (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000005)
#define OUT_7_POH_CL              (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000006)
#define OUT_8_POH_CL              (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000007)
#define OUT_9_POH_CL              (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000008)
#define OUT_10_POH_CL             (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000009)
#define OUT_11_POH_CL             (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000A)
#define OUT_12_POH_CL             (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000B)
#define OUT_13_POH_CL             (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000C)
#define OUT_14_POH_CL             (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000D)
#define OUT_15_POH_CL             (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000E)
#define OUT_16_POH_CL             (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000F)
#define OUT_17_POH_CL             (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000010)
#define OUT_18_POH_CL             (FUNC_POH_CL_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000011)

/* low side moduls */
#define OUT_37_POL_CL         (VAR_CUR1_DU32 | FUNC_POL_CL_DU32 | MOD_OUT_POL_EHR_DU32 | 0x00000000)
#define OUT_41_POL_CL         (VAR_CUR1_DU32 | FUNC_POL_CL_DU32 | MOD_OUT_POL_EHR_DU32 | 0x00000001)

#define OUT_38_POL_CL             (FUNC_POL_CL_DU32 | MOD_OUT_POL_DU32 | 0x00000000)
#define OUT_39_POL_CL             (FUNC_POL_CL_DU32 | MOD_OUT_POL_DU32 | 0x00000001)
#define OUT_40_POL_CL             (FUNC_POL_CL_DU32 | MOD_OUT_POL_DU32 | 0x00000002)
#define OUT_42_POL_CL             (FUNC_POL_CL_DU32 | MOD_OUT_POL_DU32 | 0x00000003)
#define OUT_43_POL_CL             (FUNC_POL_CL_DU32 | MOD_OUT_POL_DU32 | 0x00000004)
#define OUT_44_POL_CL             (FUNC_POL_CL_DU32 | MOD_OUT_POL_DU32 | 0x00000005)
#define OUT_45_POL_CL             (FUNC_POL_CL_DU32 | MOD_OUT_POL_DU32 | 0x00000006)
#define OUT_46_POL_CL             (FUNC_POL_CL_DU32 | MOD_OUT_POL_DU32 | 0x00000007)

/*** current ************************/

#define OUT_47_AOC                 (FUNC_AOC_DU32 | MOD_OUT_AOC_DU32 | 0x00000000)

/*** voltage ************************/

#define OUT_33_AOV                (FUNC_AOV_DU32 | MOD_OUT_PVG_DU32 | 0x00000000)
#define OUT_34_AOV                (FUNC_AOV_DU32 | MOD_OUT_PVG_DU32 | 0x00000001)
#define OUT_35_AOV                (FUNC_AOV_DU32 | MOD_OUT_PVG_DU32 | 0x00000002)
#define OUT_36_AOV                (FUNC_AOV_DU32 | MOD_OUT_PVG_DU32 | 0x00000003)

#define OUT_47_AOV                (FUNC_AOV_DU32 | MOD_OUT_AOC_DU32 | 0x00000000)

/*** input digits *******************************/

/* high side moduls */
#define OUT_1_AI                  (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000000)
#define OUT_2_AI                  (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000001)
#define OUT_3_AI                  (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000002)
#define OUT_4_AI                  (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000003)
#define OUT_5_AI                  (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000004)
#define OUT_6_AI                  (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000005)
#define OUT_7_AI                  (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000006)
#define OUT_8_AI                  (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000007)
#define OUT_9_AI                  (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000008)
#define OUT_10_AI                 (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000009)
#define OUT_11_AI                 (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000A)
#define OUT_12_AI                 (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000B)
#define OUT_13_AI                 (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000C)
#define OUT_14_AI                 (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000D)
#define OUT_15_AI                 (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000E)
#define OUT_16_AI                 (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000F)
#define OUT_17_AI                 (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000010)
#define OUT_18_AI                 (FUNC_AI_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000011)

#define OUT_19_AI              (VAR_CUR1_DU32 | FUNC_AI_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000000)
#define OUT_20_AI              (VAR_CUR1_DU32 | FUNC_AI_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000001)
#define OUT_21_AI                              (FUNC_AI_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000002)
#define OUT_22_AI                              (FUNC_AI_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000003)
#define OUT_23_AI                              (FUNC_AI_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000004)
#define OUT_24_AI                              (FUNC_AI_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000005)
#define OUT_25_AI                              (FUNC_AI_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000006)
#define OUT_26_AI                              (FUNC_AI_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000007)
#define OUT_27_AI              (VAR_CUR1_DU32 | FUNC_AI_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000008)
#define OUT_28_AI              (VAR_CUR1_DU32 | FUNC_AI_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000009)
#define OUT_29_AI                              (FUNC_AI_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000A)
#define OUT_30_AI                              (FUNC_AI_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000B)
#define OUT_31_AI                              (FUNC_AI_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000C)
#define OUT_32_AI                              (FUNC_AI_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000D)

/* low side moduls */
#define OUT_37_AI                 (VAR_CUR1_DU32 | FUNC_AI_DU32 | MOD_OUT_POL_EHR_DU32 | 0x00000000)
#define OUT_41_AI                 (VAR_CUR1_DU32 | FUNC_AI_DU32 | MOD_OUT_POL_EHR_DU32 | 0x00000001)

#define OUT_38_AI                 (FUNC_AI_DU32 | MOD_OUT_POL_DU32 | 0x00000000)
#define OUT_39_AI                 (FUNC_AI_DU32 | MOD_OUT_POL_DU32 | 0x00000001)
#define OUT_40_AI                 (FUNC_AI_DU32 | MOD_OUT_POL_DU32 | 0x00000002)
#define OUT_42_AI                 (FUNC_AI_DU32 | MOD_OUT_POL_DU32 | 0x00000003)
#define OUT_43_AI                 (FUNC_AI_DU32 | MOD_OUT_POL_DU32 | 0x00000004)
#define OUT_44_AI                 (FUNC_AI_DU32 | MOD_OUT_POL_DU32 | 0x00000005)
#define OUT_45_AI                 (FUNC_AI_DU32 | MOD_OUT_POL_DU32 | 0x00000006)
#define OUT_46_AI                 (FUNC_AI_DU32 | MOD_OUT_POL_DU32 | 0x00000007)

/*** input current ******************************/

/* high side moduls */
#define OUT_1_PIC                 (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000000)
#define OUT_2_PIC                 (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000001)
#define OUT_3_PIC                 (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000002)
#define OUT_4_PIC                 (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000003)
#define OUT_5_PIC                 (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000004)
#define OUT_6_PIC                 (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000005)
#define OUT_7_PIC                 (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000006)
#define OUT_8_PIC                 (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000007)
#define OUT_9_PIC                 (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000008)
#define OUT_10_PIC                (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000009)
#define OUT_11_PIC                (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000A)
#define OUT_12_PIC                (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000B)
#define OUT_13_PIC                (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000C)
#define OUT_14_PIC                (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000D)
#define OUT_15_PIC                (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000E)
#define OUT_16_PIC                (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x0000000F)
#define OUT_17_PIC                (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000010)
#define OUT_18_PIC                (FUNC_PIC_DU32 | MOD_OUT_POH_VND_DU32 | 0x00000011)

#define OUT_19_PIC            (VAR_CUR1_DU32 | FUNC_PIC_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000000)
#define OUT_20_PIC            (VAR_CUR1_DU32 | FUNC_PIC_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000001)
#define OUT_21_PIC                            (FUNC_PIC_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000002)
#define OUT_22_PIC                            (FUNC_PIC_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000003)
#define OUT_23_PIC                            (FUNC_PIC_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000004)
#define OUT_24_PIC                            (FUNC_PIC_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000005)
#define OUT_25_PIC                            (FUNC_PIC_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000006)
#define OUT_26_PIC                            (FUNC_PIC_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000007)
#define OUT_27_PIC            (VAR_CUR1_DU32 | FUNC_PIC_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000008)
#define OUT_28_PIC            (VAR_CUR1_DU32 | FUNC_PIC_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x00000009)
#define OUT_29_PIC                            (FUNC_PIC_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000A)
#define OUT_30_PIC                            (FUNC_PIC_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000B)
#define OUT_31_PIC                            (FUNC_PIC_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000C)
#define OUT_32_PIC                            (FUNC_PIC_DU32 | MOD_OUT_POH_VND_CS_DU32 | 0x0000000D)

/* low side moduls */
#define OUT_37_PIC               (VAR_CUR1_DU32 | FUNC_PIC_DU32 | MOD_OUT_POL_EHR_DU32 | 0x00000000)
#define OUT_41_PIC               (VAR_CUR1_DU32 | FUNC_PIC_DU32 | MOD_OUT_POL_EHR_DU32 | 0x00000001)

#define OUT_38_PIC                (FUNC_PIC_DU32 | MOD_OUT_POL_DU32 | 0x00000000)
#define OUT_39_PIC                (FUNC_PIC_DU32 | MOD_OUT_POL_DU32 | 0x00000001)
#define OUT_40_PIC                (FUNC_PIC_DU32 | MOD_OUT_POL_DU32 | 0x00000002)
#define OUT_42_PIC                (FUNC_PIC_DU32 | MOD_OUT_POL_DU32 | 0x00000003)
#define OUT_43_PIC                (FUNC_PIC_DU32 | MOD_OUT_POL_DU32 | 0x00000004)
#define OUT_44_PIC                (FUNC_PIC_DU32 | MOD_OUT_POL_DU32 | 0x00000005)
#define OUT_45_PIC                (FUNC_PIC_DU32 | MOD_OUT_POL_DU32 | 0x00000006)
#define OUT_46_PIC                (FUNC_PIC_DU32 | MOD_OUT_POL_DU32 | 0x00000007)


/**************************************************************************************************/
/* safety channels                                                                                */
/**************************************************************************************************/

/*
 * attention:
 * The order is specified by ECU group design!
 */
#define SAFOUT_37_POH             (MODE_POH_DU16 | 0x00)
#define SAFOUT_37_POL             (MODE_POL_DU16 | 0x00)
#define SAFOUT_37_DO              (MODE_DO_DU16  | 0x00)
#define SAFOUT_41_POH             (MODE_POH_DU16 | 0x01)
#define SAFOUT_41_POL             (MODE_POL_DU16 | 0x01)
#define SAFOUT_41_DO              (MODE_DO_DU16  | 0x01)
#define SAFOUT_38_POH             (MODE_POH_DU16 | 0x02)
#define SAFOUT_38_POL             (MODE_POL_DU16 | 0x02)
#define SAFOUT_38_DO              (MODE_DO_DU16  | 0x02)
#define SAFOUT_39_POH             (MODE_POH_DU16 | 0x03)
#define SAFOUT_39_POL             (MODE_POL_DU16 | 0x03)
#define SAFOUT_39_DO              (MODE_DO_DU16  | 0x03)
#define SAFOUT_40_POH             (MODE_POH_DU16 | 0x04)
#define SAFOUT_40_POL             (MODE_POL_DU16 | 0x04)
#define SAFOUT_40_DO              (MODE_DO_DU16  | 0x04)
#define SAFOUT_42_POH             (MODE_POH_DU16 | 0x05)
#define SAFOUT_42_POL             (MODE_POL_DU16 | 0x05)
#define SAFOUT_42_DO              (MODE_DO_DU16  | 0x05)
/* end for RC12-10/30 */

#define SAFOUT_43_POH             (MODE_POH_DU16 | 0x06)
#define SAFOUT_43_POL             (MODE_POL_DU16 | 0x06)
#define SAFOUT_43_DO              (MODE_DO_DU16  | 0x06)
#define SAFOUT_44_POH             (MODE_POH_DU16 | 0x07)
#define SAFOUT_44_POL             (MODE_POL_DU16 | 0x07)
#define SAFOUT_44_DO              (MODE_DO_DU16  | 0x07)
#define SAFOUT_45_POH             (MODE_POH_DU16 | 0x08)
#define SAFOUT_45_POL             (MODE_POL_DU16 | 0x08)
#define SAFOUT_45_DO              (MODE_DO_DU16  | 0x08)
#define SAFOUT_46_POH             (MODE_POH_DU16 | 0x09)
#define SAFOUT_46_POL             (MODE_POL_DU16 | 0x09)
#define SAFOUT_46_DO              (MODE_DO_DU16  | 0x09)
/* end for RC28-14/30 and RC20-10/30 */


/**************************************************************************************************/
/* specials                                                                                       */
/**************************************************************************************************/

/*** power supply modul ***************************************************************************/

/*** defines for cy141/cy320 ********************/

#define SUPPLY_NUM_DU8              9

// VSS (voltage sensor supply): start index and number
#define SUPPLY_VSS_START_DU8        6
#define SUPPLY_VSS_NUM_DU8          3

// common supplies (start index = 0)
#define VB                        (FUNC_VB_DU32        | MOD_SUPPLY_DU32 | 0x00000000)
#define VREF                      (FUNC_VREF_DU32      | MOD_SUPPLY_DU32 | 0x00000001)
#define VG3                       (FUNC_V3V3_EXT_DU32  | MOD_SUPPLY_DU32 | 0x00000002)
#define V12V                      (FUNC_V12V_DU32      | MOD_SUPPLY_DU32 | 0x00000003)
#define VREF_2V54                 (FUNC_VREF_2V54_DU32 | MOD_SUPPLY_DU32 | 0x00000004)
#define VP_1                      (FUNC_VPO_DU32       | MOD_SUPPLY_DU32 | 0x00000005)

#define VSS_1                     (FUNC_VSS5V_DU32     | MOD_SUPPLY_DU32 | 0x00000006)
#define VSS_2                     (FUNC_VSS10V_DU32    | MOD_SUPPLY_DU32 | 0x00000007)
#define VSS_3                     (FUNC_VSS5V_DU32     | MOD_SUPPLY_DU32 | 0x00000008)

/* no connections to ADC */
#define VP_2                      (FUNC_VDO_DU32       | MOD_SUPPLY_DU32 | 0x00000009)


/*** hardware temperature modul *******************************************************************/

#define TEMP_HW_NUM_DU8             2

#define AIT_HW_1                  (FUNC_AIT_DU32 | MOD_TEMP_HW_DU32 | 0x00000000)
#define AIT_HW_2                  (FUNC_AIT_DU32 | MOD_TEMP_HW_DU32 | 0x00000001)


#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _CHANNELS_D

#endif  /* _CHANNELS_H_D */

/* EOF ########################################################################################## */
