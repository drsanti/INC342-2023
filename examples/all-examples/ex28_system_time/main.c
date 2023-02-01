/************************************************************
 * Example 28. System Time Functions                        *
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
 * Demonstread how to use the system time functions
 *   1) Sys_GetTimeMilli()
 *   2) Sys_GetTimeMicro()
 *
 * This application prints system time values in milliseconds
 * and microseconds.
 ************************************************************/


/************************************************************
 * Include the system header.
 ************************************************************/
#include <ecc.h>


/**
 * Callback function of the software timer.
 */
void TMR_Callback( event_t *event ) {

    /**
     * Get system time in milliseconds.
     */
    double ms = Sys_GetTimeMilli();
    Uart1_Printf( "time ms: %.3f, ", mS );

    /**
     * Get system time in microseconds.
     */
    double us = Sys_GetTimeMicro();
    Uart1_Printf( "time us: %.3f\n", uS );

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
     * Create a software timer.
     */
    Timer_Create( 500, TMR_Callback );


    /**
     * Initializes the Uart1 (For debugging).
     */
    Uart1_Init( 115200, 64, 128 );
    Uart1_Printf( "\n\nSystem Time Functions.\n" );


    /**
     * Starts the system.
     */
    System_Start();

    return 0;
}
