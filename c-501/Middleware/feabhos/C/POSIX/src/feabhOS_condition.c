#include "feabhOS_condition.h"

#include "feabhOS_defs.h"
#include "feabhOS_signal.h"
#include "feabhOS_mutex.h"

typedef struct feabhOS_condition
{
  feabhOS_SIGNAL signal;
  
} feabhOS_condition_t;


static feabhOS_CONDITION getInstance(void)
{
  static feabhOS_condition_t conditions[MAX_CONDITIONS];
  static unsigned int next_condition = 0;

  if(next_condition < MAX_CONDITIONS)
  {
    return &conditions[next_condition++];
  }
  else
  {
    return NULL;
  }
}


feabhOS_error feabhOS_condition_create(feabhOS_CONDITION * const pCondition)
{
  feabhOS_CONDITION condition;
  feabhOS_error err = ERROR_UNKNOWN;

  condition = getInstance();
  
  if(condition != NULL)
  {
    err = feabhOS_signal_create(&condition->signal);
  }
  else
  {
    err = ERROR_MEMORY;
  }

  *pCondition = condition;

  return err;
}


void feabhOS_condition_notify(feabhOS_CONDITION * const pCondition)
{
  feabhOS_CONDITION condition = *pCondition;
  feabhOS_signal_notify_all(&condition->signal);
}


feabhOS_error feabhOS_condition_wait(feabhOS_CONDITION *pCondition, feabhOS_MUTEX * const pMutex, duration_mSec_t timeout)
{
  feabhOS_CONDITION condition = *pCondition;
  feabhOS_error err;
  
  feabhOS_mutex_unlock(pMutex);
  err = feabhOS_signal_wait(&condition->signal, timeout);
  feabhOS_mutex_lock(pMutex, WAIT_FOREVER);
  return err;
}


void feabhOS_condition_destroy(feabhOS_CONDITION * const pCondition)
{
  feabhOS_CONDITION condition = *pCondition;
  feabhOS_signal_destroy(&condition->signal);
}
