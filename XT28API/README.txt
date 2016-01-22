/*! \mainpage XT28 Forwarder API Introduction
 
 Welcome to the API documentation for the XT28 Forwarder API.
 This API uses the bodas API to implement its functionality.
The Api struckture is seen in a figure below
   
   \image html xt28API.png "XT28 api Structure and dependencys" 

The api contagins the following moduels and sub moduels

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
