/************************************************************
 * File:    ECC_Cmder.h                                     *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  12 March 2020                                   *
 ************************************************************/

#ifndef __RTL_CMDEX_CORE_H__

    #define __RTL_CMDEX_CORE_H__

    #include <bsp.h>
    #include <rtl.h>


    #define CMDEX_CMD_MAX       20
    #define CMDEX_CMD_LEN       32

    #define CMDEX_RET_ERR       -1
    #define CMDEX_RET_OK        +1

    /**
     * COMDEX Structure.
     */
    typedef struct {
        timer_t     *timer;
        char        cmds[CMDEX_CMD_MAX][CMDEX_CMD_LEN];
        int16_t     put;        // Queue put index.
        int16_t     get;        // Queue get index.
        int16_t     cnt;        // Queue count index.
        char        resp[48];
        callback_t  exec_callback;
        const char* cmd;        // Current command string.
        int         cmdi;       // Current command index.
    }cmdex_t;

    /**
     * CMDEX Event Structure.
     */
    typedef struct {
        int16_t         status;     // Comdex status.
        const char *    resp;       // Pointer to Comdex response string.
        const cmdex_t * sender;     // Pointer to sender,
    }cmdex_event_t;

    /**
     * Cmdex_Init
     * Initializes the Cmdex object and callback.
     * Parameter:
     * - callback: Callback function of the Comdex.
     */
    void Cmdex_Init( callback_t callback );


    /**
     * Cmdex_SetCallback
     * Sets the callback function of the Comdex.
     * Parameter:
     * - callback: Callback function of the Comdex.
     */
    void Cmdex_SetCallback( callback_t callback );


    /**
     * Cmdex_Execute
     * Executes the given command.
     * Parameter:
     * - line: Input command (line of string) ended with CRLF.
     */
    bool Cmdex_Execute( const char *line );



#endif // __RTL_CMDEX_CORE_H__
