//**************************************************************************************************
//
//  FILENAME:    dia_constants.h
//
//  DESCRIPTION:
//! \file        dia_constants.h
//! \brief       protocol specific defines
//
//**************************************************************************************************
// (c) Copyright by BOSCH REXROTH AG, all rights reserved
//**************************************************************************************************
//
// PROJECT:                   RC30_Plattform
//
// FILE VERSION INFORMATION:  $Revision: 2450 $
//                            $Date: 2010-02-12 11:59:09 +0100 (Fr, 12 Feb 2010) $
//                            $Author: oub2si $
//
// REVISION HISTORY:
//
//
//**************************************************************************************************

#ifndef _DIA_CONSTANTS_H_D
  #define _DIA_CONSTANTS_H_D

//*** include files ********************************************************************************
// List of include files needed in this module.

//*** defines **************************************************************************************
// List of defines needed in this header file and defines to be made available to other modules.

// *************************************************************************************************
// D A T A   I D E N T I F I E R S   ( D I D )
// *************************************************************************************************

#define DID_INVALID_IDENTIFIER_DU16                         0x0000

// *************************************************************************************************
// S E R V I C E   I D E N T I F I E R S   ( S I D )
// *************************************************************************************************

#define SID_DiagnosticSessionControl_DU8                    0x10u
#define SID_ReadECUIdentification_DU8                       0x1Au
#define SID_SecurityAccess_DU8                              0x27u
#define SID_TesterPresent_DU8                               0x3Eu
#define SID_ECUReset_DU8                                    0x11u
#define SID_ReadDataByIdentifier_DU8                        0x22u
#define SID_DynamicDefineIdentifier_DU8                     0x2Cu
#define SID_WriteDataByIdentifier_DU8                       0x2Eu
#define SID_ReadMemoryByAddress_DU8                         0x23u
#define SID_WriteMemoryByAddress_DU8                        0x3Du
#define SID_RequestDownload_DU8                             0x34u
#define SID_RequestUpload_DU8                               0x35u
#define SID_TransferData_DU8                                0x36u
#define SID_RequestTransferExit_DU8                         0x37u
#define SID_RoutineControl_DU8                              0x31u
#define SID_NodeControl_DU8                                 0xBAu
#define SID_DynamicDefineIdentifierBR_DU8                   0xBBu
#define SID_BODAS_RTS_COMMUNICATION_DU8                     0xBEu
#define SID_negativeResponse_DU8                            0x7Fu

// *************************************************************************************************
// L O C A L   I D E N T I F I E R S   ( L I D )
// *************************************************************************************************

// ... for SID_DiagnosticSessionControl_DU8
#define LID_DefaultSession_DU8                              0x81u
#define LID_DemoSession_DU8                                 0x80u
#define LID_ServiceSession_DU8                              0x91u
#define LID_AdjustmentSession_DU8                           0xB3u
#define LID_DevelopmentSession_DU8                          0xF7u
// ... for SID_SecurityAccess_DU8
#define LID_RequestSeedDEMO_DU8                             0x05u
#define LID_SendKeyDEMO_DU8                                 0x06u
#define LID_RequestSeedSERVICE_DU8                          0x07u
#define LID_SendKeySERVICE_DU8                              0x08u
#define LID_RequestSeedADJUSTMENT_DU8                       0x09u
#define LID_SendKeyADJUSTMENT_DU8                           0x0Au
#define LID_RequestSeedDEVELOPMENT_DU8                      0x0Bu
#define LID_SendKeyDEVELOPMENT_DU8                          0x0Cu
#define LID_RequestSeedBOOTBLOCK_DU8                        0x0Du
#define LID_SendKeyBOOTBLOCK_DU8                            0x0Eu
#define LID_RequestSeedPassword_DU8                         0x60u
#define LID_SetPassword_DU8                                 0x61u
#define LID_SetScrambledPassword_DU8                        0x62u
// ... for SID_TesterPresent_DU8
#define LID_SuppressResponseFalse_DU8                       0x00u
#define LID_SuppressResponseTrue_DU8                        0x80u
// ... for SID_ECUReset_DU8
#define LID_PowerOnReset_DU8                                0x01u
// ... for SID_DynamicDefineIdentifier_DU8 and SID_DynamicDefineIdentifierBR_DU8
#define LID_DefineByIdentifier_DU8                          0x01u
#define LID_DefineByMemoryAddress_DU8                       0x02u
// ... for SID_RequestDownload_DU8 and SID_RequestUpload_DU8
#define LID_NoEncryptionDecription_DU8                      0x00u
// .. for SID_RoutineControl_DU8
#define LID_StartRoutine_DU8                                0x01u
#define LID_StopRoutine_DU8                                 0x02u
#define LID_RequestRoutineResults_DU8                       0x03u
// ...  for SID_NodeControl_DU8
#define LID_PrepareScanning_DU8                             0x01u
#define LID_Scanning_DU8                                    0x02u
#define LID_TestNodeIdentifier_DU8                          0x03u
#define LID_SetNodeIdentifier_DU8                           0x04u
#define LID_GetNodeIdentifier_DU8                           0x05u

