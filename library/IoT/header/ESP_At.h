/************************************************************
 * File:    ESP_At.h                                        *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  19 March 2020                                   *
 ************************************************************/

#ifndef __ESP_AT_H__
#define __ESP_AT_H__

    #include <bsp.h>
    #include <rtl.h>

    /************************************************************
     *
     * AT
     *
     ************************************************************/

    /************************************************************
     * AT WORKING STATUSES
     ************************************************************/
    #define AT_STATUS_READY     0
    #define AT_STATUS_WAITING   1
    #define AT_STATUS_END_PKG   2 // \r\n
    #define AT_STATUS_GOT_RESP  3 // OK, ERROR, FAIL, ..., etc.

    #define AT_DEFAULT_TIMEOUT  5000

    #define AT_CAPTURE_ENABLED  true
    #define AT_CAPTURE_DISABLED false

    /************************************************************
     * AT RESPONSE CODES (RCODE)
     ************************************************************/
    #define AT_RESP_OK              0 // OK
    #define AT_RESP_SEND_OK         1 // SEND OK
    #define AT_RESP_BUSY            2 // Busy
    #define AT_RESP_NO_CHANGE       3
    #define AT_RESP_LINKED          4
    // #define AT_RESP_UNLINK          5
    // #define AT_RESP_READY           6
    #define AT_RESP_READY           5
    #define AT_RESP_UNLINK          6
    #define AT_RESP_ERROR           7
    #define AT_RESP_FAIL            8
    #define AT_RESP_TIMEOUT         9
    #define AT_RESP_UNKNOWN        -1

    #define AT_MAX_RESP_LINES 30    // Maximum of response lines.
    typedef struct {
        int16_t     items;                      // Number of items (lines).
        char *      lines[AT_MAX_RESP_LINES];   // Pointers to lines.
    }at_response_t;


    /************************************************************
     * AT-COMMAND OBJECT STRUCTURE
     ************************************************************/
    typedef struct {
        int16_t             rcode;          // Return code of the AT command.
        int16_t             status;         // Status, ready or waiting.
        bool                needData;       // The command needs response data.
       const char *         command;        // Pointer to the last command.
        timer_t *           timer;
        uint16_t            timeout;        // Timeout values.
        at_response_t       resp;           // Response data structure.
        callback_t          at_callback;    // Callback function of the command executor.

    }at_command_t;
    //extern at_command_t _at_;

    /************************************************************
     * ESP EVENT OBJECT STRUCTURE
     ************************************************************/
    typedef struct {
        int16_t         rcode;      // Return code of the AT command.
        const char *    rstr;       // Return string of the AT command.
        const char *    command;    // Pointer to the last command.
        at_response_t * response;   // Response data structure.
        at_command_t *  sender;     // Sender, the at command data structure.
    }esp_event_t;


    /**
     * Esp_AtGetResponseString
     * Returns the current response string of the AT command execution.
     */
    const char * Esp_AtGetResponseString( void );


    /**
     * Sets callback function of the at-command operation.
     * This callback function will be called at the end of the operation.
     * Parameter:
     * - callback: The callback function of the at-command operation.
     */
    void Esp_SetCmdCallback( callback_t callback );

    /**
     * Set the timeout of the AT operation.
     * It affects to the current waiting operation only.
     * The timeout value will be changed to DEFAULT value
     * when the Esp_AtSendData or Esp_AtSendCommand is called.
     * Parameter:
     * - timeout_ms: The timeout value in milliseconds.
     */
    void Esp_SetTimeout( uint16_t timeout_ms );

    /**
     * Send the command to the ESP module.
     * This function should be called when the at.waiting == false
     * Parameters:
     * - command: The command to be sent to the ESP module.
     * - timeout: Timeout value, in milliseconds, of the at-command operation.
     */
    void Esp_AtSendCommand( const char* command, uint16_t timeout );

    /**
     * Sends the command to the ESP module and captures all response lines.
     * This function should be called when the at.waiting == false
     * Parameters:
     * - command: The command to be sent to the ESP module.
     * - timeout: Timeout value, in milliseconds, of the at-command operation.
     * - capture: Capture enabled flag, true means enabled, false means disabled.
     */
    void Esp_AtSendCommandCapture( const char* command, uint16_t timeout, bool capture );

    /**
     * Send the data buffer to the ESP module.
     * This function should be called when the at.waiting == false
     * Parameters:
     * - buffer: Buffer containing bytes of data to be sent to the ESP.
     * - length: Number of bytes stored in the buffer.
     * - timeout: Timeout value, in milliseconds, of the sending operation.
     */
    void Esp_AtSendData( const char* buffer, uint16_t length, uint16_t timeout );

    /**
     * Enables the at-command capture operation.
     * This function must be called next to the call of the
     * Esp_AtSendData() or Esp_AtSendCommand(). Because the two functions
     * reset the capture flag by default.
     * Parameter:
     * - enabled: Enabled flag, true means enabled, false means disabled.
     */
    void Esp_AtEnableCapture( bool enabled );


    int16_t Esp_AtGetResponseCode( void );


    /**
     * Esp_AtProcessLine
     * Precesses incoming lines sent from the ESP.
     * This function must be called by the ESP line received callback.
     * The AT and WiFi states and operations are performed in this function.
     * Parameter:
     *  - line: A line of data to be processed.
     */
    void Esp_AtProcessLine( const char*  line );


#endif // __ESP_AT_H__
