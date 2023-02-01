/************************************************************
 * File:    BSP_Led.h                                       *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  16 February 2020                                *
 * Update:  24 February 2020                                *
 *          Added Led_Wrt function                          *
 ************************************************************/


#ifndef __BSP_LED_H__

    #define __BSP_LED_H__

    #include <BSP_Mcu.h>

    /*******************************************************
     * LED IDs
     *******************************************************/
    #define LED_ID_0        0   // ID of the LED 0.
    #define LED_ID_1        1   // ID of the LED 1.
    #define LED_ID_2        2   // ID of the LED 2.
    #define LED_ID_3        3   // ID of the LED 3.

    /*******************************************************
     * LED IDs
     *******************************************************/
    #define LED_MAX_COUNT   4   // Number of LEDs.

    /*******************************************************
     * LED STATUS (ACTIVE LOW)
     *******************************************************/
    #define LED_ON          0   // LED ON  status.
    #define LED_OFF         1   // LED OFF status.

    /*******************************************************
     * LED TRIS DIRECTION
     *******************************************************/
    #define LED_TRIS_OUT    0   // TRIS register outout direction value.
    #define LED_TRIS_INP    1   // TRIS register input direction value.

    /*******************************************************
     * LED TRIS
     *******************************************************/
    #define LED0_TRIS   TRISAbits.TRISA2    // LED0 TRIS register (bit TRISA2).
    #define LED1_TRIS   TRISAbits.TRISA4    // LED1 TRIS register (bit TRISA4).
    #define LED2_TRIS   TRISBbits.TRISB2    // LED2 TRIS register (bit TRISB2).
    #define LED3_TRIS   TRISBbits.TRISB3    // LED3 TRIS register (bit TRISB3).

    /*******************************************************
     * LED LAT (USED FOR WRITING)
     *******************************************************/
    #define LED0_LAT    LATAbits.LATA2      // LED0 LAT register (bit LATA2).
    #define LED1_LAT    LATAbits.LATA4      // LED1 LAT register (bit LATA4).
    #define LED2_LAT    LATBbits.LATB2      // LED2 LAT register (bit LATB2).
    #define LED3_LAT    LATBbits.LATB3      // LED3 LAT register (bit LATB3).

    /*******************************************************
     * LED PORT (USED FOR READING)
     *******************************************************/
    #define LED0_PORT   PORTAbits.RA2       // LED0 PORT register (bit RA2).
    #define LED1_PORT   PORTAbits.RA4       // LED0 PORT register (bit RA4).
    #define LED2_PORT   PORTBbits.RB2       // LED0 PORT register (bit RB2).
    #define LED3_PORT   PORTBbits.RB3       // LED0 PORT register (bit RB3).


    /*******************************************************
     * LED SET MACROS
     *******************************************************/
    #define Led0_Set() ( LED0_LAT=LED_ON )  // Turn LED0 ON.
    #define Led1_Set() ( LED1_LAT=LED_ON )  // Turn LED1 ON.
    #define Led2_Set() ( LED2_LAT=LED_ON )  // Turn LED2 ON.
    #define Led3_Set() ( LED3_LAT=LED_ON )  // Turn LED3 ON.

     /*******************************************************
     * LEDs CLR MACROS
     *******************************************************/
    #define Led0_Clr() ( LED0_LAT=LED_OFF)  // Turn LED0 OFF.
    #define Led1_Clr() ( LED1_LAT=LED_OFF)  // Turn LED1 OFF.
    #define Led2_Clr() ( LED2_LAT=LED_OFF)  // Turn LED2 OFF.
    #define Led3_Clr() ( LED3_LAT=LED_OFF)  // Turn LED3 OFF.

    /*******************************************************
     * LEDs INV MACROS
     *******************************************************/
    #define Led0_Inv() ( LED0_LAT=!LED0_PORT) // Invert/Toggle status of LED0.
    #define Led1_Inv() ( LED1_LAT=!LED1_PORT) // Invert/Toggle status of LED1.
    #define Led2_Inv() ( LED2_LAT=!LED2_PORT) // Invert/Toggle status of LED2.
    #define Led3_Inv() ( LED3_LAT=!LED3_PORT) // Invert/Toggle status of LED3.

    /*******************************************************
     * LEDs GET MACROS
     *******************************************************/
    #define Led0_Get() ( !LED0_PORT )       // Get status (LED_ON or LED_OFF) of LED0.
    #define Led1_Get() ( !LED1_PORT )       // Get status (LED_ON or LED_OFF) of LED1.
    #define Led2_Get() ( !LED2_PORT )       // Get status (LED_ON or LED_OFF) of LED2.
    #define Led3_Get() ( !LED3_PORT )       // Get status (LED_ON or LED_OFF) of LED3.



    /*******************************************************
     * LEDs WRITE MACROS
     *******************************************************/
    #define Led0_Wrt( data )  Led_Wrt( LED_ID_0, data ) // Write bit data to LED0.
    #define Led1_Wrt( data )  Led_Wrt( LED_ID_1, data ) // Write bit data to LED2.
    #define Led2_Wrt( data )  Led_Wrt( LED_ID_2, data ) // Write bit data to LED3.
    #define Led3_Wrt( data )  Led_Wrt( LED_ID_3, data ) // Write bit data to LED4.


    /*******************************************************
     * Led_Set
     * Turns on the LED specified by the id.
     * Parameter:
     * - id: Id of the target LED (LED_ID_0,..., LED_ID_3).
     *******************************************************/
    void Led_Set(uint8_t id);


    /*******************************************************
     * Led_Clr
     * Turns off the LED specified by the id.
     * Parameter:
     * - id: Id of the target LED (LED_ID_0,..., LED_ID_3).
     *******************************************************/
    void Led_Clr(uint8_t id);


    /*******************************************************
     * Led_Wrt
     * Writes 1-bit of data to the LED specified by the id.
     * Parameter:
     * - id: Id of the target LED (LED_ID_0,..., LED_ID_3).
     * - data: A 1-bit data to be written to the target LED.
     *******************************************************/
    void Led_Wrt(uint8_t id, bool data);

    /*******************************************************
     * Led_Inv
     * Inverses or toggle the LED specified by the id.
     * Return the current status of the target LED.
     * Parameter:
     * - id: Id of the target LED (LED_ID_0,..., LED_ID_3).
     *******************************************************/
    bool Led_Inv(uint8_t id);


    /*******************************************************
     * Led_Get
     * Returns status of the LED (LED_ON or LED_OFF) specified by the id.
     * Parameter:
     * - id: Id of the target LED (LED_ID_0,..., LED_ID_3).
     *******************************************************/
    bool Led_Get(uint8_t id);


    /*******************************************************
     * Led_Write
     * Writes a byte data to the LEDs (Only 4-bit LSB are taken).
     * Parameter:
     * - data: A byte data (0x00 - 0x0F).
     *******************************************************/
    void Led_Write(uint8_t data);


    /*******************************************************
     * Led_Read
     * Returns a byte data of the LEDs (0x00 - 0x0F).
     *******************************************************/
    uint8_t Led_Read(void);

#endif // __BSP_LED_H__
