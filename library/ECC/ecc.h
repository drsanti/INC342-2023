/************************************************************
 * File:    ecc.h (system core)                             *
 * Description:                                             *
 *          Demonstrates how to use the RTOS, BSP and RTL.  *
 *          (Please see closely in the app.h and config.cfg)*
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 ************************************************************
 * Update:  23 February 2020                                *
 ************************************************************/

#ifndef __ECC_H__
    #define __ECC_H__

    // #define SYSTEM_DEFAULT_NETWORK_SSID "WLRT02"
    // #define SYSTEM_DEFAULT_NETWORK_PASS "WLRT11112"

    #define SYSTEM_DEFAULT_NETWORK_SSID "HttpServer"
    #define SYSTEM_DEFAULT_NETWORK_PASS "ecclab11112"


    /************************************************************
     * These two lines must be defined in the app.h
     ************************************************************/
    //#define ECC_SYSTEM_USE_RTL      0
    //#define ECC_SYSTEM_USE_RTOS     0

    #include <app.h>
    #include <bsp.h>
    #include <rtl.h>
    #include <iot.h>
    #include <cmd.h>

    #ifndef ECC_SYSTEM_USE_RTOS
        #define ECC_SYSTEM_USE_RTOS 0
    #endif


    #if ECC_SYSTEM_USE_RTOS > 0
        #include <rtos.h>
        void System_StartCoRutine(void);
        #define vTaskDelayMs(ms) vTaskDelay(ms / portTICK_PERIOD_MS)

    #endif

    #if ECC_SYSTEM_USE_RTOS > 0
        /**
         * Initialzes all modules.
         */
        #define System_Init() {		        \
        	Mcu_Init();				        \
            Beep_Init();                    \
            Led_BlinkInit();                \
            Adc_Init();                     \
            Uart1_Init( 115200, 64, 128 );  \
            Uart2_Init( 115200, 64, 128 );  \
            __delay_ms(1000);               \
        }
        /**
         * Starts CoRutine and Scheduler.
         */
        #define System_Start(){		        \
            System_StartCoRutine();         \
        	vTaskStartScheduler();          \
        }
    #else
        /**
         * Initialzes all modules.
         */
        #define System_Init() {		        \
        	Mcu_Init();				        \
            Beep_Init();                    \
            Led_BlinkInit();                \
            Adc_Init();                     \
            Uart1_Init( 115200, 64, 128 );  \
            Uart2_Init( 115200, 64, 128 );  \
            __delay_ms(1000);               \
        }
        /**
         * Start system tick and run executors of BSP and RTL.
         */
        #define System_Start(){		    \
            Sys_Start();                \
        	while(1) {				    \
                BSP_Executor();		    \
                RTL_Executor();		    \
            }						    \
        }
    #endif

#endif // __ECC_H__
