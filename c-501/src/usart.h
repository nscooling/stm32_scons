// ----------------------------------------------------------------------------------
// usart.h
//
// DISCLAIMER:
// Feabhas is furnishing this item "as is". Feabhas does not provide any warranty
// of the item whatsoever, whether express, implied, or statutory, including, but
// not limited to, any warranty of merchantability or fitness for a particular
// purpose or any warranty that the contents of the item will be error-free.
// In no respect shall Feabhas incur any liability for any damages, including, but
// limited to, direct, indirect, special, or consequential damages arising out of,
// resulting from, or any way connected to the use of the item, whether or not
// based upon warranty, contract, tort, or otherwise; whether or not injury was
// sustained by persons or property or otherwise; and whether or not loss was
// sustained from, or arose out of, the results of, the item, or any services that
// may be provided by Feabhas.
// ----------------------------------------------------------------------------------

#ifndef USART_H_
#define USART_H_

#include <stdbool.h>
#include <stddef.h>

typedef enum
{
  BAUD_2400   = 0x1A0B,
  BAUD_9600   = 0x0683,
  BAUD_57600  = 0x0116,
  BAUD_115200 = 0x008B
} BaudRate;


typedef enum
{
  DATA_8_BITS,
  DATA_9_BITS
} DataLength;


typedef enum
{
  STOP_1_BIT,
  STOP_05_BIT,
  STOP_2_BIT,
  STOP_15_BIT
} StopBits;


typedef enum
{
  PARITY_DISABLE,
  PARITY_ENABLE
} ParityEnable;


typedef enum
{
  PARITY_EVEN,
  PARITY_ODD
} Parity;


// -------------------------------------------
// The default configuration for Feabhas
// targets is:
// baud      = BAUD_115200
// data      = DATA_8_BITS
// stop      = STOP_1_BIT
// parity_en = PARITY_DISABLE
// parity    = PARITY_ODD
//
typedef struct
{
  BaudRate     baud;
  DataLength   data;
  StopBits     stop;
  ParityEnable parity_en;
  Parity       parity;
} USART_config;


// If config is set to NULL then the default
// configuration for the target system is
// used.
//
void usart_init(USART_config * const config);


void usart_send(char val);
void usart_send_string(const char *str);

int  usart_get(void);
bool usart_try_get(int * const inout_val);


#endif // USART_H_
