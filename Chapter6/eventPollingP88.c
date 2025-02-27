#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int gpiod_line_event_poll(struct gpiod_line *line,struct gpiod_line_event *event);

int main(int argc, char **argv)
{
    int res;

    struct gpiod_chip *chip = gpiod_chip_open_by_number(0);
    struct gpiod_line *line4 = gpiod_chip_get_line(chip, 4);

    res = gpiod_line_request_both_edges_events(line4, "button");

    struct gpiod_line_event event;

    while (true)
    {
        res = gpiod_line_event_poll(line4, &event);
        if (res > 0)
        {
            gpiod_line_event_read(line4, &event);
            printf("Event on line 4 %d,%d \n\r ",event.event_type, event.ts);
            fflush(stdout);
        }
    }

}

int gpiod_line_event_poll(struct gpiod_line *line,struct gpiod_line_event *event)
{
    struct timespec timeout = {0, 0};
    int res = gpiod_line_event_wait(line, &timeout);
    if (res > 0)
        res = gpiod_line_event_read(line, event);
    if (res == 0)
        res = 1;
    return res;
}