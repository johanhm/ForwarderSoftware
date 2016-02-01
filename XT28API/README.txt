/*! \mainpage XT28 Forwarder API Introduction
 
  Welcome to the API documentation for the XT28 Forwarder API. This API contains the functions related to the
 _active dampening_ off the machine. All sensors and cylinders related to active dampening is connected to a  Rexroth BODAS 28-30 controller. As a consequence this API used the 
 functionality provided by BODAS C-API to implement its futures.

\image html xt28Bild.jpeg "XT28 Extractor Forwarder" 
 
 ### So what is active Dampening? ###
 To minimize the damage to the soil while driving in the forest and making the driving more confterbole the 
 XT28 Forwarder wheels is equioped with pendelum arms and hydralic cylinders.
 With the hydralic cylinders the wheels can move upp and down, wich means that its 
 possibole to keep the machine leveld and the pressure between the wheels distribiuted. This
 amazing thecnolegy enables the drivers to drive up to twicve as fast while still beeing more confterbole while driving
 then you are today. This is the future of the forest industri.
 
 ### How to achive Active dampening? ###
 
 The Api struckture is seen in a figure below
   
\image html xt28API.png "XT28 api Structure and dependencys" 

The api contains the following moduels and sub moduels

 - \ref ADC
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


## Supportin functionalitys #######

   Part of the API is also the support, with the dependencys seen in the figure below
   
   \image html support28api.png "Supporting functinalitys"

The \ref XT28CAN module is included by the Sensors and Actuate in order to be able to send CAN messages stuch as sensor values and 
reference current / actual current.

The \ref ADCFG module contains several pre defined controll control structures of the machine.

### Guides and exampels #######
 
 For exampels on different controller configurations see
 - \ref ADCONFIG
 - \ref ADCONTROLLERS
 - \ref EXCIPADEX
 
 */
