#include <stdio.h>
#include <stdlib.h>
#include "Gpio5.h"

inline  void WaitFallingEdge(int gpio)
{
    while (gpio_get(gpio) == 1)
    {
    };
    while (gpio_get(gpio) == 0)
    {
    };
}

uint32_t getData(int gpio)
{
    uint32_t t2;
    uint32_t data = 0;
    uint32_t t1 = time_us_32();
    for (int i = 0; i < 32; i++)
    {
        WaitFallingEdge(gpio);
        t2 = time_us_32();
        data = data << 1;
        data = data | ((t2 - t1) > 100);
        t1 = t2;
    }
    return data;
}

uint8_t getCheck(int gpio)
{
    uint8_t checksum = 0;
    uint32_t t2;
    uint32_t t1 = time_us_32();
    for (int i = 0; i < 8; i++)
    {
        WaitFallingEdge(gpio);
        t2 = time_us_32();
        checksum = checksum << 1;
        checksum = checksum | (t2 - t1) > 100;
        t1 = t2;
    }
    return checksum;
}

void dhtInitalize(int gpio)
{
    gpio_init(gpio);
    gpio_set_dir(gpio, GPIO_OUT);
    gpio_put(gpio, 1);
    sleep_ms(1);
    gpio_put(gpio, 0);
    sleep_ms(1);
    gpio_set_dir(gpio, GPIO_IN);
    for (int i = 0; i < 2; i++)
    {
        WaitFallingEdge(gpio);
    }
}

typedef struct
{
    float temperature;
    float humidity;
    bool error;
} dhtData;

void dhtread(uint32_t gpio, dhtData *reading)
{
    dhtInitalize(gpio);
    uint32_t data = getData(gpio);
    uint8_t checksum = getCheck(gpio);
    uint8_t byte1 = (data >> 24 & 0xFF);
    uint8_t byte2 = (data >> 16 & 0xFF);
    uint8_t byte3 = (data >> 8 & 0xFF);
    uint8_t byte4 = (data & 0xFF);

    reading->error = (checksum !=
               ((byte1 + byte2 + byte3 + byte4) & 0xFF));
    reading->humidity = (float)((byte1 << 8) | byte2) / 10.0;
    int neg = byte3 & 0x80;
    byte3 = byte3 & 0x7F;
    reading->temperature = (float)(byte3 << 8 | byte4) / 10.0;
    if (neg > 0)
        reading->temperature = -reading->temperature;
}
int main()
{
    rp1_Init();
    printf("data\n");
    dhtData reading;
    dhtread(4, &reading);
    printf("Humidity= %f %\n", reading.humidity);
    printf("Temperature= %f C\n", reading.temperature);
    return 0;
}