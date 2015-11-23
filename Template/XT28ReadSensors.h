/*
 * XT28ReadSensors.h
 *
 *  Created on: 23 nov. 2015
 *      Author: ladmin
 */

#ifndef _XT28READSENSORS_H_
#define _XT28READSENSORS_H_

//public functions
void read_Sensor_Task1(void);  //Read pressure sensors
void read_Sensor_Task2(void);  //Read position sensors
void send_CAN_sensors_values_Task(void);

#endif /* TEMPLATE_XT28READSENSORS_H_ */
