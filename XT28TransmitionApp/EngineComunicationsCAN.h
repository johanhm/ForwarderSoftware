
#ifndef XT28TRANSMITIONAPP_ENGINECOMINICATIONSCAN_H_
#define XT28TRANSMITIONAPP_ENGINECOMINICATIONSCAN_H_

#include "api_lib_basic.h"

typedef struct EngineData{
	int colantTemperature;
	int engineTemperature;
	int engineSpeedActual;
} EngineData;


void ECCInitAndSetupEngineCANCommunications(void);

void ECCUpdateDataFromCAN(void);

void ECCSetEngineRPMReference(int RPMReference);

EngineData ECCGetEngineData(void);


#endif /* XT28TRANSMITIONAPP_ENGINECOMINICATIONSCAN_H_ */
