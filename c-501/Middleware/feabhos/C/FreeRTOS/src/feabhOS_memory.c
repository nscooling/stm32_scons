#include "feabhOS_memory.h"
#include "FreeRTOS.h"



void feabhOS_memory_init(void)
{
	// historical
}

void *feabhOS_memory_alloc(size_bytes_t sz)
{
  return pvPortMalloc(sz);
}


void  feabhOS_memory_dealloc(void * const pMemory)
{
	vPortFree(pMemory);
}
