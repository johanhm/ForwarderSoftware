#include "PendelumArmPressure.h"
#include <math.h>
#include "XT28CANSupport.h"
#include "PendelumArmPosition.h"
#include "XT28HardwareConstants.h"
#include "XT28CANSupport.h"


//Private prototytpes
static void lowPassFilterPressureSensor(float sampleTime);

// Start of implementations
void PAPRConfigurePressureSensorsVoltageInput(void) {

	/*
    uint16 uLowerStateThreshold_u16 = 1000;
    uint16 uUpperStateThreshold_u16 = 4000;
    uint16 tiStateDebounce_u16      = 100;
    uint16 uLowerDiagThreshold_u16  = 200;
    uint16 uUpperDiagThreshold_u16  = 4800;
    uint16 tiDiagDebounce_u16       = 200;
	 */

	/* pressure sensors 7-18 */
	in_cfgVoltageInput(IN_7_AIV,  1000, 4000, 100, 200, 4800, 200); //Front right A
	in_cfgVoltageInput(IN_8_AIV,  1000, 4000, 100, 200, 4800, 200); //Front right B
	in_cfgVoltageInput(IN_9_AIV,  1000, 4000, 100, 200, 4800, 200); //Front left A
	in_cfgVoltageInput(IN_10_AIV, 1000, 4000, 100, 200, 4800, 200); //Front left B
	in_cfgVoltageInput(IN_11_AIV, 1000, 4000, 100, 200, 4800, 200); //Mid right A
	in_cfgVoltageInput(IN_12_AIV, 1000, 4000, 100, 200, 4800, 200); //Mid right B
	in_cfgVoltageInput(IN_13_AIV, 1000, 4000, 100, 200, 4800, 200); //Mid left A
	in_cfgVoltageInput(IN_14_AIV, 1000, 4000, 100, 200, 4800, 200); //Mid left B
	in_cfgVoltageInput(IN_15_AIV, 1000, 4000, 100, 200, 4800, 200); //Rear right A
	in_cfgVoltageInput(IN_16_AIV, 1000, 4000, 100, 200, 4800, 200); //Rear right B
	in_cfgVoltageInput(IN_17_AIV, 1000, 4000, 100, 200, 4800, 200); //Rear left A
	in_cfgVoltageInput(IN_18_AIV, 1000, 4000, 100, 200, 4800, 200); //Rear left B

}

static uint16 pressureData_mV[INDEX_SIZE_PRESSURESENS]  = {0};
static uint16 pressureData_Bar[INDEX_SIZE_PRESSURESENS] = {0};
void PAPRUppdatePressureDataWithSampleTime(int sampleTimeUppdate_ms) {
	float sampleTime = (float)sampleTimeUppdate_ms / 1000;
	//read Pressure sensors and calculate Cylinder Forces
	pressureData_mV[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_A] = in(IN_8_AIV);
	pressureData_mV[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_B] = in(IN_7_AIV);
	pressureData_mV[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_A]  = in(IN_10_AIV);
	pressureData_mV[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_B]  = in(IN_9_AIV);
	pressureData_mV[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_A]   = in(IN_11_AIV);
	pressureData_mV[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_B]   = in(IN_14_AIV);
	pressureData_mV[ANALOG_MID_LEFT_PENDULUM_PRESSURE_A]    = in(IN_13_AIV);
	pressureData_mV[ANALOG_MID_LEFT_PENDULUM_PRESSURE_B]    = in(IN_12_AIV);
	pressureData_mV[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_A]  = in(IN_15_AIV);
	pressureData_mV[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_B]  = in(IN_18_AIV);
	pressureData_mV[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_A]   = in(IN_17_AIV);
	pressureData_mV[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_B]   = in(IN_16_AIV);

	//Scale pressures into KiloPascals for sending  [KPa]
	uint8 x = 0;
	for(x = 0; x < INDEX_SIZE_PRESSURESENS; x++) {
		pressureData_Bar[x] = (float)pressureData_mV[x] * 6.25 - 3125;
	}

	g_debug1 = pressureData_Bar[ANALOG_MID_LEFT_PENDULUM_PRESSURE_A];
	g_debug3 = pressureData_Bar[ANALOG_MID_LEFT_PENDULUM_PRESSURE_B];

	//Low pass filter pressure signals
	lowPassFilterPressureSensor(sampleTime);

	//deubb
	g_debug2 = pressureData_Bar[ANALOG_MID_LEFT_PENDULUM_PRESSURE_A];
	g_debug4 = pressureData_Bar[ANALOG_MID_LEFT_PENDULUM_PRESSURE_B];
}

static void lowPassFilterPressureSensor(float sampleTime) {
	static uint32 pressureDataLast_Bar[INDEX_SIZE_PRESSURESENS];
	float Tfp =  1.0 / (2.0 * 3.1415);
	float alpha = Tfp/(Tfp + sampleTime);

	uint8 x = 0;
	for (x = 0; x < INDEX_SIZE_PRESSURESENS; x++) {
		pressureData_Bar[x]      = alpha * pressureDataLast_Bar[x] + (1-alpha) * pressureData_Bar[x];
		pressureDataLast_Bar[x] = pressureData_Bar[x];
	}
}


void PAPRGetPressureDataArray_bar(int pressureDataOutput_bar[static INDEX_SIZE_PRESSURESENS]) {
	int pressureChamber = 0;
	for (pressureChamber = 0; pressureChamber < INDEX_SIZE_PRESSURESENS; pressureChamber++) {
		pressureDataOutput_bar[pressureChamber] = pressureData_Bar[pressureChamber];
	}
}

float PAPRGetPressureForChamber_bar(int chamber) {
	return (float)pressureData_Bar[chamber];
}


void PAPRSendPressureDataOnCAN(uint8 CANChannel, uint32 backID, uint32 middleID, uint32 frontID) {
	CANSend_uint16( CANChannel, backID,
			pressureData_Bar[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_A],
			pressureData_Bar[ANALOG_REAR_RIGHT_PENDULUM_PRESSURE_B],
			pressureData_Bar[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_A],
			pressureData_Bar[ANALOG_REAR_LEFT_PENDULUM_PRESSURE_B]
	);
	CANSend_uint16( CANChannel, middleID,
			pressureData_Bar[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_A],
			pressureData_Bar[ANALOG_MID_RIGHT_PENDULUM_PRESSURE_B],
			pressureData_Bar[ANALOG_MID_LEFT_PENDULUM_PRESSURE_A],
			pressureData_Bar[ANALOG_MID_LEFT_PENDULUM_PRESSURE_B]
	);
	CANSend_uint16( CANChannel, frontID,
			pressureData_Bar[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_A],
			pressureData_Bar[ANALOG_FRONT_RIGHT_PENDULUM_PRESSURE_B],
			pressureData_Bar[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_A],
			pressureData_Bar[ANALOG_FRONT_LEFT_PENDULUM_PRESSURE_B]
	);
}

