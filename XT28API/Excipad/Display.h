/*
 * Display.h
 *
 *  Created on: 3 maj 2016
 *      Author: ladmin
 */

#ifndef XT28API_EXCIPAD_DISPLAY_H_
#define XT28API_EXCIPAD_DISPLAY_H_

#include "XT28CANSupport.h"
#include "api_lib_basic.h"
#include "PendelumArmPosition.h"

/*!
 * Set sensor alert state on the display
 * @param state
 */
void DisplaySetSensorAlertStateTo(bool state);

typedef enum {
	CHAIR_IS_FRONT,
	CHAIR_IS_BACK
} chairPosition;

typedef enum {
	BREAK_IS_FALSE,
	BREAK_IS_TRUE
} handBreak;

/*!
 * Get is handbreak is activated
 * @return
 */
handBreak DisplayGetHandBreakState(void);

/*!
 * Get the position of the chair
 * @return
 */
chairPosition DisplayGetChairPosition(void);

/*!
 * Configure CAN status message callback
 * @param CANChannel
 * @param statusDataboxNr
 */
void DisplayConfigureCAN(uint8 CANChannel, int statusDataboxNr);

/*!
 * To the display
 * @param offset
 */
void DisplaySetHeightReference(int offset);

/*!
 * Set active dampening on or off
 * @param state
 */
void DisplaySetADStateTo(bool state);

/*!
 *  Set Active dampening on or off
 * @param state
 */
void DisplaySetPDStateTo(bool state);


/*!
 * Send latest states
 */
void DisplaySendLatestStatesOnCAN(void);



#endif /* XT28API_EXCIPAD_DISPLAY_H_ */
