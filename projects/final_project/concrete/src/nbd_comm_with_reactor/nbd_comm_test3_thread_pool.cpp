/*********************************
 * Reviewer: 
 * Author: yisrael.fisch
 * File: nbd_comm_test3.cpp
 * ******************************/

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include <cassert>

#include "thread_pool.hpp"
#include "singleton.hpp"
#include "function.hpp"
#include "reactor.hpp"
#include "select.hpp"
#include "nbd_comm.h"

using namespace ilrd;

typedef struct msghdr msghdr_t;
typedef struct iovec iovec_t; 

typedef struct AtlasHeader
{
    uint64_t    m_requestUid;
    uint32_t    m_alarmUid;
    uint32_t    m_iotOffset;
    uint32_t    m_type;
    uint32_t    m_len;
}AtlasHeader_t;

typedef struct msg_struct
{
    msghdr_t msghdr;
    AtlasHeader_t atlas_header;
    iovec_t iov[2];
    int iot_socket;
    int flag;
}msg_struct_t;

static int read_all(int fd, char *buf, size_t count);
int NbdHandler(int nbdSock);
int IotHandler(int iotsock);
int ConnectToIot();
int SendMsgWrapper(msg_struct_t *msg_struct);

int g_Iotsock = -1;
char* storage;

int main()
{
    static const int StorageSize = 0x100000;
    storage = new char[StorageSize];
    int nbdSock = NbdDevOpen("/dev/nbd0", StorageSize);
    g_Iotsock = ConnectToIot();
    ilrd::Reactor<ilrd::Select> reactor;

    reactor.RegisterReadHandler(nbdSock, ilrd::Function<int(void)>(NbdHandler, nbdSock));
    reactor.RegisterReadHandler(g_Iotsock, ilrd::Function<int(void)>(IotHandler, g_Iotsock));
    reactor.Run();
}

int NbdHandler(int nbdSock)
{

    Singleton<ThreadPool> thread_pool;
    msg_struct_t *msg_struct = new msg_struct_t;
    memset(msg_struct, 0, sizeof(msg_struct_t));
    NbdRequest* req = NbdRequestRead(nbdSock);

    msg_struct->atlas_header.m_requestUid = reinterpret_cast<uint64_t>(req);
    msg_struct->atlas_header.m_iotOffset = req->offset;
    msg_struct->atlas_header.m_type = req->reqType;
    msg_struct->atlas_header.m_len = req->dataLen;

    msg_struct->iov[0].iov_base = &msg_struct->atlas_header;
    msg_struct->iov[0].iov_len = sizeof(AtlasHeader_t);


    msg_struct->msghdr.msg_iov = msg_struct->iov;
    msg_struct->iot_socket = g_Iotsock;
    msg_struct->flag = 0;
    msg_struct->msghdr.msg_iovlen = 1;

    if(req->reqType == NBD_CMD_WRITE)
    {
    
        msg_struct->msghdr.msg_iov[1].iov_base = req->dataBuf;
        msg_struct->msghdr.msg_iov[1].iov_len = req->dataLen;
        msg_struct->msghdr.msg_iovlen = 2;

    }
    Function<int(void)> thread_func(&SendMsgWrapper, msg_struct);
    thread_pool->Async(thread_func);
    

    return 0;
}

int SendMsgWrapper(msg_struct_t* msg_struct)
{
    int result = 0;
    if(-1 == (result = sendmsg(msg_struct->iot_socket, &msg_struct->msghdr, msg_struct->flag)))
    {
        perror("sendmsg");
    }
    delete msg_struct;
    return result;
}

int IotHandler(int iotsock)
{
    NbdRequest* req = NULL;
    AtlasHeader_t Header ;
    read_all(iotsock, reinterpret_cast<char *> (&Header), sizeof(Header));
    req = reinterpret_cast<NbdRequest*> (Header.m_requestUid);

    if(Header.m_type == NBD_CMD_READ)
    {
        read_all(iotsock, req->dataBuf, req->dataLen);
    }

    NbdRequestDone(req, 0);
    return 0;
}

int ConnectToIot()
{
    const int PORT = 29000;
    int sock_fd = 0;
    struct sockaddr_in server_addr ;
    

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
    
    if(-1 == (sock_fd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        perror("socket");
        return 1;
    }

    if(-1 == connect(sock_fd, reinterpret_cast<struct sockaddr *>(&server_addr), sizeof(server_addr)))
    {
        perror("connect");
        return 1;
    }

    return sock_fd;

}

static int read_all(int fd, char *buf, size_t count)/*read from socket to buf*/
{
    int bytes_read;

    while (count > 0)
    {
        bytes_read = read(fd, buf, count);
        assert(bytes_read > 0);/*check if read didn't failed*/
        buf += bytes_read;
        count -= bytes_read;
    }
    assert(count == 0);/*double check for success*/

    return 0;
}

/*before exec:
a. sudo modprobe nbd

from another terminal:
iotServers.out tcp

from the main terminal:
run exec with sudo.

from another terminal:
b. sudo mkfs.ext4 /dev/nbd0
c. sudo mount /dev/nbd0 /mnt
d. sodu copy something to /mnt
e.sudo umount /dev/nbd0 /mnt
f.sudo mount /dev/nbd0 /mnt
see if it was copied

to close:
g.sudo umount /dev/nbd0 /mnt
h.sudo nbd-client -d /dev/nbd0*/