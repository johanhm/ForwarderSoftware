/*! \defgroup Sensors
 *  \brief The sensors that exists on the forwarder.
 *  This group conatains the API related to sensors on the forwarder. The
 *  installed sensors on the forwarder are:
 *  - \ref IMU
 *  - \ref Pressure
 *  - \ref Pos
 */

/** \defgroup IMU
 * \ingroup Sensors
 * \brief This modules handels the configuration of the IMU and IMU Data.
 *
 *  From this module you can get the IMU data sunch as pitch angle and roll angle.
 *  @{
 */

#ifndef XT28API_SENSORS_IMU_H_
#define XT28API_SENSORS_IMU_H_

#include "api_lib_basic.h"


/*! This function configures the IMU. The IMU is a secret IMU from a secret company. It comminucates with the BODAS controller thought CAN.
 * Since the communication is thought CAN the configuration will register databoxes and callback functions. The IMU raw data will uppdate every 10ms after this functions has been called.
 *
 *
 * \param[in] CANchannel The CAN channel the IMU is connected to
 * \param[in] gyroDataboxNumber The databox the gyro should be registerd to.
 * \param[in] acceleometerDataboxNumber The databox the acceleometer data should be registerd to.
 *
 */
void IMUConfigure(uint8 CANchannel, uint16 gyroDataboxNumber, uint16 acceleometerDataboxNumber);


/*! \Brief Call to get lates value of Phi
 *
 *  The filter used to calculate the angle the forwarder have is complementary filter.
 *
 * \return Phi Returns the lates value of Phi
 *
 */
float IMUGetPhi(void);

/*! \Brief Call to get lates value of Theta
 *
 *  The filter used to calculate the angle the forwarder have is complementary filter.
 *
 * \return Phi Returns the lates value of Theta
 *
 */
float IMUGetTheta(void);




#endif /* XT28API_SENSORS_IMU_H_ */
/** @}*/
