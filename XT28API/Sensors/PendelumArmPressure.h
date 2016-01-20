/** \defgroup PAPR Pressure
 * \ingroup Sensors
 * \brief This modules handels configuration of pressure data.
 *
 *  @{
 */

#ifndef XT28API_SENSORS_PENDELUMARMPRESSURE_H_
#define XT28API_SENSORS_PENDELUMARMPRESSURE_H_

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
 * Get all pressure data
 */
void PAPRGetPressureDataArray_bar(int pressureDataOutput_bar[static INDEX_SIZE_PRESSURESENS]);

/*!
 * This function configures the pressure sensors.
 */
void PAPRConfigurePressureSensorsVoltageInput(void);

/*!
 * Uppdates the pressure data
 */
void PAPRUppdatePressureDataWithSampleTime(int sampleTimeUppdate);

/*!
 *  Sends pressureData on CAN
 */
void PAPRSendPressureDataOnCAN(uint8 CANChannel, uint32 frontID, uint32 middleID, uint32 backID);

#endif /* XT28API_SENSORS_PENDELUMARMPRESSURE_H_ */
 /** @}*/
