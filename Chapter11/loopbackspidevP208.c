#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdint.h>
FILE *doCommand(char *cmd)
{
    FILE *fp = popen(cmd, "r");
    if (fp == NULL)
    {
        printf("Failed to run command %s \n\r", cmd);
        exit(1);
    }
    return fp;
}

void checkSPI0()
{
    FILE *fd = doCommand("sudo  dtparam -l");
    char output[1024];
    int txfound = 0;

    char indicator[] = "spi=on";
    char command[] = "sudo dtparam spi=on";
    while (fgets(output, sizeof(output), fd) != NULL)
    {
        printf("%s\n\r", output);
        fflush(stdout);
        if (strstr(output, indicator) != NULL)
        {
            txfound = 1;
        }
    }
    if (txfound == 0)
    {
        fd = doCommand(command);
        sleep(2);
    }

    pclose(fd);
}

int main(int argc, char **argv)
{
    checkSPI0();

    uint8_t tx[] = {0xAA};
    uint8_t rx[] = {0};

    struct spi_ioc_transfer tr =
        {
            .tx_buf = (unsigned long)tx,
            .rx_buf = (unsigned long)rx,
            .len = 1,
            .delay_usecs = 0,
            .speed_hz = 500000,
            .bits_per_word = 8,
        };

    int fd = open("/dev/spidev0.0", O_RDWR);   
    int status = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if (status < 0)
        printf("can't send data");
    printf("%X,%X", tx[0],rx[0]);
    close(fd);
}