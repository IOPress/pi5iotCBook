#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>
int main(int argc, char **argv)
{
    int fd, ret;
    struct gpiohandle_request req;
    req.lineoffsets[0] = 4;
    req.lineoffsets[1] = 17;
    req.flags = GPIOHANDLE_REQUEST_INPUT;
    strcpy(req.consumer_label, "Input test");
    req.lines = 2;
    fd = open("/dev/gpiochip0", O_RDONLY);
    ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    close(fd);
    struct gpiohandle_data data;
    ret = ioctl(req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
    printf("%hhu , %hhu", data.values[0], data.values[1]);
    close(req.fd);
    return 0;
}
