/* ---------------------------------------------------------------------------*/
/*
  FeabhOS OS abstraction layer

  Semaphore functions

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
#ifndef FEABHOS_SEMAPHORE_H
#define FEABHOS_SEMAPHORE_H

#include "feabhOS_defs.h"
#include "feabhOS_errors.h"
#include "feabhOS_time.h"
#include "feabhOS_stdint.h"

#ifdef __cplusplus
extern "C" {
#endif
  
/*
  Semaphores are allocated statically (at compile-time)
  as part of the FeabhOS layer.  These macro defines
  the maximum number of semaphores available.
  
  For targets that have memory limitations
  (for example, ARM Cortex M3) use a fixed number
  and the memory for semaphores will be allocated
  statically (at compile time).

  Set this value to NO_LIMIT and semaphores will be
  allocated dynamically (with malloc) at run-time.
  This setting is only sensible if feabhOS is running
  on top of Windows or Posix, or similar.
*/
#define MAX_BINARY_SEMAPHORES   4
#define MAX_COUNTING_SEMAPHORES 4

typedef struct feabhOS_binary_semaphore*   feabhOS_BINARY_SEMAPHORE;
typedef struct feabhOS_counting_semaphore* feabhOS_COUNTING_SEMAPHORE;


/*
  Binary semaphore functions
*/
feabhOS_error feabhOS_binary_semaphore_create (feabhOS_BINARY_SEMAPHORE * const pSemaphore);
feabhOS_error feabhOS_binary_semaphore_take   (feabhOS_BINARY_SEMAPHORE * const pSemaphore, duration_mSec_t timeout);
void          feabhOS_binary_semaphore_give   (feabhOS_BINARY_SEMAPHORE * const pSemaphore);
void          feabhOS_binary_semaphore_destroy(feabhOS_BINARY_SEMAPHORE * const pSemaphore);

/*
  Counting semaphore functions
*/
feabhOS_error feabhOS_counting_semaphore_create (feabhOS_COUNTING_SEMAPHORE * const pSemaphore, num_elements_t max_count, num_elements_t init_count);
feabhOS_error feabhOS_counting_semaphore_take   (feabhOS_COUNTING_SEMAPHORE * const pSemaphore, duration_mSec_t timeout);
void          feabhOS_counting_semaphore_give   (feabhOS_COUNTING_SEMAPHORE * const pSemaphore);
void          feabhOS_counting_semaphore_destroy(feabhOS_COUNTING_SEMAPHORE * const pSemaphore);


#ifdef __cplusplus
}
#endif

#endif /* FEABHOS_SEMAPHORE_H */

