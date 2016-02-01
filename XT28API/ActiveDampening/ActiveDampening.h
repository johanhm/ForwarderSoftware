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
 *  \f{align}{
 *  \tag{1}
 *  u_z & = P_z e_z + I_z \int_0^t{e_z\delta t} + D_z\frac{d}{dt}e_z \\
 *	\tag{2}
 *  u_{\varphi} & = P_{\varphi} e_{\varphi} + I_{\varphi} \int_0^t{e_{\varphi}\delta t} + D_{\varphi}\frac{d}{dt}e_{\varphi} \\
 *	\tag{3}
 *  u_{\theta} & = P_{\theta} e_{\theta} + I_{\theta} \int_0^t{e_{\theta}\delta t} + D_z\frac{d}{dt}e_{\theta}
 *  \f}
 *	<BR>
 *
 *	After calculation the signals they are allocated to the wheels on the machine.
 *  The allocation of signals for the height PID controller is presented in a table below.
 *
 * <CENTER>
 * __Height allocation constants__
 * | Position  | Left | Right |
 * |-----------|------|-------|
 * | Front     | 0.16 | 0.16  |
 * | Middle    | 0.16 | 0.16  |
 * | Back      | 0.16 | 0.16  |
 * </CENTER>
 *
 *  What this means is that you calculate a signal from the height error and out you get a height signal output. To allocate it to all the
 *  wheels on the machine that output is scaled with an arbitrary number. In this case it derived from a pesudo matrix solution based on the
 *  equations of motions and geometry of the forwarder. Note that doing resaults in different constants for height controller. That becouse those constants
 *  are based on force.
 *
 *  The allocations constants for roll phi controller is seen in the table below.
 *
 * <CENTER>
 * __Angle__ \f$\varphi\f$ __allocation constants__
 * | Constants | Left |  Right |
 * |-----------|------| -------|
 * | Front     | 0.33 | -0.33  |
 * | Middle    | 0.33 | -0.33  |
 * | Back      | 0.33 | -0.33  |
 * </CENTER>
 *
 * This means that depending on a error in phi will result in that the wheels on the left side goes in one direction and on the right side goes opposite direction.
 * Finaly the allocation constants for theta
 *
 * <CENTER>
 * __Angle__ \f$\theta\f$ __allocation constants__
 * | Constants | Left | Right |
 * |-----------|------|-------|
 * | Front     | 0.12 | 0.12  |
 * | Middle    |-0.01 |-0.01  |
 * | Back      |-0.12 |-0.12  |
 * </CENTER>
 *
 * This controller will level and only level the machine. It does not take force in condidiration in anyway. From this the final output signal can be shown as
 *
 * <BR>
 *  \f{equation}{
 *  u_{out, i} = u_{z} \cdot K_{z, i} + u_{\varphi} \cdot K_{\varphi, i} + u_{\theta} \cdot K_{\theta, i}
 *  \tag{4}
 *  \f}
 * <BR>
 *
 *
 * Finaly lets summerize that the this controller can do
 *
 *<CENTER>
 * __PID Niv achivments__
 * | Active dampening Goals | PID leveling |
 * |:----------------------:|--------------|
 * | Leveling               | Yes          |
 * | Pressure distribution  | No           |
 * | Reduce vibraions       | debatable    |
 * </CENTER>
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
 * <CENTER>
 * __PID Force__
 * | Active dampening Goals | PID leveling |
 * |:----------------------:|--------------|
 * | Leveling               | No           |
 * | Pressure distribution  | Yes          |
 * | Reduce vibraions       | debatable    |
 *</CENTER>
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
 *  \f{equation}{
 *  u_i = C_{w} v_i + C_{c} v_{c} + C_{\theta} \dot\theta + C_{\varphi} \dot{\varphi}
 *  \tag{5}
 *  \f}
 *
 * So in pratrice this sort of controllers only purpose in life is to make the ride a bit smoother and reducing fast velocity changes,
 * dampening the vibrations. This sort of controller does not take leveling or group pressure into consideration in any way.
 *
 * This sort of controller will be it self achieve the following, given that it is possible to act fast egnouth on the velocity's changes:
 *
 * <CENTER>
 * __Skyhook control achivments__
 * | Active dampening Goals | PID leveling |
 * |:----------------------:|--------------|
 * | Leveling               | No           |
 * | Pressure distribution  | No           |
 * | Reduce vibraions       | Probably     |
 * </CENTER>
 *
 * ## Sliding mode
 *
 * Sliding mode 1st order controlelr is a non linjar type of controller that is used to slide on a surface. In this application the sliding surface is the
 * error of the force on the forwarder. So what it attempts to do is given a force reference is to drive this force error to zero.
 *
 * In sliding mode you determine a srurace that the controller should slide along. When the surfce is reached (simga -> 0) the equial controll will keep it there.
 * In this application when controlling the pos of the forwarder wheel the output u is going to be zero when sigma is sero thus there is no equial controll. This could
 * make the controller realy simel to implement. A great introduction page to sliding mode is found in in the case sigma -> 0 -> u -> 0 for t-> inf
 * <a href="http://www.diee.unica.it/~eusai/BOSIO/A%20QUICK%20INTRODUCTION%20TO%20SLIDING%20MODE%20CONTROL.pdf">Sliding mode intro</a>.
 *
 * A summery of sliding mode is
 *
 * \f{align}{
 * \sigma & = \dot{e} + K \cdot e \tag{10} \\
 * u & = K_{sm} \frac{\sigma}{abs{\sigma} + \epsilon} \tag{7}
 * \f}
 *
 * This approuch would drive the error to zero, with also having a continous signal. It can also easyely be turn into a
 * 2nd order slidng mode controller by using the super twisting algorithm
 *
 * \f{align}{
 * u & = - \lambda \sqrt{ |\sigma |} sgn(\sigma) + w \\
 * \dot{w} & = -W \cdot sgn(\sigma) \tag{7}
 * \f}
 *
 * where the parameters are determend as
 *
 * \f{align}{
 * \lambda & = \sqrt(U) \\
 * W & = 1.1 \cdot U \tag{7}
 * \f}
 *
 * This is a one parameter design and can be seen as sliding modes variant of PI control. The output signal is also continuous.
 *
 * ### Implemented sliding mode
 *
 * The implemented slidind mode is based on
 * <a href="https://www.kth.se/social/upload/507ff5cbf276547b13000002/Compendium_2012.pdf">KTH Non linear control</a> , lecture 9 slide 26.
 *
 *
 * The implementation math is described as follows. The sliding surface is defined as
 *
 * \f{align}{
 * \sigma & = e_{F} \tag{6} \\
 * S(\sigma) & = \frac{\sigma}{abs(\sigma) + K_s} \tag{7}
 * \f}
 *
 * As this is a first
 *
 * \f{equation}{
 * \mathcal{L} = \begin{cases}
 * 			A_A \cdot Q_{max} + \frac{A_B \cdot \sqrt{P_B} \cdot Q_{max}}{\Delta P} & if & u_{old} \geq 0 \\
 * 			A_B \cdot Q_{max} + \frac{A_A \cdot \sqrt{P_A} \cdot Q_{max}}{\Delta P} & if & u_{old} < 0
 * 		\end{cases}
 * 		\tag{8}
\f}
 *
 *gives the following control law
 *
 * \f{equation}{
 * u_{flow} = \frac{1}{\mathcal{L}} \left( \dot{x_w}(A_A^2 + A_B^2) + K_{sm} \cdot S(\sigma)  \right)
 * \tag{9}
 * \f}
 *
 * The aurthours of this control law is Frank and Bruno. For futher details on this implementation see their report at KTH.se.
 *
 *
 *
 *
 *
 *
 */



/*! \defgroup ADC Controllers
 *  \ingroup AD
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
