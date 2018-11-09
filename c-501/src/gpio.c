// -----------------------------------------------------------------------------
// gpio.c
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

#include "gpio.h"
#include "peripherals.h"
#include "bit_manip.h"

// Base address for all GPIO ports
//
#define GPIO_BASE_ADDR  ((uint32_t)AHB1_BASE_ADDR)


// GPIO hardware registers
//
typedef enum
{
  MODE,
  TYPE,
  SPEED,
  PUSH_PULL,
  IDR,
  ODR,
  BSRR,
  LOCK,
  ALT_FN1,
  ALT_FN2,
} GPIO_register;


static inline uint32_t get_port_addr(Port port)
{
  return (GPIO_BASE_ADDR + (port * 0x400));
}


static inline uint32_t get_reg_addr(Port port, GPIO_register reg)
{
  return (get_port_addr(port) + (reg * sizeof(uint32_t)));
}


void gpio_init(Port port)
{
  AHB1_enable_device(port);
}


void gpio_set_as_output(Port port, Pin_number n)
{
  volatile uint32_t * const pMODE = (uint32_t *)get_reg_addr(port, MODE);
  *pMODE |= (0x01 << (n * 2));
}


void gpio_set_as_input(Port port, Pin_number n)
{
  volatile uint32_t * const pMODE = (uint32_t *)get_reg_addr(port, MODE);
  *pMODE &= ~(0x03 << (n * 2));
}


void gpio_set_bit(Port port, Pin_number n)
{
  gpio_set(port, bit(n));
}


void gpio_set(Port port, bit_mask bits)
{
  volatile uint32_t * const pODR = (uint32_t *)get_reg_addr(port, ODR);
  *pODR |= bits;
}


void gpio_clear_bit(Port port, Pin_number n)
{
  gpio_clear(port, bit(n));
}


void gpio_clear(Port port, bit_mask bits)
{
  volatile uint32_t * const pODR = (uint32_t *)get_reg_addr(port, ODR);
  *pODR &= ~bits;
}


bool gpio_is_set(Port port, Pin_number n)
{
  volatile uint32_t * const pIDR = (uint32_t *)get_reg_addr(port, IDR);
  return is_set(*pIDR, n);
}

