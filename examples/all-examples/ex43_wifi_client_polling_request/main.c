/************************************************************
 * Example 43. HTTP Client Pooling Requests                 *
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
 * This application explains how to use a software timer for
 * client polling requests.
 *
 *  - The timer will be started when the IP address is received.
 *  - The timer will be stopped when "WIFI DISCONNECT" state is occurred.
 *  - The timer waiting will be ended when the AT return "OK" or "SEND OK",
 *    to allow the state machine to change to the next state.
 *  - Waiting time can be changed by pressing the switches.
 */


/**
 * SSID and PASS of the Access Point
 */
const char * SSID = SYSTEM_DEFAULT_NETWORK_SSID;  // Service Set Identifier
const char * PASS = SYSTEM_DEFAULT_NETWORK_PASS;   // Password of the network.


/**
 * Host and Path for the HTTP GET request.
 */
const char * host = "www.ecc-lab.com";
const char * path = "/iot/apis/?time"; // time, date, real, int


/**
 * Polling interval in milliseconds.
 */
#define POLLING_REQEUST_INTERVAL 5000

/**
 * Capture the AT returned results.
 */
#define AT_CAPTURE  false



/**
 * Client states
 */
#define CLIENT_STATE_SUSPEND    0x00 // Not initialized (not used in this example).
#define CLIENT_STATE_WAITING    0x01 // Waiting for the next request (timeout).
#define CLIENT_STATE_CONNECT    0x02 // Connect to the server.
#define CLIENT_STATE_PREPARE    0x03 // Prepare the request header.
#define CLIENT_STATE_REQUEST    0x04 // Send the request to the server.
#define CLIENT_STATE_CLOSE      0x05 // Close the connection.

/**
 * Client data structure.
 */
typedef struct {
    int16_t  state;         // Client state.
    double   interval;      // Requesting interval (ms).
    double   prevTime;      // Previous time (used to calculate interval).
}client_info_t;

/**
 * Client info object.
 */
client_info_t client;


/**
 * Timer pointer,
 */
timer_t *clientTimer = NULL;

/**
 * Callback function of the timer.
 */
void ClientTimer_Callback( event_t *event ) {

    /**
     * Get the switch event.
     */
    timer_event_t *evt = (timer_event_t *)event;

    /**
     * Helper macros
     */
    #define get_info()      ((client_info_t *)evt->context)
    #define next_state()    get_info()->state++
    #define get_state()     get_info()->state
    #define set_state(s)    get_info()->state=s
    #define wait_resp(ms)   Timer_SetInterval(evt->sender, ms)

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
         * Waiting for the next request.
         */
        case CLIENT_STATE_WAITING:
            if( Sys_GetTimeMilli() - get_info()->prevTime > get_info()->interval ) {
                next_state();
                get_info()->prevTime = Sys_GetTimeMilli();
                Led_Flash( LED_ID_3, 100 );
                Beep_Play( 20, 4000 );
            }
        break;

        /**
         * Connect to the server.
         */
        case CLIENT_STATE_CONNECT:
            sprintf(cmdbuff, "AT+CIPSTART=\"TCP\",\"%s\",80", host);
            Esp_AtSendCommandCapture( cmdbuff, AT_DEFAULT_TIMEOUT, AT_CAPTURE );
            next_state();
            wait_resp( AT_DEFAULT_TIMEOUT );
            break;

        /**
         * Prepare the memory and request header.
         */
        case CLIENT_STATE_PREPARE:

            if( datbuff != NULL) {
                free( datbuff );
            }
            datbuff = malloc( strlen(host) + strlen(path) + 64);
            sprintf( datbuff, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", path, host);

            sprintf( cmdbuff, "AT+CIPSEND=%d", strlen( datbuff ) );
            Esp_AtSendCommandCapture( cmdbuff, AT_DEFAULT_TIMEOUT, AT_CAPTURE );
            next_state();
            wait_resp(200);
        break;

        /**
         * Send the request and free the memory.
         */
        case CLIENT_STATE_REQUEST:
            Uart1_WriteAsync( "Requesting...\r\n" );
            Esp_AtSendData( datbuff, strlen( datbuff ), AT_DEFAULT_TIMEOUT<<1 );
            next_state();
            wait_resp( AT_DEFAULT_TIMEOUT );

            free( datbuff );
            datbuff = NULL;
        break;

        /**
         * Close the connection.
         */
        case CLIENT_STATE_CLOSE:
            Esp_AtSendCommandCapture( "AT+CIPCLOSE", AT_DEFAULT_TIMEOUT, AT_CAPTURE );
            next_state();
            wait_resp( 200 );
        break;

        default:
            set_state(CLIENT_STATE_WAITING);
        break;

    }
}

/**
 * Starts the timer. This function is called from the WiFiStateChanged_Callback().
 */
void Start_Client( void ) {
    if( clientTimer == NULL ) {
        client.state = CLIENT_STATE_CONNECT;
        client.interval = POLLING_REQEUST_INTERVAL;
        client.prevTime = 0;
        clientTimer = Timer_Create( 200, ClientTimer_Callback );
        clientTimer->context = &client;
        Uart1_WriteAsync( "Client polling requests start...\n" );
    }
}

/**
 * Ends the waiting state of the timer. This function is called from the Cmd_Callback().
 */
void Stop_Waiting( void ) {
    Timer_EndWaiting( clientTimer );
}


/**
 * Callback function of the WiFi data received.
 * Prints only the HTTP response lines.
 */
void WifiDataReceived_Callback( event_t *event ) {

    wifi_event_t *evt = (wifi_event_t *)event;

    /*
     * Prints only the HTTP response content lines.
     */
    if( evt->recvState >= RECV_STATE_COLLECTING ) {
        Uart1_WriteAsync( evt->line );
    }

    if( evt->recvState >= RECV_STATE_COMPLETED ) {
        Beep_Play( 40, 6000 );
    }
}


/**
 * Callback function of the switches.
 */
void KeyDown_Callback( event_t *event ) {

    client.interval = 3000 + ((switch_event_t *)event)->id * 2000;
    Uart1_Printf( "\nThe waiting interval is changed to %.2f mS.\n", client.interval );

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
        int i;
        for( i =0; i<evt->response->items; i++ ) {
            Uart1_PrintfAsync( "cap[%d]: %s\r\n", i, evt->response->lines[i] );
        }

        /**
         * Got the OK of SEND OK response, ends the timer waiting to make the state machine move to the next state.
         */
        Stop_Waiting();
    }
    else {
        Timer_Delete( clientTimer );
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

        /**
         *
         */
        Start_Client();
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
