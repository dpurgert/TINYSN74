#include <tinysn74.h>
#include <tinysn74_config.h>



uint8_t chp = 0; //chip array value
uint8_t rnd = 0; //RNG value
uint8_t chip[NUMSN74]; //set chip array, 1 chip = 16 pins, so uint 16
uint8_t pina[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};//set pins; 0x01-0x08 = "low byte" of a chip, 0x100-0x8000=high byte
uint8_t lat = 0; // latch indicator
uint8_t on = 1; // turning lights ON
int wait=0; //fully ON or OFF, wait some time before starting the loop again
uint8_t i=0; //counter int

void setup() {
  snInit(); //initialize the chip. 
}


void randlite() {
  rnd=(rand()%8); //select bit 0-8
  chp=(rand()%NUMSN74); // select the chip
  if (on==1){ //we're turning on the LEDs.
    chip[chp]=chip[chp] | pina[(rnd)];
  }
  else { //we're turning them off
    chip[chp] = chip[chp] & ~pina[(rnd)];
  }
  for (i=0; i<=NUMSN74; i++){
    if (i = NUMSN74) { //last chip, so latch on this shift
      lat=1;
    }
    snShift(chip[i]);
    if (on==1  && i==NUMSN74) { // at the last chip, check if all chips are on
      if (chip[0] == 0xFF) { //first chip is fully on, test the rest
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
      }
    }
    else if (on==0 && i==NUMSN74) { //last chip, check if everything's off
      if (chip[0] == 0x0) { //first chip is fully off, test the rest
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
      }
    }
  }
  if (wait==1){
    delay(5000); // sit for 5 seconds
  }
}

void loop() {
  // put your main code here, to run repeatedly:
    randlite();
  delay(100); //wait 0.1 second between lighting LEDs 

}
