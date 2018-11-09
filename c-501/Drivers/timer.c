// -----------------------------------------------------------------------------
// timer.c
//
// DISCLAIMER:
// Feabhas is furnishing this item "as is". Feabhas does not provide any
// warranty of the item whatsoever, whether express, implied, or statutory,
// including, but not limited to, any warranty of merchantability or fitness
// for a particular purpose or any warranty that the contents of the item will
// be error-free.
// In no respect shall Feabhas incur any liability for any damages, including,
// but limited to, direct, indirect, special, or consequential damages arising
// out of, resulting from, or any way connected to the use of the item, whether
// or not based upon warranty, contract, tort, or otherwise; whether or not
// injury was sustained by persons or property or otherwise; and whether or not
// loss was sustained from, or arose out of, the results of, the item, or any
// services that may be provided by Feabhas.
// -----------------------------------------------------------------------------

#include "timer.h"
#include "cmsis_device.h"


void timer_init(void)
{
  // Use SysTick as reference for the delay loops.
  //
  SysTick_Config(SystemCoreClock / TIMER_FREQUENCY_HZ);
}


// -----------------------------------------------------------------------------
//
#ifndef RTOS

static volatile timer_ticks_t timer_count;

void sleep(timer_ticks_t ticks)
{
  timer_count = ticks;

  // Busy wait until the SysTick decrements the counter to zero.
  //
  while (timer_count != 0U)
  {
  }
}


void SysTick_Handler(void)
{
  // Decrement to zero the counter used by the delay routine.
  //
  if(timer_count != 0U)
  {
    --timer_count;
  }
}


// -----------------------------------------------------------------------------
// FreeRTOS uses SysTick has its primary timer, so it is not available
// for client use.
//
#else

// From FreeRTOS port.c
//
void xPortSysTickHandler(void);


void SysTick_Handler(void)
{
  xPortSysTickHandler();
}

#endif
