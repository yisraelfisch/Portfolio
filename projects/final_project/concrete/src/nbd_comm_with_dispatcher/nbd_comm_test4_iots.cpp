/*********************************
 * Reviewer: 
 * Author: yisrael.fisch
 * File: nbd_comm_test4.cpp
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
#include "dispatcher.hpp"
namespace ilrd
{

class Subscriber
{
public:
    virtual void OnUpdate(msghdr_t msghdr) = 0;
};

class Subone : public Subscriber
{
public:
    Subone():m_callback(Callback<msghdr_t>(Function<void(msghdr_t)>(&Subone::OnUpdate, this)))
    {}

    virtual void OnUpdate(msghdr_t msghdr)
    {
        std::cout << "got notification:\n" << msghdr.msg_iovlen << std::endl;
    }
    const Callback<msghdr_t>& GetCallback();

private:
    const Callback<msghdr_t> m_callback;

};

const Callback<msghdr_t> &Subone::GetCallback()
{
    return m_callback;
}
}
using namespace ilrd;

/* typedef struct msghdr msghdr_t;
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

static int read_all(int fd, char *buf, size_t count);*/
int ConnectToIot(int iot_num);



char* storage;

int main()
{
    
    static const int StorageSize = 0x1000000;
    storage = new char[StorageSize];
    
    int sock_fd[NUM_OF_IOT + 1];
    

    RequestDispatcher req_dispatcher;
    
    sock_fd[0] = NbdDevOpen("/dev/nbd0", StorageSize);
    for(int i = 0; i < NUM_OF_IOT; ++i)
    {
        sock_fd[i+1] = ConnectToIot(i);
    }
    
    ilrd::Reactor<ilrd::Select> reactor;
    
    reactor.RegisterReadHandler(sock_fd[0], ilrd::Function<int(void)>(&RequestDispatcher::NbdHandler, &req_dispatcher, sock_fd));
    
    for(int i = 0; i < NUM_OF_IOT; ++i)
    {
        reactor.RegisterReadHandler(sock_fd[i+1], ilrd::Function<int(void)>(&RequestDispatcher::IotHandler,&req_dispatcher, sock_fd[i+1]));
    }
    printf("check 1\n");
    Subone sub1;
    Transmitter::Add(sub1.GetCallback());
    reactor.Run();
}



int ConnectToIot(int iot_num)
{
    const int PORT = 29000 + iot_num;
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

/*read from socket to buf*/
/*check if read didn't failed*/
/*double check for success*/
/* static int read_all(int fd, char *buf, size_t count)
{
    int bytes_read;

    while (count > 0)
    {
        bytes_read = read(fd, buf, count);
        assert(bytes_read > 0);
        buf += bytes_read;
        count -= bytes_read;
    }
    assert(count == 0);

    return 0;
} 
 */
/*before exec:
a. sudo modprobe nbd

from another terminal:
iotServers.out 1

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