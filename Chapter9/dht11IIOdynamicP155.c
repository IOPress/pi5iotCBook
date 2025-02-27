#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

FILE *doCommand(char *cmd)
{
    FILE *fp = popen(cmd, "r");
    if (fp == NULL)
    {
        printf("Failed to run command %s \n\r", cmd);
        exit(1);
    }
    return fp;
}
void checkDht11()
{
    FILE *fd = doCommand("sudo  dtparam -l");
    char output[1024];
    int txfound = 0;

    char indicator[] = "dht11  gpiopin=4";
    char command[] = "sudo dtoverlay dht11 gpiopin=4";
    while (fgets(output, sizeof(output), fd) != NULL)
    {
        printf("%s\n\r", output);
        fflush(stdout);
        if (strstr(output, indicator) != NULL)
        {
            txfound = 1;
        }
    }
    if (txfound == 0)
    {
        fd = doCommand(command);
    }

    pclose(fd);
}

int main(int argc, char **argv)
{
    char buffer[25];
    checkDht11();
    int fd = open("/sys/bus/iio/devices/iio:device0/name", O_RDONLY);
    read(fd, buffer, 25);
    close(fd);
    printf("%s", buffer);

    fd = open("/sys/bus/iio/devices/iio:device0/in_temp_input", O_RDONLY);
    read(fd, buffer, 25);
    close(fd);
    int temp;
    sscanf(buffer, "%d", &temp);

    printf("%f\n\r", temp / 1000.0);

    fd = open("/sys/bus/iio/devices/iio:device0/in_humidityrelative_input", O_RDONLY);
    read(fd, buffer, 25);
    close(fd);
    int hum;
    sscanf(buffer, "%d", &hum);
    printf("%f\n\r", hum / 1000.0);
}