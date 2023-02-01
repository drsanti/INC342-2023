/************************************************************
 * Example 27. Address of variable (mamory)                 *
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



int16_t global_var1 = 1;
int16_t global_var2 = 2;

/************************************************************
 * Main function
 ************************************************************/
int main( void ) {

    /*
     * Intianlizes the system.
     */
    System_Init();

    /**
     * Initializes the Uart1. Used to check the results.
     */
    Uart1_Init( 115200, 64, 128 );


    /**
     * Address of global variables are located at data spac.
     */
    Uart1_Printf( "\nGlobal Variables:\n" );
    Uart1_Printf( "addr: 0x%.4X 0x%.4X\n", &global_var1, &global_var2 );

    /**
     * Address of static variables are located at the same space as the global variables.
     */
    static int static_local_var1 = 3;
    static int static_local_var2 = 4;
    Uart1_Printf( "\nStatic Local Variables:\n" );
    Uart1_Printf( "addr: 0x%.4X 0x%.4X\n", &static_local_var1, &static_local_var2 );

    /**
     * Address of dynamic memory blocks are located in heap space.
     */
    int *dynamic_memory1 = malloc( 256 );
    int *dynamic_memory2 = malloc( 256 );
    Uart1_Printf( "\nDynamic Memory (Heap):\n" );
    Uart1_Printf( "addr: 0x%.4X 0x%.4X\n", dynamic_memory1, dynamic_memory2 );
    free(dynamic_memory1);
    free(dynamic_memory2);

    /**
     * Address of local variables are located in stack space.
     */
    char normal_local_var1 = 5;
    char normal_local_var2 = 6;
    Uart1_Printf( "\nNormal Local Variables:\n" );
    Uart1_Printf( "addr: 0x%.4X 0x%.4X\n", &normal_local_var1, &normal_local_var2 );

    /**
     *  RESULTS
     *
     *  Global Variables:
     *  addr: 0x0800 0x0802
     *
     *  Static Local Variables:
     *  addr: 0x0804 0x0806
     *
     *  Dynamic Memory (Heap):
     *  addr: 0x0BA2 0x0CA4
     *
     *  Normal Local Variables:
     *  addr: 0x16FE 0x16FF
    */

    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
