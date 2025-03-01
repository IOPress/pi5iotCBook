#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

void loadHTU21();

int main(int argc, char** argv) {
    loadHTU21();
    float temp;
    float hum;   
    {
        char output[1024] = {0};
        int fdtemp = open("/sys/bus/iio/devices/iio:device0/in_temp_input", O_RDWR);
        read(fdtemp, output, sizeof (output));
        close(fdtemp);
        printf("%s\n\r", output);
        sscanf(output, "%f", &temp);
        temp = temp / 1000;
        fflush(stdout);
    }

    {
        char output[1024] = {0};
        int fdhum = open("/sys/bus/iio/devices/iio:device0/in_humidityrelative_input", O_RDWR);
        read(fdhum, output, sizeof (output));
        close(fdhum);
        printf("%s\n\r", output);
        sscanf(output, "%f", &hum);
        hum = hum / 1000;
        fflush(stdout);
    }
    printf("%f\n\r", temp);
    printf("%f\n\r", hum);

    return (EXIT_SUCCESS);
}

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
void loadHTU21() {
    FILE *fd = doCommand("sudo dtparam -l");
    char output[1024];
    int txfound = 0;
    while (fgets(output, sizeof (output), fd) != NULL) {
        printf("%s\n\r", output);
        fflush(stdout);
        if (strstr(output, "i2c-sensor  htu21=true") != NULL) {
            txfound = 1;
        }
    }
    pclose(fd);
    if (txfound == 0) {
        fd = doCommand("sudo dtoverlay i2c-sensor htu21");
        pclose(fd);
    }
}