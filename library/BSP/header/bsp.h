/************************************************************
 * File:    bsp.h                                           *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  18 February 2020                                *
 ************************************************************/

#ifndef __BPS_H__
    #define __BSP_H__

    #define Delay_mS( ms ) __delay_ms( ms )
    #define Delay_uS( ms ) __delay_us( ms )

    #include <BSP_Config.h>
    #include <BSP_Main.h>
    #include <BSP_Mcu.h>
    #include <BSP_SysTick.h>
    #include <BSP_Uart.h>
    #include <BSP_Led.h>
    #include <BSP_Dio.h>
    #include <BSP_Psw.h>
    #include <BSP_Uart.h>
    #include <BSP_Pwm.h>
    #include <BSP_Beep.h>
    #include <BSP_Adc.h>
    #include <BSP_PswKey.h>
    #include <BSP_LedBlink.h>


#endif
