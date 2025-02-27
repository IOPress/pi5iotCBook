#include <gpiod.h>
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int res;
    struct gpiod_chip *chip = gpiod_chip_open_by_number(0);
    struct gpiod_line *line4 = gpiod_chip_get_line(chip, 4);
    res=gpiod_line_request_output(line4, "test output", 0);

    for(;;){
        res=gpiod_line_set_value(line4,  1);
        res=gpiod_line_set_value(line4,  0);
    };
}