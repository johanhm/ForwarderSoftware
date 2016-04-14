//**************************************************************************************************
//
//  FILENAME:    cosRCElibrary.h
//
//  DESCRIPTION:
//! \file        cosRCElibrary.h
//! \brief       RCE CANopen library
//!
//! RCE library modul to handle the RCE functionality as easy as possible. The library can be
//! used by the user to configure, start and stop up to 2 RCE devices.
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   CANopen for RC
//
// FILE VERSION INFORMATION:  $Revision: 1379 $
//                            $Date: 2008-12-08 11:16:40 +0100 (Mo, 08 Dez 2008) $
//                            $Author: wki2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _COSRCELIBRARY_H_
#define _COSRCELIBRARY_H_

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "cosAPItypes.h"

#ifdef _COSRCELIBRARY_
   #define SCOPE
#else
   #define SCOPE extern
#endif   // _COSRCELIBRARY_

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

//! maximum RCE count of the CAnopen system
#define MAX_RCE_COUNT_DU8             16

#define Running_DU8                   0
#define Successful_DU8                1
#define SDOError_DU8                  2
#define InvalidRCE_DU8                3
#define InvalidDevice_DU8             4
#define NMTError_DU8                  5
#define VerificationError_DU8         6
#define InvalidSerial_DU8             7
#define CheckFailed_DU8               8
#define WriteFailed_DU8               9
#define SaveFailed_DU8                10
#define ErrorInputParameter_DU8       11
#define ErrorSettingNodeID_DU8        12
#define ErrorWriteParameterset_DU8    13
#define ErrorWriteOwnParameterset_DU8 14
#define ErrorSaveParameterset_DU8     15
#define ErrorRCENotFound_DU8          16
#define ErrorWrongDevice_DU8          17
#define ActiveRCEError_DU8            18
#define InactiveRCEError_DU8          19
#define InvalidCommand_DU8            20
#define InvalidParameterset_DU8       21

#define NodeNotFound_DU8              253
#define InvalidNode_DU8               254
#define UnknownError_DU8              255

#define InvalidRCE_DU32               0xFFFFFFFE;
#define SDOError_DU32                 0xFFFFFFFF;

#define NEW_RCE_DU8             0
#define INITIALIZED_RCE_DU8     1

// input channels RCE 1
#define RCE_DIG_A1          0x01
#define RCE_DIG_A2          0x02
#define RCE_DIG_A3          0x03
#define RCE_DIG_A4          0x04
#define RCE_DIG_A5          0x05
#define RCE_DIG_A6          0x06
#define RCE_DIG_A7          0x07
#define RCE_DIG_A8          0x08
#define RCE_DIG_A9          0x09
#define RCE_DIG_A10         0x0A
#define RCE_DIG_A11         0x0B
#define RCE_DIG_A12         0x0C
#define RCE_DIG_A13         0x0D
#define RCE_DIG_A14         0x0E
#define RCE_ANA_A6          0x1D
#define RCE_ANA_A7          0x1E
#define RCE_ANA_A1          0x21
#define RCE_ANA_A2          0x22
#define RCE_ANA_A3          0x23
#define RCE_ANA_A4          0x24
#define RCE_ANA_A5          0x25
#define RCE_ANA_A8          0x2B
#define RCE_ANA_A9          0x2C
#define RCE_ANA_A10         0x2D
#define RCE_ANA_A11         0x2E
#define RCE_ANA_A12         0x2F
#define RCE_ANA_A13         0x30
#define RCE_ANA_A14         0x31
#define RCE_ANA_A15         0x32
#define RCE_ANA_A16         0x33
#define RCE_ANA_A17         0x34
#define RCE_FRQ_A1          0x3F
#define RCE_FRQ_A2          0x40

