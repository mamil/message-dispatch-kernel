#include "ClientKernel.h"

//todo:
//socket
//database
//


int main()
{
    ExceptionBase::GetExcep().StartMoniter();//Òì³£Éú³Édump
    ClientKernel cKernel;

    if (cKernel.InitKernel() != 0)
    {
        return -1;
    }
    
    cKernel.IntoKernelConsole();


    return 0;
}