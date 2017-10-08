#pragma once
#include "GeneralMacro.h"

#include "../service/Service.h"
#include"../command/ServiceCommand.h"
#include"ExceptionBase.h"

class Service;
//class ServiceCommand;

class Kernel
{
public:
    Kernel(void);
    virtual ~Kernel(void);

    int InitKernel();

    DWORD m_nKernelThreadID;

    int IntoKernelConsole();
protected:
    virtual int OnKernelConsole();

public:
    virtual int OnInitKernel();

public://线程部分
    bool m_bRunThread;
    void StartThread(){ m_bRunThread = true; }
    void StopThread(){ m_bRunThread = false; }
    bool IsThreadRuning(){ return m_bRunThread == true; }
    virtual int run();
    HANDLE m_hThread;

public://任务分派
    std::list< Service* > m_listServers;//服务列表
    std::map< std::string, Service* > m_mapServiceCmd;//命令与服务的对应
    std::deque<SERVICE_CMD_SP > m_dequeCmd;//要处理的命令

    int DispatchCommand();//分发任务
    int AddServiceToKernel(Service* server);//添加服务m_listServers
    int SendServiceCMD(SERVICE_CMD_SP server);//
    Service* FindServiceByCmd(std::string sCMD);
    int BindServiceCmdToKernel(Service* pService);//m_mapServiceCmd

};

