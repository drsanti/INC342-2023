/************************************************************
 * File:    BSP_Psw.h                                       *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  16 February 2020                                *
 ************************************************************/


#ifndef __BSP_PSW_H__

    #define __BSP_PSW_H__

    #include <BSP_Mcu.h>

    /*******************************************************
     * PSW IDs
     *******************************************************/
    #define PSW_ID_0        0       // PB Switch #0
    #define PSW_ID_1        1       // PB Switch #1
    #define PSW_ID_2        2       // PB Switch #2
    #define PSW_ID_3        3       // PB Switch #3

    #define PSW_MAX_KEYS    4

    /*******************************************************
     * PSW LOGIC(ON/OFF) FOR ACTIVE LOW
     *******************************************************/
    #define PSW_ON          0
    #define PSW_OFF         1

    /*******************************************************
     * PSW PORT
     *******************************************************/
    #define PSW_PORT        PORTB

    /*******************************************************
     * TRIS INPUT DIRECTION
     *******************************************************/
    #define PSW_TRIS_INP    1

    /*******************************************************
     * PSW TRIS
     *******************************************************/
    #define PSW0_TRIS   TRISBbits.TRISB4
    #define PSW1_TRIS   TRISBbits.TRISB5
    #define PSW2_TRIS   TRISBbits.TRISB6
    #define PSW3_TRIS   TRISBbits.TRISB7

    /*******************************************************
     * PSW PORT
     *******************************************************/
    #define PSW0_PORT   PORTBbits.RB4
    #define PSW1_PORT   PORTBbits.RB5
    #define PSW2_PORT   PORTBbits.RB6
    #define PSW3_PORT   PORTBbits.RB7

    /*******************************************************
     * PSW GET MACROS
     *******************************************************/
    #define Psw0_Get()  (!PSW0_PORT)
    #define Psw1_Get()  (!PSW1_PORT)
    #define Psw2_Get()  (!PSW2_PORT)
    #define Psw3_Get()  (!PSW3_PORT)


    /*******************************************************
     * Psw_Get
     * Returns the status of the target push button switch specified by the id.
     * It returns true if the PSW is on, false if the PSW is off.
     * Parameter:
     * - id: Id of the target switch (PSW_ID_0, PSW_ID_1, PSW_ID_2, PSW_ID_3)
     *******************************************************/
    bool Psw_Get(uint8_t id);

    /*******************************************************
     * Psw_Get
     * Return a byte (0x00-0x0F) data representing the status of the target push button switches.
     *******************************************************/
    uint8_t Psw_Read(void);


#endif // __BSP_PSW_H__
