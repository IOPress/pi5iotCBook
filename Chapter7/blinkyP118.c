#include <stdlib.h>
#include "Gpio5.h"

int main(int argc, char **argv)
{
    rp1_Init();
    gpio_init(2);
    gpio_set_dir(2, true);
    while (true)
    {
        gpio_put(2, 1);
        sleep(1);
        gpio_put(2, 0);
        sleep(1);
    }
    return (EXIT_SUCCESS);
}