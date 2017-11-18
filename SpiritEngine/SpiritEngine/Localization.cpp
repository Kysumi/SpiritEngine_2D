#include "stdafx.h"
#include "Localization.h"


namespace se
{
	Localization g_Localization;

	Localization::Localization()
	{
	}

	void Localization::reload()
	{
		g_Localization._loaded = false;
		lua_close(g_Localization._state);
		Tools::Print("Reloading Localization...", false);
		load();
	}

	void Localization::load()
	{
		if (g_Localization._loaded == false) {
			//Open a new lua state 
			g_Localization._state = luaL_newstate();

			//Check the new state was made, if it failed. Report it and stop laoding
			if (g_Localization._state == NULL)
				Tools::Print("[Error - Localization::load] Failed to allocate memory", false);
			else
			{
				//Open the libs for lua and load the required modules
				luaL_openlibs(g_Localization._state);



				//Try load the content loader lua file
				//If it loads, set loaded to true for error checking.
				std::string file = "./Content/Lua/Locals/" + se::Config::getSetting(LANGUAGE_LOCALIZATION) + ".lua";
				if (luaL_dofile(g_Localization._state, file.c_str())) {
					Tools::Print(std::string("[Error - Localization::load] ") + lua_tostring(g_Localization._state, -1), false);
					g_Localization._loaded = false;
				}
				else {
					g_Localization.loadStrings();
					g_Localization._loaded = true;
				}
			}
		}

	}

	std::string Localization::getLocal(std::string key)
	{

		bool found = false;
		for (auto s : g_Localization._strings)
		{
			if (s.first == key) {
				found = true;
				break;
			}
		}

		if (found)

			return g_Localization._strings[key];
		else {

			Tools::Print(std::string("[Error - Localization::getLocal] '") + key + "' is not a valid key.", false);
			return std::string("Not a real string.");
		}
	}


	void Localization::loadStrings()
	{

		lua_getglobal(g_Localization._state, "STRINGS");
		_strings.clear();
		lua_pushnil(g_Localization._state);

		while (lua_next(g_Localization._state, -2) != 0)
		{
			if (lua_isstring(g_Localization._state, -1))
				g_Localization._strings[lua_tostring(g_Localization._state, -2)] = lua_tostring(g_Localization._state, -1);

			lua_pop(g_Localization._state, 1);
		}
	}


	Localization::~Localization()
	{
	}

}