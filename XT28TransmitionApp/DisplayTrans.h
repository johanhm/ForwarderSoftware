
#ifndef XT28TRANSMITIONAPP_DISPLAYTRANS_H_
#define XT28TRANSMITIONAPP_DISPLAYTRANS_H_

#include "api_lib_basic.h"
#include "WheelMotorActuate.h"
#include "AngleJointActuate.h"
#include "CabinSensors.h"
#include "XT28TransmissionCANSupport.h"
#include "AngleJointSensor.h"
#include "EngineComunicationsCAN.h"

/*!
 * Display status CAN message
 * @param CANChannel
 */
void DTSendDMSOnCAN(uint8 CANChannel);



#endif /* XT28TRANSMITIONAPP_DISPLAYTRANS_H_ */
