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
const int KERNEL_WAIT_TIME = 5 * 1000;
const int KERNEL_WORK = 0;

//typedef DWORD KERNELHANDLE;

class ServiceCommand;
typedef ServiceCommand* ServiceCMD;


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