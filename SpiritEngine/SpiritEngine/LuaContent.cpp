#include "stdafx.h"
#include "LuaContent.h"
#include "LuaScript.h"


namespace le
{
	LuaContent m_LuaContent;

	void LuaContent::RegisterFunctions(LuaScript * L)
	{
		RegisterFunctions(L->getState());
	}

	void LuaContent::RegisterFunctions(lua_State * L)
	{
		g_BaseLua.registerTable(L, "Content");

		g_BaseLua.registerMethod(L, "Content", "loadTexture", LuaContent::luaLoadTexture);
		g_BaseLua.registerMethod(L, "Content", "loadSound", LuaContent::luaLoadSound);
		g_BaseLua.registerMethod(L, "Content", "loadFont", LuaContent::luaLoadFont);
		g_BaseLua.registerMethod(L, "Content", "isLoaded", LuaContent::luaLoadFont);
		g_BaseLua.registerMethod(L, "Content", "load", LuaContent::luaIsLoaded);
		g_BaseLua.registerMethod(L, "Content", "getLoaded", LuaContent::luaGetLoaded);
	}

	int LuaContent::luaLoadTexture(lua_State * L)
	{
		if (lua_isstring(L, -1) && lua_isstring(L, -2))
		{
			std::string name = lua_tostring(L, -2);
			std::string loc = lua_tostring(L, -1);
			loadImage(name, loc);
			se::Tools::Print("[Success - LuaContent::luaLoadTexture] " + name + " has been loaded from " + loc + ".");
			return 1;
		}
		return 0;
	}

	int LuaContent::luaLoadFont(lua_State * L)
	{
		if (lua_isstring(L, -1) && lua_isstring(L, -2))
		{
			std::string name = lua_tostring(L, -2);
			std::string loc = lua_tostring(L, -1);
			loadFont(name, loc);
			se::Tools::Print("[Success - LuaContent::luaLoadFont] " + name + " has been loaded from " + loc + ".");
			return 1;
		}
		return 0;
	}

	int LuaContent::luaLoadSound(lua_State * L)
	{
		if (lua_isstring(L, -1) && lua_isstring(L, -2))
		{
			std::string name = lua_tostring(L, -2);
			std::string loc = lua_tostring(L, -1);
			loadSound(name, loc);
			se::Tools::Print("[Success - LuaContent::luaLoadSound] " + name + " has been loaded from " + loc + ".");
			return 1;
		}
		return 0;
	}

	int LuaContent::luaLoad(lua_State * L)
	{
		if (lua_isstring(L, -1))
		{
			std::string asset = lua_tostring(L, -1);
			se::Content::load(asset);

		}

		return 0;
	}

	int LuaContent::luaIsLoaded(lua_State * L)
	{
		if (lua_isstring(L, 1))
		{
			std::string asset = lua_tostring(L, 1);
			bool autoLoad = false;

			if (lua_isboolean(L, 2))
				autoLoad = (bool)lua_toboolean(L, 2);

			if (Content::isLoaded(asset, autoLoad))
				lua_pushboolean(L, true);
			else
				lua_pushboolean(L, false);
		}

		return 1;
	}

	int LuaContent::luaGetLoaded(lua_State * L)
	{

		std::map<std::string, std::string> * loadedItems = getLoadedItems();

		//create a table
		//lua_createtable(L, 0, loadedItems->size());

		lua_createtable(L, loadedItems->size(),0);

		int index = 1;
		//populate table with font names
		for (auto item : *loadedItems)
		{
			lua_pushnumber(L, index);
			lua_createtable(L, 0, 2);
			lua_pushstring(L, item.first.c_str());
			lua_setfield(L, -2, "Name");
			lua_pushstring(L, item.second.c_str());
			lua_setfield(L, -2, "Value");

			lua_settable(L, -3);
			//BaseLua::setField(L, index, );
			index++;
		}
		return 1;
	}

}