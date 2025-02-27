#define _POSIX_C_SOURCE 199309L
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/gpio.h>
#include <sys/ioctl.h>
#include <time.h>
int main(int argc, char **argv)
{
    int fd, ret;
    struct timespec delay = {0, 10 * 1000 * 1000};
    struct timespec time1, time2;
    fd = open("/dev/gpiochip0", O_RDONLY);
    struct gpiohandle_request req;
    req.lineoffsets[0] = 4;
    strcpy(req.consumer_label, "RC Measure");
    req.lines = 1;

    req.flags = GPIOHANDLE_REQUEST_INPUT;
    ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    nanosleep(&delay, NULL);
    close(req.fd);

    req.flags = GPIOHANDLE_REQUEST_OUTPUT;
    struct gpiohandle_data data;
    data.values[0] = 0;
    ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    ret = ioctl(req.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
    nanosleep(&delay, NULL);
    close(req.fd);

    req.flags = GPIOHANDLE_REQUEST_INPUT;
    clock_gettime(CLOCK_REALTIME, &time1);
    ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
    ret = ioctl(req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);

    while (data.values[0] == 0)
    {
        ret = ioctl(req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL,
                    &data);
    }
    clock_gettime(CLOCK_REALTIME, &time2);
    printf("Time=%d", (time2.tv_nsec - time1.tv_nsec) / 1000);
    return 0;
}