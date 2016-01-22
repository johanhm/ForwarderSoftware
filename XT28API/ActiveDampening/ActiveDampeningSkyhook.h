/*! \defgroup ADSH Skyhook
 * \ingroup ADC
 * 	Skyhook
 *
 *  @{
 */

#ifndef XT28API_ACTIVEDAMPENING_ACTIVEDAMPENINGSKYHOOK_H_
#define XT28API_ACTIVEDAMPENING_ACTIVEDAMPENINGSKYHOOK_H_

#include "XT28HardwareConstants.h"
#include "math.h"
#include "stdlib.h"
#include "api_lib_basic.h"


/*!
 * Set skyhoop dudes
 */
void ADSHSetSkyhookParameters(float wheelGainIn, float chassiGainIn, float phiGainIn, float thetaGainIn);

/*!
 * skyhook
 */
void ADSHGetSkyhookSignals(float signalArrayOut[static SUM_WHEELS], float wheelVel[static SUM_WHEELS], float avrageVelocity, float gyroVelX, float gyroVelY);




#endif /* XT28API_ACTIVEDAMPENING_ACTIVEDAMPENINGSKYHOOK_H_ */
/** @}*/
