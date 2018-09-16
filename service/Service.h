#pragma once
//#include "Kernel.h"
#include "../globe/GeneralMacro.h"
#include "../command/ServiceCommand.h"


class Kernel;
//class ServiceCommand;

using SERVICE_CMD_SP = std::shared_ptr< ServiceCommand >;
using SERVICE_CMD_P = ServiceCommand * ;

class Service
{
public:
    Service(void);
    virtual ~Service(void);

    virtual int Invoke(SERVICE_CMD_SP pCmd) = 0;
    virtual int InitService() = 0;
private:
    friend class Kernel;
    Kernel* m_pKernel;
    void BindToKernel(Kernel* kernel);

public://func
    std::list<std::string> m_listCMD;
    void AddFunc(std::string sCMD);

    ULONGLONG m_dwCreateTime;
    void sayMyself();
};

/*/////////////Same in Service
public:
    typedef void (ServiceGold::*ServiceFunc)(SERVICE_CMD pCmd);
    typedef struct SERVIC_CMD_FUNC
    {
        SERVICE_CMD m_pCmd;
        ServiceFunc m_pFunc;
    };
    typedef std::map<std::string, SERVIC_CMD_FUNC > SERVICE_FUNC_MAP;
    typedef std::pair<std::string, SERVIC_CMD_FUNC > SERVICE_FUNC_PAIR;
    std::pair<std::map<std::string, SERVIC_CMD_FUNC>::iterator, bool> pr;

protected:
    virtual int Invoke(SERVICE_CMD pCmd);
    virtual int InitService();
    virtual void AddCmdFunc(SERVICE_CMD pCmd, ServiceFunc Func);

private:
    SERVICE_FUNC_MAP m_mapServiceFunc;
    /////////////Same in Service*/
