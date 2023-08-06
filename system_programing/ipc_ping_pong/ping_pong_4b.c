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
    mqd_t qd_server = {0};
    char buf[MAX_MSG_SIZE] = {0};
    

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;   

    if((qd_server = mq_open (SERVER_QUEUE_NAME, O_RDONLY, 0666, &attr)) == -1)
    {
        perror ("Server: mq_open (server)");
        exit (1);
    }

  
    if(mq_receive(qd_server, buf , MAX_MSG_SIZE , 0) == -1)
    {
        perror ("recive");
        exit (1);
    }
    printf("got the message: %s\n", buf);

    if(mq_close (qd_server) == -1)
    {
        perror ("mq_close");
        exit (1);
    }



    return 0;

}