#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Gpio5.h"

int main(int argc, char **argv)
{
    rp1_Init();
    gpio_set_function(8, GPIO_FUNC_SPI);  // CS0
    gpio_set_function(9, GPIO_FUNC_SPI);  // MISO
    gpio_set_function(10, GPIO_FUNC_SPI); // MOSI
    gpio_set_function(11, GPIO_FUNC_SPI); // SCLK
    spi_init(SPI0, 3 * 1000 * 1000);
    spi_set_format(SPI0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    uint8_t wBuff[3] = {0x01, 0x80, 0x00};
    uint8_t rBuff[3];
    spi_set_slave(SPI0, 0);
    spi_set_CS_toggle(SPI0, false);
    int n = spi_write_read_blocking(SPI0, wBuff, rBuff, 3);
    int data = ((int)rBuff[1] & 0x03) << 8 | (int)rBuff[2];
    float volts = (float)data * 3.3f / 1023.0f;
    printf("%f V\n", volts);
    return (EXIT_SUCCESS);
}