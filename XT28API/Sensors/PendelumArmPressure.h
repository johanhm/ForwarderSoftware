/** \defgroup PAPR Pressure
 * \ingroup PASENS
 * \brief Pendulum arm cylinder pressure
 *
 * This module does the following:
 *
 * 1. Configure input ports of pressure sensors
 * 2. Read pressure sensors and low pass filter
 * 3. Provide functionality to read pressure data
 * 4. Send pressure data on CAN
 *
 *  @{
 */

#ifndef XT28API_SENSORS_PENDELUMARMPRESSURE_H_
#define XT28API_SENSORS_PENDELUMARMPRESSURE_H_

#include "api_lib_basic.h"
#include <math.h>
#include "XT28CANSupport.h"
#include "PendelumArmPosition.h"
#include "XT28HardwareConstants.h"

/* Uppdate error codes */
#define PRESSURE_UPPDATED  		(0x00)
#define PRESSURE_UPDATE_ERROR 	(0x01)

/* Pressure sensor input */
#define IN_FR_A			(IN_8_AIV)
#define IN_FR_B			(IN_7_AIV)
#define IN_FL_A			(IN_10_AIV)
#define IN_FL_B			(IN_9_AIV)
#define IN_MR_A			(IN_11_AIV)
#define IN_MR_B			(IN_14_AIV)
#define IN_ML_A			(IN_13_AIV)
#define IN_ML_B			(IN_12_AIV)
#define IN_BR_A			(IN_15_AIV)
#define IN_BR_B			(IN_18_AIV)
#define IN_BL_A			(IN_17_AIV)
#define IN_BL_B			(IN_16_AIV)

/* Pressure sensor index */
#define ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_A		(0)
#define ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_B		(1)
#define ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_A		(2)
#define ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_B		(3)
#define ANALOG_MID_RIGHT_PENDULUM_PRESSURE_A		(4)
#define ANALOG_MID_RIGHT_PENDULUM_PRESSURE_B		(5)
#define ANALOG_MID_LEFT_PENDULUM_PRESSURE_A			(6)
#define ANALOG_MID_LEFT_PENDULUM_PRESSURE_B			(7)
#define ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_A		(8)
#define ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_B		(9)
#define ANALOG_REAR_LEFT_PENDULUM_PRESSURE_A		(10)
#define ANALOG_REAR_LEFT_PENDULUM_PRESSURE_B		(11)
#define INDEX_SIZE_PRESSURESENS						(12)

/*! \name Configure and Update */
/*!
 * This function configures the pressure sensors.
 */
void PAPRConfigurePressureSensorsVoltageInput(void);

/*!
 *	Does the following:
 *	1. Read the pressure on input ports
 *	2. low pass filter pressure data
 *
 * @param sampleTimeUppdate	The period this function is called in milliseconds.
 * @return error code. If 0 everything is fine
 */
void PAPRUppdatePressureDataWithSampleTime(int sampleTimeUppdate);

/*!
 * Check pressure sensors for error
 * @return TRUE if there is an error, false oterwhice
 */
bool PAPRCheckPressureSensorForErrors(void);
/** @}*/

/*! \name Get */
/*!
 * Get pressure data in bar for a chamber. The order is defined in \ref XT28HWC
 *
 * @param chamber
 * @return Pressure
 */
float PAPRGetPressureForChamber_bar(int chamber);

/*!
 * Get all pressure data in a array.
 *
 * @param pressureDataOutput_bar	Pointer to output array that will be filled with latest pressure data
 */
void PAPRGetPressureDataArray_bar(int pressureDataOutput_bar[static INDEX_SIZE_PRESSURESENS]);
/** @}*/

/*! \name CAN */
/*!
 *  Sends pressureData on CAN
 *
 * @param CANChannel	CAN Channel
 * @param frontID		Extended format
 * @param middleID		Extended format
 * @param backID		Extended format
 */
void PAPRSendPressureDataOnCAN(uint8 CANChannel, uint32 frontID, uint32 middleID, uint32 backID);
/** @}*/

#endif /* XT28API_SENSORS_PENDELUMARMPRESSURE_H_ */
/** @}*/
