/************************************************************
 * File:    BSP_Main.h                                      *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  17 February 2020                                *
 ************************************************************/

#ifndef __BSP_MAIN_H__

    #define	__BSP_MAIN_H__

    #include <BSP_Uart.h>
    #include <BSP_PswKey.h>
    #include <BSP_Beep.h>
    #include <BSP_Adc.h>
    #include <BSP_LedBlink.h>

    /*******************************************************
     * BSP_TickIsrExecutor (extern)
     * Increases the bsp_isr_ticks used in the BSP_Executor().
     * This function must be called by system ticker.
     *******************************************************/
    extern inline void BSP_TickIsrExecutor (void);

    /*******************************************************
     * BSP_Executor
     * Performs all executors.
     * This function must be called by the main infinite loop.
     *******************************************************/
    inline void BSP_Executor(void);

#endif // __BSP_MAIN_H__
