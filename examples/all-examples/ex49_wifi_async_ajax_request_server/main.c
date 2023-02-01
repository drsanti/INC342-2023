/************************************************************
 * Example 49. Asynchronous AJAX Request (Simple Control)   *
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
 * HTTP 200 OK response header (17 bytes).
 */
const char *httpRespOK   = "HTTP/1.1 200 OK\r\n";

/**
 * HTTP 404 OK Not Found response header (24 bytes).
 */
const char *httpRespNF   = "HTTP/1.1 404 Not Found\r\n";

/**
 * HTML Content-type (27 bytes).
 */
const char *htmlRespHead = "Content-Type: text/html\r\n\r\n";

/**
 * CSS Content-type (26 bytes).
 */
const char *cssRespHead  = "Content-Type: text/css\r\n\r\n";

/**
 * JavaScript Content-type (33 bytes).
 */
const char *jsRespHead   = "Content-Type: text/javascript\r\n\r\n";


/**
 * HTML Content.
 */
const char *htmlContent = "<html><head><title>ECC-Lab</title><link rel='icon' href='data:;base64,iVBORw0KGgo='><link rel='stylesheet' href='http://ecc-lab.com/shared/bootstrap.css'><script src='http://ecc-lab.com/shared/jquery.js'></script><script src='http://ecc-lab.com/shared/bootstrap.js'></script><link rel='stylesheet' type='text/css' href='./index.css'><script type='text/javascript' src='index.js'></script></head><body><div class='container'><div class='row box'><div class='col col-xs-12'><div class='g-name'>Toggle LED</div><button class='btn btn-warning' id='led0-inv'>LED0 Inv</button><button class='btn btn-warning' id='led1-inv'>LED1 Inv</button><button class='btn btn-warning' id='led2-inv'>LED2 Inv</button><button class='btn btn-warning' id='led3-inv'>LED3 Inv</button></div></div><div class='row box'><div class='col col-xs-12'><div class='g-name'>Torn ON LED</div><button class='btn btn-danger' id='led0-on'>LED0 On</button><button class='btn btn-danger' id='led1-on'>LED1 On</button><button class='btn btn-danger' id='led2-on'>LED2 On</button><button class='btn btn-danger' id='led3-on'>LED3 On</button></div></div><div class='row box'><div class='col col-xs-12'><div class='g-name'>Torn OFF LED</div><button class='btn btn-primary' id='led0-off'>LED0 Off</button><button class='btn btn-primary' id='led1-off'>LED1 Off</button><button class='btn btn-primary' id='led2-off'>LED2 Off</button><button class='btn btn-primary' id='led3-off'>LED3 Off</button></div></div><div class='row box'><div class='col col-xs-12'><div class='g-name'>Read ADC</div><button class='btn btn-success' id='adc0'>ADC0</button><button class='btn btn-success' id='adc1'>ADC1</button><button class='btn btn-success' id='adc2'>ADC2</button><button class='btn btn-success' id='adc3'>ADC3</button></div></div><div class='row box'><div class='col col-xs-12'><div class='result' id='output'>ECC-Lab</div></div></div></div></body></html>";


/**
 * CSS Content.
 */
const char *cssContent = "body{margin:0;padding:0;background-color:#234;text-align:center}.g-name{color:grey;font-size:2em;margin-top:.5em;margin-bottom:.5em}.box{border:2px solid gray;border-radius:10px;padding-bottom:3em;margin-top:3em}.btn{width:7em;height:3.5em;font-weight:700;margin-left:.5em;margin-right:.5em;font-size:1.5em}.btn-danger,.btn-warning{color:black}.result{color:coral;font-weight:700;font-size:36px;margin-top:50px}";


/**
 * JavaScript Content.
 */
