#pragma once
#ifdef WIN32
#include <Windows.h>
#include <dbghelp.h>
#include <excpt.h>

#include <stdlib.h>
#include <WinBase.h>


typedef    BOOL(WINAPI * MINIDUMP_WRITE_DUMP)(
    IN HANDLE            hProcess,
    IN DWORD            ProcessId,
    IN HANDLE            hFile,
    IN MINIDUMP_TYPE    DumpType,
    IN CONST PMINIDUMP_EXCEPTION_INFORMATION    ExceptionParam, OPTIONAL
    IN PVOID                                    UserStreamParam, OPTIONAL
    IN PVOID                                    CallbackParam OPTIONAL
    );

class ExceptionBase
{
public:
    ~ExceptionBase();

    int StartMoniter();
    void PrintError();

    static ExceptionBase& GetExcep();
    int DoMiniDump(void* pExcpInfo);

private:
    ExceptionBase();

    HANDLE m_hFileMiniDump;
    static ExceptionBase m_objExcep;
    HMODULE    hDbgHelp;
    MINIDUMP_WRITE_DUMP    MiniDumpWriteDump_;

    int CreateDumpFile();
    int WriteDump(void* info);
};

#endif // WIN32
