/************************************************************
 * File:    BSP_PswKey.h                                    *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  17 February 2020                                *
 ************************************************************/


#ifndef __BSP_PSW_KEY_H__

    #define __BSP_PSW_KEY_H__

    #include <BSP_Psw.h>

    /******************************************************
     * STATES OF SWITCHES
     ******************************************************/
    #define PSW_STATE_OFF               0<<0    // 0x00: KEY_OFF
    #define PSW_STATE_DOWN              1<<0    // 0x01: KEY_DOWN
    #define PSW_STATE_HOLD              1<<1    // 0x02: KEY_HOLD
    #define PSW_STATE_LOCK              1<<2    // 0x04: KEY_LOCK
    #define PSW_STATE_UP                1<<3    // 0x08: KEY_UP

    #define PSW_STATE_CHANGE            1<<4    // 0x10: Used for KeyChangedCallback only.

    /******************************************************
     * STATES TICKS
     ******************************************************/
    #define PSW_STATE_CHANGED_TICKS     20      // Ticks for state changing (OFF->DOWN, [HOLD, LOCK]->UP, UP->OFF).
    #define PSW_DOWN_TO_HOLD_TICKS      1000    // Ticks for state DOWN->HOLD.
    #define PSW_HOLD_TO_PULSE_TICKS     2000    // Ticks for state HOLD->LOCK.

    /******************************************************
     * KEY HOLDING EMITTING TICKS
     ******************************************************/
    #define PSW_PULSE_MAX_TICKS         200     // Ticks for starting (maximum) interval of KEY_LOCK callback emitting.
    #define PSW_PULSE_MIN_TICKS         50      // Ticks for minimum interval of KEY_LOCK callback emitting.
    #define PSW_PULSE_DEC_TICKS         5       // Tick for interval decreasing step.


    /*******************************************************
     * SWITCH EVENT TYPES
     *******************************************************/
    #define EVT_SWITCH_PSW              0


    /******************************************************
     * PSW OBJECT STRUCTURE
     ******************************************************/
    typedef struct {
        int         id;                         // Id of the switch.
        uint16_t    state;                      // State of the switch.
        char        *sname;                     // State name of the switch.
        uint8_t     data;                       // Data representing states of all switches.

        callback_t  change_callback;            // KeyChanged callback function.
        callback_t  down_callback;              // KeyDown callback function.
        callback_t  hold_callback;              // KeyHold callback function.
        callback_t  lock_callback;              // KeyLock callback function.
        callback_t  up_callback;                // KeyUp callback function.

        bool        onoff;                      // Current key state.
        uint16_t    onticks;                    // KeyON tick counter used when the current key state is ON.
        uint16_t    offticks;                   // KeyOFF tick counter used when the current key state is OFF.
        bool        changed;                    // Key state changed flag used to signal the callback emitter.
        uint8_t     callback_flags;             // Callback flags used to indicate the available callback functions.

    }switch_t;


    /******************************************************
     * SWITCH EVENT STRUCTURE
     ******************************************************/
    typedef struct {
        int         type;                       // Switch evnt type.
        int         id;                         // Id of the switch.
        uint16_t    state;                      // State of the switch.
        char        *sname;                     // State name of the switch.
        switch_t    *sender;                    // Switch object.
    }switch_event_t;

    /******************************************************
     * Psw_SetKeyDownCallback
     * Sets/Adds KeyDown callback to the switch specified by the id.
     * Retuens false if the operation failed.
     * Parameter:
     * - id: Id of the target switch (PSW_ID_0, PSW_ID_1, PSW_ID_2, PSW_ID_3).
     * - callback: Callback function to execute when the KeyDown state is detected.
     ******************************************************/
    bool Psw_SetKeyDownCallback(int16_t id, callback_t callback);


    /******************************************************
     * Psw_SetKeyHoldCallback
     * Sets/Adds KeyHold callback to the switch specified by the id.
     * Retuens false if the operation failed.
     * Parameter:
     * - id: Id of the target switch (PSW_ID_0, PSW_ID_1, PSW_ID_2, PSW_ID_3).
     * - callback: Callback function to execute when the KeyHold state is detected.
     ******************************************************/
    bool Psw_SetKeyHoldCallback(int16_t id, callback_t callback);


    /******************************************************
     * Psw_SetKeyLockCallback
     * Sets/Adds KeyLock callback to the switch specified by the id.
     * Retuens false if the operation failed.
     * Parameter:
     * - id: Id of the target switch (PSW_ID_0, PSW_ID_1, PSW_ID_2, PSW_ID_3).
     * - callback: Callback function to execute when the KeyLock state is detected.
     ******************************************************/
    bool Psw_SetKeyLockCallback(int16_t id, callback_t callback);


    /******************************************************
     * Psw_SetKeyUpCallback
     * Sets/Adds KeyUp callback to the switch specified by the id.
     * Retuens false if the operation failed.
     * Parameter:
     * - id: Id of the target switch (PSW_ID_0, PSW_ID_1, PSW_ID_2, PSW_ID_3).
     * - callback: Callback function to execute when the KeyUp state is detected.
     ******************************************************/
    bool Psw_SetKeyUpCallback(int16_t id, callback_t callback);


    /******************************************************
     * Psw_SetKeyChangedCallback
     * Sets/Adds KeyChanged callback to the switch specified by the id.
     * Retuens false if the operation failed.
     * Parameter:
     * - id: Id of the target switch (PSW_ID_0, PSW_ID_1, PSW_ID_2, PSW_ID_3).
     * - callback: Callback function to execute when the KeyChanged state is detected.
     ******************************************************/
    bool Psw_SetKeyChangedCallback(int16_t id, callback_t callback);

    int16_t Psw_GetKeyState(int16_t id);


    /************************************************************
     * PSW_KeyTickedExecutor
     * Performs callback functions.
     * This function must be called from the BSP_Main every ticked interval.
     *********************************************************/
    inline void PSW_KeyTickedExecutor(void);



#endif // __BSP_PSW_KEY_H__
