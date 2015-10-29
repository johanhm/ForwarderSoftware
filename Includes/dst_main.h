//**************************************************************************************************
//
//  FILENAME:    dst_main.h
//
//  DESCRIPTION:
//! \file        dst_main.h
//! \brief       diagnostic data structures  defines and typedefs
//!
// *************************************************************************************************
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_Plattform
//
// FILE VERSION INFORMATION:  $Revision: 5903 $
//                            $Date: 2013-06-03 13:41:38 +0200 (Mo, 03 Jun 2013) $
//                            $Author: oub2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _DST_MAIN_H_D
#define _DST_MAIN_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"           // standard type definitions

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.
//! the maximum count of function parameters for a function
#define MaxNumberOfListEntries_DU8        ((uint8)(0x10))
//! the maximum count of function parameters for a function
#define MaxFuncParams_DU8                 ((uint8)(0x08))
//! text length of one unit code
#define UnitCodeLength_DU8                ((uint8)(0x08))
//! the maximum string length of a password, must not have a size higher 32!!!
#define PasswordLength_DU8                ((uint8)(0x10))

//! maximum number of languages for some strings like names or descriptions - DO NOT CHANGE!!!
#define NumberOfLanguages_DU8             ((uint8)(0x04))
//! maximum textlength for names or descriptions - DO NOT CHANGE!!!
#define TextLength_DU8                    ((uint8)(0x20))
//! maximum number of parameters in one parameter group - DO NOT CHANGE!!!
#define NumberOfParameters_DU8            ((uint8)(0x08))
//! maximum number of process variables in one process variable group - DO NOT CHANGE!!!
#define NumberOfProcessVariables_DU8      ((uint8)(0x08))
//! maximum number of parameter groups in a menu - DO NOT CHANGE!!!
#define NumberOfParameterGroups_DU8       ((uint8)(0x08))
//! maximum number of default values for one parameter - DO NOT CHANGE!!!
#define NumberOfDefaultValues_DU8         ((uint8)(0x10))

//! number
#define PARA_NUMBER_DU8                   ((uint8)(0x00))
//! switch with two representations ON/OFF
#define PARA_SWITCH_DU8                   ((uint8)(0x04))
//! trimming for poti
#define PARA_TRIMMING_DU8                 ((uint8)(0x05))
//! lerning curve mode
#define PARA_CURVE_DU8                    ((uint8)(0x06))
//! parameter represents a string list
#define PARA_LIST_DU8                     ((uint8)(0x07))
//! analogue value
#define PARA_ANALOG_DU8                   ((uint8)(0x08))
//! function call
#define PARA_FUNCTION_DU8                 ((uint8)(0x09))

//! number
#define PROC_NUMBER_DU8                   ((uint8)(0x00))
//! switch with two representations ON/OFF
#define PROC_SWITCH_DU8                   ((uint8)(0x01))
//! represent as binary number
#define PROC_BINARY_DU8                   ((uint8)(0x02))
//! represent as hexadecimal number
#define PROC_HEXADEZIMAL_DU8              ((uint8)(0x03))
//! represent as bargraph
#define PROC_BARGRAPH_DU8                 ((uint8)(0x04))

//! language flag for the first language
#define DIAG_LANGUAGE0_DU8                ((uint8)(0x00))
//! language flag for the second language
#define DIAG_LANGUAGE1_DU8                ((uint8)(0x01))
//! language flag for the third language
#define DIAG_LANGUAGE2_DU8                ((uint8)(0x02))
//! language flag for fourth language
#define DIAG_LANGUAGE3_DU8                ((uint8)(0x03))

//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.

// PRQA S 5001, 5004 ++
//! the attribute of a process variable can have several meanings specified here
typedef union attr_t
{
   uint16 NumberOfDigits_u16;       // count of digits for hexadecimal or binary view of numbers
   uint16 BargraphMaximum_u16;      // highest shown value (100 percent) of a bargraph
   uint16 PostCommaDigits_u16;      // count of digits after the comma for numbers
   uint8  data_au8[2];              // for diagnosis internal usage
} attr_tu;

//! attribute 1 of a parameter can have several meanings specified here
typedef union attr1_t
{
   sint16 MinValue_s16;             // minimum value for parameter, lower values won't be stored
   uint16 InputChannel_u16;         // input channel identifier for analog values or learn curves
   uint16 ListNumber_u16;           // index of a list for the strings of a list parameter
   uint8  data_au8[2];              // for diagnosis internal usage
} attr1_tu;

//! attribute 2 of a parameter can have several meanings specified here
typedef union attr2_t
{
   sint16 MaxValue_s16;             // minimum value for parameter, higher values won't be stored
   uint16 InputChannel_u16;         // input channel identifier for learn curves
   uint16 ListEntries_u16;          // number of listentries for a list parameter
   uint8  data_au8[2];              // for diagnosis internal usage
} attr2_tu;

