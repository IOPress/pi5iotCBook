#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "squarewaveP337.pio.h"
int main()
{
    uint offset = pio_add_program(pio0, &squarewave_program);
    uint sm = pio_claim_unused_sm(pio0, true);
    pio_sm_config c = 
               squarewave_program_get_default_config(offset);
    sm_config_set_set_pins(&c, 3, 1);
    sm_config_set_in_pins(&c, 2);
    pio_gpio_init(pio0, 2);
    pio_gpio_init(pio0, 3);
    pio_sm_set_consecutive_pindirs(pio0, sm, 2, 1, false);
    pio_sm_set_consecutive_pindirs(pio0, sm, 3, 1, true);
    sm_config_set_clkdiv_int_frac(&c, 255, 0);
    pio_sm_init(pio0, sm, offset, &c);
    pio_sm_set_enabled(pio0, sm, true);   
    while(true){} 
    return 0;
}