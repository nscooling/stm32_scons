/*
 * buffer.h
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

#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdbool.h>

// ------------------------------------------------------------------------
// Buffer configuration
//
#define BUFFER_SIZE 4   // number of elements; NOT bytes

typedef int value_t;    // change this to store different types;

// ------------------------------------------------------------------------
// Buffer error codes
typedef enum
{
  BUFFER_OK,
  BUFFER_FULL,
  BUFFER_EMPTY,
  BUFFER_UNKNOWN
} Buffer_error;

// ------------------------------------------------------------------------
//  Initialisation should be performed before the buffer is used.
//  The initialisation function sets up the buffer and ensures it is ready
//  to receive / retrieve data.
//
void buffer_init(void);

// ------------------------------------------------------------------------
//  The value to be added is passed as a parameter.
//  The value is stored in the buffer at the current free location.
//  If the buffer is full the value will not be stored and an error value
//  will be returned to the caller.
//
Buffer_error buffer_add(value_t to_store);

// ------------------------------------------------------------------------
//  The value at the current 'head' of the buffer is returned.
//  If the buffer is empty the return value pointer will be unchanged
//  and an error value is returned to the caller.
//
Buffer_error buffer_get(value_t * const to_get);


// ------------------------------------------------------------------------
//  Returns whether the buffer is currently
//  empty.
//
bool buffer_is_empty(void);

#endif
