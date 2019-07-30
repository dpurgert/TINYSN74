/**
 * @file
 * @brief A more involved example
 *
 * This example sketch shows how this library can be utilized to create
 * complex effects.  In this case, we're selecting a random pin on a
 * random chip to light.
*/
#include <tinysn74.h>

// As with the other example, the use of global variables helps us have
// a better idea of RAM usage at compile time

/**
 * @brief Chip select value
 *
 * uint8_t as 255 is more than a Tiny2x or 4x chip can run; so this
 * saves a bit of RAM.  Change to uint16_t if you're using a Tiny8x and
 * want to run more than 255 SN74HC595
*/
uint8_t chp = 0; 

/** 
 * @brief RNG value
 *
 * Value for the pin we're going to light
*/
uint8_t rnd = 0;

/**
 * @brief Chip array
 *
 * 8-bit unsigned integer array holds the values for the pin(s) that are
 * active on any one chip.
 *
 * Array is in "most significant chip first" order -- that is, chip[0]
 * is the SN74HC595 chip that is farthest away. chip[NUMSN74-1] is the
 * chip directly connected to MOSI
*/
uint8_t chip[NUMSN74]; 

/**
 * @brief Integer to pin conversion
 * 
 * If we just used a value 0-255, we'd get however many pins lit,
 * corresponding to the decimal -> binary conversion of a random number.
 * That is, if we fed chip[n] a value of 133, pins 8, 3, and 1 would
 * light (corresponding to 128 + 4 + 1), and that's not what we want.  
 *
 *
 * ArrayValue = Hex (decimal)
 * - [0] = 0x01 (1)
 * - [1] = 0x02 (2)
 * - [2] = 0x04 (4)
 * - [3] = 0x08 (8)
 * - [4] = 0x10 (16)
 * - [5] = 0x20 (32)
 * - [6] = 0x40 (64)
 * - [7] = 0x80 (128)
*/
uint8_t pina[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

/**
 * @brief Indicator for enabling outputs
 *
 * When 1, the output selected in this run will be set logic high.  When
 * 0, output will be set to logic low.
*/
uint8_t on = 1;

/**
 * @brief Indicate loop should delay.
 * 
 * When 1, loop will delay for N seconds (default 5) before switching
 * state.  That is, if all the outputs just finished going logic high,
 * wait before setting random outputs to logic low (or vice-versa).
*/
int wait=0; 

/**
 * @brief Counter for walking the chip array.
 *
 * Set to uint8_t, as Tiny2x/4x will never exceed 255 SN74 chips; so
 * this saves some RAM.  Change to uint16_t for a tiny8x if you choose
 * to use more than 255 chips.
*/
uint8_t i=0;

/**
 * @brief Program initialization
 * 
 * Runs once at power on or microcontroller reset. Calls snInit() and
 * seeds the PRNG with the number of microseconds since the chip (re)
 * booted.
*/
void setup() {
  snInit(); 
  srand(micros());
}

/**
 * @brief Randomly select the chip and pin to change state.
 * 
 * Provided that NUMSN74 >1, this will randomly select a pin and chip
 * from their respective arrays, and set the output state accordingly.
 * Once the data is shifted out and latched in, the function determines
 * if the whole array's outputs are logic high or logic low, in order to
 * determine if the other cycle should be started.
*/
void randlite() {
  rnd=(rand()%8); //select pin 0 to 7, 
  //if NUMSN74 is 1, then it's pointless to use the PRNG, since int
  //modulo one (int % 1) is always 0 anyway. 
  #if (NUMSN74 > 1) 
    chp=(rand()%NUMSN74); // select the chip, 0 to (NUMSN74-1)
  #endif
  if (on==1){ //we're turning on the LEDs.
    chip[chp] |= pina[rnd];
  }
  else { //we're turning them off
    chip[chp] &= ~pina[rnd];
  }
  snShift(chip); //shift in the array...
  snLat();//shifting done, latch
  
  /*
   * Now that we've latched the data in, loop through the chips to see
   * if everything's in the correct state (i.e. all are on if we're
   * turning LEDs on or vice versa).  If they are, then we'll wait for 5
   * seconds before flipping states.
  */

  if (on==1) { // at the last chip, check if all chips are on
    if (chip[0] == 0xFF) { //first chip is fully on, test the rest
      #if NUMSN74 == 1
        on=0;//turn off
        wait=1;//wait
      #else
        for (i=1; i<=NUMSN74; i++){ //start from chip 1, we already know chip0 is 0xFF
          //this test loop only successfully completes when all chips
          //are 0xFF
          if (chip[i]!=chip[0]) { //chip[j] isn't 0xFF
            on=1; // reset to keep turning things on, in case chip[j-1] was 0xFF
            wait=0;// reset to not wait, in case chip[j-1] was 0xFF
            break; // get out of test loop
          }
          else {
            on=0; //chip's 0xFF, set to start turning off
            wait=1; //we'll wait
          }
        }
      #endif
    }
  }
  else if (on==0) { //last chip, check if everything's off
    if (chip[0] == 0x0) { //first chip is fully off, test the rest
      #if NUMSN74 == 1
        on=1;//turn off
        wait=1;//wait
      #else
        for (i=1; i<=NUMSN74; i++){ //start from chip 1, we already know chip0 is 0
          //this test loop only successfully completes when all chips
          //are 0x00
          if (chip[i]!=chip[0]) { //chip[j] isn't 0
            on=0; // reset to keep turning off, in case chip[j-1] was 0x0
            wait=0; //reset to not wait in case chip[j-1] was 0x0
            break; // get out of this test loop
          }
          else {
            on=1; // chip's 0x0, set to start turning on
            wait=1; //we'll wait
          }
        }
      #endif
    }
  }
  
  if (wait==1){
    delay(4900); // sit for 4.9 seconds, to accommodate 100ms delay every iteration of loop()
    wait=0; // reset for next pass.
  }
}

/** 
 * @brief Main program loop
 *
 * Infinite loop to continually call randlite(), and wait 100 ms after
 * every execution.
*/
void loop() {
    randlite();
  delay(100); //wait 0.1 second between lighting LEDs 

}
