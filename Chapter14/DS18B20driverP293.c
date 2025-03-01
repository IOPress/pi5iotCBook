#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
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

void load1w(int pin)
{
    FILE *fd = doCommand("sudo dtparam -l");
    char output[1024];
    int txfound = 0;
    while (fgets(output, sizeof(output), fd) != NULL)
    {
        printf("%s\n\r", output);
        fflush(stdout);
        if (strstr(output, "w1-gpio-pi5") != NULL)
        {
            txfound = 1;
        }
    }
    pclose(fd);
    if (txfound == 0)
    {
        char cmd[100];
        snprintf(cmd, 100, "sudo dtoverlay w1-gpio-pi5 gpiopin=%d",
                                                             pin);

        fd = doCommand(cmd);
        pclose(fd);
    }
}


int getDevices(char path[][100], int *num)
{
    char buffer[500];
    int fd = open("/sys/bus/w1/drivers/w1_master_driver/w1_bus_master1/w1_master_slaves", O_RDONLY);
    read(fd, buffer, 500);
    close(fd);
    *num = 0;
    for (char *p = strtok(buffer, "\n"); p != NULL;p = strtok(NULL, "\n"))
    {
        snprintf(path[(*num)++], 100, "/sys/bus/w1/devices/%s", p);
    }
    num--;
}

int getData(char path[], char name[], char data[], int n)
{
    char file[100];
    snprintf(file, 100, "%s/%s", path, name);
    int fd = open(file, O_RDONLY);
    int c = read(fd, data, n);
    close(fd);
    data[c] = 0;
    return c;
}

int main(int argc, char **argv)
{
    load1w(4);
    char path[10][100];
    int num;
    getDevices(path, &num);
    printf("%d  %s\n\r", num, path[0]);
    if (num < 1)
        exit(-1);

    char output[1024] = {0};
    char file[100];

    getData(path[0], "name", output, 100);
    printf("Name %s\n\r", output);

    getData(path[0], "resolution", output, 100);
    printf("Resolution %s\n\r", output);

    getData(path[0], "w1_slave", output, 100);
    printf("w1_slave %s\n\r", output);

    getData(path[0], "temperature", output, 100);
    printf("temperature %s\n\r", output);
    float temp;
    sscanf(output, "%f", &temp);
    temp = temp / 1000;
    printf("temperature %f C\n\r",temp);

    getData(path[0], "alarms", output, 100);
    printf("alarms %s\n\r", output);

}