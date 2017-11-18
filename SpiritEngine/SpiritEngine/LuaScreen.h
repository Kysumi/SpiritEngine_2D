#pragma once
#include "BaseModule.h"
namespace le
{
	class LuaScreen :
		public BaseModule
	{
	public:
		LuaScreen() { RegisterModule(this); };
		~LuaScreen() {};

		// Inherited via BaseModule
		virtual void RegisterFunctions(LuaScript * L) override;
		virtual void RegisterFunctions(lua_State * L) override;
	};
}

