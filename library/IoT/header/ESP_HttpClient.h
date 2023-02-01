/************************************************************
 * File:    ESP_HttpClient.h                                *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  19 March 2020                                   *
 ************************************************************/

#ifndef __ESP_HTTP_CLIENT_H__
    #define __ESP_HTTP_CLIENT_H__


    #include <ESP_At.h>
    #include <ESP_Wifi.h>

    #define HTTP_CLIENT_STATE_CONNECT        0  // Connecting to server.
    #define HTTP_CLIENT_STATE_PREPARE        1  // Prepare the request.
    #define HTTP_CLIENT_STATE_REQUEST        2  // Sent the request to the server.
    #define HTTP_CLIENT_STATE_WAITTING       3  // Waiting for the response from the server.
    #define HTTP_CLIENT_STATE_CLOSE          4  // Close the connection.
    #define HTTP_CLIENT_STATE_COMPLETED      5  // All operation are completed.
    #define HTTP_CLIENT_STATE_ERROR         -1  // Operation error.

    #define HTTP_CLIENT_RESP_TYPE_ERROR     -1  // Error
    #define HTTP_CLIENT_RESP_TYPE_HEADER     0  // Header
    #define HTTP_CLIENT_RESP_TYPE_CONTENT    1  // Content

    typedef struct {
        const char *        host;
        const char *        path;

        int16_t             state;
        timer_t *           timer;
        callback_t          res_callback;       // Got response callback
        callback_t          net_callback;       // Got IP callback
        const char *        ssid;
        const char *        pass;
    }http_client_t;

    typedef struct {
        int16_t         type;       // Response type (head or content).
        const char *    line;
        int16_t         length;
        http_client_t * sender;
    }http_client_event_t;



    void Esp_HttpClientRequest( const char *host, const char *path, callback_t response_callback );

    void Esp_HttpClientInit( const char *ssid, const char *pass, callback_t wifi_callback );


#endif // __ESP_HTTP_CLIENT_H__
