//**************************************************************************************************
//
//  FILENAME:    appl_basicDiag.c
//
//  DESCRIPTION:
//! \file        appl_basicDiag.c
//! \brief       Support of basic diagnostic functions.
//!
//! This module implements some basic diagnostics functions using the UDS protocol.
//! The communication will be initialized with the function basicDiag_initComm(). This function
//! registers an UDS instance and starts the communication. It has to be called within the
//! function sys_main() of the application after the can databoxes have been registered. The
//! BasicDiag needs one free RX databox on the corresponding CAN channel. If further UDS instances
//! are required by the application then the UDS registration within basicDiag_initComm() has to be
//! adapted accordingly. The ecuAddress and the toolAddress must be unique with the CAN network.
//!
//! Example for an initialization of the basic diagnostic:
//!
//! basicDiag_initComm(CAN_2,   // canChannel
//!                    1,       // rxDatabox
//!                    0x55,    // ecuAddr
//!                    0xF0,    // toolAddr
//!                    0,       // priority
//!                    20);     // cycleTime
//!
//! The UDS messages have one of the following formats:
//! - Request message (ServiceTool -> ECU):
//!     Request_SID (8bit), Request_DID (16bit), Request_Data (n x 8bit)
//! - Positve response message (ECU -> ServiceTool):
//!     Response_SID (8bit), Request_DID (16bit), Response_Data (n x 8bit, see below)
//! - Negative response message (ECU -> ServiceTool):
//!     NegResponse_SID (8bit), Request_SID (8bit), ErrorCode (8bit)
//!
//!
//! The following service identifiers (SID) are implemented within this file:
//! Not implemented SIDs and DIDs lead to a negative response message.
//!
//! 1) ReadDataByIdentifier (SID=22)
//! ================================
//! This service supports the following data identifiers (DID)
//!
//! 1.1) Read application name (DID = 0xF182)
//! -----------------------------------------
//! Request_Data:  none
//! Response_Data: Application name with up to 32 bytes in ASCII format and with 0x00 termination.
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    4     03 22 F1 82                ."..
//! 18DAF055x    8     10 15 62 F1 82 54 65 73    ..b..Tes
//! 18DA55F0x    3     30 20 00                   0 .
//! 18DAF055x    8     21 74 70 72 6F 67 72 61    !tprogra
//! 18DAF055x    8     22 6D 6D 20 46 55 4E 43    "mm FUNC
//! 18DAF055x    2     23 00                      #.
//!
//! 1.2) Read serial number (DID = 0xF18C)
//! --------------------------------------
//! Request_Data:  none
//! Response_Data: 32 bit serial number BCD coded, e.g. 0x00001123
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    4     03 22 F1 8C                ."..
//! 18DAF055x    8     07 62 F1 8C 00 00 11 23    .b.....#
//!
//! 1.3) Read hardware type (DID = 0xF192)
//! --------------------------------------
//! Request_Data:  none
//! Response_Data: 16 bit hardware code, e.g. 0x00D6.
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    4     03 22 F1 92                ."..
//! 18DAF055x    6     05 62 F1 92 00 D6          .b....
//!
//! 1.4) Read hardware version number (DID = 0xF193)
//! ------------------------------------------------
//! Request_Data:  none
//! Response_Data: Hardware version number with 12 bytes in ASCII format, e.g. "R917006878  "
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    4     03 22 F1 93                ."..
//! 18DAF055x    8     10 0F 62 F1 93 52 39 31    ..b..R91
//! 18DA55F0x    3     30 20 00                   0 .
//! 18DAF055x    8     21 37 30 30 36 38 37 38    !7006878
//! 18DAF055x    3     22 20 20                   "
//!
//! 1.5) Read parameter data (DID = 0xFD00)
//! ---------------------------------------
//! Request_Data:  1 byte eepromPage, 1 byte eepromIndex
//! Response_Data: 16 bit eeprom data from given page and index.
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    6     05 22 FD 00 05 01          ."....
//! 18DAF055x    6     05 62 FD 00 FF FF          .b....
//!
//! 1.6) Read process data (DID = 0xFD80)
//! -------------------------------------
//! This service reads one or more 32 bit data from the data buffer basicDiagProcData_as32[].
//! Before the basicDiag can send any data from this buffer the application has to copy the
//! corresponding process data using the function basicDiag_setProcessVar().
//! The size of this data buffer is defined with BasicDiagNbrProcData_DU8 and can be changed.
//! But the maximal number of requested process data per request message is limited due to the
//! maximal TX buffer size (BasicDiagTxBuffSize_DU16)! If the response does not fit into the
//! message then a negatives response with error BasicDiagResponseToLong_DU8 (=0x14) will be sent.
//!
//! Request_Data:  1 byte firstIndex, 1 byte lastIndex of process data buffer
//! Response_Data: 32 bit process data per requested index.
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    6     05 22 FD 80 00 01          ."....
//! 18DAF055x    8     10 0B 62 FD 80 00 00 00    ..b.....
//! 18DA55F0x    3     30 20 00                   0 .
//! 18DAF055x    6     21 00 00 00 00 00          !.....
//!
//! 1.7) Read operating hours (DID = 0xFE0B)
//! ----------------------------------------
//! Request_Data:  none
//! Response_Data: 32 bit operation time in minutes, e.g. 0x0000D237.
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    4     03 22 FE 0B                ."..
//! 18DAF055x    8     07 62 FE 0B 00 00 D2 9F    .b......
//!
//! 1.8) Read active errors (DID = 0xFEF0)
//! --------------------------------------
//! Request_Data:  none
//! Response_Data:
//! a) There exist no active erros:
//!    8 bit number of active errors, e.g. 0x00.
//! b) There exist active errors:
//!    8 bit number of active errors, e.g. 0x01.
//!    16 bit error code, 8 bit error parameter,                ) this part will be
//!    8 bit occurance counter, 32 bit operation time stamp     ) repeated per error
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    4     03 22 FE F0                ."..
//! 18DAF055x    8     10 14 62 FE F0 02 03 01    ..b.....
//! 18DA55F0x    3     30 20 00                   0 .
//! 18DAF055x    8     21 07 01 00 00 D2 A0 03    !.......
//! 18DAF055x    8     22 02 08 01 00 00 D2 A0    ".......
//!
//! 1.9) Read saved errors (DID = 0xFEF1)
//! -------------------------------------
//! Request_Data:  none
//! Response_Data:
//! a) There exist no saved erros:
//!    8 bit number of saved errors, e.g. 0x00.
//! b) There exist saved errors:
//!    8 bit number of saved errors, e.g. 0x01.
//!    16 bit error code, 8 bit error parameter,                ) this part will be
//!    8 bit occurance counter, 32 bit operation time stamp     ) repeated per error
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    4     03 22 FE F1                ."..
//! 18DAF055x    8     10 14 62 FE F1 02 03 01    ..b.....
//! 18DA55F0x    3     30 20 00                   0 .
//! 18DAF055x    8     21 07 01 00 00 D2 A0 03    !.......
//! 18DAF055x    8     22 02 08 01 00 00 D2 A0    ".......
//!
//!
//! 2) WriteDataByIdentifier (SID=2E)
//! =================================
//! This service supports the following data identifiers (DID)
//!
//! 2.1) Write parameter data (DID = 0xFD00)
//! ----------------------------------------
//! This service is protected with the seed and key security access mechanism.
//!
//! Request_Data:  1 byte eepromPage, 1 byte eepromIndex
//!                16 bit eeprom data from given page and index.
//! a) Successful execution:
//!    Response_Data: none
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    8     07 2E FD 00 05 01 12 34    .......4
//! 18DAF055x    4     03 6E FD 00                .n..
//!
//! b) Unsuccessful execution due to eeprom writing error:
//!    Negative response with error BasicDiagGeneralReject_DU8 (=0x10)
//! c) Unsuccessful execution due to missing or failed security access:
//!    Negative response with error BasicDiagSecurityAccessDenied_DU8 (=0x33)
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    8     07 2E FD 00 05 01 12 34    .......4
//! 18DAF055x    4     03 7F 2E 33                ...3
//!
//! 2.2) Delete active errors (DID = 0xFEF0)
//! ----------------------------------------
//! Request_Data:  none
//! Response_Data: none
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    4     03 2E FE F0                ....
//! 18DAF055x    4     03 6E FE F0                .n..
//!
//! 2.3) Delete saved errors (DID = 0xFEF1)
//! ---------------------------------------
//! This service is protected with the seed and key security access mechanism.
//!
//! Request_Data:  none
//! a) Successful execution:
//!    Response_Data: none
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    4     03 2E FE F1                ....
//! 18DAF055x    4     03 6E FE F1                .n..
//!
//! b) Unsuccessful execution due to missing or failed security access:
//!    Negative response with error BasicDiagSecurityAccessDenied_DU8 (=0x33)
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    4     03 2E FE F1                ....
//! 18DAF055x    4     03 7F 2E 33                ...3
//!
//!
//! 3) Security access (SID=27)
//! ===========================
//! This service supports the following local identifiers (LID)
//!
//! 3.1) Request seed (LID = 0x05)
//! ------------------------------
//! This service must be called before any key for the security can be send to the ECU.
//!
//! Request_Data:  none.
//! Response_Data: Currently hardcoded ASCII chars from securitySeed_cau8[].
//!                This string has to be replaced by an algorithm from the application.
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    3     02 27 05                   .'.
//! 18DAF055x    8     07 67 05 68 65 6C 6C 6F    .g.hello
//!
//! 3.2) Send key (LID = 0x06)
//! --------------------------
//! This service requires a previously request seed.
//!
//! Request_Data:  Currently hardcoded ASCII chars from securityKey_cau8[].
//!                This string has to be replaced by an algorithm from the application.
//! a) Successful execution:
//!    Response_Data: 1 byte with BasicDiagSecurityAccessAllowed_DU8 (=0x34)
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    8     07 27 06 77 6F 72 6C 64    .'.world
//! 18DAF055x    4     03 67 06 34                .g.4
//!
//! b) Unsuccessful execution due to missing request seed:
//!    Negative response with error BasicDiagRequestSequenceError_DU8 (=0x24)
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    8     07 27 06 77 6F 72 6C 64    .'.world
//! 18DAF055x    4     03 7F 27 24                ..'$
//!
//! c) Unsuccessful execution due to wrong key:
//!    Negative response with error BasicDiagInvalidKey_DU8 (=0x35)
//!
//! Example:
//! ID           DLC   Data                       Data ASCII
//! 18DA55F0x    8     07 27 06 77 6F 72 6C 6C    .'.worll
//! 18DAF055x    4     03 7F 27 35                ..'5
//!
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_Plattform
//
// FILE VERSION INFORMATION:  $Revision: 5233 $
//                            $Date: 2013-01-23 10:44:13 +0100 (Mi, 23 Jan 2013) $
//                            $Author: oub2si $
//
// REVISION HISTORY:
//
//**************************************************************************************************


