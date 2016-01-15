/** \defgroup PAPOS Posetion
 * \ingroup Sensors
 * \brief This modules handels the pos sensor data.
 *
 *  @{
 */


#ifndef XT28API_SENSORS_PENDELUMARMPOSITION_H_
#define XT28API_SENSORS_PENDELUMARMPOSITION_H_

#include "api_lib_basic.h"

/*!
 *  Configures the pos sensors
 */
void PAPOSConfigurePositionSensorsVoltageInput(void);

/*!
 *  Uppdate the pos data of the forwarder. This taks need to know the sampletime it is in.
 */
void PAPOSUppdatePosSensorsDataWithSampleTime(int sampleTime_ms);

/*!
 * Get the latest pos data value in mm for a specific wheel
 */
int PAPOSGetPosDataForWheel_mm(int wheel);

/*!
 * Sends pos data on CAN
 */
void PAPOSSendPosDataOnCAN(uint CANChannel, uint32 middleAndBackID, uint32 frontID);

/*!
 * Sends vel data on CAN
 */
void PAPOSSendVelDataOnCAN(uint CANChannel, uint32 middleAndBackID, uint32 frontID);

#endif /* XT28API_SENSORS_PENDELUMARMPOSITION_H_ */
 /** @}*/
