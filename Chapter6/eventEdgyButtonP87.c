#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int res;    
    struct timespec timeout = {0, 0};    
    struct gpiod_chip *chip = gpiod_chip_open_by_number(0);
    struct gpiod_line *line4 = gpiod_chip_get_line(chip, 4);
    res = gpiod_line_request_both_edges_events(line4, "button");    
    printf("Press button \n\r");
    fflush(stdout);
    sleep(20);
    struct gpiod_line_event event;

    res=gpiod_line_event_wait(line4,&timeout);
    if (res>0)
    {
        res = gpiod_line_event_read(line4, &event);
        printf("button pressed %d",event.ts.tv_nsec);
    }
    else
    {
        printf("button not pressed");
    }

}