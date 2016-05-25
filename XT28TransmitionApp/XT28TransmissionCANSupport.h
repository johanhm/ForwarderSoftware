/** \defgroup DRIVECAN Transmission CAN Support
 * \ingroup SUPPORT
 * \brief CAN Support for transmission ECU
 *
 *
 *
 *  @{
 */

#ifndef XT28TRANSMITIONAPP_XT28TRANSMISSIONCANSUPPORT_H_
#define XT28TRANSMITIONAPP_XT28TRANSMISSIONCANSUPPORT_H_

#include "api_lib_basic.h"


#define CAN_ID_TX_SENSOR_INFO_DMS_1				0x18FE1010 	//Sensor data
#define CAN_ID_TX_SENSOR_INFO_DMS_2				0x18FE1011
#define CAN_ID_TX_SENSOR_INFO_DMS_3				0x18FE1012
#define CAN_ID_TX_SENSOR_INFO_DMS_4				0x18FE1020

/*Test*/
#define CAN_ID_DEBUG1	 						0x5
#define CAN_ID_DEBUG2	 						0x8
#define CAN_ID_DEBUG3	 						0x10

extern sint16 g_debug1_1;
extern sint16 g_debug1_2;
extern sint16 g_debug1_3;
extern sint16 g_debug1_4;
extern sint16 g_debug2_1;
extern sint16 g_debug2_2;
extern sint16 g_debug2_3;
extern sint16 g_debug2_4;
extern sint16 g_debug3_1;
extern sint16 g_debug3_2;
extern sint16 g_debug3_3;
extern sint16 g_debug3_4;

/*!
 * Set up CAN for the transmission ECU
 */
void XT28TCANInitAndSetup(void);

/*!
 * Send the debug variables
 * @param CANChannel Channel to send the debug variable on
 */
void CANSendDebuggMessage(uint8 CANChannel);



#endif /* XT28TRANSMITIONAPP_XT28TRANSMISSIONCANSUPPORT_H_ */

/** @}*/
