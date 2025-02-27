#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

void pwm(struct gpiod_line *line, int);

int main(int argc, char **argv)
{
    int period = 20;
    int duty = 25;
    int res;
    struct gpiod_chip *chip = gpiod_chip_open_by_number(0);
    struct gpiod_line *line4 = gpiod_chip_get_line(chip, 4);
    res = gpiod_line_request_output(line4, "test output", 0);

    struct timespec ontime = {0, 0};
    struct timespec offtime = {0, 0};
    ontime.tv_nsec = period * duty * 10 * 1000;
    offtime.tv_nsec = (period - period * duty / 100) * 1000 * 1000;

    for (;;)
    {
        res = gpiod_line_set_value(line4, 1);
        nanosleep(&ontime, NULL);
        res = gpiod_line_set_value(line4, 0);
        nanosleep(&offtime, NULL);
    };
}