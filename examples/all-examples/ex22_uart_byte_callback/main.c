/************************************************************
 * Example 22. Uart Byte Received Callback                  *
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
 * Callback function of Uart1 byte received.
 * This function called by CoRutine or BSP executor.
 */
void Rx_Callback( void *event ) {
    Led_Flash( LED_ID_0, 1 );
    Uart1_WriteAsync("rxd\r\n");
}

/**
 * Callback function of Uart1 ISR byte received.
 * This function called from RX ISR (byte received interrupt).
 * Be careful to write code in the ISR called function.
 */
void RxISR_Callback( void *event ) {
    Led_Flash( LED_ID_1, 1 );
    Uart1_WriteAsync( "isr\r\n" );
}

/**
 * Callback function of Uart1 asynchronous buffer empty.
 * This function will be called when the asynchronous buffer is empty.
 */
void Tx_Callback( void *event ) {
    Led_Flash( LED_ID_2, 1 );
    Beep( 20 );
}

void TxRx_FullCallback( void *event ) {
    Uart1_Write( "buffer full!\r\n" );
}


/************************************************************
 * Main function
 ************************************************************/
int main(void) {

    /*
     * Initializes the system.
     */
    System_Init();

    /**
     * Initializes the Uart1. Used to check the results.
     * Run the command line with -monitor option to see the results.
     * e.g., ecc-pic24-cli -build -flash -monitor
     */
    Uart1_Init( 115200, 32, 64 );


    /**
     * Set the RxCallback (byte received) function to the Uart1.
     */
    Uart1_SetRxCallback( Rx_Callback );


    /**
     * Set the RxIsrCallback (ISR byte received) function to the Uart1.
     */
    Uart1_SetRxIsrCallback( RxISR_Callback );


    /**
     * Set the TxCallback function to the Uart1.
     * The callback function will be called when the
     * asynchronous buffer is empty. For example, after the function
     * Uart_WriteAsync("hello") is called and the lasted character, 'o' is
     * written to the TXREG, the callback function is called.
     */
    Uart1_SetTxCallback ( Tx_Callback );

     /**
     * Set the BufferFullCallback function to the Uart1.
     * The callback function will be called when one of the asynchronous buffer
     * of TX or RX is full (no space to put a new byte). For example, if in that time
     * the TX buffer has 2 bytes of free spaces, and the Uart_WriteAsync("hello") is called,
     * this callback function will be called to inform that "no more space in this time".
     */
    Uart1_SetBufferFullCallback( TxRx_FullCallback );


    /**
     * Note:
     * The Uart2 can be used in the same way.
     */


    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
