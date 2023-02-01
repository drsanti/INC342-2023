

```c
/************************************************************
 * Example 1. Digital Output Functions                      *
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
     * There are 4 channels of the general-purpose output pins.
     * Each channel has its own id:
     *  - DOUT_ID_0 is the digital output channel 0.
     *  - DOUT_ID_1 is the digital output channel 1.
     *  - DOUT_ID_2 is the digital output channel 2.
     *  - DOUT_ID_3 is the digital output channel 3.
     * The digital output channels support both read and write operations.
     * The logic data low (0) and high (1) are defined by LOGIC_LOW and LOGIC_HIGH respectively.
     * The digital output channels are connected to LEDs, the active-low LEDs.
     */



    /**
     * Ex1.
     * Access the digital output channel by the function name.
     */
    Dout0_Set();                        // Set digital output #0 (change to HIGH).
    Dout1_Clr();                        // Clear digital output #1 (change to LOW).
    Dout2_Inv();                        // Invert/Toggle digital output #2 (change to opposite logic).
    bool do3 = Dout3_Get();             // Get/Read logic status of output #3 and store in the do3.


    /**
     * Ex2.
     * Access the digital output channel by the ID.
     */
    Dout_Set( DOUT_ID_0 );              // Set digital output #0 (change to HIGH).
    Dout_Clr( DOUT_ID_1 );              // Clear digital output #1 (change to LOW).
    Dout_Inv( DOUT_ID_2 );              // Invert/Toggle digital output #2 (change to opposite logic).
    bool bit3 = Dout_Get( DOUT_ID_3 );  // Get/Read logic status of output #3 and store in the bit3.


    /**
     * Ex3.
     * Control output logic by function name and value.
     */
    Dout0_Wrt( LOGIC_LOW );             // Write logic LOW to digital output #0 (change to LOW).
    Dout1_Wrt( LOGIC_HIGH );            // Write logic HIGH to digital output #1 (change to HIGH).
    Dout2_Wrt( false );                 // Write logic FALSE to digital output #2 (change to LOW).
    Dout3_Wrt( true );                  // Write logic TRUE to digital output #3 (change to HIGH).
    Dout0_Wrt( 0 );                     // Write logic 0 to digital output #0 (change to LOW).
    Dout1_Wrt( 1 );                     // Write logic 1 to digital output #1 (change to HIGH).


    /**
     * Ex4.
     * Control output logic by ID and value.
     */
    Dout_Wrt( DOUT_ID_0, LOGIC_LOW );   // Write logic LOW to digital output #0 (change to LOW).
    Dout_Wrt( DOUT_ID_1, LOGIC_HIGH );  // Write logic HIGH to digital output #1 (change to HIGH).
    Dout_Wrt( DOUT_ID_2, false );       // Write logic FALSE to digital output #2 (change to LOW).
    Dout_Wrt( DOUT_ID_3, true );        // Write logic TRUE to digital output #3 (change to HIGH).
    Dout_Wrt( DOUT_ID_0, 0 );           // Write logic 0 to digital output #0 (change to LOW).
    Dout_Wrt( DOUT_ID_1, 1 );           // Write logic 1 to digital output #1 (change to HIGH).


    /**
     * Ex5.
     * Control output logic by a byte data.
     * Bit4 to bit7 are ignored.
     */
    Dout_Write(0x01);                   // Write data 0x01 (0001) to digital output channels.
    Dout_Write(0x03);                   // Write data 0x03 (0011) to digital output channels.
    Dout_Write(0x07);                   // Write data 0x07 (0111) to digital output channels.
    Dout_Write(0x0F);                   // Write data 0x0F (1111) to digital output channels.


    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
```
