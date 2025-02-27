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
    req.flags = GPIOHANDLE_REQUEST_OUTPUT;
    req.default_values[0] = 0;
    req.default_values[1] = 0;
    strcpy(req.consumer_label, "Output test");
    req.lines = 2;

    fd = open("/dev/gpiochip0", O_RDONLY);
    ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    close(fd);

    struct gpiohandle_data data;
    data.values[0] = 0;
    data.values[1] = 1;
    while (1)
    {
        data.values[0] = !data.values[0];
        data.values[1] = !data.values[1];
        ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    }
    return 0;
}
