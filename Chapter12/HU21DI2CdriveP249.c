#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>

void checkI2CBus();
FILE * doCommand(char *cmd);
uint8_t crcCheck(uint8_t msb, uint8_t lsb, uint8_t check);

int main(int argc, char** argv) {

    checkI2CBus();

    int i2cfd = open("/dev/i2c-1", O_RDWR);
    ioctl(i2cfd, I2C_SLAVE, 0x40);
    char buf[3] = {0xF3};
    write(i2cfd, buf, 1);

    while (1) {
        int result = read(i2cfd, buf, 3);
        if (result > 0) break;
        usleep(10 * 1000);

    }
    uint8_t msb = buf[0];
    uint8_t lsb = buf[1];
    uint8_t check = buf[2];
    printf("msb %d \n\rlsb %d \n\rchecksum %d \n\r", msb, lsb,
                                                         check);
    unsigned int data16 = ( (unsigned int) msb << 8) | 
                                   (unsigned int) (lsb & 0xFC);
    float temp = (float) (-46.85 + (175.72 * data16 /
                                               (float) 65536));
    printf("Temperature %f C \n\r", temp);
    printf("crc = %d\n\r", crcCheck(msb, lsb, check));
    buf[0] = 0xF5;
    write(i2cfd, buf, 1);

    while (1) {
        int result = read(i2cfd, buf, 3);
        if (result > 0) break;
        usleep(10 * 1000);
    }
    msb = buf[0];
    lsb = buf[1];
    check = buf[2];
    printf("crc = %d\n\r", crcCheck(msb, lsb, check));
    data16 = ((unsigned int) msb << 8) |
                                       (unsigned int) (lsb & 0xFC);
    float hum = -6 + (125.0 * (float) data16) / 65536;
    printf("Humidity %f %% \n\r", hum);
    close(i2cfd);
    return (EXIT_SUCCESS);
}

uint8_t crcCheck(uint8_t msb, uint8_t lsb, uint8_t check) {
    uint32_t data32 = ((uint32_t) msb << 16) | 
                        ((uint32_t) lsb << 8) | (uint32_t) check;
    uint32_t divisor = 0x988000;
    for (int i = 0; i < 16; i++) {
        if (data32 & (uint32_t) 1 << (23 - i)) data32 ^= divisor;
        divisor >>= 1;
    };
    return (uint8_t) data32;
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

FILE * doCommand(char *cmd) {
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("Failed to run command %s \n\r", cmd);
        exit(1);
    }
    return fp;
}