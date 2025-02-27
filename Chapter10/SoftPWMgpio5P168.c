#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "Gpio5.h"

struct pwmargs
{
    int ontime;
    int offtime;   
};
void *pwmrun(void *arg)
{
    struct pwmargs *pwmdata = (struct pwmargs *)arg;
    volatile int i;
    for (;;)
    {
        gpio_put(4, true);
        for(i=0;i<pwmdata->ontime;i++){};
        gpio_put(4, false);
        for(i=0;i<pwmdata->offtime;i++){};
    };
}

static struct pwmargs pwmdata;
int main(int argc, char **argv)
{
    int period = 50;
    int duty = 25;
    int scale=435;
    pwmdata.ontime=(period*duty/100)*scale;
    pwmdata.offtime =  (period - period * duty / 100) *scale;
    rp1_Init();
    gpio_init(4);
    gpio_set_dir(4, true);
    pthread_t pwmThread;
    if (pthread_create(&pwmThread, NULL, pwmrun, (void *)&pwmdata))
    {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    while(true){};
    return 0;
}