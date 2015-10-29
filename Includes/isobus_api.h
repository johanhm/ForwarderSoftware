//**************************************************************************************************
//
//  FILENAME:    isobus_api.h
//
//  DESCRIPTION:
//! \file        isobus_api.h
//! \brief       header file for ISOBUS API functions
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_Plattform
//
// FILE VERSION INFORMATION:  $Revision: 5915 $
//                            $Date: 2013-06-05 14:51:41 +0200 (Mi, 05 Jun 2013) $
//                            $Author: oub2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _ISOBUS_API_H_D
  #define _ISOBUS_API_H_D


//*** include files ********************************************************************************
// List of include files needed in this module.
#include "std_type.h"     //standard type definitions

#ifdef _ISOBUS_API_D
  #define SCOPE_D
#else
  #define SCOPE_D extern
#endif   // _ISOBUS_API_D

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

//--- isobus rx/tx databox status
#define ISOBUS_BOXSTATUS_NONE_DU16          0x0000 // message box is not yet initialized
#define ISOBUS_BOXSTATUS_INIT_DU16          0x0100 // message box is initialized
#define ISOBUS_BOXSTATUS_VALID_DU16         0x0200 // rx message box data are valid
#define ISOBUS_BOXSTATUS_VAL_OVFL_DU16      0x0201 // rx data are valid, but overflow occurs (DM1/2)
#define ISOBUS_BOXSTATUS_INV_SEQNBR_DU16    0x0301 // data are invalid, wrong sequence nbr received
#define ISOBUS_BOXSTATUS_INV_ABORT_DU16     0x0302 // data are invalid, rx/tx transfer aborted
#define ISOBUS_BOXSTATUS_INV_TIMEOUT_DU16   0x0303 // data are invalid, timeout occurs
#define ISOBUS_BOXSTATUS_INV_OVFL_DU16      0x0304 // data are invalid, overflow error
#define ISOBUS_BOXSTATUS_INV_PGN_ERR_DU16   0x0310 // data are invalid, different PGN in RTS and DPO
#define ISOBUS_BOXSTATUS_INV_DPO_ERR_DU16   0x0311 // data are invalid, CTS - DPO inconsistency
#define ISOBUS_BOXSTATUS_PENDING_DU16       0x0400 // tx msg waits for sending, tx not yet started
#define ISOBUS_BOXSTATUS_BAM_RX_DU16        0x0500 // receiving of a BAM message is in progress
#define ISOBUS_BOXSTATUS_CMDT_RX_DU16       0x0501 // receiving of a CMDT message is in progress
#define ISOBUS_BOXSTATUS_BAM_TX_DU16        0x0600 // transmitting of a BAM message is in progress
#define ISOBUS_BOXSTATUS_UNPACK_DU16        0x0700 // unpacking of received DM1/2 BAM is in progress
#define ISOBUS_BOXSTATUS_ETP_RX_DU16        0x0800 // receiving of a ETP message is in progress

#define ISOBUS_BOXSTATUS_MASK_DU16          0xFF00 // Status mask for main status


//--- isobus controller application status  (main status = hi byte, sub status = lo byte)
#define ISOBUS_CASTATUS_NONE_DU16           0x0000 // CA is not yet initialized
#define ISOBUS_CASTATUS_INIT_DU16           0x0100 // CA is initialized
#define ISOBUS_CASTATUS_WAIT_CLAIM_DU16     0x0200 // CA waits for could claim an address
#define ISOBUS_CASTATUS_ADDR_CLAIMED_DU16   0x0300 // CA could claim an address (operation state)
#define ISOBUS_CASTATUS_CANNOT_CLAIM_DU16   0x0400 // CA could not claim an address

#define ISOBUS_CASTATUS_MASK_DU16           0xFF00 // Status mask for main status
#define ISOBUS_SUBSTATUS_TIMEOUT_DU16       0x0001 // isobus cycle timeout occured
#define ISOBUS_SUBSTATUS_RXOVFL_DU16        0x0002 // rx buffer overflow occured


