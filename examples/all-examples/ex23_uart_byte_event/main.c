/************************************************************
 * Example 23. Uart Byte Received Callback and Event        *
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
 * Callback function of Uart1 byte received.
 * This function called by CoRutine or BSP executor.
 */
void Rx_Callback( void *event ) {
    Led_Flash( LED_ID_0, 1 );

    uart_event_t *evt = (uart_event_t *)event;  // Get the event.
    char c = evt->byte;                         // Get the received character.
    if(c == '\r') {
        Uart1_Printf( "received: [CR] from Uart%d\r\n", evt->id );
    }
    else if (c == '\n') {
        Uart1_Printf( "received: [LF] from Uart%d\r\n", evt->id );
        Beep(100);
    }
    else {
        Uart1_Printf( "received:  %c   from Uart%d\r\n", c, evt->id );
    }
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
     * Set the RxCallback (byte received) function to the Uart1.
     */
    Uart1_SetRxCallback( Rx_Callback );

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
