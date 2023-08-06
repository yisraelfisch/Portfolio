#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 

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

    printf("waiting for connection, my address is %d\n", server_addr.sin_addr.s_addr);

    return sock_fd;
}

int CreateSocketClient(int port, unsigned int address)
{
    int sock_fd = 0;
    struct sockaddr_in server_addr = {0};


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = address;
  
    
    if(-1 == (sock_fd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        perror("socket");
        return -1;
    }

    return sock_fd;
}

#define PORT 4000

int main()
{
    char buf[5] = {0};
    int sock_fd = 0;
    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};
    socklen_t addrlen = 0;
    

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  
    
    if(-1 == (sock_fd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        perror("socket");
        return 1;
    }


    if(-1 == bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        perror("bind");
        return 1;
    }

    printf("waiting for connection, my address is %d\n", server_addr.sin_addr.s_addr);

    addrlen = sizeof(client_addr);
    if(-1 == recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &addrlen))
    {
        perror("recvfrom")
        return -1;
    }    
        

    printf("%s\n", buf);

    if(-1 == sendto(sock_fd, "fischy", strlen("ficshy")+1, 0, (struct sockaddr *)&client_addr, addrlen))
    {
        perror("sendto");
        return 1;
    }

}