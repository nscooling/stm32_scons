#include "feabhOS_mutex.h"
#include "feabhOS_defs.h"
#include "stddef.h"

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
  feabhOS_MUTEX mutex;
  OS_ERROR_TYPE OSError;
  feabhOS_error error;

  mutex = getInstance();
  if(mutex == NULL)
  {
    error = ERROR_MEMORY;
  }
  else
  {
    OSError = pthread_mutex_init(&mutex->lock, NULL);
    if(OSError == 0) error = ERROR_OK;
    else             error = ERROR_UNKNOWN;
  }
  *pMutex = mutex;
  return error;
}


feabhOS_error feabhOS_mutex_lock(feabhOS_MUTEX * const pMutex, duration_mSec_t timeout)
{
  feabhOS_MUTEX mutex = *pMutex;
  feabhOS_error error = ERROR_UNKNOWN;
  OS_ERROR_TYPE OSError;

  struct timespec abs_timeout;
  abs_timeout.tv_sec = timeout / 1000;
  abs_timeout.tv_nsec = (timeout - (abs_timeout.tv_sec * 1000)) * 1000000000UL;

  OSError = pthread_mutex_timedlock(&mutex->lock, &abs_timeout);

  if (OSError == 0) error = ERROR_OK;
  else            	error = ERROR_TIMED_OUT;
  return error;
}


void feabhOS_mutex_unlock(feabhOS_MUTEX * const pMutex)
{
  feabhOS_MUTEX mutex = *pMutex;
	pthread_mutex_unlock(&mutex->lock);
}


void feabhOS_mutex_destroy(feabhOS_MUTEX * const pMutex)
{
  feabhOS_MUTEX mutex = *pMutex;
	pthread_mutex_destroy(&mutex->lock);
}
