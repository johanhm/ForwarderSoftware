
/** \defgroup AJS Angle Joint Sensors
 * \ingroup SENSORS
 * \brief Handle the angle measurements of the joints front and back.
 *
 *  Does the following:
 *
 *  1. Configure the Angle joint sensors.
 *  2. Provide functionality to update angle data with complementary filter.
 *  3. Get the angle of front or back wagon.
 *
 *  @{
 */

#ifndef XT28TRANSMITIONAPP_ANGLEJOINTSENSOR_H_
#define XT28TRANSMITIONAPP_ANGLEJOINTSENSOR_H_

#include "api_lib_basic.h"

/*! Angle sensors of joints */
///@{
#define AIV_Angle_sensor_F_sig1		(IN_30_AIV)
#define AIV_Angle_sensor_F_sig2		(IN_31_AIV)
#define AIV_Angle_sensor_R_sig1		(IN_32_AIV)
#define AIV_Angle_sensor_R_sig2		(IN_8_AIV)
///@}


/*! \name Configure and uppdate */
///@{
/*!
 * Configure and initialize the sensors connected to angle joint sensors. This function is mandatory to call to configure the sensors.
 */
void AJSInitAngleJointSensors(void);

/*!
 * Update the sensor data
 */
void AJSUppdateAngleSensorData(void);
///@}


/*! \name CAN */
///@{
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
///@}


/*! \name Angle joint Outputs */
///@{
/*!
 * Get front angle in [deg]
 * @return [-25 deg to 25 deg]
 */
int AJSGetAngleFront(void);

/*!
 * Get back angle in [deg]
 * @return [-25 deg to 25 deg]
 */
int AJSGetAngleBack(void);
///@}


#endif /* XT28TRANSMITIONAPP_ANGLEJOINTSENSOR_H_ */
/** @}*/
