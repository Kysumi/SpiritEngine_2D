#include "stdafx.h"
#include "ScreenManager.h"
#include "BaseLua.h"

namespace se
{

	ScreenManager g_ScreenManager;

	ScreenManager::ScreenManager()
	{
		//Open a new lua state 
		_state = luaL_newstate();

		//Check the new state was made, if it failed. Report it and stop laoding
		if (_state == NULL)
			Tools::Print("[Error - ScreenManager::ScreenManager] Failed to allocate memory", false);
		else
		{
			//Open the libs for lua and load the required modules
			luaL_openlibs(_state);
			g_BaseLua.loadGlobal(_state);



			//Try load the content loader lua file
			//If it loads, set loaded to true for error checking.
			if (luaL_dofile(_state, "./Content/Lua/System/ScreenManager.lua")) {
				Tools::Print(std::string("[Error - ScreenManager::ScreenManager] ") + lua_tostring(_state, -1), false);
				_loaded = false;
			}
			else {
				_loaded = true;
			}
		}	
	}


	ScreenManager::~ScreenManager()
	{
	}

}



/*Functions:
Cascades through all files inside / content / lua / screens/*
Triggers "LoadContent" in *.lua if it exists
Registers all screens as "Screen" object in c++
Assigns all scences to its parent "Screen" (Id or name?)
Interface with the content loader too load all assets and update the progress bars on the loading screen.
Manage activation and deactivation of screens and drawing them in their layers? (dunno if i should manage this as c++)*/