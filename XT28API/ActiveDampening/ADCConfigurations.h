/*! \defgroup ADCFG	ADC configurations
 *  \brief This module contains pre defined setups for different ways to controll the forwarder,.
 *
 *  @{
 */

#ifndef XT28API_ACTIVEDAMPENING_ADCCONFIGURATIONS_H_
#define XT28API_ACTIVEDAMPENING_ADCCONFIGURATIONS_H_

#include "ActiveDampening.h"
#include "PendelumArmActuate.h"
#include "PendelumArmPosition.h"
#include "PendelumArmForces.h"
#include "IMU.h"
#include "api_lib_basic.h"

/*!
 *  This setups the PID only config with current outputs
 */
void ADCFGNivPIDSetup(bool state);

/*!
 *  PID niv setup togheter with skyhook
 */
void ADCFGNivPIDAndSkyhookSetup(bool state);

/*!
 *  PID for Z phi and Theta -> Pesude Froce
 *  Added to
 *  Skyhook signal -> Pesudo SKyhook signal
 *
 *  Add togheter and convert to cylinder load force
 *
 *  Sliding mode controller made by Frank and Bruno -> flow %
 *
 *  Send to actuate with unit flow %
 */
void ADCFGPesudoForcePIDSkyhookSlidingMode(bool state);

#endif /* XT28API_ACTIVEDAMPENING_ADCCONFIGURATIONS_H_ */
 /** @}*/
