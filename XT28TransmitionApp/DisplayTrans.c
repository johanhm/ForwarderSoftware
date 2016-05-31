#include "DisplayTrans.h"

			//Display
#define CAN_ID_TX_FUNCTION_INFO_DMS_1		0x18FE1030 // 	(*0x18FE1010*)
#define CAN_ID_TX_FUNCTION_INFO_DMS_2		0x18FE1031 // 	(*0x18FE1011*)


int maxValueToDisplay = 0;
void DTSetMaxValueToDisplay(int maxValue) {
	maxValueToDisplay = maxValue;
}

void DTSendDMSOnCAN(uint8 CANChannel) {

	uint16 Button_Drive_Status = 0;
	uint16 Button_Turn_Status = 0;
	uint16 Button_Break_Status = WMAGetBreakState() * 4;

	driveState DriveSTATE = TCSGetSetDriveState();
	turnState TurnSTATE = AJAGetTurnState();

	if 		(DriveSTATE == NEUTRAL_DRIVE) Button_Drive_Status = 1;
	else if (DriveSTATE == FORWARD_DRIVE) Button_Drive_Status = 4;
	else if (DriveSTATE == BACKWARD_DRIVE)Button_Drive_Status = 16;
	else 								  Button_Drive_Status = 0;

	if 		(TurnSTATE == TURN_COMBINED) 	Button_Turn_Status = 16;
	else if (TurnSTATE == TURN_FRONT) 		Button_Turn_Status = 1;
	else if (TurnSTATE == TURN_REAR) 		Button_Turn_Status = 4;
	else if (TurnSTATE == TURN_PID) 		Button_Turn_Status = 64;
	else 									Button_Turn_Status = 0;

	//Construct msg Function DMS 1
	uint8 data_au8_fun_dms_1[8];
	data_au8_fun_dms_1[0] = Button_Break_Status;
	data_au8_fun_dms_1[1] = Button_Turn_Status;
	data_au8_fun_dms_1[2] = Button_Drive_Status;
	data_au8_fun_dms_1[3] = CSGetCharPosition();//PositionSTATE;
	data_au8_fun_dms_1[4] = AJSGetAngleFront() * 2 / 100; //angleData[MDEG_ANGLE_SENSOR_FRONT_1]*2/100;
	data_au8_fun_dms_1[5] = AJSGetAngleBack() * 2 / 100; //angleData[MDEG_ANGLE_SENSOR_REAR_1]*2/100;
	data_au8_fun_dms_1[6] = ECCGetEngineData().engineSpeedActual / 10; //Engine_speed_Act/10;
	data_au8_fun_dms_1[7] = (sint8)ECCGetEngineData().engineTemperature;//Engine_temp;

	can_sendData(CANChannel, CAN_ID_TX_FUNCTION_INFO_DMS_1, CAN_EXD_DU8, 8, data_au8_fun_dms_1);

	//Construct msg Function DMS 2
	uint8 data_au8_fun_dms_2[8];
	data_au8_fun_dms_2[0] = CSGetDoorState();			//doorDataDig;
	data_au8_fun_dms_2[1] = CSGetFuelMeterOhm(); 		//Ohm_fuelmeterData;
	data_au8_fun_dms_2[2] = CSGetTankTemp();			//tanktempData;
	data_au8_fun_dms_2[3] = CSGetFuelMeterPercentage();	//Pcent_fuelmeterData;
	data_au8_fun_dms_2[4] = 0;//buttonStatus[BUTTON_OVERDRIVE];
	data_au8_fun_dms_2[5] = maxValueToDisplay / 10;
	data_au8_fun_dms_2[6] = ( WMSGetAvrageRPMForWheels() * 0.1047 * 0.74 / 10 );
	data_au8_fun_dms_2[7] = 0;

	can_sendData(CANChannel, CAN_ID_TX_FUNCTION_INFO_DMS_2, CAN_EXD_DU8, 8, data_au8_fun_dms_2);
}
