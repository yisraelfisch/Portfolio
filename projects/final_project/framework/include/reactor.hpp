/*********************************
 * Reviewer: 
 * Author: Mike Meyers
 * File: reactor.hpp
 * ******************************/

#pragma once

#include "function.hpp"
#include "imonitor.hpp"
#include "select.hpp"
#include <unordered_map>

namespace ilrd
{

template<typename MONITOR> 
class Reactor
{
public:
  explicit Reactor();
    
  void RegisterReadHandler(int fd, const Function<int(void)>& func);
  void Run();
  //Void Stop();
  
  
private:
	std::unordered_map<int, Function<int(void)>> m_handlers;
  MONITOR m_monit;
};

template <typename MONITOR>
inline Reactor<MONITOR>::Reactor()
{
    static_cast<IMonitor*>(&m_monit);
}

template <typename MONITOR>
inline void Reactor<MONITOR>::RegisterReadHandler(int fd, const Function<int(void)>& func)
{
    m_monit.SetRead(fd);
    m_handlers[fd] = func;
}

template <typename MONITOR>
inline void Reactor<MONITOR>::Run()
{
    while(1)
    {
        int num_of_events = 0;
        if((num_of_events = m_monit.WaitForEvent()) == -1)
        {
            perror("WaitForEvent");
        }

        for(int i = 0; i < num_of_events; ++i)
        {
            m_handlers[m_monit.GetNextReadFd()]();
        }
    }
}

} // ilrd