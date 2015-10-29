//**************************************************************************************************
//
//  FILENAME:    j1939_api.h
//
//  DESCRIPTION:
//! \file        j1939_api.h
//! \brief       header file for J1939 API functions
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_Plattform
//
// FILE VERSION INFORMATION:  $Revision: 5898 $
//                            $Date: 2013-06-03 12:36:35 +0200 (Mo, 03 Jun 2013) $
//                            $Author: oub2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _J1939_API_H_D
  #define _J1939_API_H_D


//*** include files ********************************************************************************
// List of include files needed in this module.
#include "common_api.h"     //standard type definitions

#ifdef _J1939_API_D
  #define SCOPE_D
#else
  #define SCOPE_D extern
#endif   // _J1939_API_D

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

//--- j1939 rx/tx databox status
#define J1939_BOXSTATUS_NONE_DU16         0x0000 // message box is not yet initialized
#define J1939_BOXSTATUS_INIT_DU16         0x0100 // message box is initialized
#define J1939_BOXSTATUS_VALID_DU16        0x0200 // rx message box data are valid
#define J1939_BOXSTATUS_VAL_OVFL_DU16     0x0201 // rx data are valid, but overflow occurs (DM1/2)
#define J1939_BOXSTATUS_INV_SEQNBR_DU16   0x0301 // data are invalid, wrong sequence nbr received
#define J1939_BOXSTATUS_INV_ABORT_DU16    0x0302 // data are invalid, rx/tx transfer aborted
#define J1939_BOXSTATUS_INV_TIMEOUT_DU16  0x0303 // data are invalid, timeout occurs
#define J1939_BOXSTATUS_INV_OVFL_DU16     0x0304 // data are invalid, overflow error
#define J1939_BOXSTATUS_PENDING_DU16      0x0400 // tx message waits for sending, tx not yet started
#define J1939_BOXSTATUS_BAM_RX_DU16       0x0500 // receiving of a BAM message is in progress
#define J1939_BOXSTATUS_BAM_TX_DU16       0x0600 // transmitting of a BAM message is in progress
#define J1939_BOXSTATUS_UNPACK_DU16       0x0700 // unpacking of received DM1/2 BAM is in progress

#define J1939_BOXSTATUS_MASK_DU16         0xFF00  // Status mask for main status

//--- j1939 controller application status (main status = hi byte, sub status = lo byte)
#define J1939_CASTATUS_NONE_DU16          0x0000  // CA is not yet initialized
#define J1939_CASTATUS_INIT_DU16          0x0100  // CA is initialized
#define J1939_CASTATUS_WAIT_CLAIM_DU16    0x0200  // CA waits for could claim an address
#define J1939_CASTATUS_ADDR_CLAIMED_DU16  0x0300  // CA could claim an address (operation state)
#define J1939_CASTATUS_CANNOT_CLAIM_DU16  0x0400  // CA could not claim an address

#define J1939_CASTATUS_MASK_DU16          0xFF00  // Status mask for main status
#define J1939_SUBSTATUS_TIMEOUT_DU16      0x0001  // j1939 cycle timeout occured
#define J1939_SUBSTATUS_RXOVFL_DU16       0x0002  // rx buffer overflow occured


//--- return codes of j1939 functions
#define J1939_RC_NO_ERRORS_DU16        0    // ok
#define J1939_RC_INVALID_ADDR_DU16     1    // invalid address
#define J1939_RC_INV_DATABOX_DU16      2    // invalid data box number
#define J1939_RC_INV_PGN_DU16          3    // invalid pgn
#define J1939_RC_INV_SRC_DU16          4    // invalid source address
#define J1939_RC_INV_TIMEOUT_DU16      5    // invalid timeout value for rx msg
#define J1939_RC_INV_DATA_LEN_DU16     6    // invalid data length
#define J1939_RC_INV_DATA_PTR_DU16     7    // invalid data address
#define J1939_RC_OVERLAP_ADDR_DU16     8    // address overlaps with other buffers
#define J1939_RC_INV_STARTTIMEOUT_DU16 9    // invalid start timeout value for rx msg

