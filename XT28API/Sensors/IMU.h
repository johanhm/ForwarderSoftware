/*! \defgroup SENSORS Sensors
 *
 *  This group contains the API related to sensors on the forwarder.
 *
 *  In general to be able to use a sensor module the user need to do the following
 *
 *  1. Configure the sensor
 *  2. Initialize the sensor
 *  3. Call the update sensor data function periodically
 *
 */

/** \defgroup IMU IMU
 * \ingroup SENSORS
 * \brief XT28 IMU Configuration and setup.
 *
 *  Does the following:
 *
 *  1. Configure the IMU.
 *  2. Initialize the IMU.
 *  3. Provide functionality to update angle data with complementary filter.
 *  4. Provide functionality to read angels and gyroscope data.
 *  5. Send IMU and filtered angels on CAN.
 *
 *  @{
 */

#ifndef XT28API_SENSORS_IMU_H_
#define XT28API_SENSORS_IMU_H_

#include "api_lib_basic.h"

/*!
 * \name Setup and Initialize
 */
///@{

/*! This function configures the IMU.
 *
 *### Important: ####
 * _This functions must be called in main() to be able to use the IMU Data_
 *
 * \param[in] CANchannel The CAN channel the IMU is connected to
 * \param[in] gyroDataboxNumber The data box the gyroscope should be register to.
 * \param[in] acceleometerDataboxNumber The data box the accelerometer data should be register to.
 *
 */
void IMUConfigureInertialMeasurementUnit(uint8 CANchannel, uint16 gyroDataboxNumber, uint16 acceleometerDataboxNumber);

/*!
 *  This function sends a CAN message that initialize the IMU.
 *
 *  ### Important: ####
 *  This function must be called _after_ CAN init and IMUConfigure();
 *
 *  \return Returns 0 if success. Error messages are not implemented.
 */
uint16 IMUInit(void);
///@}


/*!
 * \name Update IMU Data
 */
///@{
/*!
 * Update IMU data.
 *
 * \note Must be called periodically every 10ms.
 *
 */
void IMUUppdateFilterdAngelsWithComplementaryFilter(void);
/** @}*/


/*!
 * \name Get IMU Sensor data
 */
///@{


/*! Call the get Phi
 *
 * \return Returns the latest value of Phi
 *
 */
float IMUGetPhi(void);

/*!  Call to get Theta
 *
 * \return Returns the latest value of Theta
 */
float IMUGetTheta(void);

/*!
 * Get angle velocity around Y axis. This axis is the same as angle Theta
 *
 * \return gyroVelY
 */
float IMUGetAngleVelY(void);

/*!
 * Get angle velocity around x axis, this is same axis as Phi
 *
 * \return gyroVelX
 */
float IMUGetAngleVelX(void);

///@}


/*!
 * \name CAN Support
 */
///@{

/*! This function will send out the raw values on corresponding can ID when called.
 *
 * \param[in] CANChannel The channel the message should be sent on
 * \param[in] gyroID The id for IMU message. In short format
 * \param[in] accID
 *
 */
void IMUSendIMURawValuesOnCAN(uint8 CANChannel, uint32 gyroID, uint32 accID);

/*!
 *  Send filtered angles Phi and Theta on CAN.
 *
 * @param CANChannel	CANChannel the message is sent on
 * @param ID			ID used, extended format
 */
void IMUSendFilterdAngleDataOnCAN(uint CANChannel, sint32 ID);
///@}




#endif /* XT28API_SENSORS_IMU_H_ */
/** @}*/
