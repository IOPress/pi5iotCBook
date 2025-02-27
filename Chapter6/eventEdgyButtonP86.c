#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int res;
    struct gpiod_chip *chip = gpiod_chip_open_by_number(0);
    struct gpiod_line *line4 = gpiod_chip_get_line(chip, 4);   
    res = gpiod_line_request_input(line4,"button");
    printf("Press button \n\r");
    fflush(stdout);
    sleep(20);
    if (gpiod_line_get_value(line4) == 1)
    {
        printf("button pressed");
    }
    else
    {
        printf("button not pressed");
    }
}