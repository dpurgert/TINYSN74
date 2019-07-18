# TINYSN74
Library for Texas Instruments SN74HC595 Shift Registers (and clones),
for use with ATTINY chips.

Communication is currently bit-banging, with SPI in the works.  

## Details
- Current version: 0.0.1
- Supports:
..- ATTinyx5 (25/45/85)
..- ATTinyx4 (24/44/84) - only minimally tested.

## Pinouts

### ATTiny x5

Default pinout for the ATTiny 25/45/85 series.  Note that MISO is
required if setting SPI Mode.  Considering modifying the lib to also
allow CLR to be an optional pin.

|desc|pin|---|pin|desc|
|----|---|---|---|----|
|RESET|1|---|8|VCC|
|CLR - PB3|2|---|7|PB2 - CLK|
|LAT - PB4|3|---|6|PB1 - MISO|
|GND|4|---|5|PB0 - MOSI|


### ATTiny x4

Default pinout for the ATTiny 24/44/84 series.  Note that MISO is
required if setting SPI Mode.  

V0.0.1 Initial test pinout

Pins currently undefined in the library are marked as "+++" 


|desc|pin|---|pin|desc|
|----|---|---|---|----|
|VCC|1|---|14|VCC|
|+++ PB0|2|---|13|PA0 +++|
|+++ PB1|3|---|12|PA1 +++|
|RESET|4|---|11|PA2 +++|
|+++ PB2|5|---|10|PA3 - CLR|
|LAT - PA7|6|---|9|PA4 - CLK|
|MOSI - PA6|7|---|8|PA5 - MISO|

## Attribution
Lots of influence from lots of places, mainly the sparkfun repo for the
TLC5940 driver.  Thanks to one and all for sharing your solutions.
