/************************************************************
 * Example 5. LED Flashing Control Functions                *
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
     * Using LED flashing control function.
     */
    Led_Flash( LED_ID_0, 100 );     // Turn ON LED0 for 100 mS, then turn OFF.
    Led_Flash( LED_ID_1, 200 );     // Turn ON LED1 for 200 mS, then turn OFF.
    Led_Flash( LED_ID_2, 300 );     // Turn ON LED2 for 300 mS, then turn OFF.
    Led_Flash( LED_ID_3, 400 );     // Turn ON LED3 for 400 mS, then turn OFF.


    /**
     *      100 mS
     *      +----+                          ON
     * LED0 |    |________________________  OFF
     *
     *      +--------+                      ON
     * LED1 | 200 mS |____________________  OFF
     *
     *      +------------+                  ON
     * LED2 |   300 mS   |________________  OFF
     *
     *      +----------------+              ON
     * LED3 |     400 mS     |____________  OFF
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
