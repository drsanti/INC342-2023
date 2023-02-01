/************************************************************
 * File:    BSP_Mcu.h                                       *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  16 February 2020                                *
 ************************************************************/


#ifndef __BSP_MCU_H__

    #define	__BSP_MCU_H__

	#include <BSP_Config.h>

	/*******************************************************
     * Performs critical section
     *******************************************************/

	#define PERFORM_CRITICAL_SECTION(action) {	\
        int old_ipl;                            \
        SET_AND_SAVE_CPU_IPL(old_ipl, 7);       \
        action;                                 \
        RESTORE_CPU_IPL(old_ipl);               \
    }

	/*******************************************************
     * Disable and Enable ISE of Timer1
     *******************************************************/
	#define TIMER1_ISR_DISABLE()    IEC0bits.T1IE=0
	#define TIMER1_ISR_ENABLE()     IEC0bits.T1IE=1

    #define Mcu_Restart()           {__delay_ms(1000); __asm__ volatile ("reset");}

    /*******************************************************
     * Mcu_Init
     * Initializes CPU clock and IOs. It calls Mcu_ClockInit() and Mcu_IoInit()
     *******************************************************/
    void Mcu_Init(void);

    /*******************************************************
     * Mcu_ClockInit
     * Initializes CPU clock.
     *******************************************************/
    void Mcu_ClockInit(void);

    /*******************************************************
     * Mcu_IoInit
     * Initializes IOs.
     *******************************************************/
    void Mcu_IoInit(void);

    /*******************************************************
     * Mcu_UnlockRemap
     * Unlocks IOs remapping.
     *******************************************************/
    void Mcu_UnlockRemap(void);

    /*******************************************************
     * Mcu_LockRemap
     * Locks IOs remapping.
     *******************************************************/
    void Mcu_LockRemap(void);


#endif // __BSP_MCU_H__
