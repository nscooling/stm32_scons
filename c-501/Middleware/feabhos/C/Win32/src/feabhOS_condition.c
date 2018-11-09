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

#include "feabhOS_condition.h"
#include "feabhOS_defs.h"
#include "feabhOS_signal.h"
#include "feabhOS_mutex.h"
#include "feabhOS_memory.h"

typedef struct feabhOS_condition
{
  feabhOS_SIGNAL signal;
  
} feabhOS_condition_t;


/*
  Condition structure allocation using dynamic
  memory. NOTE, as the FeabhOS scheduler
  never terminates we do not deallocate
  condition structure memory (in this implementation)
*/
#if MAX_CONDITIONS == NO_LIMIT
#undef MAX_CONDITIONS
#define MAX_CONDITIONS 0x7FFFFFF
#endif

static unsigned condition_index = 0;

static feabhOS_condition_t* allocate_condition()
{
  if(condition_index < MAX_CONDITIONS)
  {
    ++condition_index;
    return feabhOS_memory_alloc(sizeof(feabhOS_condition_t));
  }
  else
  {
    return 0;
  }
}



feabhOS_error feabhOS_condition_create(feabhOS_CONDITION * const pCondition)
{
  feabhOS_error err;
  feabhOS_condition_t *pTemp;

  pTemp = allocate_condition();
  if(pTemp != 0)
  {
    err = feabhOS_signal_create(&pTemp->signal);
  }
  else
  {
    /* No more conditions left to allocate! */
    err = ERROR_MEMORY;
  }
  (*pCondition) = pTemp;
  return err;
}


void feabhOS_condition_notify(feabhOS_CONDITION * const pCondition)
{
  feabhOS_signal_notify_all(&(*pCondition)->signal);
}


feabhOS_error feabhOS_condition_wait(feabhOS_CONDITION * const pCondition, feabhOS_MUTEX * const pMutex, duration_mSec_t timeout)
{
  feabhOS_error err;
  
  feabhOS_mutex_unlock(pMutex);
  err = feabhOS_signal_wait(&(*pCondition)->signal, timeout);
  feabhOS_mutex_lock(pMutex, WAIT_FOREVER);
  return err;
}


void feabhOS_condition_destroy(feabhOS_CONDITION * const pCondition)
{
  feabhOS_signal_destroy(&(*pCondition)->signal);
}
