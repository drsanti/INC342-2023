/************************************************************
 * Example 34. ESP8266 Console/Terminal                     *
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
 * This application receives an AT command from the user
 * through console window (Uart1) and sends the command to
 * the ESP module via Uart2.
 *
 * How to test?
 * Run the cli with the -monitor option and input the command
 * in the terminal/console window, e.g., AT+GMR and hit Enter key.
 ************************************************************/


/************************************************************
 * Setup
 *
 * 1) Change the SSID and PASS to match your AP or Hotspot
 * 2) Run the application, and wait 3-10 seconds.
 * 3) Press PSW1 to check the connected SSID.
 * 4) Press PSW2 to check IP address.
 ************************************************************/


/**
 * SSID and PASS of the Access Point
 */
const char * SSID = SYSTEM_DEFAULT_NETWORK_SSID;  // Service Set Identifier
const char * PASS = SYSTEM_DEFAULT_NETWORK_PASS;   // Password of the network.


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

        /**
         * Print all response lines (data).
         */
        int i;
        for( i =0; i<evt->response->items; i++ ) {
            Uart1_Printf( "cap[%d]: %s\r\n", i, evt->response->lines[i] );
        }
    }
    else {
        Uart1_PrintfAsync( "AtOK Code: %d %s\r\n", evt->rcode, evt->rstr );
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
        Beep_Play( 50, 5000  );
        Led_Pwm( LED_ID_0, 0, 2, 1000 );
        Uart1_PrintfAsync( "\nConnected to %s\n\n", SSID );

        /**
         * Ask for IP and MAC addresses.
         */
        Esp_AtSendCommandCapture( "AT+CIFSR",  AT_DEFAULT_TIMEOUT, AT_CAPTURE_ENABLED );
    }
    else {
        Led_Pwm( LED_ID_0, 0, 2, 100 );
        Beep_Play( 100, 2000 );
    }
}


/**
 * Callback function of Uart1 line-received.
 * This function will be called when the Enter key is pressed.
 */
void Console_LineCallback( event_t *event ) {

    /**
     * Get the received line.
     */
    uart_event_t *evt = (uart_event_t *)event;
    const char *line = evt->line;

    /**
     * Allocate a block of memory
     */
    int    len = strlen(line)-2;    // Exclude the "\r\n"
    char *command = (char *)malloc(len+1);

    /**
     * Copy and add NULL-terminator to the end of the buffer.
     */
    strcpy( command, line );
    command[len] = 0;

    /**
     * Print the received command.
     */
    Uart1_PrintfAsync( "ATComd: [%s]\r\n", command );

    /**
     * Send the received command to the ESP.
     */
    Esp_AtSendCommandCapture( command,  AT_DEFAULT_TIMEOUT, AT_CAPTURE_ENABLED );

    /**
     * Free the memory.
     */
    free( command );
    command = NULL;
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
    Uart1_Init( 115200, 256, 512 );
    Uart1_Printf( "\n\nExample commands:\n");
    Uart1_Printf( "AT+GMR, AT+CWJAP?, AT+CIFSR, AT+CWLAP\n\n");

    /**
     * Set callback function to the Uart1.
     */
    Uart1_SetRxLineCallback( Console_LineCallback, 128 );

    /**
     * Initializes the Uart2 (For ESP8266 module).
     */
    Uart2_Init( 115200, 256, 256 );

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
