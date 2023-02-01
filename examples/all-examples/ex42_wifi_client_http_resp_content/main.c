/************************************************************
 * Example 42. HTTP Response Content                        *
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
 * This application explains the HTTP response content.
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
 *
 * When the request is made, the server will return the content
 * to the client, the ESP8266. if our settings are:
 *  - host: "www.ecc-lab.com"
 *  - path: "/iot/apis/?time"
 * The response content shoule be:
 * ----------------------------
 * 09:58:49
 *
 * ----------------------------
 * The server is programmed to return the current time when the
 * client requests to the "iot/apis/?time".
 *
 * If we changed the path (url) root, "/", the server will return
 * the html content (webpage) which look like this:
 * -------------------------------------------
 * <!doctype html><html...
 * ...
 * ...
 * ...</html>
 *
 * -------------------------------------------
 *
 * Generally, requesting a webpage (HTML) not make any sense for
 * the ESP8266. It is not designed to work with the HTML content.
 * That a reason why a special server that supports AIP calling is
 * required in the IoT applications.
 */


/**
 * SSID and PASS of the Access Point
 */
const char * SSID = SYSTEM_DEFAULT_NETWORK_SSID;    // Service Set Identifier
const char * PASS = SYSTEM_DEFAULT_NETWORK_PASS;    // Password of the network.



/**
 * Callback function of the WiFi data received.
 * Ptins only the HTTP response lines.
 */
void WifiDataReceived_Callback( event_t *event ) {

    wifi_event_t *evt = ( wifi_event_t * )event;

    /*
     * Prints only the HTTP response content lines.
     */
    if( evt->recvState >= RECV_STATE_COLLECTING ) {
        Uart1_WriteAsync( evt->line );
    }
}


/**
 * Callback function of the switches.
 */
void KeyDown_Callback( event_t *event ) {

    /**
     * Capture the AT returned reqults.
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
    //const char * path = "/";

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
    wifi_event_t *evt = ( wifi_event_t * )event;

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
        Esp_AtSendCommandCapture( "AT+CIFSR", AT_DEFAULT_TIMEOUT, AT_CAPTURE_ENABLED );
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
        Psw_SetKeyDownCallback( i, KeyDown_Callback );
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
