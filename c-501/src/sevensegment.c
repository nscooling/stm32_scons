// -----------------------------------------------------------------------------
// sevensegment.c
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

#include "sevensegment.h"
#include "gpio.h"
#include "bit_manip.h"

typedef enum
{
  SEGMENT_A = 8,
  SEGMENT_B,
  SEGMENT_C,
  SEGMENT_D
} Sevensegment_bit;


void sevensegment_init(void)
{
  gpio_init(PORT_D);
  gpio_set_as_output(PORT_D, SEGMENT_A);
  gpio_set_as_output(PORT_D, SEGMENT_B);
  gpio_set_as_output(PORT_D, SEGMENT_C);
  gpio_set_as_output(PORT_D, SEGMENT_D);
  sevensegment_blank();
}


void sevensegment_display(int value)
{
  if(value < 10)
  {
    gpio_clear(PORT_D, bit_range(SEGMENT_A, SEGMENT_D));
    gpio_set(PORT_D, value << SEGMENT_A);
  }
}


void sevensegment_blank(void)
{
  gpio_set(PORT_D, bit_range(SEGMENT_A, SEGMENT_D));
}


