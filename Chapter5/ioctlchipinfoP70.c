#include <stdio.h> 
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>
int main(int argc, char **argv) {
    int fd;
    struct gpiochip_info info;
    fd = open("/dev/gpiochip0", O_RDONLY);
    int ret = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &info);
    close(fd);
    printf("label: %s\n name: %s\n number of lines: %u\n",info.label,info.name,info.lines);
    return 0;
}