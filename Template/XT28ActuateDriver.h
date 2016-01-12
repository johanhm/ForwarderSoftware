/*! \defgroup Actuate
 *  \brief This module handles the actuation of the pendelum arms
 */

/** \addtogroup Actuate
 *  @{
 */


#ifndef _XT28ACTUATEDRIVER_H_
#define _XT28ACTUATEDRIVER_H_

/*! \brief Task that actuate current on pendelum arms
 * This is a awsome functionality that this function have
 *
 *  Well.
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
/** @}*/


