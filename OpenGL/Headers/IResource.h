#pragma once
#include <iostream>
#include "mathLibrary.hpp"


__interface IResource
{
	 void Load(const std::string& name) = 0;
	 void UnLoad() = 0;
}; 
