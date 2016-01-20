/** \defgroup PAF Forces
 * \ingroup Sensors
 * \brief This modules calculates the forces action on the wheels. To calculate this data it used the pressure data and pos
 * data from PAPR and PAPOS
 *
 *  @{
 */

#ifndef XT28API_SENSORS_PENDELUMARMFORCES_H_
#define XT28API_SENSORS_PENDELUMARMFORCES_H_

#include "XT28HardwareConstants.h"
#include "api_lib_basic.h"

// Pressure sensor index
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


/*!
 * Uppdate the force data on each wheel
 */
void PAFUppdateForceOnWheelsDataUsing(int pressureDataInput[INDEX_SIZE_PRESSURESENS], int posDataInput[SUM_WHEELS]);

/*!
 *  Sends cylinder force on CAN
 */
void PAFSendCylinderChamberForceOnCAN(uint8 CANChannel, uint32 backID, uint32 middleID, uint32 frontID);

/*!
 * Sends Cylinder load force on CAN
 */
void PAFSendCylinderLoadForceOnCAN(uint8 CANChannel, uint32 middleAndBackID, uint32 frontID);

/*!
 *  Sends Calculated vertical force on CAN
 */
void PAFSendVerticalWheelForceOnCAN(uint8 CANChannel, uint32 middleAndBackID, uint32 frontID);

/*!
 * Send force error % on CAN
 */
void PAFSendForceErrorPercentageOnCAN(uint8 CANChannel, uint32 frontAndMiddleID, uint32 backID);

/*!
 * Send mass center location on CAN
 */
void PAFSendMassCenterLocationOnCAN(uint CANCHannel, uint32 ID);

/*!
 * Send this on CAN
 */
void PAFSendOptimalForceRefOnCAN(uint8 CANChannel, uint32 frontAndMiddleID, uint32 backID);

/*!
 * Get calculated optimal force ref
 */
int PAFGetOptimalReferenceForceForWheel_N(uint8 wheelNumber);

/*!
 * Get converted force
 */
sint32 PAFConvertVerticalForceOnWheelToCylinderLoadForce(uint16 cylinderPoss_mm, sint32 verticalForce);




#endif /* XT28API_SENSORS_PENDELUMARMFORCES_H_ */
/** @}*/
