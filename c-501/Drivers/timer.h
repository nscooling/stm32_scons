// -----------------------------------------------------------------------------
// timer.h
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

#ifndef SYSTICK_TIMER_H
#define SYSTICK_TIMER_H

#include <stdint.h>

#define TIMER_FREQUENCY_HZ (1000u)
typedef uint32_t timer_ticks_t;


// You must call timer_init() once
// (normally at the beginning of
// main()
//
void timer_init(void);

// -----------------------------------------------------------------------------
// The timer code (and associated sleep() function) are only
// available if the RTOS is not in use.
// Clients must use the RTOS sleep function for timing.
//
#ifndef RTOS

void sleep(timer_ticks_t ticks);

#endif
// -----------------------------------------------------------------------------



#endif // SYSTICK_TIMER_H
