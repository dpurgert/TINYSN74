# TINYSN74
Library for Texas Instruments SN74HC595 Shift Registers (and clones),
for use with ATTINY chips.

Communication is currently bit-banging, with SPI in the works.  

## Usage
Clone the repository into the "libraries" directory in your arduino
installation directory.

The library includes two (2) header files:
- tinysn74.h
- tinysn74\_config.h

The library provides several functions:
- snInit -- This is called from within you sketch setup() function
- snShift (byte b\*) -- This shifts the data out, requires an array to be
  passed in
- snLat -- Latch shifted data to the output pins
- snClr -- Clear the outputs
- snOE -- (Optional) Must be enabled in tinysn74\_config, allows
  triggering the output enable pin from within your program


## Details
- Current version: 0.6.0
- Supports:
  - ATTinyx5 (25/45/85)
  - ATTinyx4 (24/44/84) - only minimally tested.

## Pinouts

### SN74HC595
Reference pinout of a SN75HC595 shift register.

Output H' is the "carry forward".  Use this to daisy-chain.

|desc|pin|(PDIP/SOIC)|pin|desc|
|----|---|---|---|----|
|Out B|1|---|16|VCC|
|Out C|2|---|15|Out A|
|Out D|3|---|14|Data In|
|Out E|4|---|13|OE|
|Out F|5|---|12|Latch|
|Out G|6|---|11|CLK|
|Out H|7|---|10|CLR|
|GND|8|---|9|Out H'|

### ATTiny x5

Default pinout for the ATTiny 25/45/85 series.  Note that MISO is
required if setting SPI Mode.  Considering modifying the lib to also
allow CLR to be an optional pin.

|desc|pin|(PDIP/SOIC)|pin|desc|
|----|---|---|---|----|
|RESET|1|---|8|VCC|
|CLR - PB3|2|---|7|PB2 - CLK|
|LAT - PB4|3|---|6|PB1 - MISO|
|GND|4|---|5|PB0 - MOSI|


### ATTiny x4

Default pinout for the ATTiny 24/44/84 series.  Note that MISO is
required if setting SPI Mode.  

V0.0.1 Initial test pinout

Pins currently undefined in the library (i.e. available for use) are
marked as "+++" 


|desc|pin|(PDIP/SOIC)|pin|desc|
|----|---|---|---|----|
|VCC|1|---|14|GND|
|+++ PB0|2|---|13|PA0 +++|
|+++ PB1|3|---|12|PA1 +++|
|RESET|4|---|11|PA2 +++|
|+++ PB2|5|---|10|PA3 - CLR|
|LAT - PA7|6|---|9|PA4 - CLK|
|MOSI - PA6|7|---|8|PA5 - MISO|

## Attribution
Lots of influence from lots of places, mainly the sparkfun repo for the
TLC5940 driver.  Thanks to one and all for sharing your solutions.

## Changelog

0.6.0 - Added example sketch, fixed math errors causing the library to
eat significantly more RAM than necessary.
