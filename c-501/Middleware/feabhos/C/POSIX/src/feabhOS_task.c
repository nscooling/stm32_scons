#include "feabhOS_task.h"
#include "feabhOS_memory.h"
#include <pthread.h>
#include <unistd.h>

//typedef struct feabhOS_task
//{
//  OS_TASK_TYPE handle;
//
//} feabhOS_task_t;


/*
  Win32 requires a particular function signature for its threads.  To
  hide this (and stick with the feabhOS function signature) we must
  wrap the client's function and parameter into a structure and pass
  this structure to an intermediary function with the Win32 signature.
*/
typedef struct feabhOS_task_callback
{
  int (*func)(void*);
  void *parameter;

} feabhOS_task_callback_t;


typedef struct feabhOS_task
{
  OS_TASK_TYPE            handle;
  feabhOS_task_callback_t callback;

} feabhOS_task_t;


/*
 * Scheduled function is in a form that is compatible
 * with pthread calls.
 */
static void* scheduledFunction(void *arg)
{
  feabhOS_task_callback_t* pCallback = (feabhOS_task_callback_t*)arg;
  pCallback->func(pCallback->parameter);
  return NULL;
}

/* ----------------------------------------------------------------------------*/

/* 
	MEMORY MANAGEMENT FOR TASK STRUCTURES
        -------------------------------------
*/

static feabhOS_TASK getInstance(void)
{
	return (feabhOS_TASK) feabhOS_memory_alloc(sizeof(feabhOS_task_t));
}


feabhOS_error feabhOS_task_create(feabhOS_TASK * const  pTask, 
                                  int (*pFunction)(void*),
                                  void *                param, 
                                  feabhOS_stack_size_t  stack, 
                                  feabhOS_priority_t    priority)
{
	feabhOS_error err = ERROR_UNKNOWN;
	OS_ERROR_TYPE OSError;
  feabhOS_TASK  task;

  task = getInstance();
  if(task == NULL) return ERROR_MEMORY;

  task->callback.func = pFunction;
  task->callback.parameter = param;

  pthread_attr_t taskAttribute;
  pthread_attr_init(&taskAttribute);
  pthread_attr_setstacksize(&taskAttribute, stack);

	OSError = pthread_create(&task->handle,
													 &taskAttribute,
													 scheduledFunction,
													 &task->callback);
	if(OSError == 0)
	{
		err = ERROR_OK;
	}
	else
	{
		err = ERROR_MEMORY;
	}

  pthread_setschedprio(task->handle, priority);

  // Transfer ownership of task to client
  //
  *pTask = task;
  return err;
}


void feabhOS_task_join(feabhOS_TASK * const pTask)
{
	pthread_join((*pTask)->handle, NULL);
	/* TODO: Should we discard the return value? */
}


void feabhOS_task_setPriority(feabhOS_TASK * const pTask, feabhOS_priority_t prio)
{
  pthread_setschedprio((*pTask)->handle, prio);
}


void feabhOS_task_destroy(feabhOS_TASK * const pTask)
{
	// TODO: We don't have to destroy the structure on pthreads
}


void feabhOS_task_sleep(duration_mSec_t period)
{
	usleep(period * 1000);
}


void feabhOS_task_yield(void)
{
  feabhOS_task_sleep(0);
}



