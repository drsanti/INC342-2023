#ifndef __ESP_HTTP_CMDEX__
#define __ESP_HTTP_CMDEX__

    #include <ESP_At.h>
    #include <ESP_Wifi.h>


    /**
     * Server states.
     */
    #define HTTP_CMDEX_STATE_INITIAL    0x00    // Initial state, CIPMUX.
    #define HTTP_CMDEX_STATE_START      0x01    // Start the server.
    #define HTTP_CMDEX_STATE_WAITING    0x02    // Waiting for one or more requests.
    #define HTTP_CMDEX_STATE_REQUEST    0x03    // One or more clients requested.
    #define HTTP_CMDEX_STATE_WAITRES    0x04    // Wait for response updated.
    #define HTTP_CMDEX_STATE_RESPONSD   0x05    // Responding to a terget client.
    #define HTTP_CMDEX_STATE_CLOSE      0x06    // Close the current connection.


    /**
     * Request structure.
     */
    typedef struct {
        bool                pending;        // Waiting for response.
        int16_t             channel;        // Connecting channel.
        char *              pgetreq;        // Pointer to GET request memory.
    }request_info_t;


    #define MAX_REQUESTS    5               // Maximum of requests.
    /**
     * Server structure
     *
     */
    typedef struct {
        timer_t             *timer;                 // State control timer.
        int16_t             state;                  // Server operation state.
        request_info_t      requests[MAX_REQUESTS]; // Requests array.
        request_info_t      *target;                // Target for making the response.
        int16_t             put;                    // Put index.
        int16_t             get;                    // Get index.
        int16_t             cnt;                    // Request counter.

        int16_t             chunkState;             // Chunk respond state.
        int16_t             length;                 // Data length.
        bool                waitAt;

        const char *        ssid;                   // Pointer to Network SSID.
        const char *        pass;                   // Pointer to Network PASS.

        callback_t          req_callback;           // Request Callback function.
        callback_t          res_callback;           // Response Callback function.

    }http_cmdex_t;

     typedef struct {
        const char *        ptrRequest;     // Pointer to the IPD line.
        const char *        ptrResponse;    // Update in the user callback.
     }http_cmdex_event_t;



    /**
     * Initializes the WebServer object and set up all required settings.
     * Parameters:
     * - ssid: SSID of the network.
     * - pass: PASS of the network.
     * - req_callback: Callback function called when the server get a new request.
     * - res_callback: Callback function called before the server sends response data.
     */
    void Esp_HttpCmdexInit( const char *ssid, const char *pass, callback_t req_callback, callback_t res_callback );

    void Esp_HttpCmdexDoResponse( const char * data );



#endif // __ESP_HTTP_CMDEX__
