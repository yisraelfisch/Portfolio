#define _DEFAULT_SOURCE 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

#define SIZE  20

int main()
{
    int fd = 0;
    const char *buf = "ping";
    char *name = "/shared";
    void *str = NULL;

    if((fd = shm_open(name, O_CREAT | O_RDWR, 0666)) < 0)
    {
        perror("shm_open");
        exit (1);
    }

    ftruncate(fd, SIZE);

    printf("new income message\n");
    str = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    if(str == (void *)-1)
    {
        perror("mmap");
        exit (1);
    }
    printf("check");
    sprintf((char *)str, "%s", buf);

    munmap(str, SIZE);
    close(fd);
    return 0;
}