#define J1939_RC_INV_CYCLE_DU16       10    // invalid cycle time for tx msg
#define J1939_RC_INV_OFFSET_DU16      11    // invalid offset time for tx msg
#define J1939_RC_INV_PRIO_DU16        12    // invalid priority of msg

#define J1939_RC_PGN_SRC_EXIST_DU16   20    // Data box with same pgn+src already exists
#define J1939_RC_PGN_PRIO_EXIST_DU16  21    // Data box with same pgn+prio already exists
#define J1939_RC_CFG_NOTALLOWED_DU16  22    // configuration is not allowed

#define J1939_RC_INV_BOX_STATUS_DU16  30    // invalid data box status

#define J1939_RC_INV_SPN_DU16         40    // invalid SPN
#define J1939_RC_INV_FMI_DU16         41    // invalid FMI
#define J1939_RC_DM1_FULL_DU16        42    // max nbr of DM1 failures reached
#define J1939_RC_DM2_FULL_DU16        43    // max nbr of DM2 failures reached
#define J1939_RC_SPN_NOT_FOUND_DU16   44    // SPN is not stored in list

#define J1939_RC_INV_ECU_ADDR_DU16    50    // invalid ECU address
#define J1939_RC_INV_DM_TYPE_DU16     51    // invalid DM type

#define J1939_RC_INV_LIST_SIZE_DU16   60    // invalid list size
#define J1939_RC_INV_EE_PAGE_DU16     61    // invalid eeprom page nbr
#define J1939_RC_INV_EE_IDX_DU16      62    // invalid eeprom start index of failure list
#define J1939_RC_INIT_MISSING_DU16    63    // function not allowed without initialization

#define J1939_RC_EEP_OVERFLOW_DU16    70    // internal eeprom queue overflow

#define J1939_RC_DM1_NOT_EXIST_DU16    0    // DM1 failure does not exits within DM1 failure list
#define J1939_RC_DM1_EXIST_DU16        1    // DM1 failure exists within DM1 failure list

//--- special parameter values used by API functions
#define J1939_SPN_ALL_DU32            0xFFFFFFFFu
#define J1939_FMI_ALL_DU8             0xFFu

#define J1939_LIST_NONE_DU16        0x00    // DM failure list type NULL
#define J1939_LIST_DM1_DU16         0x01    // DM failure list type DM1
#define J1939_LIST_DM2_DU16         0x02    // DM failure list type DM2
#define J1939_LIST_DM1_V1_DU16      0x11    // DM failure list type DM1 and CM version 1
#define J1939_LIST_DM2_V1_DU16      0x12    // DM failure list type DM2 and CM version 1
#define J1939_LIST_DM1_V2_DU16      0x21    // DM failure list type DM1 and CM version 2
#define J1939_LIST_DM2_V2_DU16      0x22    // DM failure list type DM2 and CM version 2
#define J1939_LIST_DM1_V3_DU16      0x31    // DM failure list type DM1 and CM version 3
#define J1939_LIST_DM2_V3_DU16      0x32    // DM failure list type DM2 and CM version 3

#define J1939_DTC_LIST_SIZE_DU16      20    // DM failure list size (DTCs of another ECU)

#define J1939_CM1_VERSION1_DU16     0x10    // DTC conversion mode Version 1 in case of CM-Bit = 1
#define J1939_CM1_VERSION2_DU16     0x20    // DTC conversion mode Version 2 in case of CM-Bit = 1
#define J1939_CM1_VERSION3_DU16     0x30    // DTC conversion mode Version 3 in case of CM-Bit = 1
#define J1939_CM1_MASK_DU16         0xF0u   // DTC conversion mode mask


//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.

// PRQA S 635 ++

typedef struct j1939_canID_pkt_t
{
  /* first byte in memory */
  uint8 SourceAddr_u8 : 8;   // this byte is the node id of the sender of this message
  uint8 PDUSpecial_u8 : 8;   // when the pdu format value is < 240, this byte contents the
                             // destination address. when the pdu format value is 240 to 255, it
                             // contents the group extension
  uint8 PDUFormat_u8  : 8;   // this byte is used as a part of the pgn
  uint8 DataPage_u2   : 2;   // these bits identify the data pages of the parameter group
  uint8 Priority_u3   : 3;   // these 3 bits define the priority of the following message
  uint8 unusedBits_u3 : 3;   // these 3 bits are overhead for the 29 bit data
  /* last byte in memory */
}  __attribute__ ((packed)) j1939_canID_ts;

