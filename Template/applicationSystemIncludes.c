/*
 * applicationSystemIncludes.c
 *
 *  Created on: 23 nov. 2015
 *      Author: ladmin
 */

#include "ActiveDamping.h"


/***************************************************************************************************
 *  FUNCTION:      appl_updateDiagData
 */
/**\brief         Update the variables which may be changed by BODAS-service.
 *
 * This function has to be programmed by the user and is only required for BODAS-service.
 * The function is called after application parameters have been modified with BODAS-service
 * and the new values can be taken over by the application.
 *
 *
 * \param[in]      -
 *
 * \return         -
 */
/**************************************************************************************************/
void appl_updateDiagData(void) {

} //appl_updateDiagData(void)

void appl_ErrorHandler(uint16 errorCode_u16, uint8 errorParam_u8) {
	static uint16 tempErrCode_u16;
	static uint8  tempErrParam_u8;

	tempErrCode_u16 = errorCode_u16;
	tempErrParam_u8 = errorParam_u8;
} // appl_ErrorHandler

void appl_setDefaults(void) {

} // appl_setDefaults

void appl_AfterRunFunc(void) {
	//nothing
} // appl_AfterRunFunc

void appl_Task_1(void) {
	uint16 diag_u16;
	safout_ts safout_s;
	uint16 appl_moError_u16;
	bool appl_VpFirstOnStatus_l;


	/* trigger check point 0 */
	sys_triggerTC(0);

	/* switch on VP's (power supplies for outputs) for the first time */
	appl_VpFirstOnStatus_l = appl_setVpOnFirst();
	if (FALSE != appl_VpFirstOnStatus_l) {

	}

	/*
	 * evaluation from the shut down test after startup - the channel is only available after
	 * an execcuted shut down test !!!
	 */

	diag_u16 = safout_getStatus (SAFOUT_41_POH);

	if (SDT_EXECUTE_DU16 == (diag_u16 & SDT_EXECUTE_DU16)) {
		// execution from a shut down test pending (no power supply for the outputs) or
		// still running - channel is not available
		// ...
	} else {
		if (SDT_FAILED_DU16 == (diag_u16 & SDT_FAILED_DU16)) {
			// shut down failed - channel is not available

			// short circuits to the supply side from the shut down switch(es) could be ignored
			// for a improved availability
			safout_ignoreError(SAFOUT_41_POH);

			// ...
		}

		if (SDT_CURRENT_TIMEOUT_DU16 == (diag_u16 & SDT_CURRENT_TIMEOUT_DU16)) {
			// no current flow through the shut down switch(es)within the stated time (open load etc.)
			//
			// ...
		}
	}
	// ...

	/*
	 * shut down test is finished, channel is available - evaluation from the diagnosis status
	 */

	diag_u16 = safout_getStatusxt (SAFOUT_41_POH, &safout_s);

	if (NO_AVAILABILITY_DU16 == (diag_u16 & NO_AVAILABILITY_DU16)) {
		// channel is deactivated - check the extended information for the error evaluation

		// ...

		// short circuits to the supply side from the shut down switch could be ignored
		// for a improved availability
		safout_ignoreError(SAFOUT_41_POH);

		// ...

	} else {
		// channel is available
		safout (SAFOUT_41_POH, OUT_1_POH_CL, 400);

		// ...
	}

	// Check if there is a hardware monitor error
	appl_moError_u16 = mo_getError();
	if (0 != appl_moError_u16) {
		// There is a harware monitor error

		// Inform the User by using CAN_1 (note: Transmitter of CAN_2, CAN_3 and CAN_4 are disabled
		// at several errors)

		switch (appl_moError_u16) {
		case MOF_VSS_1_DU16:
		{
			// sensor supply 1: voltage is out of range
			// reaction: e.g. ignore all signals of sensors which are supplied by VSS_1
			break;
		}

		case MOF_3V3_1V5_HW_DU16  :
		{
			// ECU internal voltages 1,5V/3,3V (one or both) are out of range
			// reaction: e.g.
			// - set outputs for an emergency mode such as speed < 5km/h:
			//   out(..);
			// - muting (include reset of hardware ciruit for 3V3/1V5 cut off and unlock VP on
			//   and EMCY on):
			//   mo_ignoreError();
			// - set VPs  on:
			//   sys_setVP(VP_1, ON);
			//   sys_setVP(VP_2, ON);
			// - set EMCY on:
			//   emcy_setPowerOn();
			// - If ECU internal voltages 1,5V/3,3V are in range than there is power on outputs.
			break;
		}

		//...

		default:
		{
			break;
		}
		} // switch
	} // if

	// ...
} // appl_Task_1

