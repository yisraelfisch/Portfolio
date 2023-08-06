/*********************************
 * Reviewer: 
 * Author: yisrael.fisch
 * File: nbd_comm_test2.cpp
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

#include "function.hpp"
#include "reactor.hpp"
#include "select.hpp"
#include "nbd_comm.h"

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

static int read_all(int fd, char *buf, size_t count);
int Handler(int nbdSock);
int IotHandler(int iotsock);
int ConnectToIot();

int Iotsock = -1;
char* storage;

int main()
{
    static const int StorageSize = 0x100000;
    storage = new char[StorageSize];
    int nbdSock = NbdDevOpen("/dev/nbd0", StorageSize);
    Iotsock = ConnectToIot();
    ilrd::Reactor<ilrd::Select> reactor;

    reactor.RegisterReadHandler(nbdSock, ilrd::Function<int(void)>(Handler, nbdSock));
    reactor.RegisterReadHandler(Iotsock, ilrd::Function<int(void)>(IotHandler, Iotsock));
    reactor.Run();
}

int Handler(int nbdSock)
{
    msghdr_t msghdr;
    AtlasHeader_t Header ;
    NbdRequest* req = NbdRequestRead(nbdSock);
    iovec_t iov[2];

    Header.m_requestUid = reinterpret_cast<uint64_t>(req);
    Header.m_iotOffset = req->offset;
    Header.m_type = req->reqType;
    Header.m_len = req->dataLen;

    iov[0].iov_base = &Header;
    iov[0].iov_len = sizeof(Header);

    msghdr.msg_iov = iov;
    msghdr.msg_control = 1;

    switch (req->reqType)
    {
    case NBD_CMD_READ:
        if(-1 == sendmsg(Iotsock, &msghdr, 0))
        {
            perror("sendmsg");
            return 1;
        }

        break;

    case NBD_CMD_WRITE:
        iov[1].iov_base = req->dataBuf;
        iov[1].iov_len = req->dataLen;
        msghdr.msg_control = 2;
        if(-1 == sendmsg(Iotsock, &msghdr, 0))
        {
            perror("sendmsg");
            return 1;
        }

        break;

    default:
        break;
    }
    //NbdRequestDone(req, 0);

    return 0;
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