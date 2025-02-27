#include <gpiod.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

struct pwmargs
{
    struct gpiod_line *line;
    int ontime;
    int offtime;
};

void *pwmrun(void *arg)
{
    struct pwmargs *pwmdata = (struct pwmargs *)arg;
    volatile int i;
    int res;
    for (;;)
    {
        res = gpiod_line_set_value(pwmdata->line, 1);
        for (i = 0; i < pwmdata->ontime; i++)
        {
        };
        res = gpiod_line_set_value(pwmdata->line, 0);
        for (i = 0; i < pwmdata->offtime; i++)
        {
        };
    };
}

static struct pwmargs pwmdata;
int main(int argc, char **argv)
{

  int period = 10;
  int duty = 25;
  int scale = 385;
  pwmdata.ontime = (period * duty / 100) * scale;
  pwmdata.offtime = (period - period * duty / 100) * scale;
  int res;
  struct gpiod_chip *chip = gpiod_chip_open_by_number(0);
  pwmdata.line = gpiod_chip_get_line(chip, 4);
  res = gpiod_line_request_output(pwmdata.line, "test output", 0);

    pthread_t pwmThread;
    if (pthread_create(&pwmThread, NULL, pwmrun, (void *)&pwmdata))
    {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    for (;;)
    {
    };
}