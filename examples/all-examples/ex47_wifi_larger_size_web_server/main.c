/************************************************************
 * Example 47. WebServer for larger file size (>2048)       *
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
 */


/**
 * SSID and PASS of the Access Point
 */
const char * SSID = SYSTEM_DEFAULT_NETWORK_SSID;    // Service Set Identifier
const char * PASS = SYSTEM_DEFAULT_NETWORK_PASS;    // Password of the network.


/**
 * HTTP response header (17 bytes).
 */
const char *httpRespOK   = "HTTP/1.1 200 OK\r\n";

/**
 * HTML content-type (27 bytes).
 */
const char *htmlRespHead = "Content-Type: text/html\r\n\r\n";


/**
 * 4148 bytes of the static webpage.
 */
const char *htmlContent = "<html><head><title>ECC-Lab</title><style>body{text-align:center;background:#332;font-family:monospace;color:gray}h1{color:aqua;font-size:42px}.btn{width:120px;height:50px;font-size:20px;border-radius:4px;color:gainsboro;border:4px solid rgba(200,200,200,0.4);margin:0px 5px 0px 5px}.btn-success{background:rgb(12,184,55)}.btn-warning{background:rgb(199,107,2)}.btn-danger{background:rgb(238,25,25)}.btn-info{background:rgb(41,129,245)}.btn-primary{background:rgb(2,30,83)}.btn:hover{border:4px solid rgba(230,218,218,0.7);color:white;cursor:pointer}#line{width:100%;height:1px;margin-bottom:18px;background:lightcoral}#line2{width:100%;height:0.5px;margin-top:15px;background:rgba(11,68,255,0.767)}.led{display:inline-block;margin:20px 44px 20px 44px;width:44px;height:44px;border-radius:50%}.led-red{background-color:#F00;box-shadow:rgba(0,0,0,0.2) 0 -1px 7px 1px,inset #441313 0 -1px 9px,rgba(236,12,12,0.5) 0 2px 12px}.led-yellow{background-color:rgb(252,255,94);box-shadow:rgba(0,0,0,0.2) 0 -1px 7px 1px,inset #222501 0 -1px 9px,rgba(222,247,0,0.5) 0 2px 12px}.led-green{background-color:rgb(99,255,94);box-shadow:rgba(0,0,0,0.2) 0 -1px 7px 1px,inset #012507 0 -1px 9px,rgba(43,255,0,0.5) 0 2px 12px}.led-blue{background-color:rgb(94,231,255);box-shadow:rgba(0,0,0,0.2) 0 -1px 7px 1px,inset #010f25 0 -1px 9px,rgba(0,225,255,0.5) 0 2px 12px}.led-orange{background-color:rgb(255,140,94);box-shadow:rgba(0,0,0,0.2) 0 -1px 7px 1px,inset #251701 0 -1px 9px,rgba(255,187,0,0.5) 0 2px 12px}</style></head><body><h1>Static Webpage Example</h1><div id='line'></div><div><button class='btn btn-success'>Welcome</button><button class='btn btn-warning'>to</button><button class='btn btn-danger'>the</button><button class='btn btn-info'>MCU</button><button class='btn btn-primary'>world!</button></div><div><div class='led led-green'></div><div class='led led-yellow'></div><div class='led led-red'></div><div class='led led-blue'></div><div class='led led-orange'></div></div><div id='line'></div><div>2,048 bytes</div><div id='line2'></div><h1>Static Webpage Example</h1><div id='line'></div><div><button class='btn btn-success'>Welcome</button><button class='btn btn-warning'>to</button><button class='btn btn-danger'>the</button><button class='btn btn-info'>MCU</button><button class='btn btn-primary'>world!</button></div><div><div class='led led-green'></div><div class='led led-yellow'></div><div class='led led-red'></div><div class='led led-blue'></div><div class='led led-orange'></div></div><div id='line'></div><div>2,048 bytes</div><div id='line2'></div><h1>Static Webpage Example</h1><div id='line'></div><div><button class='btn btn-success'>Welcome</button><button class='btn btn-warning'>to</button><button class='btn btn-danger'>the</button><button class='btn btn-info'>MCU</button><button class='btn btn-primary'>world!</button></div><div><div class='led led-green'></div><div class='led led-yellow'></div><div class='led led-red'></div><div class='led led-blue'></div><div class='led led-orange'></div></div><div id='line'></div><div>2,048 bytes</div><div id='line2'></div><h1>Static Webpage Example</h1><div id='line'></div><div><button class='btn btn-success'>Welcome</button><button class='btn btn-warning'>to</button><button class='btn btn-danger'>the</button><button class='btn btn-info'>MCU</button><button class='btn btn-primary'>world!</button></div><div><div class='led led-green'></div><div class='led led-yellow'></div><div class='led led-red'></div><div class='led led-blue'></div><div class='led led-orange'></div></div><div id='line'></div><div>2,048 bytes</div><div id='line2'></div><h1>Static Webpage Example</h1><div id='line'></div><div><button class='btn btn-success'>Welcome</button><button class='btn btn-warning'>to</button><button class='btn btn-danger'>the</button><button class='btn btn-info'>MCU</button><button class='btn btn-primary'>world!</button></div><div><div class='led led-green'></div><div class='led led-yellow'></div><div class='led led-red'></div><div class='led led-blue'></div><div class='led led-orange'></div></div><div id='line'></div><div>2,048 bytes</div><div id='line2'></div></body></html>";