// *************************************************************************************************
// D I A G N O S T I C   T R O U B L E   C O D E S   ( D T C )
// *************************************************************************************************

#define DTC_GeneralReject_DU8                               0x10u
#define DTC_ServiceNotSupported_DU8                         0x11u
#define DTC_SubFunctionNotSupported_DU8                     0x12u
#define DTC_InvalidFormat_DU8                               0x13u
#define DTC_ResponseTooLong_DU8                             0x14u
#define DTC_BusyRepeatRequest_DU8                           0x21u
#define DTC_CoditionsNotCorrect_DU8                         0x22u
#define DTC_RequestSequenceError_DU8                        0x24u
#define DTC_RoutineNotComplete_DU8                          0x23u
#define DTC_RequestOutOfRange_DU8                           0x31u
#define DTC_SecurityAccessDenied_DU8                        0x33u
#define DTC_SecurityAccessRequested_DU8                     0x33u
#define DTC_InvalidKey_DU8                                  0x35u
#define DTC_ExceedNumberOfAttempts_DU8                      0x36u
#define DTC_RequiredTimeDelayNotExpired_DU8                 0x37u
#define DTC_DownloadNotAccepted_DU8                         0x40u
#define DTC_ImproperDownloadType_DU8                        0x41u
#define DTC_CanNotDownloadToSpecifiedAddress_DU8            0x42u
#define DTC_CanNotDownloadNumberOfBytesRequested_DU8        0x43u
#define DTC_UploadNotAccepted_DU8                           0x50u
#define DTC_ImproperUploadType_DU8                          0x51u
#define DTC_CanNotUploadFromSpecifiedAddress_DU8            0x52u
#define DTC_CanNotUploadNumberOfBytesRequested_DU8          0x53u
#define DTC_TransferSuspended_DU8                           0x71u
#define DTC_TransferAborted_DU8                             0x72u
#define DTC_IllegalAddressInBlockTransfer_DU8               0x74u
#define DTC_IllegalByteCountInBlockTransfer_DU8             0x75u
#define DTC_IllegalBlockTransferType_DU8                    0x76u
#define DTC_BlockTransferDataChecksumError_DU8              0x77u
#define DTC_RequestCorrrectReceive_RespPending_DU8          0x78u
#define DTC_IncorrectByteCountDuringBlockTransfer_DU8       0x79u
#define DTC_ServiceNotSupportedInActiveDiagnosticMode_DU8   0x80u
#define DTC_GeneralProgFailure_DU8                          0x72u
#define DTC_ServiceNotSupportedInActiveSession_DU8          0x7Fu

// *************************************************************************************************
// E C U   I D E N T I F I C A T I O N   C O D E S   ( E C U )
// *************************************************************************************************

#define ECU_ECUIdentificationDataTable_DU8                  0x80u
#define ECU_ECUSerialNumber_DU8                             0x8Cu
#define ECU_ApplicationName_DU8                             0x8Du
#define ECU_SystemSupplierECUHardwareNumber_DU8             0x92u
#define ECU_SystemSupplierECUHardwareVersionNumber_DU8      0x93u
#define ECU_SystemSupplierECUSoftwareNumber_DU8             0x94u
#define ECU_SystemSupplierECUSoftwareVersionNumber_DU8      0x95u
#define ECU_ProgrammingDate_DU8                             0x99u

// *************************************************************************************************
// other defines
// *************************************************************************************************

#define err_NoError_DU8                                     0x00u
#define SendResponse_DU8                                    0x80u
#define SuppressResponse_DU8                                0x00u
#define diag_Unverified_DU8                                 0x00u
#define diag_Verified_DU8                                   0x01u
#define diag_DeleteSession_DU8                              0x08u
#define diag_keyRequested_DU8                               0x08u
#define diag_ChecksumOK_DU8                                 0x34u
#define diag_ChecksumError_DU8                              0x35u
#define diag_negResponseDLC_DU8                             0x03u

// diagnostics actions which can be controlled via api function diag_permitAccess()
#define DIAG_ACCESS_NONE_DU16                               0x0000  // no access allowed
#define DIAG_ACCESS_RESET_DU16                              0x0001  // reset or flash allowed
#define DIAG_ACCESS_ECU_INFO_DU16                           0x0002  // write ecu info text allowed
#define DIAG_ACCESS_ALL_DU16                                0xFFFF  // whole access allowed

//*** typdefs/structures ***************************************************************************
// Typedefs/structures to be made available to other modules.

//*** public data **********************************************************************************
// Declarations of variables to be made available to other modules.

//*** public functions *****************************************************************************
// Declarations of functions to be made available to other modules.

//**************************************************************************************************

#endif   // _DIA_CONSTANTS_H_D

// EOF #############################################################################################
