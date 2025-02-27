#define _POSIX_C_SOURCE 199309L
#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int res;

    struct timespec delay = {0, 10 * 1000 * 1000};
    struct timespec time1;

    struct gpiod_chip *chip = gpiod_chip_open_by_number(0);
    struct gpiod_line *line4 = gpiod_chip_get_line(chip, 4);

    res = gpiod_line_request_input(line4, "RMeasure");
    nanosleep(&delay, NULL);
    gpiod_line_release(line4);

    res = gpiod_line_request_output(line4, "RMeasure", 0);
    nanosleep(&delay, NULL);
    gpiod_line_release(line4);
    clock_gettime(CLOCK_REALTIME, &time1);

    gpiod_line_request_rising_edge_events(line4, "RMeasuret");
    struct gpiod_line_event event;
    gpiod_line_event_read(line4, &event);
    printf("Event on line 4 %d, %d", event.event_type,
           (event.ts.tv_nsec - time1.tv_nsec) / 1000);
}