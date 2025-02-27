#include <stdio.h>
#include <stdlib.h>
#include "Gpio5.h"
int main(int argc, char **argv)
{
  int pin1 = 4;
  rp1_Init();
  gpio_init(pin1);
  gpio_pull_up(pin1);
  gpio_set_dir(pin1, false);
  gpio_put(pin1, false);  
  volatile int temp;
  while (true)
  {
    gpio_set_dir(pin1, true);
    for(temp=0;temp<2000;temp++){};
    gpio_set_dir(pin1, false);
    for(temp=0;temp<2000;temp++){};
  }
  return (EXIT_SUCCESS);
}