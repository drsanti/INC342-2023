/************************************************************
 * Example 19. ADC Value Changed Callback & Event           *
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
 * Callback function of all ADC channels.
 */
void ADCx_VoltageChangedCallback( event_t *event )  {

    adc_event_t *evt = (adc_event_t *)event;
    Led_Flash( evt->id, 2 );
    Uart1_Printf( "ADC[%d]: %4d, dif: %2d, dir: %s\r\n", evt->id, evt->value,
                                 evt->delta, evt->direction < 0 ? "DEC" : "INC" );

    /**
     * Beep frequency is depended on the delta value.
     */
    if( evt->id == ADC_ID_1 ) {
        Beep_Play( 50, 100*evt->delta );
    }
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
     * Set the Changed (value changed) callback function to all channels of the ADCs.
     * To check the detection results, change the POTs (voltage sources) on the board.
     */
    uint16_t i;

    for( i = ADC_ID_0; i <= ADC_ID_3; i++ ) {
        Adc_SetChangedCallback(  i, ADCx_VoltageChangedCallback );
        Adc_SetChangedInterval(  i, 50 );       // Set detection interval, the scan time.
        Adc_SetChangedThreshold( i, 10 );       // Set detection threshold value, the comparison value.
    }

    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
