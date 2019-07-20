/*
* SN74Count - this short example counts from 0 to 255, and lights LEDs
* on a single SN74HC595.  
*
*/

#include <tinysn74.h>
#include <tinysn74_config.h>


//global only so we know approximately how much RAM is getting used.
uint8_t i=0; //counter int
uint8_t chip[1]; //shift expects an array



void setup() {
  snInit();
}

void loop() {
  for (i=0; i<256; i++)
   {
    chip[0] = i;
    snShift(chip);
    snLat();
    delay(100);
   }
   delay(2000);
}
