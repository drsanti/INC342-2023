/************************************************************
 * File:    BSP_Beep.h                                      *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 ************************************************************
 * Update:  22 February 2020 (Initial)                      *
 * Update:  01 March 2020                                   *
 *          Added Beep_Generate() function                  *
 ************************************************************/

#ifndef __BSP_BEEP_H__
    #define __BSP_BEEP_H__

    #include <BSP_Mcu.h>

    /*******************************************************
     * Beep Notes
     *******************************************************/
    #define BEEP_Do     262     // Do
    #define BEEP_Re     294     // Re
    #define BEEP_Me     330     // Me
    #define BEEP_Fa     349     // Fa
    #define BEEP_So     392     // Sol
    #define BEEP_La     440     // La
    #define BEEP_Si     494     // Si
    #define BEEP_DO     523     // Do'

    /*******************************************************
     * Beep States
     *******************************************************/
    #define BEEP_ON     0       // Beep ON.
    #define BEEP_OFF    1       // Beep OFF.

    /*******************************************************
     * BEEP OBJECT STRUCTURER
     *******************************************************/
    typedef struct {
        uint16_t    interval;   // Beep inrerval (in mS).
        uint16_t    ticks;      // Tick counter.
        uint16_t    counter;    // Number of beep.
        uint16_t    status;     // Beep status.
        float       frequency;  // Beep frequency (Hz).
        float       power;      // Beep ower (0.0 - 1.0).
        uint16_t    OCxRS;      // Used to save OCxRS value.
        callback_t  callback;   // Callback function.
    }beep_t;

    /*******************************************************
     * BEEP OBJECT STRUCTURER
     *******************************************************/
    typedef struct {
        uint16_t interval;      // Beep interval (in mS).
        uint16_t counter;       // Number of beep.
        float    frequency;     // Beep frequency.
        float    power;         // Beep power (0.0-1.0)
        beep_t   *sender;       // Beep object.
    }beep_event_t;

    /************************************************************
    * Beep_Init
    * Initializes the beep peripherals and parameters.
    *************************************************************/
    void Beep_Init(void);

    /************************************************************
    * Beep_SetFrequency
    * Sets the frequency of the beep sound.
    * Paremeter:
    * - frequency: Frequency of the beep sound (1Hz - 160kHz).
    *************************************************************/
    void Beep_SetFrequency(float freq);

    /************************************************************
    * Beep_SetCallback
    * Set callback function of the beep sound. The callback
    * function will be called at the end of the beep sound period.
    * Paremeter:
    * - callback: Callback function of the beep.
    *************************************************************/
    void Beep_SetCallback(callback_t callback);

    /************************************************************
    * Beep_SetPower
    * Set the power of the beep sound.
    * Paremeter:
    * - power: Power of the beep sound (0.0 - 1.0).
    *************************************************************/
    void Beep_SetPower(float freq);

    /************************************************************
    * Beep
    * Starts the beep sound with the previous settings of the
    * frequency and power.
    * Paremeter:
    * - interval: Period (length) of the beep sound.
    *************************************************************/
    void Beep(uint16_t interval);

    /************************************************************
    * Beep_Play
    * Play the beep sound with the given frequency and interval.
    * Paremeters:
    * - interval: Period (length) of the beep sound (mS).
    * - frequency: frequency of the beep sound (Hz).
    *************************************************************/
    void Beep_Play(uint16_t interval, float frequency);


    /************************************************************
    * Beep_Generate
    * Play the beep sound with the given frequency and interval.
    * Paremeters:
    * - interval: Period (length) of the beep sound (mS).
    * - frequency: frequency of the beep sound (Hz).
    * - power: Power of the beep sound (0.0 to 1.0 for 0% to 100%).
    *************************************************************/
    void Beep_Generate(uint16_t interval, float frequency, float power);

    /************************************************************
    * BEEP_TickedExecutor
    * Performs beep sound execution.
    * This function must be called from the BSP_Main every
    * ticked interval.
    *************************************************************/
    inline void BEEP_TickedExecutor(void);

#endif // __BSP_BEEP_H__
