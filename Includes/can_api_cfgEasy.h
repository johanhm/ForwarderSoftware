/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        can_api_cfgEasy.h
*
*  \brief       Interface for easy configuration of CAN buffers and databoxes.
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   API RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 2403 $
*                            $Date: 2010-02-08 17:53:04 +0100 (Mo, 08 Feb 2010) $
*                            $Author: gtg2si $
*
* REVISION HISTORY:
*
***************************************************************************************************/

#ifndef _CAN_API_CFGEASY_H_D   /* replace it with the filename in capital letters */
#define _CAN_API_CFGEASY_H_D   /* replace it with the filename in capital letters */


/**** include files ********************************************************************************
* List of include files needed in this module. DO NOT INCLUDE HEADER FILES WITH VARIABLE           *
* DECLARATIONS HERE! ONLY TYPEDEFS OR DEFINES ARE ALLOWED!                                        */

#include "can_api.h"

#ifdef _CAN_API_CFGEASY_D      /* replace it with the filename in capital letters */
   #define SCOPE_D
#else
   #define SCOPE_D extern
#endif   /* _CAN_API_CFGEASY_D */

/**** defines **************************************************************************************
* List of defines needed in this header file and defines to be made available to other modules.   */


/***************************************************************************************************
*  FUNCTION:      can_cfgTxBuf
*/
/**\brief         A transmit buffer is configured/defined in the API for a CAN channel.
*
* In contrast to can_registerTxBuf() the buffer will be declared by API itself.
* Errors are messaged by API error handling as can_registerTxBuf() errors.
*
* \param[in]      chnl_u8           node number, either CAN_1, CAN_2, CAN_3, CAN_4
* \param[in]      numMsg_u16        number of CAN messages
*
* \return         error code        same values as can_registerTxBuf()
*/
/**************************************************************************************************/

