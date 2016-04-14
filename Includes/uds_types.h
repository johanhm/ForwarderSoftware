//**************************************************************************************************
//
//  FILENAME:    uds_types.h
//
//  DESCRIPTION:
//! \file        uds_types.h
//! \brief       header file with type definitons for uds functions
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

#ifndef _UDS_TYPES_H_D
   #define _UDS_TYPES_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"         // standard type definitions
#include "system.h"             // task definitions
#include "can_api.h"            // CAN definitions

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

//! Size of can raw message buffer for RECEIVING kwp messages. This buffer size
//! has influence on the max block length within the flow control messages sent by the RC.
#define rxCanBufferSize_DU8         10

//! Size of can raw message buffer for TRANSMITTING kwp messages. CAUTION: This buffer size
//! MUST be less or equal the buffer size of can_sendData to avoid buffer overflow during sending.
#define txCanBufferSize_DU8         10


// *************************************************************************************************
// D I A G N O S T I C   T R O U B L E   C O D E S   ( D T C )
// *************************************************************************************************
#define uds_DTC_PositiveResponse_DU8                        0x00u
#define uds_DTC_ServiceNotSupported_DU8                     0x11u

// *************************************************************************************************
// other defines
// *************************************************************************************************
#define uds_SIDIndex_DU8                                    0x00u
#define uds_LIDIndex_DU8                                    0x01u
#define uds_DTCIndex_DU8                                    0x02u

#define uds_comTypeInit_DU8                                 0x00
#define uds_comTypeServer_DU8                               0x01
#define uds_comTypeClient_DU8                               0x02
#define uds_comTypeDlc8_DU8                                 0x04

//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.

// PRQA S 5001 ++             // API structure names should not be changed any more
//! struct of an uds message
typedef struct UDSMSG_TS
{
  uint16 size_u16;            // buffer size
  uint16 DLC_u16;             // actual data length
  uint8  *data_au8;           // pointer to uds message buffer
} udsMsg_ts;
// PRQA S 5001 --

//! struct of a can message in a can message ring buffer for data transfer with transport layer
typedef struct UDS_CANMSG_TS
{
  uint32 canID_u32;
  uint8 DLC_u8;
  uint8 data_au8[8];
} uds_canMsg_ts;

//! struct of a can message ring buffer
typedef struct UDS_CANMSGBUF_TS
{
  uint8 bufferSize_u8;
  uint8 readIndex_u8;
  uint8 writeIndex_u8;
  bool  bufferFull_l;
  uds_canMsg_ts *canMsg_pas;
} uds_canMsgBuf_ts;

//! struct of flow control settings only used in this module
typedef struct UDS_FLOWCTRL_TS
{
  uint8 flowState_u8;         // state of transceiption (pause or resume)
  uint8 STmin_u8;             // time distance in ms between two consecutive frames
  uint8 maxBlock_u8;          // max count of consecutive frames in one burst
  uint8 SepTime_u8;           // time in ms after the last consecutive frame (self incremented)
} uds_flowCtrl_ts;

//! struct of the transport layer transmission and receiption state
typedef struct UDS_TPSTATE_TS
{
  uint8  receive_u8;          // state flag of transport layer receive function
  uint8  transmit_u8;         // state flag of transport layer transmit function
  uds_flowCtrl_ts rxFlowCtrl_s __attribute__ ((aligned (4)));   // struct with rx flow control
                                                                // settings
  uds_flowCtrl_ts txFlowCtrl_s __attribute__ ((aligned (4)));   // struct with tx flow control
                                                                // settings
  uint8  cycleTime_u8;        // the call distance between two transport layer calls
  uint8  rxCFCnt_u8;          // counter of received consecutive frames
  uint8  rxBurstCnt_u8;       // counter of received consecutive frames after a flow control
  uint16 rxDataCnt_u16;       // counter of received data
  uint8  txCFCnt_u8;          // counter of transmitted consecutive frames
  uint8  txBurstCnt_u8;       // counter of transmitted consecutive frames after a flow control
  uint16 txDataCnt_u16;       // counter of transmitted data
  uint16 timer_u16;           // timer for protocol timeout supervision
} uds_tpState_ts;

// PRQA S 4880 ++
//! typedef for the function pointer to the evaluation callback function within the application
typedef uint8 (*rxCallback_tpf)(udsMsg_ts *rxUdsMsg_ps, udsMsg_ts *txUdsMsg_ps);
// PRQA S 4880 --

//! typedef for the function pointer to the error callback function within the application
typedef void (*errorCallback_tpf)(uint16 errorCode_u16);

//! common UDS communication parameters
typedef struct UDS_PARAM_TS
{
  uint8       cycleTime_u8;                               // execution cycle time of uds task
  uint8       priority_u8;                                // priority of uds task
  uint8       chnl_u8;                                    // CAN channel (CAN1..CAN4)
  uint8       ownId_u8;                                   // own address for communication
  uint8       toolId_u8;                                  // tool address for communication
  uint8       taskHandle_u8;                              // task handle of system scheduler
  uint8       comType_u8;                                 // communication type (server/client)
  bool        udsInitDone_l;                              // flag to prevent multiple initialization
  uint16      instanceNum_u16;                            // number of this uds instance (=idx+1!)
  sint16      messageFormat_s16;                          // standard or extended can identifier
  uint16      rxDataBox_u16;                              // databox for reception of uds services
  uint16      bcRxDataBox_u16;                            // broadcast databox for reception
  uint16      txDataBox_u16;                              // databox for transmission
  uint32      rxId_u32;                                   // reception CAN identifier
  uint32      txId_u32;                                   // transmission CAN identifier
  Task_tpf    task_pf;                                    // pointer to uds task
  can_RxDataboxCallback_tpf rxCallback_pf;                // pointer to can rx callback function
} uds_param_ts;

//! memory structure for one UDS instance
typedef struct uds_instance_t
{
  can_DataboxData_ts  rxBoxBuff_s __attribute__ ((aligned (4)));  // temp. buffer for rx can databox
  // raw can message data of rx buffer
  uds_canMsg_ts       rxCanMsg_as[rxCanBufferSize_DU8] __attribute__ ((aligned (4)));
  // raw can message data of tx buffer
  uds_canMsg_ts       txCanMsg_as[txCanBufferSize_DU8] __attribute__ ((aligned (4)));
  uds_canMsgBuf_ts    rxCanBuff_s __attribute__ ((aligned (4)));  // rx can msg buffer control
  uds_canMsgBuf_ts    txCanBuff_s __attribute__ ((aligned (4)));  // tx can msg buffer control
  udsMsg_ts           rxKwpMsg_s __attribute__ ((aligned (4)));   // rx uds message buffer
  udsMsg_ts           txKwpMsg_s __attribute__ ((aligned (4)));   // tx uds message buffer
  uds_tpState_ts      tpState_s __attribute__ ((aligned (4)));    // transport protocol control
  uds_param_ts        udsParam_s __attribute__ ((aligned (4)));   // common uds parameters
  rxCallback_tpf      rxFunc_pf;                          // function to evaluate a rx msg
  errorCallback_tpf   errorFunc_pf;                       // function to evaluate run time errors
} uds_instance_ts;


//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.

// ----- this file should not contain any data declarations!! -----

//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.

// ----- this file should not contain any function declarations!! -----

//**************************************************************************************************

#endif  // _UDS_TYPES_H_D

// EOF #############################################################################################
