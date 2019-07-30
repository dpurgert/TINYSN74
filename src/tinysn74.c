/***********************************************************************
*
*                 Program: SN74HC595 Library - sn74.c
*                      by: Dan Purgert <dan@djph.net>    
*               copyright: 2018
*                 version: 0.6
*                    date: Fri, 19 Jul 2019 19:27:13 -0400
*                 purpose: Library for the SN74HC595 shift register, as
*                        : it's readily available from suppliers
*
*                 license: GPL v2 (only)
*              repository: http://github.com/dpurgert
*
*  This program is free software; you can redistribute it and/or
*  modify it under the terms of the GNU General Public License
*  as published by the Free Software Foundation.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
*  02110-1301, USA.
***********************************************************************/

/**
 * @file
 * @brief Library to drive SN74HC595 chips with ATTiny microcontrollers.
 *
 * This library provides the necessary hooks for you to control Texas
 * Instruments SN74HC595 shift registers (or equivalent).
*/

/** AVR IO Library */
//#include <avr/io.h>
/** @brief AVR Interrupt Library */
#include <avr/interrupt.h>
/** @brief For _delay_ms() */
#include <util/delay.h>

/** @brief Library configuration file */
#include "tinysn74_config.h"
/** @brief Library headers */
#include "tinysn74.h"

/** @brief DEBUG = 1 for debugging / slowing things down */
#define DEBUG 1


/** @brief sends a pulse to the pin (i.e. set logic high, then low)*/
#define pulse(port,pin) port |= _BV(pin); port &= ~_BV(pin);

/** @brief pulls a pin logic high */
#define hi(port,pin) port |= _BV(pin);
/** @brief pulls a pin logic low */
#define lo(port,pin) port &= ~_BV(pin);

/** 
 * @brief Initializes the library.
 *
 * This function sets up the ports / pins of the ATTINY to output, and
 * clears the output registers of the connected shift register(s).
*/
void snInit (void)
{
  /* setup pins 
  * Reminder - see tinysn74_config.h to define the pin/port
  */
  CLR_DDR |= 1<<(CLR_PIN); //set clear pin as output 
  LAT_DDR |= 1<<(LAT_PIN); //set latch pin as output
  
  snShiftInit(); // output shift port/pin(s), depends SPI / BIT-BANG

  snCLR(); // clear the SN74 registers, so we're in a known state.

  #if SN74OE == 1    
    OE_DDR |= 1<<(OE_PIN);
    snOE(0x0) // enable low.
  #endif
}

/**
 * @brief Clear the output register.
 * 
 * This function will clear all outputs of the connected SN74 chips,
 * without having to shift in N bytes of 0x00
*/
void snCLR (void)
{
  #if DEBUG == 1
    // slow things down so we can see the pins go high with a LED
    lo(CLR_PORT,CLR_PIN);
    hi (CLK_PORT,CLK_PIN);
    _delay_ms (100);
    lo (CLK_PORT,CLK_PIN);
    hi (LAT_PORT,LAT_PIN);
    _delay_ms (100);
    lo (LAT_PORT,LAT_PIN);
    hi(CLR_PORT,CLR_PIN);
  #else
    lo(CLR_PORT,CLR_PIN);
    pulse(CLK_PORT,CLK_PIN);
    pulse(LAT_PORT,LAT_PIN);
    hi(CLR_PORT,CLR_PIN);
  #endif 
}

/**
 * @brief Enable / disable SN74 outputs.
 *
 * If the snOE option is enabled (see tinysn47_config.h), this function
 * will allow you to enable or disable the output register.  
 *
 * Note that when disabled, the output register retains its previous
 * value - the pins are simply put into high-impedance.
 *
 * @param off uint8_t value to pass a '0' or '1'.  As the chip uses
 * logic low, setting off to '0' will ENABLE the output register.
*/
void snOE (uint8_t off)
{
  #if SN74OE == 1  
    if (off==0) // enable
      //set OE pin low - ENABLE outputs
      OE_DDR &= ~1<<(SN_OE_PIN);
    else 
      //set OE pin high - DISABLE outputs
      OE_DDR |= 1<<(SN_OE_PIN); 
  #endif
}

#if DATA_XFER_MOD == SN74_BANG
/**
 * @brief Initializes the shifting logic.  
 *
 * This function comes in two (2) forms, determined by your selection of
 * DATA_XFER_MOD in tinysn74_config.h.
 *
 * In bitbang mode (default); the function merely sets pins; whereas in
 * SPI mode, the function will also initialize the timers and SPI
 * "baudrate".
*/
void snShiftInit (void)
{
  DOT_DDR |= 1<<(DOT_PIN); //DOT (MOSI) as output
  CLK_DDR |= 1<<(CLK_PIN); //CLK as output
  CLK_PORT &= ~1<<(CLK_PIN); //CLK is low
}

