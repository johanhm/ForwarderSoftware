#include "CabinSensors.h"

#define DIGITAL_CHAIR_FRONT					0
#define DIGITAL_CHAIR_REAR					1
#define INDEX_SIZE_CHAIR					2

//defines index for global door
#define DIGITAL_DOOR						0
#define INDEX_SIZE_DOOR						1

void CSConfigureCabinSensors(void) {

	/* DOOR */
	/* The door is sending high and low signals dependent on chair position, 10V */
	in_cfgVoltageInput(AID_DOOR, 4000, 6000, 100, 2000, 6600, 100);
	/****CHAIR****/				/*The chair is sending high and low signals dependent on chair position, 10V*/
	in_cfgVoltageInput(AID_CHAIR_FOR, 4000, 6000, 100, 200, 6600, 200);
	in_cfgVoltageInput(AID_CHAIR_REV, 4000, 6000, 100, 200, 6600, 200);

	/****OIL TEMP****/
	in_cfgTempSensorType(AIT_oil_temp, 1); /*Temperature is calibrated from Bosch Rexroth since their sensor is used*/
	/****FUEL METER****/
	in_cfgTempSensorType(AIR_fuel_meter, 255);/*A custon resistance which has to be calibrated by hand*/

}


//static int  fuelmeterData;
//static int  fuelmeterPmil;
static int  tanktempData;
//static int  tanktempPmil;
static int  Ohm_fuelmeterData = 0;
static int Pcent_fuelmeterData = 0;

static int chairData[INDEX_SIZE_CHAIR] = {0};
static int doorDataDig;


void CSUpdateCabinSensor(void) {

	/* Char */
	chairData[DIGITAL_CHAIR_FRONT] = in(AID_CHAIR_FOR);
	chairData[DIGITAL_CHAIR_REAR] = in(AID_CHAIR_REV);

	/* Mother's door */
	doorDataDig = in(IN_1_AID);

	/* Temperature */
	Ohm_fuelmeterData= in(AIR_fuel_meter);
	/**********FUEL METER CONVERSION*********/
	//--Fuel Meter calibrationdata--//
	const int Fuel_meter_Ohm_min = 187;
	const int Fuel_meter_Ohm_max = 11;
	Pcent_fuelmeterData = 100 * Ohm_fuelmeterData / (Fuel_meter_Ohm_max-Fuel_meter_Ohm_min) - 100 * Fuel_meter_Ohm_min / (Fuel_meter_Ohm_max - Fuel_meter_Ohm_min);

	/* Gas tank */
	tanktempData = in(AIT_oil_temp)-50;

}

/*!
 * fixme redundans sensor, fix some logic to check for erros yo, if errors are ignored the following return should be sufficent
 */
chairPosition CSGetCharPosition(void) {

	if (chairData[DIGITAL_CHAIR_FRONT] == TRUE) {
		return CHAIR_IS_FRONT;
	}
	return CHAIR_IS_BACK;
}







