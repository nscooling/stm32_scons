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
#include "feabhOS_memory.h"
#include <stdlib.h>
#include "Windows.h"
#include "feabhOS_defs.h"
#include "feabhOS_time.h"

/* 
  NOTE:
  We cannot use the feabhOS mutex since that requires
  the memory functions to dynamically allocate memory.
  Doing so would result in a recursive loop.
  Instead we must directly call the underlying
  OS and use its mutual exclusion mechanism.
*/
static OS_MUTEX_TYPE memoryLock;

/*
  Helper functions for memory mutex.
*/
static void lock();
static void unlock();


void  feabhOS_memory_init(void)
{
  memoryLock = CreateMutex(NULL, FALSE, NULL);
}


void *feabhOS_memory_alloc(size_bytes_t sz)
{
  void *requestedMemory = 0;
  
  lock();
  requestedMemory = malloc(sz);
  unlock();
  return requestedMemory;
}


void  feabhOS_memory_dealloc(void * const pMemory)
{
  lock();
  free(pMemory);
  unlock();
}


void lock()
{
  WaitForSingleObject(memoryLock, (OS_TIME_TYPE)WAIT_FOREVER);
}

void unlock()
{
  ReleaseMutex(memoryLock);
}