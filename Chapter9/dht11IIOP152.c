#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
    char buffer[25];
    int fd = open("/sys/bus/iio/devices/iio:device0/name",
                                                   O_RDONLY);
    read(fd, buffer, 25);
    close(fd);
    printf("%s",buffer);
    fd = open("/sys/bus/iio/devices/iio:device0/in_temp_input", 
                                                       O_RDONLY);
    read(fd, buffer, 25);
    close(fd);
    int temp;
    sscanf(buffer, "%d", &temp);

    printf("%f\n\r", temp / 1000.0);
    fd=open("/sys/bus/iio/devices/iio:device0/in_humidityrelative_input",O_RDONLY);
    read(fd, buffer, 25);
    close(fd);
    int hum;
    sscanf(buffer, "%d", &hum);
    printf("%f\n\r", hum / 1000.0);
}