/* ---------------------------------------------------------------------------*/
/*
  FeabhOS OS abstraction layer

  Signal functions

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
#ifndef FEABHOS_SIGNAL_H
#define FEABHOS_SIGNAL_H

#include "feabhOS_defs.h"
#include "feabhOS_errors.h"
#include "feabhOS_time.h"

#ifdef __cplusplus
extern "C" {
#endif
  
/*
  Signals are allocated statically (at compile-time)
  as part of the FeabhOS layer.  This macro defines
  the maximum number of signals available.

  For targets that have memory limitations
  (for example, ARM Cortex M3) use a fixed number
  and the memory for signals will be allocated
  statically (at compile time).

  Set this value to NO_LIMIT and signals will be
  allocated dynamically (with malloc) at run-time.
  This setting is only sensible if feabhOS is running
  on top of Windows or Posix, or similar.
*/
#define MAX_SIGNALS 4

typedef struct feabhOS_signal* feabhOS_SIGNAL;


feabhOS_error feabhOS_signal_create    (feabhOS_SIGNAL * const pSignal);
feabhOS_error feabhOS_signal_wait      (feabhOS_SIGNAL * const pSignal, duration_mSec_t timeout);
void          feabhOS_signal_notify_one(feabhOS_SIGNAL * const pSignal);
void          feabhOS_signal_notify_all(feabhOS_SIGNAL * const pSignal);
void          feabhOS_signal_destroy   (feabhOS_SIGNAL * const pSignal);


#ifdef __cplusplus
}
#endif

#endif /* FEABHOS_SIGNAL_H */

