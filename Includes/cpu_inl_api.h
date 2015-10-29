/***************************************************************************************************
*                                                                                                  *
*  FILENAME:                                                                                      */
/**\file        cpu_inl_api.h
*
*  \brief       cpu inline definitions; based on cpu_inl.h and cpu_pub.h.
*
*/
/***************************************************************************************************
* (c) Copyright by BOSCH REXROTH AG, all rights reserved                                           *
****************************************************************************************************
*
* PROJECT:                   API RC30 platform
*
* FILE VERSION INFORMATION:  $Revision: 5235 $
*                            $Date: 2013-01-23 12:21:12 +0100 (Mi, 23 Jan 2013) $
*                            $Author: gtg2si $
*
* REVISION HISTORY:
*
***************************************************************************************************/

#ifndef _CPU_INL_API_H
#define _CPU_INL_API_H

// cpu_pub.h
#define CPU_INLINE_API              static __inline__


#define CPU_INLINE_ALWAYS_API       __attribute__ (( always_inline ))
#define CPU_INLINE_PROTOTYPE_API    CPU_INLINE_API  CPU_INLINE_ALWAYS_API

// cpu_inl.h
CPU_INLINE_PROTOTYPE_API uint32 Cpu_GetCPUPrioApi(void);
CPU_INLINE_PROTOTYPE_API void   Cpu_SetCPUPrioApi(uint32);


CPU_INLINE_API uint32 Cpu_GetCPUPrioApi(void)
{
    uint32 xICR_u32;



    asm volatile ("mfcr %0, $icr":"=d" (xICR_u32) : );


    return (xICR_u32 & 0x000000FFUL);
}



CPU_INLINE_API void Cpu_SetCPUPrioApi(uint32 numPrio_u32)
{
    uint32 xTemp_u32;



    asm volatile ("mfcr %0, $icr":"=d" (xTemp_u32) : );



    xTemp_u32 = (xTemp_u32 & 0xFFFFFF00UL) | (numPrio_u32 & 0x000000FFUL);



    asm volatile ("mtcr $icr, %0": :"d" (xTemp_u32):"memory");
    asm volatile ("isync");
}


#endif
