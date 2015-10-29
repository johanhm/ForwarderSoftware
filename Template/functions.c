/*
 * functions.c
 *
 *  Created on: 29 apr 2015
 *      Author: ladmin
 */

//Calculate force relationship Fg/Fl for a certain cylinder position
float forceRelationshipFromLoadToGround(uint16 cylinderPoss_mm) {
	float stroke = 0.82 + (cylinderPoss_mm / 1000.0);
	float alpha  = acos( (pow(bxy,2) + pow(l3,2) - pow(stroke,2)) / (2 * bxy * l3) );
	float theta  = alpha + theta2 + theta3;
	float theta1 = theta - theta3;
	float beta1  = acos((pow(stroke,2) + pow(bxy,2) - pow(l3,2)) / (2 * stroke * bxy));
	float gamma  = 0;
	float Load_force  = 1;
	float forceGroundRelationshipConstant = 0;

	if(beta1 < pi/2 + theta2) {
		gamma = pi/2 - (beta1 - theta2);
	} else {
		gamma = -(beta1 - (pi / 2 + theta2));
	}

	if (theta1 > pi/2) {
		forceGroundRelationshipConstant = Load_force * l3 * ((sin(gamma) * cos(theta1-pi/2) - cos(gamma) * sin(theta1-pi/2)) / (l1 * cos(theta - pi / 2)));
	} else if (gamma > 0) {
		forceGroundRelationshipConstant = Load_force*l3 * ((sin(gamma) * cos(pi / 2 - theta1) + cos(gamma) * sin(pi / 2 - theta1)) / (l1 * cos(pi / 2 - theta)));
	} else {
		forceGroundRelationshipConstant = Load_force * l3 * ((sin(gamma) * cos(pi / 2 - theta1) + cos(gamma) * sin(pi/2 - theta1)) / (l1 * cos(pi / 2 - theta)));
	}
	return forceGroundRelationshipConstant;  // FG/FL Relationship
}

//Return the vertical tire force correspondinthe load force in the cylinder
//sint16 Force_Vertical(uint16 cylinderPoss_mm, sint16 Load_force) {
sint16 forceOnWheelVerticalFromCylinderLoad(uint16 cylinderPoss_mm, sint16 Load_force) {
	float relativeConstant = forceRelationshipFromLoadToGround(cylinderPoss_mm);  //Get relationship dependg to ent on position
	sint16 forceOnWheelVertical_N = relativeConstant * Load_force;//Load_force; /// F_VERT bebfor i changed johan

	return forceOnWheelVertical_N;
}


//Calculates the load force needed for a desired vertical force
//sint32 Force_Load(uint16 cylinderPoss_mm, sint32 Vertical_force) {
sint32 forceCylinderLoadFromForceOnWheel(uint16 cylinderPoss_mm, sint32 Vertical_force) {
	float relativeConstant = forceRelationshipFromLoadToGround(cylinderPoss_mm);  //Get relationship dependent on position
	sint32 forceOnCylinder_N = Vertical_force / relativeConstant; //F_LOAD before i changed johan

	return forceOnCylinder_N;
}


void SENDCAN1(uint32 ID,sint16 A,sint16 B,sint16 C,sint16 D){  //Send up to 4x16bit Variables on CAN1 msg
	uint8 data_au8_sms[8] = {0};
	data_au8_sms[0] = A;
	data_au8_sms[1] = A >> 8;
	data_au8_sms[2] = B;
	data_au8_sms[3] = B >> 8;
	data_au8_sms[4] = C;
	data_au8_sms[5] = C >> 8;
	data_au8_sms[6] = D;
	data_au8_sms[7] = D >> 8;

	if (0 == can_sendData(CAN_1, ID, CAN_EXD_DU8, 8, data_au8_sms)) {}
}

void sendCan1UnsignInt(uint32 ID,uint16 A,uint16 B,uint16 C,uint16 D) {  //Send up to 4x16bit Variables on CAN1 msg
	uint8 data_au8_sms[8] = {0};
	data_au8_sms[0] = A;
	data_au8_sms[1] = A >> 8;
	data_au8_sms[2] = B;
	data_au8_sms[3] = B >> 8;
	data_au8_sms[4] = C;
	data_au8_sms[5] = C >> 8;
	data_au8_sms[6] = D;
	data_au8_sms[7] = D >> 8;

	if (0 == can_sendData(CAN_1, ID, CAN_EXD_DU8, 8, data_au8_sms)) {}
}


void SEND_ARRAY_CAN1(uint32 ID1, uint32 ID2, volatile sint16 data[], uint8 size_array) { //Send whole 6x16bit array on two CAN messages
	uint8 x = 0, i = 0;
	uint8 data_au8_sms_1[8] = {0};  //Array for message sending 1
	uint8 data_au8_sms_2[8] = {0};  //Array for message sending 2

	//Prepare data for first message
	for(x = 0; x < 4; x++) {
		data_au8_sms_1[i]   = data[x];
		data_au8_sms_1[i+1] = data[x] >> 8;
		i = i + 2;
	}

	if(size_array > 4) {  //If there is enough data then send it on second CAN message
		i=0;
		for(x = 4; x < size_array; x++) {
			data_au8_sms_2[i]   = data[x];
			data_au8_sms_2[i+1] = data[x] >> 8;
			i = i + 2;
		}
	}
	//Send Messages
	if (0 == can_sendData(CAN_1, ID1, CAN_EXD_DU8, 8, data_au8_sms_1)) {}
	if (size_array>4) {
		if (0 == can_sendData(CAN_1, ID2, CAN_EXD_DU8, (size_array*2)-8, data_au8_sms_2)) {}
	}
}
