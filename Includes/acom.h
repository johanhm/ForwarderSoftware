//**************************************************************************************************
//
//  FILENAME:    acom.h
//
//  DESCRIPTION:
//! \file        acom_.h
//! \brief       Interface for acom.c
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_Plattform
//
// FILE VERSION INFORMATION:  $Revision: 5232 $
//                            $Date: 2013-01-23 10:29:06 +0100 (Mi, 23 Jan 2013) $
//                            $Author: gtg2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _ACOM_H_D
  #define _ACOM_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"
#include "numbers.h"

#ifdef _ACOM_D
  #define SCOPE_D
#else
  #define SCOPE_D extern
#endif   // _ACOM_D

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

// --- ACOM channels
#define ACOM_1  0

/*** Definition of the error locations/codes for ACOM module **************************************/
// --- acom_init()
// Invalid parameter. <error parameter> = number of parameter
#define ACOM_INIT_1_DU16                    (ACOM_DU16 | 0x01)

// Number of data bits > 8 is only possible if parity is none!
// <error parameter> = 0
#define ACOM_INIT_2_DU16                    (ACOM_DU16 | 0x02)

// --- acom_registerRxBuf()
// Invalid parameter. <error parameter> = number of parameter
#define ACOM_REGISTERRXBUF_1_DU16           (ACOM_DU16 | 0x03)
// Calling the function is not allowed in that program state.
#define ACOM_REGISTERRXBUF_2_DU16           (ACOM_DU16 | 0x04)
// New buffer overlaps with a buffer registered already.
// <error parameter>
// 0 : Buffers have not the same start adress.
// 1 : Buffers have the same start address (speculation: application has used the same var. twice).
#define ACOM_REGISTERRXBUF_3_DU16           (ACOM_DU16 | 0x05)

// --- acom_sendData()
// Invalid parameter. <error parameter> = number of parameter
#define ACOM_SENDDATA_1_DU16                (ACOM_DU16 | 0x06)

// --- acom_getData()
// Invalid parameter. <error parameter> = number of parameter
#define ACOM_GETDATA_1_DU16                 (ACOM_DU16 | 0x07)

// Receive buffer overflow
#define ACOM_GETDATA_2_DU16                 (ACOM_DU16 | 0x08)

// Receive buffer length is zero.
#define ACOM_GETDATA_3_DU16                 (ACOM_DU16 | 0x09)

// --- acom_sendData()
// acom_sendData without previous acom_init
#define ACOM_SENDDATA_2_DU16                (ACOM_DU16 | 0x0A)

/*** Definition of return values of functions *****************************************************/
// return values of acom_init()
#define ACOM_INIT_OK_DU16             0u
#define ACOM_INIT_ERR_CHNL_DU16       1u
#define ACOM_INIT_ERR_BAUD_DU16       2u
#define ACOM_INIT_ERR_NUMBITS_DU16    3u
#define ACOM_INIT_ERR_PARITY_DU16     4u
#define ACOM_INIT_ERR_STOPBITS_DU16   5u
#define ACOM_INIT_ERR_PAR_9BIT_DU16   6u

// return values of acom_sendData()
#define ACOM_SENDDATA_OK_DU16         0u
#define ACOM_SENDDATA_NOTEMPTY_DU16   1u
#define ACOM_SENDDATA_ERR_CHNL_DU16   2u
#define ACOM_SENDDATA_ERR_ADDR_DU16   3u
#define ACOM_SENDDATA_ERR_SEND_DU16   4u
#define ACOM_SENDDATA_NO_INIT_DU16    5u

// return values of acom_getData()
#define ACOM_GETDATA_OK_DU16            0u
#define ACOM_GETDATA_ERR_BUFOVFL_DU16   1u
#define ACOM_GETDATA_ERR_CHNL_DU16      3u
#define ACOM_GETDATA_ERR_ADDRDATA_DU16  4u
#define ACOM_GETDATA_ERR_ADDRNUM_DU16   5u
#define ACOM_GETDATA_ERR_BUFLEN_DU16    6u

// return values of acom_isTxEmpty()
#define ACOM_ISTXEMPTY_EMPTY_DU16       0u
#define ACOM_ISTXEMPTY_NOTEMPTY_DU16    1u
#define ACOM_ISTXEMPTY_ERR_CHNL_DU16    2u

// return values of acom_registerRxBuf()
#define ACOM_REGISTERRXBUF_OK_DU16            0u
#define ACOM_REGISTERRXBUF_ERR_CHNL_DU16      1u
#define ACOM_REGISTERRXBUF_ERR_ADDR_DU16      2u
#define ACOM_REGISTERRXBUF_ERR_NUM_DU16       3u
#define ACOM_REGRXBUF_ERR_OVERLAPADDR_DU16    4u
#define ACOM_REGRXBUF_ERR_CFGFORBIDD_DU16     5u

// return values of acom_registerErrorCallback/acom_registerRxCallback/acom_registerTxCallback
#define ACOM_REGISTER_CALLBACK_OK_DU16            0u
#define ACOM_REGISTER_CALLBACK_ERR_CHNL_DU16      1u
#define ACOM_REGISTER_CALLBACK_ERR_ADDR_DU16      2u

//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.

//--- definition of the callback functions
// acom error callback function
typedef void(*acom_errorCallback_tpf) (uint16 error_u16);

// acom rx callback function
typedef void(*acom_rxCallback_tpf) (uint8 char_u8);

// acom tx callback function
typedef void(*acom_txCallback_tpf) (void);


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.


//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.
SCOPE_D uint16 acom_init(uint8 chnl_u8, uint32 baudRate_u32, uint8 dataBits_u8,
                         uint8 parity_u8, uint8 stopBits_u8);

SCOPE_D uint16 acom_sendData(uint8 chnl_u8, uint16 numBytes_u16, uint8 *data_pau8);
SCOPE_D uint16 acom_isTxEmpty(uint8 chnl_u8);

SCOPE_D uint16 acom_registerRxBuf(uint8 chnl_u8, uint8 *buf_pau8, uint16 numBytes_u16);
SCOPE_D uint16 acom_getData(uint8 chnl_u8, uint8 *data_pau8, uint16 maxBytes_u16,
                            uint16 *numBytes_pu16);
SCOPE_D uint16 acom_getError(uint8 chnl_u8);

SCOPE_D bool acom_getLevel(uint8 chnl_u8);

SCOPE_D uint16  acom_registerErrorCallback(uint8 chnl_u8, acom_errorCallback_tpf func_pf);
SCOPE_D uint16  acom_registerRxCallback(uint8 chnl_u8, acom_rxCallback_tpf func_pf);
SCOPE_D uint16  acom_registerTxCallback(uint8 chnl_u8, acom_txCallback_tpf func_pf);


#undef SCOPE_D

#undef _ACOM_D             // reseting definition, prevents double definition of a variable if
                           // includes are nested
#endif  // _ACOM_H_D

// EOF #############################################################################################
