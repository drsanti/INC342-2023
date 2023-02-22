/************************************************************
 * Example 44. ESP32 HTTP Server Basic Commands             *
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
 * This example explains how to set up the HTTP server and
 * request handling technique. Generally, the browser will
 * send two requests to the server. One is a webpage request,
 * and another is a favicon (favicon.ico) request.
 * In this example, the favicon request will be ignored.
 * Check in the WifiDataReceived_Callback function for the
 * implementation details.
 *
 * When the client requests, the requesting information, e.g.,
 * the connection channel will be taken. After that, the state
 * machine will be changed to SERVER_STATE_REQUEST state and
 * the HTML response header and HTML response data.
 *
 * The HTTP response header is composed of three lines:
 * -----------------------------
 * HTTP/1.1 200 OK\r\n
 * Content-Type: text/html\r\n
 * \r\n
 * -----------------------------
 *
 * The HTML data is dynamically created by appending the
 * system time and sensor voltage in the format of
 * "<h1>Time: dddd.ddd mS, Sensor: d.ddd volts.</h1>".
 *
 * To check the result, run the application, open a web browser
 * and give it the IP address provided by the ESP. The result
 * shown in the web browser should look like this:
 * ---------------------------------------
 * Time: 1434357.625 mS, Sensor: 1.000 volts.
 * ---------------------------------------
 */


/**
 * SSID and PASS of the Access Point
 */
const char * SSID = SYSTEM_DEFAULT_NETWORK_SSID;    // Service Set Identifier
const char * PASS = SYSTEM_DEFAULT_NETWORK_PASS;    // Password of the network.



/**
 * Capture the AT returned results.
 */
#define AT_CAPTURE  false


/**
 * Timer pointer,
 */
timer_t *serverTimer = NULL;

/**
 * Server states.
 */
#define SERVER_STATE_INITIAL    0x00
#define SERVER_STATE_START      0x01
#define SERVER_STATE_WAITING    0x02
#define SERVER_STATE_REQUEST    0x03
#define SERVER_STATE_RESPONSD   0x04
#define SERVER_STATE_CLOSE      0x05

/**
 * Request structure.
 */
typedef struct {
    int16_t     state;
    int16_t     channel;
}request_info_t;
request_info_t  request;

/**
 * Callback function of the timer.
 */
void ClientTimer_Callback( event_t *event ) {

    /**
     * HTTP Response header.
     */
    const char *httpHead = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

    /**
     * HTML header for auto-refresh (3 seconds)
     */
    const char *htmlHead = "<head><meta http-equiv='refresh' content='3'></head>\r\n";

    /**
     * Use this html header to avoid the GET /favicon.ico HTTP/1.1
     */
    // const char *htmlHead = "<head><link rel='icon' href='data:;base64,iVBORw0KGgo='><meta http-equiv='refresh' content='3'></head>\r\n";


    /**
     * Get the switch event.
     */
    timer_event_t *evt = (timer_event_t *)event;

    /**
     * Helper macros
     */
    #define get_info()      ((request_info_t *)evt->context)
    #define next_state()    get_info()->state++
    #define get_state()     get_info()->state
    #define set_state(s)    get_info()->state=s
    #define wait_resp(ms)   Timer_SetInterval(evt->sender, ms)
    #define wait_next(ms)   get_info()->state++; wait_resp(ms)

    /**
     * Temporal buffer fo storing command.
     */
    char cmdbuff[64];


    /**
     * Pointer to dynamic memory buffer.
     */
    static char *datbuff = NULL;

    switch( get_state()  ) {

        /**
         * Configures the module to work as multiple IP connections.
         */
        case SERVER_STATE_INITIAL:
            Esp_AtSendCommandCapture( "AT+CIPMUX=1", AT_DEFAULT_TIMEOUT, AT_CAPTURE );
            wait_next(100);
        break;

        /**
         * Start the server and make it lesten to the port 80.
         */
        case SERVER_STATE_START:
            Esp_AtSendCommandCapture( "AT+CIPSERVER=1,80", AT_DEFAULT_TIMEOUT, AT_CAPTURE );
            wait_next(100);
        break;


        /**
         * Waiting for a request. The WiFi data received callback will release this state.
         */
        case SERVER_STATE_WAITING:
            Led_Flash( LED_ID_3, 1 );
            wait_resp(50); /* NO STATE IS CHANGED */
        break;


        /**
         * A client requested. Prepare the response header and data.
         */
        case SERVER_STATE_REQUEST:
            Beep_Play( 50, 5000 );

            if( datbuff != NULL ) {
                free( datbuff );
            }
            datbuff = malloc( strlen(httpHead) + 64 );
            sprintf( datbuff, "%s%s<h1>Time: %.3f mS, Sensor: %.3f volts.</h1>", httpHead, htmlHead, Sys_GetTimeMilli(), (double)Adc_GetVoltage( ADC_ID_1 ));

            sprintf( cmdbuff, "AT+CIPSEND=%d,%d", request.channel, strlen(datbuff) );
            Esp_AtSendCommandCapture( cmdbuff, AT_DEFAULT_TIMEOUT, AT_CAPTURE );
            wait_next( AT_DEFAULT_TIMEOUT );
        break;

        /**
         * Send the response header and data to the client.
         */
        case SERVER_STATE_RESPONSD:
            Esp_AtSendData( datbuff, strlen(datbuff), AT_DEFAULT_TIMEOUT );
            free( datbuff );
            datbuff = NULL;
            wait_next( AT_DEFAULT_TIMEOUT );
        break;

        /**
         * Close the connection.
         */
        case SERVER_STATE_CLOSE:
            sprintf( cmdbuff, "AT+CIPCLOSE=%d", request.channel );
            Esp_AtSendCommandCapture( cmdbuff, AT_DEFAULT_TIMEOUT, AT_CAPTURE );
            set_state( SERVER_STATE_WAITING );
        break;

        default:
             set_state( SERVER_STATE_CLOSE );
        break;
    }
}

