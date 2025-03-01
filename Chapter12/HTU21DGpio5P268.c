#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Gpio5.h"
uint8_t crcCheck(uint8_t msb, uint8_t lsb, uint8_t check)
{
    uint32_t data32 = ((uint32_t)msb << 16) | 
                        ((uint32_t)lsb << 8) | (uint32_t)check;
    uint32_t divisor = 0x988000;
    for (int i = 0; i < 16; i++)
    {
        if (data32 & (uint32_t)1 << (23 - i))
            data32 ^= divisor;
        divisor >>= 1;
    };
    return (uint8_t)data32;
}
int main(int argc, char **argv)
{
    rp1_Init();
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);

    i2c_init(I2C1, 100 * 1000);

    uint8_t buf[4] = {0xE3};
    i2c_write_blocking(I2C1, 0x40, buf, 1, true);
    i2c_read_blocking(I2C1, 0x40, buf, 3, false);
    uint8_t msb = buf[0];
    uint8_t lsb = buf[1];
    uint8_t check = buf[2];
    printf("msb %d \n\r lsb %d \n\r checksum %d \n\r",
                                             msb, lsb, check);
    unsigned int data16 = ((unsigned int)msb << 8) | 
                                      (unsigned int)(lsb & 0xFC);
    printf("crc = %d\n\r", crcCheck(msb, lsb, check));
    float temp = (float)(-46.85 + (175.72 * 
                                      data16 / (float)65536));
    printf("Temperature %f C \n\r", temp);
    buf[0] = 0xF5;
    i2c_write_blocking(I2C1, 0x40, buf, 1, true);
    
    while (i2c_read_blocking(I2C1, 0x40, buf, 3, false) & 0x1 )
    {
       sleep_ms(1);
    };

    msb = buf[0];
    lsb = buf[1];
    check = buf[2];
    printf("msb %d \n\r lsb %d \n\r checksum %d \n\r",
                                              msb, lsb, check);
    printf("crc = %d\n\r", crcCheck(msb, lsb, check));
    data16 = ((unsigned int)msb << 8) | (unsigned int)(lsb & 0xFC);
    float hum = -6 + (125.0 * (float)data16) / 65536;
    printf("Humidity %f %% \n\r", hum);
    return (EXIT_SUCCESS);
}