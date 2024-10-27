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
  uint8_t buff[1] = { result };
  simpleserial_put('r', 1, buff);

  return 0;
}


uint8_t reversed_one_mult(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t *buf)
{
  volatile uint8_t result = 0;
  int arr[4] = {7,5,4,2};
  unsigned char weight = 5;
    
  // Start measurement.
  trigger_low();                                              // Start measurement!!!
  for(int x = 0;x<100;x++){
      __asm__("nop");
  }
  unsigned char num = (unsigned char)(weight * buf[0]);
  for(int x = 0;x<100;x++){
      __asm__("nop");
  }
  trigger_high();                                             // Stop measurement!!!
    
  result = scmd*scmd;
  // For now we can just return the result back to the user.
  uint8_t buff[1] = { result };
  simpleserial_put('r', 1, buff);

  return 0;
}



uint8_t hundred_mult(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t *buf)
{
  volatile uint8_t result = 0;
  int arr[4] = {7,5,4,2};
  unsigned char weight = 5;
    
  trigger_high();                                          // Start measurement!!!
  for(int x = 0;x<100;x++){
      __asm__("nop");
  }
  unsigned char resutl;
  unsigned char val = buf[0];
  for(int x = 0;x<50;x++){
      __asm__("nop");
      __asm__("nop");
      unsigned char akt = x % 25;
      unsigned char resutl = (unsigned char)(x * val);
      __asm__("nop");
      __asm__("nop");
  }
  trigger_low();                                             // Stop measurement!!!
    
  result = scmd*scmd;
  // For now we can just return the result back to the user.
  uint8_t buff[1] = { result };
  simpleserial_put('r', 1, buff);

  return 0;
}

uint8_t hundred_mult_buffed(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t *buf)
{
  volatile uint8_t result = 0;
  int arr[4] = {7,5,4,2};
  unsigned char weight = 5;
    
  trigger_high();                                           // Start measurement!!!
  for(int x = 0;x<100;x++){
      __asm__("nop");
  }
  int x = 0;
  while(x<20){
      unsigned char val =  x % 10;
      unsigned char resutl = (unsigned char)(val * buf[0]);
      x++;
      for(int y = 0;y<3;y++){
          __asm__("nop");
      }
  }
  for(int x = 0;x<100;x++){
      __asm__("nop");
  }
  trigger_low();                                             // Stop measurement!!!
    
  result = scmd*scmd;
  // For now we can just return the result back to the user.
  uint8_t buff[1] = { result };
  simpleserial_put('r', 1, buff);

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
  simpleserial_addcmd('z', 16, one_mult);
  simpleserial_addcmd('r', 16, reversed_one_mult);
  simpleserial_addcmd('f', 16, hundred_mult_buffed);

  // What for the capture board to send commands and handle them.
  while (1)
    simpleserial_get();
}




