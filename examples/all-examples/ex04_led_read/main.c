/************************************************************
 * Example 4. LED Control Functions (Reading Functions)     *
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
     * Get status of target LED specified by the function name.
     */
    bool d0 = Led0_Get();                   // Get status (LED_OFF or LED_ON) of LED0.
    bool d1 = Led1_Get();                   // Get status (LED_OFF or LED_ON) of LED1.
    bool d2 = Led2_Get();                   // Get status (LED_OFF or LED_ON) of LED2.
    bool d3 = Led3_Get();                   // Get status (LED_OFF or LED_ON) of LED3.


    /**
     * Ex2.
     * Access the target LED specified by its ID.
     */
    bool bit0 = Led_Get( LED_ID_0 );        //  Get status (LED_OFF or LED_ON) of LED0.
    bool bit1 = Led_Get( LED_ID_1 );        //  Get status (LED_OFF or LED_ON) of LED1.
    bool bit2 = Led_Get( LED_ID_2 );        //  Get status (LED_OFF or LED_ON) of LED2.
    bool bit3 = Led_Get( LED_ID_3 );        //  Get status (LED_OFF or LED_ON) of LED3.


    /**
     * Ex3.
     * Read all status bits of the LEDs.
     * Bit4 to Bit7 are ignored (read as zeros).
     */
    uint8_t bits = Dinp_Read();


    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
