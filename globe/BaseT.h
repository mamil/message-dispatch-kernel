#pragma once
#include"GeneralMacro.h"

template <typename T>
class Base
{
public:
	std::string GetPoint(){ return typeid(T*).name(); }
};