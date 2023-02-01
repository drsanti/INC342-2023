/************************************************************
 * File:    RT_Main.h                                       *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  17 February 2020                                *
 ************************************************************/

#ifndef __RTL_MAIN_H__

    #define __RTL_MAIN_H__

    #include <RTL_Config.h>



    /*******************************************************
     * RTL_TickIsrExecutor (extern)
     * Increases the rtl_isr_ticks used in the RTL_Executor().
     * This function must be called by system ticker.
     *******************************************************/
    extern inline void RTL_TickIsrExecutor(void);

    /*******************************************************
     * RTL_Executor
     * Performs all executors.
     * This function must be called by the main infinite loop.
     *******************************************************/
    inline void RTL_Executor(void);

#endif // __RTL_MAIN_H__
