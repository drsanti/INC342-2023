/************************************************************
 * Example 11. PWM Signals Generation using OC modules      *
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
     * There are 4 channels of PWMs that operate long range for frequency, 0.625 Hz to 160 kHz.
     * The duty ratio and phase-shift ration can be set independently for all channels.
     * Each channel is connected to:
     *  - PWM_ID_0 connected to RB8 (SCL)
     *  - PWM_ID_1 connected to RB9 (SDA)
     *  - PWM_ID_2 connected to RB2 (LED2)
     *  - PWM_ID_3 connected to RB3 (LED3)
     *  (Please check the schematic for more details)
     */


    /**
     * Ex1.
     * Set the PWMs (all channels) to generate 50 kHz and 20% duty ratio.
     *  - 1st parameter is frequency
     *  - 2nd parameter is duty ration (>0.0 to <1.0)
     */
    Pwm_Init( 50e3, 0.2 );


    /**
     * Ex2.
     * Set the frequency of PWMs (all channels) to 1 kHz.
     * The previous setting of duty ratio is used.
     */
    Pwm_SetFrequency( 1e3 );


    /**
     * Ex3.
     * Set the duty ratio of PWMs.
     * The previous setting of frequency is used.
     *  - 1st parameter is channel ID.
     *  - 2nd parameter is duty ratio value (>0.0 to <1.0).
     */
    Pwm_SetDutyRatio( PWM_ID_0, 0.10 );
    Pwm_SetDutyRatio( PWM_ID_1, 0.20 );
    Pwm_SetDutyRatio( PWM_ID_2, 0.30 );
    Pwm_SetDutyRatio( PWM_ID_3, 0.40 );


    /**
     * Ex4.
     * Set the phase-shift ratio of PWMs.
     * - 1st parameter is channel ID.
     * - 2nd parameter is duty ratio value (>0.0 to <1.0).
     * Warning:
     * The phase-shift ratio + duty ratio must less than 1.0.
     */
    Pwm_SetShiftRatio( PWM_ID_0, 0.00 );
    Pwm_SetShiftRatio( PWM_ID_1, 0.10 );
    Pwm_SetShiftRatio( PWM_ID_2, 0.20 );
    Pwm_SetShiftRatio( PWM_ID_3, 0.30 );


    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
