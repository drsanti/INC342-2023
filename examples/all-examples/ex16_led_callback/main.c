/************************************************************
 * Example 16. LED State Changed Callback Function          *
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
 * Callback function of the PSW0.
 */
void PSW0_KeyDownCallback( event_t *event ) {

    Uart1_Write( "Flash LED0\r\n" );
    Led_Flash( LED_ID_0, 1000 );
}

/**
 * Callback function of the LED0.
 */
void LED0_CompletedCallback( event_t *event )  {

    Uart1_Printf( "LED0 state changed to %s\r\n", Led0_Get() ? "ON" : "OFF" );
}

/************************************************************
 * Main function
 ************************************************************/
int main(void) {

    /*
     * Intianlizes the system.
     */
    System_Init();

    /**
     * Initializes the Uart1. Used to check the results.
     * Run the command line with -monitor option to see the results.
     * e.g., ecc-pic24-cli -build -flash -monitor
     */
    Uart1_Init( 115200, 32, 64 );


    /**
     * Set the KeyDown callback function to the PSW0.
     */
    Psw_SetKeyDownCallback( PSW_ID_0, PSW0_KeyDownCallback );


    /**
     * Set the Changed (State Changed) callback function to the LED0.
     */
    Led_SetChangedCallback( LED_ID_0, LED0_CompletedCallback );


    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
