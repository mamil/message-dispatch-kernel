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
    int n[102400] = { 0 };//mark:Ϊ�˸����Եؿ����Ƿ����ڴ�й©
    int n2[102400] = { 0 };//error:ֻ��2���ڴ���4M�����Ǽӵ��ٶ�һ�㣬�ڴ淴�����½�����
    
};