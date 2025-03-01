#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
int main(int argc, char **argv)
{
    char buf[100];
    int fd =open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw",O_RDONLY);
  
    int n = read(fd, buf, 100);

    int data;
    sscanf(buf, "%d", &data);

    printf("%d\n\r", data);
    float volts = (((float)data) * 3.3f) / 1023.0f;
    printf("%f V\n\r", volts);
}