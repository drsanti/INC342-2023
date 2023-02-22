/************************************************************
 * Example 15. Switches (Keys) and Events                   *
 ************************************************************
 * File:    main.c                                          *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 ************************************************************
 * Update:  01 March 2020 (Initial version)                 *
 ************************************************************/


/************************************************************
 * Include the system header.
 ************************************************************/
#include <ecc.h>


/**
 * KeyDown callback function of all switches.
 */
void KeyDown_Callback( event_t *event ) {
    switch_event_t *evt = ( switch_event_t * )event;
    Led_Inv( evt->id );
    Uart1_Printf( "LED%d %s\r\n", evt->id, Led_Get( evt->id ) ? "ON" : "OFF" );
    Beep_Play( 20, 3000 );
}


/**
 * KeyChanged callback function of all switches.
 */
void KeyChanged_Callback( event_t *event ) {
    switch_event_t *evt = ( switch_event_t * )event;
    Uart1_Printf( "Key id: %d, state: %s\r\n", evt->id, evt->sname );
    Beep_Play( 20, 6000 );
}

/************************************************************
 * Main function
 ************************************************************/
int main(void) {

    /*
     * Initializes the system.
     */
    System_Init();

    /**
     * Initializes the Uart1. Used to check the results.
     * Run the command line with -monitor option to see the results.
     * e.g., ecc-pic24-cli -build -flash -monitor
     */
    Uart1_Init( 115200, 32, 64 );


    /**
     * Set the KeyDown and KeyChanged callback functions to all switches.
     */
    int16_t i;
    for(i = PSW_ID_0; i<= PSW_ID_3; i++) {
        Psw_SetKeyDownCallback   ( i, KeyDown_Callback    );
        Psw_SetKeyChangedCallback( i, KeyChanged_Callback );
    }


    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
