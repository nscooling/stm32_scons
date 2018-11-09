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
#include "feabhOS_mutex.h"
#include "feabhOS_defs.h"
#include "feabhOS_memory.h"

typedef struct feabhOS_mutex
{
  OS_MUTEX_TYPE lock;
  
} feabhOS_mutex_t;

/*
Mutex structure allocation using dynamic
memory. NOTE, as the FeabhOS scheduler
never terminates we do not deallocate
mutex structure memory (in this implementation)
*/
#if MAX_MUTEXES == NO_LIMIT
#undef MAX_MUTEXES
#define MAX_MUTEXES 0x7FFFFFF
#endif

static unsigned mutex_index = 0;

feabhOS_mutex_t* allocate_mutex()
{
  if(mutex_index < MAX_MUTEXES)
  {
    ++mutex_index;
    return feabhOS_memory_alloc(sizeof(feabhOS_mutex_t));
  }
  else
  {
    return 0;
  }
}


feabhOS_error feabhOS_mutex_create(feabhOS_MUTEX * const pMutex)
{
  feabhOS_error err = ERROR_UNKNOWN;
  feabhOS_mutex_t *pTemp;

  pTemp = allocate_mutex();
  if(pTemp != 0)
  {
    pTemp->lock = CreateMutex(NULL, FALSE, NULL);
    if(pTemp->lock == 0)
    {
      err = ERROR_UNKNOWN;
    }
    else
    {
      err = ERROR_OK;
    }
  }
  else
  {
    /* No more mutexes to allocate! */
    err = ERROR_MEMORY;
  }
  (*pMutex) = pTemp;
  return err;  
}


feabhOS_error feabhOS_mutex_lock(feabhOS_MUTEX * const pMutex, duration_mSec_t timeout)
{
  feabhOS_error err = ERROR_UNKNOWN;
  OS_ERROR_TYPE OSError;
  
  OSError = WaitForSingleObject((*pMutex)->lock, (OS_TIME_TYPE)timeout);
  switch(OSError)
  {
  case WAIT_OBJECT_0:
    err = ERROR_OK;
    break;

  case WAIT_TIMEOUT:
    err = ERROR_TIMED_OUT;
    break;

  default:
    err = ERROR_UNKNOWN;
    break;
  }
  return err;
}


void feabhOS_mutex_unlock(feabhOS_MUTEX * const pMutex)
{
  ReleaseMutex((*pMutex)->lock);
}


void feabhOS_mutex_destroy(feabhOS_MUTEX * const pMutex)
{
  CloseHandle((*pMutex)->lock);
}