/************************************************************
 * Example 30. Asynchronous vs. Synchronous Processing Time *
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
 * This application demonstrates how to measure the processing
 * time of desired functions.
 *
 * The processing time comparison of the Synchronous and
 * Asynchronous functions are provided.
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
     * Variables used to store time values.
     */
    double ts, te, ov;

    /**
     * Overhead of the Sys_GetTimeMicro() function.
     */
    ts = Sys_GetTimeMicro();
    te = Sys_GetTimeMicro();
    ov = te - ts;
    Uart1_PrintfAsync( "overhead: %.3f uS\n", ov );


    /**
     * Data to be sent to the Uart1.
     */
    const char * data = "0123456789ABCDEF\r\n";


    /**************************************
     * Uart1_Write vs. Uart1_WriteAsync
     **************************************/

    /**
     * Synchronous, Uart1_Write()
     */
    ts = Sys_GetTimeMicro();
    Uart1_Write( data );
    te = Sys_GetTimeMicro();
    double t_sync = te-ts-ov;


    /**
     * Asynchronous, Uart1_WriteAsync()
     */
    ts = Sys_GetTimeMicro();
    Uart1_WriteAsync( data );
    te = Sys_GetTimeMicro();
    double t_async = te-ts-ov;

    /**
     * Print the results.
     */
    Uart1_PrintfAsync( "\n#sync  time: %.3f uS\n", t_sync );
    Uart1_PrintfAsync( "#async time:  %.3f uS\n", t_async );



    /**************************************
     * Uart1_Printf vs. Uart1_PrintfAsync
     **************************************/

     /**
     * Synchronous, Uart1_Printf()
     */
    ts = Sys_GetTimeMicro();
    Uart1_Printf( "%s", data );
    te = Sys_GetTimeMicro();
    t_sync = te-ts-ov;


    /**
     * Asynchronous, Uart1_PrintfAsync()
     */
    ts = Sys_GetTimeMicro();
    Uart1_PrintfAsync( "%s", data );
    te = Sys_GetTimeMicro();
    t_async = te-ts-ov;

    /**
     * Print the results.
     */
    Uart1_PrintfAsync( "\n*sync  time: %.3f uS\n", t_sync );
    Uart1_PrintfAsync( "*async time:  %.3f uS\n", t_async );

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
    Uart1_Init( 115200, 64, 256 );
    Uart1_Printf( "\n\nProcessing time measurement.\r\n");


    /**
     * Starts the system.
     */
    System_Start();

    return 0;
}
