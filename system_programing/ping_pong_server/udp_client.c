#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 

#define PORT 4000

int main(int argc, char **argv)
{
    char buf[5] = {0};
    int sock_fd = 0;
    struct sockaddr_in server_addr = {0};
    socklen_t addrlen = 0;
    

    if(argc < 2)
    {
        perror("too few arguments");
        return 1;
    } 


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
  
    
    if(-1 == (sock_fd = socket(AF_INET, SOCK_DGRAM, 0)))
    {
        perror("socket");
        return 1;
    }


    if(-1 == sendto(sock_fd, "ping", strlen("ping")+1, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)))
    {
        perror("sendto");
        return 1;
    }


    if(-1 == recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr *)&server_addr, &addrlen))
    {
        return 0;
    }

    printf("%s\n", buf);

    close(sock_fd);
    return 0;


}