/*! \defgroup SUPPORT Support
 *
 * The support group contains functionality that is mainly used for development of the machine.
 */



/** \defgroup XT28CAN CAN
 * \ingroup SUPPORT
 * \brief CAN related functionality. This module does the following:
 *
 * 1. Set up CAN channels with XT28 settings
 * 2. Provide user with functions for sending signed and unsigned int16
 * 3. Send Battery voltage and Debug variables on CAN
 *
 *  @{
 */

#ifndef XT28API_XT28CANSUPPORT_H_
#define XT28API_XT28CANSUPPORT_H_

#include "api_lib_basic.h"

/*!
 *  \name CAN ID Defined in Canalyzer database
 *
 *
 */
///@{
// CAN ID's retrieved
#define CAN_ID_GYRODATA_DATA				0x1FD
#define CAN_ID_ACCELOMETER_DATA				0x2FD

// CAN ID's send out
#define CAN_ID_SENSOR_INFO_SMS_1			0x18FE1020
#define CAN_ID_SENSOR_INFO_SMS_2		    0x18FE1021
#define CAN_ID_SENSOR_INFO_SMS_3			0x18FE1022
#define CAN_ID_SENSOR_INFO_SMS_4			0x18FE1025
#define CAN_ID_SENSOR_INFO_SMS_5			0x18FE1026
#define CAN_ID_SENSOR_INFO_SMS_6			0x18FE1027
#define CAN_ID_SENSOR_INFO_SMS_7			0x18FE1028
#define CAN_ID_SENSOR_INFO_SMS_8			0x18FE1029
#define CAN_ID_SENSOR_INFO_SMS_9			0x18FE102A
#define CAN_ID_SENSOR_INFO_SMS_10			0x18FE102B
#define CAN_ID_SENSOR_INFO_SMS_11			0x18FE102C
#define CAN_ID_SENSOR_INFO_SMS_12			0x18FE102D
#define CAN_ID_SENSOR_INFO_SMS_13			0x18FE102E
#define CAN_ID_SENSOR_INFO_SMS_14			0x18FE2020
#define CAN_ID_SENSOR_INFO_SMS_15			0x18FE202A
#define CAN_ID_SENSOR_INFO_SMS_16			0x18FE202B
#define CAN_ID_SENSOR_INFO_SMS_17			0x18FE202C
#define CAN_ID_SENSOR_INFO_SMS_18			0x18FE202D
#define CAN_ID_SENSOR_INFO_SMS_19			0x18FE202E
#define CAN_ID_SENSOR_INFO_SMS_20			0x18FE202F

#define CAN_ID_DEBUG_MSG_1					0x18FE1050
#define CAN_ID_DEBUG_MSG_2					0x18FE1051
#define CAN_ID_DEBUG_MSG_3					0x18FE1052

#define CAN_ID_DEBUG_MSG_4					0x18FE1053
#define CAN_ID_DEBUG_MSG_5					0x18FE1054
#define CAN_ID_DEBUG_MSG_6					0x18FE1055

#define CAN_ID_REAL_CURRENT_FRONT 			0x17FE0006
#define CAN_ID_REAL_CURRENT_MID 			0x17FE0007
#define CAN_ID_REAL_CURRENT_BACK 			0x17FE0008

#define CAN_ID_REFERENCE_CURRENT_FRONT		0x17FE0001	//Made up for testing purposes
#define CAN_ID_REFERENCE_CURRENT_MID		0x17FE0002
#define CAN_ID_REFERENCE_CURRENT_BACK		0x17FE0003
///@}

/*!
 *  \name Global debug variables
 *  For any module that import CAN Support its possible to use these global variables
 *  to send any data on CAN. To send the data of global debug variables the user have to call CANSendDebuggMessage(uint8 CANChannel) periodically.
 */
///@{
extern sint32 g_debug1;
extern sint32 g_debug2;
extern sint32 g_debug3;
extern sint32 g_debug4;
extern sint32 g_debug5;
extern sint32 g_debug6;
///@}

/*! \name Configure */
/*!
 * This functions does the following:
 *
 * + Configure retrieve buffers for CAN channels
 *    - CAN 1
 *    - CAN 2
 *    - CAN 3
 * + Configure transmit buffers for CAN channels
 *    - CAN 1
 *    - CAN 2
 *    - CAN 3
 * + Register the use of DataBoxes on CAN channels
 *    - CAN 1
 *    - CAN 2
 *    - CAN 3
 *
 */
void CANConfigureXT28CANChannels(void);
/** @}*/



/*! \name Public */
/*!
 * Send a message with four signed integers 16 bit.
 *
 * @param CANChannel	The CAN channel you like to transmit on
 * @param ID			The CAN ID to use
 * @param A				sint16
 * @param B				sint16
 * @param C				sint16
 * @param D				sint16
 */
void CANSend_sint16(uint8 CANChannel, uint32 ID, sint16 A, sint16 B, sint16 C, sint16 D);

/*!
 * Send a message with four unsigned integers 16 bit.
 *
 * @param CANChannel	The CAN channel you like to transmit on
 * @param ID			The CAN ID to use
 * @param A				uint16
 * @param B				uint16
 * @param C				uint16
 * @param D				uint16
 */
void CANSend_uint16(uint8 CANChannel, uint32 ID, uint16 A, uint16 B, uint16 C, uint16 D);
/** @}*/



/*! \name CAN Send */
/*!
 * 	Send the battery voltage on CAN
 *
 * @param CANChannel	The CAN channel you like to transmit on
 * @param ID			The CAN ID to use
 */
void CANSendSupplyVoltageOnCAN(uint8 CANChannel, uint32 ID);

/*!
 * Send Debug variables data on CAN
 *
 * @param CANChannel	The CAN channel you like to transmit on
 */
void CANSendDebuggMessage(uint8 CANChannel);
/** @}*/

#endif /* XT28API_XT28CANSUPPORT_H_ */
/** @}*/