const char * jsContent = "window.onload=function(e){function n(e){return document.getElementById(e)}function t(e){var t=new XMLHttpRequest;t.timeout=2e3,t.onreadystatechange=function(){t.readyState==XMLHttpRequest.DONE&&(200==t.status?n('output').innerHTML=t.responseText:400==t.status?console.log('There was an error 400'):console.log('something else other than 200 was returned'))},t.open('GET',e,!0),t.send()}function o(e,o){n(e).addEventListener('click',function(){t(o)})}for(var a=0;4>a;a++)o('led'+a+'-inv','led/'+a+'/2;'),o('led'+a+'-on','led/'+a+'/1;'),o('led'+a+'-off','led/'+a+'/0;'),o('adc'+a,'adc/'+a+'/0;');setInterval(function(){t('adc/1/0;')},5e3)};";



/**
 * Custom defined indicators
 */
#define ON_REQUEST_INDICATOR()      Beep_Generate( 20, 4000, 0.2 ); /* Led_Flash(LED_ID_3, 5)*/
#define ON_CONNECTED_INDICATOR()    Beep_Generate( 20, 3000, 0.5 ); /* Led_Pwm( LED_ID_0, 0, 2, 1000 )*/
#define ON_DISCONNECTED_INDICATOR() Beep_Generate( 20, 1000, 0.5 ); /* Led_Pwm( LED_ID_0, 0, 2, 100  )*/


/**
 * Capture the AT returned reqults.
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
#define SERVER_STATE_RESPONSE   0x04    // Responding to a terget client.
#define SERVER_STATE_CLOSE      0x05    // Close the current connection.


/**
 * Request structure.
 */
typedef struct {
    bool                pending;        // Waiting for response.
    int16_t             channel;        // Connecting channel.
    char *              pGetRequest;    // Pointer to GET request memory.
}request_info_t;


#define MAX_REQUESTS    5               // Maximum of requests.
/**
 * Server structure
 *
 */
typedef struct {
    timer_t             *timer;                 // State control timer.
    int16_t             state;                  // Server operation state.
    request_info_t      requests[MAX_REQUESTS]; // Requests array.
    request_info_t      *target;                // Target for making the response.
    int16_t             put;                    // Put index.
    int16_t             get;                    // Get index.
    int16_t             cnt;                    // Request counter.

    int16_t             respState;              // Respond state.
    int16_t             length;                 // Data length.
}server_info_t;

/**
 * Pointer to server object.
 */
server_info_t server;


/**
 * Adds the request into client-array.
 * This function is called by the WiFi data received callback.
 */
