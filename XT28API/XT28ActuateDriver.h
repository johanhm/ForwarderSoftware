/*
 * XT28ActuateDriver.h
 *
 *  Created on: 26 nov. 2015
 *      Author: ladmin
 */

#ifndef _XT28ACTUATEDRIVER_H_
#define _XT28ACTUATEDRIVER_H_


/*! \brief Task that actuate current on pendelum arms
 * Swag documentation
 *
 *  How does the references work on the end????
 */
void actuatePendelumArmsTask(void);


/*! \brief Get the state of the machine
 * Swag documentation
 *
 * Well thos works nice
 */
bool getCurrentOutputState(void);


void setCurrentOutputState(bool state);
void setOutputReferenceCurrentForWheel(int wheel, int current);


#endif /* TEMPLATE_XT28ACTUATEDRIVER_H_ */
