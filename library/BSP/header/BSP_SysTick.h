/************************************************************
 * File:    BSP_SysTick.h (used for all examples)           *
 * Description:                                             *
 *          Demonstrates how to use the RTOS, BSP and RTL.  *
 *          (Please see closely in the app.h and config.cfg)*
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 ************************************************************
 * Update:  23 February 2020 (Initial)                      *
 * Update:  01 March 2020 (Update)                          *
 ************************************************************/

#ifndef __BSP_SYS_TICK__H__
    #define __BSP_SYS_TICK__H__

    #include <BSP_Config.h>

    /**
     * System clock structure.
     */
    typedef struct {
        uint8_t     hh; // Hours
        uint8_t     mm; // Minutes
        uint8_t     ss; // Seconds
        uint16_t    ms; // Milliseconds
    }clock_t;


    /*
     * Sys_Start
     * Starts the system ticker, the Timer1.
     */
    void Sys_Start(void);

    /*
     * Sys_Stop
     * Stop the system ticker, the Timer1.
     */
    void Sys_Stop(void);


    /**
     * Sys_GetTicks
     * Returns the system ticks.
     */
    uint32_t Sys_GetTicks( void );


    /**
     * Sys_GetTimeMilli
     * Returns the system time in milliseconds.
     */
    double Sys_GetTimeMilli( void );


    /**
     * Sys_GetTimeMicro
     * Returns the system time in microseconds.
     */
    double Sys_GetTimeMicro( void );


    /**
     * Sys_GetClock
     * Returns the system _clock object.
     */
    clock_t Sys_GetClock( void );


    /**
     * Sys_SetClock
     * Sets the system _clock by the given _clock object.
     * Parameter:
     *  - clock: Clock object.
     */
    void Sys_SetClock(clock_t * clock );


    /*
     * Sys_SetTickCallback
     * Adds a callback function for the system tick.
     */
    void Sys_SetTickCallback(callback_t callback);


    /*
     * Sys_TickInit
     * Initializes the system timer, the Timer1.
     */
    void Sys_TickInit(void);


    /*
     * Sys_IsrPerformTick
     * Increases system tick and performs callback function.
     */
    extern inline void Sys_IsrPerformTick( void );


#endif // __BSP_SYS_TICK__H__
