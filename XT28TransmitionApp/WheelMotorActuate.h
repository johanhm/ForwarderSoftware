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

typedef struct SRControlSignals {
	int pump_A_mEpsilon[2];
	int pump_B_mEpsilon[2];
	int motor_mEpsilon[6];
} SRControlSignals;


/*!
 *
 * @param controlSignals
 */
void WMASaturateEpsilonAndActuateMotors(SRControlSignals controlSignals);

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
 *
 * @return
 */
bool WMAGetBreakState(void);


#endif /* XT28TRANSMITIONAPP_WHEELMOTORACTUATE_H_ */
/** @}*/
