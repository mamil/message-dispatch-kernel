#include"ServiceCommand.h"

ServiceCommand::ServiceCommand()
{
    #ifdef WIN32
    m_dwCreateTime = GetTickCount64();
    #endif // WIN32
    #if defined(__linux__) || defined(__linux)
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    m_dwCreateTime = (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
    #endif // linux

    m_strSelf = initName(this);
}

void ServiceCommand::ShowMe()
{
    printf("ServiceCommand CreateTime[%lld] self[%#x]\r\n", m_dwCreateTime,this);
}