void can_1_BusOffCallback(uint16 status_u16) {
	static uint16 temp_u16;

	temp_u16 = status_u16;
} // can_1_BusOffCallback

void can_3_BusOffCallback(uint16 status_u16) {
	static uint16 temp_u16;

	temp_u16 = status_u16;
} // can_3_BusOffCallback

void appl_configOutputs(void) {
	/* POH's */
	out_cfg(OUT_1_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_2_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_3_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_4_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_5_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_6_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_7_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_8_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_9_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_10_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_11_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);
	out_cfg(OUT_12_POH_CL, cfg_debounce, cfg_frequency, cfg_minLoad, cfg_maxLoad);


	out_cfgPI(OUT_1_POH_CL, 157, 136);
	out_cfgPI(OUT_2_POH_CL, 157, 136);
	out_cfgPI(OUT_3_POH_CL, 157, 136);
	out_cfgPI(OUT_4_POH_CL, 157, 136);
	out_cfgPI(OUT_5_POH_CL, 157, 136);
	out_cfgPI(OUT_6_POH_CL, 157, 136);
	out_cfgPI(OUT_7_POH_CL, 157, 136);
	out_cfgPI(OUT_8_POH_CL, 157, 136);
	out_cfgPI(OUT_9_POH_CL, 157, 136);
	out_cfgPI(OUT_10_POH_CL, 157, 136);
	out_cfgPI(OUT_11_POH_CL, 157, 136);
	out_cfgPI(OUT_12_POH_CL, 157, 136);


	out_cfg(OUT_19_DOH, 100, f_100Hz_DU16, 4000, 18000);
	out_cfg(OUT_20_DOH, 100, f_100Hz_DU16, 4000, 18000);
	out_cfg(OUT_21_DOH, 100, f_100Hz_DU16, 4000, 18000);
	out_cfg(OUT_22_DOH, 100, f_100Hz_DU16, 4000, 18000);
	out_cfg(OUT_23_DOH, 100, f_100Hz_DU16, 4000, 18000);
	out_cfg(OUT_24_DOH, 100, f_100Hz_DU16, 4000, 18000);



} // appl_configOutputs

void appl_configInputs(void) {
	/* inputs angle sensors 1-6 */
	in_cfgVoltageInput(IN_1_AIV, 1000, 4000, 100, 200, 4800, 200); //angle sensor Front right
	in_cfgVoltageInput(IN_2_AIV, 1000, 4000, 100, 200, 4800, 200); //angle sensor Front left
	in_cfgVoltageInput(IN_3_AIV, 1000, 4000, 100, 200, 4800, 200); //angle sensor Mid right
	in_cfgVoltageInput(IN_4_AIV, 1000, 4000, 100, 200, 4800, 200); //angle sensor Mid left
	in_cfgVoltageInput(IN_5_AIV, 1000, 4000, 100, 200, 4800, 200); //angle sensor Rear right
	in_cfgVoltageInput(IN_6_AIV, 1000, 4000, 100, 200, 4800, 200); //angle sensor Rear left
	/* ... */

	/* pressure sensors 7-18 */
	in_cfgVoltageInput(IN_7_AIV, 1000, 4000, 100, 200, 4800, 200); //Front right A
	in_cfgVoltageInput(IN_8_AIV, 1000, 4000, 100, 200, 4800, 200); //Front right B
	in_cfgVoltageInput(IN_9_AIV, 1000, 4000, 100, 200, 4800, 200); //Front left A
	in_cfgVoltageInput(IN_10_AIV, 1000, 4000, 100, 200, 4800, 200); //Front left B
	in_cfgVoltageInput(IN_11_AIV, 1000, 4000, 100, 200, 4800, 200); //Mid right A
	in_cfgVoltageInput(IN_12_AIV, 1000, 4000, 100, 200, 4800, 200); //Mid right B
	in_cfgVoltageInput(IN_13_AIV, 1000, 4000, 100, 200, 4800, 200); //Mid left A
	in_cfgVoltageInput(IN_14_AIV, 1000, 4000, 100, 200, 4800, 200); //Mid left B
	in_cfgVoltageInput(IN_15_AIV, 1000, 4000, 100, 200, 4800, 200); //Rear right A
	in_cfgVoltageInput(IN_16_AIV, 1000, 4000, 100, 200, 4800, 200); //Rear right B
	in_cfgVoltageInput(IN_17_AIV, 1000, 4000, 100, 200, 4800, 200); //Rear left A
	in_cfgVoltageInput(IN_18_AIV, 1000, 4000, 100, 200, 4800, 200); //Rear left B
	//in_cfgVoltageInput(IN_19_AIV, 500, 4500, 100, 200, 4800, 200); //Pot meter

	/* inputs AIC_AI10V - activate current measuring */
	in_setCurrentMeasurement(1, ON);
	/* ... */
} // appl_configInputs