//--- return codes of isobus functions
#define ISOBUS_RC_NO_ERRORS_DU16            0   // ok
#define ISOBUS_RC_INVALID_ADDR_DU16         1   // invalid address
#define ISOBUS_RC_INV_DATABOX_DU16          2   // invalid data box number
#define ISOBUS_RC_INV_PGN_DU16              3   // invalid pgn
#define ISOBUS_RC_INV_SRC_DU16              4   // invalid source address
#define ISOBUS_RC_INV_TIMEOUT_DU16          5   // invalid timeout value for rx msg
#define ISOBUS_RC_INV_DATA_LEN_DU16         6   // invalid data length
#define ISOBUS_RC_INV_DATA_PTR_DU16         7   // invalid data address
#define ISOBUS_RC_OVERLAP_ADDR_DU16         8   // address overlaps with other buffers
#define ISOBUS_RC_INV_STARTTIMEOUT_DU16     9   // invalid start timeout value for rx msg

#define ISOBUS_RC_INV_CYCLE_DU16            10  // invalid cycle time for tx msg
#define ISOBUS_RC_INV_OFFSET_DU16           11  // invalid offset time for tx msg
#define ISOBUS_RC_INV_PRIO_DU16             12  // invalid priority of msg

#define ISOBUS_RC_PGN_SRC_EXIST_DU16        20  // Data box with same pgn+src already exists
#define ISOBUS_RC_PGN_PRIO_EXIST_DU16       21  // Data box with same pgn+prio already exists
#define ISOBUS_RC_CFG_NOTALLOWED_DU16       22  // configuration is not allowed

#define ISOBUS_RC_INV_BOX_STATUS_DU16       30  // invalid data box status

#define ISOBUS_RC_INV_SPN_DU16              40  // invalid SPN
#define ISOBUS_RC_INV_FMI_DU16              41  // invalid FMI
#define ISOBUS_RC_DM1_FULL_DU16             42  // max nbr of DM1 failures reached
#define ISOBUS_RC_DM2_FULL_DU16             43  // max nbr of DM2 failures reached
#define ISOBUS_RC_SPN_NOT_FOUND_DU16        44  // SPN is not stored in list

#define ISOBUS_RC_INV_ECU_ADDR_DU16         50  // invalid ECU address
#define ISOBUS_RC_INV_DM_TYPE_DU16          51  // invalid DM type

#define ISOBUS_RC_INV_LIST_SIZE_DU16        60  // invalid list size
#define ISOBUS_RC_INV_EE_PAGE_DU16          61  // invalid eeprom page nbr
#define ISOBUS_RC_INV_EE_IDX_DU16           62  // invalid eeprom start index of failure list
#define ISOBUS_RC_INIT_MISSING_DU16         63  // function not allowed without initialization
#define ISOBUS_RC_EE_OVERLAPPING_DU16       64  // overlapping eeprom range

#define ISOBUS_RC_EEP_OVERFLOW_DU16         70  // internal eeprom queue overflow

#define ISOBUS_RC_INV_INST_NUM_DU16         80  // invalid CA instance number
#define ISOBUS_RC_INV_CAN_CHNL_DU16         81  // invalid can channel
#define ISOBUS_RC_INV_CA_ADDR_DU16          82  // invalid CA address
#define ISOBUS_RC_CA_ADDR_IN_USE_DU16       83  // CA address already used by other CA
#define ISOBUS_RC_REGINST_NOT_ALLOWED_DU16  84  // register instances not allowed outside sys_main()
#define ISOBUS_RC_INV_FUNC_SEQU_DU16        85  // invalid execution sequence of function calls

#define ISOBUS_RC_DM1_NOT_EXIST_DU16        0   // DM1 failure doesn't exits within DM1 failure list
#define ISOBUS_RC_DM1_EXIST_DU16            1   // DM1 failure exists within DM1 failure list

