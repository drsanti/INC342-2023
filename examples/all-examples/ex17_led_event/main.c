/************************************************************
 * Example 17. LED State Changed Callback & Events          *
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
 * Callback function of the PSWs.
 */
void PSWs_KeyDownCallback( event_t *event ) {

    switch_event_t *evt = (switch_event_t *)event;

    Uart1_Printf( "Flash LED%d\r\n", evt->id );
    Led_Flash( evt->id, 1000 );
}


/**
 * Callback function of the LEDs.
 */
void LEDs_CompletedCallback( event_t *event )  {

    led_event_t *evt = (led_event_t *)event;

    Uart1_Printf( "LED%d state changed to %s\r\n", evt->id, Led_Get(evt->id) ? "ON" : "OFF" );
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
    Uart1_Init( 115200, 32, 64 );


    uint16_t i;

    /**
     * Set the KeyDown callback function to all switches.
     */

    for( i = PSW_ID_0; i <= PSW_ID_3; i++ ) {
        Psw_SetKeyDownCallback( i, PSWs_KeyDownCallback );
    }

    /**
     * Set the Changed (State Changed) callback function to all LEDs.
     */
    for( i = LED_ID_0; i <= LED_ID_3; i++ ) {
        Led_SetChangedCallback( i, LEDs_CompletedCallback );
    }

    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
