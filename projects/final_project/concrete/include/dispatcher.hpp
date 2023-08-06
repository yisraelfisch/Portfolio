#pragma once

#include <unordered_map> // std::unordered_map
#include <memory> // std::memory
#include <set> // std::set
#include "nbd_comm.h"
#include "request_host.hpp"


typedef struct msghdr msghdr_t;
typedef struct iovec iovec_t; 

/* typedef struct AtlasHeader
{
    uint32_t    m_requestUid;
    uint32_t    m_fragment_index;
    uint32_t    m_alarmUid;
    uint32_t    m_iotOffset;// local iot offset of fragment
    uint32_t    m_type;
    uint32_t    m_len;
}AtlasHeader_t; */


namespace ilrd
{
    class RequestDispatcher
    {
    public:
        int NbdHandler(int *sock_fd);
        int IotHandler(int socket);
    private:
        std::unordered_map< uint32_t, std::shared_ptr<RequestHost> > m_activeRequests;
    };//class RequestDispatcher

}




/* FragmentLength = 1024
NumFragments = RequestLength / FragmentLength

FragmentGlobalOffset = RequestOffset + FragmentIndex * FragmentLength
FragmentGlobalIndex = FragmentGlobalOffset / FragmentLength
FragmentIot = FragmentGlobalIndex % NumIots
FragmentIotOffset = FragmentGlobalIndex / NumIots * FragmentLength */