#include "request_host.hpp"
#include <iostream>

namespace ilrd
{

    std::shared_ptr<RequestHost> RequestHost::Create(int *sock_fd)
    {
        RequestHost *host_ptr = new RequestHost;
        static uint32_t requestUid = 0;
        ++requestUid;
        host_ptr->m_requestUid = requestUid;
        host_ptr->nbd_sock = sock_fd[0];
        //host_ptr->Slice(sock_fd);
        host_ptr->SendTasks(sock_fd);
        return std::shared_ptr<RequestHost> (host_ptr) ;
        
    }

/*     void RequestHost::Slice(int *sock_fd)
    {
        nbd_req = NbdRequestRead(sock_fd[0]);
        num_of_fragments = nbd_req->dataLen / FRAGMENT_SIZE;
    } */

    uint32_t RequestHost::getRequestUid()
    {
        return m_requestUid;
    }

    void RequestHost::SendTasks(int *sock_fd)
    {
        nbd_req = NbdRequestRead(sock_fd[0]);
        num_of_fragments = nbd_req->dataLen / FRAGMENT_SIZE;
        Singleton<ThreadPool> thread_pool;
        //std::shared_ptr<msg_struct_t> msg_struct(new msg_struct_t);
        //msg_struct_t msg_struct;
        //memset(&msg_struct, 0, sizeof(msg_struct_t));
        
        
        int first_fragment_index = nbd_req->offset / FRAGMENT_SIZE;
        int first_iot = first_fragment_index % NUM_OF_IOT;
        int last_fragment_index = first_fragment_index + num_of_fragments;

/*      msg_struct->nbd_req = nbd_req;
        msg_struct->atlas_header.m_requestUid = m_requestUid;
        msg_struct->atlas_header.m_len = FRAGMENT_SIZE;
        msg_struct->atlas_header.m_type = nbd_req->reqType;
        msg_struct->last_fragment_index = last_fragment_index; */
        
        for(int i = 0; i < NUM_OF_IOT && i < GetNumOfFragments(); ++i, ++first_fragment_index, (++first_iot) %= NUM_OF_IOT)
        {
            std::shared_ptr<msg_struct_t> msg_struct(new msg_struct_t);

            msg_struct->nbd_req = nbd_req;
            msg_struct->atlas_header.m_requestUid = m_requestUid;
            msg_struct->atlas_header.m_len = FRAGMENT_SIZE;
            msg_struct->atlas_header.m_type = nbd_req->reqType;
            msg_struct->last_fragment_index = last_fragment_index;
            
            msg_struct->iot_num = first_iot;
            msg_struct->iot_sock = sock_fd[first_iot+1];
            msg_struct->atlas_header.m_fragment_index = first_fragment_index;
            msg_struct->atlas_header.m_iotOffset = first_fragment_index/NUM_OF_IOT * FRAGMENT_SIZE;
            
            std::shared_ptr<Transmitter> transmitter(new Transmitter(nbd_req));
            trans_map.insert({first_iot, transmitter});

            Function<int(void)> thread_func(&Transmitter::SendMsgWrapper, transmitter.get(), msg_struct);
            thread_pool->Async(thread_func);
        }

    }


    int RequestHost::GetNumOfFragments()
    {
        return num_of_fragments;
    }

    int RequestHost::UID_Peek(int socket)
    {
        int req_uid = 0;
        Read_all(socket, reinterpret_cast<char *> (&req_uid), sizeof(int), MSG_PEEK);
        std::cout << "UID_Peek" << std::endl;
        std::cout << req_uid << std::endl;
        return req_uid;
    }

    bool RequestHost::IotReplay(int socket)
    {
        AtlasHeader_t atlas_header;
        int iot_num = 0;
        Read_all(socket, reinterpret_cast<char *>(&atlas_header), sizeof(AtlasHeader_t), MSG_PEEK);

        iot_num = atlas_header.m_fragment_index % NUM_OF_IOT;

        if(trans_map[iot_num]->TransmitterReplay(socket))
        {
            trans_map.erase(iot_num);
        }
        
        if(IsRequestDone())
        {
            NbdRequestDone(nbd_req, 0);
            std::cout << "Request Done" << std::endl;
            return true;
        }
        std::cout << "Request not Done" << std::endl;

        return false;
    }

    bool RequestHost::IsRequestDone()
    {
        return trans_map.empty();
    }

}

/* FragmentLength = 1024
NumFragments = RequestLength / FragmentLength

FragmentGlobalOffset = RequestOffset + FragmentIndex * FragmentLength
FragmentGlobalIndex = FragmentGlobalOffset / FragmentLength
FragmentIot = FragmentGlobalIndex % NumIots
FragmentIotOffset = FragmentGlobalIndex / NumIots * FragmentLength */