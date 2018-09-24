#include "Service.h"


Service::Service(void)
{
    m_dwCreateTime = GetTickCount64();
}


Service::~Service(void)
{
    m_listCMD.clear();
}

int Service::InitService()
{

    return 0;
}

void Service::BindToKernel(Kernel* kernel)
{
    m_pKernel = kernel;
}

void Service::AddFunc(std::string sCMD)
{
    m_listCMD.push_back(sCMD);
}

void Service::sayMyself()
{
    printf("Service : %lld\r\n",m_dwCreateTime);
}

/*//////////////////////////same in service
int ServiceGold::Invoke(SERVICE_CMD pCmd)
{
    auto it = m_mapServiceFunc.find(pCmd->GetName());
    if (it != m_mapServiceFunc.end())
    {
        (this->*(it->second.m_pFunc))(pCmd);
        //printf("Invoke [%s] ok!!\r\n", pCmd->GetPoint().c_str());

        return 0;
    }
    else
    {
        printf("Invoke [%s] fail!!\r\n", pCmd->GetName().c_str());
    }
    return 0;
}
void ServiceGold::AddCmdFunc(SERVICE_CMD pCmd, ServiceFunc Func)
{
    SERVIC_CMD_FUNC Cmd_Func;
    Cmd_Func.m_pCmd = pCmd;
    Cmd_Func.m_pFunc = Func;

    pr = m_mapServiceFunc.insert(SERVICE_FUNC_PAIR(Cmd_Func.m_pCmd->GetName(), Cmd_Func));
    if (pr.second)
    {
        printf("AddCmdFunc [%s] ok~~\r\n", Cmd_Func.m_pCmd->GetName().c_str());
    }
    else
    {
        printf("AddCmdFunc [%s] fail~~\r\n", Cmd_Func.m_pCmd->GetName().c_str());
    }
    AddFunc(Cmd_Func.m_pCmd->GetName());
}

//////////////////////////same in service*/