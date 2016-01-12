

#include "api_lib_basic.h"
//#include "XT28_api.h"
#include "IMU.h"

// Prototypes
void sys_main(void);


//Start of program
void sys_main(void) {


	IMUConfigure(CAN_2, 1, 2);


	// Initialize RC/SRC.
	sys_init("SMS", "RC30-00D6"); // RC28-14/30


}
