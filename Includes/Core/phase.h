

#ifndef _PHASE_H
#define _PHASE_H







#define NUM_CHANNEL_FREQ_ACQ		10

#define EXT_FREQ_BUF_DFI01_D		0
#define EXT_FREQ_BUF_DFI02_D		1
#define EXT_FREQ_BUF_DFI03_D		2
#define EXT_FREQ_BUF_DFI04_D		3
#define EXT_FREQ_BUF_DFI05_D		4
#define EXT_FREQ_BUF_DFI06_D		5
#define EXT_FREQ_BUF_DFI07_D		6
#define EXT_FREQ_BUF_DFI08_D		7
#define EXT_FREQ_BUF_DFI09_D		8
#define EXT_FREQ_BUF_DFI10_D		9












	
	




typedef struct
{
    uint32          tPrimSig_u32;        
    uint32          tSecSig_u32;         
    uint32          tShift_u32;          
    sint32          couPulse_s32;        
    bool            stSecSig_b;       	 
    									 
	uint32			tPeriodePrimSig_u32; 
    uint32			tPeriodeSecSig_u32;  
    uint8			stErrorPrimSig_u8;	 
    uint8			stErrorSecSig_u8;    				
}   phase_ts;


extern uint32 P_DFI_01_tim_u32;
extern uint32 P_DFI_02_tim_u32;
extern uint32 P_DFI_03_tim_u32;
extern uint32 P_DFI_04_tim_u32;
extern uint32 P_DFI_05_tim_u32;
extern uint32 P_DFI_06_tim_u32;
extern uint32 P_DFI_07_tim_u32;
extern uint32 P_DFI_08_tim_u32;
extern uint32 P_DFI_09_tim_u32;
extern uint32 P_DFI_10_tim_u32;




extern void Phase_DFI01_DFI02 (phase_ts* Phase_Data_ps);
extern void Phase_DFI03_DFI04 (phase_ts* Phase_Data_ps);
extern void Phase_DFI07_DFI08 (phase_ts* Phase_Data_ps);
extern void Phase_DFI09_DFI10 (phase_ts* Phase_Data_ps);

extern void Phase_DFI01_DFI02_Reset (void);
extern void Phase_DFI03_DFI04_Reset (void);
extern void Phase_DFI07_DFI08_Reset (void);
extern void Phase_DFI09_DFI10_Reset (void);

extern void Phase_PwmIn_Proc_Ini(void);

extern void Phase_PwmIn_Disable_PhaseMeasurement_DFI01_DFI02(void);
extern void Phase_PwmIn_Disable_PhaseMeasurement_DFI03_DFI04(void);
extern void Phase_PwmIn_Disable_PhaseMeasurement_DFI07_DFI08(void);
extern void Phase_PwmIn_Disable_PhaseMeasurement_DFI09_DFI10(void);

extern void Phase_PwmIn_Enable_PhaseMeasurement_DFI01_DFI02(void);
extern void Phase_PwmIn_Enable_PhaseMeasurement_DFI03_DFI04(void);
extern void Phase_PwmIn_Enable_PhaseMeasurement_DFI07_DFI08(void);
extern void Phase_PwmIn_Enable_PhaseMeasurement_DFI09_DFI10(void);

extern void Phase_PwmIn_Intr_Enable(void);
extern void Phase_PwmIn_Intr_Disable(void);

extern void Phase_DFI02_IsrProc(void);
extern void Phase_DFI04_IsrProc(void);
extern void Phase_DFI08_IsrProc(void);
extern void Phase_DFI10_IsrProc(void);



typedef struct
{
	uint32  tiPeriod_u32;
	uint32  tiPulse_u32;
} 	in_freqAcq_ts;

typedef struct
{
	in_freqAcq_ts   *start_pas;
	in_freqAcq_ts   *write_pas;
	uint8  length_u8;
	bool  full_l;
	bool  phase_l;
	uint16  counter_u16;
} 	in_freqAcqBufInfo_ts;

extern void Freq_PwmIn_Proc_Ini(void);

extern void Freq_PwmIn_Intr_Enable(void);
extern void Freq_PwmIn_Intr_Disable(void);

extern void Freq_PwmIn_Disable_FreqMeasurement_DFI01(void);
extern void Freq_PwmIn_Disable_FreqMeasurement_DFI02(void);
extern void Freq_PwmIn_Disable_FreqMeasurement_DFI03(void);
extern void Freq_PwmIn_Disable_FreqMeasurement_DFI04(void);
extern void Freq_PwmIn_Disable_FreqMeasurement_DFI05(void);
extern void Freq_PwmIn_Disable_FreqMeasurement_DFI06(void);
extern void Freq_PwmIn_Disable_FreqMeasurement_DFI07(void);
extern void Freq_PwmIn_Disable_FreqMeasurement_DFI08(void);
extern void Freq_PwmIn_Disable_FreqMeasurement_DFI09(void);
extern void Freq_PwmIn_Disable_FreqMeasurement_DFI10(void);

extern void Freq_PwmIn_Enable_FreqMeasurement_DFI01(void);
extern void Freq_PwmIn_Enable_FreqMeasurement_DFI02(void);
extern void Freq_PwmIn_Enable_FreqMeasurement_DFI03(void);
extern void Freq_PwmIn_Enable_FreqMeasurement_DFI04(void);
extern void Freq_PwmIn_Enable_FreqMeasurement_DFI05(void);
extern void Freq_PwmIn_Enable_FreqMeasurement_DFI06(void);
extern void Freq_PwmIn_Enable_FreqMeasurement_DFI07(void);
extern void Freq_PwmIn_Enable_FreqMeasurement_DFI08(void);
extern void Freq_PwmIn_Enable_FreqMeasurement_DFI09(void);
extern void Freq_PwmIn_Enable_FreqMeasurement_DFI10(void);

extern void Freq_DFI01_IsrProc(void);
extern void Freq_DFI02_IsrProc(void);
extern void Freq_DFI03_IsrProc(void);
extern void Freq_DFI04_IsrProc(void);
extern void Freq_DFI05_IsrProc(void);
extern void Freq_DFI06_IsrProc(void);
extern void Freq_DFI07_IsrProc(void);
extern void Freq_DFI08_IsrProc(void);
extern void Freq_DFI09_IsrProc(void);
extern void Freq_DFI10_IsrProc(void);

extern in_freqAcqBufInfo_ts in_freqAcqBufInfo_as[];


#endif
