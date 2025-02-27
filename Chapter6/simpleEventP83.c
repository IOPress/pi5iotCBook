#include <gpiod.h>
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int res;
    struct gpiod_chip *chip = gpiod_chip_open_by_number(0);
    struct gpiod_line *line4 = gpiod_chip_get_line(chip, 4);
    gpiod_line_request_both_edges_events(line4, "event test");
    gpiod_line_event_wait(line4, NULL);
    printf("Event on line 4");
}