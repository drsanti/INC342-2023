/************************************************************
 * Example 39. ESP8266 Auto Setup (command sequence)        *
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
 ************************************************************/

/**
 * SSID and PASS of the Access Point
 */
const char * SSID = SYSTEM_DEFAULT_NETWORK_SSID;  // Service Set Identifier
const char * PASS = SYSTEM_DEFAULT_NETWORK_PASS;   // Password of the network.


/**
 * Example of setting commands
 */
const char *Commands[] = { "ATE1", "AT+GMR", "AT+CIFSR", "AT+CWJAP?", "AT+CWMODE?", "AT+CWSAP?" };
#define NUM_COMMANDS    6


timer_t *timerSetup = NULL;

void TimerAutoSetup_Callback( event_t *event ) {

    timer_event_t *evt = ( timer_event_t * )event;

    if( evt->counter >= NUM_COMMANDS ) {
        Timer_Delete( evt->sender );
    }

    Uart1_PrintfAsync( "Executing %s ...\n", Commands[evt->counter] );
    Esp_AtSendCommandCapture( Commands[evt->counter], AT_DEFAULT_TIMEOUT, AT_CAPTURE_ENABLED );

}



/**
 * Callback function of switches.
 */
void PSWx_Callback( event_t *event ) {

    Beep_Play( 20, 3000 );
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
        int i;
        for( i =0; i<evt->response->items; i++ ) {
            Uart1_PrintfAsync( "cap[%d]: %s\r\n", i, evt->response->lines[i] );
        }

        Timer_EndWaiting( timerSetup );
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
    wifi_event_t *evt = ( wifi_event_t * )event;

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

        if( timerSetup == NULL ) {
            timerSetup = Timer_Create( 2000, TimerAutoSetup_Callback );
        }
    }
    else {
        Led_Pwm( LED_ID_0, 0, 2, 100 );
        Beep_Play( 100, 2000 );

        Timer_Delete( timerSetup );
        timerSetup = NULL;
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
    Uart1_Printf( "\n\nConnecting to %s, please wait...\n", SSID );

    /**
     * Initializes the Uart2 (For ESP8266 moduel).
     */
    Uart2_Init( 115200, 64, 256 );

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
