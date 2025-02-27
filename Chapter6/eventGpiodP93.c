#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>
#include <sys/epoll.h>
#include <gpiod.h>

int main(int argc, char **argv)
{
    int res;
    struct gpiod_chip *chip = gpiod_chip_open_by_number(0);
    struct gpiod_line *line4 = gpiod_chip_get_line(chip, 4);
    res = gpiod_line_request_rising_edge_events(line4, "button");
    int fd = gpiod_line_event_get_fd(line4);
    static struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    int epfd = epoll_create(1);
    res = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);

    int nfds = epoll_wait(epfd, &ev, 1, 20000);
    if (nfds != 0)
    {
        struct gpioevent_data edata;
        read(fd, &edata, sizeof edata);
        printf("%u,%llu", edata.id, edata.timestamp);
    }
}