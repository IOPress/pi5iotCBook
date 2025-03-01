#include <stdio.h>
#include <stdlib.h>
#include "Gpio5.h"

int presence(uint8_t pin)
{
    gpio_set_dir(pin, GPIO_OUT);
    gpio_put(pin, 1);
    sleep_ms(1);
    gpio_put(pin, 0);
    sleep_us(500);
    gpio_set_dir(pin, GPIO_IN);
    sleep_us(70);
    int b = gpio_get(pin);
    sleep_us(410);
    return b;
}

void writeBit(uint8_t pin, int b)
{
    int delay1, delay2;
    if (b == 1)
    {
        delay1 = 6;
        delay2 = 64;
    }
    else
    {
        delay1 = 60;
        delay2 = 10;
    }
    gpio_set_dir(pin, GPIO_OUT);
    gpio_put(pin, 0);
    sleep_us(delay1);
    gpio_set_dir(pin, GPIO_IN);
    sleep_us(delay2);
}

void writeByte(uint8_t pin, int byte)
{
    for (int i = 0; i < 8; i++)
    {
        if (byte & 1)
        {
            writeBit(pin, 1);
        }
        else
        {
            writeBit(pin, 0);
        }
        byte = byte >> 1;
    }
}
uint8_t readBit(uint8_t pin)
{
    gpio_set_dir(pin, GPIO_OUT);
    gpio_put(pin, 0);
    sleep_us(8);
    gpio_set_dir(pin, GPIO_IN);
    sleep_us(2);
    uint8_t b = gpio_get(pin);
    sleep_us(70);
    return b;
}

int readByte(uint8_t pin)
{
    int byte = 0;
    int i;
    for (i = 0; i < 8; i++)
    {
        byte = byte | readBit(pin) << i;
    };
    return byte;
}
int convert(uint8_t pin)
{
    writeByte(pin, 0x44);
    int i;
    for (i = 0; i < 500; i++)
    {
        sleep_ms(10);
        if (readBit(pin) == 1)
            break;
    }
    return i;
}

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

float getTemperature(uint8_t pin)
{
    if (presence(pin) == 1)
        return -1000;
    writeByte(pin, 0xCC);
    if (convert(pin) == 500)
        return -3000;
    presence(pin);
    writeByte(pin, 0xCC);
    writeByte(pin, 0xBE);
    int i;
    uint8_t data[9];
    for (i = 0; i < 9; i++)
    {
        data[i] = readByte(pin);
    }
    uint8_t crc = crc8(data, 9);
    if (crc != 0)
        return -2000;
    int t1 = data[0];
    int t2 = data[1];
    int16_t temp1 = (t2 << 8 | t1);
    float temp = (float)temp1 / 16;
    return temp;
}

 int main()
{
     rp1_Init();
    gpio_init(4);

    if (presence(4) == 1)
    {
        printf("No device \n");
    }
    float t;
    for (;;) {
        do {
            t = getTemperature(4);
        } while (t<-999);
        printf("%f\r\n",t);
        sleep(1);
    };

    return 0;
}  
