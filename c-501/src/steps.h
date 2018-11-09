// -----------------------------------------------------------------------------
// steps.h
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

#ifndef STEPS_H_
#define STEPS_H_

#include <stdint.h>

/* Program step functions */

typedef enum { EMPTY, FILL, HEAT, WASH, RINSE, SPIN, DRY, COMPLETE } Step;

struct Config
{
  unsigned rotation_period;
  unsigned dwell_period;
  unsigned num_cycles;
};


void perform_step(Step s, const struct Config * const config);

void empty(const struct Config * const config);
void fill(const struct Config * const config);
void heat(const struct Config * const config);
void wash(const struct Config * const config);
void rinse(const struct Config * const config);
void spin(const struct Config * const config);
void dry(const struct Config * const config);
void complete(const struct Config * const config);

#endif // STEPS_H_
