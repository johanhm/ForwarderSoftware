/*
 * XT28ReadSensors.h
 *
 *  Created on: 23 nov. 2015
 *      Author: ladmin
 */

#ifndef _XT28READSENSORS_H_
#define _XT28READSENSORS_H_


//public functions
void readPressureSensorsTask(void);  //Read pressure sensors
void readPositionSensorsTask(void);  //Read position sensors
void send_CAN_sensors_values_Task(void);


// This function returns the latest calculated optimal force for a wheel with number
sint16 getOptimalReferenceForceForWheel(uint8 wheelNumber);

#endif /* TEMPLATE_XT28READSENSORS_H_ */
