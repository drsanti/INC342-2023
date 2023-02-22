/************************************************************
 * Example 14. Switches (Keys) and Callbacks                *
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
 * KeyUp callback function.
 */
void KeyUp_Callback( event_t *event ) {
    Led_Set( LED_ID_0 );
}

/**
 * KeyDown callback function.
 */
void KeyDown_Callback( event_t *event ) {
    Led_Clr( LED_ID_0 );
}

/**
 * KeyHold callback function.
 */
void KeyHold_Callback( event_t *event ) {
    Beep_Play( 3000, 50 );
}

/**
 * KeyLock callback function.
 */
void KeyLock_Callback( event_t *event ) {
    Led_Inv( LED_ID_2 );
    Beep_Play( 6000, 20 );
}

/**
 * KeyChanged callback function.
 */
void KeyStateChanged_Callback( event_t *event ) {
    Led_Flash( LED_ID_3, 1 );
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
     * Ex1.
     * Set the KeyDown callback function to the PSW0.
     * The KeyUp_Callback function will be called when the PSW0 is pressed (down).
     */
    Psw_SetKeyDownCallback( PSW_ID_0, KeyUp_Callback   );


    /**
     * Ex2.
     * Set the KeyUp callback function to the PSW0.
     * The KeyUp_Callback function will be called when the PSW0 is released (up).
     */
    Psw_SetKeyUpCallback  ( PSW_ID_0, KeyUp_Callback );


    /**
     * Ex3.
     * Set the KeyHold callback function to the PSW1.
     * The KeyHold_Callback function will be called when the PSW1 is pressed and not released (hold).
     */
    Psw_SetKeyHoldCallback( PSW_ID_1, KeyHold_Callback );


     /**
     * Ex4.
     * Set the KeyLock callback function to the PSW2.
     * The KeyLock_Callback function will be called when the PSW2 is pressed and not released (still hold).
     * The frequency of callback function execution will be increased over time.
     */
    Psw_SetKeyLockCallback( PSW_ID_2, KeyLock_Callback );


    /**
     * Ex5.
     * Set the KeyChanged callback function to the PSW2.
     * The KeyChanged_Callback function will be called when the state of the PSW3 is changed.
     * The KeyChanged can be the following:
     *  - UP    ->  DOWN
     *  - DOWN  ->  UP
     *  - DOWN  ->  HOLD
     *  - HOLD  ->  UP
     *  - HOLD  ->  LOCK
     *  - LOCK  ->  UP
     * (See in the next example for more details)
     */
    Psw_SetKeyChangedCallback( PSW_ID_3, KeyStateChanged_Callback );


    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
