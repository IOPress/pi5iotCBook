#include <stdio.h>
#include <stdlib.h>

#include "Gpio5.h"

int main(int argc, char **argv)
{
  int pin1 = 4;
  int pin2 = 2;
  rp1_Init();
  gpio_init(pin1);
  gpio_set_dir(pin1, true);
  gpio_init(pin2);
  gpio_set_dir(pin2, true);

  uint32_t mask = (1 << pin1) | (1 << pin2);
  uint32_t value1 = 1 << pin1;
  uint32_t value2 = 1 << pin2;
  while (true)
  {
    gpio_put_masked(mask, value1);
    gpio_put_masked(mask, value2);
  }
  return (EXIT_SUCCESS);
}