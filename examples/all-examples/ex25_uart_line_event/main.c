/************************************************************
 * Example 25. Uart Line Received Callback and Event        *
 ************************************************************
 * File:    main.c                                          *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 ************************************************************
 * Update:  01 March 2020 (Initial version)                 *
 ************************************************************/


/************************************************************
 * Include the system header.
 ************************************************************/
#include <ecc.h>

/**
 * Callback function of Uart1 line received.
 * This function called when a line is received or no space in the buffer.
 */
void RxLine_Callback( void *event ) {

    uart_event_t *evt = (uart_event_t *)event;
    const char *line = evt->line; // The line contains "\r\n" or "\n" at the end.

    Led_Flash( LED_ID_0, 1 );
    Beep( 100 );
    Uart1_Printf( "received a line (%d bytes): %s\r\n", strlen(line), line );

}


/************************************************************
 * Main function
 ************************************************************/
int main( void ) {

    /*
     * Intianlizes the system.
     */
    System_Init();

    /**
     * Initializes the Uart1. Used to check the results.
     * Run the command line with -monitor option to see the results.
     * e.g., ecc-pic24-cli -build -flash -monitor
     */
    Uart1_Init( 115200, 64, 128 );


    /**
     * Set the RxLineCallback (line received) function to the Uart1.
     * This runction requires the buffer size passing to it.
     * It will allocates memory for storing the received line.
     * If the received line is longer than the buffer size-2,
     * the callback function is also called.
     */
    Uart1_SetRxLineCallback( RxLine_Callback, 64 );

    /**
     * We can resize the buffer by calling the function with the desired buffer size.
     *  - Uart1_SetRxLineCallback(RxLine_Callback, SIZE)
     * We can clear (un register) the callback by calling the function with the NULL parameter.
     *  - Uart1_SetRxLineCallback(NULL, DONT_CARE)
     */


    /**
     * Note:
     * The Uart2 can be used in the same way.
     */

    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
