/*
 * WheelMotorActuate.h
 *
 *  Created on: 13 maj 2016
 *      Author: ladmin
 */

#ifndef XT28TRANSMITIONAPP_WHEELMOTORACTUATE_H_
#define XT28TRANSMITIONAPP_WHEELMOTORACTUATE_H_


#include "api_lib_basic.h"
#include <math.h>
#include "WheelMotorSensor.h"


/* Motors */
#define	POH_CL_MOTOR_1_mA					OUT_5_POH_CL
#define	POH_CL_MOTOR_2_mA 					OUT_6_POH_CL
#define	POH_CL_MOTOR_3_mA 					OUT_7_POH_CL
#define	POH_CL_MOTOR_4_mA					OUT_8_POH_CL
#define	POH_CL_MOTOR_5_mA 					OUT_9_POH_CL
#define	POH_CL_MOTOR_6_mA 					OUT_10_POH_CL

/* Brake */
#define	DOH_PBRAKEVALVE1					OUT_20_DOH	//	(*Pbrake valve 1*)
#define	DOH_PBRAKEVALVE2					OUT_21_DOH	//	(*Pbrake valve 2*)
#define	DOH_PBRAKEVALVE3					OUT_22_DOH	//	(*Pbrake valve 3*)

typedef enum {
	NEUTRAL_DRIVE,
	FORWARD_DRIVE,
	BACKWARD_DRIVE,
	PID_DRIVE
} driveState;


/*!
 *
 */
void WMASetupOutputToMotors(void);

/*!
 * Set break on or off
 * @param state
 */
void WMASetBreakState(bool state);

/*!
 *
 * @param machineDriveState
 * @param slipState
 * @param periodicCallTime_ms
 */
void WMASetMotorReferenceAndActuate(driveState machineDriveState, bool overideState, bool slipState, int periodicCallTime_ms, int pMilLowPassGasPedalSignal);

/*!
 *
 * @param buttonCANSendState
 */
void WMASendMotorPWNOnCAN(bool buttonCANSendState);


#endif /* XT28TRANSMITIONAPP_WHEELMOTORACTUATE_H_ */
