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

public://�̲߳���
    bool m_bRunThread;
    void StartThread(){ m_bRunThread = true; }
    void StopThread(){ m_bRunThread = false; }
    bool IsThreadRuning(){ return m_bRunThread == true; }
    virtual int run();
    HANDLE m_hThread;

public://�������
    std::list< Service* > m_listServers;//�����б�
    std::map< std::string, Service* > m_mapServiceCmd;//���������Ķ�Ӧ
    std::deque<SERVICE_CMD_SP > m_dequeCmd;//Ҫ���������

    int DispatchCommand();//�ַ�����
    int AddServiceToKernel(Service* server);//��ӷ���m_listServers
    int SendServiceCMD(SERVICE_CMD_SP server);//
    Service* FindServiceByCmd(std::string sCMD);
    int BindServiceCmdToKernel(Service* pService);//m_mapServiceCmd

};

