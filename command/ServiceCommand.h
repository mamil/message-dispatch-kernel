#pragma once
#include "../globe/GeneralMacro.h"


class ServiceCommand
{
private:
    void ShowMe();

public:
    ServiceCommand();

    std::string m_strSelf;

    ULONGLONG m_dwCreateTime;

    inline std::string GetName()const { return m_strSelf; }

private://Timer
    uint32_t m_nTimeout;

public:
    void SetTimeOut(uint32_t Timeout){ m_nTimeout = Timeout; }

public:
    int n[102400] = { 0 };//mark:为了更明显地看到是否有内存泄漏
    int n2[102400] = { 0 };//error:只加2个内存是4M，但是加的再多一点，内存反而会下降！！
    
};