//*** include files ********************************************************************************
// List of include files needed in this module.
#include "api_lib_basic.h"      // API basic librry
#include "api_lib_eepRc.h"      // API eeprom library
#include "uds_types.h"          // API UDS type definitions
#include "uds_api.h"            // API UDS library

#define _APPL_BASICDIAG_D
#include "appl_basicDiag.h"     // Basic Diagnostics interface

//*** defines **************************************************************************************
// List of defines needed only in this module.

#define MaxNbrUdsInstances_DU8              1
#define BasicDiagUdsInstNbr_DU8             1

#define BasicDiagRxBuffSize_DU16            20        // size for UDS request msg
// The RX buffer size is dependent on the maximal expected request msg.
#define BasicDiagTxBuffSize_DU16            520       // size for UDS response msg
// The TX buffer size is dependent on the maximal expected response msg. Here the longest TX
// msg is the response with up to 64 active or saved system errors: 64 * 8 + 3 = 515 bytes.

// Define some buffer positions within the UDS buffer
#define BasicDiagBuffPosSid_DU16            0
#define BasicDiagBuffPosDidHi_DU16          1
#define BasicDiagBuffPosDidLo_DU16          2
#define BasicDiagBuffPosLid_DU16            1

#define BasicDiagNbrProcData_DU8            10        // nbr of process data variables