/**
 * Starts the timer. This function is called from the WiFiStateChanged_Callback().
 */
void Start_Server( void ) {
    if( serverTimer == NULL ) {
        request.channel = 0;
        request.state   = SERVER_STATE_INITIAL;
        serverTimer = Timer_Create( 200, ClientTimer_Callback );
        serverTimer->context = &request;
        Uart1_WriteAsync( "Server is listening on port 80...\n" );
    }
}

/**
 * Ends the waiting state of the timer. This function is called from the Cmd_Callback().
 */
void Stop_Waiting( void ) {
    Timer_EndWaiting( serverTimer );
}


/**
 * Callback function of the WiFi data received.
 * Prints only the HTTP response lines.
 */
void WifiDataReceived_Callback( event_t *event ) {

    wifi_event_t *evt = ( wifi_event_t * )event;

    /*
     * Prints only the HTTP response content lines.
     */
    if( evt->recvState & RECV_STATE_START_HEAD &&  evt->recvState < RECV_STATE_RECEIVING ) {

        if( Str_Contains( evt->line, "favicon.ico" )) {
            Uart1_WriteAsync( "Reject: " );
            Uart1_WriteAsync( evt->line );
            request.channel = evt->channelId;
            request.state   = SERVER_STATE_CLOSE;       /* REJECT */
        }
        else {
            Uart1_WriteAsync( "Accept: " );
            Uart1_WriteAsync( evt->line );
            request.channel = evt->channelId;
            request.state   = SERVER_STATE_REQUEST;     /* ACCEPT */
        }
    }
}


/**
 * Callback function of the switches.
 */
void KeyDown_Callback( event_t *event ) {

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

        /**
         * Got the OK of SEND OK response, ends the timer waiting to make the state machine move to the next state.
         */
        Stop_Waiting();
    }
    else {
        Timer_Delete( serverTimer );
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
        Esp_AtSendCommandCapture( "AT+CIFSR", AT_DEFAULT_TIMEOUT, AT_CAPTURE_ENABLED );

        /**
         *
         */
        Start_Server();
    }
    else {
        Led_Pwm( LED_ID_0, 0, 2, 100 );
    }

    Beep_Play( 50, 2000 + evt->status*1000 );
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
    for(i = PSW_ID_0; i<= PSW_ID_3; i++) {
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
