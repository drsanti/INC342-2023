/************************************************************
 * Example 9. UART1 and UART2 Basic Functions               *
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
int main( void ) {
    /*
     * Intianlizes the system.
     */
    System_Init();

    /**
     * Note:
     * There are two UARTs in this system, Uart1 (UART_ID_1) and Uart2 (UART_ID_2).
     * Both of them have the functions and operations.
     * In this example, only basic functions are explained. For more advanced function,
     * Please check in other examples for more details.
     */

    /**
     * Ex1.
     * Initialize Uart1 and Uart2.
     *  - 1st parameter is the baudrate.
     *  - 2nd parameter is the buffer size of the receiver (used for asynchronous operation).
     *  - 3rd parameter is the buffer size of the transmitter (used for asynchronous operation).
     */
    Uart1_Init( 115200, 32, 128 );  // Initializes Uart1, to operate at 115200 baudrate and set RX and TX buffer to 32 and 128 bytes.
    Uart2_Init( 9600, 64, 64 );     // Initializes Uart2, to operate at   9600 baudrate and set RX and TX buffer to 63 and  64 bytes.

    /**
     * Ex2.
     * Synchronous Put a byte (character) to the Uart.
     */
    Uart1_Put( 'a' );  // Put character 'a' to Uart1
    Uart2_Put( 'a' );  // Put character 'a' to Uart2

    /**
     * Ex3.
     * Synchronous Write a string (array of charecters) to the Uart.
     */
    Uart1_Write( "\r\nhello" );  // Write a message "hello" to Uart1.
    Uart2_Write( "hello\r\n" );  // Write a message "hello" to Uart2.

    /**
     * Ex4.
     * Synchronous Print formated string to the Uart.
     */
    int x    = 20;
    double y = x / 1.23;

    Uart1_Printf( "x: %2d, y: %.3f\r\n", x, y );  // Print a formated string to Uart1.
    Uart2_Printf( "x: %2d, y: %.3f\r\n", x, y );  // Print a formated string to Uart2.

    /**
     * Ex5.
     * Asynchronous Put a byte (character) to the Uart.
     */
    Uart1_PutAsync( 'A' );  // Put character 'A' to Uart1
    Uart2_PutAsync( 'A' );  // Put character 'A' to Uart2

    /**
     * Ex6.
     * Asynchronous Write a string (array of charecters) to the Uart.
     */
    Uart1_WriteAsync( "\r\nHELLO" );  // Write a message "HELLO" to Uart1.
    Uart2_WriteAsync( "HELLO\r\n" );  // Write a message "hello" to Uart2.

    /**
     * Ex7.
     * Asynchronous Print formated string to the Uart.
     */
    Uart1_PrintfAsync( "X: %2d, Y: %.3f\r\n", x, y );  // Print a formated string to Uart1.
    Uart2_PrintfAsync( "X: %2d, Y: %.3f\r\n", x, y );  // Print a formated string to Uart2.

    /**
     * Ex8.
     * Synchronous Get a byte (character) from Uart.
     * WARNING : These functions block CPU until a byte is received.
     *           It is recommended to use the byte received callback function instead.
     *           Check in other examples of using Uarts for more details.
     */
    char c1, c2;
    Uart1_Get( &c1 );
    Uart2_Get( &c2 );

    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