// some used UDS error codes
#define BasicDiagNoError_DU8                0x00
#define BasicDiagGeneralReject_DU8          0x10
#define BasicDiagServiceNotSupported_DU8    0x11
#define BasicDiagFunctionNotSupported_DU8   0x12
#define BasicDiagResponseToLong_DU8         0x14
#define BasicDiagRequestSequenceError_DU8   0x24
#define BasicDiagRequestOutOfRange_DU8      0x31
#define BasicDiagSecurityAccessDenied_DU8   0x33
#define BasicDiagSecurityAccessAllowed_DU8  0x34
#define BasicDiagInvalidKey_DU8             0x35

// states for security access
#define BasicDiagKeyInvalid_DU8             0x00
#define BasicDiagKeyExpected_DU8            0x01
#define BasicDiagKeyAccepted_DU8            0x02

//*** typdefs/structures ***************************************************************************
// Typedefs/structures needed only in this module.

//*** data *****************************************************************************************
// Definitions of variables used only in this module. Memory class "static" has to be used for
// each variable.

// allocate memory for the UDS stack
uds_instance_ts udsData_as[MaxNbrUdsInstances_DU8];

// define uds message buffers for 1 instance
uint8 basicDiagRxBuff_au8[BasicDiagRxBuffSize_DU16];
uint8 basicDiagTxBuff_au8[BasicDiagTxBuffSize_DU16];

// define data array for process data
sint32 basicDiagProcData_as32[BasicDiagNbrProcData_DU8];

// variable to control the security access
uint8 basicDiagSecurityControl_u8 = BasicDiagKeyInvalid_DU8;

// constants
const uint8 securitySeed_cau8[] = {'h', 'e', 'l', 'l', 'o'};
const uint8 securityKey_cau8[]  = {'w', 'o', 'r', 'l', 'd'};

//*** prototypes ***********************************************************************************
// Prototypes of functions defined and used only in this module.

//**************************************************************************************************

uint8 basicDiag_main_u8(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps);
uint8 basicDiag_readDataById_u8(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps);
uint8 basicDiag_writeDataById_u8(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps);
uint8 basicDiag_securityAccess_u8(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps);
uint8 basicDiag_getApplName_u8(udsMsg_ts *txUdsMsg_ps);
uint8 basicDiag_getHwType_u8(udsMsg_ts *txUdsMsg_ps);
uint8 basicDiag_getOperatingHours_u8(udsMsg_ts *txUdsMsg_ps);
uint8 basicDiag_getHwVersion_u8(udsMsg_ts *txUdsMsg_ps);
uint8 basicDiag_getSerialNumber_u8(udsMsg_ts *txUdsMsg_ps);
uint8 basicDiag_getProcessData_u8(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps);
uint8 basicDiag_setParam_u8(udsMsg_ts *rxUdsMsg_ps);
uint8 basicDiag_getParam_u8(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps);
uint8 basicDiag_getActiveErrors_u8(udsMsg_ts *txUdsMsg_ps);
uint8 basicDiag_getSavedErrors_u8(udsMsg_ts *txUdsMsg_ps);
uint8 basicDiag_delActiveErrors_u8(void);
uint8 basicDiag_delSavedErrors_u8(void);
uint8 basicDiag_RequestSeed_u8(udsMsg_ts *txUdsMsg_ps);
uint8 basicDiag_SendKey_u8(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps);


