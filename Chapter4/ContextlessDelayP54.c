#include <gpiod.h>
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
int res;

int delayms(int ms) {
    struct timespec delay = {0, ms * 1000*1000};
    return nanosleep(&delay, NULL);
}

int main(int argc, char **argv) {
    for (;;) {
        res = gpiod_ctxless_set_value("0", 4, 1, 1, "output test",(gpiod_ctxless_set_value_cb) delayms, (void *) 100);
        res = gpiod_ctxless_set_value("0", 4, 0, 1, "output test",(gpiod_ctxless_set_value_cb) delayms, (void *) 100);
    }
}