//--- special parameter values used by API functions
#define ISOBUS_SPN_ALL_DU32                 0xFFFFFFFFu
#define ISOBUS_FMI_ALL_DU8                  0xFFu
#define ISOBUS_BYTES_ALL_DU32               0xFFFFFFFFu

#define ISOBUS_LIST_NONE_DU16               0x00  // DM failure list type NULL
#define ISOBUS_LIST_DM1_DU16                0x01  // DM failure list type DM1
#define ISOBUS_LIST_DM2_DU16                0x02  // DM failure list type DM2
#define ISOBUS_LIST_DM1_V1_DU16             0x11  // DM failure list type DM1 and CM version 1
#define ISOBUS_LIST_DM2_V1_DU16             0x12  // DM failure list type DM2 and CM version 1
#define ISOBUS_LIST_DM1_V2_DU16             0x21  // DM failure list type DM1 and CM version 2
#define ISOBUS_LIST_DM2_V2_DU16             0x22  // DM failure list type DM2 and CM version 2
#define ISOBUS_LIST_DM1_V3_DU16             0x31  // DM failure list type DM1 and CM version 3
#define ISOBUS_LIST_DM2_V3_DU16             0x32  // DM failure list type DM2 and CM version 3

#define ISOBUS_DTC_LIST_SIZE_DU16           20    // DM failure list size (DTCs of another ECU)

#define ISOBUS_CM1_VERSION1_DU16            0x10  // DTC conv. mode Ver.1 in case of CM-Bit = 1
#define ISOBUS_CM1_VERSION2_DU16            0x20  // DTC conv. mode Ver.2 in case of CM-Bit = 1
#define ISOBUS_CM1_VERSION3_DU16            0x30  // DTC conv. mode Ver.3 in case of CM-Bit = 1
#define ISOBUS_CM1_MASK_DU16                0xF0u // DTC conv. mode mask

#define ISOBUS_nbrRxSysBoxes_DU8            0x04  // nbr of stack internal rx databoxes
#define ISOBUS_nbrTxSysBoxes_DU8            0x01  // nbr of stack internal tx databoxes

// Maximum number of own DTCs within DTC list
#define ISOBUS_MaxNbrDtc_DU16               32

// Max data length of a DM1/2 TX databox buffer (e.g. 32 DTCs * 4 bytes + 2 bytes lamp state = 130)
#define ISOBUS_DmBuffSize_DU16              ((ISOBUS_MaxNbrDtc_DU16 * 4) + 2)
// Max data length of the ReqPgn TX databox buffer
#define ISOBUS_buffLenReqPgn_DU16           34

// Maximum size of a single message
#define ISOBUS_MaxSingleSize_DU32           8ul
// Maximum size of a BAM/CMDT message (protocol limit)
#define ISOBUS_MaxTpSize_DU32               1785ul
// Maximum size of a ETP message (protocol limit)
#define ISOBUS_MaxETpSize_DU32              117440512ul


//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.

// PRQA S 635 ++

typedef struct isobus_canID_pkt_t
{
  /* first byte in memory */
  bit8 SourceAddr_b8 : 8;   // this byte is the node id of the sender of this message
  bit8 PDUSpecial_b8 : 8;   // when the pdu format value is < 240, this byte contents the
                            // destination address. when the pdu format value is 240 to 255, it
                            // contents the group extension
  bit8 PDUFormat_b8  : 8;   // this byte is used as a part of the pgn
  bit2 DataPage_b2   : 2;   // these bits identify the data pages of the parameter group
  bit3 Priority_b3   : 3;   // these 3 bits define the priority of the following message
  bit3 unusedBits_b3 : 3;   // these 3 bits are overhead for the 29 bit data
  /* last byte in memory */
}  __attribute__ ((packed)) isobus_canID_ts;

typedef union isobus_canID_t
{
   isobus_canID_ts canID_s;
   uint32         canID_u32;
} isobus_canID_tu;