// output channels RCE 1
#define RCE_LED_A1          0xA0
#define RCE_LED_A2          0xA1
#define RCE_PWM_A1          0xA6
#define RCE_PWM_A2          0xA7
#define RCE_PWM_A3          0xA8
#define RCE_PWM_A4          0xA9
#define RCE_PWM_A5          0xAA
#define RCE_PWM_A6          0xAB
#define RCE_PWM_A7          0xAC
#define RCE_PWM_A8          0xAD
#define RCE_PWM_A9          0xAE
#define RCE_PWM_A10         0xAF
#define RCE_PWM_A11         0xB0
#define RCE_PWM_A12         0xB1

// input channels RCE 2
#define RCE_DIG_B1          0x0F
#define RCE_DIG_B2          0x10
#define RCE_DIG_B3          0x11
#define RCE_DIG_B4          0x12
#define RCE_DIG_B5          0x13
#define RCE_DIG_B6          0x14
#define RCE_DIG_B7          0x15
#define RCE_DIG_B8          0x16
#define RCE_DIG_B9          0x17
#define RCE_DIG_B10         0x18
#define RCE_DIG_B11         0x19
#define RCE_DIG_B12         0x1A
#define RCE_DIG_B13         0x1B
#define RCE_DIG_B14         0x1C
#define RCE_ANA_B6          0x1F
#define RCE_ANA_B7          0x20
#define RCE_ANA_B1          0x26
#define RCE_ANA_B2          0x27
#define RCE_ANA_B3          0x28
#define RCE_ANA_B4          0x29
#define RCE_ANA_B5          0x2A
#define RCE_ANA_B8          0x35
#define RCE_ANA_B9          0x36
#define RCE_ANA_B10         0x37
#define RCE_ANA_B11         0x38
#define RCE_ANA_B12         0x39
#define RCE_ANA_B13         0x3A
#define RCE_ANA_B14         0x3B
#define RCE_ANA_B15         0x3C
#define RCE_ANA_B16         0x3D
#define RCE_ANA_B17         0x3E
#define RCE_FRQ_B1          0x41
#define RCE_FRQ_B2          0x42

// output channels RCE 2
#define RCE_LED_B1          0xA2
#define RCE_LED_B2          0xA3
#define RCE_PWM_B1          0xB2
#define RCE_PWM_B2          0xB3
#define RCE_PWM_B3          0xB4
#define RCE_PWM_B4          0xB5
#define RCE_PWM_B5          0xB6
#define RCE_PWM_B6          0xB7
#define RCE_PWM_B7          0xB8
#define RCE_PWM_B8          0xB9
#define RCE_PWM_B9          0xBA
#define RCE_PWM_B10         0xBB
#define RCE_PWM_B11         0xBC
#define RCE_PWM_B12         0xBD

//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.


//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.

//--- RCE USER FUNCTIONS: --------------------------------------------------------------------------

SCOPE uint8 RCE_setParametersetPointer_u8(uint8 DeviceNumber_u8,
                                          const CANopenParameter_ts PHUGE *Parameterset_ps);

SCOPE uint8 RCE_init_u8(uint8 RCENumber_u8,
                        uint8 NodeID_u8,
                        uint32 SerialNumber_u32,
                        boolean Enable_l);

SCOPE uint8 RCE_control_u8(uint8 DeviceNumber_u8,
                           uint8 ControlCommand_u8);

SCOPE sint32 RCE_in_s32(uint8 RCEChannel_u8);

SCOPE void RCE_out(uint8 RCEChannel_u8,
                   sint32 OutputValue_s32);

SCOPE uint8 RCE_checkError_u8(uint8 RCENumber_u8);

SCOPE uint32 RCE_getStatus_u32(uint8 RCENumber_u8,
                               boolean Enable_l);


//**************************************************************************************************

#undef SCOPE
#undef _COSRCELIBRARY_  // reseting definition, prevents double definition of a variable if
                        // includes are nested
#endif  // _COSRCELIBRARY_H_

// EOF #############################################################################################
