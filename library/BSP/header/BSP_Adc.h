/************************************************************
 * File:    BSP_Adc.h                                       *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  22 February 2020                                *
 ************************************************************/

#ifndef __ADC_H_ADC__

    #define __ADC_H_ADC__

    #include <BSP_Mcu.h>

    /*******************************************************
     * ADC Channel ID
     *******************************************************/
    #define ADC_ID_0            0       // ADC Channel 0.
    #define ADC_ID_1            1       // ADC Channel 1.
    #define ADC_ID_2            2       // ADC Channel 2.
    #define ADC_ID_3            3       // ADC Channel 3.

    /*******************************************************
     * ADC TOTAL CHANNELS
     *******************************************************/
    #define ADC_NUM_CHANNELS    4       // Number of channel.

    /*******************************************************
     * ADC VOLTAGE RANGE
     *******************************************************/
    #define ADC_VOLTAGE_MAX     3.3     // Maximum voldate
    #define ADC_VOLTAGE_MIN     0.0     // Minumum voltage
    #define ADC_VOLTAGE_REF     0.0     // Refferent voltage

    /*******************************************************
     * ADC OBJECT STRUCTURE
     *******************************************************/
    typedef struct {
        int16_t     id;                 // Id of ADC.
        int16_t     value;              // 10-bit current value.
        int16_t     previous;           // 10-bit previous value.
        int16_t     delta;              // Delta value.
        uint16_t    ticks;              // Tick counter.
        int16_t     direction;          // Changed direction (+1: Up, -1: Down).
        uint16_t    threshold;          // Changed threshold.
        uint16_t    interval;           // Changed calculation interval.
        callback_t  callback;           // Changed callback function.
    }adc_t;

    /*******************************************************
     * ADC EVENT STRUCTURE
     *******************************************************/
    typedef struct {
        uint16_t    id;                 // Id of ADC.
        int16_t     value;              // 10-bit current value.
        int16_t     delta;              // Delta value.
        int16_t     direction;          // Changed direction (+1: Up, -1: Down).
        adc_t       *sender;            // ADC object.
    }adc_event_t;



    #define Adc0_Get()          Adc_Get( ADC_ID_0 )
    #define Adc1_Get()          Adc_Get( ADC_ID_1 )
    #define Adc2_Get()          Adc_Get( ADC_ID_2 )
    #define Adc3_Get()          Adc_Get( ADC_ID_3 )

    #define Adc0_GetVoltage()   Adc_GetVoltage( ADC_ID_0 )
    #define Adc1_GetVoltage()   Adc_GetVoltage( ADC_ID_1 )
    #define Adc2_GetVoltage()   Adc_GetVoltage( ADC_ID_2 )
    #define Adc3_GetVoltage()   Adc_GetVoltage( ADC_ID_3 )



    /*******************************************************
     * Adc_Init
     * Initializes ADC peripheral and parameters.
     *******************************************************/
    void Adc_Init(void);

    /*******************************************************
     * Adc_Get
     * Returns current value of the target channel.
     * Parameter:
     * - id: Id of ADC (ADC_ID_0, ..., ADC_ID_3).
     *******************************************************/
    int16_t Adc_Get(uint16_t id);

    /*******************************************************
     * Adc_GetVoltage
     * Returns voltage of the target channel.
     * Parameter:
     * - id: Id of ADC (ADC_ID_0, ..., ADC_ID_3).
     *******************************************************/
    float Adc_GetVoltage(uint16_t id);


    /*******************************************************
     * Adc_GetPercentage
     * Returns percentage of the target channel.
     * Parameter:
     * - id: Id of ADC (ADC_ID_0, ..., ADC_ID_3).
     *******************************************************/
    float Adc_GetPercentage(uint16_t id);

    /*******************************************************
     * Adc_SetChangedCallback
     * Sets callback function for the value changed.
     * Parameter:
     * - id: Id of ADC (ADC_ID_0, ..., ADC_ID_3).
     * - callback: Callback function to be called when value changed.
     *******************************************************/
    void Adc_SetChangedCallback(uint16_t id, callback_t callback);

    /*******************************************************
     * Adc_SetChangedThreshold
     * Sets threshold value for the value changed.
     * Parameter:
     * - id: Id of ADC (ADC_ID_0, ..., ADC_ID_3).
     * - threshold: Threshold value of the value changed calculation.
     *******************************************************/
    void Adc_SetChangedThreshold(uint16_t id, uint16_t threshold);

    /*******************************************************
     * Adc_SetChangedInterval
     * Sets calculation interval (in milliseconds).
     * Parameter:
     * - id: Id of ADC (ADC_ID_0, ..., ADC_ID_3).
     * - interval: Calculation interval for the value changed.
     *******************************************************/
    void Adc_SetChangedInterval(uint16_t id, uint16_t interval);


    /************************************************************
     * ADC_TickedExecutor (System called function)
     * Performs the changed allculation and callback functions.
     * This function must be called from the BSP_Main every ticked interval.
     *********************************************************/
    inline void ADC_TickedExecutor(void);

#endif // __ADC_H_ADC__
