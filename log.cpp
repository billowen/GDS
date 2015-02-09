#include <iostream>
#include "log.h"

namespace GDS
{
    LogIO* LogIO::getInstance()
    {
        static LogIO m_Instance;
        return &m_Instance;
    }

    LogIO::~LogIO()
    {
        if (m_Out.is_open())
            m_Out.close();
    }

    void LogIO::open(std::string name)
    {
        m_Out.open(name.c_str());
    }

    bool LogIO::write(std::string msg)
    {
        if (m_Out.is_open())
        {
            m_Out << msg;
            return true;
        }
        else
        {
            return false;
        }
    }

    void LogIO::close()
    {
        if (m_Out.is_open())
        {
            m_Out.close();
        }
    }
}