typedef union j1939_canID_t
{
   j1939_canID_ts canID_s;
   uint32         canID_u32;
} j1939_canID_tu;

//--- definition of the callback functions
// j1939 receive callback function
typedef void (*j1939_rxCallback_tpf) (void);
// j1939 transmit callback function
typedef void (*j1939_txCallback_tpf) (void);

// structure of a j1939 rx databox message definition within the array of defined rx messages
typedef struct j1939_rxMsg_t
{
  j1939_canID_tu canID_u;       // can identity of msg to be received
  uint16 timeout_u16;           // timeout (ms) for supervision of cyclic msg
  uint16 startTimeout_u16;      // timeout (ms) for supervision of first msg after start-up
  uint16 counter_u16;           // actual time counter for timeout supervision
  uint16 status_u16;            // msg status, e.g. valid, invalid, timeout
  uint16 action_u16;            // action (e.g. data conversion) to be done after reception
  uint16 lenAct_u16;            // total length of actual completely received msg
  uint16 lenRx_u16;             // length of already received msg part
  uint16 lenMax_u16;            // max length of the receive buffer defined below
  uint8  *data_pau8;            // pointer to data array with length=lenMax_u16
  j1939_rxCallback_tpf func_pf; // function is called if msg received completely
} j1939_rxMsg_ts;

// structure of a j1939 tx databox message definition within the array of defined tx messages
typedef struct j1939_txMsg_t
{
  j1939_canID_tu canID_u;       // can identity of msg to be sent
  uint16 cycle_u16;             // cycle time for sending this msg
  uint16 counter_u16;           // actual time counter for cyclic sending
  uint16 status_u16;            // msg status, e.g. valid, invalid
  uint16 lenTx_u16;             // length of already transmitted msg part
  uint16 lenAct_u16;            // total length of actual msg to be sent
  uint8  *data_pau8;            // pointer to data array with length=lenAct_u16
  j1939_txCallback_tpf func_pf; // function is called before msg is to be sent
} j1939_txMsg_ts;

// structure of one DTC (NOT packed)
typedef struct j1939_dtc_t
{
  uint32 spn_u32;    // suspect parameter number
  uint8  fmi_u8;     // failure mode indicator
  uint8  occ_u8;     // occurrence counter
} j1939_dtc_ts;

// structure of one lamp status (NOT packed)
typedef struct j1939_lamp_t
{
  uint8  lampState_u8;     // lamp status
  uint8  lampFlash_u8;     // lamp flash
} j1939_lamp_ts;

// structure of one failure (NOT packed) within the failure lists for application access
typedef struct j1939_failure_t
{
  j1939_dtc_ts    dtc_s  __attribute__ ((aligned (4)));        // 32 Bit: DTC
  j1939_lamp_ts   lamp_s __attribute__ ((aligned (4)));        // 16 Bit: lamp and flash status
} j1939_failure_ts;

// structure of received and converted DM1/2 failure lists
typedef struct j1939_dtcList_t
{
  j1939_lamp_ts  lamp_s __attribute__ ((aligned (4)));                              // lamp status
  j1939_dtc_ts   dtc_as[J1939_DTC_LIST_SIZE_DU16] __attribute__ ((aligned (4)));    // DTC list
} j1939_dtcList_ts;

// structure of all data for one error handler instance for DM1 and DM2 failures
typedef struct ptr_t
{
  j1939_failure_ts  *list_pas;        // pointer to DM1 failure list (array)
  uint16            size_u16;         // size of failure list array above
  uint16            nbrAct_u16;       // actual number of active (DM1) failures within failure list
  uint16            eePage_u16;       // eeprom page nbr for DM2 failure list
  uint16            eeIndex_u16;      // eeprom start index for DM2 failure list (1.Int = amount!)
  uint16            txBoxDM1_u16;     // TX box nbr for sending the DM1 failures
  uint16            txBoxDM2_u16;     // TX box nbr for sending the DM2 failures
} j1939_errHndl_ts;

