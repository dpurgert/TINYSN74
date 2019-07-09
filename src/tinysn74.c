/***********************************************************************
*
*                 Program: SN74HC595 Library - sn74.c
*                      by: Dan Purgert <dan@djph.net>    
*               copyright: 2018
*                 version: 0.1
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

#include <avr/io.h>
#include <avr/interrupt.h>

#include "tinysn74_config.h"
#include "tinysn74.h"

//DEBG = 1 for debugging / slowing things down
#define DEBUG 0

//#if DEBUG == 1
#include <util/delay.h>
//#endif

/*send a pulse (hi, then lo) to a pin*/
#define pulse(port,pin) port |= _BV(pin); port &= ~_BV(pin);
#define hi(port,pin) port |= _BV(pin);
#define lo(port,pin) port &= ~_BV(pin);

//volatile void (*UpdateFinished)(void);


/** Interrupt called after a LAT pulse to prevent more LAT pulses. 
// not sure this works on the attiny... 
ISR(TIMER1_OVF_vect)
{
    disableLATpulse();
    clearLATinterrupt();
    if (UpdateFinished) {
        sei();
        UpdateFinished();
    }
} */

void snInit (void)
{
  /* setup pins */
  CLR_DDR |= _BV(CLR_PIN);
  LAT_DDR |= _BV (LAT_PIN);

  
  snShiftInit();

  snCLR();

  #if SN74OE == 1    
    OE_DDR |= _BV(OE_PIN);
    snOE(0x0) // enable low.
  #endif

  disableLATpulse();
  clearLATinterrupt();
  

  /* Timer 1 - BLANK / XLAT */
  TCCR0A = _BV(COM0B1) |_BV(WGM00);  // non inverting, output on OC1B, BLANK
  TCCR0B = _BV(WGM02); // Phase/freq correct PWM, OCRA top
  OCR1A = 1;             // duty factor on OC1A, LAT is inside BLANK
  OCR1B = 2;             // duty factor on BLANK (larger than OCR1A (XLAT))
  TCCR0B |= _BV(CS00);   // Sart PWM... I hope?
  
}

void snCLR (void)
{
  //clear all serial data, i think 
  #if DEBUG == 1
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
  
#if SN74OE == 1  
void snOE (uint8_t off)
{

  if (off==0) // enable
    //set OE pin low - ENABLE outputs
    OE_DDR &= ~_BV(SN_OE_PIN);
  else 
    //set OE pin high - DISABLE outputs
    OE_DDR |= _BV(SN_OE_PIN); 
}
#endif

#if DATA_XFER_MOD == SN74_BANG
void snShiftInit (void)
{
  DIN_DDR |= _BV(DIN_PIN); //DIN as output
  CLK_DDR |= _BV(CLK_PIN); //CLK as output
  CLK_PORT &= ~_BV(CLK_PIN); //CLK is low
}

void snShift (uint8_t b)
{
  for (uint8_t bit = 0x80; bit; bit >>=1) {
    if (bit & b) {
      hi(DIN_PORT,DIN_PIN);   
      #if DEBUG == 1
        _delay_ms (100);
      #endif
    }
    else {
      lo(DIN_PORT,DIN_PIN);     
    }
    #if DEBUG == 1 
      hi(CLK_PORT,CLK_PIN);
      _delay_ms (100);
      lo(CLK_PORT,CLK_PIN);
    #else 
      pulse(CLK_PORT,CLK_PIN);
    #endif
  }
}
#elif DATA_XFER_MOD == SN74_SPI
void snShiftInit (void)
{
  //MOSI, SCK and MISO

  DIN_DDR |= _BV(DIN_PIN); //MOSI as output
  CLK_DDR |= _BV(CLK_PIN); //SCLK as output
  CLK_PORT &= ~_BV(CLK_PIN); //CLK LOW


  // SPSR = SPI Status Register for ATMega == USISR maybe

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
  // SPCR = SPI Control Register for ATMega == USICR maybe
  

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

  // I have no idea if this is correct
  // SPSR = _BV(SPI2X); //double speed
  // SPCR = _BV(SPE) | _BV(MSTR); //enable SPI, in master mode 
  USISR = 0x0; //not using any TWI stuff, set counter to zero
  USICR = 1<<(USIWM0) // 3 wire mode
          | 0<<(USICS0)| 1<<(USICLK) // Software clock strobe
          | 1<<(USITC); // Toggle Clock
  
}

void snShift (uint8_t b)
{
  USIDR = b;
  while (!(USISR & 1<<(USIOIF)))
  {
    ; //wait until we hit a clock overflow 
  }
  
}

#endif

void snLat (void)
{
  // latch the data in.
  #if DEBUG == 0 
    hi(LAT_PORT,LAT_PIN);
    _delay_ms (100);
    lo(LAT_PORT,LAT_PIN);
  #else 
    pulse(LAT_PORT,LAT_PIN);
  #endif
}