inline bool Add_Request( int16_t channel, char ** line ) {
    if( server.cnt >= MAX_REQUESTS ) {
        return false;
    }
    request_info_t *rq = &server.requests[server.put];
    rq->channel  = channel;
    rq->pending  = true;
    rq->pGetRequest = *line;
    server.cnt++;
    server.put = ( server.put + 1 ) % MAX_REQUESTS;
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
    request_info_t *req = &server.requests[server.get];
    server.cnt--;
    server.get = ( server.get + 1 ) % MAX_REQUESTS;
    return req;
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

    /**
     * Target HTTP response header, e.g., 200 OK, 404 Not Found.
     */
    static const char * TargetHttpHead = NULL;

    /**
     * Target Content Header, e.g., Content-Type.
     */
    static const char * TargetRespHead  = NULL;

    /**
     * Target Content Data, e.g, HTML, CSS, JS.
     */
    static const char * TargetContent  = NULL;


    /**
     * Multiple chunks states
     */
    #define iRESP_HEAD_PREP     0 // Prepare the response header (HTTP + CONTENT).
    #define iRESP_HEAD_HTTP     1 // Send the HTTP response header (e.g., 200, 404).
    #define iRESP_HEAD_TARGET   2 // Send the target content header (e.g., Content-Type).
    #define iRESP_PREP_DATA     3 // Prepare the target data (e.g., html, css, js).
    #define iRESP_SEND_DATA     4 // Sand all chunks of the target data.


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
    #define SUSPEND(ms)             Timer_SetInterval(evt->sender, ms)
    #define WAIT_AND_MOVE(ms)       next_state(); SUSPEND(ms)

    /**
     * Command buffer.
     */
    char cmdbuff[64];

    static char respBuff[64];

    switch( get_state()  ) {

        /**
         * Configures the module to work as multiple IP connections.
         */
        case SERVER_STATE_INITIAL:
            Esp_AtSendCommandCapture( "AT+CIPMUX=1", AT_DEFAULT_TIMEOUT, AT_CAPTURE );
            WAIT_AND_MOVE( 100 );
        break;

        /**
         * Start the server and make it lesten to the port 80.
         */
        case SERVER_STATE_START:
            Esp_AtSendCommandCapture( "AT+CIPSERVER=1,80", AT_DEFAULT_TIMEOUT, AT_CAPTURE );
            WAIT_AND_MOVE( 100 );
        break;


        /**
         * Waiting for a request. The WiFi data received callback will release this state.
         */
        case SERVER_STATE_WAITING:

            /**
             * Get a request target.
             */
            server.target = Get_Request();

            if( server.target != NULL ) {

                /**
                 * Got a new request
                 */
                server.respState = 0;

                ON_REQUEST_INDICATOR();
                WAIT_AND_MOVE( 10 );     /* Check to SERVER_STATE_REQUEST */
            }
            /**
             * No request.
             */
            else {
                SUSPEND( 50 );            /* NO STATE IS CHANGED           */
            }
        break;

        /**
         * A client requested. Prepare the response header and data.
         */
        case SERVER_STATE_REQUEST:

            /**
             * Default HTTP response header.
             */
            TargetHttpHead = httpRespOK;

            /**
             * HTML Request (root/home)
             */
            if( Str_Contains( server.target->pGetRequest, "GET / " ) ) {
                TargetRespHead = htmlRespHead;
                TargetContent  = htmlContent;
            }
            /**
             * CSS Request
             */
            else if( Str_Contains( server.target->pGetRequest, "GET /index.css" ) ) {
                TargetRespHead = cssRespHead;
                TargetContent  = cssContent;
            }
            /**
             * JavaScript Request
             */
            else if( Str_Contains( server.target->pGetRequest, "GET /index.js" ) ) {
                TargetRespHead = jsRespHead;
                TargetContent  = jsContent;
            }
            else if( Str_Contains( server.target->pGetRequest, "GET /adc/" ) || Str_Contains( server.target->pGetRequest, "GET /led/" ) ) {
                // +IPD,0,328:GET /adc/0/0; HTTP/1.1  => ADC0 READ
                // +IPD,0,328:GET /led/0/1; HTTP/1.1  => LED0 ON
                // +IPD,0,328:GET /led/0/0; HTTP/1.1  => LED0 OFF
                // +IPD,0,328:GET /led/0/2; HTTP/1.1  => LED0 TOGGLE

                const char *line = server.target->pGetRequest;

                int16_t i1 = Str_IndexOf( line, "/" );
                int16_t id = line[(i1+5)]-0x30;
                int16_t fn = line[(i1+7)]-0x30;

                //Uart1_PrintfAsync("id: %d, fn: %d\r\n", id, fn);



                /**
                 * adc
                 */
                if( Str_Contains( server.target->pGetRequest, "GET /adc/" ) ) {
                    sprintf( respBuff, "<h1>ADC%d is %d</h1>", id, Adc_Get(id) );
                }
                /**
                 * led
                 */
                else {
                    //const char *LED_STATES[] = { "OF", "ON", "TOGGLE" };
                    if( fn == 0 ) {
                        Led_Clr( id );
                    }
                    else if (fn == 1) {
                        Led_Set ( id );
                    }
                    else if( fn == 2 ) {
                        Led_Inv( id );
                    }
                    sprintf(respBuff, "<h1>LED%d is %s</h1>", id, Led_Get(id)?"ON":"OFF");
                }

                TargetRespHead = htmlRespHead;
                TargetContent  = respBuff;
            }
            /**
             * Unknown request.
             */
            else {
                TargetHttpHead = httpRespNF;    /* 404 Not Found */
                TargetRespHead = htmlRespHead;
                TargetContent  = "<h2 class='error'>Unknown Request</h2>";
            }

            /**
             * Free the memory.
             */
            free( server.target->pGetRequest );
            server.target->pGetRequest = NULL;

            /**
             * Initializes/Resets the chunk object for the new request.
             */
            Chunk_Init( TargetContent, CHUNK_SIZE );

            /**
             * All parameters are prepared. Move to the next state.
             */
            WAIT_AND_MOVE( 10 );     /* Check to SERVER_STATE_RESPONSE */

        break;

        /**
         * Send the response headers and data to the client.
         */
        case SERVER_STATE_RESPONSE:

            /**
             * Prepare HTTP response and HTML head.
             */
            if( server.respState == iRESP_HEAD_PREP ) {
                server.length = strlen(TargetHttpHead) + strlen(TargetRespHead); // HTTP + RESP
                sprintf( cmdbuff, "AT+CIPSEND=%d,%d", server.target->channel, server.length );
                Esp_AtSendCommandCapture( cmdbuff, AT_DEFAULT_TIMEOUT, AT_CAPTURE );
                server.respState++;                 /* Changed to iRESP_HEAD_HTTP */
                SUSPEND( 200 );                     /* The SUSPEND() will be terminated when a response is received */
            }
            /**
             * FIRST PORTION OF HEADER
             * iRESP_HEAD_HTTP
             * Send the TargetHttpHead.
             */
            else if( server.respState == iRESP_HEAD_HTTP ) {
                Esp_AtSendData( TargetHttpHead, strlen(TargetHttpHead), AT_DEFAULT_TIMEOUT<<2 );
                server.respState++;                 /* Changed to iRESP_HEAD_TARGET             */
                SUSPEND( 20 );   /* Move to the next state, waiting is not required in this state */
            }
            /**
             * SECOND PORTION OF HEADER
             * iRESP_HEAD_TARGET
             * Send the TargetRespHead.
             */
            else if( server.respState == iRESP_HEAD_TARGET ) {
                Esp_AtSendData( TargetRespHead, strlen(TargetRespHead), AT_DEFAULT_TIMEOUT<<2 );
                server.respState++;                  /* Changed to iRESP_PREP_DATA */
                SUSPEND( 5000 );
            }

            //-------------------------START CHUNK----------------------------------------------------

            /**
             * iRESP_PREP_DATA
             * Prepare Target Content (multiple chunks).
             */
            else if( server.respState == iRESP_PREP_DATA ) {

                if( chunk.NumFrames > 0 ) {
                    chunk.SendBytes = chunk.ChunkSize;
                }
                else {
                    chunk.SendBytes = chunk.RestBytes;
                }

                if( chunk.SendBytes > 0 ) {

                    sprintf( cmdbuff, "AT+CIPSEND=%d,%d", server.target->channel, chunk.SendBytes );
                    Esp_AtSendCommandCapture( cmdbuff, AT_DEFAULT_TIMEOUT, AT_CAPTURE );
                    server.respState++;                     /* Changed to iRESP_SEND_DATA */
                }
                else {
                    CHANGE_TO_STATE( SERVER_STATE_CLOSE );  /* Changed to SERVER_STATE_CLOSE */
                }

                SUSPEND( 500 );                              /* The SUSPEND() will be terminated when a response is received */
            }
            /**
             * iRESP_SEND_DATA
             * Sent HTML content.
             */
            else if( server.respState == iRESP_SEND_DATA ) {

                /**
                 * Send the target chunk to the module.
                 */
                Esp_AtSendData( chunk.PtrFrame, chunk.SendBytes, AT_DEFAULT_TIMEOUT<<2 );

                /**
                 * Points to the next portion.
                 */
                chunk.PtrFrame += chunk.SendBytes;
                chunk.NumFrames--;

                if( chunk.SendBytes < CHUNK_SIZE ) {
                    // END
                    CHANGE_TO_STATE( SERVER_STATE_CLOSE );  /* Changed to SERVER_STATE_CLOSE */
                }
                else {
                    // Next portion
                    server.respState = iRESP_PREP_DATA;     /* Perform the next chunk       */
                }

                SUSPEND( 2000 );                            /* The SUSPEND() will be terminated when a response is received */
            }

            //-------------------------END CHUNK----------------------------------------------------

        break;

        /**
         * Close the connection.
         */
        case SERVER_STATE_CLOSE:

            sprintf( cmdbuff, "AT+CIPCLOSE=%d", server.target->channel );
            server.target->pending = false;
            Esp_AtSendCommandCapture( cmdbuff, AT_DEFAULT_TIMEOUT, AT_CAPTURE );
            CHANGE_TO_STATE( SERVER_STATE_WAITING );
            SUSPEND( 200 );
        break;

        default:
            CHANGE_TO_STATE( SERVER_STATE_CLOSE );
        break;
    }
}

