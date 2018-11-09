// -----------------------------------------------------------------------------
// main.c
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

#include "wms.h"
#include "programmes.h"


// Since only a single function needs to change
// we can use a macro to declare which function
// to use
//
#ifdef USE_CONSOLE
#define GET_USER_SELECTION usart_get_selection

// Addtional declarations
//
#include "usart.h"
extern int GET_USER_SELECTION(void);

#else
#define GET_USER_SELECTION  programkeys_get
#endif


// -----------------------------------------------------------------------------
// main
//
int main(void)
{
  wms_init();

  int selection = GET_USER_SELECTION();

  switch(selection)
  {
  case WHITE:
    white_wash();
    break;

  case COLOUR:
    colour_wash();
    break;

  case ECONOMY:
    economy_wash();
    break;

  case MIXED:
    mixed_wash();
    break;

  case USER1:
    user1_wash();
    break;

  case USER2:
    user2_wash();
    break;

  default:
    break;
  }

  return 0;
}

#ifdef USE_CONSOLE
// -----------------------------------------------------------------------------
// Use the USART to get the user selection
//
int usart_get_selection(void)
{
  usart_init(NULL);

  // Display menu
  //
  usart_send_string("\n\r");
  usart_send_string("***************************\n\r");
  usart_send_string("* Washing Machine Program *\n\r");
  usart_send_string("***************************\n\r");
  usart_send_string("1. White Wash\n\r");
  usart_send_string("2. Colour Wash\n\r");
  usart_send_string("3. Mixed Wash\n\r");
  usart_send_string("4. Economy Wash\n\r");
  usart_send_string("5. Program 1\n\r");
  usart_send_string("6. Program 2\n\r");
  usart_send_string("7. Exit to maintenance\n\r");
  usart_send_string("\nChoose a program by number\n\r");

  int selection = usart_get();

  // Convert from character to integer
  //
  selection -= '0';

  return selection;
}
#endif
