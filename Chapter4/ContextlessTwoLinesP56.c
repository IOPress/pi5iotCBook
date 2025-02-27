#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
int res;
int delayms(int ms)
{
    struct timespec delay = {0, ms * 1000 * 1000};
    return nanosleep(&delay, NULL);
}
int main(int argc, char **argv)
{
    int offsets[] = {4, 17};
    int state1[] = {1, 0};
    int state2[] = {0, 1};
    for (;;)
    {
        gpiod_ctxless_set_value_multiple("0", offsets, state1, 2, 1, "output test", (gpiod_ctxless_set_value_cb)delayms, (void *)1);
        gpiod_ctxless_set_value_multiple("0", offsets, state2, 2, 1, "output test", (gpiod_ctxless_set_value_cb)delayms, (void *)2);
    }
}