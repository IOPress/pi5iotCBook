#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>

void checkI2CBus();
FILE * doCommand(char *cmd);
int i2cReadRegister(int i2cfd, uint8_t slaveaddr, uint8_t reg, uint8_t *buf,int len);

int main(int argc, char** argv) {  
    checkI2CBus();
    int i2cfd = open("/dev/i2c-1", O_RDWR);    
    char buf2[1]={0};
    i2cReadRegister(i2cfd, 0x40, 0xE7,buf2,1);  
    printf("%d \n\r",buf2[0]);
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

int i2cReadRegister(int i2cfd, uint8_t slaveaddr, uint8_t reg, 
    uint8_t *buf,int len) {

struct i2c_msg msgs[2];
struct i2c_rdwr_ioctl_data msgset[1];

msgs[0].addr = slaveaddr;
msgs[0].flags = 0;
msgs[0].len = 1;
msgs[0].buf = &reg;

msgs[1].addr = slaveaddr;
msgs[1].flags = I2C_M_RD;
msgs[1].len = len;
msgs[1].buf = buf;

msgset[0].msgs = msgs;
msgset[0].nmsgs = 2;

if (ioctl(i2cfd, I2C_RDWR, &msgset) < 0) {
return -1;
}
return 0;
}