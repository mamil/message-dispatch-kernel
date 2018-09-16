#pragma once
#include "ClientKernel.h"

#include "service\ServiceGold.h"
#include "command\ServiceCmdGold.h"


ClientKernel::ClientKernel()
{

}

ClientKernel::~ClientKernel()
{

}

int ClientKernel::OnInitKernel()
{
    auto pGold = std::make_shared<ServiceGold>();
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
            auto pCmd = std::make_shared<ServiceCmdGold>();
            SendServiceCMD(pCmd);
        }
        else if ("bg" == sCmd || "BG" == sCmd)
        {
            auto pCmd = std::make_shared<ServiceCmdBlackGold>();
            SendServiceCMD(pCmd);
        }
        else if ("q" == sCmd || "Q" == sCmd)
        {
            break;
        }

    } while (true);
    return 0;
}