/************************************************************
 * Example 41. HTTP Response Header                         *
 ************************************************************
 * File:    main.c                                          *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 ************************************************************
 * Update:  08 March 2020 (Initial version)                 *
 ************************************************************/

/************************************************************
 * Include the system header.
 ************************************************************/
#include <ecc.h>


/**
 * Application Description:
 *
 * This application explains the HTTP response header.
 * This example uses a dynamic memory allocation method
 * in the client requesting procedures. Check on the
 * KeyDown_Callback function.
 *
 *  - PSW0: Connect to the server.
 *  - PSW1: Prepare the request.
 *  - PSW2: Sent the request to the server.
 *  - PSW3: Close the connection.
 *
 * This application connects to the www.ecc-lab.com providing
 * some simple APIs as follows:
 *  - www.ecc-lab.com/iot/apis/?int
 *  - www.ecc-lab.com/iot/apis/?real (or float or double)
 *  - www.ecc-lab.com/iot/apis/?time
 *  - www.ecc-lab.com/iot/apis/?date
 *
 * The request package, the HTTP request, at lees, must be
 * composed of the two parts, e.g., GET url followed by protocol,
 * and host name and CRLF (new line). For instance:
 * ----------------------------
 * GET /iot/apis/?time HTTP/1.1
 * Host: www.ecc-lab.com
 * CRLF
 * ----------------------------
 *
 * This is an example of the HTTP response header
 * received from the www.ecc-lab.com server.
 * --------------------------------------
 * +IPD,288:HTTP/1.1 200 OK
 * Server: nginx/1.9.2
 * Date: Sun, 08 Mar 2020 02:17:27 GMT
 * Content-Type: text/html; charset=UTF-8
 * Content-Length: 10
 * Connection: keep-alive
 * Keep-Alive: timeout=20
 * Upgrade: h2,h2c
 * X-Powered-By: PHP/5.6.31
 * Access-Control-Allow-Origin: *
 * Vary: User-Agent
 * --------------------------------------
 *
 * This is an example of the HTTP response header
 * received from the www.github.com server.
 * --------------------------------------
 * +IPD,343:HTTP/1.1 200 OK
 * Server: nginx/1.9.2
 * Date: Sun, 08 Mar 2020 02:23:27 GMT
 * Content-Type: text/html
 * Content-Length: 44
 * Connection: keep-alive
 * Keep-Alive: timeout=20
 * Upgrade: h2,h2c
 * Last-Modified: Sun, 07 Apr 2019 18:57:29 GMT
 * ETag: "2c-585f54aa95a5d"
 * Accept-Ranges: bytes
 * Vary: User-Agent
 *
 * --------------------------------------
 *
 * The first line is the ESP specific. The number
 * after the "+IPD", informs the total package size i
 * including all CRLFs and other hidden characters.
 * Other lines are the common header element of the
 * HTTP response header.
 *
 */


/**
 * SSID and PASS of the Access Point
 */
const char * SSID = SYSTEM_DEFAULT_NETWORK_SSID;    // Service Set Identifier
const char * PASS = SYSTEM_DEFAULT_NETWORK_PASS;    // Password of the network.


/**
 * Callback function of the WiFi data received.
 */
void WifiDataReceived_Callback( event_t *event ) {

    wifi_event_t *evt = ( wifi_event_t * )event;

    /*
     * Prints only the HTTP response header lines (no content).
     */
    if( evt->recvState <= RECV_STATE_END_HEAD ) {
        Uart1_WriteAsync( evt->line );
    }
}



/**
 * Callback function of the switches.
 */
