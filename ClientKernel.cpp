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
	ServiceGold *pGold = new ServiceGold;
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
			std::shared_ptr<ServiceCmdGold> pCmd(new ServiceCmdGold);
			SendServiceCMD(pCmd);
		}
		else if ("bg" == sCmd || "BG" == sCmd)
		{
			std::shared_ptr< ServiceCmdBlackGold > pCmd( new ServiceCmdBlackGold);
			SendServiceCMD(pCmd);
		}
		else if ("q" == sCmd || "Q" == sCmd)
		{
			break;
		}

	} while (true);
	return 0;
}