//**************************************************************************************************
//! FUNCTION:      basicDiag_main_u8
//
//!\brief         Main function for Basic Diagnostics.
//!
//! This function will be called from the UDS protocol handler to evaluate the basic diagnostics
//! service request. Dependent on the return code of this function the UDS stack sends
//! a positive or negative response.
//!
//!
//!
//!
//!
//!
//!
//! \param[in]    rxUdsMsg_ps   pointer to UDS RX buffer with the service request
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       retCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends neg. response with error = retCode
//
//**************************************************************************************************
uint8 basicDiag_main_u8(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps)
{
  uint8 errCode_u8 = BasicDiagNoError_DU8;  // error code

  // evaluate the requested service id (SID) from first byte of UDS message
  switch (rxUdsMsg_ps->data_au8[BasicDiagBuffPosSid_DU16])
  {
    //==============================================================================================
    // SID = 0x22: READ_DATA_BY_IDENTIFIER
    //==============================================================================================
    case 0x22:
    {
      errCode_u8 = basicDiag_readDataById_u8(rxUdsMsg_ps, txUdsMsg_ps);
      break;
    } // case 0x22

    //==============================================================================================
    // SID = 0x2E: WRITE_DATA_BY_IDENTIFIER
    //==============================================================================================
    case 0x2E:
    {
      errCode_u8 = basicDiag_writeDataById_u8(rxUdsMsg_ps, txUdsMsg_ps);
      break;
    } // case 0x2E

    //==============================================================================================
    // SID = 0x27: SECURITY_ACCESS
    //==============================================================================================
    case 0x27:
    {
      errCode_u8 = basicDiag_securityAccess_u8(rxUdsMsg_ps, txUdsMsg_ps);
      break;
    } // case 0x27

    //==============================================================================================
    // SID unknown: send negative response
    //==============================================================================================
    default:
    {
      errCode_u8 = BasicDiagServiceNotSupported_DU8;
      break;
    }
  } // switch (rxUdsMsg_ps->data_au8[0])
  return errCode_u8;
} //basicDiag_main_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_readDataById_u8
//
//!\brief        Handle diagnosis service ReadDataByIdentifier.
//!
//! This function executes the service ReadDataByIdentifier for all implemented data identifieres.
//!
//! \param[in]    rxUdsMsg_ps   pointer to UDS RX buffer with the service request
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_readDataById_u8(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps)
{
  uint16 did_u16;                           // data identifier
  uint8  errCode_u8 = BasicDiagNoError_DU8;

  // prepare positive response data, SID already inserted by the UDS stack at index 0,
  // reflect the DID within the response msg at Index 1 and 2
  txUdsMsg_ps->data_au8[BasicDiagBuffPosDidHi_DU16] =
    rxUdsMsg_ps->data_au8[BasicDiagBuffPosDidHi_DU16];
  txUdsMsg_ps->data_au8[BasicDiagBuffPosDidLo_DU16] =
    rxUdsMsg_ps->data_au8[BasicDiagBuffPosDidLo_DU16];

  // get data identifier (DID) from second byte and third byte of UDS message
  did_u16 = ((uint16)rxUdsMsg_ps->data_au8[BasicDiagBuffPosDidHi_DU16] << 8) +
             rxUdsMsg_ps->data_au8[BasicDiagBuffPosDidLo_DU16];

  // evaluate the received data identifier (DID)
  switch (did_u16)
  {
    //------------------------------------------------------------------------------------------
    // DID = 0xF182: read application name
    //------------------------------------------------------------------------------------------
    case 0xF182:
    {
      errCode_u8 = basicDiag_getApplName_u8(txUdsMsg_ps);
      break;
    }

    //------------------------------------------------------------------------------------------
    // DID = 0xF18C: read serial number
    //------------------------------------------------------------------------------------------
    case 0xF18C:
    {
      errCode_u8 = basicDiag_getSerialNumber_u8(txUdsMsg_ps);
      break;
    }

    //------------------------------------------------------------------------------------------
    // DID = 0xF192: read hardware type
    //------------------------------------------------------------------------------------------
    case 0xF192:
    {
      errCode_u8 = basicDiag_getHwType_u8(txUdsMsg_ps);
      break;
    }

    //------------------------------------------------------------------------------------------
    // DID = 0xF193: read hardware version (SAP number)
    //------------------------------------------------------------------------------------------
    case 0xF193:
    {
      errCode_u8 = basicDiag_getHwVersion_u8(txUdsMsg_ps);
      break;
    }

    //------------------------------------------------------------------------------------------
    // DID = 0xFD00: read parameter data
    //------------------------------------------------------------------------------------------
    case 0xFD00:
    {
      errCode_u8 = basicDiag_getParam_u8(rxUdsMsg_ps, txUdsMsg_ps);
      break;
    }

    //------------------------------------------------------------------------------------------
    // DID = 0xFD80: read process data
    //------------------------------------------------------------------------------------------
    case 0xFD80:
    {
      errCode_u8 = basicDiag_getProcessData_u8(rxUdsMsg_ps, txUdsMsg_ps);
      break;
    }

    //------------------------------------------------------------------------------------------
    // DID = 0xFE0B: read operating hours
    //------------------------------------------------------------------------------------------
    case 0xFE0B:
    {
      errCode_u8 = basicDiag_getOperatingHours_u8(txUdsMsg_ps);
      break;
    }

    //------------------------------------------------------------------------------------------
    // DID = 0xFEF0: read active errors
    //------------------------------------------------------------------------------------------
    case 0xFEF0:
    {
      errCode_u8 = basicDiag_getActiveErrors_u8(txUdsMsg_ps);
      break;
    }

    //------------------------------------------------------------------------------------------
    // DID = 0xFEF1: read saved errors
    //------------------------------------------------------------------------------------------
    case 0xFEF1:
    {
      errCode_u8 = basicDiag_getSavedErrors_u8(txUdsMsg_ps);
      break;
    }

    //------------------------------------------------------------------------------------------
    // DID unknown: send negative response
    //------------------------------------------------------------------------------------------
    default:
    {
      errCode_u8 = BasicDiagFunctionNotSupported_DU8;
      break;
    }
  } // switch (did_u16)

  return errCode_u8;
} // basicDiag_readDataById_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_writeDataById_u8
//
//!\brief        Handle diagnosis service WriteDataByIdentifier.
//!
//! This function executes the service WriteDataByIdentifier for all implemented data identifieres.
//!
//! \param[in]    rxUdsMsg_ps   pointer to UDS RX buffer with the service request
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_writeDataById_u8(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps)
{
  uint16 did_u16;                           // data identifier
  uint8  errCode_u8 = BasicDiagNoError_DU8;

  // prepare positive response data, SID already inserted by the UDS stack at index 0,
  // reflect the DID within the response msg at Index 1 and 2
  txUdsMsg_ps->data_au8[BasicDiagBuffPosDidHi_DU16] =
    rxUdsMsg_ps->data_au8[BasicDiagBuffPosDidHi_DU16];
  txUdsMsg_ps->data_au8[BasicDiagBuffPosDidLo_DU16] =
    rxUdsMsg_ps->data_au8[BasicDiagBuffPosDidLo_DU16];
  txUdsMsg_ps->DLC_u16 = 3;

  // get data identifier (DID) from second byte and third byte of UDS message
  did_u16 = (((uint16)rxUdsMsg_ps->data_au8[BasicDiagBuffPosDidHi_DU16] << 8) +
              rxUdsMsg_ps->data_au8[BasicDiagBuffPosDidLo_DU16]);

  switch (did_u16)
  {
    //------------------------------------------------------------------------------------------
    // DID = 0xFD00: write parameter data
    //------------------------------------------------------------------------------------------
    case 0xFD00:
    {
      errCode_u8 = basicDiag_setParam_u8(rxUdsMsg_ps);
      break;
    }

    //------------------------------------------------------------------------------------------
    // DID = 0xFEF0: delete active errors
    //------------------------------------------------------------------------------------------
    case 0xFEF0:
    {
      errCode_u8 = basicDiag_delActiveErrors_u8();
      break;
    }

    //------------------------------------------------------------------------------------------
    // DID = 0xFEF1: delete saved errors
    //------------------------------------------------------------------------------------------
    case 0xFEF1:
    {
      errCode_u8 = basicDiag_delSavedErrors_u8();
      break;
    }

    //------------------------------------------------------------------------------------------
    // DID unknown: send negative response
    //------------------------------------------------------------------------------------------
    default:
    {
      errCode_u8 = BasicDiagFunctionNotSupported_DU8;
      break;
    }

  } // switch (did_u16)

  return errCode_u8;
} // basicDiag_writeDataById_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_securityAccess_u8
//
//!\brief        Handle diagnosis service SecurityAccess.
//!
//! This function executes all functions of the service SecurityAccess.
//!
//! \param[in]    rxUdsMsg_ps   pointer to UDS RX buffer with the service request
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_securityAccess_u8(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps)
{
  uint8  errCode_u8 = BasicDiagNoError_DU8;

  // prepare positive response data, SID already inserted by the UDS stack at index 0,
  // reflect the LID within the response msg at Index 1
  txUdsMsg_ps->data_au8[BasicDiagBuffPosLid_DU16] = rxUdsMsg_ps->data_au8[BasicDiagBuffPosLid_DU16];

  // evaluate the requested local id (LID) from second byte of UDS message
  switch (rxUdsMsg_ps->data_au8[BasicDiagBuffPosLid_DU16])
  {
    //------------------------------------------------------------------------------------------
    // LID = 0x05: Request Seed
    //------------------------------------------------------------------------------------------
    case 0x05:
    {
      errCode_u8 = basicDiag_RequestSeed_u8(txUdsMsg_ps);
      break;
    }

    //------------------------------------------------------------------------------------------
    // LID = 0x06: Send Key
    //------------------------------------------------------------------------------------------
    case 0x06:
    {
      errCode_u8 = basicDiag_SendKey_u8(rxUdsMsg_ps, txUdsMsg_ps);
      break;
    }

    //------------------------------------------------------------------------------------------
    // LID unknown: send negative response
    //------------------------------------------------------------------------------------------
    default:
    {
      errCode_u8 = BasicDiagFunctionNotSupported_DU8;
      break;
    }
  }

  return errCode_u8;
} // basicDiag_securityAccess_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_getApplName_u8
//
//!\brief        Get the software application name.
//!
//! This function gets the software application name from the system and copies it into the
//! UDS response buffer.
//!
//! Remark:
//! If the application uses a constant for the application name within the function call
//! sys_init() then alternatively this constant can be used to get the application name for
//! the basicDiag. In this case the eeprom access is not required and the string of the constant
//! can be used here.
//!
//! Response format: up to 32 ASCII chars, terminated with an additional null byte.
//!
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_getApplName_u8(udsMsg_ts *txUdsMsg_ps)
{
  uint8  errCode_u8 = BasicDiagNoError_DU8;
  uint16 retCode_u16;
  uint16 copiedBytes_u16;

  retCode_u16 = sys_getVersion(VERSION_SW_PART_APPL_DU8,    // request application name
                               &txUdsMsg_ps->data_au8[3],   // ptr to first free UDS buffer position
                               32,                          // max expected string length
                               &copiedBytes_u16);           // returns the actual string length

  // check for succ. execution of system function
  if (SYSGETVERSION_OK_DU16 == retCode_u16)
  {
    // add a 0x00 as string termination
    txUdsMsg_ps->data_au8[copiedBytes_u16 + 3] = 0x00;

    // set the total length of the UDS response msg
    txUdsMsg_ps->DLC_u16 = (uint8)copiedBytes_u16 + 4;
  }
  else
  {
    errCode_u8 = BasicDiagGeneralReject_DU8;
  }
  return errCode_u8;
} // basicDiag_getApplName_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_getHwType_u8
//
//!\brief        Get the hardware type
//!
//! This function gets the hardware type from the system and copies it into the
//! UDS response buffer.
//! Response format: 16 bit number.
//!
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_getHwType_u8(udsMsg_ts *txUdsMsg_ps)
{
  uint8  errCode_u8 = BasicDiagNoError_DU8;
  uint16 retCode_u16;
  EcuInfo_ts EcuInfo_s;

  retCode_u16 = sys_getEcuInfo(&EcuInfo_s);

  // check for succ. execution of system function
  if (0 == retCode_u16)
  {
    // copy HW type, MSB first
    txUdsMsg_ps->data_au8[3] = (uint8)(EcuInfo_s.HwType_u16 >> 8);  //MSB
    txUdsMsg_ps->data_au8[4] = (uint8)(EcuInfo_s.HwType_u16);       //LSB

    // set the total length of the UDS response msg
    txUdsMsg_ps->DLC_u16 = 5;
  }
  else
  {
    errCode_u8 = BasicDiagGeneralReject_DU8;
  }
  return errCode_u8;
} // basicDiag_getHwType_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_getOperatingHours_u8
//
//!\brief        Get the operating hours counter.
//!
//! This function gets the operating hours counter from the system and copies it into the
//! UDS response buffer.
//! Response format: 32 bit number.
//!
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_getOperatingHours_u8(udsMsg_ts *txUdsMsg_ps)
{
  uint8  errCode_u8 = BasicDiagNoError_DU8;
  uint32 opHours_u32;

  opHours_u32 = sys_getAge();

  // copy operating hours type, MSB first
  txUdsMsg_ps->data_au8[3] = (uint8)(opHours_u32 >> 24);  //MSB
  txUdsMsg_ps->data_au8[4] = (uint8)(opHours_u32 >> 16);
  txUdsMsg_ps->data_au8[5] = (uint8)(opHours_u32 >> 8);
  txUdsMsg_ps->data_au8[6] = (uint8)opHours_u32;          //LSB

  // set the total length of the UDS response msg
  txUdsMsg_ps->DLC_u16 = 7;
  return errCode_u8;
} // basicDiag_getOperatingHours_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_getHwVersion_u8
//
//!\brief        Get the hardware version.
//!
//! This function gets the hardware version SAP number from the system and copies it into the
//! UDS response buffer.
//! Response format: 12 ASCII chars.
//!
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_getHwVersion_u8(udsMsg_ts *txUdsMsg_ps)
{
  uint8 i;
  uint8  errCode_u8 = BasicDiagNoError_DU8;
  uint16 retCode_u16;
  EcuInfo_ts EcuInfo_s;

  retCode_u16 = sys_getEcuInfo(&EcuInfo_s);

  // check for succ. execution of system function
  if (0 == retCode_u16)
  {
    // copy HW number to buffer position index 3
    for (i = 0; i < 12; i++)
    {
      txUdsMsg_ps->data_au8[i + 3] = EcuInfo_s.IdNr_BR_au8[i];
    }

    // set the total length of the UDS response msg
    txUdsMsg_ps->DLC_u16 = 15;
  }
  else
  {
    errCode_u8 = BasicDiagGeneralReject_DU8;
  }
  return errCode_u8;
} // basicDiag_getHwVersion_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_getSerialNumber_u8
//
//!\brief        Get the serial number.
//!
//! This function gets the ECU serial number from the system and copies it into the
//! UDS response buffer.
//! Response format: 32 bit number, BCD coded.
//!
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_getSerialNumber_u8(udsMsg_ts *txUdsMsg_ps)
{
  uint8 i;
  uint8  errCode_u8 = BasicDiagNoError_DU8;
  uint16 retCode_u16;
  EcuInfo_ts EcuInfo_s;

  retCode_u16 = sys_getEcuInfo(&EcuInfo_s);

  // check for succ. execution of system function
  if (0 == retCode_u16)
  {
    // copy serial number to buffer position index 3
    for (i = 0; i < 4; i++)
    {
      txUdsMsg_ps->data_au8[i + 3] = EcuInfo_s.SerialNr_au8[i];
    }

    // set the total length of the UDS response msg
    txUdsMsg_ps->DLC_u16 = 7;
  }
  else
  {
    errCode_u8 = BasicDiagGeneralReject_DU8;
  }
  return errCode_u8;
} // basicDiag_getSerialNumber_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_getProcessData_u8
//
//!\brief        Get process data.
//!
//! This function reads one or more process data variables and copies it into the UDS response
//! buffer. The process data have to be set first with the function basicDiag_setProcessVar()
//! before it can be read with this service.
//! The UDS request msg must contain an index range (firstIdx, lastIdx) for the process data to
//! be read. Possible values for firstIdx and lastIdx: 0...(BasicDiagNbrProcData_DU8 - 1)
//! Response format: 32 bit number per requested process data.
//!
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_getProcessData_u8(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps)
{
  uint8  idx_u8;
  uint8  firstIdx_u8;
  uint8  lastIdx_u8;
  uint16 buffPos_u16 = 3;                        // set buffer start position for data
  uint8  errCode_u8 = BasicDiagNoError_DU8;

  // get index of first and last process data to be read
  firstIdx_u8 = rxUdsMsg_ps->data_au8[3];
  lastIdx_u8  = rxUdsMsg_ps->data_au8[4];

  // check range of the requested process data indices
  if ((firstIdx_u8 > lastIdx_u8) ||
      (firstIdx_u8 >= BasicDiagNbrProcData_DU8) ||
      (lastIdx_u8 >= BasicDiagNbrProcData_DU8))
  {
    errCode_u8 = BasicDiagRequestOutOfRange_DU8;
  }

  //check whether the response message fits into the response buffer
  else if (((lastIdx_u8 - firstIdx_u8 + 1) * 4 + buffPos_u16)  > BasicDiagTxBuffSize_DU16)
  {
    errCode_u8 = BasicDiagResponseToLong_DU8;
  }

  else
  {
    // copy requested process data into UDS buffer
    for (idx_u8 = firstIdx_u8; idx_u8 <= lastIdx_u8; idx_u8++)
    {
      txUdsMsg_ps->data_au8[buffPos_u16] = (uint8)(basicDiagProcData_as32[idx_u8] >> 24); //MSB
      buffPos_u16++;
      txUdsMsg_ps->data_au8[buffPos_u16] = (uint8)(basicDiagProcData_as32[idx_u8] >> 16);
      buffPos_u16++;
      txUdsMsg_ps->data_au8[buffPos_u16] = (uint8)(basicDiagProcData_as32[idx_u8] >> 8);
      buffPos_u16++;
      txUdsMsg_ps->data_au8[buffPos_u16] = (uint8)(basicDiagProcData_as32[idx_u8]);       //LSB
      buffPos_u16++;
    }

    // set the total length of the UDS response msg
    txUdsMsg_ps->DLC_u16 = buffPos_u16;
  }
  return errCode_u8;
} // basicDiag_getProcessData_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_setParam_u8
//
//!\brief        Write one parameter into EEPROM.
//!
//! This function writes one 16 bit parameter value into the EEPROM.
//!
//! \param[in]    rxUdsMsg_ps   pointer to UDS RX buffer with the service request
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       retCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends neg. response with error = retCode
//
//**************************************************************************************************
uint8 basicDiag_setParam_u8(udsMsg_ts *rxUdsMsg_ps)
{
  uint8  page_u8;
  uint8  idx_u8;
  sint16 value_s16;
  sint16 ee_result_s16;
  uint8  errCode_u8 = BasicDiagNoError_DU8;

  // check the security access level
  if (basicDiagSecurityControl_u8 != FALSE)
  {
    // get parameter from UDS buffer
    page_u8   = rxUdsMsg_ps->data_au8[3];
    idx_u8    = rxUdsMsg_ps->data_au8[4];
    value_s16 = ((uint16)rxUdsMsg_ps->data_au8[5] << 8) + rxUdsMsg_ps->data_au8[6];

    // write parameter into EEPROM
    ee_result_s16 = ee_saveValue(page_u8, idx_u8, value_s16);

    // check execution status of API function
    if (ee_result_s16 != 0)
    {
      errCode_u8 = BasicDiagGeneralReject_DU8;
    }
  }

  else
  {
    // negative response
    errCode_u8 = BasicDiagSecurityAccessDenied_DU8;
  }

  return errCode_u8;
} // basicDiag_setParam_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_getParam_u8
//
//!\brief        Read one parameter from EEPROM.
//!
//! This function reads one 16 bit parameter value from the EEPROM mirror.
//!
//! \param[in]    rxUdsMsg_ps   pointer to UDS RX buffer with the service request
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       retCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends neg. response with error = retCode
//
//**************************************************************************************************
uint8 basicDiag_getParam_u8(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps)
{
  uint8  page_u8;
  uint8  idx_u8;
  sint16 value_s16;
  uint8  errCode_u8 = BasicDiagNoError_DU8;

  // get parameter from UDS buffer
  page_u8   = rxUdsMsg_ps->data_au8[3];
  idx_u8    = rxUdsMsg_ps->data_au8[4];

  // read parameter data from EEPROM mirror
  value_s16 = ree_getValue(page_u8, idx_u8);

  // copy requested data into UDS buffer
  txUdsMsg_ps->data_au8[3] = (uint8)(value_s16 >> 8);   //MSB
  txUdsMsg_ps->data_au8[4] = (uint8)value_s16;          //LSB

  // set the total length of the UDS response msg
  txUdsMsg_ps->DLC_u16 = 5;

  return errCode_u8;
} // basicDiag_getParam_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_getActiveErrors_u8
//
//!\brief        Get the active errors.
//!
//! This function gets the list of active errors from the system and copies it into the
//! UDS response buffer.
//! Response format: 8 bit number of errors + list of errors.
//! Error format:    16 Bit error nbr, 8 bit err. param., 8 bit occurance counter, 32 bit time stamp
//!
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_getActiveErrors_u8(udsMsg_ts *txUdsMsg_ps)
{
  #define maxNbrErrors_DU8 64
  uint8 i;
  uint8 errCode_u8 = BasicDiagNoError_DU8;
  uint16 nbrErr_u16;
  ErrorData_ts errors_as[maxNbrErrors_DU8];

  nbrErr_u16 = sys_getActiveErrors(errors_as, 0, maxNbrErrors_DU8);

  // copy the nbr of errors to buffer position index 3
  txUdsMsg_ps->data_au8[3] = (uint8)nbrErr_u16;

  // copy the error list to buffer position index 4
  for (i = 0; i < nbrErr_u16; i++)
  {
    txUdsMsg_ps->data_au8[(i * 8) + 4]  = (uint8)(errors_as[i].Code_u16 >> 8);   //MSB of error code
    txUdsMsg_ps->data_au8[(i * 8) + 5]  = (uint8)errors_as[i].Code_u16;          //LSB of error code
    txUdsMsg_ps->data_au8[(i * 8) + 6]  = errors_as[i].Param_u8;
    txUdsMsg_ps->data_au8[(i * 8) + 7]  = errors_as[i].Occurrence_u8;
    txUdsMsg_ps->data_au8[(i * 8) + 8]  = (uint8)(errors_as[i].Timestamp_u32 >> 24);   //MSB of time
    txUdsMsg_ps->data_au8[(i * 8) + 9]  = (uint8)(errors_as[i].Timestamp_u32 >> 16);
    txUdsMsg_ps->data_au8[(i * 8) + 10] = (uint8)(errors_as[i].Timestamp_u32 >> 8);
    txUdsMsg_ps->data_au8[(i * 8) + 11] = (uint8)errors_as[i].Timestamp_u32;           //LSB of time
  }

  // set the total length of the UDS response msg
  txUdsMsg_ps->DLC_u16 = (nbrErr_u16 * 8) + 4;
  return errCode_u8;
} // basicDiag_getActiveErrors_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_getSavedErrors_u8
//
//!\brief        Get the saved errors.
//!
//! This function gets the list of saved errors from the system and copies it into the
//! UDS response buffer.
//! Response format: 8 bit number of errors + list of errors.
//! Error format:    16 Bit error nbr, 8 bit err. param., 8 bit occurance counter, 32 bit time stamp
//!
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_getSavedErrors_u8(udsMsg_ts *txUdsMsg_ps)
{
  #define maxNbrErrors_DU8 64
  uint8 i;
  uint8 errCode_u8 = BasicDiagNoError_DU8;
  uint16 nbrErr_u16;
  ErrorData_ts errors_as[maxNbrErrors_DU8];

  nbrErr_u16 = sys_getSavedErrors(errors_as, 0, maxNbrErrors_DU8);

  // copy the nbr of errors to buffer position index 3
  txUdsMsg_ps->data_au8[3] = (uint8)nbrErr_u16;

  // copy the error list to buffer position index 4
  for (i = 0; i < nbrErr_u16; i++)
  {
    txUdsMsg_ps->data_au8[(i * 8) + 4]  = (uint8)(errors_as[i].Code_u16 >> 8);   //MSB of error code
    txUdsMsg_ps->data_au8[(i * 8) + 5]  = (uint8)errors_as[i].Code_u16;          //LSB of error code
    txUdsMsg_ps->data_au8[(i * 8) + 6]  = errors_as[i].Param_u8;
    txUdsMsg_ps->data_au8[(i * 8) + 7]  = errors_as[i].Occurrence_u8;
    txUdsMsg_ps->data_au8[(i * 8) + 8]  = (uint8)(errors_as[i].Timestamp_u32 >> 24);   //MSB of time
    txUdsMsg_ps->data_au8[(i * 8) + 9]  = (uint8)(errors_as[i].Timestamp_u32 >> 16);
    txUdsMsg_ps->data_au8[(i * 8) + 10] = (uint8)(errors_as[i].Timestamp_u32 >> 8);
    txUdsMsg_ps->data_au8[(i * 8) + 11] = (uint8)errors_as[i].Timestamp_u32;           //LSB of time
  }

  // set the total length of the UDS response msg
  txUdsMsg_ps->DLC_u16 = (nbrErr_u16 * 8) + 4;
  return errCode_u8;
} // basicDiag_getSavedErrors_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_delActiveErrors_u8
//
//!\brief        Delete the active errors.
//!
//! This function delets the list of active errors from the system.
//!
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_delActiveErrors_u8(void)
{
  uint8 errCode_u8 = BasicDiagNoError_DU8;

  sys_delActiveErrors();

  return errCode_u8;
} // basicDiag_delActiveErrors_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_delSavedErrors_u8
//
//!\brief        Delete the saved errors.
//!
//! This function delets the list of saved errors from the system.
//! For this service a security access is required.
//!
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_delSavedErrors_u8(void)
{
  uint8 errCode_u8 = BasicDiagNoError_DU8;

  // check the security access level
  if (basicDiagSecurityControl_u8 != FALSE)
  {
    sys_delSavedErrors();
  }

  else
  {
    // negative response
    errCode_u8 = BasicDiagSecurityAccessDenied_DU8;
  }

  return errCode_u8;
} // basicDiag_delSavedErrors_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_RequestSeed_u8
//
//!\brief        Request a seed for the security access.
//!
//! This function generates a seed for the security access mechanism and copies it into the
//! UDS response buffer.
//! Response format: ASCII string, may be changed according customer requirements.
//!
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_RequestSeed_u8(udsMsg_ts *txUdsMsg_ps)
{
  uint8 i;
  uint8 errCode_u8 = BasicDiagNoError_DU8;

  // -----------------------------------------------------------------------------------------------
  // Here normally the seed should be generated by a customer specific algorithm.
  // In this example the seed is hard coded as an ASCII string within securitySeed_cau8[].
  // -----------------------------------------------------------------------------------------------

  // copy seed at buffer position index 2
  for (i = 0; i < sizeof(securitySeed_cau8); i++)
  {
    txUdsMsg_ps->data_au8[i + 2] = securitySeed_cau8[i];
  }

  txUdsMsg_ps->DLC_u16 = sizeof(securitySeed_cau8) + 2;

  // change the security status to wait for the corresponding key
  basicDiagSecurityControl_u8 = BasicDiagKeyExpected_DU8;

  return errCode_u8;
} // basicDiag_RequestSeed_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_SendKey_u8
//
//!\brief        Evaluae the sent key.
//!
//! This function evaluates the key for the security access mechanism which was sent by the
//! diagnosis tool.
//!
//! \param[in]    rxUdsMsg_ps   pointer to UDS RX buffer with the service request
//! \param[in]    txUdsMsg_ps   pointer to UDS TX buffer for the response msg
//! \return       errCode_u8    =0: succ. execution, UDS stack sends positive response
//!                             >0: not succ., UDS stack sends negative response with this error
//
//**************************************************************************************************
uint8 basicDiag_SendKey_u8(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps)
{
  uint8 i = 0;
  uint8 errCode_u8 = BasicDiagNoError_DU8;

  // check whether the seed was previously requested
  if (BasicDiagKeyExpected_DU8 == basicDiagSecurityControl_u8)
  {
    // ---------------------------------------------------------------------------------------------
    // Here normally the reference key for the comparision has to be calculated from the
    // seed by a customer specific algorithm.
    // In this example the expected key is hard coded as an ASCII string within securityKey_cau8[].
    // ---------------------------------------------------------------------------------------------

    // check length of received key string
    if (sizeof(securityKey_cau8) != (rxUdsMsg_ps->DLC_u16 - 2))
    {
      errCode_u8 = BasicDiagInvalidKey_DU8;
    }

    // check contents of key string
    while ((BasicDiagNoError_DU8 == errCode_u8) &&
           (i < sizeof(securityKey_cau8)) && (i < (BasicDiagRxBuffSize_DU16 - 2)))
    {
      if (rxUdsMsg_ps->data_au8[i + 2] != securityKey_cau8[i])
      {
        errCode_u8 = BasicDiagInvalidKey_DU8;
      }
      i++;
    }
  }

  else
  {
    // this is an invalid sequence of the services: a key was received before a seed request
    errCode_u8 = BasicDiagRequestSequenceError_DU8;
  }

  // check for correct received and expected key
  if (BasicDiagNoError_DU8 == errCode_u8)
  {
    // change the security status to allow the functions with security access
    basicDiagSecurityControl_u8 = BasicDiagKeyAccepted_DU8;

    // prepare positive response
    txUdsMsg_ps->data_au8[2] = BasicDiagSecurityAccessAllowed_DU8;
    txUdsMsg_ps->DLC_u16 = 3;
  }
  else
  {
    // reset the security status to force a new seed request
    basicDiagSecurityControl_u8 = BasicDiagKeyInvalid_DU8;
  }

  return errCode_u8;
} // basicDiag_SendKey_u8