#define can_cfgTxBuf(chnl_u8, numMsg_u16)                                                          \
({                                                                                                 \
  static can_Message_ts BRAPI_can_TxBuf_##chnl_u8##_as[numMsg_u16];                                \
                                                                                                   \
  can_registerTxBuf(chnl_u8, BRAPI_can_TxBuf_##chnl_u8##_as, numMsg_u16);                          \
})

/**************************************************************************************************/


/***************************************************************************************************
*  FUNCTION:      can_cfgRxBuf
*/
/**\brief         A receive buffer is configured/declared in the API for a CAN channel.
*
* In contrast to can_registerRxBuf() the buffer will be declared by API itself.
* Errors are messaged by API error handling as can_registerRxBuf() errors.
*
* \param[in]      chnl_u8           node number, either CAN_1, CAN_2, CAN_3, CAN_4
* \param[in]      numMsg_u16        number of CAN messages
*
* \return         error code        same values as can_registerRxBuf()
*/
/**************************************************************************************************/

#define can_cfgRxBuf(chnl_u8, numMsg_u16)                                                          \
({                                                                                                 \
  static can_Message_ts BRAPI_can_RxBuf_##chnl_u8##_as[numMsg_u16];                                \
                                                                                                   \
  can_registerRxBuf(chnl_u8, BRAPI_can_RxBuf_##chnl_u8##_as, numMsg_u16);                          \
})

/**************************************************************************************************/


/***************************************************************************************************
*  FUNCTION:      can_cfgTxDataboxes
*/
/**\brief         Transmit databoxes are configured/declared in the API for a CAN channel.
*
* In contrast to can_registerTxDataboxes() the buffer will be declared by API itself.
* Errors are messaged by API error handling as can_registerTxDataboxes() errors.
*
* \param[in]      chnl_u8           node number, either CAN_1, CAN_2, CAN_3, CAN_4
* \param[in]      num_u16           number of transmit databoxes
*
* \return         error code        same values as can_registerTxDataboxes()
*/
/**************************************************************************************************/

#define can_cfgTxDataboxes(chnl_u8, num_u16)                                                       \
({                                                                                                 \
  static can_TxDatabox_ts BRAPI_can_TxDataboxes_##chnl_u8##_as[num_u16];                           \
                                                                                                   \
  can_registerTxDataboxes(chnl_u8, BRAPI_can_TxDataboxes_##chnl_u8##_as, num_u16);                 \
})

/**************************************************************************************************/


/***************************************************************************************************
*  FUNCTION:      can_cfgRxDataboxes
*/
/**\brief         Receive databoxes are configured/declared in the API for a CAN channel.
*
* In contrast to can_registerRxDataboxes() the buffer will be declared by API itself.
* Errors are messaged by API error handling as can_registerRxDataboxes() errors.
*
* \param[in]      chnl_u8           node number, either CAN_1, CAN_2, CAN_3, CAN_4
* \param[in]      num_u16           number of receive databoxes
*
* \return         error code        same values as can_registerRxDataboxes()
*/
/**************************************************************************************************/

#define can_cfgRxDataboxes(chnl_u8, num_u16)                                                       \
({                                                                                                 \
  static can_RxDatabox_ts BRAPI_can_RxDataboxes_##chnl_u8##_as[num_u16];                             \
                                                                                                   \
  can_registerRxDataboxes(chnl_u8, BRAPI_can_RxDataboxes_##chnl_u8##_as, num_u16);                 \
})

/**************************************************************************************************/


/***************************************************************************************************
*  FUNCTION:      can_cfgRxDatabox
*/
/**\brief         A receive databox is initialised include buffer definition.
*
* In contrast to can_initRxDatabox():
* - number of bytes are fix = 8
* - the buffer will be declared by API itself.
* - the length of buffer is fix = 1
* - there is no callback available
* Errors are messaged by API error handling as can_initRxDatabox() errors.
*
* \param[in]      chnl_u8           node number, either CAN_1, CAN_2, CAN_3, CAN_4
* \param[in]      databoxNum_u16    number of data box
* \param[in]      id_u32            message identifier
* \param[in]      format_u8         format of the message, either CAN_STD (standard 11 bit) or
*                                   CAN_EXD (extended 29 bit)
* \return         error code        same values as can_initCfgRxDatabox()
*/
/**************************************************************************************************/

#define can_cfgRxDatabox(chnl_u8, databoxNum_u16, id_u32, format_u8)                           \
({                                                                                                 \
  static can_DataboxData_ts BRAPI_can_RxDataboxData_##chnl_u8##_##databoxNum_u16##_as[1];          \
                                                                                                   \
  can_initRxDatabox(chnl_u8, databoxNum_u16, id_u32, format_u8, 8,                                 \
                    BRAPI_can_RxDataboxData_##chnl_u8##_##databoxNum_u16##_as, 1, NULL);           \
})

/**************************************************************************************************/


/***************************************************************************************************
*  FUNCTION:      can_cfgTxDatabox
*/
/**\brief         Initialise a transmit databox of a node.
*
* See description of can_initTxDatabox().
* * Errors are messaged by API error handling as can_initTxDatabox() errors.
*
* \param[in]      chnl_u8           node number, either CAN_1, CAN_2, CAN_3, CAN_4
* \param[in]      databoxNum_u16    number of transmit databox
* \param[in]      id_u32            message identifier
* \param[in]      format_u8         format of the message, either CAN_STD (standard 11 bit) or
*                                   CAN_EXD (extended 29 bit)
*
* \return         error code        same values as can_initCfgTxDatabox()
*/
/**************************************************************************************************/

#define can_cfgTxDatabox can_initTxDatabox

/**************************************************************************************************/


/***************************************************************************************************
*  FUNCTION:      can_cfgBufs
*/
/**\brief         All buffers and databoxes of a CAN channel are declared and registered in API.
*
* Errors are messaged by API error handling as errors of can_registerTxBuf(), can_registerRxBuf,
* can_registerTxDataboxes, can_registerRxDataboxes.
* Note: Databoxes has to be initialised before using.
*       See can_initTxDatabox() and can_initCfgRxDatabox( )/ can_initRxDatabox() .
*
* \param[in]      chnl_u8             node number, either CAN_1, CAN_2, CAN_3, CAN_4
* \param[in]      numMsgTxBuf_u16     number of CAN messages of transmit buffer
* \param[in]      numMsgRxBuf_u16     number of CAN messages of receive buffer
* \param[in]      numTxDataboxes_u16  number of transmit databoxes
* \param[in]      numRxDataboxes_u16  number of receive databoxes
*
* \return         error code          Error is signaled by setting a bit in error code (0 = ok):
*                                       bit 0 : error config. Tx buffer
*                                       bit 1 : error config. Rx buffer
*                                       bit 2 : error config. Tx databoxes
*                                       bit 3 : error config. Rx databoxes
*/
/**************************************************************************************************/

#define can_cfgBufs(chnl_u8, numMsgTxBuf_u16, numMsgRxBuf_u16,                                     \
                    numTxDataboxes_u16, numRxDataboxes_u16)                                        \
({                                                                                                 \
  uint16 BRAPI_error_can_cfgBufs_u16; /* tempary var. in order to return an error */               \
                                                                                                   \
  BRAPI_error_can_cfgBufs_u16 = 0; /* no error */                                                  \
                                                                                                   \
  /* avoid error in standard API function */                                                       \
  if (numMsgTxBuf_u16 != 0)                                                                        \
  {                                                                                                \
    if (can_cfgTxBuf(chnl_u8, numMsgTxBuf_u16) != 0)                                               \
    {                                                                                              \
      BRAPI_error_can_cfgBufs_u16 = BRAPI_error_can_cfgBufs_u16 | 0x1; /* bit 0 */                 \
    }                                                                                              \
  }                                                                                                \
                                                                                                   \
  /* avoid error in standard API function */                                                       \
  if (numMsgRxBuf_u16 != 0)                                                                        \
  {                                                                                                \
    if (can_cfgRxBuf(chnl_u8, numMsgRxBuf_u16) != 0)                                               \
    {                                                                                              \
      BRAPI_error_can_cfgBufs_u16 = BRAPI_error_can_cfgBufs_u16 | 0x2; /* bit 1 */                 \
    }                                                                                              \
  }                                                                                                \
                                                                                                   \
  /* avoid error in standard API function */                                                       \
  if (numTxDataboxes_u16 != 0)                                                                     \
  {                                                                                                \
    if (can_cfgTxDataboxes(chnl_u8, numTxDataboxes_u16) != 0)                                      \
    {                                                                                              \
      BRAPI_error_can_cfgBufs_u16 = BRAPI_error_can_cfgBufs_u16 | 0x4; /* bit 2 */                 \
    }                                                                                              \
  }                                                                                                \
                                                                                                   \
  /* avoid error in standard API function */                                                       \
  if (numRxDataboxes_u16 != 0)                                                                     \
  {                                                                                                \
    if (can_cfgRxDataboxes(chnl_u8, numRxDataboxes_u16) != 0)                                      \
    {                                                                                              \
      BRAPI_error_can_cfgBufs_u16 = BRAPI_error_can_cfgBufs_u16 | 0x8; /* bit 3 */                 \
    }                                                                                              \
  }                                                                                                \
                                                                                                   \
  /* return error */                                                                               \
  BRAPI_error_can_cfgBufs_u16;                                                                     \
})

/**************************************************************************************************/


/**** typdefs/structures ***************************************************************************
* Typedefs/structures to be made available to other modules.                                      */


/**** public functions *****************************************************************************
* Declarations of functions to be made available to other modules. Use SCOPE in front of each      *
* line.                                                                                           */


/**************************************************************************************************/

#undef SCOPE_D
/* Reseting definition, prevents double definition of a variable if
*  includes are nested. Replace it with the filename in capital letters. */
#undef _CAN_API_CFGEASY__D

#endif /* _CAN_API_CFGEASY_H_D */

/**************************************************************************************************/

/* EOF ########################################################################################## */
