#ifndef SE_BASEMODULE_H
#define SE_BASEMODULE_H
#include <lua.hpp>
#include "Enums.h"
#include <vector>

namespace le
{
	class LuaScript;

	class BaseModule
	{
	public:
		BaseModule() {};
		~BaseModule() {};
		virtual void RegisterFunctions(LuaScript * L) {};
		virtual void RegisterFunctions(lua_State * L) {};
		virtual void RegisterClass(LuaScript * L) { };
		virtual void RegisterClass(lua_State * L) { };

		static void LoadModules(LuaScript * L);

	protected:
		static void RegisterModule(BaseModule * m) { _modules.push_back(m); };
		static void RegisterType(std::string c, le::LuaDataType type);

	private:
		static std::vector<BaseModule *> _modules;

	};

}
#endif //SE_BASEMODULE_H

