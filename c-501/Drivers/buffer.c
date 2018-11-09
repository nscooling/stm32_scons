/*
 * buffer.c
 *
 * Created on: 27 Jun 2016
 * Author: Feabhas
 *
 * DISCLAIMER:
 * Feabhas is furnishing this item "as is". Feabhas does not provide any warranty
 * of the item whatsoever, whether express, implied, or statutory, including, but
 * not limited to, any warranty of merchantability or fitness for a particular
 * purpose or any warranty that the contents of the item will be error-free.
 * In no respect shall Feabhas incur any liability for any damages, including, but
 * limited to, direct, indirect, special, or consequential damages arising out of,
 * resulting from, or any way connected to the use of the item, whether or not
 * based upon warranty, contract, tort, or otherwise; whether or not injury was
 * sustained by persons or property or otherwise; and whether or not loss was
 * sustained from, or arose out of, the results of, the item, or any services that
 * may be provided by Feabhas.
 *
 */

#include <stddef.h>
#include "buffer.h"

static value_t      buffer[BUFFER_SIZE];  // Data store
static unsigned int write;                // Next input location
static unsigned int read;                 // Next output location
static unsigned int num_items;            // Current buffer size


void buffer_init(void)
{
}


Buffer_error buffer_add(value_t to_store)
{
  // NB: you can only write to the buffer if there's
  // space; otherwise return an error.
  //
  if (num_items == BUFFER_SIZE) return BUFFER_FULL;
  
  buffer[write] = to_store;
  ++num_items;
  ++write;
  if (write == BUFFER_SIZE) write = 0;

  return BUFFER_OK;
}


Buffer_error buffer_get(value_t * const to_get)
{
  // You can only read from a buffer if there's something
  // in it!
  //
  if (num_items == 0) return BUFFER_EMPTY;
  
  *to_get = buffer[read];
  --num_items;
  ++read;
  if (read == BUFFER_SIZE) read = 0;
    
  return BUFFER_OK;
}


bool buffer_is_empty(void)
{
  return (num_items == 0);
}
