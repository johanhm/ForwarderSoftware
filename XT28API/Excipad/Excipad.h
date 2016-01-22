/*! \defgroup EXP Excipad
 *  \brief Handle Exipad and Joystick
 *
 *  This module handels the user interface with the exipad. From this module
 *  its possibole to get status about the exipad sutch as what
 *  button was pressed last, is a button currently beeing pressed and so on.
 *
 *  This module is design to work with a excipad made by exciepad company.
 *  You can configure what can channel it is connected to on the bodas controller.
 *
 *   @{
 */

#ifndef XT28API_EXCIPAD_EXCIPAD_H_
#define XT28API_EXCIPAD_EXCIPAD_H_

#include "api_lib_basic.h"

/*!
 * Exipad Button Enum. This type is used for returing what the latest button is and sutch.
 */
typedef enum {
	NONE,		/** No Button pressed */
	BUTTON_1,	/** Button 1 */
	BUTTON_3,	/** Button 3 */
	BUTTON_4,	/** Button 4 */
	BUTTON_6,	/** Button 6 */
	BUTTON_7,	/** Button 7 */
	BUTTON_9,	/** Button 9 */
	BUTTON_16,	/** Button 16 */
	BUTTON_17,	/** Button 17 */
	BUTTON_18,	/** Button 18 */
	BUTTON_19,	/** Button 19 */
	BUTTON_20	/** Button 20 */
} exipadButton;

/*!
 * Get the last button that was pressed. If the user pressed the button again this function will return NONE,
 * will return a !lastbutton.
 *
 * \return exipadButton last pressed, toggled if pressed again.
 */
exipadButton EXPGetLastPressedButtonWithToggle(void);

/*!
 * Get the currently presed button
 */
exipadButton EXPGetCurrentlyPressedButton(void);

/*!
 *  Sets the last pressed button to state NONE.
 */
void EXPSetLastPressedButtonToNone(void);

/*
 * Check if the user is currently pressing a button on the exciepad
 */
bool EXPGetUserIsHoldingAButtonDown(void);


/*!
 * This function is mandatory to call in the setup of the program if you need to use this module.
 * This function sets up what channel the exipad is connected. The setup requier to use two databoxes in the BODAS C-API. Any channels can be used that
 * is valid by the BODAS API and is not used by any other channel.
 *
 * \param[in] CANChannel The CAN channel the exipad is connected.
 * \param[in] buttonDataboxNr A databox number, valid range is [1 - 100]
 * \param[in] joystrickDataboxNr A databox number, valid range is [1 - 100]
 */
void EXPConfigureExcipad(uint8 CANChannel, int buttonDataboxNr, int joystrickDataboxNr);

/*!
 *  Get the scaled value of the excipad joystrick.
 *
 * \return int values in range [-400 - 400]
 */
int EXPGetJoystickScaledValue(void);



#endif /* XT28API_EXCIPAD_EXCIPAD_H_ */
/** @}*/
