#include <cstring>
#include <cassert>

#include "transmitter.hpp"
#include "singleton.hpp"
#include "factory.hpp"

namespace ilrd
{
int Read_all(int fd, char *buf, size_t count, int flag);

Transmitter::Transmitter(NbdRequest *nbd_req):m_nbd_req(nbd_req)
{
}

int Transmitter::SendMsgWrapper(std::shared_ptr<msg_struct_t> msg_struct)
{
        Singleton<Factory<Command, int, int > > factory;
        std::shared_ptr<Command> command = factory->Create(msg_struct->nbd_req->reqType, msg_struct->nbd_req->reqType);
        std::cout << "SendMsgWrapper" << std::endl;
        for(int i = msg_struct->atlas_header.m_fragment_index; i < msg_struct->last_fragment_index; i += NUM_OF_IOT)
        {
            iot_set.insert(i);
        }

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

bool Transmitter::TransmitterReplay(int socket)
{
    AtlasHeader_t atlas_header;
    int frag_local_idx = 0;
    
    Read_all(socket, reinterpret_cast<char *>(&atlas_header), sizeof(AtlasHeader_t), 0);


    if(atlas_header.m_type == NBD_CMD_READ)
    {
        frag_local_idx = atlas_header.m_fragment_index - (m_nbd_req->offset / FRAGMENT_SIZE);
        Read_all(socket, m_nbd_req->dataBuf + (frag_local_idx * FRAGMENT_SIZE), FRAGMENT_SIZE, 0);
    }
    std::cout << atlas_header.m_fragment_index << std::endl;
    
    iot_set.erase(atlas_header.m_fragment_index);

    return iot_set.empty();
}

void Transmitter::Add(const Callback<msghdr_t> &callback)
{
    m_dispatcher->Add(callback);
}

Dispatcher<msghdr_t>* Transmitter::m_dispatcher(new Dispatcher<msghdr_t>);

void Transmitter::Notify(msghdr_t msghdr)
{
    m_dispatcher->Notify(msghdr);
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
        Transmitter::Notify(msg_struct->msghdr);
        std::cout << "after notify" << std::endl;
        if(-1 == sendmsg(msg_struct->iot_sock, &msg_struct->msghdr, 0))
        {
            perror("sendmsg");
        }
}
}