#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "ds1812P356.pio.h"

uint8_t crc8(uint8_t *data, uint8_t len)
{
    uint8_t i;
    uint8_t j;
    uint8_t temp;
    uint8_t databyte;
    uint8_t crc = 0;
    for (i = 0; i < len; i++)
    {
        databyte = data[i];
        for (j = 0; j < 8; j++)
        {
            temp = (crc ^ databyte) & 0x01;
            crc >>= 1;
            if (temp)
                crc ^= 0x8C;

            databyte >>= 1;
        }
    }
    return crc;
}
void writeBytes(PIO pio, uint sm, uint8_t bytes[], int len)
{
    pio_sm_put_blocking(pio, sm, 400);
    pio_sm_put_blocking(pio, sm, len - 1);
    for (int i = 0; i < len; i++)
    {
        pio_sm_put_blocking(pio, sm, bytes[i]);
    }
}
void readBytes(PIO pio, uint sm, uint8_t bytes[], int len)
{
    pio_sm_put_blocking(pio, sm, 0);
    pio_sm_put_blocking(pio, sm, len - 1);
    for (int i = 0; i < len; i++)
    {
        bytes[i] = pio_sm_get_blocking(pio, sm) >> 24;
    }
}

float getTemperature(PIO pio, uint sm)
{
    writeBytes(pio, sm, (uint8_t[]){0xCC, 0x44}, 2);
    sleep_ms(1000);
    writeBytes(pio, sm, (uint8_t[]){0xCC, 0xBE}, 2);

    uint8_t data[9];
    readBytes(pio, sm, data, 9);

    uint8_t crc = crc8(data, 9);
    if (crc != 0)
        return -2000;
    int t1 = data[0];
    int t2 = data[1];
    int16_t temp1 = (t2 << 8 | t1);
    volatile float temp = (float)temp1 / 16;
    return temp;
}

uint DS18Initalize(PIO pio, int gpio)
{

    uint offset = pio_add_program(pio, &DS1820_program);

    uint sm = pio_claim_unused_sm(pio, true);
    pio_gpio_init(pio, gpio);

    pio_sm_config c = DS1820_program_get_default_config(offset);
    sm_config_set_clkdiv_int_frac(&c, 255, 0);
    sm_config_set_set_pins(&c, gpio, 1);
    sm_config_set_out_pins(&c, gpio, 1);
    sm_config_set_in_pins(&c, gpio);
    sm_config_set_in_shift(&c, true, true, 8);
    pio_sm_init(pio0, sm, offset, &c);
    pio_sm_set_enabled(pio0, sm, true);
    return sm;
}

int main()
{
    stdio_init_all();

    uint sm = DS18Initalize(pio0, 2);

    float t;
    for (;;)
    {
        do
        {
            t = getTemperature(pio0, sm);
        } while (t < -999);
        printf("temperature %f\r\n", t);
        sleep_ms(500);
    };

    return 0;
}