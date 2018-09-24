#pragma once
#include <Windows.h>
#include <mutex>
#include <list>
#include <map>
#include <deque>
#include <atomic>
#include <process.h>
#include <memory>
#include <iostream>
#include <stdio.h>
#include <string>
#include <typeinfo>
#include <cstdio>


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