/** \defgroup WMA Wheel motor actuate
 * \ingroup ACTUATE
 * \brief Actuate the motors on each wheel
 *
 *  Does the following:
 *
 *  1. Configure motor actuation.
 *  2. Actuate depending on speed.
 *
 *  @{
 */

#ifndef XT28TRANSMITIONAPP_WHEELMOTORACTUATE_H_
#define XT28TRANSMITIONAPP_WHEELMOTORACTUATE_H_


#include "api_lib_basic.h"
#include <math.h>
#include "WheelMotorSensor.h"
#include "SystemPressureSensors.h"
#include "CabinSensors.h"
#include "XT28TransmissionCANSupport.h"


/* Motors */
#define	POH_CL_MOTOR_1_mA					OUT_5_POH_CL
#define	POH_CL_MOTOR_2_mA 					OUT_6_POH_CL
#define	POH_CL_MOTOR_3_mA 					OUT_7_POH_CL
#define	POH_CL_MOTOR_4_mA					OUT_8_POH_CL
#define	POH_CL_MOTOR_5_mA 					OUT_9_POH_CL
#define	POH_CL_MOTOR_6_mA 					OUT_10_POH_CL

/* Pumps */
#define	POH_CL_PUMP_1_A_mA					OUT_1_POH_CL
#define	POH_CL_PUMP_1_B_mA					OUT_2_POH_CL
#define	POH_CL_PUMP_2_A_mA					OUT_3_POH_CL
#define	POH_CL_PUMP_2_B_mA					OUT_4_POH_CL

/* Brake */
#define	DOH_PBRAKEVALVE1					OUT_20_DOH	//	(*Pbrake valve 1*)
#define	DOH_PBRAKEVALVE2					OUT_21_DOH	//	(*Pbrake valve 2*)
#define	DOH_PBRAKEVALVE3					OUT_22_DOH	//	(*Pbrake valve 3*)

typedef enum {
	NEUTRAL_DRIVE,
	FORWARD_DRIVE,
	BACKWARD_DRIVE,
	FORWARD_OVERDRIVE
} driveState;

typedef enum {
	REGULAOR_SECOUNDARY,
	REGULATOR_SEKVENS

}transmControlState;

/*!
 * Get current drive state
 * @return
 */
driveState WMAGetSetDriveState(void);

/*!
 *
 * @param attemtedDriveState
 * @return
 */
driveState WMAAttemtToSetDriveStateTo(driveState attemtedDriveState);

/*!
 *
 * @param gasPedal
 */
void WMAActuate(int gasPedal);

/*!
 *
 */
void WMASetupOutputToMotorsAndPumps(void);

/*!
 * Set break on or off
 * @param state
 */
void WMASetBreakState(bool state);

/*!
 * Actuate the wheels to drive in a direction depending on the set state.
 *
 * @param machineDriveState
 * @param overideState
 * @param slipState
 * @param periodicCallTime_ms
 * @param pMilLowPassGasPedalSignal
 */
void WMASetMotorReferenceAndActuate(driveState machineDriveState, bool overideState, bool slipState, int periodicCallTime_ms, int pMilLowPassGasPedalSignal);

/*!
 *
 * @param buttonCANSendState
 */
void WMASendMotorPWNOnCAN(bool buttonCANSendState);


#endif /* XT28TRANSMITIONAPP_WHEELMOTORACTUATE_H_ */
/** @}*/
