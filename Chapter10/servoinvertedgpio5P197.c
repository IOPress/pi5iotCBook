#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Gpio5.h"
int main(int argc, char **argv)
{
    rp1_Init();
    gpio_init(12);
    pwm_set_clock(1, 0);
    pwm_setup(12, TrailingEdge); 
    pwm_set_frequency_duty(12, 50, 0);
    pwm_enable(12);
    pwm_set_invert(12);

    for (;;)
    {
        pwm_set_frequency_duty(12, 50, 25);
        pwm_set_frequency_duty(12, 50, 120);      
    }
}