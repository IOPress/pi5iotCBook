#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Gpio5.h"

int main(int argc, char **argv)
{
    rp1_Init();

    gpio_set_function(8, GPIO_FUNC_SPI);  // CS0
    gpio_set_function(7, GPIO_FUNC_SPI);  // CS1
    gpio_set_function(3, GPIO_FUNC_SPI);  // CS2
    gpio_set_function(4, GPIO_FUNC_SPI);  // CS3
    gpio_set_function(9, GPIO_FUNC_SPI);  // MISO
    gpio_set_function(10, GPIO_FUNC_SPI); // MOSI
    gpio_set_function(11, GPIO_FUNC_SPI); // SCLK

    spi_init(SPI0, 5000000);
    spi_set_format(SPI0, 8, SPI_CPOL_0, SPI_CPHA_0,
                   SPI_MSB_FIRST);
    spi_set_slave(SPI0, 0);
    uint8_t wBuff[1] = {0xAA};
    uint8_t rBuff[1];
    int n = spi_write_read_blocking(SPI0, wBuff, rBuff, 1);
    printf(" %X %X %d \n ", wBuff[0], rBuff[0], n);
    return (EXIT_SUCCESS);
}