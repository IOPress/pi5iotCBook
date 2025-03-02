#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "dht22P344.pio.h"
uint dhtInitalize(PIO pio, int gpio)
{
    uint offset = pio_add_program(pio, &dht_program);

    uint sm = pio_claim_unused_sm(pio, true);
    pio_gpio_init(pio, gpio);
    pio_sm_config c = dht_program_get_default_config(offset);
    sm_config_set_clkdiv_int_frac(&c, 200, 0);
    sm_config_set_set_pins(&c, gpio, 1);
    sm_config_set_in_pins(&c, gpio);
    sm_config_set_jmp_pin(&c, gpio);
    sm_config_set_in_shift(&c, true, true, 32);
    pio_sm_init(pio0, sm, offset, &c);

    pio_sm_set_enabled(pio0, sm, true);
    return sm;
}

uint8_t getByte(PIO pio, uint sm)
{
    uint32_t count = pio_sm_get_blocking(pio0, sm);
    uint8_t byte = 0;
    for (int i = 0; i < 8; i++)
    {
        byte = byte << 1;
        if (((count >> i * 4) & 0x0F) > 8)
        {
            byte = byte | 1;
        }
    }
    return byte;
}

typedef struct
{
    float temperature;
    float humidity;
    bool error;
} dhtData;

void dhtread(PIO pio, uint sm, dhtData *reading)
{
    pio_sm_put_blocking(pio, sm, 1000);
    uint8_t byte1 = getByte(pio, sm);
    uint8_t byte2 = getByte(pio, sm);
    uint8_t byte3 = getByte(pio, sm);
    uint8_t byte4 = getByte(pio, sm);
    uint8_t checksum = getByte(pio, sm);
    reading->error = (checksum == (byte1 + byte2 + byte3 + byte4) &
                                                            0xFF);
    reading->humidity = (float)((byte1 << 8) | byte2) / 10.0;
    int neg = byte3 & 0x80;
    byte3 = byte3 & 0x7F;
    reading->temperature = (float)(byte3 << 8 | byte4) / 10.0;
    if (neg > 0) reading->temperature = -reading->temperature;
}
int main()
{
    stdio_init_all();
    uint sm = dhtInitalize(pio0, 2);
    dhtData reading;
    dhtread(pio0, sm, &reading);
    printf("Humidity= %f %\n", reading.humidity);
    printf("Temperature= %f C\n", reading.temperature);
    return 0;
}