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
#include "feabhOS_semaphore.h"
#include "feabhOS_defs.h"
#include "feabhOS_memory.h"
#include "windows.h"

typedef struct feabhOS_binary_semaphore
{
  OS_BINARY_SEMAPHORE_TYPE semaphore;
  
} feabhOS_binary_semaphore_t;


typedef struct feabhOS_counting_semaphore
{
  OS_COUNTING_SEMAPHORE_TYPE semaphore;
  
} feabhOS_counting_semaphore_t;

/*
Task structure allocation using dynamic
memory.NOTE, as the FeabhOS scheduler
never terminates we do not deallocate
signal structure memory(in this implementation)
*/

#if MAX_BINARY_SEMAPHORES == NO_LIMIT
#undef MAX_BINARY_SEMAPHORES
#define MAX_BINARY_SEMAPHORES 0x7FFFFFF
#endif

#if MAX_COUNTING_SEMAPHORES == NO_LIMIT
#undef MAX_COUNTING_SEMAPHORES
#define MAX_COUNTING_SEMAPHORES 0x7FFFFFF
#endif


static unsigned int binary_index = 0;
feabhOS_binary_semaphore_t* allocate_binary()
{
  if(binary_index < MAX_BINARY_SEMAPHORES)
  {
    ++binary_index;
    return feabhOS_memory_alloc(sizeof(feabhOS_binary_semaphore_t));
  }
  else
  {
    return 0;
  }
}

static unsigned int counting_index = 0;
feabhOS_counting_semaphore_t* allocate_counting()
{
  if(counting_index < MAX_COUNTING_SEMAPHORES)
  {
    ++counting_index;
    return feabhOS_memory_alloc(sizeof(feabhOS_counting_semaphore_t));
  }
  else
  {
    return 0;
  }
}


/*
  Common take/give functions.
*/
static feabhOS_error take(HANDLE handle, duration_mSec_t timeout);
static void          give(HANDLE handle);


/* ---------------------------------------------------------------------------*/
/*
  Binary semaphore functions
*/
feabhOS_error feabhOS_binary_semaphore_create(feabhOS_BINARY_SEMAPHORE * const pSemaphore)
{
  feabhOS_error err = ERROR_UNKNOWN;
  feabhOS_binary_semaphore_t *pTemp;

  pTemp = allocate_binary();
  if(pTemp != 0)
  {
    pTemp->semaphore = CreateSemaphore(NULL, 0, 1, NULL);
    err = ERROR_OK;
  }
  else
  {
    /* No more semaphores to allocate! */
    err = ERROR_MEMORY;
  }
  (*pSemaphore) = pTemp;
  return err;
}


feabhOS_error feabhOS_binary_semaphore_take(feabhOS_BINARY_SEMAPHORE * const pSemaphore, duration_mSec_t timeout)
{
  return take((*pSemaphore)->semaphore, timeout);
}


void feabhOS_binary_semaphore_give(feabhOS_BINARY_SEMAPHORE * const pSemaphore)
{
  give((*pSemaphore)->semaphore);
}


void feabhOS_binary_semaphore_destroy(feabhOS_BINARY_SEMAPHORE * const pSemaphore)
{
  CloseHandle((*pSemaphore)->semaphore);
}

/* ---------------------------------------------------------------------------*/
/*
  Counting semaphore functions
*/
feabhOS_error feabhOS_counting_semaphore_create(feabhOS_COUNTING_SEMAPHORE * const pSemaphore, 
                                                num_elements_t max_count, 
                                                num_elements_t init_count)
{
  feabhOS_error err = ERROR_UNKNOWN;
  feabhOS_counting_semaphore_t *pTemp;

  pTemp = allocate_counting();
  if(pTemp != 0)
  {
    pTemp->semaphore = CreateSemaphore(NULL, init_count, max_count, NULL);
    err = ERROR_OK;
  }
  else
  {
    /* No more semaphores to allocate! */
    err = ERROR_MEMORY;
  }
  (*pSemaphore) = pTemp;
  return err;  
}


feabhOS_error feabhOS_counting_semaphore_take(feabhOS_COUNTING_SEMAPHORE * const pSemaphore, duration_mSec_t timeout)
{
  return take((*pSemaphore)->semaphore, timeout);
}


void feabhOS_counting_semaphore_give(feabhOS_COUNTING_SEMAPHORE * const pSemaphore)
{
  give((*pSemaphore)->semaphore);
}


void feabhOS_counting_semaphore_destroy(feabhOS_COUNTING_SEMAPHORE * const pSemaphore)
{
  CloseHandle((*pSemaphore)->semaphore);
}

/* ---------------------------------------------------------------------------*/
/*
  Common semaphore functions
*/
feabhOS_error take(HANDLE handle, duration_mSec_t timeout)
{
  feabhOS_error err = ERROR_UNKNOWN;
  OS_ERROR_TYPE OSError;
  
  OSError = WaitForSingleObject(handle, (OS_TIME_TYPE)timeout);
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


void give(HANDLE handle)
{
  ReleaseSemaphore(handle, 1, NULL);
}

