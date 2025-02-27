#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

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

    char indicator[] = "pwm-2chan";
    char command[] = "sudo dtoverlay pwm-2chan pin=12 func=4 pin2=13 func2=4";
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
        pclose(fd);
        fd = doCommand(command);
    }

    pclose(fd);
}
enum pwm
{
    OpenChan,
    SetFreq,
    SetDuty,
    EnableChan,
    DisableChan,
    CloseChan
};

int pwmAction(enum pwm action, int chan, int param)
{
    static int fdf[2];
    static int fdd[2];
    int fd;
    char buf[150];
    char schan[6];

    if (chan != 0 && chan != 1)
        return -1;


    char path[] = "/sys/class/pwm/pwmchip2/";
    char chanNum[2];
    snprintf(schan, 6, "%s%d","pwm",chan);
    snprintf(chanNum,2,"%d",chan); 
    int L;
    switch (action)
    {
    case OpenChan:
        checkPWM();
        snprintf(buf, 150, "%s%s", path, "export");
        fd = open(buf, O_WRONLY);      
        write(fd,chanNum , 1);
        close(fd);
        sleep(2);
        snprintf(buf, 150, "%s%s%s", path, schan, "/period");
        fdf[chan] = open(buf, O_WRONLY);
        snprintf(buf, 150, "%s%s%s", path, schan, "/duty_cycle");
        fdd[chan] = open(buf, O_WRONLY);
        break;
    case SetFreq:
        L = snprintf(buf, 150, "%d", param);
        write(fdf[chan], buf, L);
        break;
    case SetDuty:
        L = snprintf(buf, 150, "%d", param);
        write(fdd[chan], buf, L);
        break;
    case EnableChan:
        snprintf(buf, 150, "%s%s%s", path, schan, "/enable");
        fd = open(buf, O_WRONLY);
        write(fd, "1", 1);
        close(fd);
        break;
    case DisableChan:
        snprintf(buf, 150, "%s%s%s", path, schan, "/enable");
        fd = open(buf, O_WRONLY);
        write(fd, "0", 1);
        close(fd);
        break;
    case CloseChan:
        close(fdf[chan]);
        close(fdd[chan]);
        snprintf(buf, 150, "%s%s%s", path, "/unexport");
        printf("%s\n",buf);
        fd = open(buf, O_WRONLY);
        write(fd, chanNum, 1);
        close(fd);
        break;
    }
    return 0;
}

int main(int argc, char **argv)
{

    pwmAction(OpenChan, 1, 0);
    pwmAction(SetFreq, 1, 10000000);
    pwmAction(SetDuty, 1, 8000000);
    pwmAction(EnableChan, 1, 0);

    pwmAction(OpenChan, 0, 0);
    pwmAction(SetFreq, 0, 10000000);
    pwmAction(SetDuty, 0, 2000000);
    pwmAction(EnableChan, 0, 0); 
}