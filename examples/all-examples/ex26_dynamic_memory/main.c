/************************************************************
 * Example 26. Using Dynamic Memory (malloc, free)          *
 ************************************************************
 * File:    main.c                                          *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 ************************************************************
 * Update:  04 March 2020 (Initial version)                 *
 ************************************************************/


/************************************************************
 * Include the system header.
 ************************************************************/
#include <ecc.h>


/**
 * Callback function of Uart1 line received.
 */
void RxLine_Callback( void *event ) {

    uart_event_t *evt = (uart_event_t *)event;
    const char *line  = evt->line; // The line contains "\r\n" or "\n" at the end.

    /**
     * Print the received line.
     */
    Uart1_Printf( "line: %s", line );

    /**
     * Get the length (number of bytes) of the received line.
     */
    int16_t length = strlen( line );

    /**
     * Allocate a block of memory from the heap space.
     */
    char *ptrMemory = (char *)malloc( length + 1 );

    /**
     * Check if the memory can be taken.
     */
    if( ptrMemory == NULL ) {
        Uart1_Printf( "Could not allocate the memory!\n" );
        return;
    }

    /**
     * Print the address and size of the located memory.
     */
    Uart1_Printf( "addr: 0x%.4X, size: %d\n", ptrMemory, sizeof(*ptrMemory)*length );

    /**
     * Access/Use the memory.
     */
    int16_t i;
    for( i = 0; i < length; i++ ) {
        ptrMemory[i] = (char)( 'A' + i );
    }

    /**
     * Fill the last byte with the "NULL terminator", can be NULL, 0, '\0' or (void *)0
     */
    ptrMemory[i] = NULL;

    /**
     * Print the data contained in the mory.
     */
    Uart1_Printf( "data: %s\r\n", ptrMemory );

    /**
     * Free the memory
     */
    free( ptrMemory );
    ptrMemory = NULL;

    /**
     * Ending beep.
     */
    Beep_Play( 4000, 50 );
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
     * Initializes the Uart1. Used to check the results.
     * Run the command line with -monitor option to see the results.
     * e.g., ecc-pic24-cli -build -flash -monitor
     */
    Uart1_Init( 115200, 64, 128 );

    /**
     * Set the RxLineCallback (line received) function to the Uart1.
     */
    Uart1_SetRxLineCallback( RxLine_Callback, 64 );

    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
