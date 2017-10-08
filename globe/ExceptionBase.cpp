#pragma once
#include<iostream>
#include"ExceptionBase.h"



ExceptionBase ExceptionBase::m_objExcep;//这句千万不能丢

ExceptionBase::ExceptionBase()
{
    m_hFileMiniDump = INVALID_HANDLE_VALUE;

    hDbgHelp = LoadLibraryA("DBGHELP.DLL");
    MiniDumpWriteDump_ = (MINIDUMP_WRITE_DUMP)GetProcAddress(hDbgHelp, "MiniDumpWriteDump");
}

ExceptionBase::~ExceptionBase()
{
}

LONG WINAPI exception_handle(struct _EXCEPTION_POINTERS* ExceptionInfo)
{
    std::cout << "get it!" << std::endl;

    if (ExceptionInfo)
    {
        return ExceptionBase::GetExcep().DoMiniDump((void*)ExceptionInfo);
    }
    else
    {
        std::cout << "No info" << std::endl;
        return 0;
    }
}

ExceptionBase& ExceptionBase::GetExcep()
{
    return ExceptionBase::m_objExcep;
}

int ExceptionBase::DoMiniDump(void* info)
{
    if ( CreateDumpFile())
    {
        return -1;
    }

    MINIDUMP_EXCEPTION_INFORMATION exception_param;
    exception_param.ExceptionPointers = (PEXCEPTION_POINTERS)info;
    exception_param.ThreadId = GetCurrentThreadId();
    exception_param.ClientPointers = TRUE;

    if (info)
    {
        WriteDump(&exception_param);
    }
    else
    {
        WriteDump(NULL);
    }

    return 0;
}

int ExceptionBase::CreateDumpFile()
{
    char file_name[MAX_PATH];
    SYSTEMTIME lpSystemTime;

    ::GetLocalTime(&lpSystemTime);
    _snprintf_s(file_name, sizeof(file_name), sizeof(file_name), "%04d%02d%02d-%02d%02d%02d-%ld.dmp", 
        lpSystemTime.wYear, lpSystemTime.wMonth, lpSystemTime.wDay, lpSystemTime.wHour, lpSystemTime.wMinute,
        lpSystemTime.wSecond, GetCurrentProcessId());

    m_hFileMiniDump = ::CreateFileA(file_name, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (m_hFileMiniDump == INVALID_HANDLE_VALUE)
    {
        std::cout<<"CreateMiniDumpFile"<<std::endl;
        return 1;
    }

    return 0;
}

int ExceptionBase::WriteDump(void * info)
{
    if (!MiniDumpWriteDump_(GetCurrentProcess(), GetCurrentProcessId(), m_hFileMiniDump,
                            MiniDumpWithFullMemory/*MiniDumpNormal*/, (PMINIDUMP_EXCEPTION_INFORMATION)info, NULL, NULL))
    {
        std::cout << "WriteMiniDumpFile" << std::endl;
        return 1;
    }

    return 0;
}

int ExceptionBase::StartMoniter()
{
    ::SetUnhandledExceptionFilter(exception_handle);
    return 0;
}

void ExceptionBase::PrintError()
{
    LPVOID lpMsgBuf;

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        (LPTSTR)&lpMsgBuf,
        0,
        NULL
        );

    std::cout << "Error:" << lpMsgBuf << std::endl;
    LocalFree(lpMsgBuf);
}