/**
 * Capture the AT returned results.
 * Should be false
 */
#define AT_CAPTURE  true


/**
 * Server states.
 */
#define SERVER_STATE_INITIAL    0x00    // Initial state, CIPMUX.
#define SERVER_STATE_START      0x01    // Start the server.
#define SERVER_STATE_WAITING    0x02    // Waiting for one or more requests.
#define SERVER_STATE_REQUEST    0x03    // One or more clients requested.
#define SERVER_STATE_RESPONSD   0x04    // Responding to a target client.
#define SERVER_STATE_CLOSE      0x05    // Close the current connection.


/**
 * Request structure.
 */
typedef struct {
    bool                pending;        // Waiting for response.
    int16_t             channel;        // Connecting channel.
}request_info_t;


#define MAX_REQUESTS    5               // Maximum of requests.
/**
 * Server structure
 *
 */
typedef struct {
    int16_t             state;                  // Server operation state.
    request_info_t      requests[MAX_REQUESTS]; // Requests array.
    request_info_t      *target;                // Target for making the response.
    int16_t             put;                    // Put index.
    int16_t             get;                    // Get index.
    int16_t             cnt;                    // Request counter.
    timer_t *           timer;
    int16_t             respState;
    int16_t             length;
}server_info_t;

/**
 * Pointer to server object.
 */
server_info_t server;


/**
 * Adds the request into client-array.
 * This function is called by the WiFi data received callback.
 */
bool Add_Request( int16_t channel ) {
    if( server.cnt >= MAX_REQUESTS ) {
        return false;
    }
    server.requests[server.put].channel = channel;
    server.requests[server.put].pending = true;
    server.cnt++;
    server.put = (server.put+1)%MAX_REQUESTS;
    return true;
}

/**
 * Return a request object.
 * This function is called by the state machine in the SERVER_STATE_WAITING state.
 */
request_info_t * Get_Request( void ) {
    if( server.cnt <= 0 ) {
        return NULL;
    }
    request_info_t *ri = &server.requests[server.get];
    server.cnt--;
    server.get = (server.get+1)%MAX_REQUESTS;
    return ri;
}

/**
 * Chunk size (2048 is the maximum value).
 */
#define CHUNK_SIZE   2048

/**
 * Chunk info structure/
 */
typedef struct {
    uint16_t         DataLength;    // Total size of the data.
    uint16_t         ChunkSize;     // Desired chunk size.
    uint16_t         NumFrames;     // Number of frames.
    uint16_t         RestBytes;     // Number of bytes of the last frame.
    uint16_t         SendBytes;     // Number of bytes to be sent.
    const char *     PtrFrame;      // Pointer to the data chunk.
}chunk_info_t;

/**
 * Chunk object.
 */
chunk_info_t chunk;


/**
 * Initializes the chunk object.
 * This function is called when the client requested.
 * See in the SERVER_STATE_WAITING state of the state machine.
 */
void Chunk_Init( const char * data, uint16_t ChunkSize ) {
    chunk.DataLength = strlen(data);
    chunk.ChunkSize  = ChunkSize;
    chunk.NumFrames  = chunk.DataLength / ChunkSize;
    chunk.RestBytes  = chunk.DataLength % ChunkSize;
    chunk.PtrFrame   = data;
}


/**
 * Callback function of the timer.
 */
