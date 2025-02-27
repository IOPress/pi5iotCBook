#include <gpiod.h>
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char **argv) {
    int res;
    struct gpiod_chip *chip = gpiod_chip_open_by_number(0);
    const char *name = gpiod_chip_name(chip);
    int num = gpiod_chip_num_lines(chip);
    printf("%s %d\n", name, num);
    gpiod_chip_close(chip);
}