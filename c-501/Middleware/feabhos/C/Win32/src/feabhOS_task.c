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
#include "feabhOS_task.h"
#include "feabhOS_memory.h"
#include "windows.h"


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


static DWORD WINAPI scheduledFunction(LPVOID arg)
{
  feabhOS_task_callback_t* pCallback = (feabhOS_task_callback_t*)arg;
  return pCallback->func(pCallback->parameter);
}

/* ----------------------------------------------------------------------------
*/
static feabhOS_task_t* allocate_task();
static unsigned int task_index = 0;

/*
  Task structure allocation using dynamic
  memory. NOTE, as the FeabhOS scheduler 
  never terminates we do not deallocate
  task structure memory (in this implementation)
*/
#if MAX_TASKS == NO_LIMIT
#undef MAX_TASKS
#define MAX_TASKS 0x7FFFFFF
#endif

feabhOS_task_t* allocate_task()
{
  if(task_index < MAX_TASKS)
  {
    ++task_index;
    return feabhOS_memory_alloc(sizeof(feabhOS_task_t));
  }
  else
  {
    return 0;
  }
}


/* ----------------------------------------------------------------------------
*/
feabhOS_error feabhOS_task_create(feabhOS_TASK * const  pTask, 
                                  int(*pFunction)(void*), 
                                  void *                param, 
                                  feabhOS_stack_size_t  stack, 
                                  feabhOS_priority_t    priority)
{
  feabhOS_error err = ERROR_UNKNOWN;
  feabhOS_task_t* pTemp;
  
  pTemp = allocate_task();
  if(pTemp != 0)
  {
    pTemp->callback.func = pFunction;
    pTemp->callback.parameter = param;
    pTemp->handle = CreateThread(NULL, 
                                 stack, 
                                 scheduledFunction, 
                                 &(pTemp->callback), 
                                 CREATE_SUSPENDED, 
                                 NULL);
    SetThreadPriority(pTemp->handle, priority);
    ResumeThread(pTemp->handle);
  }
  else
  {
    err = ERROR_MEMORY;
  }
  (*pTask) = pTemp;
  return err;
}


void feabhOS_task_join(feabhOS_TASK * const pTask)
{
  WaitForSingleObject((*pTask)->handle, INFINITE);
}


void feabhOS_task_setPriority(feabhOS_TASK * const pTask, feabhOS_priority_t prio)
{
  SetThreadPriority((*pTask)->handle, prio);
}


void feabhOS_task_destroy(feabhOS_TASK * const pTask)
{
  CloseHandle((*pTask)->handle);
}


void feabhOS_task_sleep(duration_mSec_t period)
{
  Sleep((OS_TIME_TYPE)period);
}


void feabhOS_task_yield(void)
{
  feabhOS_task_sleep(0);
}
