#include <gpiod.h>
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int res;
    struct gpiod_chip *chip = gpiod_chip_open_by_number(0);

    struct gpiod_line_bulk bulk;
    gpiod_line_bulk_init(&bulk);
    gpiod_line_bulk_add(&bulk, gpiod_chip_get_line(chip, 4));
    gpiod_line_bulk_add(&bulk, gpiod_chip_get_line(chip, 17));

    res=gpiod_line_request_bulk_output(&bulk, "test", 0);
    for (;;) {
        gpiod_line_set_value_bulk(&bulk,(int[2]){0,1});
        gpiod_line_set_value_bulk(&bulk,(int[2]){1,0});

    };
}