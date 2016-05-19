

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

extern sint32 g_debug1;
extern sint32 g_debug2;
extern sint32 g_debug3;
extern sint32 g_debug4;
extern sint32 g_debug5;
extern sint32 g_debug6;

/*!
 * Set up CAN for the transmissition ECU
 */
void XT28TCANInitAndSetup(void);

/*!
 * Send the debugg variabels
 * @param CANChannel
 */
void CANSendDebuggMessage(uint8 CANChannel);



#endif /* XT28TRANSMITIONAPP_XT28TRANSMISSIONCANSUPPORT_H_ */
