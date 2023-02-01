/************************************************************
 * Example 29. System Time Functions                        *
 ************************************************************
 * File:    main.c                                          *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 ************************************************************
 * Update:  05 March 2020 (Initial version)                 *
 ************************************************************/


/************************************************************
 * Application Description
 * Demonstread how to use the system clock functions
 *   1) Sys_GetClock()
 *   2) Sys_SetClock()
 *
 * TThis application responds to two switches, the PSW0 and PSW1.
 *  - When PSW0 is pressed, it gets and ptints the system clock.
 *  - When PSW1 is pressed, it sets the system clock to the specified time.
 ************************************************************/


/************************************************************
 * Include the system header.
 ************************************************************/
#include <ecc.h>


/**
 * Callback function of the software timer.
 */
void GetClock_Callback( event_t *event ) {
    /**
     * Get system time in milliseconds.
     */
    clock_t clock = Sys_GetClock();
    Uart1_Printf( "time %.2d:%.2d:%.2d %.3d\r\n", clock.hh, clock.mm, clock.ss, clock.ms );
}


/**
 * Callback function of the software timer.
 */
void SetClock_Callback( event_t *event ) {

    /**
     * Desired time (clock)
     */
    clock_t clock;
    clock.hh = 14;  // Hours
    clock.mm = 30;  // Minutes
    clock.ss = 55;  // Seconds
    clock.ms = 00;  // Milliseconds

    /**
     * Update the time (clock)
     */
    Sys_SetClock( &clock );
}


/************************************************************
 * Main Function
 ************************************************************/
int main( void ) {

    /**
     * Initializes the system.
     */
    System_Init();


    /**
     * Add callbacks to the switches.
     */
    Psw_SetKeyDownCallback( PSW_ID_0, GetClock_Callback );
    Psw_SetKeyDownCallback( PSW_ID_1, SetClock_Callback );


    /**
     * Initializes the Uart1 (For debugging).
     */
    Uart1_Init( 115200, 64, 128 );
    Uart1_Printf( "\n\nPSW0: Get, PSW1: Set\n");


    /**
     * Starts the system.
     */
    System_Start();

    return 0;
}
