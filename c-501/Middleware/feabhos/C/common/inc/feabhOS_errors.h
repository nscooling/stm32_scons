/* ---------------------------------------------------------------------------*/
/*
  FeabhOS OS abstraction layer

  Error codes

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
#ifndef FEABHOS_ERRORS_H
#define FEABHOS_ERRORS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
  ERROR_OK,
  
  ERROR_MEMORY,
  
  ERROR_PARAM,
  ERROR_STUPID,
  
  ERROR_TIMED_OUT,
  
  ERROR_QUEUE_EMPTY,
  ERROR_QUEUE_FULL,
  
  ERROR_UNKNOWN
    
} feabhOS_error;


#ifdef __cplusplus
}
#endif

#endif /* FEABHOS_ERRORS_H */
