#include "ClientKernel.h"

//todo:
//socket
//database
//


int main()
{
    ExceptionBase::GetExcep().StartMoniter();//�쳣����dump
    ClientKernel cKernel;

    if (cKernel.InitKernel() != 0)
    {
        return -1;
    }
    
    cKernel.IntoKernelConsole();


    return 0;
}