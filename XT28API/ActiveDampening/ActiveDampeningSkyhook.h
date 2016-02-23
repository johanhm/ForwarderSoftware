/*! \defgroup ADSH Skyhook
 * \ingroup AD
 *
 * 	\brief Skyhook control
 *
 * 	This module contains functions related to skyhook control. Use it to tune the skyhook parameters and to calculate
 * 	a reference signal.
 *
 *  @{
 */

#ifndef XT28API_ACTIVEDAMPENING_ACTIVEDAMPENINGSKYHOOK_H_
#define XT28API_ACTIVEDAMPENING_ACTIVEDAMPENINGSKYHOOK_H_

#include "XT28HardwareConstants.h"
#include "math.h"
#include "stdlib.h"
#include "api_lib_basic.h"

/*! \name Set */
/*!
 * Set the gain parameters of the Skyhook controller.
 *
 * @param[in] wheelGainIn
 * @param[in] chassiGainIn
 * @param[in] phiGainIn
 * @param[in] thetaGainIn
 */
void ADSHSetSkyhookParameters(float wheelGainIn, float chassiGainIn, float phiGainIn, float thetaGainIn);
/** @} */

/*! \name Set */
/*!
 * Get the Skyhook reference signal in a array.
 *
 * @param[out] signalArrayOut   Output array with wheel order of [FR FL MR ML BR BL]
 * @param[in] wheelVel			Input array of wheels individual velocity
 * @param[in] avrageVelocity	Machine average velocity in Z axis
 * @param[in] gyroVelX			Rotation velocity in roll
 * @param[in] gyroVelY			Rotation velocity in pitch
 */
void ADSHGetSkyhookSignals(float signalArrayOut[static SUM_WHEELS], float wheelVel[static SUM_WHEELS], float avrageVelocity, float gyroVelX, float gyroVelY);
/** @} */



#endif /* XT28API_ACTIVEDAMPENING_ACTIVEDAMPENINGSKYHOOK_H_ */
/** @}*/