//**************************************************************************************************
//! FUNCTION:      basicDiag_setProcessVar
//
//!\brief        Transfer process data to the basic diagnostics module.
//!
//! This function copies one 32 bit process data into the buffer of the basic diagnostic module.
//!
//! \param[in]    procIdx_u8    index of process data buffer (0..BasicDiagNbrProcData_DU8 - 1)
//! \param[in]    value_s32     process data value
//
//**************************************************************************************************
void basicDiag_setProcessVar(uint8 procIdx_u8, sint32 value_s32)
{
  // check range of the process data index
  if (procIdx_u8 < BasicDiagNbrProcData_DU8)
  {
    // copy process data into diagnostic buffer
    basicDiagProcData_as32[procIdx_u8] = value_s32;
  }
} // basicDiag_setProcessVar


//**************************************************************************************************
//! FUNCTION:      basicDiag_initComm
//
//!\brief        Initialize the communication for the basic diagnoctic.
//!
//! This function .
//!
//! \param[in]    canChnl_u8      can channel
//! \param[in]    rxDatabox_u16   RX databox number for the UDS communication
//! \param[in]    ecuAddr_u8      ECU address
//! \param[in]    toolAddr_u8     tool address
//! \param[in]    priority_u8     priority of the UDS communication task
//! \param[in]    cycleTime_u8    cycle time of the UDS communication task
//
//**************************************************************************************************
void basicDiag_initComm(uint8 canChnl_u8, uint16 rxDatabox_u16, uint8 ecuAddr_u8,
                        uint8 toolAddr_u8, uint8 priority_u8, uint8 cycleTime_u8)
{
  // register memory for the uds instance
  uds_registerInstances(udsData_as, MaxNbrUdsInstances_DU8);

  // register UDS callback functions for this instance
  uds_registerRxCallback(BasicDiagUdsInstNbr_DU8, basicDiag_main_u8);

  // optional register UDS error callback functions for run time errors
  // uds_registerErrorCallback(1, udsErrCallback1); // instance 1

  // register UDS rx and tx message buffers, which are defined above
  uds_registerBuffers(BasicDiagUdsInstNbr_DU8,    // instance nbr
                      basicDiagRxBuff_au8,        // pointer to rx buffer
                      BasicDiagRxBuffSize_DU16,   // size of rx buffer
                      basicDiagTxBuff_au8,        // pointer to tx buffer
                      BasicDiagTxBuffSize_DU16);  // size of tx buffer

  // initialize and start the uds communication for UDS instance 1
  uds_initComm(BasicDiagUdsInstNbr_DU8,           // instance nbr
               canChnl_u8,                        // can channel
               rxDatabox_u16,                     // rx data box nbr
               0x18DA0000,                        // standard base can id
               ecuAddr_u8,                        // own address of RC
               toolAddr_u8,                       // tool address
               priority_u8,                       // priority of uds task
               cycleTime_u8,                      // cycle time of uds task
               uds_comTypeServer_DU8);            // uds server functionality

} // basicDiag_initComm

