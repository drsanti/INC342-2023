/************************************************************
 * File:    HTTP_Server.h                                   *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  19 March 2020                                   *
 ************************************************************/

#ifndef __HTTP_CORE_SERVER_H__
#define __HTTP_CORE_SERVER_H__



    typedef struct {
        int         state;
        int         channel;
        int         length;
        bool        gotresp;
        const char  *getResponse;      // Pointer to the response buffer.
        timer_t     *timer;
        char        *getRequest;
        callback_t  req_callback;
        callback_t  res_callback;
        callback_t  line_callback;
    }http_t;

    typedef struct {
        const char      *line;
        const char      *getRequest;    // Pointer to the GET request path.
        const char      *getResponse;   // Pointer to the GET response buffer.
        http_t    *sender;
    }http_event_t;


    void Http_SetLineReceivedCallback( callback_t callback );
    void Http_ServerStart( const char *ssid, const char *pass, callback_t req_callback, callback_t res_callback );


#endif // __HTTP_CORE_SERVER_H__
