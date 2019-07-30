/**
 * @file
 * @brief This short example counts from 0 to 255.
 *
 * This simple sketch is intended to help verify the SN74 is properly
 * connected to the microcontroller
 *
*/

#include <tinysn74.h>

// Variables here are globals, as it helps ascertain how much RAM we're
// utilizing at compile time.

/// Counter
uint8_t i=0; 
/// Create the chip array.
uint8_t chip[1]; 


/**
 * @brief  Initial setup code.
 * Runs once at power-on or chip reset.  
*/
void setup() {
  snInit();
}


/**
 * @brief Main program loop
 *
 * Runs indefinitely.
*/
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
