

#ifndef XT28TRANSMITIONAPP_ANGLEJOINTSENSOR_H_
#define XT28TRANSMITIONAPP_ANGLEJOINTSENSOR_H_

#include "api_lib_basic.h"

/*! Angle sensors of joints */
#define AIV_Angle_sensor_F_sig1		(IN_30_AIV)
#define AIV_Angle_sensor_F_sig2		(IN_31_AIV)
#define AIV_Angle_sensor_R_sig1		(IN_32_AIV)
#define AIV_Angle_sensor_R_sig2		(IN_8_AIV)

/*!
 * Configure and initialize the sensors connected to angle joint sensors. This function is mandatory to call to configure the sensors.
 */
void AJSInitAngleJointSensors(void);

/*!
 * Update the sensor data
 */
void AJSUppdateAngleSensorData(void);

/*!
 * Configure CAN databox
 * @param CANChannel
 * @param databoxNumber
 * @param AngleSensorID
 */
void AJSConfigureSendDatabox(uint8 CANChannel, int databoxNumber, uint32 AngleSensorID);

/*!
 * Send data on CAN. To use this function the configure CAN function have to be called first in init of the program
 */
void AJSSendAngleDataOnCAN(void);

/*!
 * Get front angle in degree
 * @return
 */
int AJSGetAngleFront(void);

/*!
 * Get back angle
 * @return
 */
int AJSGetAngleBack(void);


#endif /* XT28TRANSMITIONAPP_ANGLEJOINTSENSOR_H_ */
