#include "ping_pong_server.h"
#define BACK_LOG 5

int CreateSocketServer(int port, int type)
{
    int sock_fd = 0;
    struct sockaddr_in server_addr = {0};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(-1 == (sock_fd = socket(AF_INET, type, 0)))
    {
        perror("socket");
        return -1;
    }

    if(-1 == bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        perror("bind");
        return -1;
    }

    if(type == SOCK_STREAM)
    {
        if(-1 == listen(sock_fd, BACK_LOG))
        {
            perror("listen");
            return 1;
        }
        printf("waiting for tcp connection\n");
    }
    else
    {
        printf("waiting for udp connection\n");
    }


    return sock_fd;
}

int CreateSocketClient(int port, unsigned int address, int type)
{
    int sock_fd = 0;
    struct sockaddr_in server_addr = {0};


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = address;
  
    
    if(-1 == (sock_fd = socket(AF_INET, type, 0)))
    {
        perror("socket");
        return -1;
    }

    return sock_fd;
}