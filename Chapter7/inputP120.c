#include <stdio.h>
#include <stdlib.h>
#include "Gpio5.h"

int main(int argc, char **argv)
{
  int pin1 = 4;
  int pin2 = 2;
  rp1_Init();
  gpio_init(pin1);
  gpio_set_dir(pin1, false);
  gpio_pull_up(pin1);
  gpio_init(pin2);
  gpio_set_dir(pin2, true);
  while (true)
  {
    if (gpio_get(pin1))
    {
      gpio_put(pin2, 0);
    }
    else
    {
      gpio_put(pin2, 1);
    }
  }
  return (EXIT_SUCCESS);
}