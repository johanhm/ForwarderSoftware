
#ifndef XT28TRANSMITIONAPP_DISPLAYTRANS_H_
#define XT28TRANSMITIONAPP_DISPLAYTRANS_H_

#include "api_lib_basic.h"
#include "WheelMotorActuate.h"
#include "AngleJointActuate.h"
#include "CabinSensors.h"
#include "XT28TransmissionCANSupport.h"
#include "AngleJointSensor.h"
#include "EngineComunicationsCAN.h"
#include "TransmistionControlSekvens.h"

/*!
 * Display status CAN message
 * @param CANChannel
 */
void DTSendDMSOnCAN(uint8 CANChannel);

/*!
 * Set display max value speed ref
 * @param maxValue
 */
void DTSetMaxValueToDisplay(int maxValue);



#endif /* XT28TRANSMITIONAPP_DISPLAYTRANS_H_ */
