volatile uint8  CYL_POSITION_LIMIT_ON = 1;     //Set to 1 to activate software cylinder position limits
volatile uint16 CYL_POS_MAX = 490; 			//Software cylinder position maximum limit (mm)
volatile uint16 CYL_POS_MIN = 100; 			//Software cylinder minimum position limit (mm)
volatile uint8  ACTIVE_FORCE_CONTROL  = 0;		// To output force control reference to valve
volatile uint8  ACTIVE_HEIGHT_CONTROL = 1;
volatile uint8  ACTIVE_HEIGHT_DAMPING = 1;
volatile uint8 	ACTIVE_ZSKY_CONTROL   = 1;
volatile uint8 	ACTIVE_THETA_CONTROL  = 1;
volatile uint8 	ACTIVE_PHI_CONTROL    = 1;
volatile uint8  Control_allocation_on  = 1;
volatile uint8  To_ground_active       = 1;

volatile uint16 balance_force = 10000;

volatile uint16 Zc_ref = 250;  //Height Reference


volatile sint16 K_z    = 1000;  //Height controller proportional constant
volatile sint16 B_Zc   = 200;  //Chassis height damping
volatile uint16 BSky_Z = 0;  //Chassis force application points Zci skyhook damping
volatile sint16 I_z    = 0;  //Integral constant

volatile sint16 K_phi    = 200;  //
volatile uint16 BSky_phi = 50;
volatile sint16 I_phi    = 0;

volatile sint16 K_theta    = 1000;
volatile uint16 BSky_theta = 200;
volatile sint16 I_theta    = 0;

#define MAX_ZI      10000   //Integrator limit Z
#define MAX_PHI_I   2000  //Integrator limit Phi
#define MAX_THETA_I 2000 //Integrator limit Theta

//Wheel in air constants
volatile sint16 air_limit= -50;  //limit how much the wheel can leave the ground (N at cylinder)

volatile uint16 Ground_ref_force = 10000;       //Force reference used to reach ground pressure [N]
volatile uint16 GROUND_P         = 10000;  //When to consider its at ground  [N]

#define MAX_COUNT 50  //x*20ms sets the transition time for the control allocation changes (50=1second)

volatile sint16 count_active[6] = {MAX_COUNT};
