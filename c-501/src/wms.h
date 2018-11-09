// -----------------------------------------------------------------------------
// wms.h
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

#ifndef WMS_H_
#define WMS_H_

#include "motor.h"
#include "sevensegment.h"
#include "programkeys.h"
#include "door.h"
#include "buzzer.h"
#include "timer.h"

// Convenience function that initialises
// all the hardware devices
//
void wms_init(void);

#endif // WMS_H_
