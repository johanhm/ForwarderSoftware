/** \defgroup PAPR Pressure
 * \ingroup Sensors
 * \brief This modules handels configuration of pressure data.
 *
 *  @{
 */

#ifndef XT28API_SENSORS_PENDELUMARMPRESSURE_H_
#define XT28API_SENSORS_PENDELUMARMPRESSURE_H_

#include "api_lib_basic.h"

/*!
 * This function configures the pressure sensors.
 */
void PAPRConfigurePressureSensorsVoltageInput(void);

/*!
 * Uppdates the pressure data
 */
void PAPRUppdatePressureData(void);

/*!
 * Uppdate the force data on each wheel
 */
void PAPRUppdateForceOnWheelsData(void);

/*!
 *  Sends pressureData on CAN
 */
void PAPRSendPressureDataOnCAN(uint8 CANChannel, uint32 frontID, uint32 middleID, uint32 backID);

/*!
 *  Sends cylinder force on CAN
 */
void PAPRSendCylinderForceOnCAN(uint8 CANChannel, uint32 backID, uint32 middleID, uint32 frontID);

/*!
 * Sends Cylinder load force on CAN
 */
void PAPRSendCylinderLoadForceOnCAN(uint8 CANChannel, uint32 middleAndBackID, uint32 frontID);

/*!
 *  Sends Calculated vertical force on CAN
 */
void PAPRSendVerticalWheelForceOnCAN(uint8 CANChannel, uint32 middleAndBackID, uint32 frontID);

/*!
 * Send force error % on CAN
 */
void PAPRSendForceErrorPercentageOnCAN(uint8 CANChannel, uint32 frontAndMiddleID, uint32 backID);

/*!
 * Send mass center location on CAN
 */
void PAPRSendMassCenterLocationOnCAN(uint CANCHannel, uint32 ID);

/*!
 * Send this on CAN
 */
void PAPRSendOptimalForceRefOnCAN(uint8 CANChannel, uint32 frontAndMiddleID, uint32 backID);


/*!
 * Get calculated optimal force ref
 */
int PAPRGetOptimalReferenceForceForWheel_N(uint8 wheelNumber);





#endif /* XT28API_SENSORS_PENDELUMARMPRESSURE_H_ */
 /** @}*/
