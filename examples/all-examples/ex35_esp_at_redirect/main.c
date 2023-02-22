/************************************************************
 * Example 35. ESP8266 Redirect response message to Uart1   *
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
 * This application receives response data from the ESP and
 * sends directly to the Uart1 byte-by-byte.
 *
 * Uart2 (RXIsr) --> Uart1 (TX)
 ************************************************************/


/**
 * SSID and PASS of the Access Point
 */
const char * SSID = SYSTEM_DEFAULT_NETWORK_SSID;   // Service Set Identifier
const char * PASS = SYSTEM_DEFAULT_NETWORK_PASS;   // Password of the network.


/**
 * Callback function of Uart1 line-received.
 * This function will be called when the Enter key is pressed.
 */
void Console_LineCallback( event_t *event ) {

    /**
     * Get the received line.
     */
    uart_event_t *evt = (uart_event_t *)event;
    const char *line  = evt->line;

    /**
     * Allocate a block of memory
     */
    int len = strlen(line)-2;    // Exclude the "\r\n"
    char *command = (char *)malloc( len+1 );

    /**
     * Copy and add NULL-terminator to the end of the command buffer.
     */
    strcpy( command, line );
    command[len] = 0;

    /**
     * Print the received command.
     */
    Uart1_PrintfAsync( "ATComd: %s\r\n", command );

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

/**
 * Callback function of Uart2 ISR byte received.
 */
void ESPByteReceived_Callback( event_t *event ) {

    uart_event_t *evt = ( uart_event_t * )event;

    /**
     * Redirect the received byte to the Uart1.
     */
    Uart1_PutAsync( evt->byte );
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
    Uart1_Init( 115200, 256, 256 );
    Uart1_Printf( "\n\nExample commands:\n");
    Uart1_Printf( "AT+GMR, AT+CWJAP?, AT+CIFSR, AT+CWLAP\n\n");

    /**
     * Set line received callback function to the Uart1.
     */
    Uart1_SetRxLineCallback( Console_LineCallback, 128 );

    /**
     * Initializes the Uart2 (For ESP8266 module).
     */
    Uart2_Init( 115200, 256, 256 );

    /**
     * Set ISR byte received callback function to the Uart2.
     */
    Uart2_SetRxIsrCallback( ESPByteReceived_Callback );

    /**
     * Initializes the ESP with reseting (true).
     */
    Esp_Init( true );

    /**
     * Join the AP or Hotpot (connect to WiFi network)
     * With the available SSID and PASS of the network.
     */
    Esp_JoinAccessPoint( SSID, PASS );

    /**
     * Starts the system.
     */
    System_Start();

    return 0;
}
