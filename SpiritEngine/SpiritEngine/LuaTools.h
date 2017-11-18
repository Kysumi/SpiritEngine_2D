#pragma once
#include "BaseModule.h"


namespace le
{
	class LuaTools :
		public BaseModule
	{
	public:
		LuaTools() { RegisterModule(this); };
		~LuaTools() {};

		// Inherited via BaseModule
		virtual void RegisterFunctions(LuaScript * L) override;
		virtual void RegisterFunctions(lua_State * L) override;

		//ContentLoader
		static int luaPrint(lua_State * L);
	};
	
	extern LuaTools m_LuaTools;

}
