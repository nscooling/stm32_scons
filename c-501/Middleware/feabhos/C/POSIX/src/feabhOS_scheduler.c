#include "feabhOS_scheduler.h"
#include "feabhOS_memory.h"


feabhOS_error feabhOS_scheduler_init(void)
{
  feabhOS_memory_init();
  return ERROR_OK;
}


feabhOS_error feabhOS_scheduler_start(void)
{
	// Should never return from this function
  for (;;);

  return ERROR_OK;
}
