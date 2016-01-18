#include "ActiveDampening.h"
#include "PendelumArmPressure.h"
#include "PendelumArmPosition.h"
#include "XT28CANSupport.h"
#include "XT28HardwareConstants.h"

//Valve flow curve parameters
#define VALVE_FLOW_FIT_PARAMETER_CP1  0.0000117254976
#define VALVE_FLOW_FIT_PARAMETER_CP2  -0.0020898157818
#define VALVE_FLOW_FIT_PARAMETER_CP3  0.1025966561449
#define VALVE_FLOW_FIT_PARAMETER_CP4  2.2459943305454
#define VALVE_FLOW_FIT_PARAMETER_CP5  399  //416.9941090504642

//Sliding mode parameters
#define DELTA_PRESSURE_8bar               800000  //8 bar pressure compensator setting
#define MAXIMUM_FLOW_QMAX_m3s             100/1000/60  // maximum flow  (m^3/s)
#define SLIDING_MODE_CONTROL_PARAMETER_Kt 0.000077 //orginalvalue is 0.000077

// Z height controller
#define MAX_ZI      10000   //Integrator limit Z
#define MAX_PHI_I   100000	//2000  //Integrator limit Phi
#define MAX_THETA_I 2000 	//Integrator limit Theta


// Private prototypes
static void heightControllAddToAllocationMatrix(void);
static void hightControllSkyhookForceAddition(void);
//static void rollPhiControllAddToAllocationMatrix(void);
//static void pitchThetaControllAddToAllocationMatrix(void);
//static void decoupleHightRollPitchAndConvertToCylinderForceForAllWheels(void);
//static void calculateForceReferenceForAllWheels(void);
//static sint32 deadBandCheckForceReferenceError(sint32 currentCylinderForce, sint32 forceReferenceCylinder, uint8 wheelCounter);
//static void mapErestimatedFlowToCurrentOutputOnWheelWithNumber(uint8 wheelCounter);
//static void calculateErestimatedFlowForWheelWithNumber(uint8 cylinderCounter);


static sint32 forceHeightSkyHookRef[SUM_WHEELS] = {0};
static void hightControllSkyhookForceAddition(void) {
	uint8 wheel = 0;
	uint16 BSky_Z = 0;  //Chassis force application points Zci skyhook damping

	for (wheel = 0; wheel < 6; wheel++) {
		forceHeightSkyHookRef[wheel] = -BSky_Z * PAPOSGetVelDataForWheel(wheel);     //Skyhook damping force per chassis wheel point [N]
		forceHeightSkyHookRef[wheel] = PAPRConvertVerticalForceOnWheelToCylinderLoadForce(PAPOSGetPosDataForWheel_mm(wheel), forceHeightSkyHookRef[wheel]); //Transform vertical force into cylinder force
	}
}

static float heightReference_mm = 0;
static float phiReference_deg = 0;
static float thetaReference_deg = 0;
void ADCSetReferenceValuesForNivController(float height, float phi, float theta) {
	heightReference_mm = height;
	phiReference_deg = phi;
	thetaReference_deg = theta;
}

static sint32 forceMatrix[3] = {0, 0, 0};
static void heightControllAddToAllocationMatrix(void) {
	static sint32 forceReferenceHeightZ = 0;
	static sint32 forceHeightDamp = 0;
	static sint16 heightError = 0;

	static sint16 K_z = 1000;
	static sint16 I_z = 0;

	static sint32 Z_k = 0;
	static sint32 Z_I = 0;
	static sint16 B_Zc = 200;

	//P(Stiffness) I control
	heightError = heightReference_mm - PAPOSGetAvrageHeightOfForwarder();   //Zc between is average of all arm positions, between (0 and 500) mm
	if (heightError < 5 && heightError > -5) {
		Z_I = 0;   //If we reach almost zero error, reset integrator
		heightError = 0;
	}
	Z_k = heightError * K_z;
	Z_I = (heightError + Z_I) * I_z;

	if (Z_I > MAX_ZI) {
		Z_I = MAX_ZI;
	}  //Clamp integrator to max
	if (Z_I < -MAX_ZI) {
		Z_I = -MAX_ZI;
	}  //Clamp integrator to min

	forceHeightDamp = -B_Zc * PAPOSGetAvrageHeightVelocityOfForwarder();
	forceReferenceHeightZ  = Z_k + Z_I + forceHeightDamp; //Sum vertical forces
	forceMatrix[0] = forceReferenceHeightZ; //Include in Force matrix for decoupling
}

