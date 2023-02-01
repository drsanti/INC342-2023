#ifndef __ESP_HTTP_SERVER_H__
#define __ESP_HTTP_SERVER_H__

    #include <ESP_At.h>
    #include <ESP_Wifi.h>


    /**
     * Server states.
     */
    #define SERVER_STATE_INITIAL    0x00    // Initial state, CIPMUX.
    #define SERVER_STATE_START      0x01    // Start the server.
    #define SERVER_STATE_WAITING    0x02    // Waiting for one or more requests.
    #define SERVER_STATE_REQUEST    0x03    // One or more clients requested.
    #define SERVER_STATE_RESPONSD   0x04    // Responding to a terget client.
    #define SERVER_STATE_CLOSE      0x05    // Close the current connection.



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

        int16_t             respState;              // Respond state.
        int16_t             length;                 // Data length.
    }server_info_t;



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


    inline void Esp_HttpServerStart( void );
    inline void Esp_HttpServerStop( void );

    inline void Esp_HttpServerProcessRequest( wifi_event_t *evt );
    inline void Esp_HttpServerProcessCmdEvent ( esp_event_t *evt );


    //
    // Private functions
    //
    // void Server_StopWaiting( void );
    // inline bool Add_Request( int16_t channel, char ** line );
    // inline request_info_t * Get_Request( void );
    // inline void Chunk_Init( const char * data, uint16_t ChunkSize );





#endif // __ESP_HTTP_SERVER_H__
