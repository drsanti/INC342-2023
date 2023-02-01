/************************************************************
 * Example 33. ESP8266 Callback and Event                   *
 ************************************************************
 * File:    main.c                                          *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 ************************************************************
 * Update:  04 March 2020 (Initial version)                 *
 ************************************************************/

/************************************************************
 * Include the system header.
 ************************************************************/
#include <ecc.h>

/************************************************************
 * Application Description
 *
 * Key Down:
 *   PSW0 - AT+GMR      Check Version and other information.
 *   PSW1 - AT+CWJAP?   Check the current connected AP.
 *   PSW2 - AT+CIFSR    Check IP and MAC addresses of AP and STA.
 *   PSW3 - AT+CWLAP    Check all the available WiFi networks.
 ************************************************************/

/**
 * Commands
 */
const char *COMDS[] = { "AT+GMR", "AT+CWJAP?", "AT+CIFSR", "AT+CWLAP" };

/**
 * Callback function of switches.
 */
void PSWx_Callback( event_t *event ) {

    switch_event_t *evt = (switch_event_t *)event;

    Uart1_PrintfAsync("\nSending command [%s]\n\n", COMDS[evt->id]);

    /**
     * Sends the command specified by the id of pressed switch.
     * - 1st parameter is the command string.
     * - 2nd parameter is the timeout value in milliseconds.
     */
    // Esp_AtSendCommand( COMDS[evt->id], 5000 );
    // Esp_AtEnableCapture ( true );

    /**
     * The two functions above can be replaced by the Esp_AtSendCommandCapture().
     * - 1st parameter is the command string.
     * - 2nd parameter is the timeout value in milliseconds.
     * - 3th parameter is the capture enabled flag.
     */
    Esp_AtSendCommandCapture( COMDS[evt->id], AT_DEFAULT_TIMEOUT, AT_CAPTURE_ENABLED );

    Beep_Play( 50, (1000 + (500 * evt->id)) );
}


/**
 * Callback function of the command execution.
 * This function will be called when the command is executed.
 */
void Cmd_Callback( event_t *event ) {

    /**
     * Get the callback event.
     */
    esp_event_t *evt = (esp_event_t *)event;

    /**
     * Check and print the returned response result, and response line(s).
     */
    if( evt->rcode == AT_RESP_OK ) {

        Uart1_PrintfAsync( "\nCommand [%s] executed.\n", evt->command );
        Led_Flash( LED_ID_0, 50 );
        Beep_Play( 50, 4000 );

        /**
         * Print all response lines (data).
         * If the at-capture is enabled, the response->items is greater than 0.
         */
        int16_t i;
        for( i =0; i<evt->response->items; i++ ) {
            Uart1_PrintfAsync( "cap[%d]: %s\r\n", i, evt->response->lines[i] );
        }
    }
    else {
        Uart1_PrintfAsync( "At Code: %d %s\r\n", evt->rcode, evt->rstr );
    }
}

/************************************************************
 * Main Function
 ************************************************************/
int main(void) {

    /**
     * Initializes the system.
     */
    System_Init();

    /**
     * Initializes the Uart1 (For debugging).
     */
    Uart1_Init( 115200, 64, 1024 );
    Uart1_WriteAsync("\nPress a switch and check the result.\n");

    /**
     * Initializes the Uart2 (For ESP8266 moduel).
     */
    Uart2_Init( 115200, 256, 256 );

    /**
     * Set callback function to all switches.
     */
    int i;
    for( i = PSW_ID_0; i <= PSW_ID_3; i++ ) {
        Psw_SetKeyDownCallback( i, PSWx_Callback );
    }

    /**
     * Initializes the ESP without reseting (false).
     */
    Esp_Init( false );

    /**
     * Set callback function to the command executor.
     */
    Esp_SetCmdCallback( Cmd_Callback );

    /**
     * Starts the system.
     */
    System_Start();

    return 0;
}
