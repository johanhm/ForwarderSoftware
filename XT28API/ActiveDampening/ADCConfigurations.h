/*!
 * \page ADCONFIG  Configurations
 *
 * Hello does thos works doxygen pls explain
 */



/*! \defgroup AD Active Dampening
 * 	This group contains module for different controller types
 * 	and a mocule that congaints different configurations of different controllers.
 */

/*! \defgroup ADCFG	Configurations
 * \ingroup SUPPORT
 *  \brief This shot dosent work
 *
 *  @{
 */

#ifndef XT28API_ACTIVEDAMPENING_ADCCONFIGURATIONS_H_
#define XT28API_ACTIVEDAMPENING_ADCCONFIGURATIONS_H_

#include "ActiveDampening.h"
#include "PendelumArmActuate.h"
#include "PendelumArmPosition.h"
#include "PendelumArmForces.h"
#include "PendelumArmPressure.h"
#include "IMU.h"
#include "api_lib_basic.h"

/*!
 * Will remove this dude
 */
void ADCFGManualTestingPlayground(bool state);

/*!
 * Enable setting the controller parameters though CAN with Canalyzer
 */
void ADCFGConfigureParameterSettingsFromCAN(uint8 CANChannel, uint16 databoxNr1, uint16 databoxNr2, uint16 databoxNr3);

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


/*!
 *  With optimal force ref
 */
void ADCFGPesudoForceWithOptimalForceRefPIDSkyhookSlidingMode(bool state);


#endif /* XT28API_ACTIVEDAMPENING_ADCCONFIGURATIONS_H_ */
 /** @}*/
