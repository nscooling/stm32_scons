#include "feabhOS_mutex.h"
#include "feabhOS_defs.h"

typedef struct feabhOS_mutex
{
  OS_MUTEX_TYPE lock;
  
} feabhOS_mutex_t;

/*
  Mutex static allocation.
  For simplicity, every time a mutex is 'created'
  by the client the next element in the array is
  used; until they are all gone.
  There is no re-use of mutexes in this implementation
*/
static feabhOS_MUTEX getInstance(void)
{
  static feabhOS_mutex_t mutexes[MAX_MUTEXES];
  static unsigned int next_mutex = 0;
  if(next_mutex < MAX_MUTEXES) return &mutexes[next_mutex++];
  else                         return NULL;
}


feabhOS_error feabhOS_mutex_create(feabhOS_MUTEX * const pMutex)
{
  feabhOS_MUTEX self;

  self = getInstance();
  if(self == NULL) return ERROR_MEMORY;

  self->lock = xSemaphoreCreateMutex();
  if(self->lock == 0) return ERROR_MEMORY;

  *pMutex = self;
  return ERROR_OK;
}


feabhOS_error feabhOS_mutex_lock(feabhOS_MUTEX * const pMutex, duration_mSec_t timeout)
{
  feabhOS_MUTEX self = *pMutex;
  feabhOS_error err = ERROR_UNKNOWN;
  OS_ERROR_TYPE OSError;
  
  OSError = xSemaphoreTake(self->lock, (OS_TIME_TYPE)timeout);
  if (OSError == pdPASS)
  {
    err = ERROR_OK;
  }
  else
  {
    err = ERROR_TIMED_OUT;
  }
  return err;
}


void feabhOS_mutex_unlock(feabhOS_MUTEX * const pMutex)
{
  feabhOS_MUTEX self = *pMutex;
  xSemaphoreGive(self->lock);
}


void feabhOS_mutex_destroy(feabhOS_MUTEX * const pMutex)
{
  /* No clean-up in FreeRTOS. */
  (void) pMutex;
}
