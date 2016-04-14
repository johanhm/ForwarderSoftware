/*!
 *  \defgroup ACTUATE Actuate
 */



/** \defgroup PAA Pendulum Arm
 * \ingroup ACTUATE
 * \brief Output to pendulum arm cylinders.
 *
 * This module handles the output to the pendulum arms on the forwarder. It does the following:
 *
 * 1. Configure output ports to pendulum arm cylinders
 * 2. Handle limitations on actuate pendulum arms.
 * 3. Handle passive dampening ( ON / OFF )
 * 4. Handle setting a reference for pendulum arm output
 * 5. Actuate set reference for pendulum arm
 *
 * The output will by default be saturated to a maximum for 800mA in order not to blow the solenoid valves up.
 * The valves also have a dead band of 400mA. This module adds it to set reference.
 *
 *  @{
 */

#ifndef XT28API_ACTUATE_PENDELUMARMACTUATE_H_
#define XT28API_ACTUATE_PENDELUMARMACTUATE_H_

#include "api_lib_basic.h"
#include "math.h"
#include "stdlib.h"
#include "XT28HardwareConstants.h"

/** \name  Defines for pendulum outputs */

#define OUT_PENDELURM_FRONT_RIGHT_A		OUT_1_POH_CL
#define OUT_PENDELURM_FRONT_RIGHT_B		OUT_2_POH_CL
#define OUT_PENDELURM_FRONT_LEFT_A		OUT_3_POH_CL
#define OUT_PENDELURM_FRONT_LEFT_B		OUT_4_POH_CL
#define OUT_PENDELURM_MID_RIGHT_A		OUT_5_POH_CL
#define OUT_PENDELURM_MID_RIGHT_B		OUT_6_POH_CL
#define OUT_PENDELURM_MID_LEFT_A		OUT_7_POH_CL
#define OUT_PENDELURM_MID_LEFT_B		OUT_8_POH_CL
#define OUT_PENDELURM_REAR_RIGHT_A		OUT_9_POH_CL
#define OUT_PENDELURM_REAR_RIGHT_B		OUT_10_POH_CL
#define OUT_PENDELURM_REAR_LEFT_A		OUT_11_POH_CL
#define OUT_PENDELURM_REAR_LEFT_B		OUT_12_POH_CL

/*!
 *	 Actuate unit
 */
typedef enum {
	CURRENT_MA,			/*!< Current   [mA] 	*/
	FLOW_PERCENTAGE,	/*!< Flow      [%] 	    */
	VELOCITY_MS			/*!< Velocity  [m/s] 	*/
} PAAOutUnit;

/*! \name Configure, Setup and Actuate */
/*!
 * Configures the outputs on the forwarder. Needs to be called in application setup in order to be able to
 * actuate anything at all on the pendulum arms.
 */
void PAAConfigurePendelumArmOutputs(void);

/*!
 *  Actuate the last set reference to pendulum arm.
 *  You typically call this function after setting the reference for all wheels using
 *  PAASetReferenceForWheelWithUnit() or PAASetReferenceArrayWithUnit()
 */
void PAAActuatePendelumArms(void);
/** @} */



/*! \name Set */
/*!
 * Set the reference current on a wheel to a specific value.
 * Valid values are in the range of [0 - 400]. This function will then add the deadband on the solenoids of 400 to the set value.
 * This function will also check if the input is valid.
 * If it is not valid the input will be saturated and the function will return an error parameter
 *
 *
 * @param wheel
 * @param unit
 * @param referenceInput
 * @return 0 = no problems, 1 = saturated
 */
int PAASetReferenceForWheelWithUnit(int wheel, PAAOutUnit unit, float referenceInput);

/*!
 * Set reference array for all wheels
 *
 * @param referenceArray	Input reference array
 * @param unit				Selected unit
 */
void PAASetReferenceArrayWithUnit(float referenceArray[static SUM_WHEELS], PAAOutUnit unit);

/*!
 * If active then this functions does the following:
 * 1. If the cylinder is close to a end position the reference output will be ser to zero.
 *
 * @param state		True = limit active, False = limit inactive
 */
void PAASetPendelumArmPosLimitState(bool state);

/*!
 *  Set current output limit.
 * \note Not yet implemented
  * @param currentLimit		Valid range [400 - 800]
  */
void PAASetReferenceCurrentSaturationLimit(int currentLimit);

/*!
 *  Set if current output should be activated or not.
 *
 *  @param state True = its possible to actuate the pendulum arms. False = No current will be set even if PAAActuatePendelumArms() is called.
 */
void PAASetPendelumArmActuateState(bool state);

/*!
 * Set passive dampening of the forwarder.
 * The machine have passive accumulators installed on each pendulum arm cylinder. They can be activated by calling this function. They will all be activated at once.
 *
 * \param[in] state Set passive dampening state to [TRUE, FALSE]
 */
void PAASetPassiveDampeningState(bool state);
/** @} */



/*! \name Get */
/*!
 * Use this function to get current reference set on wheel
 *
 * \return Reference current on wheel
 */
int PAAGetReferenceCurrentForWheel(int wheel);
/** @} */



/*! \name CAN */
/*!
 * Sends reference current on CAN
 *
 * @param CANChannel	CAN Channel
 * @param frontID		Extended format
 * @param middleID		Extended format
 * @param backID		Extended format
 */
void PAASendReferenceCurrentOnCAN(uint8 CANChannel, uint32 frontID, uint32 middleID, uint32 backID);

/*!
 * Send real actuated current on solenoid to CAN
 *
 * @param CANChannel	CAN Channel
 * @param frontID		Extended format
 * @param middleID		Extended format
 * @param backID		Extended format
 */
void PAASendRealCurrentOnCAN(uint8 CANChannel, uint32 frontID, uint32 middleID, uint32 backID);
/** @} */

#endif /* XT28API_ACTUATE_PENDELUMARMACTUATE_H_ */
/** @}*/
