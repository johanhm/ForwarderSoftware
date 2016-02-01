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
 * \brief Get PID signals for Niv controller
 *
 * \bug Only P controller truly implemented!
 *
 * \param[out] signalArray 	The output array of length 6.
 * \param[in] heightError 	error = (reference - measured value)
 * \param[in] phiError 		error = (reference - measured value)
 * \param[in] thetaError	error = (reference - measured value)
 *
 */
void ADPIDGetPIDSignalsForHeightPhiAndThetaArray(float signalArray[static SUM_WHEELS], float heightError, float phiError, float thetaError);

/*!
 * \brief Set PID parameters for pitch controller
 *
 * \bug Only P controller truly implemented!
 *
 * \param[in] P proportional constant
 * \param[in] I intergrator constant
 * \param[in] D derivative constant
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
 * \param[in] D derivative constant
 *
 * \return returns whatever the parameters was succesfully set or not.
 */
int ADPIDSetPhiControlParametersPID(float P, float I, float D);

/*!
 * \brief Set PID parameters for height controller
 *
 * \param[in] P proportional constant
 * \param[in] I intergrator constant
 * \param[in] D derivative constant
 *
 * \return returns whatever the parameters was succesfully set or not.
 */
int ADPIDSetHeightControlParametersPID(float P, float I, float D);

/*!
 * \brief Set PID parameters for force controller
 *
 * \param[in] P proportional constant
 * \param[in] I Integrator constant
 * \param[in] D derivative constant
 *
 * \return returns whatever the parameters was successfully set or not.
 */
int ADPIDSetForceControllerParametersPID(float P, float I, float D);

/*!
 * \brief Get the force controllers reference signal for a wheel
 *
 * Use this function to get the force controller signal for a specific wheel
 *
 * \param[in] wheel          Wheel, for what wheel corresponds to what number see \ref XT28HWC
 * \param[in] messuredForce  Measured Force
 * \param[in] forceReference Reference Force
 * \param[in] deadbandState  If activated. Controller will return 0 when error is less then 10%. If error is higher then 10% it returns a value until the error change sign or is zero.
 *
 * \return P * Error
 *
 */
float ADPIDGetForceControllerReferenceSignals(int wheel, float messuredForce, float forceReference, bool deadbandState);

/*!
 * \brief Get an array of signals from force controller
 *
 * \bug Only P controller is truely implemented!
 *
 * \param[in] messuredForceCylinder Messured force array
 * \param[in] forceReferenceArray   Reference force array
 * \param[out] signalArrayOut       Output signal array
 * \param[in] deadbandState         If activated. Controller will return 0 when error is less then 10%. If error is heigher then 10% it returns a value until the error change sign or is zero.
 *
 * \return P * Error array
 */
void ADPIDGetForceControllerReferenceSignalsArray(int messuredForceCylinder[static SUM_WHEELS], int forceReferenceArray[static SUM_WHEELS], float signalArrayOut[static SUM_WHEELS], bool deadbandState);


#endif /* XT28API_ACTIVEDAMPENING_ACTIVEDAMPENINGPID_H_ */
/** @}*/
