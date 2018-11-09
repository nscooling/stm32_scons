#include "feabhOS_semaphore.h"
#include "feabhOS_defs.h"
#include <semaphore.h>

#include <errno.h>

typedef struct feabhOS_binary_semaphore
{
  OS_BINARY_SEMAPHORE_TYPE semaphore;
  
} feabhOS_binary_semaphore_t;


typedef struct feabhOS_counting_semaphore
{
  OS_COUNTING_SEMAPHORE_TYPE semaphore;
  
} feabhOS_counting_semaphore_t;

/*
  Semaphore static allocation.
  For simplicity, every time a semaphore is 'created'
  by the client the next element in the array is
  used; until they are all gone.
  There is no re-use of semaphores in this implementation
*/
static feabhOS_BINARY_SEMAPHORE getBinaryInstance(void)
{
  static feabhOS_binary_semaphore_t binary_semaphores[MAX_BINARY_SEMAPHORES];
  static unsigned int next_binary = 0;

  if(next_binary < MAX_BINARY_SEMAPHORES) return &binary_semaphores[next_binary++];
  else                                    return NULL;
}


static feabhOS_COUNTING_SEMAPHORE getCountingInstance(void)
{
  static feabhOS_counting_semaphore_t counting_semaphores[MAX_BINARY_SEMAPHORES];
  static unsigned int next_counting = 0;

  if(next_counting < MAX_COUNTING_SEMAPHORES) return &counting_semaphores[next_counting++];
  else                                        return NULL;
}

/*
  Common take/give functions.
*/
static feabhOS_error take(OS_SEMAPHORE_TYPE* const handle, duration_mSec_t timeout);
static void          give(OS_SEMAPHORE_TYPE* const handle);

/* ---------------------------------------------------------------------------*/
/*
  Binary semaphore functions
*/
feabhOS_error feabhOS_binary_semaphore_create(feabhOS_BINARY_SEMAPHORE * const pSemaphore)
{
  feabhOS_BINARY_SEMAPHORE sem;
  feabhOS_error            error;
  OS_ERROR_TYPE            OSError;

  sem = getBinaryInstance();
  if(sem == NULL) return ERROR_MEMORY;

  OSError = sem_init(&sem->semaphore,
                 0,  /* Not shared over procesess */
                 1); /* Initial values */

  if(OSError == 0) error = ERROR_OK;
  else             error = ERROR_MEMORY;

  *pSemaphore = sem;
  return error;
}


feabhOS_error feabhOS_binary_semaphore_take(feabhOS_BINARY_SEMAPHORE * const pSemaphore, duration_mSec_t timeout)
{
  feabhOS_BINARY_SEMAPHORE sem = *pSemaphore;
  feabhOS_error error;

  error = take(&sem->semaphore, timeout);
  return error;
}


void feabhOS_binary_semaphore_give(feabhOS_BINARY_SEMAPHORE * const pSemaphore)
{
  feabhOS_BINARY_SEMAPHORE sem = *pSemaphore;
  give(&sem->semaphore);
}


void feabhOS_binary_semaphore_destroy(feabhOS_BINARY_SEMAPHORE * const pSemaphore)
{
  feabhOS_BINARY_SEMAPHORE sem = *pSemaphore;
	sem_destroy(&sem->semaphore);
}

/* ---------------------------------------------------------------------------*/
/*
  Counting semaphore functions
*/
feabhOS_error feabhOS_counting_semaphore_create(feabhOS_COUNTING_SEMAPHORE * const pSemaphore, 
                                                num_elements_t max_count, 
                                                num_elements_t init_count)
{
  feabhOS_COUNTING_SEMAPHORE sem;
  feabhOS_error              error;
  OS_ERROR_TYPE              OSError;

  sem = getCountingInstance();
  if(sem == NULL) return ERROR_MEMORY;

  OSError = sem_init(&sem->semaphore,
                 0,           // Not shared over procesess
                 init_count); // Initial value

  if(OSError == 0) error = ERROR_OK;
  else             error = ERROR_MEMORY;

  *pSemaphore = sem;
  return error;
}


feabhOS_error feabhOS_counting_semaphore_take(feabhOS_COUNTING_SEMAPHORE * const pSemaphore, duration_mSec_t timeout)
{
  feabhOS_COUNTING_SEMAPHORE sem = *pSemaphore;
  feabhOS_error error;
	error = take(&sem->semaphore, timeout);
	return error;
}


void feabhOS_counting_semaphore_give(feabhOS_COUNTING_SEMAPHORE * const pSemaphore)
{
  feabhOS_COUNTING_SEMAPHORE sem = *pSemaphore;
	give(&sem->semaphore);
}


void feabhOS_counting_semaphore_destroy(feabhOS_COUNTING_SEMAPHORE * const pSemaphore)
{
  feabhOS_COUNTING_SEMAPHORE sem = *pSemaphore;
	sem_destroy(&sem->semaphore);
}

/* ---------------------------------------------------------------------------*/
/*
  Common semaphore functions
*/
feabhOS_error take(OS_SEMAPHORE_TYPE* const handle, duration_mSec_t timeout)
{
  feabhOS_error error = ERROR_UNKNOWN;
  OS_ERROR_TYPE OSError;

  struct timespec waitLength =
  {
    .tv_nsec = timeout * 1000 * 1000,
  };

  OSError = sem_timedwait(handle, &waitLength);
  if (OSError == 0)
  {
    error = ERROR_OK;
  }
  else
  {
    if(errno == ETIMEDOUT) error = ERROR_TIMED_OUT;
    else                   error = ERROR_UNKNOWN;
  }
  return error;
}


void give(OS_SEMAPHORE_TYPE* const handle)
{
  sem_post(handle);
}

