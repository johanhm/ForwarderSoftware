/*!
 * \page ADCONTROLLERS Controllers
 *
 * \brief This page explains the different controllers available.
 *
 *	The purpose of Active dampening is three things
 *
 *	+ Keep the machine leveled
 *	+ Even out the group pressure.
 *	+ Reduce vibrations
 *
 *	It doesent exist one signel control type of strucke that can achinve all thease goals at the same time.
 *	What is done insteed is to use different controller with difference purpose that achinve alteast one of the problems
 *	and then superpossision the signals togheter and actuate on the wheels.
 *
 *	There is a PID controller for achinving leveling, and there is a PID controller for achiving even group pressure. Adding thease signals
 *	togheter is a way to achive the goal of active dampening.
 *
 *  PID Controllers
 *  =========================
 *
 *  The PID controllers that are implemented exist for two different goals.
 *  There exist a controller that handels the leveling of the machine.
 *  There also exist an controller that atempt the wheel to follow a set force reference.
 *
 *  ## PID leveling
 *  The PID leveling controllers input are the following
 *
 *  - Error height
 *  - Error pitch angle theta
 *  - Error roll angle phi
 *
 *  Given thease error the controller then calculate a output with the standard formula for PID as
 *
 *	<BR>
 *  <CENTER>
 *  \f$ u_z = P_z e_z + I_z \int_0^t{e_z\delta t} + D_z\frac{d}{dt}e_z \f$
 *
 *  \f$ u_{\varphi} = P_{\varphi} e_{\varphi} + I_{\varphi} \int_0^t{e_{\varphi}\delta t} + D_{\varphi}\frac{d}{dt}e_{\varphi} \f$
 *
 *  \f$ u_{\theta} = P_{\theta} e_{\theta} + I_{\theta} \int_0^t{e_{\theta}\delta t} + D_z\frac{d}{dt}e_{\theta} \f$
 *	</CENTER>
 *	<BR>
 *
 *	After calculation the signals they are allocated to the wheels on the machine.
 *  The allocation of signals for the height PID controller is presented in a table below.
 *
 * | Constants | Left | Right |
 * |-----------|------|-------|
 * | Front     | 0.16 | 0.16  |
 * | Middle    | 0.16 | 0.16  |
 * | Back      | 0.16 | 0.16  |
 *
 *  What this means is that you calculate a signal from the height error and out you get a height signal output. To allocate it to all the
 *  wheels on the machine that output is scaled with an arbitrary number. In this case it derived from a pesudo matrix solution based on the
 *  equations of motions and geometry of the forwarder. Note that doing resaults in different constants for height controller. That becouse those constants
 *  are based on force.
 *
 *  The allocations constants for roll phi controller is seen in the table below.
 *
 * | Constants | Left |  Right |
 * |-----------|------| -------|
 * | Front     | 0.33 | -0.33  |
 * | Middle    | 0.33 | -0.33  |
 * | Back      | 0.33 | -0.33  |
 *
 * This means that depending on a error in phi will result in that the wheels on the left side goes in one direction and on the right side goes opposite direction.
 * Finaly the allocation constants for theta
 *
 * | Constants | Left | Right |
 * |-----------|------|-------|
 * | Front     | 0.12 | 0.12  |
 * | Middle    |-0.01 |-0.01  |
 * | Back      |-0.12 |-0.12  |
 *
 * This controller will level and only level the machine. It does not take force in condidiration in anyway.
 *
 * Finaly lets summerize that the this controller can do
 *
 * | Active dampening Goals | PID leveling |
 * |:----------------------:|--------------|
 * | Leveling               | Yes          |
 * | Pressure distribution  | No           |
 * | Reduce vibraions       | debatable    |
 *
 * An example of how to use this function follows
~~~~~~~~~~~~~{.c}
void PIDNivControl() {

	// Set parameters
	ADPIDSetHeightControlParametersPID(heightP, heightI, 0);
	ADPIDSetPhiControlParametersPID   (phiP,    phiI, 	 0);
	ADPIDSetThetaControlParametersPID (thetaP,  thetaI,  0);

	// Get signal and put in array
	float referenceCurrentArray[SUM_WHEELS] = {0};
	ADPIDGetPIDSignalsForHeightPhiAndThetaArray(referenceCurrentArray,  // Output array
			(heightReference - PAPOSGetAvrageHeightOfForwarder()), 		// Error in Z
			(phiReference    - IMUGetPhi()),							// Error in Phi
			(thetaReference  - IMUGetTheta())							// Error in Theta
	);

	// Set reference current and actuate
	PAASetReferenceArrayWithUnit(referenceCurrentArray, CURRENT_MA);
	PAAActuatePendelumArms();
}
~~~~~~~~~~~~~
 * This set of code will level the machine.
 * The API interface for PID leveling is found at \ref ADPID.
 *
 * ## PID force wheel
 *
 * There is an implemented controller for controlling a wheel with to follow a reference force. For this system finding a reference for wheel
 * is the hard problem. The \ref PAF module calculates a suggested force. So the use of this controller is easy, give it an error and you get a signal back.
 * This controller only purpose in life is to give you a signal that makes the wheels error force go to zero. it does not take leveling into account in any way.
 *
 * In summery this sort of controller given that its possibole to calculate a force reference for all wheels:
 *
 * | Active dampening Goals | PID leveling |
 * |:----------------------:|--------------|
 * | Leveling               | No           |
 * | Pressure distribution  | Yes          |
 * | Reduce vibraions       | debatable    |
 *
 *
 * ## Skyhook controller
 *
 * The skyhook controller can be seen as a P controller that cats on velocity changes. What it does is given an velocity on a part of the machine
 * calculates a proportional signal that will counteract the velocity change.
 *
 * This controller acts on the following parts on the machine
 *
 * + Induvidual wheels
 * + Avrage chassi velocity in height
 * + Rotation velocity in pitch and roll
 *
 * In math it looks like this, output for wheel an wheel
 *
 *	<BR>
 *  <CENTER>
 *  \f$ u_i = D_{w} v_i + D_{c} v_{c} + D_{\theta} \dot\theta + D_{\varphi} \dot{\varphi} \f$
 *	</CENTER>
 *	<BR>
 *
 * So in pratrice this sort of controllers only purpose in life is to make the ride a bit smoother and reducing fast velocity changes,
 * dampening the vibrations. This sort of controller does not take leveling or group pressure into consideration in any way.
 *
 * This sort of controller will be it self achive the following, given that it is porssibole to act fast egnouth on the velocirt changes:
 *
 * | Active dampening Goals | PID leveling |
 * |:----------------------:|--------------|
 * | Leveling               | No           |
 * | Pressure distribution  | No           |
 * | Reduce vibraions       | Probably     |
 *
 *
 * ## Sliding mode
 *
 * Sliding mode 1st order controlelr is a non linjar type of controller that is used to slide on a surface. In this application the sliding surface is the
 * error of the force on the forwarder. So what it attempts to do is given a force reference is to drive this force error to zero.
 *
 *
 *
 *
 *
 */



/*! \defgroup ADC Controllers
 * \ingroup AD
 *
 *  \brief This module calculate the reference current for Active dampening controller.
 *
 *  This module requiere that the sensor modules are setup and operational. You can use this module to get
 *  what reference current that should be actuated on all wheels in order to achine active dampening.
 *  Different methods exist for calculating a reference signal. This module lets you costumize the PID parameters
 *  of Pitch and Roll controller for the machine for example.
 *  @{
 */

#ifndef XT28API_ACTIVEDAMPENING_ACTIVEDAMPENING_H_
#define XT28API_ACTIVEDAMPENING_ACTIVEDAMPENING_H_

#include "ActiveDampeningPID.h"
#include "ActiveDampeningSkyhook.h"
#include "ActiveDampeningSlidingMode.h"

#endif /* XT28API_ACTIVEDAMPENING_ACTIVEDAMPENING_H_ */
/** @}*/