//--- definition of the callback functions
// isobus receive callback function
typedef void (*isobus_rxCallback_tpf) (void);
// isobus transmit callback function
typedef uint32 (*isobus_txCallback_tpf) (void);

// structure of a isobus rx databox message definition within the array of defined rx messages
typedef struct isobus_rxMsg_t
{
  uint8  *data_pau8;              // pointer to data array with length=lenMax_u32
  isobus_rxCallback_tpf func_pf;  // function is called if msg received completely
  isobus_canID_tu canID_u;        // can identity of msg to be received
  uint32 lenAct_u32;              // expected total length of actual received msg tp be receievd
  uint32 lenRx_u32;               // length of already received msg part
  uint32 lenMax_u32;              // max length of the receive buffer defined below
  uint16 timeout_u16;             // timeout (ms) for supervision of cyclic msg
  uint16 startTimeout_u16;        // start timeout (ms) for supervision of first msg
  uint16 counter_u16;             // actual time counter for timeout supervision
  uint16 status_u16;              // msg status, e.g. valid, invalid, timeout
  uint16 action_u16;              // action (e.g. data conversion) to be done after reception
  bool   internalBox_l;           // = true, if it is an stack internal rx databox
} isobus_rxMsg_ts;

// structure of a isobus tx databox message definition within the array of defined tx messages
typedef struct isobus_txMsg_t
{
  uint8  *data_pau8;              // pointer to data array with length=lenMax_u32
  isobus_txCallback_tpf func_pf;  // function is called before msg is to be sent
  isobus_canID_tu canID_u;        // can identity of msg to be sent
  uint32 lenMax_u32;              // max length (buffer size) of msg to be sent
  uint32 lenAct_u32;              // actual length of msg to be sent
  uint16 cycle_u16;               // cycle time for sending this msg
  uint16 counter_u16;             // actual time counter for cyclic sending
  uint16 status_u16;              // msg status, e.g. valid, invalid
} isobus_txMsg_ts;

// structure of one DTC (NOT packed)
typedef struct isobus_dtc_t
{
  uint32 spn_u32;    // suspect parameter number
  uint8  fmi_u8;     // failure mode indicator
  uint8  occ_u8;     // occurrence counter
} isobus_dtc_ts;

// extended structure of one DTC with additional state (NOT packed)
typedef struct isobus_dtcExt_t
{
  uint32 spn_u32;    // suspect parameter number
  uint8  fmi_u8;     // failure mode indicator
  uint8  occ_u8;     // occurrence counter
  uint8  state_u8;   // active error state
} isobus_dtcExt_ts;

// structure of one lamp status (NOT packed)
typedef struct isobus_lamp_t
{
  uint8  lampState_u8;     // lamp status
  uint8  lampFlash_u8;     // lamp flash
} isobus_lamp_ts;

// structure of one failure (NOT packed) within the failure lists for application access
typedef struct isobus_failure_t
{
  isobus_dtcExt_ts dtc_s  __attribute__ ((aligned (4)));        // 56 Bit: DTC
  isobus_lamp_ts   lamp_s __attribute__ ((aligned (4)));        // 16 Bit: lamp and flash status
} isobus_failure_ts;

// structure of received and converted DM1/2 failure lists
typedef struct isobus_dtcList_t
{
  isobus_lamp_ts  lamp_s __attribute__ ((aligned (4)));                              // lamp status
  isobus_dtc_ts   dtc_as[ISOBUS_DTC_LIST_SIZE_DU16] __attribute__ ((aligned (4)));    // DTC list
} isobus_dtcList_ts;

