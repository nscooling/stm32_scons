// -----------------------------------------------------------------------------
// steps.cpp
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

#include <stdbool.h>
#include "steps.h"
#include "timer.h"
#include "motor.h"
#include "sevensegment.h"
#include "buzzer.h"
#include "programkeys.h"
#include "door.h"

// ---------------------------------------------------------------
// Program step functions

void empty(const struct Config * const config)
{
   sevensegment_display(EMPTY);

   unsigned duration = config->dwell_period * config->num_cycles;
   sleep(duration);
}


void fill(const struct Config * const config)
{
  static bool first_time = true;

  if(first_time)
  {
    while(door_is_open()) buzzer_pulse();
    first_time = false;
  }

  sevensegment_display(2);

  unsigned duration = config->dwell_period * config->num_cycles;
  sleep(duration);
}


void heat(const struct Config * const config)
{
  sevensegment_display(HEAT);

  unsigned duration = config->dwell_period * config->num_cycles;
  sleep(duration);
}


void wash(const struct Config * const config)
{
  sevensegment_display(WASH);

  Motor_direction dir = CLOCKWISE;
  motor_set_direction(dir);

  for(unsigned int i = 0; i < config->num_cycles; ++i)
  {
    motor_on();
    sleep(config->rotation_period);
    motor_off();

    sleep(config->dwell_period);

    dir = ((dir == CLOCKWISE) ? ANTICLOCKWISE : CLOCKWISE);
    motor_set_direction(dir);
    sleep(config->rotation_period);
  }
}


void rinse(const struct Config * const config)
{
  sevensegment_display(RINSE);

  for (unsigned int i = 0; i < config->num_cycles; ++i)
  {
    motor_on();
    sleep(config->rotation_period);
    motor_off();
    sleep(config->dwell_period);
  }
}


void spin(const struct Config * const config)
{
   sevensegment_display(SPIN);

   unsigned duration = config->dwell_period * config->num_cycles;
   motor_on();
   sleep(duration);
   motor_off();
}


void dry(const struct Config * const config)
{
  unsigned duration = config->dwell_period * config->num_cycles;

  sevensegment_display(DRY);
  sleep(duration);
}


void complete(const struct Config * const config)
{
  unsigned duration = config->dwell_period * config->num_cycles;

  sevensegment_display(COMPLETE);
  buzzer_pulse();
  sleep(duration);
  sevensegment_blank();
}


void perform_step(Step step, const struct Config * const config)
{
  switch(step)
  {
  case EMPTY:
    empty(config);
    break;

  case FILL:
    fill(config);
    break;

  case HEAT:
    heat(config);
    break;

  case WASH:
    wash(config);
    break;

  case RINSE:
    rinse(config);
    break;

  case SPIN:
    spin(config);
    break;

  case DRY:
    dry(config);
    break;

  case COMPLETE:
    complete(config);
    break;

  // default:
  //   break;
  }
}


