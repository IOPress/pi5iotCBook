#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Gpio5.h"

int main(int argc, char **argv)
{
    struct timespec delay = {0, 10000 * 1000};
    rp1_Init();
    gpio_init(12);
    pwm_set_clock(2, 0);
    pwm_setup(12, TrailingEdge);
    pwm_set_frequency_duty(12, 2000, 0);
    pwm_enable(12);
    int w = 0;
    int inc = 1;
    for (;;)
    {
        pwm_set_frequency_duty(12, 2000, w * w * w / (10 * 100));
        w = w + inc;
        if (w >= 100 || w <= 0)
            inc = -inc;
        nanosleep(&delay, NULL);
    }
    return (EXIT_SUCCESS);
}