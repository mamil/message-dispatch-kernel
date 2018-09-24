#include "ServiceGold.h"


ServiceGold::ServiceGold()
{
    
}


ServiceGold::~ServiceGold()
{
    m_mapServiceFunc.clear();
}

int ServiceGold::InitService()
{
    auto pGold = SHARED_PTR(ServiceCmdGold);
    AddCmdFunc(pGold, &ServiceGold::DealGold);
    auto pBlackGold = SHARED_PTR(ServiceCmdBlackGold);
    AddCmdFunc(pBlackGold, &ServiceGold::DealBlackGold);

    return 0;
}

void ServiceGold::DealGold(SERVICE_CMD_SP pCmd)
{
    printf("This is Gold~~[%s]\r\n",pCmd->m_strSelf.c_str());
}

void ServiceGold::DealBlackGold(SERVICE_CMD_SP pCmd)
{
    printf("This is BlackGold~~[%s] [%s]\r\n", pCmd->m_strSelf.c_str(),pCmd->GetName().c_str());
}

//////////////////////////same in service
int ServiceGold::Invoke(SERVICE_CMD_SP pCmd)
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
void ServiceGold::AddCmdFunc(SERVICE_CMD_SP pCmd, ServiceFunc Func)
{
    SERVIC_CMD_FUNC Cmd_Func;
    //Cmd_Func.m_pCmd = pCmd;
    Cmd_Func.m_pFunc = Func;

    pr = m_mapServiceFunc.insert(SERVICE_FUNC_PAIR(pCmd->GetName(), Cmd_Func));
    if ( pr.second)
    {
        printf("AddCmdFunc [%s] ok~~\r\n", pCmd->GetName().c_str());
    }
    else
    {
        printf("AddCmdFunc [%s] fail~~\r\n", pCmd->GetName().c_str());
    }
    AddFunc(pCmd->GetName());
}

//////////////////////////same in service
