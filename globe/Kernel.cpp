#include "Kernel.h"

void ThreadFun(void *pParam)
{
    Kernel *pKernel = (Kernel*)pParam;
    while (pKernel->m_bRunThread)
    {
        pKernel->run();
    }

    return;
}

Kernel::Kernel(void)
{
    m_bRunThread = true;
    m_hThread = std::thread(ThreadFun, this);
    m_hThread.detach();
}

Kernel::~Kernel(void)
{
    StopThread();
    m_dequeCmd.clear();
    m_listServers.clear();
    m_mapServiceCmd.clear();
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
    #ifdef WIN32
    m_nKernelThreadID = GetCurrentThreadId();
    #endif // WIN32
    #if defined(__linux__) || defined(__linux)
    m_nKernelThreadID = CurrentThread::gettid();
    #endif // linux

    while (m_bRunThread)
    {
        DispatchCommand();
        #ifdef WIN32
        Sleep(nWaitTime);
        #endif // WIN32
        #if defined(__linux__) || defined(__linux)
        usleep(nWaitTime);
        #endif // linux
    }

    return 0;
}

/////////////////
int Kernel::AddServiceToKernel(std::shared_ptr<Service> pService)
{
    auto pTemp = pService;
    m_listServers.push_back(pTemp);
    pService->BindToKernel(this);
    return 0;
}

int Kernel::DispatchCommand()
{
    while (!m_dequeCmd.empty())
    {
        auto pTempCMD = m_dequeCmd.front();
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

    auto service = FindServiceByCmd(serverCmd->GetName());

    return service->Invoke(serverCmd);
}

int Kernel::BindServiceCmdToKernel(std::shared_ptr<Service> pService)
{
    using ServiceCMDPair = std::pair< std::string, std::shared_ptr<Service>>;
    std::pair< std::map<std::string, std::shared_ptr<Service>>::iterator, bool > pr;
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

std::shared_ptr<Service> Kernel::FindServiceByCmd(std::string sCMD)
{
    std::map< std::string, std::shared_ptr<Service> >::iterator it = m_mapServiceCmd.find(sCMD);
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
