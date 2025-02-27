#include <gpiod.h>
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>

int event_cb(int event, unsigned int offset,const struct timespec *timestamp, void *unused)
{
   printf("[%ld.%09ld] %s\n",
     timestamp->tv_sec, timestamp->tv_nsec,
     (event == GPIOD_CTXLESS_EVENT_CB_RISING_EDGE)? "rising" :
     (event == GPIOD_CTXLESS_EVENT_CB_FALLING_EDGE)? "falling" :
     (event == GPIOD_CTXLESS_EVENT_CB_TIMEOUT) ? "timeout" : "??");
     fflush(stdout);
     return GPIOD_CTXLESS_EVENT_CB_RET_OK;
}


int main(int argc, char **argv) {
    int res;
    struct timespec time;
    time.tv_nsec=0;
    time.tv_sec=20;
    res = gpiod_ctxless_event_monitor("0",GPIOD_CTXLESS_EVENT_BOTH_EDGES, 4, 0, "monitor test",&time, NULL, event_cb, NULL);
}