void ClientTimer_Callback( event_t *event ) {


    #define iRESP_HEAD_PREP  0
    #define iRESP_HEAD_HTTP  1
    #define iRESP_HEAD_HTML  2
    #define iRESP_HTML_PREP  3
    #define iRESP_HTML_DATA  4


    #define DATA_SEND_TIMEOUT 10e3

    /**
     * Get the switch event.
     */
    timer_event_t *evt = (timer_event_t *)event;

    /**
     * Helper macros
     */
    #define get_info()              ((server_info_t *)evt->context)
    #define next_state()            get_info()->state++
    #define get_state()             get_info()->state
    #define CHANGE_TO_STATE(s)      get_info()->state=s
    #define SLEEP(ms)               Timer_SetInterval(evt->sender, ms)
    #define WAIT_AND_MOVE(ms)       get_info()->state++; SLEEP(ms)

    /**
     * Temporal buffer fo storing command.
     */
    char cmdbuff[64];


    Led_Flash( LED_ID_3, 1 );


    switch( get_state()  ) {

        /**
         * Configures the module to work as multiple IP connections.
         */
        case SERVER_STATE_INITIAL:
            Esp_AtSendCommandCapture( "AT+CIPMUX=1", AT_DEFAULT_TIMEOUT, AT_CAPTURE );
            WAIT_AND_MOVE( 100 );
        break;

        /**
         * Start the server and make it listen to the port 80.
         */
        case SERVER_STATE_START:
            Esp_AtSendCommandCapture( "AT+CIPSERVER=1,80", AT_DEFAULT_TIMEOUT, AT_CAPTURE );
            WAIT_AND_MOVE( 100 );
        break;


        /**
         * Waiting for a request. The WiFi data received callback will release this state.
         */
        case SERVER_STATE_WAITING:

            server.target = Get_Request();

            if( server.target != NULL ) {

                server.respState = 0;   // Reset the response state.

                /**
                 * Initializes/Resets the chunk object for the new request.
                 */
                Chunk_Init( htmlContent, CHUNK_SIZE );

                Beep_Play( 20, 4000);

                WAIT_AND_MOVE( 5 );     /* Check to SERVER_STATE_REQUEST */
            }
            else {
                SLEEP( 50 );            /* NO STATE IS CHANGED           */
            }
        break;


        /**
         * A client requested. Prepare the response header and data.
         */
        case SERVER_STATE_REQUEST:

            /**
             * Prepare HTTP response and HTML head.
             */
            if( server.respState == iRESP_HEAD_PREP ) {
                server.length = strlen(httpRespOK) + strlen(htmlRespHead);
                //Uart1_PrintfAsync( "Head Size: %d\n", server.length );
                sprintf( cmdbuff, "AT+CIPSEND=%d,%d", server.target->channel, server.length );
                Esp_AtSendCommandCapture( cmdbuff, AT_DEFAULT_TIMEOUT, AT_CAPTURE );
                server.respState++;                 /* Changed to iRESP_HEAD_HTTP */
                SLEEP( 500 );
            }
            /**
             * FIRST CHUNK OF HEADER
             * iRESP_HEAD_HTTP
             * Send the HTTP response.
             */
            else if( server.respState == iRESP_HEAD_HTTP ) {
                Uart1_WriteAsync("**iRESP_HEAD_HTTP**\n");
                Esp_AtSendData( httpRespOK, strlen(httpRespOK), DATA_SEND_TIMEOUT );
                server.respState++;                 /* Changed to iRESP_HEAD_HTML   */
                SLEEP( 1 );     /* Go to next, no waiting is required in this state */
            }
            /**
             * SECOND CHUNK OF HEADER
             * iRESP_HEAD_HTML
             * Send the HTML htmlRespHead
             */
            else if( server.respState == iRESP_HEAD_HTML ) {
                Uart1_WriteAsync("**iRESP_HEAD_HTML**\n");
                Esp_AtSendData( htmlRespHead, strlen(htmlRespHead), DATA_SEND_TIMEOUT );
                server.respState++;                  /* Changed to iRESP_HTML_PREP */
                SLEEP( DATA_SEND_TIMEOUT );
            }

            //-------------------------START CHUNK----------------------------------------------------

            /**
             * iRESP_HTML_PREP
             * Prepare HTML content.
             */
            else if( server.respState == iRESP_HTML_PREP ) {

                if( chunk.NumFrames > 0 ) {
                    chunk.SendBytes = CHUNK_SIZE;
                }
                else {
                    chunk.SendBytes = chunk.RestBytes;
                }

                if( chunk.SendBytes > 0 ) {

                    sprintf( cmdbuff, "AT+CIPSEND=%d,%d", server.target->channel, chunk.SendBytes );
                    Esp_AtSendCommandCapture( cmdbuff, AT_DEFAULT_TIMEOUT, AT_CAPTURE );
                    server.respState++;                     /* Changed to iRESP_HTML_DATA */
                }
                else {
                    CHANGE_TO_STATE( SERVER_STATE_CLOSE );  /* Changed to SERVER_STATE_CLOSE */
                }

                //Uart1_PrintfAsync("*nf: %2d nb: %d ptr: 0x%.4X\n", chunk.NumFrames, chunk.SendBytes, chunk.PtrFrame);

                SLEEP( 500 );
            }
            /**
             * iRESP_HTML_DATA
             * Sent HTML content.
             */
            else if( server.respState == iRESP_HTML_DATA ) {
                Esp_AtSendData( chunk.PtrFrame, chunk.SendBytes, DATA_SEND_TIMEOUT );

                /**
                 * Points to the next portion.
                 */
                chunk.PtrFrame += chunk.SendBytes;
                chunk.NumFrames--;

                if( chunk.SendBytes < CHUNK_SIZE ) {
                    // END
                    CHANGE_TO_STATE( SERVER_STATE_CLOSE );    /* Changed to SERVER_STATE_CLOSE */
                }
                else {
                    // Next portion
                    server.respState = iRESP_HTML_PREP;
                }

                //Uart1_PrintfAsync("#nf: %2d nb: %4d ptr: 0x%.4X\n", chunk.NumFrames, chunk.SendBytes, chunk.PtrFrame);

                SLEEP( DATA_SEND_TIMEOUT );
            }

            //-------------------------END CHUNK----------------------------------------------------

        break;

        /**
         * Send the response header and data to the client.
         */
        case SERVER_STATE_RESPONSD:
            WAIT_AND_MOVE( 1 );
        break;

        /**
         * Close the connection.
         */
        case SERVER_STATE_CLOSE:

            sprintf( cmdbuff, "AT+CIPCLOSE=%d", server.target->channel );
            server.target->pending = false;
            Esp_AtSendCommandCapture( cmdbuff, AT_DEFAULT_TIMEOUT, AT_CAPTURE );
            CHANGE_TO_STATE( SERVER_STATE_WAITING );
            SLEEP( 200 );
            Uart1_Printf("**%d closed**\n", server.target->channel);
        break;

        default:
            CHANGE_TO_STATE( SERVER_STATE_CLOSE );
        break;
    }
}