/*
static void rollPhiControllAddToAllocationMatrix(void) {
	if (ACTIVE_PHI_CONTROL == 1) {

		Phi_I = I_phi;
		static volatile sint32 Idel = 0;
		static volatile sint32 Phi_I_old = 0;
		static volatile float intergratorPart = 0;
		Phi_error = 0 - Phi_deg; //Reference is 0

		if(Phi_error > 5 || Phi_error < -5) {  //Error tolerance of 1 degree when the value was set to 5
			intergratorPart = intergratorPart + (float)(Phi_error) / 10; //if the error is less then 1 this will be zero
		}

		if (ACTIVE_FORCE_CONTROL == 0) {
			intergratorPart = 0;
		}

		Phi_k = Phi_error * K_phi;
		if (Phi_I != Phi_I_old) {
			intergratorPart = 0;
			Phi_I_old       = Phi_I;
		}

		Idel = intergratorPart * Phi_I ;
		//Phi_I = Phi_I * intergratorPart / 100;

		if (Idel > MAX_PHI_I) {
			//Phi_I = MAX_PHI_I;
			if (Phi_I == 0 ) {
				Phi_I = 1;
			}
			intergratorPart = MAX_PHI_I / Phi_I;
		}  //Clamp integrator to max
		if (Idel < -MAX_PHI_I) {
			intergratorPart = -MAX_PHI_I / Phi_I;
		}

		Phi_sky = -BSky_phi * Gyro_Phi_deg;
		F_REF_Phi = Phi_k + Phi_sky + Idel;//Phi_I; //Sum phi moment
		F_matrix[1] = F_REF_Phi;  //Assign to force vector
		//sl_debug_1 = Idel;
		//sl_debug_2 = intergratorPart;
		//sl_debug_3 = Phi_I;
	}
	else {
		F_matrix[1] = 0;
	}
}
 */

/*
static void pitchThetaControllAddToAllocationMatrix(void) {
	if(ACTIVE_THETA_CONTROL == 1) {

		Theta_error = 0 - Theta_deg; //Reference is 0
		if(Theta_error < 0.5 && Theta_error > -0.5){  //Error tolerance of 1 degree when the value was set to 5
			Theta_I = 0;   //If we reach almost zero error, reset integrator
			Theta_error = 0;
		}

		Theta_k = Theta_error * K_theta;  //Ref=0  Error=(0-Thetadeg)

		Theta_I = -Theta_deg + Theta_I;
		if(Theta_I > MAX_THETA_I) {
			Theta_I = MAX_THETA_I;
		}  //Clamp integrator to max
		if(Theta_I < -MAX_THETA_I) {
			Theta_I = -MAX_THETA_I;
		}  //Clamp integrator to min

		Theta_sky = -BSky_theta * Gyro_Theta_deg;
		F_REF_Theta = Theta_k + Theta_sky + Theta_I; //Sum theta moment
		F_matrix[2] = F_REF_Theta;  //Assign to force vector
	}
	else {
		F_matrix[2] = 0;
	}
}
 */

/*
static void decoupleHightRollPitchAndConvertToCylinderForceForAllWheels(void) {
	uint8 i = 0;
	uint8 k = 0;

	for (i = 0; i <= 5; i++) {  //Moore row counter
		sum = 0;
		for (k = 0; k <= 2; k++) {  //Moore column counter
			if (Control_allocation_on == 0) {
				sum = sum + (float)moore_inverse[i][k] * F_matrix[k];
			}
			if (Control_allocation_on == 1) {
				sum = sum + (float)moore_inverse_modified[i][k] * F_matrix[k];
			}
		}
		F_REF[i] = sum;  //Vertical reference force for each cylinder
		F_REF_CYL[i] = forceCylinderLoadFromForceOnWheel(posData[i], F_REF[i]);  //Calculate needed cylinder force according to arm position
	}
}
 */

