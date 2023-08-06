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
    char *name = "/shared";
    char buf[10] = {0};
    char *str = NULL;

    if((fd = shm_open(name, O_CREAT | O_RDWR, 0666)) < 0)
    {
        perror("shm_open");
        exit (1);
    }

    ftruncate(fd, SIZE);

    str = (char *)mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(str == (void *)-1)
    {
        perror("mmap");
        exit (1);
    }
    sprintf(buf, "%s", str);
    printf("got the message: %s\n", buf);

    munmap(str, SIZE);
    close(fd);
    shm_unlink(name);
    return 0;
}