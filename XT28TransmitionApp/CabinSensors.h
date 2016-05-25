
/** \defgroup CS Cabin Sensors
 * \ingroup SENSORS
 * \brief Handles sensors related to the cabin.
 *
 *  Does the following:
 *
 *  1. Configure cabin sensors
 *  2. Update sensor data
 *  3. Get the chair position.
 *
 *  The module handles the following sensors
 *
 *  1. Chair position
 *  2. Oil temperature
 *  3. Door sensor
 *  4. Fuel meter sensor
 *
 *  @{
 */



#ifndef XT28TRANSMITIONAPP_CABINSENSORS_H_
#define XT28TRANSMITIONAPP_CABINSENSORS_H_

#include "api_lib_basic.h"

//(*Chair position*)
#define AID_CHAIR_REV						IN_3_AID		// (*Chair in reverse position*)(*2_AID, sends high signal when in opposite mode*)
#define AID_CHAIR_FOR						IN_2_AID		// (*Chair in forward position*)(*3_AID*)

//(*Door signal*)
#define AID_DOOR			 				IN_1_AID		//(*: DWORD:=IN_1_AIV;*)

//(*Temperature*)
#define AIT_oil_temp						IN_64_AIT
//(*Fuel meter*)
#define AIR_fuel_meter						IN_65_AIR



typedef enum {
	CHAIR_IS_FRONT,
	CHAIR_IS_BACK
} chairPosition;

/*!
 * Configure the sensors used in the cabin and engine
 * the following sensors is included in this function
 *
 * 1. Fuel meter
 * 2. Temperature meater
 * 3. Chair position front or back
 * 4. Door state open or closed
 */
void CSConfigureCabinSensors(void);

/*!
 * Uppdate the sensor data
 */
void CSUpdateCabinSensor(void);

/*!
 * Get the chair position
 * @return chairPosition
 */
chairPosition CSGetCharPosition(void);

/*!
 *
 * @return
 */
bool CSGetDoorState(void);

/*!
 *
 * @return
 */
int CSGetFuelMeterPercentage(void);

/*!
 *
 * @return
 */
int CSGetFuelMeterOhm(void);

/*!
 *
 * @return
 */
int CSGetTankTemp(void);

#endif /* XT28TRANSMITIONAPP_CABINSENSORS_H_ */
