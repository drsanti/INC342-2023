/************************************************************
 * File:    BSP_Uart.ch                                     *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  16 February 2020                                *
 * Update:  24 February 2020                                *
 *          Added line detector & UartX_SetRxLineCallback() *
 ************************************************************
 * Update:  26 February 2020 (see Note1)                    *
 * Update:  01 March 2020                                   *
 *          Add ready flag to uart structure to prevent the *
 *          uninitialized problems in the executor          *
 ************************************************************/


#ifndef __BSP_UART_H__

    #define __BSP_UART_H__

    #include <BSP_Config.h>
    #include <BSP_Queue.h>


    /*******************************************************
     * UART IDs
     *******************************************************/
    #define UART_ID_1   1
    #define UART_ID_2   2


    /*******************************************************
     * U1 TX&RX ISRs CONTROL
     *******************************************************/
    #define UART1_TX_ISR_ENABLE()       ( IEC0bits.U1TXIE = 1 )
    #define UART1_TX_ISR_DISABLE()      ( IEC0bits.U1TXIE = 0 )
    #define UART1_RX_ISR_ENABLE()       ( IEC0bits.U1RXIE = 1 )
    #define UART1_RX_ISR_DISABLE()      ( IEC0bits.U1RXIE = 0 )



    /*******************************************************
     * U2 TX&RX ISRs CONTROL
     *******************************************************/
    #define UART2_TX_ISR_ENABLE()       ( IEC1bits.U2TXIE = 1 )
    #define UART2_TX_ISR_DISABLE()      ( IEC1bits.U2TXIE = 0 )
    #define UART2_RX_ISR_ENABLE()       ( IEC1bits.U2RXIE = 1 )
    #define UART2_RX_ISR_DISABLE()      ( IEC1bits.U2RXIE = 0 )



    #define Uart1_SetRxIsr( enabled )   ( IEC0bits.U1RXIE = enabled )
    #define Uart1_SetTxIsr( enabled )   ( IEC0bits.U1TXIE = enabled )

    #define Uart2_SetRxIsr( enabled )   ( IEC1bits.U2RXIE = enabled )
    #define Uart2_SetTxIsr( enabled )   ( IEC1bits.U2TXIE = enabled )


    /*******************************************************
     * UART1 TX&RX BUFFER LENGTH
     *******************************************************/
    //#define U1TX_BUFF_LENGTH    256
    //#define U1RX_BUFF_LENGTH    128

    /*******************************************************
     * UART1 TX&RX BUFFER LENGTH
     *******************************************************/
    //#define U2TX_BUFF_LENGTH    256
    //#define U2RX_BUFF_LENGTH    128




    /*******************************************************
     * UARTx BUFFER LENGTH for Uartx_Printf
     *******************************************************/
    #define PRINTF_BUFF_LENGTH  256 //!! Dont touch this value



    /*******************************************************
     * UART EVENT TYPES
     *******************************************************/
    #define EVT_UART_RX_ISR     0
    #define EVT_UART_TX_ISR     1 /* Not used for now      */
    #define EVT_UART_RX_STD     2
    #define EVT_UART_TX_STD     3 /* Not used for now      */
    #define EVT_UART_TX_EMP     4 /* Tx queue empty        */
    #define EVT_UART_RX_STR     5 /* Line (string) received*/

    #define EVT_UART_RX_ERR     0x10<<0 /* Rx queue full   */
    #define EVT_UART_TX_ERR     0x10<<1 /* Tx queue full   */


    /*******************************************************
     * LINE DETECTOR OBJECT STRUCTURE
     *******************************************************/
    typedef struct {
        int         state;          // State of line detection.
        int         index;          // Index of buffer.
        int         length;         // Buffer length in bytes.
        char        *buffer;        // Line queue object.
        callback_t  line_rcv_cbk;   // Line received callback performed outside the Tx ISR.
    }uart_line_t;


    /*******************************************************
     * UART OBJECT STRUCTURE
     *******************************************************/
    typedef struct {
        int         id;             // Id of the UART (UART_ID_1 or UART_ID_2).
        uint8_t     ready;          // Ready flag, set by Init function
        char        std_rxd;        // Rx data of queue buffer.
        char        isr_rxd;        // Rx data of Rx ISR.
        char        isr_txd;        // Tx data of Tx ISR.
        bool        txemp;          // Tx buffer empty flag.
        Queue       *rxqueue;       // Rx queue object.
        Queue       *txqueue;       // Tx queue object.

        uint16_t    rxqfullcnt;     // Rx queue full counter.
        uint16_t    txqfullcnt;     // Tx queue full counter.

        callback_t  rxd_isr_cbk;    // Rx ISR callback performed inside the Rx ISR.

        callback_t  rxd_std_cbk;    // Rx standard callback performed outside the Rx ISR.
        callback_t  txd_empty_cbk;  // Tx queue empty callback performed outside the Tx ISR.

        callback_t  queue_full_cbk; // Rx and Tx queue full callback.

        uart_line_t ln;

    }uart_t;


    /*******************************************************
     * UART EVENT OBJECT STRUCTURE
     *******************************************************/
    typedef struct {
        int     type;               // Uart event type.
        int     id;                 // Id of the UART (UART_ID_1 or UART_ID_2).
        char    byte;               // Received byte data.
        char    *line;              // Received string data (line).
        int     length;             // Number of bytes in the line.
        uart_t  *sender;            // Uart object.
    }uart_event_t;




    /*******************************************************
     * Uart1_Init
     * Initializes Uart1.
     * Parameter:
     * - baurate: Baudrate of the Uart1.
     * - rxBuffLength: RX buffer size in bytes.
     * - txBuffLength: TX buffer size in bytes.
     *******************************************************/
    void Uart1_Init(uint32_t baurate, uint16_t rxBuffLength, uint16_t txBuffLength);


    /*******************************************************
     * Uart2_Init
     * Initializes Uart2.
     * Parameter:
     * - baurate: Baudrate of the Uart2.
     * - rxBuffLength: RX buffer size in bytes.
     * - txBuffLength: TX buffer size in bytes.
     *******************************************************/
    void Uart2_Init(uint32_t baurate, uint16_t rxBuffLength, uint16_t txBuffLength);


    /*******************************************************
     * Uart_Init
     * Initializes the Uart specified by the id.
     * Parameter:
     * - id: Uart id (UART_ID_1 or UART_ID_2).
     * - baurate: Baudrate of the Uart1.
     * - rxBuffLength: RX buffer size in bytes.
     * - txBuffLength: TX buffer size in bytes.
     *******************************************************/
    void Uart_Init(int id, uint32_t baurate, uint16_t rxBuffLength, uint16_t txBuffLength);

    /*******************************************************
     * Uart1_Put
     * Put a byte data into the Uart1 TX register.
     * It waits until the previous byte is sent before puts the new one into the TX register.
     * Parameter:
     * - data: A byte data.
     *******************************************************/
    void Uart1_Put(char data);

    /*******************************************************
     * Uart2_Put
     * Put a byte data into the Uart2 register.
     * It waits until the previous byte is sent before puts the new one into the TX register.
     * Parameter:
     * - data: A byte data.
     *******************************************************/
    void Uart2_Put(char data);

    /*******************************************************
     * Uart1_Get
     * Get a byte of data from Uart1 RX register.
     * It waits until a byte is received and writes the received byte to the output variable (*data).
     * Parameter:
     * - data: Output byte data.
     *******************************************************/
    void Uart1_Get(char *data);

    /*******************************************************
     * Uart2_Get
     * Get a byte of data from Uart2 RX register.
     * It waits until a byte is received and writes the received byte to the output variable (*data).
     * Parameter:
     * - data: Output byte data.
     *******************************************************/
    void Uart2_Get(char *data);



    /*******************************************************
     * Uart1_Write
     * Write a string (array of characters) to the Uart1.
     * It waits until all bytes are sent.
     * Parameter:
     * - string: Array of characters.
     *******************************************************/
    void Uart1_Write(const char *string);

    /*******************************************************
     * Uart2_Write
     * Write a string (array of characters) to the Uart2.
     * It waits until all bytes are sent.
     * Parameter:
     * - string: Array of characters.
     *******************************************************/
    void Uart2_Write(const char *string);

    /*******************************************************
     * Uart1_WriteBytes
     * Writes multiple bytes to Uart1.
     * It waits until all bytes are sent.
     * Parameter:
     * - buffer: Array of characters.
     * - length: Number of bytes to be written.
     *******************************************************/
    void Uart1_WriteBytes( const char *buffer, uint16_t length );

    /*******************************************************
     * Uart2_WriteBytes
     * Writes multiple bytes to Uart2.
     * It waits until all bytes are sent.
     * Parameter:
     * - buffer: Array of characters.
     * - length: Number of bytes to be written.
     *******************************************************/
    void Uart2_WriteBytes( const char *buffer, uint16_t length );


    /*******************************************************
     * Uart1_PutAsync
     * Asynchronously put a byte data into the Uart1 TX register.
     * It puts the byte data into TX queue and returns immediately.
     * Returns zero if the TX queue is full.
     * Parameter:
     * - data: A byte data.
     *******************************************************/
    uint16_t Uart1_PutAsync(char data);


    /*******************************************************
     * Uart2_PutAsync
     * Asynchronously put a byte data into the Uart2 TX register.
     * It puts the byte data into TX queue and returns immediately.
     * Returns zero if the TX queue is full.
     * Parameter:
     * - data: A byte data.
     *******************************************************/
    uint16_t Uart2_PutAsync(char data);


    /*******************************************************
     * Uart1_WriteAsync
     * Asynchronously write a string (array of characters) to the Uart1.
     * It writes all bytes into TX queue and returns immediately.
     * Parameter:
     * - string: Array of characters.
     *******************************************************/
    uint16_t Uart1_WriteAsync(const char *string);

    /*******************************************************
     * Uart2_WriteAsync
     * Asynchronously write a string (array of characters) to the Uart2.
     * It writes all bytes into TX queue and returns immediately.
     * Parameter:
     * - string: Array of characters.
     *******************************************************/
    uint16_t Uart2_WriteAsync(const char *string);


    /*******************************************************
     * Uart1_Printf
     * Synchronously prints a formatted string to Uart1.
     * Parameter:
     * - format: The formatted string.
     * - ...: Additional parameters used to create the string.
     *******************************************************/
    void Uart1_Printf(const char *format, ...);

    /*******************************************************
     * Uart2_Printf
     * Synchronously prints a formatted string to Uart2.
     * Parameter:
     * - format: The formatted string.
     * - ...: Additional parameters used to create the string.
     *******************************************************/
    void Uart2_Printf(const char *format, ...);


     /*******************************************************
     * Uart1_PrintfAsync
     * Asynchronously prints a formatted string to Uart1.
     * Parameter:
     * - format: The formatted string.
     * - ...: Additional parameters used to create the string.
     *******************************************************/
    void Uart1_PrintfAsync(const char *format, ...);

    /*******************************************************
     * Uart2_PrintfAsync
     *  Asynchronously prints a formatted string to Uart2.
     * Parameter:
     * - format: The formatted string.
     * - ...: Additional parameters used to create the string.
     *******************************************************/
    void Uart2_PrintfAsync(const char *format, ...);


    /*******************************************************
     * Uart_Printf
     * Asynchronously prints a formatted string to the Uart specified by the id.
     * Parameter:
     * - id: Uart id (UART_ID_1 or UART_ID_2)
     * - format: The formatted string.
     * - ...: Additional parameters used to create the string.
     *******************************************************/
    void Uart_Printf(int id, const char *format, ...);



    /*******************************************************
     * Uart1_GetTxBufferSpace
     * Returns the free space (in buyes) of the Uart1 tx buffer.
     *******************************************************/
    int16_t Uart1_GetTxBufferSpace( void );

    /*******************************************************
     * Uart2_GetTxBufferSpace
     * Returns the free space (in buyes) of the Uart2 tx buffer.
     *******************************************************/
    int16_t Uart2_GetTxBufferSpace( void );

    /*******************************************************
     * Uart1_ClearTxBuffer
     * Clear tx buffer of Uart1.
     *******************************************************/
    void Uart1_ClearTxBuffer( void );

    /*******************************************************
     * Uart2_ClearTxBuffer
     * Clear tx buffer of Uart2.
     *******************************************************/
    void Uart2_ClearTxBuffer( void );

    /*******************************************************
     * Uart1_ClearRxBuffer
     * Clear rx buffer of Uart1.
     *******************************************************/
    void Uart1_ClearRxBuffer( void );

    /*******************************************************
     * Uart2_ClearRxBuffer
     * Clear rx buffer of Uart2.
     *******************************************************/
    void Uart2_ClearRxBuffer( void );


    /*******************************************************
     * Uart1_ClearLineBuffer
     * Clears line buffer of Uart1.
     *******************************************************/
    void Uart1_ClearLineBuffer(void);

    /*******************************************************
     * Uart2_ClearLineBuffer
     * Clears line buffer of Uart2.
     *******************************************************/
    void Uart2_ClearLineBuffer(void);



    /**
     * Sets Tx buffer size of the Uart1.
     * Parameter:
     * - txSize: Buffer size in bytes.
     */
    void Uart1_SetTxBuffer( uint16_t size );

    /**
     * Sets Rx buffer size of the Uart1.
     * Parameter:
     * - size: Buffer size in bytes.
     */
    void Uart1_SetRxBuffer( uint16_t size );

    /**
     * Sets Tx buffer size of the Uart2.
     * Parameter:
     * - size: Buffer size in bytes.
     */
    void Uart2_SetTxBuffer( uint16_t size );

    /**
     * Sets Rx buffer size of the Uart2.
     * Parameter:
     * - size: Buffer size in bytes.
     */
    void Uart2_SetRxBuffer( uint16_t size );


    //
    // ISR CALLBACKS
    //


    /*******************************************************
     * Uart1_SetRxIsrCallback
     * Set ISR callback function the Uart1 byte received.
     * Parameter:
     * - callback: Callback function of the Uart1 byte received.
     *******************************************************/
    void Uart1_SetRxIsrCallback(callback_t callback);

    /*******************************************************
     * Uart2_SetRxIsrCallback
     * Set ISR callback function the Uart2 byte received.
     * Parameter:
     * - callback: Callback function of the Uart2 byte received.
     *******************************************************/
    void Uart2_SetRxIsrCallback(callback_t callback);

    /*******************************************************
     * Uart1_SetTxIsrCallback
     * Set ISR callback function the Uart1 byte transmitted.
     * Parameter:
     * - callback: Callback function of the Uart1 byte transmitted.
     *******************************************************/
    //void Uart1_SetTxIsrCallback(callback_t callback);

    /*******************************************************
     * Uart2_SetTxIsrCallback
     * Set ISR callback function the Uart2 byte transmitted.
     * Parameter:
     * - callback: Callback function of the Uart2 byte transmitted.
     *******************************************************/
    //void Uart2_SetTxIsrCallback(callback_t callback);


    //
    // STD CALLBACKS
    //

    /*******************************************************
     * Uart1_SetRxCallback
     * Set callback function the Uart1 byte received.
     * Parameter:
     * - callback: Callback function of the Uart1 byte received.
     *******************************************************/
    void Uart1_SetRxCallback(callback_t callback);

    /*******************************************************
     * Uart2_SetRxCallback
     * Set callback function the Uart2 byte received.
     * Parameter:
     * - callback: Callback function of the Uart2 byte received.
     *******************************************************/
    void Uart2_SetRxCallback(callback_t callback);

    /*******************************************************
     * Uart1_SetTxCallback
     * Set callback function the Uart1 bytes transmitted.
     * The callback back function will be called when the Tx queue
     * is empty after an asynchronous function is called.
     * Parameter:
     * - callback: Callback function of the Uart1 bytes transmitted.
     *******************************************************/
    void Uart1_SetTxCallback(callback_t callback);

    /*******************************************************
     * Uart2_SetTxCallback
     * Set callback function the Uart2 bytes transmitted.
     * The callback back function will be called when the Tx queue
     * is empty after an asynchronous function is called.
     * Parameter:
     * - callback: Callback function of the Uart2 bytes transmitted.
     *******************************************************/
    void Uart2_SetTxCallback( callback_t callback );

    /*******************************************************
     * Uart1_SetRxLineCallback
     * Set callback function the Uart1 line received.
     * Parameter:
     * - callback: Callback function of the Uart1 line received.
     * - buffLength: Buffer size of the line received buffer.
     *******************************************************/
    void Uart1_SetRxLineCallback( callback_t callback, uint16_t buffLength );

    /*******************************************************
     * Uart1_SetRxLineCallback
     * Set callback function the Uart1 line received.
     * Parameter:
     * - callback: Callback function of the Uart1 line received.
     * - buffLength: Buffer size of the line received buffer.
     *******************************************************/
    void Uart2_SetRxLineCallback( callback_t callback, uint16_t buffLength );


    /*******************************************************
     * Uart1_SetBufferFullCallback
     * Set callback function the Uart1 buffer full.
     * Parameter:
     * - callback: Callback function of the Uart1 buffer full.
     *******************************************************/
    void Uart1_SetBufferFullCallback( callback_t callback );

    /*******************************************************
     * Uart2_SetBufferFullCallback
     * Set callback function the Uart2 buffer full.
     * Parameter:
     * - callback: Callback function of the Uart2 buffer full.
     *******************************************************/
    void Uart2_SetBufferFullCallback( callback_t callback );



    /*******************************************************
     * Uart1_Executor
     * Performs the Rx callback function of Uart1.
     * This function is called by the BSP_Executor.
     *******************************************************/
    inline void Uart1_Executor(void);

    /*******************************************************
     * Uart2_Executor
     * Performs the Rx callback function of Uart2.
     * This function is called by the BSP_Executor.
     *******************************************************/
    inline void Uart2_Executor(void);



#endif // __BSP_UART_H__
