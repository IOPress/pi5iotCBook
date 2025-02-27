#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <gpiod.h>
#include <sys/epoll.h>
#include <pthread.h>

typedef void (*eventHandler)(struct gpiod_line_event *);

typedef struct
{
    struct gpiod_line *line;
    eventHandler func;
} intVec;

void myHandler(struct gpiod_line_event *event)
{
    printf("%d,%d \n\r", event->event_type,event->ts.tv_nsec / 1000);
    fflush(stdout);
}

void *waitInterrupt(void *arg)
{
    intVec *intData = (intVec *)arg;
    struct gpiod_line_event event;
    while (true)
    {
        int res = gpiod_line_event_read(intData->line, &event);
        if (res == 0)
            intData->func(&event);
    }
}

int main(int argc, char **argv)
{
    int fd, ret, res;

    struct gpiod_chip *chip = gpiod_chip_open_by_number(0);
    struct gpiod_line *line4 = gpiod_chip_get_line(chip, 4);

    res = gpiod_line_request_rising_edge_events(line4, "button");

    intVec intData;
    intData.line = line4;
    intData.func = &myHandler;

    pthread_t intThread;
    if (pthread_create(&intThread, NULL, waitInterrupt,
                                              (void *)&intData))
    {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    for (;;)
    {
        printf("Working\n\r");
        fflush(stdout);
        sleep(2);
    }
}