// structure of all data for one error handler instance for DM1 and DM2 failures
typedef struct isobus_err_t
{
  isobus_failure_ts  *list_pas;        // pointer to DM1 failure list (array)
  uint16             size_u16;         // size of failure list array above
  uint16             nbrAct_u16;       // actual number of active (DM1) failures within failure list
  uint16             eePage_u16;       // eeprom page nbr for DM2 failure list
  uint16             eeIndex_u16;      // eeprom start index for DM2 failure list (1.Int = amount!)
  uint16             txBoxDM1_u16;     // TX box nbr for sending the DM1 failures
  uint16             txBoxDM2_u16;     // TX box nbr for sending the DM2 failures
} isobus_err_ts;

//! struct for isobus BAM transport control
typedef struct isobus_bamCtrl_t
{
  uint16          lenTx_u16;    // nbr already sent data bytes
  uint16          timer_u16;    // timer for TX BAM control
  uint8           state_u8;     // status of TX BAM protocol handler
  isobus_txMsg_ts *txMsg_ps;    // ptr to message buffer, which is currently sended via BAM
} isobus_bamCtrl_ts;

typedef union isobus_PGN_t
{
   uint8 PGN_au8[4];
   uint32 PGN_u32;
} isobus_PGN_tu;

//! struct with required data for receiving rx databox via mtp handler
typedef struct isobusRxTpCtrl_t
{
   isobus_canID_tu canID_u;         // response or transmit CANid
   isobus_PGN_tu   PGN_u;           // PGN to be handled
   isobus_rxMsg_ts *rxMsgPtr_ps;    // pointer to rx databox, currently handled by mtp handler
   uint16          doneDataCnt_u16; // nbr of already handled data bytes of succ. completed packages
   uint16          timer_u16;       // time counter [ms] for timeout supervision
   uint8           packageCount_u8; // nbr of single msgs (packets) per package which fit into buff.
   uint8           packageStart_u8; // first message (packet) nbr of the package to be handled
   uint8           packageNumber_u8;// actual message sequence (packet) number
   uint8           lastPackage_u8;  // last message (packet) number
   uint8           maxPackage_u8;   // max. nbr of messages to be handled per packet (for CTS msg)
   uint8           state_u8;        // status of state machine
   bool            retryCtsFlag_l;  // retry flag for requesting the same package via CTS
} isobus_rxTpCtrl_ts;

//! struct with required data for transmitting tx databox via mtp handler
typedef struct isobusTxTpCtrl_t
{
   isobus_canID_tu canID_u;         // response or transmit CANid
   isobus_PGN_tu   PGN_u;           // PGN to be handled
   isobus_txMsg_ts *txMsgPtr_ps;    // pointer to tx databox, currently handled by mtp handler
   uint16          msgDlc_u16;      // total number of data bytes
   uint16          doneDataCnt_u16; // nbr of already handled data bytes
   uint16          timer_u16;       // time counter [ms] for timeout supervision
   uint8           packageCount_u8; // nbr of single msgs (packets) per package which fit into buff.
   uint8           packageStart_u8; // first message (packet) nbr of the package to be handled
   uint8           packageNumber_u8;// actual message sequence number to be sent
   uint8           lastPackage_u8;  // last message (packet) number
   uint8           state_u8;        // status of state machine
} isobus_txTpCtrl_ts;

//! struct with required data for receiving rx databox via ETP handler
typedef struct isobusRxEtpCtrl_t
{
   isobus_canID_tu canID_u;         // response or transmit CANid
   isobus_PGN_tu   PGN_u;           // PGN to be handled
   isobus_rxMsg_ts *rxMsgPtr_ps;    // pointer to rx databox, currently handled by mtp handler
   uint32         doneDataCnt_u32;  // nbr of already handled data bytes of succ. completed packages
   uint32         packageStart_u32; // first message (=offset) nbr of the package to be handled
   uint32         lastPackage_u32;  // last message number = total nbr of messages
   uint16         timer_u16;        // time counter [ms] for timeout supervision
   uint8          packageNumber_u8; // actual message sequence number to be received
   uint8          packageCount_u8;  // nbr of single msgs per burst which fit into buffer
   uint8          maxPackage_u8;    // max. nbr of messages to be handled per burst (for CTS msg)
   uint8          state_u8;         // status of state machine
   bool           retryCtsFlag_l;   // retry flag for requesting the same package via CTS
} isobus_rxEtpCtrl_ts;

