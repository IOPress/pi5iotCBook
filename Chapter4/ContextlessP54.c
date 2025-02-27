#include <gpiod.h>
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
int res;
int main(int argc, char **argv) {
    for (;;) {
         res = gpiod_ctxless_set_value("0", 4, 1, 1, "output test", NULL, NULL);
         res = gpiod_ctxless_set_value("0", 4, 0, 1, "output test", NULL, NULL);
    }
}