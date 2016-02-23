/*! \mainpage XT28 Forwarder API Introduction
 
  Welcome to the API documentation for the XT28 Forwarder API. This API contains the functions related to the
 _active dampening_ off the machine. All sensors and cylinders related to active dampening is connected to a  Rexroth BODAS 28-30 controller. As a consequence this API used the 
 functionality provided by BODAS C-API to implement its futures.

\image html xt28Bild.jpeg "XT28 Extractor Forwarder" 
 
 ### So what is active Dampening? ###
 To minimize the damage to the soil while driving in the forest and making the driving more comfortable the 
 XT28 Forwarder wheels is equipped with pendulum arms and hydraulic cylinders.
 With the hydraulic cylinders the wheels can move up and down, which means that its 
 possible to keep the machine leveled and the pressure between the wheels distributed. This
 amazing technology enables the drivers to drive up to twice as fast while still being more comfortable while driving
 then you are today. This is the future of the forest industry.
 
 ### How to achieve Active dampening? ###
 
 The API structure is seen in a figure below
   
\image html xt28API.png "XT28 API Structure and dependency" 

The API contains the following modules and sub modules

 - \ref AD
	+ \ref ADPID
	+ \ref ADSH
	+ \ref ADSM
 - \ref EXP
 - \ref SENSORS
   + \ref IMU
   + \ref PAPOS
   + \ref PAPR
   + \ref PAF
 - \ref ACTUATE
	+ \ref PAA

 Related hardware constants for the XT28 is defined in the of

 - \ref XT28HWC

 Where most of the API make use of hardware constants to function.


## Supporting functionality #######

   Part of the API is also the support, with the dependences seen in the figure below
   
   \image html support28api.png "Supporting functionality's"

The \ref XT28CAN module is included by the Sensors and Actuate in order to be able to send CAN messages such as sensor values and 
reference current / actual current.

The \ref ADCFG module contains several pre-defined control control structures of the machine.

### Guides and examples #######
 
 For examples on different controller configurations see
 - \ref ADCONFIG
 - \ref ADCONTROLLERS
 - \ref EXCIPADEX
 
 */
