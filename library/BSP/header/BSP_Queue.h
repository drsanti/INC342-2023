/************************************************************
 * File:    BSP_Queue.h                                     *
 * Author:  Asst.Prof.Dr.Santi Nuratch                      *
 *          Embedded Computing and Control Laboratory       *
 *          ECC-Lab, INC, KMUTT, Thailand                   *
 * Update:  16 February 2020                                *
 ************************************************************/

#ifndef __BSP_QUEUE_H__

    #define __BSP_QUEUE_H__

    #include <BSP_Header.h>

    /********************************************************
     * ERROR CODE OF THE QUEUE
     ********************************************************/
    #define QUEUE_ERROR_NONE    0 // Queue operation success.
    #define QUEUE_ERROR_EMPTY   1 // Queue is empty.
    #define QUEUE_ERROR_FULL    2 // Queue is full.

    /********************************************************
     * DATA STRUCTURE OF THE QUEUE
     ********************************************************/
    typedef struct {
        char    *buf;   /* Buffer, an array of bytes        */
        uint16_t put;   /* Put index                        */
        uint16_t get;   /* Get index                        */
        uint16_t cnt;   /* Number of bytes in the quque     */
        uint16_t len;   /* Number of bytes of queue size    */
        uint16_t err;   /* Error code of the q operaions    */
    }Queue;

    /********************************************************
     * Queue_Init
     * Initializes the queue object.
     * Parameters:
     * - queue: Queue object.
     * - buffer: Buffer of characters.
     * - length: Buffer length in bytes.
     ********************************************************/
    void Queue_Init(Queue *queue, char *buffer, uint16_t length);


    /********************************************************
     * Queue_Put
     * Puts a byte of data into queue buffer.
     * Returns zero if the operation is failed.
     * Parameters:
     * - queue: Queue object.
     * - data: A byte data.
     ********************************************************/
    int16_t Queue_Put(Queue *queue, char data);


    /********************************************************
     * Queue_Get
     * Puts a byte of data into queue buffer.
     * Returns zero if the operation is failed.
     * Parameters:
     * - queue: Queue object.
     * - data: Out put byte data.
     ********************************************************/
    int16_t Queue_Get(Queue *queue, char *data);


    /********************************************************
     * Queue_Space
     * Returns free space of the queue buffer in bytes.
     * Parameter:
     * - queue: Queue object.
     ********************************************************/
    uint16_t Queue_Space(Queue *queue);


    /*******************************************************
     * Queue_Reset
     * Resets the queue object. All parameters are cleared.
     *******************************************************/
    void Queue_Reset(Queue *queue);

#endif // __BSP_QUEUE_H__
