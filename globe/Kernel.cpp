#include "Kernel.h"

unsigned __stdcall ThreadFun(void *pParam)
{
    Kernel *pKernel = (Kernel*)pParam;
    while (pKernel->m_bRunThread)
    {
        pKernel->run();
    }

    return 0;
}

Kernel::Kernel(void)
{
    m_bRunThread = true;
    m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadFun, this, 0, nullptr);
}


Kernel::~Kernel(void)
{
    StopThread();
}

int Kernel::InitKernel()
{
    OnInitKernel();

    auto it = m_listServers.begin();
    for (; it != m_listServers.end(); ++it)
    {
        (*it)->InitService();
        BindServiceCmdToKernel(*it);
    }

    return 0;
}

int Kernel::OnInitKernel()
{
    return 0;
}

int Kernel::IntoKernelConsole()
{
    OnKernelConsole();

    return 0;
}

int Kernel::run()
{
    int nWaitTime = KERNEL_WAIT_TIME;
    m_nKernelThreadID = GetCurrentThreadId();

    while (m_bRunThread)
    {
        DispatchCommand();
        Sleep(nWaitTime);
    }

    return 0;
}

/////////////////
int Kernel::AddServiceToKernel(Service* pService)
{
    Service* pTemp = pService;
    m_listServers.push_back(pTemp);
    pService->BindToKernel(this);
    return 0;
}

int Kernel::DispatchCommand()
{
    SERVICE_CMD_SP pTempCMD;
    while (!m_dequeCmd.empty())
    {
        pTempCMD = m_dequeCmd.front();
        m_dequeCmd.pop_front();
        //SendServiceCMD(pTempCMD);
    }
    return 0;
}

int Kernel::SendServiceCMD(SERVICE_CMD_SP serverCmd)
{
    if (!serverCmd)
    {
        return -1;
    }

    Service *service = FindServiceByCmd(serverCmd->GetName());
    
    return service->Invoke(serverCmd);
}

int Kernel::BindServiceCmdToKernel(Service* pService)
{
    using ServiceCMDPair = std::pair< std::string, Service*>;
    std::pair< std::map<std::string, Service*>::iterator, bool > pr;
    auto it = pService->m_listCMD.begin();

    for (; it != pService->m_listCMD.end(); it++)
    {
        pr = m_mapServiceCmd.insert(ServiceCMDPair(*it,pService));
        if (!pr.second)
        {
            printf("BindServiceCmdToKernel fail! cmd[%s]\r\n",it->c_str());
        }
        else
        {
            printf("BindServiceCmdToKernel ok! cmd[%s]\r\n", it->c_str());
        }
    }

    return 0;
}

Service* Kernel::FindServiceByCmd(std::string sCMD)
{
    std::map< std::string, Service* >::iterator it = m_mapServiceCmd.find(sCMD);
    if (it != m_mapServiceCmd.end())
    {
        return it->second;
    }
    return nullptr;
}

int Kernel::OnKernelConsole()
{
    return 0;
}
