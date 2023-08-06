#pragma once

#include <unordered_map> // std::unordered_map
#include <memory> // std::memory
#include <set> // std::set
#include <sys/socket.h>
#include <cstring>
#include <cassert>

#include "factory.hpp"
#include "thread_pool.hpp"
#include "singleton.hpp"
#include "function.hpp"
#include "reactor.hpp"
#include "select.hpp"
#include "nbd_comm.h"


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

    class RequestHost
    {
    public:
        friend class RequestDispatcher;

        static std::shared_ptr<RequestHost> Create(int *sock_fd);
        void Slice(int *sock_fd);
        uint32_t getRequestUid();
        void SendTasks(int *sock_fd);
        int SendMsgWrapper(std::shared_ptr<msg_struct_t> msg_struct);
        int GetNumOfFragments();
        static int UID_Peek(int socket);
        bool IotReplay(int socket);
        void EraseFragment(int frag_local_idx);
        bool IsRequestDone();
        //NbdRequest *getRequest();
        
    private:
        RequestHost(){};
        NbdRequest *nbd_req;
        std::set<int> fragment_set;
        int num_of_fragments;
        int nbd_sock;
        uint32_t m_requestUid;
       
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

}