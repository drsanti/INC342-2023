/************************************************************
 * Example 6. LED Blinking Control Function                 *
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


/************************************************************
 * Main function
 ************************************************************/
int main(void) {

    /*
     * Initializes the system.
     */
    System_Init();


    /**
     * Note:
     * There are 4 Active-Low LEDs on the experiment board.
     * Each LED has its own id:
     *  - LED_ID_0 is the LED0 (connected to digital output channel 0).
     *  - LED_ID_1 is the LED1 (connected to digital output channel 1).
     *  - LED_ID_2 is the LED2 (connected to digital output channel 2).
     *  - LED_ID_3 is the LED3 (connected to digital output channel 3).
     * The LEDs support both read and write operations.
     * The statuses of an LED (on, off) are defined by LED_ON and LED_OFF respectively.
     */



    /**
     * Ex1.
     * Using LED blinking control function.
     *  - The second parameter is shift-time of delay-time (in milliseconds).
     *  - The third parameter is on-time, the interval of ON state (in milliseconds).
     */
    Led_Blink( LED_ID_0, 400, 100 );     // Wait for 400 mS and then turn ON the LED0 for 100 mS, then, turn OFF.
    Led_Blink( LED_ID_1, 300, 200 );     // Wait for 300 mS and then turn ON the LED1 for 200 mS, then, turn OFF.
    Led_Blink( LED_ID_2, 200, 300 );     // Wait for 200 mS and then turn ON the LED2 for 300 mS, then, turn OFF.
    Led_Blink( LED_ID_3, 100, 400 );     // Wait for 100 mS and then turn ON the LED3 for 400 mS, then, turn OFF.


    /**
     *                        100mS
     *             400mS      +----+        ON
     * LED0   ________________|    |____    OFF
     *
     *            300mS   +--------+        ON
     * LED1   ____________| 200mS  |____    OFF
     *
     *         20 mS  +------------+        ON
     * LED2   ________|   300mS    |____    OFF
     *
     *      100mS +----------------+        ON
     * LED3   ____|     400mS      |____    OFF
     *
     *
     * Note:
     *  The diagram represents ON/OFF status not logic levels.
     *  The logic level are inverted (LEDs are the Active-Low)
     */


    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
