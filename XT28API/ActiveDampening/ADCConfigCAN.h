/*
 * ADConfigCAN.h
 *
 *  Created on: 20 apr. 2016
 *      Author: ladmin
 */

#ifndef XT28API_ACTIVEDAMPENING_ADCCONFIGCAN_H_
#define XT28API_ACTIVEDAMPENING_ADCCONFIGCAN_H_

#include "XT28CANSupport.h"
#include "ActiveDampening.h"


/*!
 * Enable setting the controller parameters though CAN with Canalyzer
 *
 * @param CANChannel	The CAN channel you send parameters from
 * @param databoxNr1	A unique valid data box number
 * @param databoxNr2	A unique valid data box number
 * @param databoxNr3	A unique valid data box number
 * @param databoxNr4	A unique valid data box number
 */
void ADCFGConfigureParameterSettingsFromCAN(uint8 CANChannel, uint16 databoxNr1, uint16 databoxNr2, uint16 databoxNr3, uint16 databoxNr4);


/*!
 * Get funtions
 */
float ADCFGetCANHeightRef(void);
float ADCFGetCANPhiRef(void);
float ADCGetCANThetaRef(void);
float ADCGetCANForcePGain(void);

/*!
 * Set the control parameters from CAN
 */
void ADCSetControlParametersWithCAN(void);



#endif /* XT28API_ACTIVEDAMPENING_ADCCONFIGCAN_H_ */