/***************************************************************************************************
 *  FUNCTION:      appl_setVpOnFirst
 */
/**\brief         All VP's are switched on.
 *
 * This function must be called cyclically.
 *
 * \param[in]      -
 *
 * \return         TRUE: Setting VPs on was finished. All VPs are switched on.
 *                 FALSE: Setting VPs on was not finished.
 */

bool appl_setVpOnFirst(void) {
	static uint8 firstVpOnState_u8 = 0;
	uint16 status_u16;
	bool returnValue_l = TRUE;

	if (0xFF != firstVpOnState_u8) {
		returnValue_l = FALSE;
		switch (firstVpOnState_u8) {
		case 0:
		{
			status_u16 = sys_setVP(VP_1, ON);

			switch (status_u16)
			{
			case SYSSETVP_OK_DU16:
			{
				// ok
				// VP_1 is ready (and Shut off path test are finished). Goto VP_2.
				firstVpOnState_u8 = 1;
				break;
			}

			case SYSSETVP_ON_LOCKED_DU16:
			{
				// Setting VP ON is locked (because of hardware monitor error)
				// Unlock is possible by calling mo_ignoreError() (muting of hardware monitor errors)
				// Setting VP on must be repeated.
				// mo_ignoreError();
				break;
			}

			case SYSSETVP_SOP_TEST_RUNNING_DU16:
			{
				// SOP test is running. It must be waited.
				break;
			}

			case SYSSETVP_INH_ACTIVE_DU16:
			{
				// Power supply is disabled by inhibit or output-enable input pin
				// Setting VP on must be repeated.
				break;
			}

			case SYSSETVP_NOUBATT_DU16:
			{
				// No power supply connected (at KL30).
				// Setting VP on must be repeated.
				break;
			}

			case SYSSETVP_NOVP_DU16:
			{
				// Power supply cannot be switched on for switch-off tests.
				// Check for error messages indicating that VP is switched off due to hardware or
				// monitoring errors.
				// Setting VP on must be repeated.
				break;
			}

			case SYSSETVP_UNEXPECTED_VP_DU16:
			{
				// Unexpected state of power supply for power stages previous to switch-off tests.
				// Setting VP on must be repeated.
				break;
			}

			default:
			{
				break;
			}
			} // switch

			break;
		} // case

		case 1:
		{
			status_u16 = sys_setVP(VP_2, ON);

			switch (status_u16)
			{
			case SYSSETVP_OK_DU16:
			{
				// ok
				// First time is finished.
				firstVpOnState_u8 = 0xFF;
				returnValue_l = TRUE;
				break;
			}

			case SYSSETVP_ON_LOCKED_DU16:
			{
				// Setting VP ON is locked (because of hardware monitor error)
				// Unlock is possible by calling mo_ignoreError() (muting of hardware monitor errors)
				// Setting VP on must be repeated.
				// mo_ignoreError();
				break;
			}

			default:
			{
				break;
			}
			} // switch
			break;
		} // case

		default:
		{
			break;
		}
		} // switch
	} // if
	// else: It is not the first time. So nothing must be done.

	return returnValue_l;
} // appl_setVpOnFirst

void appl_EmergencyTask(void) {
	sys_triggerTC(0);
} // appl_EmergencyTask

void appl_IdleTask_1(void) {

} // appl_IdleTask_1
