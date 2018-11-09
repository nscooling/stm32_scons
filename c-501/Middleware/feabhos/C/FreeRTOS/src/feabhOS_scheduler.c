#include "feabhOS_scheduler.h"
#include "feabhOS_memory.h"
#include "FreeRTOS.h"
#include "task.h"


feabhOS_error feabhOS_scheduler_init(void)
{
  feabhOS_memory_init();
  return ERROR_OK;
}


feabhOS_error feabhOS_scheduler_start(void)
{
  vTaskStartScheduler();
  return ERROR_OK;
}