/**
 * Starts the Server. This function is called from the WiFiStateChanged_Callback().
 */
void Start_Server( void ) {
    if( server.timer == NULL ) {
        server.cnt   = server.get = server.put = 0;
        server.state = SERVER_STATE_INITIAL;
        server.timer = Timer_Create( 200, ClientTimer_Callback );
        server.timer->context = &server;
        Uart1_WriteAsync( "Server is listening on port 80...\n" );
    }
}

/**
 * Stop the Server. This function is called from the WiFiStateChanged_Callback().
 */
void Stop_Server( void ) {
    Timer_Delete( server.timer );
    server.timer = NULL;
}

/**
 * Ends the waiting state of the timer. This function is called from the Cmd_Callback().
 */
void Stop_Waiting( void ) {
    Timer_EndWaiting( server.timer );
}


/**
 * Callback function of the WiFi data received.
 * Ptints only the HTTP response lines.
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
        }
        else {
            Uart1_WriteAsync( "Accept: " );
            Uart1_WriteAsync( evt->line );

            /**
             * Must be copy in this point to avoid data loss.
             */
            char *p = malloc( strlen(evt->line) + 1 );
            strcpy(p, evt->line);
            Add_Request( evt->channelId, &p );
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
        int16_t i;
        for( i =0; i<evt->response->items; i++ ) {
            Uart1_PrintfAsync( "cap[%d]: %s\r\n", i, evt->response->lines[i] );
        }

        /**
         * Got the OK of SEND OK response, ends the timer waiting to make the state machine move to the next state.
         */
        Stop_Waiting();
    }
    else if( evt->rcode >= AT_RESP_ERROR ) {

        if( server.state == SERVER_STATE_CLOSE ) {
            server.state = SERVER_STATE_INITIAL;
        }
        else {
            server.state = SERVER_STATE_CLOSE;
        }

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

        Uart1_PrintfAsync( "Connected to %s\n\n", SSID );

        /**
         * Ask for IP and MAC addresses.
         */
        Esp_AtSendCommandCapture( "AT+CIFSR", AT_DEFAULT_TIMEOUT, AT_CAPTURE_ENABLED );

        /**
         * Start the Server.
         */
        Start_Server();


        ON_CONNECTED_INDICATOR();
    }
    else {

        if( evt->status == WIFI_STATUS_DISCONNECT ) {

            /**
             * Stop the Server.
             */
            Stop_Server();

            ON_DISCONNECTED_INDICATOR();
        }
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
    Uart1_Init( 115200, 256, 512 );
    Uart1_Printf( "\n\nConnecting to %s, please wait...\n", SSID );

    /**
     * Initializes the Uart2 (For ESP8266 module).
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
