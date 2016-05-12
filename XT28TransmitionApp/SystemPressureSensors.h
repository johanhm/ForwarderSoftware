/*
 * SystemPressureSensors.h
 *
 *  Created on: 12 maj 2016
 *      Author: ladmin
 */

#ifndef XT28TRANSMITIONAPP_SYSTEMPRESSURESENSORS_H_
#define XT28TRANSMITIONAPP_SYSTEMPRESSURESENSORS_H_

#define ANALOG_PUMP1_PRESSURE_A				0
#define ANALOG_PUMP1_PRESSURE_B				1
#define ANALOG_PUMP2_PRESSURE_A				2
#define ANALOG_PUMP2_PRESSURE_B				3
#define MBAR_PUMP1_PRESSURE_A				4
#define MBAR_PUMP1_PRESSURE_B				5
#define MBAR_PUMP2_PRESSURE_A				6
#define MBAR_PUMP2_PRESSURE_B				7
#define MBAR_LP_PUMP1_PRESSURE_A			8
#define MBAR_LP_PUMP1_PRESSURE_B			9
#define MBAR_LP_PUMP2_PRESSURE_A			10
#define MBAR_LP_PUMP2_PRESSURE_B			11
#define MBAR_LP_OLD_PUMP1_PRESSURE_A		12
#define MBAR_LP_OLD_PUMP1_PRESSURE_B		13
#define MBAR_LP_OLD_PUMP2_PRESSURE_A		14
#define MBAR_LP_OLD_PUMP2_PRESSURE_B		15
#define INDEX_SIZE_PRESSURE					16

		//(* Pressure inputs*)
#define AIV_Pressure_1_A_mV	 				IN_26_AIV
#define AIV_Pressure_1_B_mV 				IN_27_AIV //old old was in_21
#define AIV_Pressure_2_A_mV 				IN_28_AIV
#define AIV_Pressure_2_B_mV 				IN_29_AIV

#include "api_lib_basic.h"
#include <math.h>

/*!
 *  Init
 */
void SPSConfigureSystemPressureSensors(void);

/*!
 * Uppdate sensor data
 */
void SPSUppdateSystemPressureSensors(void);

/*!
 * Get pump 1's pressure
 * @return
 */
int SPSGetPump1Pressure_mbar(void);

/*!
 * Get pump2 pressure
 * @return
 */
int SPSGetPump2Pressure_mbar(void);

/*!
 * Send sensor data on CAN
 */
void SPSSendSensorDataOnCAN(void);

/*!
 * Configure system pressure send CAN channel
 * @param CANChannel
 * @param databoxNumber
 * @param systemPressureCANID
 */
void SPSConfigureSendSensorDatabox(uint8 CANChannel, uint8 databoxNumber, int systemPressureCANID);

#endif /* XT28TRANSMITIONAPP_SYSTEMPRESSURESENSORS_H_ */
