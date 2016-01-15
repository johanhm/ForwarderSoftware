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

/*! \brief Use this function to get a reference current for a wheel.
 *
 * \param[in] Wheel The wheel you need to get a reference current for. Valid values are [0-5]
 * where the number is defined by XT28 hardware constants.
 */
int ADCGetReferenceCurrentForWheel(int wheel);

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






#endif /* XT28API_ACTIVEDAMPENING_ACTIVEDAMPENING_H_ */
/** @}*/
