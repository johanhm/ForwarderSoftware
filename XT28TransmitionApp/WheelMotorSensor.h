/*
 * WheelMotorSensor.h
 *
 *  Created on: 13 maj 2016
 *      Author: ladmin
 */

#ifndef XT28TRANSMITIONAPP_WHEELMOTORSENSOR_H_
#define XT28TRANSMITIONAPP_WHEELMOTORSENSOR_H_

#include "api_lib_basic.h"


		//(*Motor speeds*)
#define FI_Motor_1_hz						IN_66_FI
#define FI_Motor_2_hz						IN_67_FI
#define FI_Motor_3_hz						IN_68_FI
#define FI_Motor_4_hz						IN_71_FI
#define FI_Motor_5_hz						IN_72_FI
#define FI_Motor_6_hz						IN_73_FI
 // Motor count
#define CI_Motor_1							IN_66_CI
#define CI_Motor_2							IN_67_CI
#define CI_Motor_3							IN_68_CI
#define CI_Motor_4							IN_71_CI
#define CI_Motor_5							IN_72_CI
#define CI_Motor_6							IN_73_CI




/*!
 *
 */
void WMSInitAndConfigureSpeedSensors(void);

/*!
 *
 */
void WMSUpdateSensorValues(void);

/*!
 *
 */
void WMSSendSensorDataOnCAN(void);

/*!
 *
 * @param wheel
 * @return
 */
int WMSGetRPMForWheel(int wheel);

/*!
 *
 * @return
 */
int WMSGetAvrageRPMForWheels(void);



#endif /* XT28TRANSMITIONAPP_WHEELMOTORSENSOR_H_ */
