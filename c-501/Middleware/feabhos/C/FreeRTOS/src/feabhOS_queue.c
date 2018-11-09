#include "feabhOS_queue.h"
#include "feabhOS_defs.h"

typedef struct feabhOS_queue
{
  OS_QUEUE_TYPE queue;
  
} feabhOS_queue_t;

/*
  Queue static allocation.
  For simplicity, every time a queue is 'created'
  by the client the next element in the array is
  used; until they are all gone.
  There is no re-use of queues in this implementation
*/
static feabhOS_QUEUE getInstance(void)
{
 static feabhOS_queue_t queues[MAX_QUEUES];
 static unsigned int next_queue = 0;

 if(next_queue < MAX_QUEUES) return &queues[next_queue++];
 else                        return NULL;
}


feabhOS_error feabhOS_queue_create(feabhOS_QUEUE * const pQueue, size_bytes_t elemSize, num_elements_t queueSize)
{
  feabhOS_QUEUE self;
  
  self = getInstance();
  if(self == NULL) return ERROR_MEMORY;

  self->queue = xQueueCreate((portBASE_TYPE)queueSize, (portBASE_TYPE)elemSize);
  if(self->queue == 0) return ERROR_MEMORY;

  *pQueue = self;
  return ERROR_OK;
}


feabhOS_error feabhOS_queue_put(feabhOS_QUEUE * const pQueue, void * const in,  duration_mSec_t timeout)
{
  feabhOS_QUEUE self = *pQueue;
  feabhOS_error err = ERROR_UNKNOWN;
  OS_ERROR_TYPE OSError;
  
  OSError = xQueueSendToBack(self->queue, in, (OS_TIME_TYPE)timeout);
  if(OSError == pdPASS)
  {
    err = ERROR_OK;
  }
  else
  {
    /* Timeout expired; and still no space on the queue. */
    err = ERROR_QUEUE_FULL;
  }
  return err;
}


feabhOS_error feabhOS_queue_get(feabhOS_QUEUE * const pQueue, void * const out, duration_mSec_t timeout)
{
  feabhOS_QUEUE self = *pQueue;
  feabhOS_error err = ERROR_UNKNOWN;
  OS_ERROR_TYPE OSError;
  
  OSError = xQueueReceive(self->queue, out, (OS_TIME_TYPE)timeout);
  if(OSError == pdPASS)
  {
    err = ERROR_OK;
  }
  else
  {
    /* Timeout expired; and still no items on the queue. */
    err = ERROR_QUEUE_EMPTY;
  }
  return err;
}


num_elements_t feabhOS_queue_size(feabhOS_QUEUE *pQueue)
{
  feabhOS_QUEUE self = *pQueue;
  return (num_elements_t)uxQueueMessagesWaiting(self->queue);
}


void feabhOS_queue_destroy(feabhOS_QUEUE *pQueue)
{
  feabhOS_QUEUE self = *pQueue;
  vQueueDelete(self->queue);
}

