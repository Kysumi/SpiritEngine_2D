#ifndef LE_LUACONTENT_H
#define LE_LUACONTENT_H

#include "BaseModule.h"
#include "Content.h"

namespace le
{

	class LuaContent :
		public BaseModule , public se::Content
	{
	public:
		LuaContent() {};
		~LuaContent() {};

		// Inherited via BaseModule
		virtual void RegisterFunctions(LuaScript * L) override;
		virtual void RegisterFunctions(lua_State * L) override;

		//ContentLoader
		static int luaLoadTexture(lua_State * L);
		static int luaLoadFont(lua_State * L);
		static int luaLoadSound(lua_State * L);
		static int luaLoad(lua_State * L);
		static int luaIsLoaded(lua_State * L);
		static int luaGetLoaded(lua_State * L);

	};
	extern LuaContent m_LuaContent;
}

#endif // !LE_LUACONTENT_H
