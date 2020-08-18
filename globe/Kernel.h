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

    #ifdef WIN32
    DWORD m_nKernelThreadID;
    #endif // WIN32
    #if defined(__linux__) || defined(__linux)
    int m_nKernelThreadID;
    #endif // linux

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
    std::thread m_hThread;

public://任务分派
    std::list< std::shared_ptr<Service> > m_listServers;//服务列表
    std::map< std::string, std::shared_ptr<Service> > m_mapServiceCmd;//命令与服务的对应
    std::deque<SERVICE_CMD_SP > m_dequeCmd;//要处理的命令

    int DispatchCommand();//分发任务
    int AddServiceToKernel(std::shared_ptr<Service> server);//添加服务m_listServers
    int SendServiceCMD(SERVICE_CMD_SP server);//
    std::shared_ptr<Service> FindServiceByCmd(std::string sCMD);
    int BindServiceCmdToKernel(std::shared_ptr<Service> pService);//m_mapServiceCmd

};

