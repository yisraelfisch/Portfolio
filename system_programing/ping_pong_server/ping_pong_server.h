#ifndef __PING_PONG_SERVER_H__
#define __PING_PONG_SERVER_H__

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> 

int CreateSocketServer(int port, int type);
/*
create a new socket for server
parameters: port number end socket type(SOCK_DGRAM or SOCK_STREAM)
*/
int CreateSocketClient(int port, unsigned int address, int type);
/*
create a new sockett for client
parameters: port number, server ip end socket type(SOCK_DGRAM or SOCK_STREAM)
*/

#endif /* __PING_PONG_SERVER__*/