/* ---------------------------------------------------------------------------*/
/*
  FeabhOS OS abstraction layer

  Mutex functions

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
#ifndef FEABHOS_MUTEX_H
#define FEABHOS_MUTEX_H

#include "feabhOS_defs.h"
#include "feabhOS_errors.h"
#include "feabhOS_time.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
  Mutexes are allocated statically (at compile-time)
  as part of the FeabhOS layer.  This macro defines
  the maximum number of mutexes available.

  For targets that have memory limitations
  (for example, ARM Cortex M3) use a fixed number
  and the memory for mutexes will be allocated
  statically (at compile time).

  Set this value to NO_LIMIT and mutexes will be
  allocated dynamically (with malloc) at run-time.
  This setting is only sensible if feabhOS is running
  on top of Windows or Posix, or similar.
*/
#define MAX_MUTEXES 4

//struct feabhOS_mutex;
typedef struct feabhOS_mutex* feabhOS_MUTEX;


feabhOS_error feabhOS_mutex_create (feabhOS_MUTEX * const pMutex);
feabhOS_error feabhOS_mutex_lock   (feabhOS_MUTEX * const pMutex, duration_mSec_t timeout);
void          feabhOS_mutex_unlock (feabhOS_MUTEX * const pMutex);
void          feabhOS_mutex_destroy(feabhOS_MUTEX * const pMutex);


#ifdef __cplusplus
}
#endif

#endif /* FEABHOS_MUTEX_H */



