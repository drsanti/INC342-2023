/************************************************************
 * Example 8. PWM-based Beep Sound Control Functions        *
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
     * The beep sound is generate by a Buzzer.
     * The driver signal is based on the PWM.
     * 1.0 Hz to 160.0 kHz are supported.
     * For the beep sound, 100 Hz to 10 kHz are recommended.
     */

    /**
     * Ex1.
     * Generate beep sound with previous settings.
     */
    Beep(100);         // Generate beep sound for 100 mS.
    Delay_mS(1000);    // Delay for 1000 mS.

    /**
     * Ex2.
     * Set the beep frequency.
     */
    Beep_SetFrequency(4000.0f);    // Set beep frequency to 4 kHz
    Beep(100);                     // Generate beep sound for 100 mS.
    Delay_mS(1000);                // Delay for 1000 mS.

    /**
     * Ex3.
     * Set the beep power (0.0 - 1.0).
     *
     *  0.0f:   0% of beep power.
     *  1.0f: 100% of beep power.
     */
    Beep_SetPower(0.20f);    // Set beep power to 20%
    Beep(100);               // Generate beep sound for 100 mS.
    Delay_mS(1000);          // Delay for 1000 mS.

    /**
     * Ex4.
     * Play the beep sound with the specified frequency and interval.
     * The previous setting of power is used.
     *  - 1st parameter is the beep interval (mS).
     *  - 2nd parameter is the beep frequency (Hz).
     */
    Beep_Play(100, 5000);    // Play 5 kHz of beep sound for 0.1 seconds.
    Delay_mS(1000);          // Delay for 1000 mS.

    /**
     * Ex5.
     * Play the beep sound with the specified properties.
     * The previous setting of power is used.
     *  - 1st parameter is the beep interval (mS).
     *  - 2nd parameter is the beep frequency (Hz).
     *  - 3rd parameter is the beep power (0.0 - 1.0).
     */
    Beep_Generate(100, 2000, 0.5f);    // Play 2 kHz beep sound with 50% power for 0.1 seconds.

    /*
     * Starts the system.
     */
    System_Start();

    return 0;
}
