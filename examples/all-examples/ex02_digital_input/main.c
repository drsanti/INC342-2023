/************************************************************
 * Example 2. Digital Input Functions                       *
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
     * There are 4 channels of the general-purpose input pins.
     * Each channel has its own id:
     *  - DINP_ID_0 is the digital input channel 0.
     *  - DINP_ID_1 is the digital input channel 1.
     *  - DINP_ID_2 is the digital input channel 2.
     *  - DINP_ID_3 is the digital input channel 3.
     * The digital input channels support read operation only.
     * The logic data low (0) and high (1) are defined by LOGIC_LOW and LOGIC_HIGH respectively.
     * The digital input channels are connected to PSWs (Push Button Switches), the active-low PSWs.
     */



    /**
     * Ex1.
     * Access the digital input channel specified by the function name.
     */
    bool d0 = Dinp0_Get();                  // Get logic data from digital input #0.
    bool d1 = Dinp1_Get();                  // Get logic data from digital input #1.
    bool d2 = Dinp2_Get();                  // Get logic data from digital input #2.
    bool d3 = Dinp3_Get();                  // Get logic data from digital input #3.


    /**
     * Ex2.
     * Access the digital input channel specified by ID.
     */
    bool bit0 = Dinp_Get( DINP_ID_0 );      //  Get logic data from digital input #0.
    bool bit1 = Dinp_Get( DINP_ID_1 );      //  Get logic data from digital input #1.
    bool bit2 = Dinp_Get( DINP_ID_2 );      //  Get logic data from digital input #2.
    bool bit3 = Dinp_Get( DINP_ID_3 );      //  Get logic data from digital input #3.



    /**
     * Ex3.
     * Read all bits of the gitial input channels.
     * Bit4 to Bit7 are ignored (read as zeros).
     */
    uint8_t bits = Dinp_Read();



    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
