// -----------------------------------------------------------------------------
// peripherals.h
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

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include <stdint.h>

// -----------------------------------------------------------------------------
// Utility functions to simplify enabling devices
//
// Base address for devices on the STM32F10x
//
#define FLASH_BASE_ADDR  ((uint32_t)0x08000000) // FLASH base address
#define SRAM_BASE_ADDR   ((uint32_t)0x20000000) // SRAM base address in the alias region
#define PERIPH_BASE_ADDR ((uint32_t)0x40000000) // Peripheral base address in the alias region

// Peripheral memory map
//
#define APB1_BASE_ADDR    ((uint32_t)(PERIPH_BASE_ADDR + 0x00000)) // Advanced Peripheral Bus 1
#define APB2_BASE_ADDR    ((uint32_t)(PERIPH_BASE_ADDR + 0x10000)) // Advanced Peripheral Bus 2
#define AHB1_BASE_ADDR    ((uint32_t)(PERIPH_BASE_ADDR + 0x20000)) // Advanced High-performance Bus 1

typedef enum
{
  GPIO_A    = 0,
  GPIO_B    = 1,
  GPIO_C    = 2,
  GPIO_D    = 3,
  GPIO_E    = 4,
  GPIO_F    = 5,
  GPIO_G    = 6,
  GPIO_H    = 7,
  GPIO_I    = 8
} AHB1_Device;

typedef enum
{
  TIMER_2   = 0,
  TIMER_3   = 1,
  TIMER_4   = 2,
  TIMER_5   = 3,
  TIMER_6   = 4,
  TIMER_7   = 5,
  TIMER_12  = 6,
  TIMER_13  = 7,
  TIMER_14  = 8,
  SPI_2     = 14,
  SPI_3     = 15,
  USART_2   = 17,
  USART_3   = 18,
  USART_4   = 19,
  USART_5   = 20,
  I2C_1     = 21,
  I2C_2     = 22,
  I2C_3     = 23
} APB1_Device;


void AHB1_enable_device(AHB1_Device device);
void APB1_enable_device(APB1_Device device);


#endif // PERIPHERALS_H_
