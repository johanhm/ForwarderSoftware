/*! \defgroup ADPID PID
 * \ingroup ADC
 *
 *  \brief This module calculate the reference current for Active dampening controller.
 *
 *  This module requiere that the sensor modules are setup and operational. You can use this module to get
 *  what reference current that should be actuated on all wheels in order to achine active dampening.
 *  Different methods exist for calculating a reference signal. This module lets you costumize the PID parameters
 *  of Pitch and Roll controller for the machine for example.
 *  @{
 */

#ifndef XT28API_ACTIVEDAMPENING_ACTIVEDAMPENINGPID_H_
#define XT28API_ACTIVEDAMPENING_ACTIVEDAMPENINGPID_H_

#include "XT28HardwareConstants.h"
#include "math.h"
#include "stdlib.h"
#include "api_lib_basic.h"

/*!
 * Get PID signals
 */
void ADPIDGetPIDSignalsForHeightPhiAndThetaArray(float signalArray[static SUM_WHEELS], float heightError, float phiError, float thetaError);

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
int ADPIDSetThetaControlParametersPID(float P, float I, float D);

/*!
 * \brief Set PID parameters for heave controller
 *
 * \param[in] P proportional constant
 * \param[in] I intergrator constant
 * \param[in] D dereiative constant
 *
 * \return returns whatever the parameters was succesfully set or not.
 */
int ADPIDSetPhiControlParametersPID(float P, float I, float D);

/*!
 * Set PID for height
 */
int ADPIDSetHeightControlParametersPID(float P, float I, float D);

/*!
 * Set force controller PID parameters
 */
int ADPIDSetForceControllerParametersPID(float P, float I, float D);

/*!
 * Force controller swag with optimal deadband
 */
float ADPIDGetForceControllerReferenceSignals(int wheel, float messuredForce, float forceReference, bool deadbandState);

/*!
 * Get array
 */
void ADPIDGetForceControllerReferenceSignalsArray(int messuredForceCylinder[static SUM_WHEELS], int forceReferenceArray[static SUM_WHEELS], float signalArrayOut[static SUM_WHEELS], bool deadbandState);


#endif /* XT28API_ACTIVEDAMPENING_ACTIVEDAMPENINGPID_H_ */
/** @}*/
