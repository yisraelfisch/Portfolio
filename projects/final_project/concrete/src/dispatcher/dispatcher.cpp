#include "dispatcher.hpp"
#include "transmitter.hpp"
#include <iostream>

namespace ilrd
{

    int RequestDispatcher::NbdHandler(int *sock_fd)
    {
        Singleton<Factory<Command, int, int > > factory;
        factory->Add<Read>(NBD_CMD_READ);
        factory->Add<Write>(NBD_CMD_WRITE);
        std::shared_ptr<RequestHost> req_host_ptr = NULL;
        req_host_ptr = RequestHost::Create(sock_fd);
        std::cout<< "NbdHandler" << std::endl;
        m_activeRequests.insert({req_host_ptr->getRequestUid(), req_host_ptr});

        return 0;
    }

    int RequestDispatcher::IotHandler(int socket)
    {   
        bool is_req_done = false;
        int uid_req = 0;
        //call a static function that knowes the requrst uid
        uid_req = RequestHost::UID_Peek(socket);
        //handle replay
        std::cout<< uid_req << std::endl; 
        is_req_done = m_activeRequests.at(uid_req)->IotReplay(socket);
        std::cout<< "IotHandler after" << std::endl; 
        //get a massage that all fragment were sent(the host job)
        //send reply to  nbd(the host job)
        //erase the request from the map
        if(is_req_done == true)
        {
            m_activeRequests.erase(uid_req);
        }

        return 0;
    }
}

