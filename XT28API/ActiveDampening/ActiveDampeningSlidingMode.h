/*! \defgroup ADSM Sliding Mode
 * \ingroup ADC
 * 	Sliding mode
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
 * Frank and brunos black magic
 */
float ADSMCalculateSlidingModeControllerForWheel(int wheel, float messuredCylinderForce, float pesudoForceReference_N, float pressureA_Pa, float pressureB_Pa, float velocityWheel_ms, bool deadbandState);



#endif /* XT28API_ACTIVEDAMPENING_ACTIVEDAMPENINGSLIDINGMODE_H_ */
/** @}*/
