// ----------------------------------------------------------------------------------
// usart.c
//
// DISCLAIMER:
// Feabhas is furnishing this item "as is". Feabhas does not provide any warranty
// of the item whatsoever, whether express, implied, or statutory, including, but
// not limited to, any warranty of merchantability or fitness for a particular
// purpose or any warranty that the contents of the item will be error-free.
// In no respect shall Feabhas incur any liability for any damages, including, but
// limited to, direct, indirect, special, or consequential damages arising out of,
// resulting from, or any way connected to the use of the item, whether or not
// based upon warranty, contract, tort, or otherwise; whether or not injury was
// sustained by persons or property or otherwise; and whether or not loss was
// sustained from, or arose out of, the results of, the item, or any services that
// may be provided by Feabhas.
// ----------------------------------------------------------------------------------

#include <stdlib.h>
#include "usart.h"
#include "peripherals.h"
#include "usart_utils.h"
#include "stm32f4xx.h"
#include "buffer.h"

// We are using only one of the STM32F4xx's USARTs
// in this project.  In this case, USART3
// These macros allow us to port to another
// USART in the future.
//
#define USART_BASE_ADDR   (APB1_BASE_ADDR + 0x4800)
#define USART_NAME         USART_3
#define TX_GPIO            GPIO_B
#define RX_GPIO            GPIO_B
#define TX_PIN             10
#define RX_PIN             11
#define USART_IRQ          USART3_IRQn
#define USART_ISR_HANDLER  USART3_IRQHandler

// Register structures
//
// Control Register 1
//
typedef struct
{
  uint32_t SBK      : 1;
  uint32_t RWU      : 1;
  uint32_t RE       : 1;
  uint32_t TE       : 1;
  uint32_t IDLEIE   : 1;
  uint32_t RXEIE    : 1;
  uint32_t TCIE     : 1;
  uint32_t TXEIE    : 1;
  uint32_t PEIE     : 1;
  uint32_t PS       : 1;
  uint32_t PCE      : 1;
  uint32_t WAKE     : 1;
  uint32_t M        : 1;
  uint32_t UE       : 1;
  uint32_t          : 18;
} Control1;


// Control Register 2
//
typedef struct
{
  uint32_t ADD      : 4;
  uint32_t          : 1;
  uint32_t LBDL     : 1;
  uint32_t LBDIE    : 1;
  uint32_t          : 1;
  uint32_t LBCL     : 1;
  uint32_t CPHA     : 1;
  uint32_t CPOL     : 1;
  uint32_t CLKEN    : 1;
  uint32_t STOP     : 2;
  uint32_t LINEN    : 1;
  uint32_t          : 17;
} Control2;

// Divisor (for baud rate)
//
typedef struct
{
  uint32_t fraction : 4;
  uint32_t mantissa : 12;
} BaudDivisor;


// Status register
//
typedef struct
{
  uint32_t PE       : 1;
  uint32_t FE       : 1;
  uint32_t NE       : 1;
  uint32_t ORE      : 1;
  uint32_t IDLE     : 1;
  uint32_t RXNE     : 1;
  uint32_t TC       : 1;
  uint32_t TXE      : 1;
  uint32_t LBD      : 1;
  uint32_t CTS      : 1;
  uint32_t Reserved : 22;
} Status;

// Data register
//
typedef union
{
  uint32_t Tx;
  uint32_t Rx;
} Data;


// Register mappings
//
static volatile Status      * const status    = (Status*)     (USART_BASE_ADDR + 0x00);
static volatile Data        * const data      = (Data*)       (USART_BASE_ADDR + 0x04);
static volatile BaudDivisor * const baud_div  = (BaudDivisor*)(USART_BASE_ADDR + 0x08);
static volatile Control1    * const control1  = (Control1*)   (USART_BASE_ADDR + 0x0C);
static volatile Control2    * const control2  = (Control2*)   (USART_BASE_ADDR + 0x10);


// Helper functions
//
static inline void    enable(void);
static inline void    disable(void);
static inline uint8_t read(void);
static inline void    write(uint8_t val);
static inline void    configure_interrupts(void);
static inline void    enable_rx_interrupt(void);
static inline void    disable_rx_interrupt(void);



// Default settings for the STM32F407
// target board
//
USART_config default_cfg =
{
  .baud      = BAUD_115200,
  .data      = DATA_8_BITS,
  .stop      = STOP_1_BIT,
  .parity_en = PARITY_DISABLE,
  .parity    = PARITY_ODD
};


void usart_init(USART_config * const config)
{
  // Enable the device (clock)
  //
  APB1_enable_device(USART_NAME);

  // Disable for configuration; then
  // (re)enable at the end of the function
  //
  disable();

  // Ensure there's a configuration
  //
  USART_config *cfg = (config != NULL? config : &default_cfg);

  // Set up the data transmission
  // characteristics.
  //
  control1->PS   = cfg->parity;
  control1->PCE  = cfg->parity_en;
  control1->M    = cfg->data;
  control2->STOP = cfg->stop;

  // Baud rate must be extracted from
  // the Baud_rate enum (Strictly, this
  // is not necessary; the value could be
  // written directly to the register)
  //
  baud_div->mantissa = cfg->baud >> 4;
  baud_div->fraction = cfg->baud & 0x0F;

  // Configure Tx and Rx pins
  //
  usart_enable_IO();

  configure_interrupts();
  enable();
}


void configure_interrupts(void)
{
  // Configure interrupt operation
  //
  NVIC_EnableIRQ(USART_IRQ);
  NVIC_SetPriority(USART_IRQ, 10);

  buffer_init();
  enable_rx_interrupt();
}


uint8_t read(void)
{
  return data->Rx;
}


void write(uint8_t val)
{
  data->Tx = val;
}


void enable(void)
{
  control1->UE = 1;
  control1->RE = 1;
  control1->TE = 1;
}


void disable(void)
{
  control1->UE = 0;
  control1->RE = 0;
  control1->TE = 0;
}


void enable_rx_interrupt(void)
{
  control1->RXEIE = 1;
}


void disable_rx_interrupt(void)
{
  control1->RXEIE = 0;
}


void usart_send(char val)
{
  while (status->TXE == 0)
  {
    // wait...
  }
  write(val);
}


void usart_send_string(const char *str)
{
  while (*str != '\0')
  {
    usart_send(*str);
    ++str;
  }
}


int usart_get(void)
{
  bool success;
  int val;
  do
  {
    success = usart_try_get(&val);
  } while(!success);
  return val;
}


bool usart_try_get(int * const inout_val)
{
  bool success;
  NVIC_DisableIRQ(USART_IRQ);

  success = (buffer_get(inout_val) != BUFFER_EMPTY);

  NVIC_EnableIRQ(USART_IRQ);
  return success;
}


void USART_ISR_HANDLER(void)
{
  buffer_add(read());
}


