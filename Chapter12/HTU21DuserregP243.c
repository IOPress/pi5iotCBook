#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

FILE * doCommand(char *cmd) {
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command %s \n\r", cmd);
        exit(1);
    }
    return fp;
}

void checkI2CBus() {
    FILE *fd = doCommand("sudo dtparam -l");
    char output[1024];
    int txfound = 0;
    while (fgets(output, sizeof (output), fd) != NULL) {
        printf("%s\n\r", output);
        fflush(stdout);
        if (strstr(output, "i2c_arm=on") != NULL) {
            txfound = 1;
        }
        if (strstr(output, "i2c_arm=off") != NULL) {
            txfound = 0;
        }
    }
    pclose(fd);
    if (txfound == 0) {
        fd = doCommand("sudo dtparam i2c_arm=on");
        pclose(fd);
    }
}


int main(int argc, char** argv) {

    checkI2CBus();

    int i2cfd = open("/dev/i2c-1", O_RDWR);
    ioctl(i2cfd, I2C_SLAVE, 0x40);
    char buf[4] = {0xE7};
    write(i2cfd,buf,1);
    read(i2cfd,buf,1);
    printf("%x\n\r",buf[0]);
    close(i2cfd);
    return (EXIT_SUCCESS);
}

