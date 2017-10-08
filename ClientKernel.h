#pragma once
#include "globe\Kernel.h"


class ClientKernel : public Kernel
{
public:
    ClientKernel();
    virtual ~ClientKernel();

protected:
    virtual int OnInitKernel();
    virtual int OnKernelConsole();
};