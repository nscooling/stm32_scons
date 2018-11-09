// -----------------------------------------------------------------------------
// gpio.h
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

#ifndef GPIO_H_
#define GPIO_H_

#include <stdbool.h>

// -----------------------------------------------------------------------------
// GPIO functions
//
typedef enum
{
  PORT_A, PORT_B, PORT_C, PORT_D,
  PORT_E, PORT_F, PORT_G, PORT_H
} Port;


typedef unsigned int Pin_number;
typedef unsigned int bit_mask;


void gpio_init(Port port);

void gpio_set_as_output(Port port, Pin_number n);
void gpio_set_as_input(Port port, Pin_number n);

void gpio_set_bit(Port port, Pin_number n);
void gpio_set(Port port, bit_mask bits);

void gpio_clear_bit(Port port, Pin_number n);
void gpio_clear(Port port, bit_mask bits);

bool gpio_is_set(Port port, Pin_number n);



#endif // GPIO_H_
