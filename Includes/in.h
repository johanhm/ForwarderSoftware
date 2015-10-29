/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        in.h
*
*  \brief       Interface for in.c.
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   RC30 plattform
*
* FILE VERSION INFORMATION:  $Revision: 5910 $
*                            $Date: 2013-06-04 07:55:43 +0200 (Di, 04 Jun 2013) $
*                            $Author: ltm2si $
*
* REVISION HISTORY:
*
*
***************************************************************************************************/

#ifndef _IN_H_D      /* replace it with the filename in capital letters */
#define _IN_H_D      /* replace it with the filename in capital letters */

/**** include files ********************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

#ifdef _IN_D     /* replace it with the filename in capital letters */
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   /* _IN_D */

/**** defines **************************************************************************************
* List of defines needed in this header file and defines to be made available to other modules.   */

#define in_tiMaxStateDebounce_DU16       1000
#define in_tiMaxDiagDebounce_DU16        1000

//--- error codes
#define IN_ERR_NO_ERRORS_DU16            0u
#define IN_ERR_CHNL_DU16                 1u   /* invalid channel */
#define IN_ERR_INVALID_ADDR_DU16         2u   /* invalid address. */
#define IN_ERR_BUF_LEN_DU16              3u   /* invalid buffer length */
#define IN_ERR_PHASE_DU16                4u   /* phase measurement is enabled */
#define IN_ERR_OVERLAP_ADDR_DU16         5u   /* buffer which has to be registered by application
                                               * overlaps with a present buffer registered by
                                               * application. */
#define IN_ERR_REGISTERED_BUF_DU16       6u   /* buffer is not registered */
#define IN_ERR_COPY_DATA_DU16            7u   /* data could not be copied successfully/complete */

/**** typdefs/structures ***************************************************************************
* Typedefs/structures to be made available to other modules.                                      */


/**** public functions *****************************************************************************
* Declarations of functions to be made available to other modules. Use SCOPE_D in front of each    *
* line.                                                                                           */

SCOPE_D void in_setPullup (uint8 group_u8,
                           bool state_l);
SCOPE_D void in_setCurrentMeasurement (uint8 group_u8,
                                       bool state_l);

SCOPE_D void in_setDSM (uint32 chnl_u32,
                        bool state_l);

SCOPE_D void in_cfgVoltageInput (uint32 chnl_u32,
                                 uint16 uLowerStateThreshold_u16,
                                 uint16 uUpperStateThreshold_u16,
                                 uint16 tiStateDebounce_u16,
                                 uint16 uLowerDiagThreshold_u16,
                                 uint16 uUpperDiagThreshold_u16,
                                 uint16 tiDiagDebounce_u16);

SCOPE_D void in_cfgCurrentInput (uint32 chnl_u32,
                                 uint16 tiDiagDebounce_u16);

SCOPE_D void in_cfgDigitalInput (uint32 chnl_u32,
                                 uint16 tiStateDebounce_u16);

SCOPE_D void in_cfgTempSensorType (uint32 chnl_u32,
                                   uint8 sensorType_u8);

SCOPE_D void in_getPhase (uint32 chnl_u32,
                          phaseDep_ts *phaseDep_ps);

SCOPE_D void in_resetPhase (uint32 chnl_u32);
SCOPE_D void in_enablePhase (uint32 chnl_u32);

SCOPE_D uint8 in_getStatus(uint32 chnl_u32);

SCOPE_D sint32 inxt(uint32 chnl_u32,
                    in_ts *in_ps);

SCOPE_D void in_setPeriod(uint32 chnl_u32,
                          uint32 tiSetPeriod_u32,
                          in_fi_per_ts *in_fi_per_ps);

// PRQA S 3453 ++ // function like macro is needed here

// PRQA S 5000 ++
// API functions
/* redefines from the function name */
#define in_getState(CHNL_U32)  in_getStatus(CHNL_U32)
// PRQA S 5000 --


/***************************************************************************************************
*  FUNCTION:      in
*/
/**\brief         This is the macro interface for the old in() function for backward compatibility.
*
* The structure of the inxt() function is close to the inputs. \n
* The inputs could be grouped as following: \n
* DI   (digital input) \n
* AI   (analog input) \n
* AID  (analog input with digital values) \n
* AIV  (analog input with voltage values) \n
* AIC  (analog inputs with current values) \n
* AIT  (analog inputs with temperature values) \n
* FI   (frequency input) \n
* DSM  (frequency input) \n
* PIC  (current inputs) \n
*
* If the application feeds this function with an invalid channel number a user defined callback
* function will be called. In this case the return value will be 0.
*
* \param[in]      chnl_u32      channel number
*
* \return         return_s32    zero in case of a wrong channel number \n
*                               DI    TRUE/FALSE \n
*                               AI    digits (0..16500) \n
*                               AID   TRUE/FALSE \n
*                               AIV   voltage in (mV] \n
*                               AIC   current in [uA] \n
*                               FI    frequency in [1/10 Hz] \n
*                               DSM   [31..24]  state \n
*                                     [23..16]  direction \n
*                                     [00..15]  frequency in [1/10 Hz] \n
*                               PIC   current in [mA] \n
*/
/**************************************************************************************************/

// PRQA S 5000 ++
// API functions
#define in(chnl_u32)    inxt(chnl_u32, (NULL))
// PRQA S 5000 --

// PRQA S 3453 --

/* end of in */

/**************************************************************************************************/



#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _IN_D

#endif  /* _IN_H_D */
