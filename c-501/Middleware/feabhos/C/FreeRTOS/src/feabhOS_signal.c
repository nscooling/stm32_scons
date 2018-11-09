#include "feabhOS_signal.h"
#include "feabhOS_semaphore.h"

/*---------------------------------------*/
/* 
  NOTE:
  EmbOS does not support the idea of a 
  task-independent signal, so we must 
  simulate it with a binary semaphore
  (The 'semaphore-as-signal' pattern)
*/
/*---------------------------------------*/

typedef struct feabhOS_signal
{
  feabhOS_BINARY_SEMAPHORE signal;
  num_elements_t waitingTasks;
  
} feabhOS_signal_t;

/*
  Signal static allocation.
  For simplicity, every time a signal is 'created'
  by the client the next element in the array is
  used; until they are all gone.
  There is no re-use of signals in this implementation
*/
static feabhOS_SIGNAL getInstance(void)
{
  static feabhOS_signal_t signals[MAX_SIGNALS];
  static unsigned int next_signal = 0;

  if(next_signal < MAX_SIGNALS) return &signals[next_signal++];
  else                          return NULL;
}


feabhOS_error feabhOS_signal_create(feabhOS_SIGNAL * const pSignal)
{
  feabhOS_SIGNAL self;
  feabhOS_error  err;

  self = getInstance();
  if(self == NULL) return ERROR_MEMORY;

  err = feabhOS_binary_semaphore_create(&self->signal);
  if(err == ERROR_MEMORY) return ERROR_MEMORY;
  
  feabhOS_binary_semaphore_take(&self->signal, WAIT_FOREVER);
  self->waitingTasks = 0;

  *pSignal = self;
  return ERROR_OK;
}


void feabhOS_signal_notify_one(feabhOS_SIGNAL * const pSignal)
{
  feabhOS_SIGNAL self = *pSignal;

 /* Give the semaphore, releasing any waiting tasks */
  feabhOS_binary_semaphore_give(&self->signal);
  if(self->waitingTasks > 0)
  {
    self->waitingTasks--;
  }
}

void feabhOS_signal_notify_all(feabhOS_SIGNAL * const pSignal)
{
  feabhOS_SIGNAL self = *pSignal;

  /* Give the semaphore, releasing any waiting tasks */
  while(self->waitingTasks > 0)
  {
    feabhOS_binary_semaphore_give(&self->signal);
    self->waitingTasks--;
  }
}


feabhOS_error feabhOS_signal_wait(feabhOS_SIGNAL * const pSignal, duration_mSec_t timeout)
{
  feabhOS_SIGNAL self = *pSignal;
  (void) timeout;

  /* Attempt to take the semaphore, which should pend*/
  feabhOS_error err = ERROR_UNKNOWN;
  
  self->waitingTasks++;
  err = feabhOS_binary_semaphore_take(&self->signal, WAIT_FOREVER);
  
  return err;
}


void feabhOS_signal_destroy(feabhOS_SIGNAL * const pSignal)
{
  /* No cleanup in FreeRTOS. */
  (void) pSignal;
}
