

#ifndef _MANUEL_CONTROL_H_
#define _MANUEL_CONTROL_H_

void manual_Control_Task(void); //public available
void appl_Task_1(void);

// application prototypes declared in manual control and used in application
bool appl_setVpOnFirst(void);
void appl_EmergencyTask(void);

void appl_IdleTask_1(void);

void appl_setDefaults(void);
void appl_ErrorHandler(uint16 errorCode_u16, uint8 errorParam_u8);
void appl_updateDiagData(void);
void appl_AfterRunFunc(void);

#endif
