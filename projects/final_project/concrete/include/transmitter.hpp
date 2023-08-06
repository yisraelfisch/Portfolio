#pragma once

#include <sys/socket.h>
#include <set>
#include <memory>

#include "nbd_comm.h"
#include "observer.hpp"

typedef struct msghdr msghdr_t;
typedef struct iovec iovec_t;

typedef struct AtlasHeader
{
    uint32_t    m_requestUid;
    uint32_t    m_fragment_index;
    uint32_t    m_alarmUid;
    uint32_t    m_iotOffset;// local iot offset of fragment
    uint32_t    m_type;
    uint32_t    m_len;
}AtlasHeader_t;

typedef struct msg_struct
{
    msghdr_t msghdr;
    AtlasHeader_t atlas_header;
    iovec_t iov[2];
    int iot_num;
    int iot_sock;
    int last_fragment_index;
    NbdRequest *nbd_req;

}msg_struct_t;

static int const FRAGMENT_SIZE = 1024;
static int const NUM_OF_IOT = 8;

namespace ilrd
{

int Read_all(int fd, char *buf, size_t count, int flag);

class Transmitter
{
public:
    Transmitter(NbdRequest *nbd_req);
    int SendMsgWrapper(std::shared_ptr<msg_struct_t> msg_struct);
    bool TransmitterReplay(int socket);
    static void Add(const Callback<msghdr_t>& callback); //AtlasHeader? not TaskInfo?
    static void Notify(msghdr_t msghdr);
private:
    NbdRequest *m_nbd_req;
    std::set<uint32_t> iot_set;
    static Dispatcher<msghdr_t>* m_dispatcher;
};

    class Command
    {
    public:
        virtual void SendToIot(std::shared_ptr<msg_struct_t> msg_struct) = 0;
    };//class Command

    class Read : public Command
    {
    public:
        virtual void SendToIot(std::shared_ptr<msg_struct_t> msg_struct);
        Read(int type = 0):m_type(type) {};
    private:
        int m_type;
    };//class Read

    class Write : public Command
    {
    public:
        virtual void SendToIot(std::shared_ptr<msg_struct_t> msg_struct);
        Write(int type = 1):m_type(type) {};
    private:
        int m_type;    
    };//class Write
} //namespace ilrd