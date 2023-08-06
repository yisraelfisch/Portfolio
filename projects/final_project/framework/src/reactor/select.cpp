#include "imonitor.hpp"
#include "select.hpp"
#include "cstddef"

namespace ilrd
{
    Select::Select() : m_fd_max(0)
    {
        FD_ZERO(&m_read_set);
        FD_ZERO(&m_master);
    }

    int Select::WaitForEvent()
    {
        m_read_set = m_master;

        return select(m_fd_max + 1, &m_read_set, NULL, NULL, NULL);
    }

    int Select::GetNextReadFd()
    {
        int i = 0;
        for(i = 0; i <= (m_fd_max + 1) && !FD_ISSET(i, &m_read_set); ++i);

        if(i == (m_fd_max + 1))
        {
            return -1;
        }

        FD_CLR(i, &m_read_set);
        return i;
    }

    void Select::SetRead(int fd)
    {
        FD_SET(fd, &m_master);

        if(fd > m_fd_max)
        {
            m_fd_max = fd;
        }
    }

    void Select::ClearRead(int fd)
    {
        FD_CLR(fd, &m_master);
    }
}