/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        can_api.h
*
*  \brief       Interface for can.c
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   API RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 5905 $
*                            $Date: 2013-06-03 14:57:53 +0200 (Mo, 03 Jun 2013) $
*                            $Author: oub2si $
*
* REVISION HISTORY:
*
***************************************************************************************************/

#ifndef _CAN_API_H_D   /* replace it with the filename in capital letters */
#define _CAN_API_H_D   /* replace it with the filename in capital letters */


/**** include files ********************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

#include "common_api.h"
#include "types.h"

#ifdef _CAN_API_D      /* replace it with the filename in capital letters */
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   /* _CAN_API_D */

/**** defines **************************************************************************************
* List of defines needed in this header file and defines to be made available to other modules.   */

// PRQA S 5000 ++     // items of API should not be renamed

//--- CAN channels (nodes)
#define CAN_1     0
#define CAN_2     1
#define CAN_3     2
#define CAN_4     3

//--- identifier format
// standard 11 bit
#define CAN_STD_DU8   0u
/* Redeklaration has to be avoided because it is defined in can_pub.h of DS core. But if this
   file is not include (e.g. API user) it will be defined here.
*/
#ifndef CAN_STD
#define CAN_STD         CAN_STD_DU8
#endif // CAN_STD

// extended 29 bit
#define CAN_EXD_DU8   1u
/* Redeklaration has to be avoided because it is defined in can_pub.h of DS core. But if this
   file is not include (e.g. API user) it will be defined here.
*/
#ifndef CAN_EXD
#define CAN_EXD         CAN_EXD_DU8
#endif // CAN_EXD

// max CAN id for standard format
#define CAN_STD_MAX_ID_DU32 0x7FFu
// max CAN id for extended format
#define CAN_EXD_MAX_ID_DU32 0x1FFFFFFFu
// none CAN id
#define CAN_NONE_ID_DU32 0xFFFFFFFFu

// max number of data byte of a CAN message
#define CAN_MAX_NUM_DATA_DU8 8

//--- baud rates
#define BAUD_1000K        1000000u
#define BAUD_500K         500000u
#define BAUD_250K         250000u
#define BAUD_125K         125000u
#define BAUD_100K         100000u
#define BAUD_50K          50000u

// PRQA S 5000 --

//--- error codes
#define CAN_ERR_NO_ERRORS_DU16         0u
#define CAN_ERR_UNKNOWN_BAUDRATE_DU16  1u
#define CAN_ERR_SAMPLEPOINT_DU16       2u // invalid sample point
//#define CAN_ERR_CAN_ID_EXCEED_DU16     7 // can id exceeds the valid 11 or 29 Bit range
#define CAN_ERR_DATABOXNUM_DU16        9u // Data box number is invalid.
#define CAN_ERR_CHNL_DU16             14u // invalid channel (node)
#define CAN_ERR_ID_DU16               15u // invalid id
#define CAN_ERR_FORMAT_DU16           16u // invalid format
#define CAN_ERR_NUM_DATA_DU16         17u // invalid number of data bytes
#define CAN_ERR_NUM_MSG_DU16          18u /* invalid number of messages */
#define CAN_ERR_MASK_DU16             19u // invalid mask

#define CAN_ERR_TXBUF_OVFL_DU16       20u // Transmit buffer overflow

#define CAN_ERR_RXBUF_OVFL_DU16       30u // Receive buffer overflow.
#define CAN_ERR_RXBUF_EMPTY_DU16      31u // Receive buffer is empty.
#define CAN_ERR_RXBUF_LEN0_DU16       32u // Receive buffer length is zero.
                                          // (That means buffer length is not registered.)

#define CAN_ERR_OVERLAP_ADDR_DU16     55u // A buffer which has to be registered by application
                                          // (with the help of can-API functions)
                                          // overlaps with a present buffer registered by
                                          // application.

#define CAN_ERR_INVALID_ADDR_DU16     60u // Invalid address.
#define CAN_ERR_DATABOX_BUFLEN0_DU16  61u // Buffer length of a databox is zero.
                                          // This means that the databox is not initialised.
#define CAN_ERR_DATABOX_NOINIT_DU16   62u // Data box is not initialised.
#define CAN_ERR_DATABOX_ID_EXIST_DU16 63u // A data box with this id is initialised already.
#define CAN_ERR_DATABOXES_NUM_OLD_NEW_DU16 64u // Number of databoxes registered already is greater
                                              // than the new number. This error is only possible if
                                              // RTS library is implemented.
