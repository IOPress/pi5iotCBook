#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char **argv)
{
    int res;
    struct timespec time1;
    struct gpiod_chip *chip = gpiod_chip_open_by_number(0);
    struct gpiod_line *line4 = gpiod_chip_get_line(chip, 4);
    res = gpiod_line_request_both_edges_events(line4, "Measure");
    struct gpiod_line_event event;
    while (true)
    {
        do
        {
            res = gpiod_line_event_read(line4, &event);
        } while (event.event_type != GPIOD_LINE_EVENT_RISING_EDGE);
       
        time1.tv_nsec = event.ts.tv_nsec;

        do
        {
            res = gpiod_line_event_read(line4, &event);
        } while (event.event_type != GPIOD_LINE_EVENT_FALLING_EDGE);

        printf("Pulse Width %d \r\n",
                                       (event.ts.tv_nsec - time1.tv_nsec) / 1000);
        fflush(stdout);
    }
}