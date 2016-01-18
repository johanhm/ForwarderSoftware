/*! \defgroup Sensors XT28 Sensors
 *  \brief The sensors that exists on the forwarder.
 *  This group conatains the API related to sensors on the forwarder. The
 *  installed sensors on the forwarder are:
 *  - \ref IMU
 *  - \ref Pressure
 *  - \ref Pos
 */

/** \defgroup IMU IMU)
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
 #### Example code: ###
 ~~~~~~~~~~{.c}
 #include "api_lib_basic.h"

 uint16 gyroBoxNr = 1;
 uint16 accBoxNr  = 2;
 IMUConfigure(CAN_2, gyroBoxNr, accBoxNr);
 ~~~~~~~~~~
 *
 */
void IMUConfigureInertialMeasurementUnit(uint8 CANchannel, uint16 gyroDataboxNumber, uint16 acceleometerDataboxNumber);

/*!
 *  This function sends the start init message to the IMU. It has to be called after the CAN channels have been initilazied.
 *
 *  \return Returns 0 if everything went ok. If it returns something else something went wrong.
 */
uint16 IMUInit(void);


/*! \Brief Call to get lates value of Phi
 *
 *  The filter used to calculate the angle the forwarder have is complementary filter.
 *
 * \return Phi Returns the lates value of Phi
 *
 #### Example code: ###
 ~~~~~~~~~~{.c}
float phiDegree = IMUGetTheta();
 ~~~~~~~~~~
 *
 */
float IMUGetPhi(void);

/*! \Brief Call to get lates value of Theta
 *
 *  The filter used to calculate the angle the forwarder have is complementary filter.
 *
 * \return Phi Returns the lates value of Theta
 *
 #### Example code: ###
 ~~~~~~~~~~{.c}
float thetaDegree = IMUGetTheta();
 ~~~~~~~~~~
 *
 */
float IMUGetTheta(void);

/*! \Brief This function will send out the raw values on corresponding can ID when called.
 *
 * \param[in] CANChannel The channel the message should be sent on
 * \param[in] gyroID The id for IMU message. In short format
 * \param[in] accID
 *
 */
void IMUSendIMURawValuesOnCAN(uint8 CANChannel, uint32 gyroID, uint32 accID);

/*!
 * Sends the filterd angles on CAN
 */
void IMUSendFilterdAngleDataOnCAN(uint CANChannel, sint32 ID);




#endif /* XT28API_SENSORS_IMU_H_ */
/** @}*/
