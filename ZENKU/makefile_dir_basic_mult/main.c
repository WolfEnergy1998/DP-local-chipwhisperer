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
uint8_t handle(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t *buf)
{
  volatile uint8_t result = 0;
  int arr[4] = {7,5,4,2};
  signed char weight = 27;
  /*for(int x = 0;x<arr[0];x++){
      signed char num = (signed char)(buf[x]) * weight;
  }*/
  // Start measurement.
  trigger_high();
  //signed char num = (signed char)(buf[0]) * weight;
  for(int x = 0;x<10000;x++){
      signed char num = (signed char)(buf[0]) * weight;
  }
  // Stop measurement.
  trigger_low();
    
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
  simpleserial_addcmd('p', 16, handle);

  // What for the capture board to send commands and handle them.
  while (1)
    simpleserial_get();
}




