/************************************************************
 * Example 12. Software Timers                              *
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
 * Pointers to timer objects.
 */
timer_t *t1, *t2;


/**
 * Callback function of timer t1.
 */
void T1_Callback( event_t *event ) {

    Led_Flash( LED_ID_0, 5 );   // Flash the LED0
}

/**
 * Callback function of timer t2.
 */
void T2_Callback( event_t *event ) {

    // static int cnt = 0;         // Counter variable.

    // Led_Flash( LED_ID_3, 5 );   // Flash the LED3.

    // ++cnt;                      // Increase the counter by 1.

    // if( cnt == 5 ) {            // If the cnt == 5,
    //     Timer_Delete( t1 );     // Delete the timer t1 (delete another).
    // }

    // if( cnt == 10 ) {           // If the cnt == 10,
    //     Timer_Delete( t2 );     // Delete the timer t2 (self-deleting).
    // }

    Uart1_Printf( "ADC1 value changed detected, value: %4d.\r\n", Adc1_Get() );


}


/************************************************************
 * Main function
 ************************************************************/
int main( void ) {

    /*
     * Intianlizes the system.
     */
    System_Init();


    /**
     * Note:
     * In this system, 10 software timers are allowed.
     */


    /**
     * Create two software timers, t1 and t2.
     * Each timer has its own callback function.
     */
    t1 = Timer_Create(  100, T1_Callback ); // Execute the callback function, T1_Callback, every 100 mS.
    t2 = Timer_Create( 1000, T2_Callback ); // Execute the callback function, T1_Callback, every 1000 mS.


    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
