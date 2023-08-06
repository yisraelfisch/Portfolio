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
        host_ptr->Slice(sock_fd);
        host_ptr->SendTasks(sock_fd);
        return std::shared_ptr<RequestHost> (host_ptr) ;
        
    }

    void RequestHost::Slice(int *sock_fd)
    {
        nbd_req = NbdRequestRead(sock_fd[0]);
        num_of_fragments = nbd_req->dataLen / FRAGMENT_SIZE;
        for(int i = 0; i < num_of_fragments; ++i)
        {
            fragment_set.insert(i);
        }
    }

    uint32_t RequestHost::getRequestUid()
    {
        return m_requestUid;
    }

    void RequestHost::SendTasks(int *sock_fd)
    {
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
            
            Function<int(void)> thread_func(&RequestHost::SendMsgWrapper, this, msg_struct);
            thread_pool->Async(thread_func);
        }

    }

    int RequestHost::SendMsgWrapper(std::shared_ptr<msg_struct_t> msg_struct)
    {
        Singleton<Factory<Command, int, int > > factory;
        std::shared_ptr<Command> command = factory->Create(nbd_req->reqType, nbd_req->reqType);
        std::cout << "SendMsgWrapper" << std::endl;
        for(int i = msg_struct->atlas_header.m_fragment_index; i < msg_struct->last_fragment_index; i += NUM_OF_IOT)
        {
            memset(&msg_struct->msghdr, 0, sizeof(msg_struct->msghdr));
            //uint32_t local_offset = msg_struct->atlas_header.m_iotOffset;

            msg_struct->atlas_header.m_fragment_index = i;
            msg_struct->atlas_header.m_iotOffset += FRAGMENT_SIZE;
            msg_struct->iov[0].iov_base = &msg_struct->atlas_header;
            msg_struct->iov[0].iov_len = sizeof(AtlasHeader_t);
            msg_struct->msghdr.msg_iov = msg_struct->iov;
            msg_struct->msghdr.msg_iovlen = 1;
            
            std::cout << msg_struct->atlas_header.m_requestUid << std::endl;
            std::cout << msg_struct->atlas_header.m_type << std::endl;
            
            
            command->SendToIot(msg_struct);
            /* if(nbd_req->reqType == NBD_CMD_WRITE)
            {
                msg_struct->iov[1].iov_base = nbd_req->dataBuf + (msg_struct->atlas_header.m_fragment_index - (nbd_req->offset / FRAGMENT_SIZE)) * FRAGMENT_SIZE;
                msg_struct->iov[1].iov_len = FRAGMENT_SIZE;
                msg_struct->msghdr.msg_iovlen = 2;
            } */

            //msghdr->msg_iov = iov;

           /*  if(-1 == sendmsg(msg_struct->iot_sock, &msg_struct->msghdr, 0))
            {
                perror("sendmsg");
            } */

            //local_offset += FRAGMENT_SIZE; 

        }
        return 1;
    
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
        int frag_local_idx = 0;
        Read_all(socket, reinterpret_cast<char *>(&atlas_header), sizeof(AtlasHeader_t), 0);

        frag_local_idx = atlas_header.m_fragment_index - (nbd_req->offset / FRAGMENT_SIZE);

        if(atlas_header.m_type == NBD_CMD_READ)
        {
            Read_all(socket, nbd_req->dataBuf + (frag_local_idx * FRAGMENT_SIZE), FRAGMENT_SIZE, 0);
        }
        std::cout << atlas_header.m_fragment_index << std::endl;
        EraseFragment(frag_local_idx);
        
        if(IsRequestDone())
        {
            NbdRequestDone(nbd_req, 0);
            std::cout << "Request Done" << std::endl;
            return true;
        }
        std::cout << "Request not Done" << std::endl;

        return false;
    }

    void RequestHost::EraseFragment(int frag_local_idx)
    {
        fragment_set.erase(frag_local_idx);
    }

    bool RequestHost::IsRequestDone()
    {
        return fragment_set.empty();
    }

    int Read_all(int fd, char *buf, size_t count, int flag)/*read from socket to buf*/
    {
        int bytes_read;

        while (count > 0)
        {
            bytes_read = recv(fd, buf, count, flag);
            assert(bytes_read > 0);/*check if read didn't failed*/
            buf += bytes_read;
            count -= bytes_read;
        }
        assert(count == 0);/*double check for success*/

        return 0;
    }
    //---------------------------- class Read func -----------------------//
    void Read::SendToIot(std::shared_ptr<msg_struct_t> msg_struct)
    {
            std::cout << "read command" << std::endl;
            if(-1 == sendmsg(msg_struct->iot_sock, &msg_struct->msghdr, 0))
            {
                perror("sendmsg");
            }
    }
    //---------------------------- class Write func -----------------------//
    void Write::SendToIot(std::shared_ptr<msg_struct_t> msg_struct)
    {
            std::cout << "write command" << std::endl;
            msg_struct->msghdr.msg_iov[1].iov_base = msg_struct->nbd_req->dataBuf + (msg_struct->atlas_header.m_fragment_index - (msg_struct->nbd_req->offset / FRAGMENT_SIZE)) * FRAGMENT_SIZE;
            msg_struct->msghdr.msg_iov[1].iov_len = FRAGMENT_SIZE;
            msg_struct->msghdr.msg_iovlen = 2;
            
            if(-1 == sendmsg(msg_struct->iot_sock, &msg_struct->msghdr, 0))
            {
                perror("sendmsg");
            }
    }
}

/* FragmentLength = 1024
NumFragments = RequestLength / FragmentLength

FragmentGlobalOffset = RequestOffset + FragmentIndex * FragmentLength
FragmentGlobalIndex = FragmentGlobalOffset / FragmentLength
FragmentIot = FragmentGlobalIndex % NumIots
FragmentIotOffset = FragmentGlobalIndex / NumIots * FragmentLength */