/**
 * @brief Shifting logic to get data from the micro to the shift
 * registers
 *
 * This function comes in two (2) forms, determined by your selection of
 * DATA_XFER_MOD in tinysn74_config.h.
 *
 * In bitbang mode (default), the function utilizes a for loop to
 * iterate over the array of chip data.  In SPI mode, the SPI output
 * register and timers are utilized to iterate over the data.
 *
 * @param *b is the pointer to the chip array.
*/
void snShift (uint8_t *b)
{
  for (int chip=0;chip<NUMSN74;chip++) {
    for (uint8_t bit = 0x80; bit; bit >>=1) {
      if (bit & *b) {
        hi(DOT_PORT,DOT_PIN);   
        #if DEBUG == 1
          _delay_ms (100);
        #endif
      }
      else {
        lo(DOT_PORT,DOT_PIN);     
      }
      #if DEBUG == 1 
        hi(CLK_PORT,CLK_PIN);
        _delay_ms (100);
        lo(CLK_PORT,CLK_PIN);
      #else 
        pulse(CLK_PORT,CLK_PIN);
      #endif
    }
    *b++; //next byte in the array
  }
}
#elif DATA_XFER_MOD == SN74_SPI
void snShiftInit (void)
{
  //MOSI, SCK and MISO

  DOT_DDR |= 1<<(DOT_PIN); //MOSI as output
  CLK_DDR |= 1<<(CLK_PIN); //SCLK as output
  CLK_PORT &= 0<<(CLK_PIN); //CLK LOW


  /*  SPSR = SPI Status Register for ATMega == USISR maybe?
   *  I really shouldn't have started trying to write this for ATMega,
   *  but how was I supposed to know I'd fall in love with the Tinies?
  */ 

  /* -- SPSR -- 
      7. SPIF - Interrupt Flag
      6. WCOL - Write Collision
      5. -- (reserved)
      4. -- (reserved)
      3. -- (reserved)
      2. -- (reserved) 
      1. -- (reserved)
      0. SPI2X -- SCK frequency doubled

    -- vs --
    -- USISR --
      7. USISIF - Start cond. Interrupt flag
      6. USIOIF - Counter Overflow interrupt
      5. USIPF - Stop Condition flag
      4. USIDC - Data Collision (2-wire only)
      3. USICNT3 - clock
      2. USICNT2 - clock 
      1. USICNT1 - clock 
      0. USICNT0 - clock
  */
  // SPCR = SPI Control Register for ATMega == USICR maybe?
  

  /* -- SPCR -- 
      7. SPIE - Interrupt Enable
      6. SPE - SPI Enable
      5. DORD - LSB or MSB first
      4. MSTR - Master select
      3. CPOL - Clock Polarity
      2. CPHA - Clock Phase
      1. SPR1 - SPI Clock Rate
      0. SPR0 - SPI Clock Rate

    -- vs --
    -- USICR --
      7. USISIE - Start Cond. Interrupt Enable
      6. USIOIE - Counter Overflow Interrupt Enable
      5. USIWM1 - Wire Mode
      4. USIWM0 - Wire Mode
      3. USICS1 - Clock Source
      2. USICS0 - Clock Source
      1. USICLK - Clock Strobe
      0. USITC  - Toggle Clock
  */

  //USIDR = USI Data Register

  /* I have no idea if this is correct.
  * Set USISIE, USIOIE,USIWM1,USICS0 =0
  * and USIWM0, USICS1,USICLK, USITC =1
  *
  * IN THEORY, this means it'll run SPI Mode 1,
  * utilizing the USITC strobe bit as the clock source for the 4 bit
  * counter. 
  */

  USICR = 1<<(USIWM0)//3wire mode (SPI)
   | 1<<(USICS1) //CS1:0 = 1,0 set external clock source
   | 1<<(USICLK) //Set USITC as external clock
   | 1<<(USITC); //start the clock, mybe
  
  
}

void snShift (uint8_t *b)
{
  //start shifting out data
  for (int chip=0;chip<NUMSN74;chip++) {
    USIDR = *b;
    USISR = 1<<(USIOIF); //reset counter?
    cli(); // disable interrupts because apparently you "might" get one.
    while (!(USISR & 1<<(USIOIF)))
    {
      USICR |= 1<<(USITC); //wait until we hit a clock overflow 
    }
    sei(); //re-enable interrupts
    *b++; // next byte in the array
  }
}

#endif

/**
 * @brief Latcn data from SN74's internal shift register to the output.
 *
 * This function is what actually sets the output pins to the value
 * contained in the input shift register.  Without calling this, the
 * pins will never go logic high (or logic low).
*/
void snLat (void)
{
  // Kick the SN74 RX register over to the pin outputs
  #if DEBUG == 1
    hi(LAT_PORT,LAT_PIN);
    _delay_ms (100);
    lo(LAT_PORT,LAT_PIN);
  #else 
    pulse(LAT_PORT,LAT_PIN);
  #endif
}
