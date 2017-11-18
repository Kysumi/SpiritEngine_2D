#include "stdafx.h"
#include "Content.h"
#include "BaseLua.h"
#include "LuaTools.h"
#include "LuaContent.h"

namespace se
{


	std::map<std::string, sf::Texture*> Content::_textures;
	std::map<std::string, sf::Font*> Content::_fonts;
	std::map<std::string, sf::Sound*> Content::_sounds;
	std::map<std::string, std::string> Content::_itemsLoaded;

	bool Content::_loaded = false;
	lua_State * Content::_state;

	Content::Content()
	{
	
	}

	void Content::setup()
	{

		if (_loaded == false) {
			//Open a new lua state 
			_state = luaL_newstate();

			//Check the new state was made, if it failed. Report it and stop laoding
			if (_state == NULL)
				Tools::Print("[Error - Content::Content] Failed to allocate memory", false);
			else
			{
				//Open the libs for lua and load the required modules
				luaL_openlibs(_state);
				le::m_LuaTools.RegisterFunctions(_state);
				le::m_LuaContent.RegisterFunctions(_state);
				g_BaseLua.loadGlobal(_state);
				


				//Try load the content loader lua file
				//If it loads, set loaded to true for error checking.
				if (luaL_dofile(_state, "./Content/Lua/System/ContentLoader.lua")) {
					Tools::Print(std::string("[Error - Content::Content] ") + lua_tostring(_state, -1), false);
					_loaded = false;
				}
				else {
					_loaded = true;
				}
			}
		}
	}

	Content::~Content()
	{
		lua_close(_state);
	}


	void Content::load(std::string asset)
	{
		if (errorCheck()) {

			//Pulls the required lua function to the front to be called
			lua_getglobal(_state, "LoadAsset");

			//Pushes the path of the assest that is to be loaded to the lua stack

			lua_pushstring(_state, asset.c_str());
			//Calls the helper function to invoke the required function

			int ret = callHelper(1, 1);
			//need to check ret and decides on error handling for not loading content
		}
		else
		{
			Tools::Print("[Error - Content::load] Could not load asset.");
		}
	}


	// Checks if an asset is loaded, if its not and load == true, it loads it
	bool Content::isLoaded(std::string asset, bool autoLoad)
	{
		if (errorCheck()) {
			//Pulls the required lua function to the front to be called
			lua_getglobal(_state, "IsAssetLoaded");
			//Pushes the path of the assest that is to be loaded to the lua stack
			lua_pushstring(_state, asset.c_str());
			//Calls the helper function to invoke the required function
			callHelper(1, 1);

			bool ret = (bool)lua_toboolean(_state, -1);
			lua_pop(_state, 1);

			//If the functon returns false and autoload is true. Load the file
			//If autoload is false. return true/false
			if (ret == false && autoLoad) {
				Tools::Print("Content Not Loaded (Auto Loading)");
				load(asset);
			}
			else return (bool)ret;

			//if load was called. re-run isLoaded and reutrn the outcome (should be true)
			return isLoaded(asset, false);
		}
		else
		{
			Tools::Print("[Error - Content::isLoaded] Could not load asset.");
			return false;
		}
	}

	void Content::loadImage(std::string name, std::string loc)
	{
		sf::Texture * newTexture = new sf::Texture();
		newTexture->loadFromFile(loc);

		_textures[name] = newTexture;
		
		_itemsLoaded[name] = "Image";

	}

	void Content::loadFont(std::string name, std::string loc)
	{
		sf::Font * newFont = new sf::Font();
		newFont->loadFromFile(loc);

		_fonts[name] = newFont;
	}

	void Content::loadSound(std::string name, std::string loc)
	{
		//Dunno if it needs to be a pointer atm
		//sf::SoundBuffer buffer;
		//buffer.loadFromFile(loc);

		//sf::Sound * newSound = new sf::Sound();
		//newSound->setBuffer(buffer);

		//_sounds[name] = newSound;

	}

	int Content::callHelper(int args, int ret)
	{

		int error_index = lua_gettop(_state) - args;
		lua_pushcfunction(_state, g_BaseLua.luaErrorHandler);
		lua_insert(_state, error_index);

		int r = lua_pcall(_state, args, ret, error_index);
		lua_remove(_state, error_index);
		return r;
	}



}
