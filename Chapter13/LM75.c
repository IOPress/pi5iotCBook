#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
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
int findInd(FILE *fd, char *indicator)
{
    char output[1024];
    int txfound = 0;
    while (fgets(output, sizeof(output), fd) != NULL)
    {
        printf("%s\n\r", output);
        fflush(stdout);
        if (strstr(output, indicator) != NULL)
        {
            txfound = 1;
        }
    }
    return txfound;
}
void checkLM75()
{
    FILE *fd = doCommand("sudo  dtparam -l");
    char indicator1[] = "i2c_arm=on";
    char command1[] = "sudo dtparam i2c_arm=on";
    char indicator2[] = "lm75";
    char command2[] = "sudo dtoverlay i2c-sensor lm75 addr=0x48";

    int txfound = findInd(fd, indicator1);
    if (txfound == 0){
        pclose(fd);
        fd = doCommand(command1);
        sleep(2);
    }
    pclose(fd);
    fd = doCommand("sudo  dtparam -l");
    txfound = findInd(fd, indicator2);
    if (txfound == 0){
        pclose(fd);
        fd = doCommand(command2);
        sleep(2);
    }
    pclose(fd);
}
int main(int argc, char **argv)
{
   checkLM75();

    int fd = open("/sys/class/hwmon/hwmon3/temp1_input",O_RDONLY);
    char buf[100] = {0};
    read(fd, buf, 100);
    printf("%s\n\r", buf);
    float temp;
    sscanf(buf, "%f", &temp);
    temp = temp / 1000;
    printf("%f\n\r", temp);
    close(fd);
}