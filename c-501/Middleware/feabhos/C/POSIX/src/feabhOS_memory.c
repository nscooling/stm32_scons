#include "feabhOS_memory.h"
#include "feabhOS_mutex.h"
#include <stdlib.h>

static feabhOS_MUTEX memoryLock;

void feabhOS_memory_init(void)
{
  feabhOS_mutex_create(&memoryLock);
}

void *feabhOS_memory_alloc(size_bytes_t sz)
{
  void *requestedMemory = 0;
  
  feabhOS_mutex_lock(&memoryLock, WAIT_FOREVER);
  requestedMemory = malloc(sz);
  feabhOS_mutex_unlock(&memoryLock);
  return requestedMemory;
}


void  feabhOS_memory_dealloc(void * const pMemory)
{
  feabhOS_mutex_lock(&memoryLock, WAIT_FOREVER);
  free(pMemory);
  feabhOS_mutex_unlock(&memoryLock);
}
