/* ---------------------------------------------------------------------------*/
/*
  FeabhOS OS abstraction layer

  Task functions

*/
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
/* ---------------------------------------------------------------------------*/
#ifndef FEABHOS_TASK_H
#define FEABHOS_TASK_H

#include "feabhOS_errors.h"
#include "feabhOS_defs.h"
#include "feabhOS_time.h"

#ifdef __cplusplus
extern "C" {
#endif
  
/*
  This macro defines the maximum number of tasks
  available.  
  
  For targets that have memory limitations
  (for example, ARM Cortex M3) use a fixed number
  and the memory for tasks will be allocated 
  statically (at compile time).
  
  Set this value to NO_LIMIT and tasks will be
  allocated dynamically (with malloc) at run-time.
  This setting is only sensible if feabhOS is running
  on top of Windows or Posix, or similar.
*/
#define MAX_TASKS 4


typedef enum
{
  STACK_TINY   = OS_STACK_TINY,
  STACK_SMALL  = OS_STACK_SMALL,
  STACK_NORMAL = OS_STACK_NORMAL,
  STACK_LARGE  = OS_STACK_LARGE,
  STACK_HUGE   = OS_STACK_HUGE
    
} feabhOS_stack_size_t;


typedef enum
{
  PRIORITY_LOWEST  = OS_PRIORITY_LOWEST,
  PRIORITY_LOW     = OS_PRIORITY_LOW,
  PRIORITY_NORMAL  = OS_PRIORITY_NORMAL,
  PRIORITY_HIGH    = OS_PRIORITY_HIGH,
  PRIORITY_HIGHEST = OS_PRIORITY_HIGHEST
} feabhOS_priority_t;

typedef struct feabhOS_task* feabhOS_TASK;


feabhOS_error feabhOS_task_create     (feabhOS_TASK * const  pTask, 
                                       int (*pFunction)(void*),
                                       void *                param, 
                                       feabhOS_stack_size_t  stack, 
                                       feabhOS_priority_t    priority);

void          feabhOS_task_join       (feabhOS_TASK * const pTask);
void          feabhOS_task_setPriority(feabhOS_TASK * const pTask, feabhOS_priority_t prio);
void          feabhOS_task_destroy    (feabhOS_TASK * const pTask);

/* 
  Sleep and yield only ever apply to the calling task,
  so you don't need to specify which task that is.
*/
void          feabhOS_task_sleep(duration_mSec_t period);
void          feabhOS_task_yield(void);


#ifdef __cplusplus
}
#endif

#endif /* FEABHOS_TASK_H */
