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

  //int arr[4] = {7,5,4,2};
  //network net = construct_network(5, 4, arr);

  int arr[4] = {7,5,4,2};
  network net = construct_quantized_network2(4,arr);

  // expects an input of byte lenght, of number neurons in first layer
  for(int x = 0; x < arr[0]; x++){
    net.layers[0].neurons[x].a = (signed char)(buf[x]);
    /*printf("Neuron %d[",x);
    for(int y = 0; y <arr[1]; y++){
      char akt_weight = net.layers[0].neurons[x].weights[y];
      printf("\tWeight_%d:%d,",y,akt_weight);
    }
    printf("]\n");*/
  }

  //int ****random_indices = generate_random_indices(net);

  // Start measurement.
  trigger_high();

  forward(net,0);
  //forward_shuffled(net);
  //forward_shuffled_without_overhead(net, random_indices, 0);
  //forward_shuffled_without_overhead_activations_at_end(net, random_indices, 2);

  // Stop measurement.
  trigger_low();


  // For now we can just return the result back to the user.
  result = scmd*scmd;
  uint8_t buff[1] = { result };
  int return_string_len =  ((arr[1] + 1) * arr[0]) + 1;
  char string[return_string_len];
  // char string[] = "Hello";
    for(int x = 0; x < arr[0]; x++){
        for(int y = 0;y<arr[1];y++){
            string[(x*(arr[1]+1)) + y] = net.layers[0].neurons[x].weights[y];
        }
        string[(x*(arr[1]+1)) + arr[1]] = net.layers[0].neurons[x].bias;
    }
    string[return_string_len - 1] = 0;
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

  // What for the capture board to send commands and handle them.
  while (1)
    simpleserial_get();
}



