#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define SERVER_QUEUE_NAME   "/server"
#define MAX_MESSAGES        10
#define MAX_MSG_SIZE        10


int main()
{
    int i = 3;
    mqd_t qd_server = {0};
    char buf[MAX_MSG_SIZE] = {"ping"};

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;   

    if((qd_server = mq_open (SERVER_QUEUE_NAME, O_WRONLY | O_CREAT, 0666, &attr)) == -1)
    {
        perror ("Server: mq_open (server)");
        exit (1);
    }

    while(i--)
    {
        printf("new income message\n");
        if(mq_send (qd_server, buf, strlen(buf)+1 , 0) == -1)
        {
            perror ("Send");

        }

    }

    if(mq_close (qd_server) == -1)
    {
        perror ("mq_close");
        exit (1);
    }

    return 0;


}