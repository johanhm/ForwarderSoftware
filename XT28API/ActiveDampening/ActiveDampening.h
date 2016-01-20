/*! \defgroup ADC ActiveDampening
 *  \brief This module calculate the reference current for Active dampening controller.
 *
 *  This module requiere that the sensor modules are setup and operational. You can use this module to get
 *  what reference current that should be actuated on all wheels in order to achine active dampening.
 *  Different methods exist for calculating a reference signal. This module lets you costumize the PID parameters
 *  of Pitch and Roll controller for the machine for example.
 *  @{
 */

#ifndef XT28API_ACTIVEDAMPENING_ACTIVEDAMPENING_H_
#define XT28API_ACTIVEDAMPENING_ACTIVEDAMPENING_H_

#include "XT28HardwareConstants.h"
#include "math.h"
#include "stdlib.h"
/*!
 * Get PID signals
 */
void ADCGetPIDSignalsForHeightPhiAndTheta(float signalArray[static SUM_WHEELS], float heightError, float phiError, float thetaError);

/*!
 * Set skyhoop dudes
 */
void ADCSetSkyhookParameters(float wheelGainIn, float chassiGainIn, float phiGainIn, float thetaGainIn);

/*!
 * skyhook
 */
void ADCGetSkyhookSignals(float signalArrayOut[static SUM_WHEELS], float wheelVel[static SUM_WHEELS], float avrageVelocity, float gyroVelX, float gyroVelY);

/*!
 * \brief Set PID parameters for pitch controller
 *
 * \param[in] P proportional constant
 * \param[in] I intergrator constant
 * \param[in] D dereiative constant
 *
 * \return returns whatever the parameters was succesfully set or not.
 *
 */
int ADCSetThetaControlParametersPID(float P, float I, float D);

/*!
 * \brief Set PID parameters for heave controller
 *
 * \param[in] P proportional constant
 * \param[in] I intergrator constant
 * \param[in] D dereiative constant
 *
 * \return returns whatever the parameters was succesfully set or not.
 */
int ADCSetPhiControlParametersPID(float P, float I, float D);

/*!
 * Set PID for height
 */
int ADCSetHeightControlParametersPID(float P, float I, float D);

/*!
 * Frank and brunos black magic
 */
float ADCCalculateSlidingModeControllerForWheel(int wheel, float pesudoForce, float pressureA, float pressureB, float velocityWheel);


#endif /* XT28API_ACTIVEDAMPENING_ACTIVEDAMPENING_H_ */
/** @}*/