/**
 * Starts the timer. This function is called from the WiFiStateChanged_Callback().
 */
void Start_Server( void ) {
    if( server.timer == NULL ) {
        server.cnt = server.get = server.put = 0;
        server.state = SERVER_STATE_INITIAL;
        server.timer = Timer_Create( 200, ClientTimer_Callback );
        server.timer->context = &server;
        Uart1_WriteAsync( "Server is listening on port 80...\n" );
    }
}

void Stop_Server( void ) {
    Timer_Delete( server.timer );
    server.timer = NULL;
}

/**
 * Ends the waiting state of the timer. This function is called from the Cmd_Callback().
 */
void Stop_Waiting( void ) {
    //Timer_EndWaiting( server.timer );
    Timer_SetInterval( server.timer, 20 );
    Uart1_WriteAsync("**end timer**\n");
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
    if( evt->recvState & RECV_STATE_START_HEAD &&  evt->recvState < RECV_STATE_RECEIVING ) {


        if( Str_Contains( evt->line, "favicon.ico" )) {
            Uart1_WriteAsync( "Reject: " );
            Uart1_WriteAsync( evt->line );
        }
        else {
            Uart1_WriteAsync( "Accept: " );
            Uart1_WriteAsync( evt->line );
            Add_Request( evt->channelId );
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
    esp_event_t *evt = (esp_event_t *)event;

    /**
     * Check and print the returned response result, and response line(s).
     */
    if( evt->rcode == AT_RESP_OK ||  evt->rcode == AT_RESP_SEND_OK ) {

        /**
         * Prints all response lines (data) of the AT.
         */
        int i;
        for( i =0; i<evt->response->items; i++ ) {
            Uart1_PrintfAsync( "res[%d]: %s\r\n", i, evt->response->lines[i] );
        }

        /**
         * Got the OK of SEND OK response, ends the timer waiting to make the state machine move to the next state.
         */
        Stop_Waiting();
    }
    else if( evt->rcode >= AT_RESP_ERROR ) {

        server.state = SERVER_STATE_CLOSE;
        Timer_SetInterval( server.timer, 20 );
        /**
         * Prints AT Code
         */
        Uart1_PrintfAsync( "AtCode: %d %s\r\n", evt->rcode, evt->rstr );
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
         * Start the server.
         */
        Start_Server();
    }
    else {
        /**
         * Stop the server.
         */
        Stop_Server();
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
    for(i = PSW_ID_0; i<= PSW_ID_3; i++ ) {
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