//! struct with required data for transmitting tx databox via ETP handler
typedef struct isobustxEtpCtrl_t
{
   isobus_canID_tu canID_u;         // response or transmit CANid
   isobus_PGN_tu   PGN_u;           // PGN to be handled
   isobus_txMsg_ts *txMsgPtr_ps;    // pointer to tx databox, currently handled by mtp handler
   uint32         msgDlc_u32;       // total number of data bytes
   uint32         doneDataCnt_u32;  // nbr of already handled data bytes
   uint32         packageStart_u32; // first message (=offset) nbr of the package to be handled
   uint32         lastPackage_u32;  // last message number = total nbr of messages
   uint16         timer_u16;        // time counter [ms] for timeout supervision
   uint8          packageNumber_u8; // actual message sequence number
   uint8          packageCount_u8;  // nbr of msgs for next burst which must fit into buffer
   uint8          maxPackage_u8;    // max. nbr of messages to be handled per burst (for CTS msg)
   uint8          state_u8;         // status of state machine
} isobus_txEtpCtrl_ts;

//! Structure of isobus rx data box info for API. The buffer itself is located API-external. The
//! application has to declare the buffer.
typedef struct isobus_rxDataboxInfo_t
{
  isobus_rxMsg_ts *mem_pas;  // pointer to the buffer for data boxes
  uint16          num_u16;   // number of data boxes
} isobus_rxDataboxInfo_ts;

//! Structure of isobus tx data box info for API. The buffer itself is located API-external. The
//! application has to declare the buffer.
typedef struct isobus_txDataboxInfo_t
{
  isobus_txMsg_ts *mem_pas;  // pointer to the buffer for data boxes
  uint16          num_u16;   // number of data boxes
} isobus_txDataboxInfo_ts;

// structure of CA name
typedef struct isobus_caName_pkt_t
{
  bit21 serialNbr_b21         : 21;  //(LSB)
  bit11 manufacturerCode_b11  : 11;
  bit3  ecuInstance_b3        : 3;
  bit5  functionInstance_b5   : 5;
  bit8  function_b8           : 8;
  bit1  reserved_b1           : 1;
  bit7  deviceClass_b7        : 7;
  bit4  deviceInstance_b4     : 4;
  bit3  industryGroup_b3      : 3;
  bit1  arbitAddrCapable_b1   : 1;   //(MSB)
}  __attribute__ ((packed)) isobus_caName_ts;

// structure for name management services
typedef struct isobus_nm_pkt_t
{
  bit8  chkSumOrErrCode_b8    : 8;  //(LSB)
  bit8  qualFlags_b8          : 8;
  bit4  ctrlMode_b4           : 4;
  bit1  reserved1_b1          : 1;
  bit11 manufacturerCode_b11  : 11;
  bit3  ecuInstance_b3        : 3;
  bit5  functionInstance_b5   : 5;
  bit8  function_b8           : 8;
  bit1  reserved2_b1          : 1;
  bit7  deviceClass_b7        : 7;
  bit4  deviceInstance_b4     : 4;
  bit3  industryGroup_b3      : 3;
  bit1  arbitAddrCapable_b1   : 1;   //(MSB)
}  __attribute__ ((packed)) isobus_nm_ts;

typedef union isobus_caName_t
{
   uint8            name_au8[8];
   isobus_caName_ts name_s;
   isobus_nm_ts     nm_s;
} isobus_caName_tu;

