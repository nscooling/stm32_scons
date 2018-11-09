/*
DISCLAIMER:
Feabhas is furnishing this item "as is". Feabhas does not provide any warranty
of the item whatsoever, whether express, implied, or statutory, including, but
not limited to, any warranty of merchantability or fitness for a particular
purpose or any warranty that the contents of the item will be error-free.
In no respect shall Feabhas incur any liability for any damages, including, but
limited to, direct, indirect, special, or consequential damages arising out of,
resulting from, or any way connected to the use of the item, whether or not
based upon warranty, contract, tort, or otherwise; whether or not injury was
sustained by persons or property or otherwise; and whether or not loss was
sustained from, or arose out of, the results of, the item, or any services that
may be provided by Feabhas.
*/
#include "feabhOS_queue.h"
#include "feabhOS_mutex.h"
#include "feabhOS_condition.h"
#include "feabhOS_memory.h"

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
Queue structure allocation using dynamic
memory. NOTE, as the FeabhOS scheduler
never terminates we do not deallocate
signal structure memory (in this implementation)
*/
#if MAX_QUEUES == NO_LIMIT
#undef MAX_QUEUES
#define MAX_QUEUES 0x7FFFFFF
#endif

static unsigned queue_index = 0;

feabhOS_queue_t* allocate_queue()
{
  if(queue_index < MAX_QUEUES)
  {
    ++queue_index;
    return feabhOS_memory_alloc(sizeof(feabhOS_queue_t));
  }
  else
  {
    return 0;
  }
}



feabhOS_error feabhOS_queue_create(feabhOS_QUEUE * const pQueue, size_bytes_t elemSize, num_elements_t queueSize)
{
  feabhOS_error err = ERROR_UNKNOWN;
  feabhOS_queue_t *pTemp;
  
  pTemp = allocate_queue();
  if(pTemp != 0)
  {
    /*
      Set up each of the queue structure's fields.
    */
    pTemp->pBuffer     = feabhOS_memory_alloc(elemSize * queueSize);
    pTemp->elementSize = elemSize;
    pTemp->capacity = queueSize;
    pTemp->read = 0;
    pTemp->write = 0;
    pTemp->numItems = 0;
    feabhOS_mutex_create(&(pTemp->mutex));
    feabhOS_condition_create(&(pTemp->notEmpty));
    feabhOS_condition_create(&(pTemp->notFull));
    
    /*
      To do:  Add a LOT of error checking here...
    */
    err = ERROR_OK;
  }
  else
  {
    /* No more queues to allocate! */
    err = ERROR_MEMORY;
  }
  (*pQueue) = pTemp;
  return err;  
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


num_elements_t feabhOS_queue_size(feabhOS_QUEUE * const pQueue)
{
  return (*pQueue)->numItems;
}


void feabhOS_queue_destroy(feabhOS_QUEUE * const pQueue)
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

