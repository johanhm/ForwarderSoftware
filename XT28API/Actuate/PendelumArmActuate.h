/** \defgroup PAActuate Actuate
 * \ingroup PAActuate
 * \brief This modules handels the pos sensor data.
 *
 *  @{
 */

#ifndef XT28API_ACTUATE_PENDELUMARMACTUATE_H_
#define XT28API_ACTUATE_PENDELUMARMACTUATE_H_

#include "api_lib_basic.h"

/*!
 * Configure the outputs
 */
void PAAConfigurePendelumArmOutputs(void);

/*!
 * Set passive dampening state
 */
void PAASetPassiveDampeningState(bool state);

/*!
 * Get reference current for a wheel
 */
int PAAGetReferenceCurrentForWheel(int wheel);

/*!
 * Set the reference current for a wheel
 */
int PAASetReferenceCurrentForWheel(int wheel, int referenceCurrent_ma);

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
void PAASetActuateState(bool state);

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