//! Structure of a ISOBUS CA (controller application) instance.
typedef struct isobus_appInst_t
{
  isobus_rxDataboxInfo_ts rxDataboxInfo_s;      // user defined ISOBUS Receive data boxes info
  isobus_txDataboxInfo_ts txDataboxInfo_s;      // user defined ISOBUS Transmit data boxes info
  isobus_bamCtrl_ts       txBamCtrl_s;          // isobus tx bam control data
  isobus_txMsg_ts         txBamBuff_s;          // BAM message buffer for requestPGN answers
  isobus_rxTpCtrl_ts      rxTpCtrl_s;           // rx tp control data for RTS/CTS transport layer
  isobus_txTpCtrl_ts      txTpCtrl_s;           // tx tp control data for RTS/CTS transport layer
  isobus_rxEtpCtrl_ts     rxEtpCtrl_s;          // rx ETP control data for RTS/CTS transport layer
  isobus_txEtpCtrl_ts     txEtpCtrl_s;          // tx ETP control data for RTS/CTS transport layer
  sint8                   *ecuLoc_pas8;         // pointer to ECU location string
  sint8                   *ecuType_pas8;        // pointer to ECU type string
  sint8                   *ecuMan_pas8;         // pointer to ECU manufacturer string
  sint8                   *applTask_pas8;       // pointer to application task name
  isobus_err_ts           err_s;                // DM1/2 error data of own application
  isobus_rxMsg_ts         rxSysDatabox_as[ISOBUS_nbrRxSysBoxes_DU8]; // internal isobus rx databoxes
  isobus_txMsg_ts         txSysDatabox_as[ISOBUS_nbrTxSysBoxes_DU8]; // internal isobus tx databoxes
  uint8                   rxDataRequPgn_au8[8]; // data of rx databox for request PGN msg
  uint8                   rxDataAddrClm_au8[8]; // data of rx databox for address claim msg
  uint8                   rxDataCmdAddr_au8[9]; // data of rx databox for commanded msg
  uint8                   rxDataNameNmt_au8[8]; // data of rx databox for name management msg
  uint8                   txDataRequPgn_au8[ISOBUS_buffLenReqPgn_DU16];// tx buffer for RequPgn msg
  uint8                   dm1BuffDat_au8[ISOBUS_DmBuffSize_DU16];  // buffer for DM1 tx databox
  uint8                   dm2BuffDat_au8[ISOBUS_DmBuffSize_DU16];  // buffer for DM2 tx databox
  isobus_caName_tu        caName_u;             // controller application name
  isobus_caName_tu        caPendName_u;         // controller application pending name
  uint16                  caStatus_u16;         // global status of controller application
  uint16                  addrClaimTimer_u16;   // timer [ms] for address claiming supervision
  uint16                  taskNextTxIdx_u16;    // TX msg index to be sent in next cycle
  uint8                   ownAddr_u8;           // own CA (source) address
  uint8                   canChannel_u8;        // can channel used by CA
  uint8                   nameMngSourceAddr_u8; // source address of last name management request
  bool                    sendDm1Allowed_l;     // TRUE, if add. DM1 may be sent wihtin 1s periode
  bool                    dm1LampStateJ1939_l;  // TRUE -> handle DM1 lamp state according J1939.
} isobus_appInst_ts;
// PRQA S 635 --

//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.


//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.

SCOPE_D void isobus_initComm(uint8 canChnl_u8,
                             uint8 priority_u8,
                             uint8 cycleTime_u8,
                             uint8 maxTime_u8);

SCOPE_D uint16 isobus_registerRxDataboxes(uint8 instanceNum_u8,
                                          isobus_rxMsg_ts *mem_pas,
                                          uint16 num_u16);

SCOPE_D uint16 isobus_registerTxDataboxes(uint8 instanceNum_u8,
                                          isobus_txMsg_ts *mem_pas, uint16 num_u16);

SCOPE_D uint16 isobus_initRxDatabox(uint8 instanceNum_u8,
                                    uint16 boxNum_u16,
                                    uint32 pgn_u32,
                                    uint8  src_u8,
                                    uint16 timeout_u16,
                                    uint16 startTimeout_u16,
                                    uint32 lenMax_u32,
                                    uint8  *data_pau8,
                                    isobus_rxCallback_tpf func_pf);

