/************************************************************
 * Example 18. ADC Value Changed Callback Functions         *
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
 * Callback function of the ADC1 (LDR) value changed.
 */
void ADC1_VoltageChangedCallback( event_t *event )  {

    Led_Inv( LED_ID_1 );
    Beep_Play( 100, 4000 );
    Uart1_Printf( "ADC1 value changed detected, %value: %4d.\r\n", Adc1_Get() );
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
    Uart1_Init( 115200, 32, 64 );


    /**
     * Set the Changed (value changed) callback function to the ADC1 (LDR).
     * The change the jumper AN1/LDR to LED (right-hand side) before run the application.
     * To check the detection results, move your hand over the LDR.
     */
    Adc_SetChangedCallback( ADC_ID_1, ADC1_VoltageChangedCallback );


    /**
     * Set detection interval, the scan time.
     */
    Adc_SetChangedInterval( ADC_ID_1, 200 );


    /**
     * Set detection threshold value, the comparison value.
     */
    Adc_SetChangedThreshold( ADC_ID_1, 50 );


    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
