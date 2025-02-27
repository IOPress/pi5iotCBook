#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

typedef struct{
    uint32_t status;
    uint32_t ctrl; 
}GPIOregs;

#define GPIO ((GPIOregs*)GPIOBase)

typedef struct
{
    uint32_t Out;
    uint32_t OE;
    uint32_t In;
    uint32_t InSync;
} rioregs;

#define rio ((rioregs *)RIOBase)
#define rioXOR ((rioregs *)(RIOBase + 0x1000 / 4))
#define rioSET ((rioregs *)(RIOBase + 0x2000 / 4))
#define rioCLR ((rioregs *)(RIOBase + 0x3000 / 4))


int main(int argc, char **argv)
{
    int memfd = open("/dev/mem", O_RDWR | O_SYNC);
    uint32_t *map = (uint32_t *)mmap(
        NULL,
        64 * 1024 * 1024,
        (PROT_READ | PROT_WRITE),
        MAP_SHARED,
        memfd,
        0x1f00000000
    );
    if (map == MAP_FAILED)
    {
        printf("mmap failed: %s\n", strerror(errno));
        return (-1);
    };
    close(memfd);

    uint32_t *PERIBase = map;
    uint32_t *GPIOBase = PERIBase + 0xD0000 / 4;
    uint32_t *RIOBase = PERIBase + 0xe0000 / 4;
    uint32_t *PADBase = PERIBase + 0xf0000 / 4;
    uint32_t *pad = PADBase + 1;   
    
    uint32_t pin = 2;
    uint32_t fn = 5;

    GPIO[pin].ctrl=fn;
    pad[pin] = 0x10;
    rioSET->OE = 0x01<<pin;
    rioSET->Out = 0x01<<pin;
    
    for (;;)
    {
        rioXOR->Out = 0x04;
    } 
    return (EXIT_SUCCESS);
}