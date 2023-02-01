#ifndef __ESP_WEB_SERVER__
#define __ESP_WEB_SERVER__

    #include <ESP_At.h>
    #include <ESP_Wifi.h>




    /**
     * Server states.
     */
    #define WEB_SERVER_STATE_INITIAL    0x00    // Initial state, CIPMUX.
    #define WEB_SERVER_STATE_START      0x01    // Start the server.
    #define WEB_SERVER_STATE_WAITING    0x02    // Waiting for one or more requests.
    #define WEB_SERVER_STATE_REQUEST    0x03    // One or more clients requested.
    #define WEB_SERVER_STATE_RESPONSD   0x04    // Responding to a terget client.
    #define WEB_SERVER_STATE_CLOSE      0x05    // Close the current connection.


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
        callback_t          callback;               // Callback function.
        bool                waitAt;

        const char *        ssid;                   // Pointer to Network SSID.
        const char *        pass;                   // Pointer to Network PASS.

    }webserver_t;

     typedef struct {
        const char *        ptrIpdLine; // Pointer to the IPD line.

        int16_t             getReqType; // Update in the user callback.
        const char *        ptrContent; // Update in the user callback.
        const char *        ptrHeader;  // Update in the user callback.
     }webserver_event_t;

    #define GET_REQUEST_TYPE_USR    0   // USER Request (Cmdex)
    #define GET_REQUEST_TYPE_HTML   1   // HTML Request (/index.html, /)
    #define GET_REQUEST_TYPE_CSS    2   // CSS Request (/index.css)
    #define GET_REQUEST_TYPE_JS     3   // JavaScript Request (/index.js)
    #define GET_REQUEST_TYPE_ICO    4   // Favicon.ico Request(/favicon.ico)



    /**
     * Chunk size (2048 is the maximum value).
     */
    #define CHUNK_SIZE   2048

    /**
     * Chunk info structure/
     */
    typedef struct {
        uint16_t         DataLength;    // Total size of the data.
        uint16_t         ChunkSize;     // Desired chunk size.
        uint16_t         NumFrames;     // Number of frames.
        uint16_t         RestBytes;     // Number of bytes of the last frame.
        uint16_t         SendBytes;     // Nuber of bytes to be sent.
        const char *     PtrFrame;      // Pointer to the data chunk.
    }chunk_info_t;

    /**
     * Initializes the WebServer object and set up all required settings.
     * Parameters:
     * - ssid: SSID of the network.
     * - pass: PASS of the network.
     * - callback: Callback function called when the server get a new request.
     */
    void Esp_WebServerInit( const char *ssid, const char *pass, callback_t callback );



#endif // __ESP_WEB_SERVER__