// PRQA S 635 --

//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.

// variables for one instance of the error handler
SCOPE_D j1939_errHndl_ts   j1939_errHndl_s;     // contains all global data of error handler

#ifdef _J1939_API_D
  j1939_errHndl_ts *j1939_errHndl_ps = &j1939_errHndl_s;  // ptr to global error handler structure
#else
  extern j1939_errHndl_ts *j1939_errHndl_ps;
#endif   // _J1939_API_D


//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.

SCOPE_D void j1939_initComm(uint8 canChnl_u8,
                            uint8 ownAddr_u8,
                            uint8 priority_u8,
                            uint8 cycleTime_u8,
                            uint8 maxTime_u8);

SCOPE_D uint16 j1939_registerRxDataboxes(j1939_rxMsg_ts *mem_pas, uint16 num_u16);

SCOPE_D uint16 j1939_registerTxDataboxes(j1939_txMsg_ts *mem_pas, uint16 num_u16);

SCOPE_D uint16 j1939_initRxDatabox(uint16 boxNum_u16,
                                   uint32 pgn_u32,
                                   uint8  src_u8,
                                   uint16 timeout_u16,
                                   uint16 startTimeout_u16,
                                   uint16 lenMax_u16,
                                   uint8  *data_pau8,
                                   j1939_rxCallback_tpf func_pf);

SCOPE_D uint16 j1939_initTxDatabox(uint16 boxNum_u16,
                                   uint32 pgn_u32,
                                   uint8  prio_u8,
                                   uint16 cycle_u16,
                                   uint16 offset_u16,
                                   uint16 lenAct_u16,
                                   uint8  *data_pau8,
                                   j1939_txCallback_tpf func_pf);

SCOPE_D uint16 j1939_sendDatabox(uint16 boxNum_u16);

SCOPE_D uint16 j1939_getRxDataboxStatus(uint16 boxNum_u16, uint16 *msgLen_pu16);

SCOPE_D uint16 j1939_initFailureList(j1939_failure_ts  *listFailure_pas,
                                     uint16            listSize_u16,
                                     uint16            eePage_u16,
                                     uint16            eeIndex_u16,
                                     uint16            txBoxDM1_u16,
                                     uint16            txBoxDM2_u16);

SCOPE_D uint16 j1939_setFailureDM1(uint32 spn_u32,
                                   uint8  fmi_u8,
                                   uint8  lampState_u8,
                                   uint8  lampFlash_u8);

SCOPE_D uint16 j1939_resetFailureDM1(uint32 spn_u32, uint8  fmi_u8);

SCOPE_D uint16 j1939_testFailureDM1(uint32 spn_u32, uint8  fmi_u8);

SCOPE_D uint16 j1939_resetFailureDM2(void);

SCOPE_D uint16 j1939_initDiagnostic(uint8             srcAddr_u8,
                                    uint16            dmType_u16,
                                    j1939_dtcList_ts  *dtcList_ps,
                                    uint16            boxNum_u16,
                                    j1939_rxCallback_tpf func_pf);

SCOPE_D uint16 j1939_getDiagnostic(uint8  destAddr_u8,
                                 uint16 dmType_u16);

SCOPE_D uint16 j1939_getStatus(uint8 canChnl_u8);

SCOPE_D void j1939_setCaName(uint8 industryGroup_u8,
                             uint8 vehicleInstance_u8,
                             uint8 vehicleSystem_u8,
                             uint8 function_u8,
                             uint8 functionInstance_u8,
                             uint8 ecuInstance_u8);

SCOPE_D uint16 j1939_sendRequestPGN(uint8  destAddr_u8,
                                    uint32 pgn_u32);

//**************************************************************************************************

#undef SCOPE_D

#undef _J1939_API_D         // reseting definition, prevents double definition of a variable if
                              // includes are nested
#endif  // _J1939_API_H_D

// EOF #############################################################################################
