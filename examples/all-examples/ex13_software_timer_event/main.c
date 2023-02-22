/************************************************************
 * Example 13. Software Timer and Event                     *
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
 * Callback function of all timers.
 */
void Tx_Callback( event_t *event ) {

    /**
     * Get the event of the timer.
     */
    timer_event_t *evt = ( timer_event_t * )event;


    /**
     * Flash the LED specified by the id of the timer.
     * We created 4 timers, therefore, the id can be 0, 1, 2 and 3.
     * The timer id is mapped to the LED id.
     */
    Led_Flash( evt->id, 2 );   // Flash the LED0<id>


    /**
     * Each timer has its own internal counter increased when the timeout is occurred.
     * It also has a context pointer that can point to anything. We can use the
     * internal counter and the context for various applications.
     */
    if( evt->id >= 2 ) {
        if( evt->counter % 5 == 0 ) {
            Beep_Play( 50, *(float *)evt->context );
        }
    }
}


/************************************************************
 * Main function
 ************************************************************/
int main( void ) {

    /*
     * Initializes the system.
     */
    System_Init();


    /**
     * Data to be used as beep frequency.
     * These data are passed to the callback of the
     * timer using the context pointer of the timer.
     */
    float freqs[] = { 2000, 4000, 5000, 8000 };

    /**
     * Create 4 timers with different timeout and give them the same callback function.
     */
    int16_t i;
    for( i = 0; i < 4; i++ ) {
        timer_t *t = Timer_Create( 100 + i*200, Tx_Callback );
        t->context = &freqs[i];
    }


    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
