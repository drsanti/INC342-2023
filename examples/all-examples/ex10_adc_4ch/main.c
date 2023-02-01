/************************************************************
 * Example 10. ADC Basic Functions                          *
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
     * Initializes the system.
     */
    System_Init();


    /**
     * Note:
     * There are 4 channels of 10-bit ADCs.
     * The input pins of the ADCs are connected to POTs.
     * All channels of the ADCs can be wired to external voltage sources by setting the input selection jumpers.
     * The channel 1, (ADC_ID_1) can be wired to LED by setting a jumper.
     * Please check the schematic for more details.
     *
     * In this example, only basic functions of the ADCs are explained.
     * Other advanced functions can be checked in other examples.
     */


    /**
     * Ex1.
     * Get 10-bit data from the adc channels specified by the function name.
     */
    int16_t adc0 = Adc0_Get();
    int16_t adc1 = Adc1_Get();
    int16_t adc2 = Adc2_Get();
    int16_t adc3 = Adc0_Get();

    /**
     * Ex2.
     *  Get voltage values from the ADC channels specified by the function name.
     */
    int16_t v0 = Adc0_GetVoltage();
    int16_t v1 = Adc1_GetVoltage();
    int16_t v2 = Adc2_GetVoltage();
    int16_t v3 = Adc3_GetVoltage();

    /**
     * Ex3.
     * Get 10-bit data from the ADC channels specified by the ID.
     */
    int16_t ch0 = Adc_Get( ADC_ID_0 );
    int16_t ch1 = Adc_Get( ADC_ID_2 );
    int16_t ch2 = Adc_Get( ADC_ID_2 );
    int16_t ch3 = Adc_Get( ADC_ID_3 );

    /**
     * Ex4.
     * Get voltage values from the ADC channels specified by the ID.
     */
    float voltage0 = Adc_GetVoltage( ADC_ID_0 );
    float voltage1 = Adc_GetVoltage( ADC_ID_1 );
    float voltage2 = Adc_GetVoltage( ADC_ID_2 );
    float voltage3 = Adc_GetVoltage( ADC_ID_3 );


    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