#define CAN_ERR_DATABOXES_NUM_DU16    65u /* invalid number of databoxes */

#define CAN_ERR_CFG_NOTALLOWED_DU16   99u // Configuration is not allowed.

//--- return code of can_isDataboxFree
#define CAN_TX_DATABOX_EMPTY_DU16         0u // Tx databox is empty
#define CAN_TX_DATABOX_NOT_EMPTY_DU16     1u // Tx databox is not empty

/*--- CAN buffer types
  useful for the second parameter of can_resetTxBuf()
*/
#define CAN_BUFTYPE_BUF_DU8         0x01 /* bit 0: buffer */
#define CAN_BUFTYPE_DATABOXES_DU8   0x02 /* bit 1: data boxes */

/**** typdefs/structures ***************************************************************************
* Typedefs/structures to be made available to other modules.                                      */

// structur of a can message
typedef struct can_Message_t
{
  uint32 id_u32; // identifier of the message
  uint8 format_u8; // format which will be transmitted, either STD, XTD
  uint8 numBytes_u8; // number of data bytes which will be transmitted or which where received
  uint8 data_au8[8]; // data which will be transmitted or which were received
} can_Message_ts;

// Structure of data of a can data box.
typedef struct can_DataboxData_t
{
  uint8 data_au8[8];  // data which will be transmitted or which were received
  uint8 numBytes_u8 INSERT_PADDING_D;  // number of data bytes which will be transmitted
                                       // or which where received
} can_DataboxData_ts;

// Structur of a buffer management.
typedef struct can_BufManage_t
{
  uint16 length_u16;  // length of the buffer
  uint16 idx_in_u16;  // index for write in the buffer
  uint16 idx_out_u16; // index for readout the buffer
  bool BufEmpty_l;    // This flag shows if the buffer is empty.
                      //  FALSE : Buffer is not empty.
                      //          If then idx_out = idx_in: buffer is full (no put in).
                      //  TRUE :  Buffer is empty (nothing is to send or noting was received).
  bool BufOvfl_l;     // This flag shows if a buffer overflow is occured.
                      //  FALSE : No buffer overflow is occured since last user inquiry of status
                      //          (e.g. with can_getData..)
                      //  TRUE  : Buffer overflow is occured.
} can_BufManage_ts;

/* Structure for a can databox buffer. Only data of the can message are buffered.
*/
typedef struct can_DataboxBufInfo_t
{
  can_DataboxData_ts *start_pas INSERT_PADDING_D; // start address of the buffer for data
  can_BufManage_ts Manage_s INSERT_PADDING_D; // Management of the buffer
} can_DataboxBufInfo_ts;

// Structure of a can receive (Rx) databox.
typedef struct can_RxDatabox_t
{
  uint32 id_u32; // message identifier
  uint8 format_u8; // format of the message
  uint8 numBytes_u8; // number of bytes in data_u8. This value is set in initialisation of data box.
  void (*callback_pf) (void); // pointer to a callback function
  can_DataboxBufInfo_ts Buf_s INSERT_PADDING_D; // Buffer for data inclusive all management
                                                // informations.
} can_RxDatabox_ts;

typedef can_RxDatabox_ts can_Databox_ts; // because downward compatibility


/* Structure of a can send (transmit, Tx) databox.
   - Only the actual data had to send will be buffered!
   - There is no callback function.
*/
typedef struct can_TxDatabox_t
{
  uint32 id_u32; // message identifier
  uint8 format_u8; // format of the message
  uint8 numBytes_u8; // number of bytes in data_u8. This value is set in initialisation of data box.
  uint8 data_au8[8]; // data = 8 bytes
  bool empty_l; // TRUE = databox is empty; FALSE = databox contains data which were not sent
  bool init_l;  // TRUE  = databox is intialised;
                // FALSE = databatox is not initialised yet
} can_TxDatabox_ts;

//--- definition of the callback functions
// can receive callback function
typedef void (*can_RxCallback_tpf) (uint8 format_u8, uint32 id_u32, uint8 numBytes_u8,
                                    uint8 *data_pau8);

// can bus off callback function
typedef void (*can_BusOffCallback_tpf) (uint16 status_u16);

// can receive data box callbck function
typedef void (*can_RxDataboxCallback_tpf) (void);

