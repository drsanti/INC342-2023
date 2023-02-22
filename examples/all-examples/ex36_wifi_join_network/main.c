/************************************************************
 * Example 36. ESP8266 Connect to AP (WiFi Network)         *
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
 * Setup
 *
 * 1) Change the SSID and PASS to match your AP or Hotpot
 * 2) Run the application, and wait 3-10 seconds.
 * 3) Press PSW1 to check the connected SSID.
 * 4) Press PSW2 to check IP address.
 ************************************************************/


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
 * SSID and PASS of the Access Point
 */
const char * SSID = SYSTEM_DEFAULT_NETWORK_SSID;    // Service Set Identifier.
const char * PASS = SYSTEM_DEFAULT_NETWORK_PASS;    // Password of the network.


/**
 * Commands
 */
const char *COMDS[] = { "AT+GMR", "AT+CWJAP?", "AT+CIFSR", "AT+CWLAP" };


/**
 * Callback function of switches.
 */
void PSWx_Callback( event_t *event ) {

    switch_event_t *evt = ( switch_event_t * )event;

    Uart1_PrintfAsync( "\nSending command [%s]\n\n", COMDS[evt->id] );

    /**
     * Sends the command specified by the id of pressed switch.
     * - 1st parameter is a command string.
     * - 2nd parameter is a control flag. If true, it returns response line(s).
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
    esp_event_t *evt = ( esp_event_t * )event;

    /**
     * Check and print the returned response result, and response line(s).
     */
    if( evt->rcode == AT_RESP_OK ) {

        /**
         * Print all response lines (data).
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
int main( void ) {

    /**
     * Initializes the system.
     */
    System_Init();

    /**
     * Initializes the Uart1 (For debugging).
     */
    Uart1_Init( 115200, 64, 1024 );
    Uart1_WriteAsync( "\nPress a switch and check the result.\n" );

    /**
     * Initializes the Uart2 (For ESP8266 module).
     */
    Uart2_Init( 115200, 256, 256 );

    /**
     * Set callback function to all switches.
     */
    int16_t i;
    for( i = PSW_ID_0; i <= PSW_ID_3; i++ ) {
        Psw_SetKeyDownCallback( i, PSWx_Callback );
    }

    /**
     * Initializes the ESP with reseting (true).
     */
    Esp_Init( true );

    /**
     * Set callback function to the command executor.
     */
    Esp_SetCmdCallback( Cmd_Callback );

    Uart1_PrintfAsync( "\nConnecting to %s ...\n", SSID );

    /**
     * Join the AP or Hotspot (connect to WiFi network)
     * With the available SSID and PASS of the network.
     */
    Esp_JoinAccessPoint( SSID, PASS );


    /**
     * Starts the system.
     */
    System_Start();

    return 0;
}
