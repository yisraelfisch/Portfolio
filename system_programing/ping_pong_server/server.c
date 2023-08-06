#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>
#include "ping_pong_server.h"

#define PORT 4000

int main()
{
    fd_set read_fds;
    fd_set read_fds_master;
    int highest_fds = -1;
    int udp_socket = -1;
    int tcp_socket = -1;
    int accept_socket = -1;
    char stdin_buf[1024] = {0};
    char udp_buf[1024] = {0};
    char tcp_buf[1024] = {0};
    struct sockaddr_in udp_client_addr = {0};
    struct sockaddr_in tcp_client_addr = {0};
    socklen_t udp_sock_len = 0;
    socklen_t accept_sock_len = 0;
    int retval;
    printf("waiting for stdin connection\n");

    if(-1 == (udp_socket = CreateSocketServer(PORT, SOCK_DGRAM)))
    {
        perror("CreateSocketServer - UDP socket");
        return 1;
    }

    highest_fds = udp_socket;

    if(-1 == (tcp_socket = CreateSocketServer(PORT, SOCK_STREAM)))
    {
        perror("CreateSocketServer - TCP socket");
        return 1;
    }

    highest_fds = tcp_socket;
    //struct timeval tv;

    /* Watch stdin (fd 0) to see when it has input. */

    FD_ZERO(&read_fds);
    FD_ZERO(&read_fds_master);

    FD_SET(0, &read_fds_master);
    FD_SET(udp_socket, &read_fds_master);
    FD_SET(tcp_socket, &read_fds_master);

    read_fds = read_fds_master;

    /* Wait up to five seconds. */

    //tv.tv_sec = 5;
    //tv.tv_usec = 0;
    while(1)
    {

        retval = select(highest_fds+1 , &read_fds, NULL, NULL, NULL);
        /* Don't rely on the value of tv now! */

        if (retval == -1)
        {
            perror("select()");
            return 1;
        }
        else if (retval)
        {
            
            if(FD_ISSET(0, &read_fds))
            {
                read(0, &stdin_buf, sizeof(stdin_buf));
                printf("%s", stdin_buf);
            }

            if(FD_ISSET(udp_socket, &read_fds))
            {
                udp_sock_len = sizeof(udp_client_addr);
                if(-1 == recvfrom(udp_socket, udp_buf, sizeof(udp_buf), 0, (struct sockaddr *)&udp_client_addr, &udp_sock_len))
                {
                    perror("recvfrom");
                    return -1;
                }    
                    
                printf("%s\n", udp_buf);
                printf("got udp message\n");
                if(-1 == sendto(udp_socket, "fischy", strlen("ficshy")+1, 0, (struct sockaddr *)&udp_client_addr, udp_sock_len))
                {
                    perror("sendto");
                    return 1;
                }

            }

            if(FD_ISSET(tcp_socket, &read_fds))
            {
                accept_sock_len = sizeof(tcp_client_addr);

                puts("got a tcp request");
                if(-1 == (accept_socket = accept(tcp_socket, (struct sockaddr *)&tcp_client_addr, &accept_sock_len)))
                {
                    perror("accept");
                    return 1;
                }
                highest_fds = accept_socket;
                FD_SET(accept_socket, &read_fds_master);
            }

            if(FD_ISSET(accept_socket, &read_fds))
            {
                int recv_status;
                if(-1 == (recv_status == recv(accept_socket, tcp_buf, sizeof(tcp_buf), 0 )))
                {
                    perror("recv");
                    return 0;
                }
                else if(0 == recv_status)
                {
                    close(accept_socket);
                    FD_CLR(accept_socket, &read_fds_master);
                }
                else
                {
                    printf("%s\n", tcp_buf);
                    puts("ccc");

                    if(-1 == send(accept_socket, "fischy", strlen("fischy")+1, 0))
                    {
                        perror("sendto");
                        return 1;
                    }
                }
            }


            read_fds = read_fds_master;
        }
        /* else
        {
            printf("No data within five seconds.\n");
        } */
    }

    return 0;
}

