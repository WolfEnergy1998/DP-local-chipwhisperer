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


network * net = NULL;
int arr[4] = {7,2,2};

/// This function will handle the 'p' command send from the capture board.
/// It returns the squared version of the scmd given.
/// It does this in approximately equal time, which allows us to see clear
/// differences between different scmd values.
uint8_t handle(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t *buf)
{
  volatile uint8_t result = 0;
  int arr[4] = {7,2,2};
  int return_string_len =  ((arr[1] + 1) * arr[0]) + 1;
  char string[return_string_len];

  // expects an input of byte lenght, of number neurons in first layer#
  for(int x = 0; x < arr[0]; x++){
      net->layers[0].neurons[x].a = (int8_t)(buf[x]);
  }
  // char string[] = "Hello";
  for(int x = 0; x < arr[1]; x++){ // Crossing first layer (not input layer)
      for(int y = 0;y<arr[0];y++){ // Choose each neuron from input layer, and save it's weight, and set weight of first weight to (x+1) * 10, in essence this is only for basic testing, and essentialy it sends back S1,S2,S3,S4,S5...0 where SX is weight of input X-th connection, of x-th neuron   
          //if(y == 0){
          //    net->layers[0].neurons[y].weights[x] = (uint8_t)((x+1) * 10);
          //}
          string[(x*(arr[0]+1)) + y] = net->layers[0].neurons[y].weights[x];
      }
      string[(x*(arr[0]+1)) + arr[0]] = net->layers[0].neurons[x].bias;
  }
  string[return_string_len - 1] = 0;


  // Start measurement.
  trigger_high();
  for(int x = 0;x<100;x++){
      __asm__("nop");
  }

  forward(*net,0);
    
  
  string[return_string_len - 1] = 0;
  // Stop measurement.
  for(int x = 0;x<100;x++){
      __asm__("nop");
  }
  trigger_low();

  // For now we can just return the result back to the user.
  result = scmd*scmd;
  uint8_t buff[1] = { result };
  uint8_t return_len = return_string_len;
  simpleserial_put('r', return_len, string);

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

  arr[0] = 7;
  arr[1] = 2;
  arr[2] = 2;
  network ann = construct_quantized_network2(3,arr);
  net = &ann;
  // What for the capture board to send commands and handle them.
  while (1)
    simpleserial_get();
}