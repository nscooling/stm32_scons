#include "feabhOS_semaphore.h"
#include "feabhOS_defs.h"

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
static feabhOS_error take(xSemaphoreHandle handle, duration_mSec_t timeout);
static void          give(xSemaphoreHandle handle);

/* ---------------------------------------------------------------------------*/
/*
  Binary semaphore functions
*/
feabhOS_error feabhOS_binary_semaphore_create(feabhOS_BINARY_SEMAPHORE * const pSemaphore)
{
  feabhOS_BINARY_SEMAPHORE self;

  self = getBinaryInstance();
  if(self == NULL) return ERROR_MEMORY;

  vSemaphoreCreateBinary(self->semaphore);
  if(self->semaphore == 0) return ERROR_MEMORY;
  
  *pSemaphore = self;
  return ERROR_OK;
}


feabhOS_error feabhOS_binary_semaphore_take(feabhOS_BINARY_SEMAPHORE * const pSemaphore, duration_mSec_t timeout)
{
  feabhOS_BINARY_SEMAPHORE self = *pSemaphore;
  return take(self->semaphore, timeout);
}


void feabhOS_binary_semaphore_give(feabhOS_BINARY_SEMAPHORE * const pSemaphore)
{
  feabhOS_BINARY_SEMAPHORE self = *pSemaphore;
  give(self->semaphore);
}


void feabhOS_binary_semaphore_destroy(feabhOS_BINARY_SEMAPHORE * const pSemaphore)
{
  /* No clean-up in FreeRTOS. */
  (void) pSemaphore;
}

/* ---------------------------------------------------------------------------*/
/*
  Counting semaphore functions
*/
feabhOS_error feabhOS_counting_semaphore_create(feabhOS_COUNTING_SEMAPHORE * const pSemaphore, 
                                                num_elements_t max_count, 
                                                num_elements_t init_count)
{
  feabhOS_COUNTING_SEMAPHORE self;

  self = getCountingInstance();
  if(self == NULL) return ERROR_MEMORY;
  
  self->semaphore = xSemaphoreCreateCounting((portBASE_TYPE)max_count, (portBASE_TYPE)init_count);
  if(self->semaphore == 0) return ERROR_MEMORY;

  *pSemaphore = self;
  return ERROR_OK;
}


feabhOS_error feabhOS_counting_semaphore_take(feabhOS_COUNTING_SEMAPHORE * const pSemaphore, duration_mSec_t timeout)
{
  feabhOS_COUNTING_SEMAPHORE self = *pSemaphore;
  return take(self->semaphore, timeout);
}


void feabhOS_counting_semaphore_give(feabhOS_COUNTING_SEMAPHORE * const pSemaphore)
{
  feabhOS_COUNTING_SEMAPHORE self = *pSemaphore;
  give(self->semaphore);
}


void feabhOS_counting_semaphore_destroy(feabhOS_COUNTING_SEMAPHORE * const pSemaphore)
{
  /* No clean-up in FreeRTOS. */
  (void) pSemaphore;
}


/* ---------------------------------------------------------------------------*/
/*
  Common semaphore functions
*/
feabhOS_error take(xSemaphoreHandle handle, duration_mSec_t timeout)
{
  feabhOS_error err = ERROR_UNKNOWN;
  OS_ERROR_TYPE OSError;
  
  OSError = xSemaphoreTake(handle, (OS_TIME_TYPE)timeout);
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


void give(xSemaphoreHandle handle)
{
  xSemaphoreGive(handle);
}
