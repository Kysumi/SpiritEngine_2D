#ifndef SE_LUASCRIPT_H
#define SE_LUASCRIPT_H
#include "BaseLua.h"
namespace le
{

	class LuaScript :
		public BaseLua
	{
	public:
		LuaScript();
		~LuaScript();

		lua_State * getState() { return _state; };
	};
}
#endif //SE_LUASCRIPT_H
