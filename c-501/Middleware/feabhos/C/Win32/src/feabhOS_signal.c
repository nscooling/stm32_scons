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
#include "feabhOS_signal.h"
#include "feabhOS_semaphore.h"
#include "feabhOS_memory.h"

typedef struct feabhOS_signal
{
  OS_SIGNAL_TYPE signal;
  num_elements_t waitingTasks;
  
} feabhOS_signal_t;


/*
Task structure allocation using dynamic
memory. NOTE, as the FeabhOS scheduler
never terminates we do not deallocate
signal structure memory (in this implementation)
*/
#if MAX_SIGNALS == NO_LIMIT
#undef MAX_SIGNALS
#define MAX_SIGNALS 0x7FFFFFF
#endif

static unsigned signal_index = 0;

feabhOS_signal_t* allocate_signal()
{
  if(signal_index < MAX_SIGNALS)
  {
    ++signal_index;
    return feabhOS_memory_alloc(sizeof(feabhOS_signal_t));
  }
  else
  {
    return 0;
  }
}


feabhOS_error feabhOS_signal_create(feabhOS_SIGNAL * const pSignal)
{
  feabhOS_error err = ERROR_UNKNOWN;
  feabhOS_signal_t* pTemp;

  pTemp = allocate_signal();
  if(pTemp != 0)
  {
    pTemp->signal = CreateEvent(NULL, FALSE, FALSE, NULL);
    if(pTemp->signal != NULL)
    {
      err = ERROR_OK;
    }
    pTemp->waitingTasks = 0;
  }
  else
  {
    /* No more signals left to allocate! */
    err = ERROR_MEMORY;
  }
  (*pSignal) = pTemp;
  return err;
}


void feabhOS_signal_notify_one(feabhOS_SIGNAL * const pSignal)
{
  SetEvent((*pSignal)->signal);
  if((*pSignal)->waitingTasks > 0)
  {
    (*pSignal)->waitingTasks--;
  }
}

void feabhOS_signal_notify_all(feabhOS_SIGNAL * const pSignal)
{
 /* Give the semaphore, releasing any waiting tasks */
  while((*pSignal)->waitingTasks > 0)
  {
    SetEvent((*pSignal)->signal);
    (*pSignal)->waitingTasks--;
  }
}


feabhOS_error feabhOS_signal_wait(feabhOS_SIGNAL * const pSignal, duration_mSec_t timeout)
{
  feabhOS_error err = ERROR_UNKNOWN;
  OS_ERROR_TYPE OSError;
  
  (*pSignal)->waitingTasks++;

  OSError = WaitForSingleObject((*pSignal)->signal, (OS_TIME_TYPE)timeout);
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

void feabhOS_signal_destroy(feabhOS_SIGNAL * const pSignal)
{
  CloseHandle((*pSignal)->signal);
}