/** \defgroup XT28HWC Machine Constants
 * \brief The constants used by the XT28 API are declared here
 *
 *  @{
 */

#ifndef XT28API_XT28HARDWARECONSTANTS_H_
#define XT28API_XT28HARDWARECONSTANTS_H_


/** \name  Defines for pendelurm outputs */
#define OUT_PENDELURM_FRONT_RIGHT_A		OUT_1_POH_CL
#define OUT_PENDELURM_FRONT_RIGHT_B		OUT_2_POH_CL
#define OUT_PENDELURM_FRONT_LEFT_A		OUT_3_POH_CL
#define OUT_PENDELURM_FRONT_LEFT_B		OUT_4_POH_CL
#define OUT_PENDELURM_MID_RIGHT_A		OUT_5_POH_CL
#define OUT_PENDELURM_MID_RIGHT_B		OUT_6_POH_CL
#define OUT_PENDELURM_MID_LEFT_A		OUT_7_POH_CL
#define OUT_PENDELURM_MID_LEFT_B		OUT_8_POH_CL
#define OUT_PENDELURM_REAR_RIGHT_A		OUT_9_POH_CL
#define OUT_PENDELURM_REAR_RIGHT_B		OUT_10_POH_CL
#define OUT_PENDELURM_REAR_LEFT_A		OUT_11_POH_CL
#define OUT_PENDELURM_REAR_LEFT_B		OUT_12_POH_CL

/** \name Defines for pos of sensordata and current actuate. */
#define FR	 		0
#define FL	 		1
#define MR	 		2
#define ML 			3
#define BR 			4
#define BL			5
#define SUM_WHEELS	6
 /** @}*/

/** \name Hardware Constants */
#define CYLINDER_PUSH_AREA_SIDE_A1_m2 0.00785 // Cylinder push area (m^2) A side
#define CYLINDER_PUSH_AREA_SIDE_B2_m2 0.00589 // Cylinder pull area (m^2) B side
 /** @}*/

/** \name Forwarder Gemoetry */
#define  LENGTH_OF_FORWARDER_m          6.05;
#define  LENGTH_TO_MID_OFF_FORWARDER_m  3.70;
#define  WIDTH_OF_FORWARDER_m           2.35;
 /** @}*/

#endif /* XT28API_XT28HARDWARECONSTANTS_H_ */
 /** @}*/
