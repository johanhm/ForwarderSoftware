/*!
 *  \defgroup ACTUATE Actuate
 */



/** \defgroup PAA Pendelum Arm
 * \ingroup ACTUATE
 * \brief Handle output to pendelum arm
 *
 * This module handels the output to the pendelum arms on the forwarder.
 * The output will by defualt be saturated to a maximum for 800mA in order not to plow the solenoid valves up.
 *
 *
 *  @{
 */

#ifndef XT28API_ACTUATE_PENDELUMARMACTUATE_H_
#define XT28API_ACTUATE_PENDELUMARMACTUATE_H_

#include "api_lib_basic.h"
#include "math.h"
#include "stdlib.h"
#include "XT28HardwareConstants.h"

/*!
 * THe unit for setting output
 */
typedef enum {
	CURRENT_MA,			/* Current   [mA] 	*/
	FLOW_PERCENTAGE,	/* Flow      [%] 	*/
	VELOCITY_MS			/* Velocity  [m/s] 	*/
} PAAOutUnit;

/*!
 * Configures the outputs on the forwarder. THis needs to be called in application setup in order to be able to
 * actuate anything at all on the pendelum arms.
 */
void PAAConfigurePendelumArmOutputs(void);

/*!
 * Set passive dampening state of the forwarder.
 * The machine have passive accamulators installd on each wheel. They can be activated by calling this function. They will all be activated at once.
 *
 * \param[in] Set passive dampening state to [TRUE, FALSE]
 */
void PAASetPassiveDampeningState(bool state);

/*!
 * Use this function to investigate what the reference current on a wheel is at this point in time when you call it.
 *
 * \return Reference current on wheel
 */
int PAAGetReferenceCurrentForWheel(int wheel);

/*!
 * Set the reference current on a wheel to a specific value.
 * Valid values are in the range of [0 - 400]. This function will then add the deadband on the solenoids of 400 to the set value.
 * This function will also check if the input is valid.
 * If it is not valid the input will be saturated and the function will return an error parameter
 *
 * \return 0 Set current, valid range
 * \return 1 Set current, saturated.
 */
int PAASetReferenceForWheelWithUnit(int wheel, PAAOutUnit unit, float referenceInput);

/*!
 * Set reference array for all wheels
 */
void PAASetReferenceArrayWithUnit(float referenceArray[static SUM_WHEELS], PAAOutUnit unit);

/*!
 *  This function sends the current reference current actuate on pendelumarm.
 */
void PAAActuatePendelumArms(void);

/*!
 * Enabels or disables the pos limit
 */
void PAASetPendelumArmPosLimitState(bool state);

/*!
 * Set current output limit.  Not yet implemented
 */
void PAASetReferenceCurrentSaturationLimit(int currentLimit);

/*!
 *  Set if current output should be activated or not.
 */
void PAASetPendelumArmActuateState(bool state);

/*!
 * Sends reference current on CAN
 */
void PAASendReferenceCurrentOnCAN(uint8 CANChannel, uint32 frontID, uint32 middleID, uint32 backID);

/*!
 * Send real actuated current on solenoid to CAN
 */
void PAASendRealCurrentOnCAN(uint8 CANChannel, uint32 frontID, uint32 middleID, uint32 backID);


#endif /* XT28API_ACTUATE_PENDELUMARMACTUATE_H_ */
/** @}*/
