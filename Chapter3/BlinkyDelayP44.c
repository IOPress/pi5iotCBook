#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
    int fd = open("/sys/class/leds/ACT/trigger", O_WRONLY);
    write(fd, "timer", 5);
    close(fd);
    fd = open("/sys/class/leds/ACT/delay_on", O_WRONLY);
    write(fd, "2000", 4);
    close(fd);
    fd = open("/sys/class/leds/ACT/delay_off", O_WRONLY);
    write(fd, "3000", 4);
    close(fd);
}