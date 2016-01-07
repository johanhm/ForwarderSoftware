/*
 * XT28ManualControlPrivate.h
 *
 *  Created on: 23 nov. 2015
 *      Author: ladmin
 */

#ifndef _XT28MANUALCONTROLPRIVATE_H_
#define _XT28MANUALCONTROLPRIVATE_H_

//---------------CAN MESSAGE IDENTIFIER IN HEX-------------
#define MSG_ENABLE_PENDULUM_ARM_FRONT_RIGHT 0x10 //16	 //Byte 4, bit 5
#define MSG_ENABLE_PENDULUM_ARM_FRONT_LEFT 	0x01 //1	 //Byte 4, bit 1
#define MSG_ENABLE_PENDULUM_ARM_MID_RIGHT	0x04 //4     //Byte 5, bit 3
#define MSG_ENABLE_PENDULUM_ARM_MID_LEFT	0x40 //64	 //Byte 4, bit 7
#define MSG_ENABLE_PENDULUM_ARM_REAR_RIGHT	0x01 //1	 //Byte 6, bit 1
#define MSG_ENABLE_PENDULUM_ARM_REAR_LEFT	0x10 //16	 //Byte 5, bit 5
#define MSG_ENABLE_PENDULUM_ARM_ALL_DOWN	0x40 //64	 //Byte 3, bit 3
#define MSG_ENABLE_PENDULUM_ARM_ALL_UP		0x04 //4	 //Byte 3, bit 7
#define MSG_ENABLE_PENDULUM_ARM_TILT_Y		0x10 //16	 //Byte 2, bit 5
#define MSG_ENABLE_PENDULUM_ARM_TILT_X		0x40 //64	 //Byte 2, bit 7
#define MSG_ENABLE_SIMPLE_CONTROL			0x01 //1 	 //Byte 3, bit 1

/*** Defines for manual functions *************************************************************** */
//----------------------JOYSTICK CONTROL----------------------
#define JOYSTICK_Y_HIGH_POINT				4300
#define JOYSTICK_Y_MID_POINT				2350
#define JOYSTICK_Y_LOW_POINT				350
#define JOYSTICK_Y_DEADBAND					200
#define JOYSTICK_Y_HIGH_DEADBAND			JOYSTICK_Y_MID_POINT+JOYSTICK_Y_DEADBAND
#define JOYSTICK_Y_LOW_DEADBAND				JOYSTICK_Y_MID_POINT-JOYSTICK_Y_DEADBAND

//---------------------DEFINES FOR buttonStatus------------------
// Index_Cylinder_Left/Right_Front/Mid/Rear
#define INDEX_CYLINDER_FRONT_RIGHT 			0
#define INDEX_CYLINDER_FRONT_LEFT			1
#define INDEX_CYLINDER_MID_RIGHT	 		2
#define INDEX_CYLINDER_MID_LEFT 			3
#define INDEX_CYLINDER_REAR_RIGHT	 		4
#define INDEX_CYLINDER_REAR_LEFT	 		5
#define INDEX_CYLINDER_ALL_DOWN				6
#define INDEX_CYLINDER_ALL_UP				7
#define INDEX_CYLINDER_TILT_Y				8
#define INDEX_CYLINDER_TILT_X				9
#define INDEX_SIMPLE_CONTROL		        10
#define INDEX_SIZE_BUTTONSTATUS				11

//------------------------Solenoids----------------------------
#define SOLENOID_OFF						0	//Used for solenoid valve (off)


//private functions used only by manual control
void setXT28ControllState(void);
void actuateXT28CurrentControlState(void);

void modes(can_Message_ts* msg_s);
void setPassiveDampeningState(uint16 passiveState);
void caseSwitch(can_Message_ts* msg_s);
bool toggleVariable(bool toggleTarget);
void setVariablesZero(void);

//debugg function
void mirrorCANMessageForDebug(void);


#endif /* TEMPLATE_XT28MANUALCONTROLPRIVATE_H_ */
