
#include "SystemPressureSensors.h"

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


void SPSConfigureSystemPressureSensors(void) {

	/****PRESSURE SENSORS****/
	in_cfgVoltageInput(AIV_Pressure_1_A_mV, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(AIV_Pressure_1_B_mV, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(AIV_Pressure_2_A_mV, 1000, 4000, 100, 200, 4800, 200);
	in_cfgVoltageInput(AIV_Pressure_2_B_mV, 1000, 4000, 100, 200, 4800, 200);
}


static int pressureData[INDEX_SIZE_PRESSURE] = {0};
void SPSUppdateSystemPressureSensors(void) {

	//read Pump pressure sensors
	pressureData[ANALOG_PUMP1_PRESSURE_A] = in(AIV_Pressure_1_A_mV);
	pressureData[ANALOG_PUMP1_PRESSURE_B] = in(AIV_Pressure_1_B_mV);
	pressureData[ANALOG_PUMP2_PRESSURE_A] = in(AIV_Pressure_2_A_mV);
	pressureData[ANALOG_PUMP2_PRESSURE_B] = in(AIV_Pressure_2_B_mV);

	/**********PRESSURE CONVERSION*********/
	const int Pressure_Umax = 4500;
	const int Pressure_Umin = 500;
	const int Umax_pressure = 60000; //[0.01 bar]

	pressureData[MBAR_PUMP1_PRESSURE_A] = Umax_pressure * (pressureData[ANALOG_PUMP1_PRESSURE_A] - Pressure_Umin) / (Pressure_Umax - Pressure_Umin);
	if (pressureData[ANALOG_PUMP1_PRESSURE_A] > Pressure_Umax) {
		pressureData[MBAR_PUMP1_PRESSURE_A] = Umax_pressure;
	}
	else if (pressureData[ANALOG_PUMP1_PRESSURE_A] < Pressure_Umin) {
		pressureData[MBAR_PUMP1_PRESSURE_A] = 0;
	}

	pressureData[MBAR_PUMP1_PRESSURE_B] = Umax_pressure * (pressureData[ANALOG_PUMP1_PRESSURE_B] - Pressure_Umin) / (Pressure_Umax - Pressure_Umin);
	if (pressureData[ANALOG_PUMP1_PRESSURE_B] > Pressure_Umax) {
		pressureData[MBAR_PUMP1_PRESSURE_B] = Umax_pressure;
	}
	else if (pressureData[ANALOG_PUMP1_PRESSURE_B] < Pressure_Umin) {
		pressureData[MBAR_PUMP1_PRESSURE_B] = 0;
	}

	pressureData[MBAR_PUMP2_PRESSURE_A] = Umax_pressure * (pressureData[ANALOG_PUMP2_PRESSURE_A] - Pressure_Umin) / (Pressure_Umax - Pressure_Umin);
	if (pressureData[ANALOG_PUMP2_PRESSURE_A] > Pressure_Umax) {
		pressureData[MBAR_PUMP2_PRESSURE_A] = Umax_pressure;
	}
	else if (pressureData[ANALOG_PUMP2_PRESSURE_A] < Pressure_Umin) {
		pressureData[MBAR_PUMP2_PRESSURE_A] = 0;
	}

	pressureData[MBAR_PUMP2_PRESSURE_B] = Umax_pressure * (pressureData[ANALOG_PUMP2_PRESSURE_B] - Pressure_Umin) / (Pressure_Umax-Pressure_Umin);
	if (pressureData[ANALOG_PUMP2_PRESSURE_B] > Pressure_Umax) {
		pressureData[MBAR_PUMP2_PRESSURE_B] = Umax_pressure;
	}
	else if (pressureData[ANALOG_PUMP2_PRESSURE_B] < Pressure_Umin) {
		pressureData[MBAR_PUMP2_PRESSURE_B] = 0;
	}

	//LOW PASS FILTER OF SIGNALS
	const float T_s = 0.020;
	const float f_cutoff = 0.8;

	const float Tf = 1 / (2 * M_PI * f_cutoff);
	const float alpha = Tf / (Tf + T_s);

	uint8 i;
	for (i = 0; i <= 3; i++) {
		pressureData[MBAR_LP_OLD_PUMP1_PRESSURE_A + i] = pressureData[MBAR_LP_PUMP1_PRESSURE_A + i];
		pressureData[MBAR_LP_PUMP1_PRESSURE_A + i] = alpha * pressureData[MBAR_LP_OLD_PUMP1_PRESSURE_A + i] + (1 - alpha) * pressureData[MBAR_PUMP1_PRESSURE_A + i];
	}
}

int SPSGetPump1Pressure_mbar(void) {
	return pressureData[MBAR_PUMP1_PRESSURE_A];
}

int SPSGetPump2Pressure_mbar(void) {
	return pressureData[MBAR_PUMP2_PRESSURE_A];
}

static uint8 sensorCANChannel;
static int sensorDataboxNumber;
void SPSConfigureSendSensorDatabox(uint8 CANChannel, uint8 databoxNumber, int systemPressureCANID) {

	sensorCANChannel = CANChannel;
	sensorDataboxNumber = databoxNumber;
	can_cfgTxDatabox(CANChannel,
			databoxNumber,
			systemPressureCANID,
			CAN_EXD_DU8
	);
}

void SPSSendSensorDataOnCAN(void) {

	//Construct msg SENSOR DMS 1
	uint8 data_au8_sens_dms_1[8];
	data_au8_sens_dms_1[0] = pressureData[MBAR_PUMP1_PRESSURE_A];
	data_au8_sens_dms_1[1] = pressureData[MBAR_PUMP1_PRESSURE_A] >> 8;
	data_au8_sens_dms_1[2] = pressureData[MBAR_PUMP1_PRESSURE_B];
	data_au8_sens_dms_1[3] = pressureData[MBAR_PUMP1_PRESSURE_B] >> 8;
	data_au8_sens_dms_1[4] = pressureData[MBAR_PUMP2_PRESSURE_A];
	data_au8_sens_dms_1[5] = pressureData[MBAR_PUMP2_PRESSURE_A] >> 8;
	data_au8_sens_dms_1[6] = pressureData[MBAR_PUMP2_PRESSURE_B];
	data_au8_sens_dms_1[7] = pressureData[MBAR_PUMP2_PRESSURE_B] >> 8;

	can_sendDatabox( sensorCANChannel,
			sensorDataboxNumber,
			8,
			data_au8_sens_dms_1
	);
}