// can receive hardware data box callbck function
typedef void (*can_RxHwDataboxCallback_tpf) (uint32 msgId_u32, uint8 msgDlc_u8, uint8 *msgData_pu8);

/**** public data **********************************************************************************
* Declarations of variables to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */


/**** public functions *****************************************************************************
* Declarations of functions to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */

SCOPE_D uint16 can_init(uint8 chnl_u8, uint32 baudRate_u32);
SCOPE_D uint16 can_getStatus(uint8 chnl_u8);
SCOPE_D uint16 can_registerBusOffCallback(uint8 chnl_u8, can_BusOffCallback_tpf func_pf);

SCOPE_D uint16 can_registerTxBuf(uint8 chnl_u8, can_Message_ts *buf_pas, uint16 numMsg_u16);
SCOPE_D uint16 can_sendData(uint8  chnl_u8,
                            uint32 id_u32,
                            uint8  format_u8,
                            uint8  numBytes_u8,
                            uint8 *data_pau8);
SCOPE_D uint16 can_isTxEmpty(uint8 chnl_u8);

SCOPE_D uint16 can_registerTxDataboxes(uint8 chnl_u8, can_TxDatabox_ts *mem_pas, uint16 num_u16);
SCOPE_D uint16 can_initTxDatabox(uint8 chnl_u8, uint16 databoxNum_u16, uint32 id_u32,
                                 uint8 format_u8);
SCOPE_D uint16 can_sendDatabox(uint8 chnl_u8, uint16 txDataboxNum_u16, uint8 numBytes_u8,
                               uint8 *data_pau8);
SCOPE_D uint16 can_isDataboxFree(uint8 chnl_u8, uint16 txDataboxNum_u16);
SCOPE_D sint32 can_getRxBufStatus(uint8 chnl_u8);
SCOPE_D sint32 can_getTxBufStatus(uint8 chnl_u8);
SCOPE_D uint16 can_resetTxBuf(uint8 chnl_u8, uint8 bufType_u8);

SCOPE_D uint16 can_registerRxCallback(uint8 chnl_u8, can_RxCallback_tpf func_pf);
SCOPE_D uint16 can_registerRxBuf(uint8 chnl_u8, can_Message_ts *buf_pas, uint16 numMsg_u16);
SCOPE_D uint16 can_getData(uint8 chnl_u8, can_Message_ts *msg_ps);

SCOPE_D uint16 can_registerRxDataboxes(uint8 chnl_u8, can_RxDatabox_ts *mem_pas, uint16 num_u16);
SCOPE_D uint16 can_initRxDatabox(uint8 chnl_u8, uint16 databoxNum_u16, uint32 id_u32,
                                 uint8 format_u8, uint8 numBytes_u8, can_DataboxData_ts *buf_pas,
                                 uint16 buf_len_u16, can_RxDataboxCallback_tpf callback_pf);
SCOPE_D uint16 can_getDatabox(uint8 chnl_u8, uint16 databoxNum_u16, uint8 *data_pau8,
                              uint8 *numBytes_pu8);

SCOPE_D uint16 can_stop(uint8 chnl_u8);
SCOPE_D uint16 can_start(uint8 chnl_u8);
SCOPE_D uint16 can_setTxCycle(uint8 chnl_u8, uint16 time_u16);
SCOPE_D uint16 can_initxt(uint8 chnl_u8, uint32 baudRate_u32, uint8 samplePoint_u8);
SCOPE_D void can_cfgHwBoxes(uint16 numRxCan1_u16, uint16 numRxCan2_u16,
                            uint16 numRxCan3_u16, uint16 numRxCan4_u16);
SCOPE_D void can_setRxFilter(uint8 chnl_u8, uint8 format_u8,
                             uint32 msgId_u32, uint32 acceptMask_u32);
SCOPE_D uint16 can_initRxHwDatabox(uint8  chnl_u8,
                                   uint16 databoxNum_u16,
                                   uint32 id_u32,
                                   uint32 mask_u32,
                                   uint8  format_u8,
                                   can_RxHwDataboxCallback_tpf callback_pf);
SCOPE_D sint32 can_getErrCounter(uint8 chnl_u8, bool reset_l);

/**************************************************************************************************/

#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _CAN_API_D

#endif // _CAN_API_H_D

/**************************************************************************************************/

/* EOF ########################################################################################## */
