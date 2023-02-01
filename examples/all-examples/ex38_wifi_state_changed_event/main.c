/************************************************************
 * Example 38. ESP8266 WiFi State Changed Callback & Event  *
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
 * 1) Change the SSID and PASS to match your AP or Hotspot
 * 2) Run the applicatio, and wait 3-10 seconds.
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
const char * SSID = SYSTEM_DEFAULT_NETWORK_SSID;  // Service Set Identifier
const char * PASS = SYSTEM_DEFAULT_NETWORK_PASS;   // Password of the network.


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
         * Prints all response lines (data).
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


/**
 * Callback function of the WiFi state changed.
 * This function will be called when the state of the WiFi is changed.
 */
void WiFi_Callback( event_t *event ) {

    /**
     * Get the event.
     */
    wifi_event_t *evt = (wifi_event_t *)event;

    /**
     * Print the WiFi status code.
     */
    Uart1_PrintfAsync( "WiFi Code: %d %s\r\n", evt->status, evt->sname );

    /**
     * Got the IP (Ready for IoT application)
     */
    if( evt->status == WIFI_STATUS_GOT_IP ) {

        Beep_Play( 50, 5000 );
        Led_Pwm( LED_ID_0, 0, 2, 1000 );
        Uart1_PrintfAsync( "\nConnected to \"%s\"\n\n", SSID );

        /**
         * Ask for IP and MAC addresses.
         */
        Esp_AtSendCommandCapture( "AT+CIFSR", AT_DEFAULT_TIMEOUT, AT_CAPTURE_ENABLED );
    }
    else {
        Led_Pwm( LED_ID_0, 0, 2, 100 );
        Beep_Play( 100, 2000 );
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
    Uart1_Init( 115200, 256, 256 );
    Uart1_Printf( "\n\nConnecting to %s, please wait...\n", SSID );

    /**
     * Initializes the Uart2 (For ESP8266 moduel).
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
     * Set callback function to the WiFi state changed.
     */
    Esp_SetWiFiStateChangedCallback( WiFi_Callback );

    /**
     * Join the AP or Hotspot (connect to WiFi network)
     * With the available SSID and PASS of the network.
     */
    Esp_JoinAccessPoint( SSID, PASS );

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
