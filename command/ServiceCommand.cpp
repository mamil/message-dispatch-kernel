#include"ServiceCommand.h"

ServiceCommand::ServiceCommand()
{
    m_dwCreateTime = GetTickCount64();
    m_strSelf = initName(this);
}

void ServiceCommand::ShowMe()
{
    printf("ServiceCommand CreateTime[%lld] self[%#x]\r\n", m_dwCreateTime,this);
}