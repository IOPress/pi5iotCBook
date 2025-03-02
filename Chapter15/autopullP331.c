#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "autopullP330.pio.h"

int main()
{
    uint offset = pio_add_program(pio0, &squarewave_program);
    uint sm = pio_claim_unused_sm(pio0, true);
    pio_sm_config c =
                squarewave_program_get_default_config(offset);
    sm_config_set_set_pins(&c, 2, 2);
    sm_config_set_out_pins(&c, 2, 2);
    pio_gpio_init(pio0, 2);
    pio_gpio_init(pio0, 3);
    pio_sm_set_consecutive_pindirs(pio0, sm, 2, 2, true);
    sm_config_set_clkdiv_int_frac(&c, 255, 0);
    sm_config_set_out_shift (&c, true, true, 6);
    pio_sm_init(pio0, sm, offset, &c);
    pio_sm_set_enabled(pio0, sm, true);
    while (true)
    {
        pio_sm_put_blocking(pio0, sm, 0xFEDCBA98);
    }
    return 0;
}