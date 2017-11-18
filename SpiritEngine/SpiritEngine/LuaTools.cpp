#include "stdafx.h"
#include "LuaTools.h"
#include "LuaScript.h"


namespace le
{
	LuaTools m_LuaTools;


	void LuaTools::RegisterFunctions(LuaScript * L)
	{
		RegisterFunctions(L->getState());
	/*	L->registerTable("Tools");
		
		L->registerMethod("Tools", "print", LuaTools::luaPrint);*/
	
	}

	void LuaTools::RegisterFunctions(lua_State * L)
	{
		g_BaseLua.registerTable(L,"Tools");
		g_BaseLua.registerMethod(L,"Tools", "print", LuaTools::luaPrint);
	}


	int LuaTools::luaPrint(lua_State * L)
	{

		if (lua_isstring(L, -1))
		{
			se::Tools::Print(lua_tostring(L, -1),lua_toboolean(L,-2));
		}
		return 0;
	}

}