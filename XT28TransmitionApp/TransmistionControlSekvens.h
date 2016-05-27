
#ifndef XT28TRANSMITIONAPP_TRANSMISIONCONTROLSEKEVNS_H_
#define XT28TRANSMITIONAPP_TRANSMISIONCONTROLSEKEVNS_H_

#include "api_lib_basic.h"
#include "WheelMotorActuate.h"
#include <math.h>
#include "WheelMotorSensor.h"
#include "SystemPressureSensors.h"
#include "CabinSensors.h"
#include "EngineComunicationsCAN.h"
#include "GasPedalSensor.h"


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
 *
 * @return
 */
bool TCSAttemtToSetBreakStateTo(bool breakState);

/*!
 * Get current drive state
 * @return
 */
driveState TCSGetSetDriveState(void);

/*!
 *
 * @param attemtedDriveState
 * @return
 */
driveState TCSAttemtToSetDriveStateTo(driveState attemtedDriveState);

/*!
 *
 * @param gasPedal
 */
void TCSActuate(int gasPedal, int maxSpeed);

/*!
 *
 * @param buttonCANSendState
 */
void TCSSendMotorPWNOnCAN(bool buttonCANSendState);



#endif /* XT28TRANSMITIONAPP_TRANSMISIONCONTROLSEKEVNS_H_ */