/*
static void calculateForceReferenceForAllWheels(void) {
	uint8 wheel = 0;
	for(wheel = 0; wheel <= 5; wheel++) {
		if (To_ground_active == 0) {
			Ref_ground_force[wheel] = 0;
		}

		//change between optimal dispribuiton or not
		F_REF_CYL[wheel] = getOptimalReferenceForceForWheel(wheel) * 10 + F_REF_CYL[wheel] + F_Z_sky[wheel] + Ref_ground_force[wheel];

		//F_REF_CYL[wheel] = messuredForceCylinderLoad_deciN[wheel] * 10 + F_REF_CYL[wheel] + F_Z_sky[wheel] + Ref_ground_force[wheel];

		//if(F_REF_CYL[x]<GROUND_P){F_REF_CYL[x]=Load_force[x]*10+Ref_ground_force[x];}
		if(F_REF_CYL[wheel] < GROUND_P) {
			F_REF_CYL[wheel] = GROUND_P;
		}
	}
}
 */

/*
static void calculateErestimatedFlowForWheelWithNumber(uint8 wheelCounter) {

	//create variables
	uint32 sl_P1  = 0; //KPa*1000=[Pa]
	uint32 sl_P2  = 0;  //Kpa*1000=[Pa]
	sint32 sl_Fl  = 0; //Load force in [N]
	sint32 sl_Vel = 0;  //Cylinder velocity in mm/s
	sint32 sigma  = 0;

	float L = 0;
	float sgn = 0;

	//Map Variables to latest cylinder values and scale
	sl_P1 = pressureData[wheelCounter*2] * 1000; //KPa*1000=[Pa]
	sl_P2 = pressureData[(wheelCounter*2)+1] * 1000;  //Kpa*1000=[Pa]
	sl_Fl = messuredForceCylinderLoad_deciN[wheelCounter] * 10; //Load force in [N]

	if ((velData[wheelCounter] > -10) || (velData[wheelCounter] < 10)) {
		sl_Vel = 0;
	} else {
		sl_Vel = velData[wheelCounter];
	} //Cylinder velocity in mm/s

	//sigma = sl_Fl - F_REF_CYL[wheelCounter]; //dont commet this you retard
	sigma = deadBandCheckForceReferenceError(sl_Fl , F_REF_CYL[wheelCounter], wheelCounter);

	sigma = sigma / 200;
	sgn = ((float)sigma / (labs(sigma) + 1000.0));

	if (sl_uold[wheelCounter] >= 0) {
		L = CYLINDER_PUSH_AREA_SIDE_A1_m2 * MAXIMUM_FLOW_QMAX_m3s + CYLINDER_PUSH_AREA_SIDE_B2_m2 * sqrt(abs(sl_P2 - 0)) * MAXIMUM_FLOW_QMAX_m3s / sqrt(DELTA_PRESSURE_8bar);
	} else {
		L = CYLINDER_PUSH_AREA_SIDE_B2_m2 * MAXIMUM_FLOW_QMAX_m3s + CYLINDER_PUSH_AREA_SIDE_A1_m2 * sqrt(abs(sl_P1 - 0)) * MAXIMUM_FLOW_QMAX_m3s / sqrt(DELTA_PRESSURE_8bar);
	}
	sl_u = 1.0 / L * ((pow(CYLINDER_PUSH_AREA_SIDE_A1_m2,2) + pow(CYLINDER_PUSH_AREA_SIDE_B2_m2,2)) * ((float)sl_Vel / 1000.0) - SLIDING_MODE_CONTROL_PARAMETER_Kt * sgn);  //Requested flow in percentage

	//Saturate requested flow % between -1 and 1  (100% full flow on both directions)
	if (sl_u > 1) {
		sl_u = 1;
	} else if (sl_u < -1) {
		sl_u = -1;
	}
	sl_uold[wheelCounter] = sl_u;
}
 */

