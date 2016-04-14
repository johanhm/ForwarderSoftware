/*
 * XT28ActuateDriver.c
 *
 *  Created on: 26 nov. 2015
 *      Author: ladmin
 */

#include "ActiveDamping.h"

//-----------------------Defines for pendelurm outputs --------------------------------------
#define OUT_PENDELURM_FRONT_RIGHT_A		OUT_1_POH_CL
#define OUT_PENDELURM_FRONT_RIGHT_B		OUT_2_POH_CL
#define OUT_PENDELURM_FRONT_LEFT_A		OUT_3_POH_CL
#define OUT_PENDELURM_FRONT_LEFT_B		OUT_4_POH_CL
#define OUT_PENDELURM_MID_RIGHT_A		OUT_5_POH_CL
#define OUT_PENDELURM_MID_RIGHT_B		OUT_6_POH_CL
#define OUT_PENDELURM_MID_LEFT_A		OUT_7_POH_CL
#define OUT_PENDELURM_MID_LEFT_B		OUT_8_POH_CL
#define OUT_PENDELURM_REAR_RIGHT_A		OUT_9_POH_CL
#define OUT_PENDELURM_REAR_RIGHT_B		OUT_10_POH_CL
#define OUT_PENDELURM_REAR_LEFT_A		OUT_11_POH_CL
#define OUT_PENDELURM_REAR_LEFT_B		OUT_12_POH_CL

#define REFERENCE_CURRENT_ZERO 0 //Number taken as valve closed Zero output on both solenoids
#define REFERENCE_CURRENT_MAXIMUM_B_mA -200 //Min Ref Equivalent to Max output on Solenoid B Deadband+ -RefMin
#define REFERENCE_CURRENT_MAXIMUM_A_mA 200 //400 //Max Ref Equivalent to Max output on Solenoid A  Deadband+ Refmax
#define DEADZONE_FOR_SOLEONID_CURRENT_mA 390

volatile sint16 referenceSoleonidOutputCurrent_ma[6] = {REFERENCE_CURRENT_ZERO};
volatile sint16 Ref_A[6] = {REFERENCE_CURRENT_ZERO};
volatile sint16 Ref_B[6] = {REFERENCE_CURRENT_ZERO};

volatile uint8 defaultSafety = 0;



void actuatePendelumArmsTask(void) {
	uint8 i = 0;

	//Check global variables are within minimum and maximum range and limits
	for(i = 0; i < 6; i++) {
		//referenceSoleonidOutputCurrent_ma[i] = referenceSoleonidOutputCurrent_ma[i];
		if(referenceSoleonidOutputCurrent_ma[i] < REFERENCE_CURRENT_MAXIMUM_B_mA) {
			referenceSoleonidOutputCurrent_ma[i] = REFERENCE_CURRENT_MAXIMUM_B_mA;
		}
		else if(referenceSoleonidOutputCurrent_ma[i] > REFERENCE_CURRENT_MAXIMUM_A_mA) {
			referenceSoleonidOutputCurrent_ma[i] = REFERENCE_CURRENT_MAXIMUM_A_mA;
		}
	}
	//Compute scaled values for each cylinder's valves
	for(i = 0; i < 6; i++) {
		if(referenceSoleonidOutputCurrent_ma[i] == 0) {//both valves off
			Ref_A[i] = 0;
			Ref_B[i] = 0;}
		else if(referenceSoleonidOutputCurrent_ma[i] > 0) {//Output scaled on A  turn off B
			Ref_A[i] = referenceSoleonidOutputCurrent_ma[i] + DEADZONE_FOR_SOLEONID_CURRENT_mA;  //Out between 400 and 800
			Ref_B[i] = 0;}
		else if(referenceSoleonidOutputCurrent_ma[i] < 0) {//Output scaled on B  turn off A
			Ref_A[i] = 0;
			Ref_B[i] = (-1 * referenceSoleonidOutputCurrent_ma[i]) + DEADZONE_FOR_SOLEONID_CURRENT_mA;	} //Out between 400 and 800
	}

	//Cylinder position limit control, does not let cylinder be actuated further in the direction that passed the limit
	if (CYL_POSITION_LIMIT_ON) {
		for (i = 0; i < 6; i++) {
			if (Cyl_limit[i] == 1) {
				if (posData[i] < CYL_POS_MIN) { //Assuming REF_A() makes the cylinder go to the positive (extending) direction
					Ref_A[i] = 0;
				} else if (posData[i] > CYL_POS_MAX) {
					Ref_B[i] = 0;
				}     //Assuming REF_B() makes the cylinder go to the negative (retracting) direction
			}
		}
	}

	//If OUT_Analog then actuate solenoids with scaled values
	if(ANALOG_OUTPUT_ON == 1) {
		out(OUT_PENDELURM_FRONT_RIGHT_A, Ref_A[FR]);
		out(OUT_PENDELURM_FRONT_RIGHT_B, Ref_B[FR]);

		out(OUT_PENDELURM_FRONT_LEFT_A,  Ref_A[FL]);
		out(OUT_PENDELURM_FRONT_LEFT_B,  Ref_B[FL]);

		out(OUT_PENDELURM_MID_RIGHT_A,   Ref_A[MR]);
		out(OUT_PENDELURM_MID_RIGHT_B,   Ref_B[MR]);

		out(OUT_PENDELURM_MID_LEFT_A,    Ref_A[ML]);
		out(OUT_PENDELURM_MID_LEFT_B,    Ref_B[ML]);

		out(OUT_PENDELURM_REAR_RIGHT_A,  Ref_A[BR]);
		out(OUT_PENDELURM_REAR_RIGHT_B,  Ref_B[BR]);

		out(OUT_PENDELURM_REAR_LEFT_A,   Ref_A[BL]);
		out(OUT_PENDELURM_REAR_LEFT_B,   Ref_B[BL]);
	}

	defaultSafety++;
	if (defaultSafety > 80) {   //if no command has been received for 80*1ms out references to 0
		for (i = 0; i < 6; i++) {
			referenceSoleonidOutputCurrent_ma[i] = 0;
		}
		defaultSafety = 82;
	}
}
