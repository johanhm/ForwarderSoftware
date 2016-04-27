/** \defgroup PAPOS Position
 * \ingroup PASENS
 * \brief Pendulum arm position sensor data.
 *
 * It does the following:
 *
 * 1. Configure input ports on BODAS ECU that the position sensor are connected to
 * 2. Let the user update the sensor data
 * 3. Let the user read the position data
 * 4. Send position data on CAN.
 *
 *  @{
 */


#ifndef XT28API_SENSORS_PENDELUMARMPOSITION_H_
#define XT28API_SENSORS_PENDELUMARMPOSITION_H_

#include "math.h"
#include "XT28CANSupport.h"
#include "api_lib_basic.h"
#include "XT28HardwareConstants.h"

#define POS_UPPDATED_WITH_NO_ERRORS	(0x00)
#define POS_ERROR					(0x01)

/*! \name Configure, Setup and Update */
/*!
 *  Configures the input ports of the position sensors.
 *  \note This function must be called in main() when setting your application if
 *  in order to be able to use the position sensors.
 */
void PAPOSConfigurePositionSensorsVoltageInput(void);

/*!
 *  Update the position data of the forwarder using the sample time.
 *  This function need to be periodical called.
 *
 * @param sampleTime_ms  The sample time this function is called, in unit milliseconds.
 * @return error code
 */
void PAPOSUppdatePosSensorsDataWithSampleTime(int sampleTime_ms);

/*!
 * Check pos sensor for connection error
 * @return
 */
bool PAPOSCheckPosSensorsForErrors(void);
/** @} */

/*! \name Get Sensor Data */
/*!
 * Get the latest position data value in millimeters for a specific wheel
 *
 * @param wheel
 * @return Position data in millimeters
 */
int PAPOSGetPosDataForWheel_mm(int wheel);

/*!
 * Get position data for all wheels in the form of an array. The order is defined in \ref XT28HWC
 *
 * @param posDataOutput		Pointer to the output array.
 */
void PAPOSGetPosDataArray(int posDataOutput[static SUM_WHEELS]);

/*!
 * Get velocity data for a wheel
 *
 * @param wheel
 * @return velocity data in unit millimeters per second
 */
int PAPOSGetVelDataForWheel(int wheel);

/*!
 * Get velocity data array for all wheels. Order defined in \ref XT28HWC
 *
 * @param velDataOutput	Pointer to the output array
 */
void PAPOSGetVelDataArray(float velDataOutput[static SUM_WHEELS]);

/*!
 * Get average height of the machine.
 *
 * @return	Average height of the forwarder in millimeters.
 */
float PAPOSGetAvrageHeightOfForwarder(void);

/*!
 * Get average machine velocity in Z axis
 *
 * @return Average machine velocity in Z axis in unit millimeters per second
 */
float PAPOSGetAvrageHeightVelocityOfForwarder(void);
/** @} */

/**!
 *  Get the angle between front and back wheels
 * @return beta in radians
 */
float PAPOSGetBeta(void);

/*! \name CAN Send */
/*!
 * Sends position data on CAN
 *
  * @param CANChannel		CAN Channel
  * @param middleAndBackID	Extended format
  * @param frontID			Extended format
  */
void PAPOSSendPosDataOnCAN(uint CANChannel, uint32 middleAndBackID, uint32 frontID);

/*!
 * Sends velocity data on CAN
 *
 * @param CANChannel		CAN Channel
 * @param middleAndBackID	Extended format
 * @param frontID			Extended format
 */
void PAPOSSendVelDataOnCAN(uint CANChannel, uint32 middleAndBackID, uint32 frontID);
/** @} */

#endif /* XT28API_SENSORS_PENDELUMARMPOSITION_H_ */
/** @}*/