/*
static sint32 deadBandCheckForceReferenceError(sint32 currentCylinderForce, sint32 forceReferenceCylinder, uint8 wheelCounter) {

	static volatile sint32 sigmaOld[5]              = {0};
	static volatile uint8  forceControllerWindowCase[5] = {0};

	sint32 errorSigma = currentCylinderForce - forceReferenceCylinder;
	float errorChangedSign = 0;

	switch (forceControllerWindowCase[wheelCounter]) {
	case 0:
		if (abs(errorSigma) > ((float)forceReferenceCylinder * 0.1)) {
			forceControllerWindowCase[wheelCounter] = 1;
		}
		errorSigma = 0;
		break;

	case 1:
		errorChangedSign = errorSigma - sigmaOld[wheelCounter];
		if (fabs(errorChangedSign) > fabs(errorSigma)) {
			forceControllerWindowCase[wheelCounter] = 0;
		}
		errorSigma = currentCylinderForce - forceReferenceCylinder;
		break;
	}
	sigmaOld[wheelCounter] = errorSigma;
	return errorSigma;
}
 */

/*
static void mapErestimatedFlowToCurrentOutputOnWheelWithNumber(uint8 wheelCounter) {
	float absoluteFlowInPercent = fabs(sl_u * 100.0);
	if (sl_u < 0.025 && sl_u > -0.025) {
		sl_current = 400;
	} else if (fabs(sl_u) > 0.97) {
		sl_current = 800 * (sl_u / fabs(sl_u)); //changed from 600
	} else {
		sl_current = (sl_u/fabs(sl_u)) * (VALVE_FLOW_FIT_PARAMETER_CP1*pow(absoluteFlowInPercent,4) + VALVE_FLOW_FIT_PARAMETER_CP2*pow(absoluteFlowInPercent,3) + VALVE_FLOW_FIT_PARAMETER_CP3*pow(absoluteFlowInPercent,2) + VALVE_FLOW_FIT_PARAMETER_CP4 * absoluteFlowInPercent + VALVE_FLOW_FIT_PARAMETER_CP5);
	}

	sl_debug_current = sl_current - (sl_current / labs(sl_current)) * 400;  //Valve current to output in CAN for debugging

	//Set reference to valves only if control is active generally and per cylinder
	if ((ACTIVE_FORCE_CONTROL == 1) & (Force_control_cylinders[wheelCounter] == 1)) {
		referenceSoleonidOutputCurrent_ma[wheelCounter] = -1 * sl_debug_current - To_ground_ref[wheelCounter];
		defaultSafety = 0;
	}
}
 */

void ADCUppdateReferenceOutputsForNewSensorValues(void) {

	//Zc damping individual chassis point skyhook damping implementation
	hightControllSkyhookForceAddition();

	//Chassis Height control Zc
	heightControllAddToAllocationMatrix();

	//Roll (Phi) control    P (Stiffness) I (integrator)  Skyhook damping (D)
	//rollPhiControllAddToAllocationMatrix();

	//Pitch (Theta) control   P (Stiffness) I (integrator) Skyhook damping (D)
	//pitchThetaControllAddToAllocationMatrix();

	//Decoupling of forces and assign to individual cylinders
	//Multiply 6x3 moore inverse times 3x1 Force_reference matrix
	//decoupleHightRollPitchAndConvertToCylinderForceForAllWheels();

	//ADD current Load force, calculated cylinder force needed and individual skyhook damping forces
	//calculateForceReferenceForAllWheels();

	uint8 wheelCounter = 0; //Loop counter
	for (wheelCounter = 0; wheelCounter < 6; wheelCounter++) {  //ALL
		//Calculate erestimated flow with sliding mode controll structure
		//calculateErestimatedFlowForWheelWithNumber(wheelCounter);

		//Calculate corresponding valve current for requested flow using fitted flow curve
		//mapErestimatedFlowToCurrentOutputOnWheelWithNumber(wheelCounter);

	}//end for


}


int ADCGetReferenceCurrentForWheel(int wheel) {
	return wheel;

}

int ADCSetThetaControlParametersPID(float P, float I, float D) {
	int p = P;
	p = I;
	p = D;

	return 1;

}

int ADCSetPhiControlParametersPID(float P, float I, float D) {
	int p = P;
	p = I;
	p = D;

	return 1;
}
