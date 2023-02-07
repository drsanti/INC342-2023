/************************************************************
 * File:    BSP_Config.h                                    *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  16 February 2020                                *
 ************************************************************/

#ifndef __BSP_CONFIG_H__

    #define	__BSP_CONFIG_H__

    /********************************************************
     * XC16 Header.
     ********************************************************/
    #include <BSP_Header.h>

    /********************************************************
     * CPU clock frequency. 32MHz.
     ********************************************************/
    #define FOSC            32e6        // CPU clock frequency, 32 MHz.
    #define CONFIG_FOSC     FOSC        // CPU clock frequency, 32 MHz.

    /********************************************************
     * Peripherals clock frequency. 16MHz.
     ********************************************************/
    #define FCY             (FOSC/2)    // Peripherals clock frequency, 16 MHz.
    #define CONFIG_FCY      FCY         // Peripherals clock frequency, 16 MHz.

    /********************************************************
     * Use libpic30. The FCY must be declared first.
     ********************************************************/
    #include <libpic30.h>

    /********************************************************
     * Time per tick of the system tick timer (timer1).
     ********************************************************/
    #define CONFIG_SYSTEM_TIME_PER_TICK     1e-3

    /********************************************************
     * Common callback function type.
     ********************************************************/
    typedef void (*callback_t)(void *);

    typedef void event_t;

#endif
