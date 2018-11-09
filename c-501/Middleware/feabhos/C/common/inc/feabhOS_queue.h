/* ---------------------------------------------------------------------------*/
/*
  FeabhOS OS abstraction layer

  Queue functions

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
#ifndef FEABHOS_QUEUE_H
#define FEABHOS_QUEUE_H

#include "feabhOS_errors.h"
#include "feabhOS_time.h"
#include "feabhOS_stdint.h"

#ifdef __cplusplus
extern "C" {
#endif
  
/*
  The memory for a queue is allocated dynamically
  on construction, but the control structures for a
  queue are allocated statically (at compile-time)
  as part of the FeabhOS layer.  This macro defines
  the maximum number of queues available.

  For targets that have memory limitations
  (for example, ARM Cortex M3) use a fixed number
  and the memory for queues will be allocated
  statically (at compile time).

  Set this value to NO_LIMIT and queue structures will be
  allocated dynamically (with malloc) at run-time.
  This setting is only sensible if feabhOS is running
  on top of Windows or Posix, or similar.
*/
#define MAX_QUEUES 4

typedef struct feabhOS_queue* feabhOS_QUEUE;


feabhOS_error  feabhOS_queue_create (feabhOS_QUEUE * const pQueue, size_bytes_t elemSize, num_elements_t queueSize);
feabhOS_error  feabhOS_queue_put    (feabhOS_QUEUE * const pQueue, void * const in,  duration_mSec_t timeout);
feabhOS_error  feabhOS_queue_get    (feabhOS_QUEUE * const pQueue, void * const out, duration_mSec_t timeout);
num_elements_t feabhOS_queue_size   (feabhOS_QUEUE * const pQueue);
void           feabhOS_queue_destroy(feabhOS_QUEUE * const pQueue);


#ifdef __cplusplus
}
#endif

#endif /* FEABHOS_QUEUE_H */
