#include <tinysn74.h>
#include <tinysn74_config.h>


#define WDEL 5000 // delay after all LEDs are on, before starting over
#define LDEL 100 // delay between lighting each LED

uint8_t chp = 0; //chip array value
uint8_t rnd = 0; //RNG value
uint8_t chip[NUMSN74]; //set chip array, 1 chip = 8 pins, so uint 8, as int may be 16 bits (wastes space)

/* If we just used a value 0-255, we'd get however many pins lit, and
 * that's not what we want.  The array translates a pin position (1-8)
 * to the corresponding binary value, represented in hexadecimal.
 * Decimal and binary values also shown.
 * Later, we use the array to perform bitwise OR operations with the
 * value(s) already stored in the chip array, so we can enable (or
 * disable) individual pins.
*/

uint8_t pina[8]={0x01, //pin 1 = 1
                 0x02, //pin 2 = 2
                 0x04, //pin 3 = 4
                 0x08, //pin 4 = 8
                 0x10, //pin 5 = 16
                 0x20, //pin 6 = 32
                 0x40, //pin 7 = 64
                 0x80};//pin 8 = 128

uint8_t on = 1; // turning lights ON
int wait=0; //fully ON or OFF, wait some time before starting the loop again
uint8_t i=0; //counter int

void setup() {
  snInit(); //initialize the chip. 
}


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

  for (i=0; i<=NUMSN74; i++){
    if (on==1  && i==NUMSN74) { // at the last chip, check if all chips are on
      if (chip[0] == 0xFF) { //first chip is fully on, test the rest
        #if NUMSN74 == 1
          on=0;//turn off
          wait=1;//wait
        #else
          for (int j=1; j<=NUMSN74; j++){ //start from chip 1, we already know chip0 is 0xFF
            //this test loop only successfully completes when all chips
            //are 0xFF
            if (chip[j]!=chip[0]) { //chip[j] isn't 0xFF
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
    else if (on==0 && i==NUMSN74) { //last chip, check if everything's off
      if (chip[0] == 0x0) { //first chip is fully off, test the rest
        #if NUMSN74 == 1
          on=1;//turn off
          wait=1;//wait
        #else
          for (int j=1; j<=NUMSN74; j++){ //start from chip 1, we already know chip0 is 0
            //this test loop only successfully completes when all chips
            //are 0x00
            if (chip[j]!=chip[0]) { //chip[j] isn't 0
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
  }
  if (wait==1){
    delay(WDEL); // sit for 5 seconds
  }
}

void loop() {
  // put your main code here, to run repeatedly:
    randlite();
  delay(LDEL); //wait 0.1 second between lighting LEDs 

}
