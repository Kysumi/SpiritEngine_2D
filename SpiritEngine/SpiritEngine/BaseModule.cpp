#include "stdafx.h"
#include "BaseModule.h"
#include "LuaScript.h"
namespace le
{
	std::vector<BaseModule*> BaseModule::_modules;


	void BaseModule::LoadModules(LuaScript * L)
	{
		for (size_t i = 0; i < _modules.size(); i++)
		{
			_modules[i]->RegisterClass(L);
			_modules[i]->RegisterFunctions(L);
		}
	}

	void BaseModule::RegisterType(std::string c, LuaDataType type)
	{
		BaseLua::ClassTypes[c] = type;
	}
}
