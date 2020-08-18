#include "globe/GeneralMacro.h"
#include "ClientKernel.h"


//todo:
//socket
//database
//


int main()
{
    {
        #ifdef WIN32
        ExceptionBase::GetExcep().StartMoniter();//异常生成dump
        #endif // WIN32

        ClientKernel cKernel;

        if (cKernel.InitKernel() != 0)
        {
            return -1;
        }

        cKernel.IntoKernelConsole();
    }

    #ifdef WIN32
    //memory leak
    //Send all reports to STDOUT
    /*_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);*/

    //_CrtDumpMemoryLeaks();

    _CrtMemDumpAllObjectsSince(NULL);
    #endif // WIN32

    return 0;
}