SCOPE_D uint16 isobus_initTxDatabox(uint8 instanceNum_u8,
                                    uint16 boxNum_u16,
                                    uint32 pgn_u32,
                                    uint8  prio_u8,
                                    uint16 cycle_u16,
                                    uint16 offset_u16,
                                    uint32 lenMax_u32,
                                    uint8  *data_pau8,
                                    isobus_txCallback_tpf func_pf);

SCOPE_D uint16 isobus_sendDatabox(uint8 instanceNum_u8,
                                  uint16 boxNum_u16);

SCOPE_D uint16 isobus_getRxDataboxStatus(uint8 instanceNum_u8,
                                         uint16 boxNum_u16,
                                         uint32 *msgLen_pu32);

SCOPE_D uint16 isobus_initFailureList(uint8 instanceNum_u8,
                                      isobus_failure_ts *listFailure_pas,
                                      uint16 listSize_u16,
                                      uint16 eePage_u16,
                                      uint16 eeIndex_u16,
                                      uint16 txBoxDM1_u16,
                                      uint16 txBoxDM2_u16);

SCOPE_D uint16 isobus_setFailureDM1(uint8 instanceNum_u8,
                                    uint32 spn_u32,
                                    uint8 fmi_u8,
                                    uint8 lampState_u8,
                                    uint8 lampFlash_u8);

SCOPE_D uint16 isobus_resetFailureDM1(uint8 instanceNum_u8,
                                      uint32 spn_u32,
                                      uint8 fmi_u8,
                                      bool keep_l);

SCOPE_D uint16 isobus_testFailureDM1(uint8 instanceNum_u8,
                                     uint32 spn_u32,
                                     uint8 fmi_u8);

SCOPE_D uint16 isobus_resetFailureDM2(uint8 instanceNum_u8);

SCOPE_D uint16 isobus_initDiagnostic(uint8 instanceNum_u8,
                                     uint8 srcAddr_u8,
                                     uint16 dmType_u16,
                                     isobus_dtcList_ts *dtcList_ps,
                                     uint16 boxNum_u16,
                                     isobus_rxCallback_tpf func_pf);

SCOPE_D uint16 isobus_getDiagnostic(uint8 instanceNum_u8,
                                    uint8 destAddr_u8,
                                    uint16 dmType_u16);

SCOPE_D uint16 isobus_getStatus(uint8 instanceNum_u8);

SCOPE_D void isobus_setCaName(uint8 instanceNum_u8,
                              uint8 arbitAddrCapable_u8,
                              uint8 industryGroup_u8,
                              uint8 deviceInstance_u8,
                              uint8 deviceClass_u8,
                              uint8 function_u8,
                              uint8 functionInstance_u8,
                              uint8 ecuInstance_u8,
                              uint16 manufacturerCode_u16);

SCOPE_D uint16 isobus_sendRequestPGN(uint8 instanceNum_u8,
                                     uint8 destAddr_u8,
                                     uint32 pgn_u32);

SCOPE_D uint16 isobus_registerInstances(isobus_appInst_ts *mem_pas,
                                        uint16 num_u16);

SCOPE_D uint16 isobus_setCaAddr(uint8 instanceNum_u8,
                                uint8 canChnl_u8,
                                uint8 ownAddr_u8);

SCOPE_D uint8 isobus_getCaAddr(uint8 instanceNum_u8);

SCOPE_D void isobus_setCaInfo(uint8  instanceNum_u8,
                              sint8 *ecuLoc_pas8,
                              sint8 *ecuType_pas8,
                              sint8 *ecuMan_pas8,
                              sint8 *applTask_pas8);

//**************************************************************************************************

#undef SCOPE_D

#undef _ISOBUS_API_D         // reseting definition, prevents double definition of a variable if
                              // includes are nested
#endif  // _ISOBUS_API_H_D

// EOF #############################################################################################
