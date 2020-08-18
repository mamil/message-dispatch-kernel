#pragma once
#include "ClientKernel.h"

#include "service/ServiceGold.h"
#include "command/ServiceCmdGold.h"


ClientKernel::ClientKernel()
{

}

ClientKernel::~ClientKernel()
{

}

int ClientKernel::OnInitKernel()
{
    auto pGold = SHARED_PTR(ServiceGold);
    AddServiceToKernel(pGold);

    return 0;
}

int ClientKernel::OnKernelConsole()
{
    std::string sCmd = "0";

    do
    {
        std::cin >> sCmd;
        if ("g" == sCmd || "G" == sCmd)
        {
            auto pCmd = SHARED_PTR(ServiceCmdGold);
            SendServiceCMD(pCmd);
        }
        else if ("g1000" == sCmd || "G1000" == sCmd)
        {
            for (int i = 0; i < 1000; i++)
            {
                auto pCmd = SHARED_PTR(ServiceCmdGold);
                SendServiceCMD(pCmd);
            }
        }
        else if ("bg" == sCmd || "BG" == sCmd)
        {
            auto pCmd = SHARED_PTR(ServiceCmdBlackGold);
            SendServiceCMD(pCmd);
        }
        else if ("q" == sCmd || "Q" == sCmd)
        {
            break;
        }
        else if ("d" == sCmd || "D" == sCmd)
        {
            #ifdef WIN32
            ExceptionBase::GetExcep().DoMiniDump(this);
            #endif // WIN32
        }

    } while (true);
    return 0;
}