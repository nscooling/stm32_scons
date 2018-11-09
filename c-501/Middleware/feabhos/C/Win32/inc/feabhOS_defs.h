/* ---------------------------------------------------------------------------*/
/*
  FeabhOS OS abstraction layer

  OS-specific definitions.
  These must be configured for the particular
  underlying OS.
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
#ifndef FEABHOS_DEFS_H
#define FEABHOS_DEFS_H

/* 
  Got to include the OS-specific configuration and header
  files.
*/
#include "windows.h"


/* ---------------------------------------------------------------------------*/
/*
  Stack size definitions
*/
#define OS_STACK_TINY   256
#define OS_STACK_SMALL  512
#define OS_STACK_NORMAL 1024
#define OS_STACK_LARGE  2048
#define OS_STACK_HUGE   4096


/* ---------------------------------------------------------------------------*/
/*
  Priority definitions
*/
#define OS_PRIORITY_LOWEST  THREAD_PRIORITY_LOWEST
#define OS_PRIORITY_LOW     THREAD_PRIORITY_BELOW_NORMAL
#define OS_PRIORITY_NORMAL  THREAD_PRIORITY_NORMAL
#define OS_PRIORITY_HIGH    THREAD_PRIORITY_ABOVE_NORMAL
#define OS_PRIORITY_HIGHEST THREAD_PRIORITY_HIGHEST


/* ---------------------------------------------------------------------------*/
/*
  OS-specific structures
*/

#define OS_TASK_TYPE               HANDLE
#define OS_MUTEX_TYPE              HANDLE
#define OS_SIGNAL_TYPE             HANDLE
#define OS_CONDITION_TYPE
#define OS_BINARY_SEMAPHORE_TYPE   HANDLE
#define OS_COUNTING_SEMAPHORE_TYPE HANDLE
#define OS_QUEUE_TYPE              


/* ---------------------------------------------------------------------------*/
/*
  OS-specific time durations
*/
typedef DWORD               OS_TIME_TYPE;
#define OS_ZERO_TIMEOUT     0
#define OS_INFINITE_TIMEOUT INFINITE


/* ---------------------------------------------------------------------------*/
/*
  OS-specific error types
*/
typedef DWORD  OS_ERROR_TYPE;

/* ---------------------------------------------------------------------------*/

#endif /* FEABHOS_DEFS_H */