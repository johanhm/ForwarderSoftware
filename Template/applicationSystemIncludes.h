/*
 * applicationSystemIncludes.h
 *
 *  Created on: 23 nov. 2015
 *      Author: ladmin
 */

#ifndef _APPLICATIONSYSTEMINCLUDES_H_
#define _APPLICATIONSYSTEMINCLUDES_H_

//Public functions
void appl_Task_1(void);
void appl_ErrorHandler(uint16 errorCode_u16, uint8 errorParam_u8);
void appl_setDefaults(void);
void appl_AfterRunFunc(void);
void appl_updateDiagData(void);
bool appl_setVpOnFirst(void);

void can_1_BusOffCallback(uint16 status_u16);
void can_3_BusOffCallback(uint16 status_u16);

//--- In / Out ----------------------------
void appl_configOutputs(void);
void appl_configInputs(void);

void appl_EmergencyTask(void);
void appl_IdleTask_1(void);

#endif /* TEMPLATE_APPLICATIONSYSTEMINCLUDES_H_ */
