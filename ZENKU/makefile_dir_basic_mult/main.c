/*
 * SimpleSerial V2 Template C code
 * Can be freely used to implement ChipWhisperer target binaries.
 *
 * Date: 14th March 2021
 */

#include <stdint.h>
#include <stdlib.h>
#include "network.h"

#define SS_VER SS_VER_2_1
#include "../../../hardware/victims/firmware/simpleserial/simpleserial.h"

/// This function will handle the 'p' command send from the capture board.
/// It returns the squared version of the scmd given.
/// It does this in approximately equal time, which allows us to see clear
/// differences between different scmd values.
uint8_t one_mult(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t *buf)
{
  volatile uint8_t result = 0;
  int arr[4] = {7,5,4,2};
  unsigned char weight = 5;
    
  trigger_high();                                          // Start measurement!!!
  for(int x = 0;x<100;x++){
      __asm__("nop");
  }
  unsigned char num = (unsigned char)(weight * buf[0]);
  for(int x = 0;x<100;x++){
      __asm__("nop");
  }
  trigger_low();                                             // Stop measurement!!!
    
  result = scmd*scmd;
  // For now we can just return the result back to the user.
  uint8_t buff[2] = { weight };
  buff[-1] = 0;
  simpleserial_put('r', 2, buff);

  return 0;
}



uint8_t hundred_mult(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t *buf)
{
  volatile uint8_t result = 0;
  int arr[4] = {7,5,4,2};
  unsigned char weight = 5;
  int counter = 50;
  unsigned char resutl;
  unsigned char val = buf[0];
  int return_string_len =  ((arr[1] + 1) * arr[0]) + 1;
  char string[counter+1]; 


    
  trigger_high();                                          // Start measurement!!!
  for(int x = 0;x<100;x++){
      __asm__("nop");
  }
  for(int x = 0;x<counter;x++){
      __asm__("nop");
      __asm__("nop");
      unsigned char akt = x % (counter/2);
      unsigned char result = (unsigned char)(x * val);
      __asm__("nop");
      __asm__("nop");
  }
  trigger_low();                                             // Stop measurement!!!
    
  //result = scmd*scmd;
  // For now we can just return the result back to the user.
  for(int x = 0; x < counter; x++){
        string[x] = x % (counter/2);
  }
  string[return_string_len - 1] = 0;
  simpleserial_put('r', counter+1, string);
  return 0;
}



int main(void) {
  // Setup the specific chipset.
  platform_init();
  // Setup serial communication line.
  init_uart();
  // Setup measurement trigger.
  trigger_setup();

  simpleserial_init();

  // Insert your handlers here.
  simpleserial_addcmd('p', 16, hundred_mult);
  simpleserial_addcmd('o', 16, one_mult);

  // What for the capture board to send commands and handle them.
  while (1)
    simpleserial_get();
}