void KeyDown_Callback( event_t *event ) {

    /**
     * Capture the AT returned results.
     */
    #define AT_CAPTURE true

    /**
     * Get the switch event.
     */
    switch_event_t *evt = ( switch_event_t * )event;

    /**
     * Host and Path for the HTTP GET request.
     */
    const char * host = "www.ecc-lab.com";
    const char * path = "/iot/apis/?time";

    /**
     * Messages
     */
    const char *InfoMessages[] = { "\n1) Connect\n", "\n2) Prepare\n", "\n3) Request, please wait...\n", "\n4) Close\n" };


    Uart1_WriteAsync( InfoMessages[evt->id] );

    /**
     * Temporal buffer fo storing command.
     */
    char cmdbuff[64];

    /**
     * Pointer to memory buffer.
     */
    static char *datbuff = NULL;

    switch( evt->id ) {

        /**
         * Connect to the server.
         */
        case PSW_ID_0:
        sprintf(cmdbuff, "AT+CIPSTART=\"TCP\",\"%s\",80", host);
        Esp_AtSendCommandCapture( cmdbuff, AT_DEFAULT_TIMEOUT, AT_CAPTURE  );
        break;

        /**
         * Prepare the memory and request header.
         */
        case PSW_ID_1:
            if( datbuff != NULL) {
                free( datbuff );
            }
            datbuff = malloc( strlen(host) + strlen(path) + 64);
            sprintf( datbuff, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", path, host);

            sprintf( cmdbuff, "AT+CIPSEND=%d", strlen( datbuff ) );
            Esp_AtSendCommandCapture( cmdbuff, AT_DEFAULT_TIMEOUT, AT_CAPTURE  );
        break;

        /**
         * Send the request and free the memory.
         */
        case PSW_ID_2:
            Esp_AtSendData( datbuff, strlen( datbuff ), AT_DEFAULT_TIMEOUT );

            free( datbuff );
            datbuff = NULL;
        break;

        /**
         * Close the connection.
         */
        case PSW_ID_3:
            Esp_AtSendCommandCapture( "AT+CIPCLOSE", AT_DEFAULT_TIMEOUT, AT_CAPTURE  );
        break;
    }

    /**
     * Beep
     */
    Beep_Play( 50, 4000 );
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
    if( evt->rcode == AT_RESP_OK ||  evt->rcode == AT_RESP_SEND_OK ) {

        /**
         * Prints all response lines (data) of the AT.
         */
        int16_t i;
        for( i =0; i<evt->response->items; i++ ) {
            Uart1_PrintfAsync( "cap[%d]: %s\r\n", i, evt->response->lines[i] );
        }
    }
    else {
        /**
         * Prints AT Code
         */
        Uart1_PrintfAsync( "At Code: %d %s\r\n", evt->rcode, evt->rstr );
    }
}


/**
 * Callback function of the WiFi state changed.
 * This function will be called when the state of the WiFi is changed.
 */
void WiFiStateChanged_Callback( event_t *event ) {

    /**
     * Get the event.
     */
    wifi_event_t *evt = (wifi_event_t *)event;

    /**
     * Prints the WiFi status code and status name.
     */
    Uart1_PrintfAsync( "WiFi Code: %d %s\r\n", evt->status, evt->sname );

    /**
     * Got the IP (Ready for IoT application)
     */
    if( evt->status == WIFI_STATUS_GOT_IP ) {

        Led_Pwm( LED_ID_0, 0, 2, 1000 );
        Uart1_PrintfAsync( "\nConnected to %s\n\n", SSID );

        /**
         * Ask for IP and MAC addresses.
         */
        Esp_AtSendCommandCapture( "AT+CIFSR", AT_DEFAULT_TIMEOUT, AT_CAPTURE );
    }
    else {
        Led_Pwm( LED_ID_0, 0, 2, 100 );
    }

    Beep_Play( 50, (2000 + evt->status*1000) );
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
    Uart1_Init( 115200, 64, 512 );
    Uart1_Printf( "\n\nConnecting to %s, please wait...\n", SSID );

    /**
     * Initializes the Uart2 (For ESP8266 moduel).
     */
    Uart2_Init( 115200, 512, 256 );


    /**
     * Initializes the ESP with reseting (true).
     */
    Esp_Init( true );

    /**
     * Set callback function to the WiFi state changed.
     */
    Esp_SetWiFiStateChangedCallback( WiFiStateChanged_Callback );

    /**
     * Set callback function to the WiFi data received.
     */
    Esp_SetWiFiDataReceivedCallback ( WifiDataReceived_Callback );

    /**
     * Set the KeyDown and KeyChanged callback functions to all switches.
     */
    int16_t i;
    for( i = PSW_ID_0; i<= PSW_ID_3; i++ ) {
        Psw_SetKeyDownCallback   ( i, KeyDown_Callback );
    }

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
