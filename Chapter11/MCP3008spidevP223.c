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

    uint8_t tx[] = {0x01, 0x80, 0x00};
    uint8_t rx[3];

    struct spi_ioc_transfer tr =
        {
            .tx_buf = (unsigned long)tx,
            .rx_buf = (unsigned long)rx,
            .len = 3,
            .delay_usecs = 0,
            .speed_hz = 0,
            .bits_per_word = 0,
        };

    int fd = open("/dev/spidev0.0", O_RDWR);

    static uint8_t mode = 0;
    int status = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (status == -1)
        printf("can't set spi mode");

    static uint8_t bits = 8;
    status = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (status == -1)
        printf("can't set bits per word");

    static uint32_t speed = 100000;
    status = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (status == -1)
        printf("can't set max speed hz");

    status = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    if (status < 0)
        printf("can't send data");

    int data = ((int)rx[1] & 0x03) << 8 | (int)rx[2];
    float volts = (((float)data) * 3.3f) / 1023.0f;
    printf("%f V\n\r", volts);

    close(fd);
}