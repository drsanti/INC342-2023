/************************************************************
 * File:    BSP_Dio.h                                       *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  24 February 2020                                *
 ************************************************************/

#ifndef __DIO_H__
#define __DIO_H__

    #include <BSP_Led.h>
    #include <BSP_Psw.h>

    #define DOUT_ID_0       0  /* Digital Output Channel 0  */
    #define DOUT_ID_1       1  /* Digital Output Channel 1  */
    #define DOUT_ID_2       2  /* Digital Output Channel 2  */
    #define DOUT_ID_3       3  /* Digital Output Channel 3  */

    #define DINP_ID_0       0  /* Digital Input Channel 0   */
    #define DINP_ID_1       1  /* Digital Input Channel 1   */
    #define DINP_ID_2       2  /* Digital Input Channel 2   */
    #define DINP_ID_3       3  /* Digital Input Channel 3   */

    #define LOGIC_LOW       0  /* Logic Low (0) value       */
    #define LOGIC_HIGH      1  /* Logic High (1) value      */

    /**
     * Writes a byte of data to the digital outputs.
     * Parameter:
     * - data: A byte data (0x00-0x0F) to be written.
     */
    #define Dout_Write(data)    Led_Write(data)


    /**
     * Writes a 1-bit of data (LOGIC_LOW or LOGIC_HIGH) to a digital output.
     * Parameter:
     * - id: Id of the target digital output (DOUT_ID0,...,DOUT_ID3).
     * - data: Bit data to be written.
     */
    #define Dout_Wrt(id, data)  Led_Wrt(id, data)


    /**
     * Writes a 1-bit of data (LOGIC_LOW or LOGIC_HIGH) to a digital output #0.
     * Parameter:
     * - data: Bit data to be written.
     */
     #define Dout0_Wrt(data)  Led_Wrt(0, data)


    /**
     * Writes a 1-bit of data (LOGIC_LOW or LOGIC_HIGH) to a digital output #1.
     * Parameter:
     * - data: Bit data to be written.
     */
     #define Dout1_Wrt(data)  Led_Wrt(1, data)


    /**
     * Writes a 1-bit of data (LOGIC_LOW or LOGIC_HIGH) to a digital output #2.
     * Parameter:
     * - data: Bit data to be written.
     */
     #define Dout2_Wrt(data)  Led_Wrt(2, data)


    /**
     * Writes a 1-bit of data (LOGIC_LOW or LOGIC_HIGH) to a digital output #3.
     * Parameter:
     * - data: Bit data to be written.
     */
     #define Dout3_Wrt(data)  Led_Wrt(3, data)




    /**
     * Sets a digital output specified by the id (change to logic LOGIC_HIGH).
     * Parameter:
     * - id: Id of the target digital output (DOUT_ID0,...,DOUT_ID3).
     */
    #define Dout_Set(id)    Led_Clr(id)

    /**
     * Resets a digital output specified by the id (change to logic LOGIC_LOW).
     * Parameter:
     * - id: Id of the target digital output (DOUT_ID0,...,DOUT_ID3).
     */
    #define Dout_Clr(id)    Led_Set(id)

    /**
     * Toggles a digital output specified by the id to the different logic.
     * Parameter:
     * - id: Id of the target digital output (DOUT_ID0,...,DOUT_ID3).
     */
    #define Dout_Inv(id)    Led_Inv(id)

    /**
     * Returns status (LOGIC_LOW or LOGIC_HIGH) of the digital output specified by the id.
     * Parameter:
     * - id: Id of the target digital output (DOUT_ID0,...,DOUT_ID3).
     */
    #define Dout_Get(id)    Led_Get(id)


    /**
     * Sets the digital output channel #0 (change to LOGIC_HIGH).
     */
    #define Dout0_Set()     (LED0_LAT = 1)

    /**
     * Sets the digital output channel #1 (change to LOGIC_HIGH).
     */
    #define Dout1_Set()     (LED1_LAT = 1)

    /**
     * Sets the digital output channel #2 (change to LOGIC_HIGH).
     */
    #define Dout2_Set()     (LED2_LAT = 1)

    /**
     * Sets the digital output channel #3 (change to LOGIC_HIGH).
     */
    #define Dout3_Set()     (LED3_LAT = 1)



    /**
     * Resets the digital output channel #0 (change to LOGIC_LOW).
     */
    #define Dout0_Clr()     (LED0_LAT = 0)

    /**
     * Resets the digital output channel #1 (change to LOGIC_LOW).
     */
    #define Dout1_Clr()     (LED1_LAT = 0)

    /**
     * Resets the digital output channel #2 (change to LOGIC_LOW).
     */
    #define Dout2_Clr()     (LED2_LAT = 0)

    /**
     * Resets the digital output channel #3 (change to LOGIC_LOW).
     */
    #define Dout3_Clr()     (LED3_LAT = 0)



    /**
     * Toggles the digital output channel #0.
     */
    #define Dout0_Inv()     (LED0_LAT = !LED0_LAT)

    /**
     * Toggles the digital output channel #1.
     */
    #define Dout1_Inv()     (LED1_LAT = !LED0_LAT)

    /**
     * Toggles the digital output channel #2.
     */
    #define Dout2_Inv()     (LED2_LAT = !LED0_LAT)

    /**
     * Toggles the digital output channel #3.
     */
    #define Dout3_Inv()     (LED3_LAT = !LED0_LAT)


    /**
     * Returns status (LOGIC_LOW or LOGIC_HIGH) of the digital output #0.
     */
    #define Dout0_Get()     (LED0_LAT = !LED0_LAT)

    /**
     * Returns status (LOGIC_LOW or LOGIC_HIGH) of the digital output #1.
     */
    #define Dout1_Get()     (LED1_LAT = !LED1_LAT)

    /**
     * Returns status (LOGIC_LOW or LOGIC_HIGH) of the digital output #2.
     */
    #define Dout2_Get()     (LED2_LAT = !LED2_LAT)

    /**
     * Returns status (LOGIC_LOW or LOGIC_HIGH) of the digital output #2.
     */
    #define Dout3_Get()     (LED3_LAT = !LED3_LAT)



    /**
     * Returns status (LOGIC_LOW or LOGIC_HIGH) of the digital input specified by the id.
     * Parameter:
     * - id: Id of the target digital output (DINP_ID0,...,DINP_ID3).
     */
    #define Dinp_Get(id)    Psw_Get(id)

    /**
     * Returns status (LOGIC_LOW or LOGIC_HIGH) of the digital input channel #0.
     */
    #define Dinp0_Get()     PSW0_PORT

    /**
     * Returns status (LOGIC_LOW or LOGIC_HIGH) of the digital input channel #1.
     */
    #define Dinp1_Get()     PSW1_PORT

    /**
     * Returns status (LOGIC_LOW or LOGIC_HIGH) of the digital input channel #2.
     */
    #define Dinp2_Get()     PSW2_PORT

    /**
     * Returns status (LOGIC_LOW or LOGIC_HIGH) of the digital input channel #3.
     */
    #define Dinp3_Get()     PSW3_PORT


    /**
     * Returns a byte of data representing the logic data of all digital input channels.
     * Bit4 to Bit7 are ignored and read as zero.
     */
    #define Dinp_Read()     (PSW_PORT&0xFF)

#endif // __DIO_H__
