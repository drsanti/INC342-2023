/************************************************************
 * File:    BSP_LedBlink.h                                  *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  22 February 2020                                *
 ************************************************************/

#ifndef __LED_BLINK_H__

    #define __LED_BLINK_H__

    #include <BSP_Led.h>

    /*******************************************************
     * LED FLASHING/BLINKING STATES
     *******************************************************/
    #define LED_STATE_IDLE      0       // Idle.
    #define LED_STATE_BEGIN     1       // Begin. (phase-shifting starts)
    #define LED_STATE_ON        2       // ON.
    #define LED_STATE_OFF       3       // OFF.


    /*******************************************************
     * LED OPERATION MODES
     *******************************************************/
    #define LED_MODE_LED        0       // Normal mode.
    #define LED_MODE_FLS        1       // Flashing mode.
    #define LED_MODE_BLK        2       // Blinking mode.
    #define LED_MODE_PWM        3       // PWM blinking mode.

    /*******************************************************
     * LED OBJECT STRUCTURE
     *******************************************************/
    typedef struct {
        int16_t     id;                 // Id of LED.
        uint16_t    mode;               // Operation mode.
        uint16_t    ticks;              // Tick counter.
        uint16_t    period;             // Signal period (in mS).
        uint16_t    width;              // Pulse-width period (in mS).
        uint16_t    shift;              // Phase-shift period (in mS).
        uint16_t    state;              // Operation state.
        bool        changed;            // State changed flag.
        uint16_t    counter;            // Completion counter (number of cycles).
        callback_t  callback;           // Callback function.
    }led_t;

    typedef struct {
        int16_t     id;                 // Id of LED.
        uint16_t    mode;               // Operation mode.
        uint16_t    state;              // Operation state.
        uint16_t    counter;            // Completion counter (number of cycles).
        led_t       *sender;            // LED object.
    }led_event_t;


    /************************************************************
    * Led_BlinkInit
    * Initializes parameters of the flasher, blinkers and PWM-blinkers.
    *************************************************************/
    void Led_BlinkInit(void);


    /************************************************************
    * Led_Flash
    * Flashes the LED specified by the id. The on-time interval
    * of the target LED is controlled by the width parameter.
    * Parameters:
    * - id: Id of the target LED (LED_ID_0, ..., LED_ID_3).
    * - width: On-time interval (in milliseconds).
    *************************************************************/
    void Led_Flash(int16_t id, uint16_t width);


    /************************************************************
    * Led_Blink
    * Blinks the LED specified by the id. The target LED starts
    * with OFF stage. This state can be controlled by the `shift`.
    * Then it turns ON. The ON time can be controlled by the `width`.
    * Parameters:
    * - id: Id of the target LED (LED_ID_0, ..., LED_ID_3).
    * - shift: Shift-time interval (n milliseconds).
    * - width: On-time interval (in milliseconds).
    *************************************************************/
    void Led_Blink(int16_t id, uint16_t shift, uint16_t width);


    /************************************************************
    * Led_Pwm
    * Performs LED blinkig style using PWM signal.
    * Parameters:
    * - id: Id of the target LED (LED_ID_0, ..., LED_ID_3).
    * - shift: Shift-time interval (in milliseconds).
    * - width: On-time interval (in milliseconds.
    * - period: Total time of the PWM signal (in milliseconds).
    *************************************************************/
    void Led_Pwm(int16_t id, uint16_t shift, uint16_t width, uint16_t period);


    /************************************************************
    * Led_SetChangedCallback
    * Sets callback function to the target LED.
    * The callback functon will be called when the LED operation is completed.
    * Parameters:
    * - id: Id of the target LED (LED_ID_0, ..., LED_ID_3).
    * - callback: Callback function of the target LED.
    *************************************************************/
    void Led_SetChangedCallback(int16_t id, callback_t callback);

    /************************************************************
    * Led_SetMode
    * Sets operation mode of the LED.
    * Used to switch from PWM mode to normal (LED) mode.
    * Parameters:
    * - id: Id of the target LED (LED_ID_0, ..., LED_ID_3).
    * - mode: Mode of the LED operation.
    *************************************************************/
    void Led_SetMode(int16_t id, int16_t mode);


    /************************************************************
    * LED_BlinkTickedExecutor
    * Performs led flshing/flashing execution.
    * This function must be called from the BSP_Main every
    * ticked interval.
    *************************************************************/
    inline void LED_BlinkTickedExecutor(void);

#endif // __LED_BLINK_H__
