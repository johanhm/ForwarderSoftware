/*! \defgroup ADSM Sliding Mode
 * \ingroup AD
 *
 * 	\brief Sliding mode control.
 *
 *
 *
 *  @{
 */

#ifndef XT28API_ACTIVEDAMPENING_ACTIVEDAMPENINGSLIDINGMODE_H_
#define XT28API_ACTIVEDAMPENING_ACTIVEDAMPENINGSLIDINGMODE_H_

#include "XT28HardwareConstants.h"
#include "math.h"
#include "stdlib.h"
#include "api_lib_basic.h"


/*!
 * Get the reference signal for a wheel given a force reference, current measured force, pressure on both chambers and the velocity for a wheel.
 * This function have the option of dead band which means If true the output signal will turn zero if the error changes sign or becomes zero.
 * The signal will activate again when the error is greater then 10%.
 *
 * The return value is the suggested flow on the cylinder. Positive means the wheel should go down, negative means it should go up.
 *
 * @param[in] wheel							Wheel number
 * @param[in] messuredCylinderForce			Measured force
 * @param[in] pesudoForceReference_N		Reference force
 * @param[in] pressureA_Pa					Pressure on chamber A for the wheel
 * @param[in] pressureB_Pa					Pressure on chamber B for the wheel
 * @param[in] velocityWheel_ms				Velocity for the wheel
 * @param[in] deadbandState					Set if the signal should dead band or not.
 * @return Flow reference in % [-1, +1]
 */
float ADSMCalculateSlidingModeControllerForWheel(int wheel, float messuredCylinderForce, float pesudoForceReference_N, float pressureA_Pa, float pressureB_Pa, float velocityWheel_ms, bool deadbandState);



#endif /* XT28API_ACTIVEDAMPENING_ACTIVEDAMPENINGSLIDINGMODE_H_ */
/** @}*/
