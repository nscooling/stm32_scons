// -----------------------------------------------------------------------------
// programkeys.c
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

#include "programkeys.h"
#include "gpio.h"

typedef enum
{
  PS1 = 1,
  PS2,
  PS3,
  CANCEL,
  ACCEPT,
  LATCH = 14
} Programkey_bit;


void programkeys_init(void)
{
  gpio_init(PORT_D);
  gpio_set_as_input(PORT_D, PS1);
  gpio_set_as_input(PORT_D, PS2);
  gpio_set_as_input(PORT_D, PS3);
  gpio_set_as_input(PORT_D, CANCEL);
  gpio_set_as_input(PORT_D, ACCEPT);
  gpio_set_as_output(PORT_D, LATCH);
}


int programkeys_get(void)
{
  int val = 0;

  // Set the latch
  //
  gpio_set_bit(PORT_D, LATCH);

  // While the accept key has not been pressed,
  // grab the values of the program switch
  //
  do
  {
    if(gpio_is_set(PORT_D, PS1)) val |= 0x01;
    if(gpio_is_set(PORT_D, PS2)) val |= 0x02;
    if(gpio_is_set(PORT_D, PS3)) val |= 0x04;

    // If Cancel is pressed, drop the latch
    // and reset.
    //
    if(gpio_is_set(PORT_D, CANCEL))
    {
      val = 0;
      gpio_clear_bit(PORT_D, LATCH);
      gpio_set_bit(PORT_D, LATCH);
    }
  } while (!gpio_is_set(PORT_D, ACCEPT));

  // Drop the latch and wait for the
  // Accept key has been *released*
  //
  gpio_clear_bit(PORT_D, LATCH);
  while(gpio_is_set(PORT_D, ACCEPT))
  {
    // wait...
  }

  return val;
}

