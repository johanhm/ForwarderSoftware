
#ifndef XT28TRANSMITIONAPP_ANGLEJOINTACTUATE_H_
#define XT28TRANSMITIONAPP_ANGLEJOINTACTUATE_H_

#include "api_lib_basic.h"
#include "stdlib.h"
#include "AngleJointSensor.h"

//Turning cylinders
#define	POH_CL_TURN_FRONT_A_mA				OUT_13_POH_CL 	// (*FRONT*)
#define	POH_CL_TURN_FRONT_B_mA				OUT_14_POH_CL
#define	POH_CL_TURN_REAR_A_mA				OUT_15_POH_CL	//(*REAR*)
#define	POH_CL_TURN_REAR_B_mA				OUT_16_POH_CL

//TurningValves
#define cfg_T_DEBOUNCE				100					/* [ms] */
#define cfg_T_DITHER_FREQUENCY 		f_200Hz_DU16		/* [Hz] */
#define cfg_T_RESISTANCE_MIN		5000		//7400	/* [mOhm] */
#define cfg_T_RESISTANCE_MAX		30000		//21700


typedef enum {
	TURN_COMBINED,
	TURN_FRONT,
	TURN_REAR,
	TURN_PID
} turnState;


/*!
 * Set up, need to be called for the rest off the functions to function at all
 */
void AJAInitAndSetupAngleJointActuate(void);

void AJAActuate(turnState xt28TurnState, int joystickValue, bool chairPosition, int avrageWheelSpeed);





#endif /* XT28TRANSMITIONAPP_ANGLEJOINTACTUATE_H_ */
