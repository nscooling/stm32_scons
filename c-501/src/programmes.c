// -----------------------------------------------------------------------------
// programmes.c
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

#include <stddef.h>
#include "programmes.h"
#include "steps.h"

#define array_sizeof(arr) (sizeof(arr) / sizeof(arr[0]))

static void wash_programme(Step programme[], size_t size, const struct Config * const config)
{
  for(unsigned int i = 0; i < size; ++i)
  {
    perform_step(programme[i], config);
  }
}


// ---------------------------------------------------------------
// Wash programmes
//

void white_wash(void)
{
  static Step cycle[] = { 
    FILL, 
    HEAT, 
    WASH, 
    EMPTY, 
    FILL, 
    HEAT, 
    EMPTY, 
    RINSE, 
    EMPTY, 
    SPIN, 
    DRY, 
    COMPLETE 
  };

  static const struct Config config =
  {
    .rotation_period = 5000,
    .dwell_period    = 4000,
    .num_cycles      = 5
  };

  wash_programme(cycle, array_sizeof(cycle), &config);
}


void colour_wash(void)
{
  static Step cycle[] = { FILL, HEAT, WASH, RINSE, EMPTY, SPIN, DRY, COMPLETE };

  static const struct Config config =
  {
    .rotation_period = 6000,
    .dwell_period    = 4000,
    .num_cycles      = 6
  };

  wash_programme(cycle, array_sizeof(cycle), &config);
}


void mixed_wash(void)
{
  static Step cycle[] = { FILL, HEAT, WASH, EMPTY, SPIN, DRY, COMPLETE };

  static const struct Config config =
  {
    .rotation_period = 8000,
    .dwell_period    = 2000,
    .num_cycles      = 4
  };

  wash_programme(cycle, array_sizeof(cycle), &config);
}


void economy_wash(void)
{
  static Step cycle[] = { FILL, HEAT, WASH, SPIN, COMPLETE };

  static const struct Config config =
  {
    .rotation_period = 4000,
    .dwell_period    = 2000,
    .num_cycles      = 4
  };

  wash_programme(cycle, array_sizeof(cycle), &config);
}


void user1_wash(void)
{
  static Step cycle[] = { COMPLETE };

  static const struct Config config =
  {
    .rotation_period = 1000,
    .dwell_period    = 1000,
    .num_cycles      = 1
  };

  wash_programme(cycle, array_sizeof(cycle), &config);
}


void user2_wash(void)
{
  static Step cycle[] = { COMPLETE };

  static const struct Config config =
  {
    .rotation_period = 1000,
    .dwell_period    = 1000,
    .num_cycles      = 1
  };

  wash_programme(cycle, array_sizeof(cycle), &config);
}
