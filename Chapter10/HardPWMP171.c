#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
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
void checkPWM()
{
    FILE *fd = doCommand("sudo  dtparam -l");
    char output[1024];
    int txfound = 0;

    char indicator[] = "pwm";
    char command[] = "sudo dtoverlay pwm-2chan,pin=13 func=4 pin2=12 func2=4";
    while (fgets(output, sizeof(output), fd) != NULL)
    {
        printf("%s\n\r", output);
        fflush(stdout);
        if (strstr(output, indicator) != NULL)
        {
            txfound = 1;
            printf("Overlay already loaded\n\r");
        }
    }
    if (txfound == 0)
    {
        fd = doCommand(command);
        sleep(2);
    }
    pclose(fd);
}

int main(int argc, char **argv)
{
    checkPWM();      
    int fd = open("/sys/class/pwm/pwmchip2/export", O_WRONLY);
    write(fd, "0", 1); 
    close(fd);
    sleep(3);
    fd = open("/sys/class/pwm/pwmchip2/pwm0/period", O_WRONLY);
    write(fd, "10000000", 8);
    close(fd);
    fd = open("/sys/class/pwm/pwmchip2/pwm0/duty_cycle", O_WRONLY);
    write(fd, "8000000", 7);
    close(fd);
    fd = open("/sys/class/pwm/pwmchip2/pwm0/enable", O_WRONLY);
    write(fd, "1", 1);
    close(fd);   
    fd = open("/sys/class/pwm/pwmchip2/export", O_WRONLY);
    write(fd, "1", 1); 
    close(fd);
    sleep(3);
    fd = open("/sys/class/pwm/pwmchip2/pwm1/period", O_WRONLY);
    write(fd, "10000000", 8);
    close(fd);
    fd = open("/sys/class/pwm/pwmchip2/pwm1/duty_cycle", O_WRONLY);
    write(fd, "5000000", 7);
    close(fd);
    fd = open("/sys/class/pwm/pwmchip2/pwm1/enable", O_WRONLY);
    write(fd, "1", 1);
    close(fd);
}