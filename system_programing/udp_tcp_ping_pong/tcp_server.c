#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 

#define PORT 4000
#define BACK_LOG 5

int main()
{
    char buf[5] = {0};
    int sock_fd = 0;
    int accept_fd = 0;
    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};
    socklen_t addrlen = 0;
    

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  
    
    if(-1 == (sock_fd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("socket");
        return 1;
    }


    if(-1 == bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        perror("bind");
        return 1;
    }

    if(-1 == listen(sock_fd, BACK_LOG))
    {
        perror("listen");
        return 1;
    }

    addrlen = sizeof(client_addr);

    printf("waiting for connection, my address is %d\n", server_addr.sin_addr.s_addr);
    
    if(-1 == (accept_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &addrlen)))
    {
        perror("accept");
        return 1;
    }


    if(-1 == recv(accept_fd, buf, sizeof(buf), 0 ))
    {
        perror("recv");
        return 0;
    }

    printf("%s\n", buf);

    if(-1 == send(accept_fd, "pong", strlen("pong")+1, 0))
    {
        perror("sendto");
        return 1;
    }

    close(sock_fd);

}