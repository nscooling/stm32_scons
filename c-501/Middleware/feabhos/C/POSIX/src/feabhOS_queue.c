#include "feabhOS_queue.h"
#include "feabhOS_defs.h"
#include "feabhOS_mutex.h"
#include "feabhOS_condition.h"
#include "feabhOS_memory.h"
#include <string.h>

typedef struct feabhOS_queue
{
  void*             pBuffer;
  size_bytes_t      elementSize;
  num_elements_t    capacity;
  num_elements_t    numItems;
  unsigned int      read;
  unsigned int      write;
  feabhOS_MUTEX     mutex;
  feabhOS_CONDITION notEmpty;
  feabhOS_CONDITION notFull;
  
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

  /*
        Set up each of the queue structure's fields.
  */
  (*pQueue)->pBuffer     = feabhOS_memory_alloc(elemSize * queueSize);
  (*pQueue)->elementSize = elemSize;
  (*pQueue)->capacity    = queueSize;
  (*pQueue)->read        = 0;
  (*pQueue)->write       = 0;
  (*pQueue)->numItems    = 0;
  feabhOS_mutex_create(&(*pQueue)->mutex);
  feabhOS_condition_create(&(*pQueue)->notEmpty);
  feabhOS_condition_create(&(*pQueue)->notFull);

  /*
	To do:  Add a LOT of error checking here...
  */
  return ERROR_OK;
}


feabhOS_error feabhOS_queue_put(feabhOS_QUEUE * const pQueue, void * const in,  duration_mSec_t timeout)
{
  feabhOS_error err = ERROR_UNKNOWN;
  uint8_t *writeLocation;

  feabhOS_mutex_lock(&(*pQueue)->mutex, WAIT_FOREVER);

  /* Sleep until there is space
   in the buffer.  If the condition
   times out, unlock and exit with
   no further processing.
  */
	while ((*pQueue)->numItems == (*pQueue)->capacity)
	{
		err = feabhOS_condition_wait(&(*pQueue)->notFull, &(*pQueue)->mutex, timeout);
		if(err == ERROR_TIMED_OUT)
		{
			feabhOS_mutex_unlock(&(*pQueue)->mutex);
			return err;
		}
	}

	/*
	Copy the item to the buffer.  Horrible pointer
	arithmetic ahead!
	*/
	writeLocation = (uint8_t *)(*pQueue)->pBuffer + ((*pQueue)->write * (*pQueue)->elementSize);
	memcpy(writeLocation, in, (*pQueue)->elementSize);
	(*pQueue)->numItems++;
	/*
	Move the write index (wrapping as necessary)
	*/
	(*pQueue)->write++;
	if((*pQueue)->write == (*pQueue)->capacity)
	{
		(*pQueue)->write = 0;
	}

	/* Signal any waiting tasks that there
	 is now some data in the buffer
	*/
	feabhOS_condition_notify(&(*pQueue)->notEmpty);

	feabhOS_mutex_unlock(&(*pQueue)->mutex);
	return err;
}


feabhOS_error feabhOS_queue_get(feabhOS_QUEUE * const pQueue, void * const out, duration_mSec_t timeout)
{
 feabhOS_error err = ERROR_UNKNOWN;
	uint8_t *readLocation;

	feabhOS_mutex_lock(&(*pQueue)->mutex, WAIT_FOREVER);

	/* Sleep until there is space
		 in the buffer.  If the condition
		 times out, unlock and exit with
		 no further processing.
	*/
	while ((*pQueue)->numItems == 0)
	{
		err = feabhOS_condition_wait(&(*pQueue)->notEmpty, &(*pQueue)->mutex, timeout);
		if(err == ERROR_TIMED_OUT)
		{
			feabhOS_mutex_unlock(&(*pQueue)->mutex);
			return err;
		}
	}

	/*
		Copy the item from  the buffer.  Horrible pointer
		arithmetic ahead!
	*/
	readLocation = (uint8_t *)(*pQueue)->pBuffer + ((*pQueue)->read * (*pQueue)->elementSize);
	memcpy(out, readLocation, (*pQueue)->elementSize);
	(*pQueue)->numItems--;
	/*
		Move the read index (wrapping as necessary)
	*/
	(*pQueue)->read++;
	if((*pQueue)->read == (*pQueue)->capacity)
	{
		(*pQueue)->read = 0;
	}

	/* Signal any waiting tasks that there
		 is now some data in the buffer
	*/
	feabhOS_condition_notify(&(*pQueue)->notFull);

	feabhOS_mutex_unlock(&(*pQueue)->mutex);
	return err;
}


num_elements_t feabhOS_queue_size(feabhOS_QUEUE *pQueue)
{
	return (*pQueue)->numItems;
}


void feabhOS_queue_destroy(feabhOS_QUEUE *pQueue)
{
  /*
    Make sure we clean up all the component parts
    of the queue.
  */
  feabhOS_memory_dealloc   (&(*pQueue)->pBuffer);
  feabhOS_mutex_destroy    (&(*pQueue)->mutex);
  feabhOS_condition_destroy(&(*pQueue)->notEmpty);
  feabhOS_condition_destroy(&(*pQueue)->notFull);
}

