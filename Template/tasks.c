/*
 * tasks.c
 All periodic running tasks
 */


#include "ActiveDamping.h"


//Ground contact controller
void test_Task(void) {

	uint8 x = 0,j = 0;
	for(x = 0; x < 6; x++) {  //Supervisor condition monitoring

		//Check which wheels are not in the ground
		if(messuredForceCylinderLoad_deciN[x] < air_limit / 10) {
			Ref_ground_force[x] = Ground_ref_force; //How fast to reach ground
			In_ground[x]        = 0;
		} else if (messuredForceCylinderLoad_deciN[x] > GROUND_P / 10) {   //Load limit
			Ref_ground_force[x] = 0;
			In_ground[x]        = 1;
		}

		//Arm position monitoring
		ARM_ACTIVE[x] = 1;  //Start active
		//if(posData[x]<CYL_POS_MIN){ARM_ACTIVE[x]=0;}           //Arms outside the position limits then disable
		//if(posData[x]>CYL_POS_MAX){ARM_ACTIVE[x]=0;}

		//Pressure condition monitoring
		if((pressureData[j] < 200) && (pressureData[j+1] < 200)) {
			ARM_ACTIVE[x] = 0;
		}  //If both sensors measure less than 1 bar, then either faulty sensor or hydraulic circuit
		j = j + 2;

		ARM_ACTIVE[x] = ARM_ACTIVE[x] && In_ground[x];   //Deactivate also if wheel is in the air


		if (ARM_ACTIVE[x] == 1) {
			count_active[x]++;
			ARM_ACTIVE_F[x] = count_active[x] / (float)MAX_COUNT;
		}
		if (ARM_ACTIVE[x] == 0) {
			count_active[x]--;
			ARM_ACTIVE_F[x] = count_active[x] / (float)MAX_COUNT;
		}

		if (ARM_ACTIVE_F[x] > 1) {
			ARM_ACTIVE_F[x] = 1;
			count_active[x] = MAX_COUNT;
		}  //Limit between 0 and 1
		if (ARM_ACTIVE_F[x] < 0) {
			ARM_ACTIVE_F[x] = 0;
			count_active[x] = 0;
		}
	}

	double a[18]={1.0,1.0,1.0,1.0,1.0,1.0,0.5,-0.5,0.5,-0.5,0.5,-0.5,1.5,1.5,-0.5,-0.5,-2.75,-2.75};
	double a_modified[18]={0};
	uint i=0;

	for(i = 0; i < 6; i++) {                    //Change Geometry matrix depending on unavailable actuators (Off the ground, not responding, saturated)
		a_modified[i]    = a[i]    * ARM_ACTIVE_F[i];
		a_modified[i+6]  = a[i+6]  * ARM_ACTIVE_F[i];
		a_modified[i+12] = a[i+12] * ARM_ACTIVE_F[i];
	}

	double b[18] = {0};
	funcpinv(a_modified,b);  //Calculate pseudo inverse

	//Change new inverse matrix from array[18] into 6x3 format
	uint8 index_1 = 0;
	for(i = 0; i < 6; i++) {
		for(x = 0; x < 3; x++) {
			moore_inverse_modified[i][x] = b[index_1];
			index_1++;
		}
	}
	sint16 i9 = 0;
	sint16 i10 = 0;
	for(i = 0; i < 6; i++) {
		i9=((In_ground[i]<<i)| i9 );
		i10=((ARM_ACTIVE[i]<<i)| i10 );
	}
	sendCAN1_sint16(CAN_ID_DEBUG_MSG_6	,i9,i10,ACTIVE_FORCE_CONTROL,0);
}
