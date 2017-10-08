#pragma once
#include "Service.h"

#include "../command/ServiceCmdGold.h"
#include "../command/ServiceCmdBlackGold.h"

class ServiceGold :
    public Service
{
public:
    ServiceGold();
    virtual ~ServiceGold();

    void DealGold(SERVICE_CMD_SP pCmd);
    void DealBlackGold(SERVICE_CMD_SP pCmd);

    /////////////Same in Service
public:
    typedef void (ServiceGold::*ServiceFunc)(SERVICE_CMD_SP pCmd);
    typedef struct SERVIC_CMD_FUNC
    {
        SERVICE_CMD_P m_pCmd;
        ServiceFunc m_pFunc;
    };
    using SERVICE_FUNC_MAP = std::map<std::string, SERVIC_CMD_FUNC >;
    using SERVICE_FUNC_PAIR = std::pair<std::string, SERVIC_CMD_FUNC >;
    std::pair<std::map<std::string, SERVIC_CMD_FUNC>::iterator, bool> pr;

protected:
    virtual int Invoke(SERVICE_CMD_SP pCmd);
    virtual int InitService();
    virtual void AddCmdFunc(SERVICE_CMD_P pCmd, ServiceFunc Func);

private:
    SERVICE_FUNC_MAP m_mapServiceFunc;
    /////////////Same in Service
};

