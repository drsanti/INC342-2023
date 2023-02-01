/************************************************************
 * File:    BSP_Pwm.h                                       *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  19 February 2020                                *
 ************************************************************/


#ifndef __BSP_Pwm_H__

    #define __BSP_Pwm_H__

    #include <BSP_Mcu.h>
    #include <BSP_Led.h>

    /*******************************************************
     * PWM CHANNELS
     *******************************************************/
    #define PWM_NUM_CHANNELS 4


    /*******************************************************
     * PWM CHANNEL IDs
     *******************************************************/
    #define PWM_ID_0        0       // PWM Channel 0 (A)
    #define PWM_ID_1        1       // PWM Channel 1 (B)
    #define PWM_ID_2        2       // PWM Channel 2 (C)
    #define PWM_ID_3        3       // PWM Channel 3 (D)

    /*******************************************************
     * PWM OPERATION STATUSES
     *******************************************************/
    #define PWM_STATUS_STOPPED      0
    #define PWM_STATUS_RUNNING      1

    typedef struct {
        uint16_t    id;     // PWM (OS) channel id (0,...,4).
        uint16_t    status; // Status (Stopped or Running).
        float       freq;   // Frequency.
        float       duty;   // Duty ratio.
        float       shift;  // Shift ratio.
        uint16_t    PRTM;   // Value of PR2 register.
        uint16_t    OCRC;   // Value of OCxR register.
        uint16_t    OCRS;   // Value of OCxRS register.
        uint16_t    OCS;    // Value of OCxS register.
    }pwm_t;


    /*******************************************************
     * Pwm_Init
     * Initializes all channels of PWMs(OCs) with the specified frequency and duty cycle ratio.
     * Parameter:
     * - freq: Frequency value (in Hz) of all PWMs(OCs) channels.
     * - duty: Duty cycle ratio (0.0 - 1.0) of all PWMs(OCs) channels.
     *******************************************************/
    void Pwm_Init( float freq, float duty );

    /*******************************************************
     * Pwm_SetDutyRatio
     * Set duty ratio of the PWM channel specified by the id.
     * Parameter:
     * - id: Id of the target PWM channel (PWM_ID_0, ..., PWM_ID_4).
     * - duty: Duty cycle ratio (0.0 - 1.0) of the target PWM channel.
     *******************************************************/
    bool Pwm_SetDutyRatio( int id, float duty );

    /*******************************************************
     * Pwm_SetFrequency
     * Set the frequency of all PWM (OC) channels. The duty ratio will not be changed.
     * Parameter:
     * - freq: Frequency value applied to all channels.
     *******************************************************/
    bool Pwm_SetFrequency( float freq );


    /*******************************************************
     * Pwm_SetShiftRatio
     * Set phase shift ratio of the PWM channel specified by the id.
     * Parameter:
     * - id: Id of the target PWM channel (PWM_ID_0, ..., PWM_ID_4).
     * - shift: Phase shifting ratio (0.0 - 1.0) of the target PWM channel.
     *******************************************************/
    bool Pwm_SetShiftRatio( int id, float shift );

    void Pwm_Start( int id );
    void Pwm_Stop( int id ) ;

#endif // __BSP_Pwm_H__
