/************************************************************
 * Example 21. Beep Callback Function and Event             *
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
 * Callback function of the Beep sound ending.
 * When it ends playing a note, make it play the next one.
 */
void Beep_Callback( void *event ) {

    /**
     * Beep frequency values for different notes.
     */
    const float Notes[] = {
        BEEP_Do, BEEP_Re, BEEP_Me, BEEP_Fa,
        BEEP_So, BEEP_La, BEEP_Si, BEEP_DO
    };

    beep_event_t *evt = ( beep_event_t * )event;    // Get the event.

    uint16_t idx = evt->counter % (sizeof(Notes) / sizeof(float) );
    float freq   = Notes[idx] * 1.5;                // Get the frequency.
    Beep_Play( 400, freq );                         // Play the target note.

    Uart1_Printf("idx: %d, freq: %4.2f\r\n", idx, freq); // Print the information.
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
     * Set a callback function to the beep.
     * The callback function will be called
     * at the end of the beep sound.
     */
    Beep_SetCallback( Beep_Callback );

    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
