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
    int n[102400] = { 0 };//mark:为了更明显地看到是否有内存泄漏

public:
    void SetTimeOut(uint32_t Timeout){ m_nTimeout = Timeout; }

};