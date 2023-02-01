/************************************************************
 * File:    ESP_Wifi.h                                      *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  19 March 2020                                   *
 ************************************************************/

#ifndef __ESP_WIFI_H__
#define __ESP_WIFI_H__

    #include <ESP_At.h>

    typedef struct {
        const char *    ssid;
        const char *    pass;
        char            ip[16]; //xxx.xxx.xxx.xxx
        callback_t      callback;
    }network_info_t;


    /************************************************************
     *
     * WIFI
     *
     ************************************************************/

    #define WIFI_STATUS_UNKNOWN    -1       // Unknown in the initial state.
    #define WIFI_STATUS_READY       0       // Ready (After reseting).
    #define WIFI_STATUS_DISCONNECT  1       // Disconnected from the network.
    #define WIFI_STATUS_CONNECTED   2       // Connected to the network.
    #define WIFI_STATUS_GOT_IP      3       // Got IP address.


    /************************************************************
     * WIFI OBJECT STRUCTURE
     ************************************************************/

    typedef struct {
        int16_t         status;             // WiFi status.
        callback_t      wifi_callback;      // WiFi State Changed callback function.
        callback_t      data_callback;      // WiFi Data Received callback function.

        const char *    ssid;
        const char *    pass;
    }wifi_t;
    extern wifi_t wifi;

    #define RECV_STATE_INITIAL        0x00  // Initial state.
    #define RECV_STATE_WAITING        0x01  // Waiting for IPD line.
    #define RECV_STATE_START_HEAD     0x02  // Got the IPD line.
    #define RECV_STATE_RECEIVING      0x04  // Receiving lines of data.
    #define RECV_STATE_END_HEAD       0x08  // Got the CRLF, the end of header.
    #define RECV_STATE_COLLECTING     0x10  // Collecting the content.
    #define RECV_STATE_COMPLETED      0x20  // All lines are received.


    #define WIFI_MODE_CLIENT          0     // Client mode based on the IPD line.
    #define WIFI_MODE_SERVER          1     // Server mode based on the IPD line.

    /************************************************************
     * WIFI EVENT OBJECT STRUCTURE
     ************************************************************/
    typedef struct {
        int16_t         status;             // WiFi status code.
        const char*     sname;              // WiFi status name.
        int16_t         channelId;          // Client connected channel.
        char *          line;               // Current received line.
        int16_t         mode;               // Operation mode based on IPD line.
        int16_t         totalBytes;         // Total bytes of the current package (including hidden bytes).
        int16_t         recvBytes;          // Number of the received bytes.
        int16_t         recvState;          // REceiving state.

        wifi_t *        sender;             // WiFi object.
    }wifi_event_t;


    void Esp_SetWiFiStateChangedCallback( callback_t callback );

    void Esp_SetWiFiDataReceivedCallback( callback_t callback );


    int16_t Esp_WiFiProcessLine( uart_event_t *event );

    inline void Esp_Init( bool reset );

    void Esp_JoinAccessPoint( const char *ssid, const char *pass );

    void Esp_WiFiConnectToNetwork( const char *ssid, const char *pass);

    //
    // HELPER FUNCTIONS
    //
    /**
     * IPD_Check
     * Check if the input string is the IPD line.
     * Returns true if the input string is the IPD line.
     * Parameter:
     * - line: Input string to be checked.
     */
    bool IPD_Check( const char *line );

    int16_t IPD_GetChannel( const char *line );

    int16_t IPD_GetDataLength( const char *line );

    char * HTTP_GetRequestPath( const char* line, char *pathOut );

    char * HTTP_GetWebSocketKey( const char *line, char *uff25 );


#endif // __ESP_WIFI_H__
