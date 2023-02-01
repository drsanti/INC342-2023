/************************************************************
 * Example 32. ESP8266 AT-Commands and Callback             *
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
 * When a switch is pressed, an AT command will be sent to the
 * ESP module. All returned bytes of data (messages) of the
 * ESP module are redirected to the Uart1 (terminal). When the
 * at-command operation is completed, the LED0 will flash together
 * with the beep sound.
 *
 * Key Down:
 *   PSW0 - AT+GMR      Check Version and other information.
 *   PSW1 - AT+CWJAP?   Check the current connected AP.
 *   PSW2 - AT+CIFSR    Check IP and MAC addresses of AP and STA.
 *   PSW3 - AT+CWLAP    Check all the available WiFi networks.
 ************************************************************/

/**
 * Commands
 */
const char *COMDS[] = { "AT+GMR", "AT+CWJAP?", "AT+CIFSR", "AT+CWLAP" };

/**
 * Callback function of switches.
 */
void PSWx_Callback( event_t *event ) {

    switch_event_t *evt = (switch_event_t *)event;

    Uart1_PrintfAsync( "\nSending command [%s]\n\n", COMDS[evt->id] );

    /**
     * Sends the command specified by the id of pressed switch.
     * - 1st parameter is a command string.
     * - 2nd parameter is a timeout value in milliseconds.
     */
    Esp_AtSendCommand( COMDS[evt->id], AT_DEFAULT_TIMEOUT );

    Beep_Play( 50, (1000 + (500 * evt->id)) );
}

/**
 * Callback function of the Uart2 byte received (ESP).
 * Redirects the received bytes from the ESP to the terminal (Uart1).
 */
void Uart2Byte_Callback( event_t *event ) {
    uart_event_t *evt = ( uart_event_t * )event;
    Uart1_PutAsync( evt->byte );
}

/**
 * Callback function of the command execution.
 * This function will be called when the command is executed.
 */
void Cmd_Callback( event_t *event ) {
    esp_event_t *evt = ( esp_event_t * )event;
    Uart1_PrintfAsync( "\nCommand [%s] executed.\n", evt->command );
    Led_Flash( LED_ID_0, 50 );
    Beep_Play( 50, 4000 );
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
    Uart1_WriteAsync( "\nPress a switch and check the result.\n" );

    /**
     * Initializes the Uart2 (For ESP8266 moduel).
     */
    Uart2_Init( 115200, 256, 256 );

    /**
     * Set the byte received callback function to the Uart2.
     */
    Uart2_SetRxCallback( Uart2Byte_Callback );

    /**
     * Set callback function to all switches.
     */
    int16_t i;
    for( i = PSW_ID_0; i <= PSW_ID_3; i++ ) {
        Psw_SetKeyDownCallback( i, PSWx_Callback );
    }

    /**
     * Initializes the ESP without reseting (false).
     */
    Esp_Init( false );

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
