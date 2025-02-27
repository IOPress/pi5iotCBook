#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char** argv) {
    int fd = open("/sys/class/hwmon/hwmon0/temp1_input", O_RDONLY);
    char buf[100] = {0};
    read(fd, buf, 100);
    printf("%s\n\r", buf);
    float temp;
    sscanf(buf, "%f", &temp);
    temp = temp / 1000;
    printf("%f\n\r", temp);
}