//! attribute 3 of a parameter can have several meanings specified here
typedef union attr3_t
{
   uint16 StepWidth_u16;            // step width for in-/decrementing values from the service tool
   uint16 FunctionNumber_u16;       // index of the function for the parametertype function
   uint16 FrequencyRange_u16;       // frequency range used for parametertype learncurve
   uint8  data_au8[2];              // for diagnosis internal usage
} attr3_tu;

//! attribute 4 of a parameter can have several meanings specified here
typedef union attr4_t
{
   sint16 DefaultValue_as16[NumberOfDefaultValues_DU8];
   sint16 AnalogChannel_as16[NumberOfDefaultValues_DU8];
   sint16 Frequency_as16[NumberOfDefaultValues_DU8];
   uint8  data_au8[32];             // for diagnosis internal usage
} attr4_tu;

//! eeprom adress format
typedef  struct EEPROMAdrress_t
{
   uint8 Page_u8;                   // eeprom page
   uint8 IntIndex_u8;               // index in eeprom page
}  __attribute__ ((packed)) EEPROMAdrress_ts;

//! parameter structure
typedef struct Parameter_t
{
   sint8 ParameterName_as8[NumberOfLanguages_DU8][TextLength_DU8];
   uint8 ParameterType_u8;          // parameter type
   attr1_tu attr1_u;                // attribute 1 (see definition above)
   attr2_tu attr2_u;                // attribute 2 (see definition above)
   attr3_tu attr3_u;                // attribute 3 (see definition above)
   uint8 UnitCode_au8[NumberOfLanguages_DU8];   // unit code indices for each language
   sint16 Multiplier_s16;           // multiplier used by service tool to scale the displayed value
   sint16 Divisor_s16;              // divisor used by service tool to scale the displayed value
   uint16 NumberOfDigits_u16;       // count of digits or count of function parameters
   uint8 AccesslevelCode_u8;        // a parameters minimum required acceslevel
   attr4_tu attr4_u;                // attribute 4 (see definition above)
   EEPROMAdrress_ts EEPROMAddress_s;// eeprom address, where the parameter value is to store
}  __attribute__ ((packed)) Parameter_ts;

//! parameter group
typedef struct ParameterGroup_t
{
   sint8 GroupName_as8[NumberOfLanguages_DU8][TextLength_DU8];
   Parameter_ts Param_as[NumberOfParameters_DU8];
}  __attribute__ ((packed)) ParameterGroup_ts;

//! parameter menu
typedef struct ParameterMenu_t
{
   sint8 MenuName_as8[NumberOfLanguages_DU8][TextLength_DU8];
   ParameterGroup_ts ParameterGroup_as[NumberOfParameterGroups_DU8];
}  __attribute__ ((packed)) ParameterMenu_ts;

//! process value
typedef struct ProcessVariable_t
{
   sint8 ProcessVarName_as8[NumberOfLanguages_DU8][TextLength_DU8];
   uint8 ProcVarType_u8;            // processvariable type
   uint8 UnitCode_au8[NumberOfLanguages_DU8];   // unit code indices for each language
   sint16 Multiplier_s16;           // multiplier used by service tool to scale the displayed value
   sint16 Divisor_s16;              // divisor used by service tool to scale the displayed value
   attr_tu attr_u;                  // attribute (see definition above)
   uint8 AccesslevelCode_u8;        // a parameters minimum required acceslevel
}  __attribute__ ((packed)) ProcessVariable_ts;

//! process value group
typedef struct ProcessVariableGroup_t
{
   sint8 GroupName_as8[NumberOfLanguages_DU8][TextLength_DU8];
   ProcessVariable_ts ProcessVariable_as[NumberOfProcessVariables_DU8];
}  __attribute__ ((packed)) ProcessVariableGroup_ts;

//! this is the layout, application errors are described in flash
typedef struct ApplError_t
{
   uint16 Code_u16;
   sint8  Description_as8[NumberOfLanguages_DU8][TextLength_DU8];
}  __attribute__ ((packed)) ApplError_ts;

//! this struct defines the error memory layout for occured errors
typedef struct ErrorEntry_t
{
   uint16 Code_u16;
   uint8  Param_u8;
   uint8  Frequency_u8;
   uint32 TimeStamp_u32;
} ErrorEntry_ts;

//! this structure defines a list entry for parameter type list in flash for text descriptions
typedef struct ParaListEntry_t
{
   sint8  Description_as8[NumberOfLanguages_DU8][TextLength_DU8];
}  __attribute__ ((packed)) ParaListEntry_ts;

//! this structure defines a list entry for parameter type list in flash for text descriptions
typedef struct FuncParams_t
{
   sint8  Description_as8[NumberOfLanguages_DU8][TextLength_DU8];
}  __attribute__ ((packed)) FuncParams_ts;

// PRQA S 5001, 5004 --

//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.

//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.

//**************************************************************************************************

#endif  // _DST_MAIN_H_D

// EOF #############################################################################################
