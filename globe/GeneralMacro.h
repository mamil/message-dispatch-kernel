#pragma once
#include <mutex>
#include <list>
#include <map>
#include <deque>
#include <atomic>
#include <memory>
#include <iostream>
#include <stdio.h>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <thread>

// for win headers
#ifdef WIN32
#include <Windows.h>
#include <process.h>
#endif // WIN32

// for linux
#if defined(__linux__) || defined(__linux)
#include <time.h>
#include <unistd.h>
#include <sys/syscall.h>
#endif // linux

//#include "../command/ServiceCommand.h"


const int TIMER_NOT_EXIST = -1;
const int KERNEL_WAIT_TIME = 5 * 10;
const int KERNEL_WORK = 0;

//typedef DWORD KERNELHANDLE;

class ServiceCommand;

using ServiceCMD = ServiceCommand * ;

template <typename T>
std::string GetName(T* pCmd)
{
    return typeid(pCmd).name();
}

template <typename T>
std::string initName(T*)
{
    return typeid(T*).name();
}

// linux thread id
#if defined(__linux__) || defined(__linux)
class CurrentThread
{
public:
    static pid_t gettid()
    {
        return syscall(SYS_gettid);
    }
};
#endif // linux


//for memory leaks
#ifdef WIN32

#ifdef _DEBUG
    #define SHARED_PTR(param) std::shared_ptr<param>(new param);
#else
    #define SHARED_PTR(param) std::make_shared<param>();
#endif // _DEBUG


#ifdef _DEBUG
    #define CHECK_MEMORY_LEAKS
#endif // _DEBUG

#ifdef CHECK_MEMORY_LEAKS
    #define _CRTDBG_MAP_ALLOC
    #include <stdlib.h>
    #include <crtdbg.h>
    #define CHECK_MEMORY_LEAKS_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
    #define new CHECK_MEMORY_LEAKS_NEW
#endif // CHECK_MEMORY_LEAKS

#endif // WIN32

#if defined(__linux__) || defined(__linux)
#define SHARED_PTR(param) std::make_shared<param>();
#endif // linux