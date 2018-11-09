// -----------------------------------------------------------------------------
// usart_utils.c
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

#include <stdint.h>
#include "usart_utils.h"

// -----------------------------------------------------------------------------
// This code is stand-alone, so must hold all the
// configuration information it needs to work
//
typedef enum
{
  USART_1, USART_2, USART_3, USART_4, NUM_USARTS
} USART;


typedef enum
{
  GPIO_A, GPIO_B, GPIO_C, GPIO_D,
  GPIO_E, GPIO_F, GPIO_G, GPIO_H
} GPIO_port;


typedef enum
{
  AF_0, AF_1, AF_2,  AF_3,  AF_4,  AF_5,  AF_6,  AF_7,
  AF_8, AF_9, AF_10, AF_11, AF_12, AF_13, AF_14, AF_15
} Alt_fn;


// -----------------------------------------------------------------------------
// Configuration structures for each pin.  We make no
// assumptions whether the Tx and Rx pins are on the
// same port, or even use the same alternative function
//
typedef struct
{
  GPIO_port port;
  int       num;
  Alt_fn    fn;
} Pin_config;


typedef struct
{
  Pin_config Tx;
  Pin_config Rx;
} USART_config;


// -----------------------------------------------------------------------------
// A little bit of future proofing.
// This array is not necessary but, if in the future we
// want to support more than one USART, we can expand
// this code to support configurations for every USART
//
static USART_config config[NUM_USARTS] =
{
  [USART_3] = {
               .Tx = { GPIO_B, 10, AF_7 },
               .Rx = { GPIO_B, 11, AF_7 }
              }
};

static USART current = USART_3;


// -----------------------------------------------------------------------------
// Memory addresses
//
static const uint32_t AHB1_addr     = 0x40020000;
static const uint32_t ABH1_rcc_addr = 0x40023830;

// GPIO hardware registers
//
typedef struct
{
  uint32_t MODE;
  uint32_t TYPE;
  uint32_t SPEED;
  uint32_t PUSH_PULL;
  uint32_t IDR;
  uint32_t ODR;
  uint32_t BSRR;
  uint32_t LOCK;
  uint32_t ALT_FN_LOW;
  uint32_t ALT_FN_HIGH;
} GPIO_registers;


// Helper function for generating addresses
//
static inline uint32_t get_port_addr(GPIO_port port)
{
  return (AHB1_addr + (port * 0x400));
}

// -----------------------------------------------------------------------------
// Configure a GPIO pin according to the
// supplied configuration
//
static void enable(const Pin_config * const pin)
{
  // Mode settings
  //
  static const uint32_t pull_up   = 0x01;
  static const uint32_t alt_fn    = 0x02;
  static const uint32_t very_high = 0x03;

  // Hardware access pointers
  //
  volatile uint32_t * const AHB1_rcc   = (uint32_t*)ABH1_rcc_addr;
  volatile GPIO_registers * const port = (GPIO_registers*)get_port_addr(pin->port);

  // Enable the device
  //
  *AHB1_rcc |= (1 << pin->port);

  // Reset the pin's operation
  //
  port->MODE &= ~(0x03   << (pin->num * 2));
  port->MODE |=  (alt_fn << (pin->num * 2));

  port->SPEED &= ~(0x03      << (pin->num * 2));
  port->SPEED |=  (very_high << (pin->num * 2));

  port->PUSH_PULL &= ~(0x01    << pin->num);
  port->PUSH_PULL |=  (pull_up << pin->num);

  // The Alt-Fn configuration requires 4 bits per pin - hence
  // 64 bits in total.  Configuration for pins 0 - 7 is in
  // register ALT_FN_LOW; for pins 8 - 15 use ALT_FN_HIGH
  //
  if(pin->num < 8)
  {
    port->ALT_FN_LOW &= ~(0x0F    << (4 * (pin->num % 8)));
    port->ALT_FN_LOW |=  (pin->fn << (4 * (pin->num % 8)));
  }
  else
  {
    port->ALT_FN_HIGH &= ~(0x0F    << (4 * (pin->num % 8)));
    port->ALT_FN_HIGH |=  (pin->fn << (4 * (pin->num % 8)));
  }
}


// -----------------------------------------------------------------------------
//
void usart_enable_IO(void)
{
  enable(&config[current].Tx);
  enable(&config[current].Rx);
}




