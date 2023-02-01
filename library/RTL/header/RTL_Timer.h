/************************************************************
 * File:    Timer.h                                         *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  17 February 2020                                *
 ************************************************************/

#ifndef __RTL_TIMER_H__

    #define __RTL_TIMER_H__

    #include <RTL_Config.h>


    /*******************************************************
     * TIMER OBJECT STRUCTURE
     *******************************************************/
    typedef struct {
        int         id;         /* Id of the timer, 0, 1, ...       */
        uint16_t    interval;   /* Sleep interval in milliseconds.  */
        uint16_t    ticks;      /* Tick counter (internally used).  */
        uint16_t    counter;    /* Alarmed counter value.           */
        callback_t  callback;   /* Callback function.               */
        void        *context;   /* Context of the timer.            */
    }timer_t;

    #define EVT_TIMER_ALARM     0

    /*******************************************************
     * TIMER EVENT STRUCTURE
     *******************************************************/
    typedef struct {
        int         type;       /* Timer event type.                */
        int         id;         /* Id of the timer, 0, 1, ...       */
        uint16_t    counter;    /* Alarmed counter value.           */
        uint16_t    steps;      /* General proposed variable        */
        void        *context;   /* Context of the timer.            */
        timer_t     *sender;    /* Timer object,                    */
    }timer_event_t;


    /*******************************************************
     * Timer_Create
     * Creates and returns a timer object.
     * Parameters:
     * - interval: Sleeping interval in milliseconds.
     * - callback: Callback function, performed when the timer ready.
     *******************************************************/
    timer_t * Timer_Create(uint16_t interval, callback_t callback);


    /**
     * Timer_SetInterval
     * Sets/Changes interval of the timer.
     * Parameters:
     * - timer: Timer object.
     * - interval: Interval (in milliseconds) of the timer.
     */
    void Timer_SetInterval( timer_t *timer, uint16_t interval );

    /**
     * Timer_EndWaiting
     * Ends the current waiting and start the new cycle.
     * Parameter:
     * - timer: Timer object.
     */
    void Timer_EndWaiting( timer_t *timer );

    /*******************************************************
     * Timer_Delete
     * Deletes the given timer object.
     * Parameters:
     * - timer: timer object to be removed.
     *******************************************************/
    void Timer_Delete(timer_t * timer);


    /***********************************************************
     * Timer_TickedExecutor (ticked execution)
     * This function is called by the RTL_Executor() every tick.
     ***********************************************************/
    inline void Timer_TickedExecutor(void);

#endif // __RTL_TIMER_H__
