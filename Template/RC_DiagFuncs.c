//**************************************************************************************************
//
//  FILENAME:    RC_DiagFuncs.c
//
//  DESCRIPTION:
//! \file        RC_DiagFuncs.c
//! \brief       application implemented diagnostic functions
//!
//! the in this module called functions execution can be started by the diagnostic tool
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_Plattform
//
// FILE VERSION INFORMATION:  $Revision: 5235 $
//                            $Date: 2013-01-23 12:21:12 +0100 (Mi, 23 Jan 2013) $
//                            $Author: gtg2si $
//
// REVISION HISTORY:
//
//**************************************************************************************************


//*** include files ********************************************************************************
// List of include files needed in this module.
#include "api_lib_basic.h"

//*** defines **************************************************************************************
// List of defines needed only in this module.

//*** typdefs/structures ***************************************************************************
// Typedefs/structures needed only in this module.

//*** data *****************************************************************************************
// Definitions of variables used only in this module. Memory class "static" has to be used for
// each variable.
// ecu response text for an unknown function
const uint8 FuncErrors_as[4][16] =
{
  // string for lanuage 0
  "Function unknown",
  // string for lanuage 1
  "Funktion unbeka.",
  // string for lanuage 2
  "Fonction inconn.",
  // string for lanuage 3
  "Funcion incogni."
};

//*** prototypes ***********************************************************************************
// Prototypes of functions defined and used only in this module.
// do not change the following two declarations
void diag_ECUFunction(uint16 FunctionIndex_u16,
                      uint8* Param_pau8,
                      uint8* Response_pau8,
                      uint8 Language_u8);
void (*diag_ECUFunction_pf)(uint16 FunctionIndex_u16,
                            uint8* Param_pau8,
                            uint8* Response_pau8,
                            uint8 Language_u8) = diag_ECUFunction;
// declare your functions here
void RC_diagTestFunction(sint16 par1_s16,
                         uint32 par2_u32,
                         uint16 par3_u16,
                         uint8  par4_u8,
                         uint8* Response_pau8);

//**************************************************************************************************


//**************************************************************************************************
// FUNCTION:      diag_ECUFunction_pau8
//
//! \brief        here the application depending ecu functions are called
//!
//! here is the place to implement or to call an application specific function, which can be started
//! by a BODAS-service command
//!
//! \param[in]    FunctionIndex_u16       index to specify, what function is to start
//! \param[in]    Param_pau8              array with optional parameters from the diagnostic tool
//! \param[in]    Language_u8             specify the active controller language
//!
//! \return       ResultString_pau8       string as result for a function execution
//
//**************************************************************************************************

void diag_ECUFunction(uint16 FunctionIndex_u16,
                      uint8* Param_pau8,
                      uint8* Response_pau8,
                      uint8  Language_u8)
{
   uint8 counter_u8;

   // select the requested function by the function index
   switch (FunctionIndex_u16)
   {
      // when function number 0 is requested by the tool
      case 0x0000:
      {
         // call the function with parameters from Param_pau8 and set result string
         RC_diagTestFunction((sint16)(((sint32)Param_pau8[ 0] << 24) |
                                      ((sint32)Param_pau8[ 1] << 16) |
                                      ((sint32)Param_pau8[ 2] <<  8) |
                                      ((sint32)Param_pau8[ 3])),
                             (uint32)(((sint32)Param_pau8[ 4] << 24) |
                                      ((sint32)Param_pau8[ 5] << 16) |
                                      ((sint32)Param_pau8[ 6] <<  8) |
                                      ((sint32)Param_pau8[ 7])),
                             (uint16)(((sint32)Param_pau8[ 8] << 24) |
                                      ((sint32)Param_pau8[ 9] << 16) |
                                      ((sint32)Param_pau8[10] <<  8) |
                                      ((sint32)Param_pau8[11])),
                             (uint8) (((sint32)Param_pau8[12] << 24) |
                                      ((sint32)Param_pau8[13] << 16) |
                                      ((sint32)Param_pau8[14] <<  8) |
                                      ((sint32)Param_pau8[15])),
                             Response_pau8);
         break;
      }
      // when the function is unknown
      default:
      {
        // get the language dependend string to show the user the function is unknown
        for (counter_u8 = 0; counter_u8 < 16; counter_u8++)
        {
          Response_pau8[counter_u8] = FuncErrors_as[Language_u8][counter_u8];
        }
        break;
      }
   }
}

//**************************************************************************************************


//**************************************************************************************************
// FUNCTION:      RC_diagTestFunction_pau8
//
//! \brief        test function for calling an ecu internal function from BODAS-service
//!
//! this function can be called from the diagnostic tool. the can give parameters to the function
//! and the return value is sent to the diagnostic tool after function execution
//!
//! \param[in]    par1_s16       signed integer parameter from dst_parastructure.h
//! \param[in]    par2_u32       unsigned long parameter from dst_parastructure.h
//! \param[in]    par3_u16       unsigned integer parameter from dst_parastructure.h
//! \param[in]    par4_u8        unsigned char parameter from dst_parastructure.h
//!
//! \return       ResultString_pau8       string as result for a function execution
//
//**************************************************************************************************

void RC_diagTestFunction(sint16 par1_s16,
                         uint32 par2_u32,
                         uint16 par3_u16,
                         uint8  par4_u8,
                         uint8* response_pau8)
{
   response_pau8[ 0] = '-';
   response_pau8[ 1] = '-';
   response_pau8[ 2] = '>';
   response_pau8[ 3] = ' ';
   response_pau8[ 4] = (par1_s16 & 0x000F) + 0x30;
   response_pau8[ 5] = (par2_u32 & 0x000F) + 0x30;
   response_pau8[ 6] = (par3_u16 & 0x000F) + 0x30;
   response_pau8[ 7] = (par4_u8  & 0x000F) + 0x30;
   response_pau8[ 8] = ' ';
   response_pau8[ 9] = '<';
   response_pau8[10] = '-';
   response_pau8[11] = '-';
   response_pau8[12] = 'd';
   response_pau8[13] = 'o';
   response_pau8[14] = 'n';
   response_pau8[15] = 'e';
}

//**************************************************************************************************


// EOF #############################################################################################
