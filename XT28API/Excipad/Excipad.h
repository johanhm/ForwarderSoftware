/*! \defgroup EXP Excipad
 *  \brief Thos module handels joystrick and buttons
 *
 *   @{
 */

#ifndef XT28API_EXCIPAD_EXCIPAD_H_
#define XT28API_EXCIPAD_EXCIPAD_H_

#include "api_lib_basic.h"

/*!
 * The button cases
 */
typedef enum {
	NONE,
	BUTTON_1,
	BUTTON_3,
	BUTTON_4,
	BUTTON_6,
	BUTTON_7,
	BUTTON_9,
	BUTTON_16,
	BUTTON_17,
	BUTTON_18,
	BUTTON_19,
	BUTTON_20
} exipadButton;

/*!
 * Get last pressed button
 */
exipadButton EXPGetLastPressedButtonWithToggle(void);

/*!
 * Get the currently presed button
 */
exipadButton EXPGetCurrentlyPressedButton(void);

/*
 * Check if the user is currenntly pressing a button on the exipad
 */
bool EXPGetUserIsHoldingAButtonDown(void);


/*!
 * Configure excipad
 */
void EXPConfigure(uint8 CANChannel, int buttonDataboxNr, int joystrickDataboxNr);



#endif /* XT28API_EXCIPAD_EXCIPAD_H_ */
/** @}*/
