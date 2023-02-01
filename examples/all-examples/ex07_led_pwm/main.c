/************************************************************
 * Example 7. LED PWM-based Blinking Control Function       *
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
     * Intianlizes the system.
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
     * Using PWM-based LED blinking control function.
     *  - The 2nd parameter is shift-time of delay-time (in milliseconds).
     *  - The 3rd parameter is on-time, the interval of ON state (in milliseconds).
     *  - The 4th parameter is total time, t_on + t_off (in milliseconds).
     */
    Led_Pwm( LED_ID_0, 400, 100, 1000 );     // Wait for 400 mS and then make the LED0 blinking 1.0 Hz, T-ON is 100.
    Led_Pwm( LED_ID_1, 300, 200, 1000 );     // Wait for 300 mS and then make the LED1 blinking 1.0 Hz, T-ON is 200.
    Led_Pwm( LED_ID_2, 200, 300, 1000 );     // Wait for 200 mS and then make the LED2 blinking 1.0 Hz, T-ON is 300.
    Led_Pwm( LED_ID_3, 100, 400, 1000 );     // Wait for 100 mS and then make the LED3 blinking 1.0 Hz, T-ON is 400.



    /**
     *                        100mS            1000 mS
     *             400mS      +----+                              +----   ON
     * LED0   ________________|    |_____________.________________|  =>   OFF
     *
     *            300mS   +--------+                          +--------   ON
     * LED1   ____________| 200mS  |_____________.____________|      =>   OFF
     *
     *         20 mS  +------------+                      +------------   ON
     * LED2   ________|   300mS    |_____________.________|          =>   OFF
     *
     *      100mS +----------------+                  +----------------   ON
     * LED3   ____|     400mS      |_____________.____|              =>   OFF
     *
     *
     * Note:
     *  The diagram represents ON/OFF status not logic levels.
     *  The logic level are inverted (LEDs are the Active-Low)
     */


    /**
     * Note:
     * After the Led_Pwm() function is called, the output pin connected to the LED
     * is controlled by the system. The basic control functions cannot be used.
     * To stop the PWM-based blink, call the Led_SetMode() function.
     * For example Led_SetMode( LED_ID_0, LED_MODE_LED ). After this function is executed,
     * The basic control functions can be used again.
     */

    /**
     * Ex2.
     * Set the operation of the LED to normal operation.
     * It is now can be controlled by normal control functions.
     */
    Led_SetMode( LED_ID_0, LED_MODE_LED );



    /**
     * Ex3.
     * Set the operation of the LED to PWM-based blinking again.
     * It is now blinking agran.
     */
    Led_SetMode( LED_ID_0, LED_MODE_PWM );



    /**
     * Note:
     *  The LEDs can be set to perform in 4 different modes/states:
     *  - LED_MODE_LED : Normal operation, control by a user.
     *  - LED_MODE_FLS : Flashing operation, controlled by system.
     *  - LED_MODE_BLK : Blinking operation, controlled by system.
     *  - LED_MODE_PWM : PWM-based blinking operation, controlled by the system.
     *
     * The operation modes will be changed by the system depended on the function that we call.
     * If the LED is running in PWM-based blinking, it cannot be controlled by the normal
     * control function.
     *
     * If the Led_Flash() is called the operation mode will be changed to LED_MODE_FLS and back to LED_MODE_LED automatically.
     * If the Led_Blink() is called the operation mode will be changed to LED_MODE_FLS and back to LED_MODE_LED automatically.
     */


    /**
     * Ex4.
     * While the LED is working in PWM-based mode,
     * The Led_Flash() and/or Led_Blink can be called.
     * After the flashing and/or blinking operation is completed,
     * the operation mode of the LED will be chabged back to the normal operation.
     */
    Led_Flash( LED_ID_0, 200 );
    Led_Blink( LED_ID_1, 200, 500 );


    /**
     * Turn them back to PWM-based blinking again.
     */
    Led_SetMode( LED_ID_0, LED_MODE_PWM );
    Led_SetMode( LED_ID_1, LED_MODE_PWM );


    /**
     * Note:
     *  The On-time of LED0 is overwritten by the Led_Flash().
     *  The On-time and Shift-time of LED1 are overwritten by the Led_Blink().
     *  The PWM-based blinking should be re-initialized again.
     */

    Led_Pwm( LED_ID_0, 400, 100, 1000 );     // Wait for 400 mS and then make the LED0 blinking 1.0 Hz, T-ON is 100.
    Led_Pwm( LED_ID_1, 300, 200, 1000 );     // Wait for 300 mS and then make the LED1 blinking 1.0 Hz, T-ON is 200.


    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
