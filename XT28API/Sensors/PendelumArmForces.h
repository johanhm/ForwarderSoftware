/** \defgroup PASENS Pendulum arm
 * Pendulum arm sensors
 *
 *  \ingroup SENSORS
 */


/** \defgroup PAF Forces
 * \ingroup PASENS
 * \brief Pendulum arm forces
 *
 * This module is design to be independent. To be able to get force data the user
 * have to call the function PAFUppdateForceOnWheelsDataUsing().
 *
 * The reason for this is it makes this module testable.
 *
 * It does the following:
 *
 * 1. Update forces with position and pressure
 * 2. Get optimal force and measured force on a wheel
 * 3. Send all this on CAN
 *
 *
 *  @{
 */

#ifndef XT28API_SENSORS_PENDELUMARMFORCES_H_
#define XT28API_SENSORS_PENDELUMARMFORCES_H_

#include "XT28HardwareConstants.h"
#include "api_lib_basic.h"
#include <math.h>
#include "XT28CANSupport.h"

/* Maby rethink this, only pressure module i needed and thats duh to the defines so its in the same order. */
#include "PendelumArmPressure.h"
#include "PendelumArmPosition.h"
/* emd, still to enforce that this module does not depend on the other two it should maby ce changed */

// Pressure sensor index
/*
#define ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_A		0
#define ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_B		1
#define ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_A		2
#define ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_B		3
#define ANALOG_MID_RIGHT_PENDULUM_PRESSURE_A		4
#define ANALOG_MID_RIGHT_PENDULUM_PRESSURE_B		5
#define ANALOG_MID_LEFT_PENDULUM_PRESSURE_A			6
#define ANALOG_MID_LEFT_PENDULUM_PRESSURE_B			7
#define ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_A		8
#define ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_B		9
#define ANALOG_REAR_LEFT_PENDULUM_PRESSURE_A		10
#define ANALOG_REAR_LEFT_PENDULUM_PRESSURE_B		11
#define INDEX_SIZE_PRESSURESENS						12
*/

/*!	\name Update */
/*!
 *  Call this function periodically to update the Force and mass center data in this module.
 *  Arguments for this functions are the sensor data you can get from \ref PAPOS and \ref PAPR.
 *
 * @param pressureDataInput		Array of pressure data for all cylinder chambers, should have length of 12
 * @param posDataInput			Array of position data for all cylinder arms, should be of length 6
 */
void PAFUppdateForceOnWheelsDataUsing(int pressureDataInput[INDEX_SIZE_PRESSURESENS], int posDataInput[SUM_WHEELS]);
/** @} */



/*! \name Get functions */
/*!
 * Get calculated optimal force reference for a specific wheel.
 *
 * @param wheelNumber
 * @return Reference force for wheel in Newton
 */
int PAFGetOptimalReferenceForceForWheel_N(uint8 wheelNumber);

/*!
 * Get measured Cylinder load force.
 *
 * @param wheelNumber
 * @return Measured force acting on the Cylinder for specified wheel.
 */
int PAFGetMessuredCylinderLoadForceForWheel_dN(uint8 wheelNumber);


/*!
 * Converts a Vertical force into corresponding cylinder load force. This convention is based
 * on geometry calculations.
 *
 * @param cylinderPoss_mm  The wheels extension, see \ref PAPOS
 * @param verticalForce    The vertical force to convert
 * @return Corresponding cylinder load force.
 */
sint32 PAFConvertVerticalForceOnWheelToCylinderLoadForce(uint16 cylinderPoss_mm, sint32 verticalForce);

/*!
 * Get a array of optimal force reference.
 *
 * @param forceOptRefOutputArray  Output array for force reference, size of 6.
 */
void PAFGetOptimalReferenceForceArray_N(int forceOptRefOutputArray[static SUM_WHEELS]);

/*!
 *  Get an array of measured force on the cylinder.
 *
 * @param forceCylLoadOutputArray Output array for measured force reference, size of 6.
 */
void PAFGetMessuredCylinderLoadForceArray_dN(int forceCylLoadOutputArray[static SUM_WHEELS]);
///@}



/*! \name CAN */
/*!
 * 	Send cylinder chamber force on CAN
 *
 * @param CANChannel	CAN channel
 * @param backID		Extended format
 * @param middleID		Extended format
 * @param frontID		Extended format
 */
void PAFSendCylinderChamberForceOnCAN(uint8 CANChannel, uint32 backID, uint32 middleID, uint32 frontID);

/*!
 * Sends Cylinder load force on CAN
 *
 * @param CANChannel		CAN channel
 * @param middleAndBackID	Extended format
 * @param frontID			Extended format
 */
void PAFSendCylinderLoadForceOnCAN(uint8 CANChannel, uint32 middleAndBackID, uint32 frontID);

/*!
 *  Sends Calculated vertical force on CAN
 * @param CANChannel		CAN channel
 * @param middleAndBackID	Extended format
 * @param frontID			Extended format
 */
void PAFSendVerticalWheelForceOnCAN(uint8 CANChannel, uint32 middleAndBackID, uint32 frontID);

/*!
 * Send force error % on CAN
 *
 * @param CANChannel			CAN channel
 * @param frontAndMiddleID		Extended format
 * @param backID				Extended format
 */
void PAFSendForceErrorPercentageOnCAN(uint8 CANChannel, uint32 frontAndMiddleID, uint32 backID);

/*!
 * Send mass center location on CAN
 *
 * @param CANCHannel	CAN channel
 * @param ID			Extended format
 */
void PAFSendMassCenterLocationOnCAN(uint CANCHannel, uint32 ID);

/*!
 * Send this on CAN
 * @param CANChannel		CAN channel
 * @param frontAndMiddleID	Extended format
 * @param backID			Extended format
 */
void PAFSendOptimalForceRefOnCAN(uint8 CANChannel, uint32 frontAndMiddleID, uint32 backID);
///@}

#endif /* XT28API_SENSORS_PENDELUMARMFORCES_H_ */
/** @}*/
