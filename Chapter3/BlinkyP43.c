#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
    int fd = open("/sys/class/leds/ACT/trigger", O_WRONLY);
    write(fd, "none",4);
    close(fd);
    fd = open("/sys/class/leds/ACT/brightness", O_WRONLY);
    while (1)
    {
        write(fd, "0",1);
        sleep(1);
        write(fd, "1",1);
        sleep(1);
    }
}