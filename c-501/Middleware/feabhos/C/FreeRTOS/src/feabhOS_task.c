#include "feabhOS_task.h"
#include "FreeRTOS.h"
#include "task.h"

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


static void scheduledFunction(void *arg)
{
  feabhOS_task_callback_t* pCallback = (feabhOS_task_callback_t*)arg;
  pCallback->func(pCallback->parameter);
}

/* ----------------------------------------------------------------------------*/

/* 
	MEMORY MANAGEMENT FOR TASK STRUCTURES
        -------------------------------------
*/

/*
	for a FreeRTOS implementation we don't
	allow dynamic allocation of task structs.
	This is to keep control of heap memory in our
	limited-resource system.
  If the client has set MAX_TASKS to NO_LIMIT
	we need to stop compilation with an error.
*/
#if MAX_TASKS==NO_LIMIT
#error "You must not set MAX_TASKS to NO_LIMIT with FreeRTOS"
#endif

/*
  Task structure static allocation.
  For simplicity, every time a task is 'created'
  by the client the next element in the array is
  used; until they are all gone.
  There is no re-use of tasks in this implementation
*/
static feabhOS_TASK getInstance(void)
{
  static feabhOS_task_t tasks[MAX_TASKS];
  static unsigned int next_task = 0;

  if(next_task < MAX_TASKS) return &tasks[next_task++];
  else                      return NULL;
}


feabhOS_error feabhOS_task_create(feabhOS_TASK * const  pTask, 
                                  int (*pFunction)(void*),
                                  void *                param, 
                                  feabhOS_stack_size_t  stack,
                                  feabhOS_priority_t    priority)
{
  feabhOS_TASK  self;
  OS_ERROR_TYPE OS_error;
	
  self = getInstance();
  if(self == NULL) return ERROR_MEMORY;

  self->callback.func = pFunction;
  self->callback.parameter = param;

  OS_error = xTaskCreate(scheduledFunction,
                         "Task",
                         (portSHORT)(stack / sizeof(StackType_t)),
                         &self->callback,
                         (portBASE_TYPE)priority,
                         &self->handle);
  /*
    The OS will fail if it cannot allocate memory
    for (its own) control structures.
  */
  if(OS_error != pdPASS) return ERROR_MEMORY;
  
  *pTask = self;
  return ERROR_OK;
}


void feabhOS_task_join(feabhOS_TASK * const pTask)
{
  /*
    FreeRTOS does not support task joining
  */
  (void) pTask;
}


void feabhOS_task_setPriority(feabhOS_TASK * const pTask, feabhOS_priority_t prio)
{
  feabhOS_TASK self = *pTask;
  vTaskPrioritySet(&self->handle, (portBASE_TYPE)prio);
}


void feabhOS_task_destroy(feabhOS_TASK * const pTask)
{
  feabhOS_TASK self = *pTask;
  vTaskDelete(self->handle);
}


void feabhOS_task_sleep(duration_mSec_t period)
{
  portTickType delay = (OS_TIME_TYPE)(period) / portTICK_RATE_MS;
  vTaskDelay(delay);
}


void feabhOS_task_yield(void)
{
  feabhOS_task_sleep(0);
}



