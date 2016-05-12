
#ifndef XT28TRANSMITIONAPP_GASPEDALSENSOR_H_
#define XT28TRANSMITIONAPP_GASPEDALSENSOR_H_

#include "api_lib_basic.h"
#include <math.h>

		//(*FORWARD drive*)
#define AIV_GAS_F_A							IN_33_AIV // (*Signal A, 0.5V-4.5V*)
#define AIV_GAS_F_B							IN_34_AIV // (*Signal B, 4.5V-0.5V*)
#define AID_GAS_F_NO						IN_4_AIV // (*Analog on eller inte *)
		//(*BACKWARDS drive*)
#define AIV_GAS_R_A							IN_35_AIV // (*Signal A, 0.5V-4.5V*)
#define AIV_GAS_R_B							IN_36_AIV // (*Signal B, 4.5V-0.5V*)
#define AID_GAS_R_NO						IN_5_AIV 	// (*Analog on eller inte *)
		//(*Forward brake*)
#define AIV_BRAKE_F_A						IN_37_AIV	// (*Signal A, 0.5V-4.5V*)
#define AIV_BRAKE_F_B						IN_38_AIV	// (*Signal B, 4.5V-0.5V*)
#define AID_BRAKE_F_NO						IN_6_AIV			// (*Analog on eller inte *)
		//(*BACKWARD brake*)
#define AIV_BRAKE_R_A						IN_39_AIV	// (*Signal A, 0.5V-4.5V*)
#define AIV_BRAKE_R_B						IN_25_AIV	// (*Signal B, 4.5V-0.5V*)
#define AID_BRAKE_R_NO						IN_7_AIV		// (*Analog on eller inte *)


/*!
 * Configure gaspadal sensor inputs
 */
void GPSConfigureGasPedalInputSensors(void);

/*!
 * Call this periodicly to uppdate the sensor data.
 */
void GPSUppdatePedalSensorData(void);

/*!
 * Get gasPedal sensor value
 * @param chairPosition
 * @return
 */
int GPSGetGassPedalFilterdAndScaled(bool chairPosition);

/*!
 * Get break pedal sensor value
 * @param chairPosition
 * @return
 */
int GPSGetBreakPedal(bool chairPosition);

#endif /* XT28TRANSMITIONAPP_GASPEDALSENSOR_H_ */
