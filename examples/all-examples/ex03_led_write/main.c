/************************************************************
 * Example 3. LED Control Functions (Writing Functions)     *
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
     * Access the target LED specified by function name.
     */
    Led0_Set();                         // Turn ON  the LED0.
    Led1_Set();                         // Turn OFF the LED1.
    Led2_Inv();                         // Invert/Toggle status of the LED2 (change to opposite status).
    bool led3 = Led3_Get();             // Get status (LED_ON or LED_OFF) of the LED3.


    /**
     * Ex2.
     * Access the target LED specified by its ID.
     */
    Led_Set( LED_ID_0 );                // Turn ON  the LED0.
    Led_Clr( LED_ID_1 );                // Turn OFF the LED1.
    Led_Inv( LED_ID_2 );                // Invert/Toggle status of the LED2 (change to opposite status).
    bool bit3 = Led_Get( LED_ID_3 );    // Get status (LED_ON or LED_OFF) of the LED3.


    /**
     * Ex3.
     * Control LED status specified by function name and value.
     */
    Led0_Wrt( LED_ON );                 // Turn ON  the LED0.
    Led1_Wrt( LED_OFF );                // Turn OFF the LED1.
    Led2_Wrt( false );                  // Turn ON  the LED2 (it is the Active-Low LED).
    Led3_Wrt( true );                   // Turn OFF the LED3 (it is the Active-Low LED).
    Led0_Wrt( 0 );                      // Turn ON  the LED0 (it is the Active-Low LED).
    Led1_Wrt( 1 );                      // Turn OFF the LED1 (it is the Active-Low LED).


    /**
     * Ex4.
     * Control LED status specified by ID and value.
     */
    Led_Wrt( LED_ID_0, LED_ON );        // Turn ON  the LED0.
    Led_Wrt( LED_ID_1, LED_OFF );       // Turn OFF the LED1.
    Led_Wrt( LED_ID_2, false );         // Turn ON  the LED2 (it is the Active-Low LED).
    Led_Wrt( LED_ID_3, true );          // Turn OFF the LED3 (it is the Active-Low LED).
    Led_Wrt( LED_ID_0, 0 );             // Turn ON  the LED0 (it is the Active-Low LED).
    Led_Wrt( LED_ID_1, 1 );             // Turn OFF the LED1 (it is the Active-Low LED).


    /**
     * Ex5.
     * Control status of LEDs specified by a control byte data.
     * Bit4 to bit7 are ignored.
     * Note of this function:
     *  - logic 1 of bit-data means ON.
     *  - logic 0 of bit-data means OFF.
     */
    Led_Write( 0x01 );                  // Write data 0x01 (0001) to LEDs (Only LED0 is turned ON).
    Led_Write( 0x03 );                  // Write data 0x03 (0011) to LEDs (LED0 & LED1 are turned ON).
    Led_Write( 0x07 );                  // Write data 0x07 (0111) to LEDs (Only LED3 is tuened OFF).
    Led_Write( 0x0F );                  // Write data 0x0F (1111) to LEDs (ALL LEDs are turned ON).


    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
