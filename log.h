#ifndef __GDS_LOG_H__
#define __GDS_LOG_H__

#include <fstream>
#include <string>

namespace GDS
{
    class LogIO
    {
        std::ofstream m_Out;
        LogIO();
    public:
        static LogIO* getInstance();
        ~LogIO();
        
        void open(std::string name);
        bool write(std::string msg);
        void close();
    };
}

#endif
