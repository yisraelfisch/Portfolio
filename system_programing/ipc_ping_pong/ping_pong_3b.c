#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_NAME1 "P1"
#define FIFO_NAME2 "P2"

int main(void)
{
    char buf[5] = {0};
	int fd1 = 0;
    int fd2 = 0;

	if(-1 == mknod(FIFO_NAME1, S_IFIFO | 0666, 0))
    {
        perror("mknod");
    }
    if(-1 == mknod(FIFO_NAME2, S_IFIFO | 0666, 0))
    {
        perror("mknod");
    }
    fd1 = open(FIFO_NAME1, O_RDWR);
	if(-1 == fd1)
    {
        perror("open");
    }
    fd2 = open(FIFO_NAME2, O_RDWR);
    if(-1 == fd2)
    {
        perror("open");
    }

    while(1)
    {
        if(-1 == (read(fd1, buf, sizeof(buf))))
        {
            perror("read");
        }

        printf("%s\n", buf);

        if(-1 == (write(fd2, "PONG", 5)))
        {
            perror("write");
        }
    }

	return 0;
}