#include "stdafx.h"
#include "Config.h"
#include "Localization.h"
#include "Tools.h"

namespace se {

//Compat reasons
#if LUA_VERSION_NUM >= 502
#define lua_strlen lua_rawlen
#endif

	std::string se::Config::_stringConfigs[(int)LAST_STRING_CONFIG];
	int32_t se::Config::_intergerConfigs[(int)LAST_INPUT];
	float se::Config::_floatConfigs[(int)LAST_FLOAT_CONFIG];
	bool se::Config::_booleanConfigs[(int)LAST_BOOLEAN_CONFIG];

	bool se::Config::_isLoaded = false;

	Config::Config()
	{

	}


	Config::~Config()
	{
	}

	std::string Config::getSetting(Config_String key)
	{
		if (_isLoaded && key < LAST_STRING_CONFIG) {
			return _stringConfigs[key];
		}
		else {
			se::Tools::Print("[Warning - se::Config::getSetting<Config_String>] Value not found.", false);
			return std::string();
		}
	}

	int Config::getSetting(Config_Int key)
	{
		if (_isLoaded && key < LAST_INT_CONFIG) {
			return _intergerConfigs[key];
		}
		else {
			se::Tools::Print("[Warning - se::Config::getSetting<Config_Int>] Value not found.", false);
			return -1;
		}
	}

	float Config::getSetting(Config_Float key)
	{
		if (_isLoaded && key < LAST_FLOAT_CONFIG) {
			return _floatConfigs[key];
		}
		else {
			se::Tools::Print("[Warning - se::Config::getSetting<Config_Float>] Value not found.", false);
			return 0.0f;
		}
	}

	int Config::getSetting(InputType key)
	{
		if (_isLoaded && key < LAST_INPUT) {
			return _intergerConfigs[key];
		}
		else {
			se::Tools::Print("[Warning - se::Config::getSetting<InputType>] Value not found.", false);
			return -1;
		}
	}

	bool Config::getSetting(Config_Boolean key)
	{
		if (_isLoaded && key < LAST_BOOLEAN_CONFIG) {
			return _booleanConfigs[key];
		}
		else {
			se::Tools::Print("[Warning - se::Config::getSetting<Config_Boolean>] Value not found.", false);
			return false;
		}
	}

	bool Config::load()
	{

		lua_State* L = luaL_newstate();
		if (!L) {
			se::Tools::Print("[Error - Config::load] Failed to allocate memory", false);
			return false;
		}

		luaL_openlibs(L);

		if (luaL_dofile(L, "./Content/config.lua")) {
			se::Tools::Print(std::string("[Error - Config::load] ") + lua_tostring(L, -1), false);
			lua_close(L);
			return false;
		}


		if (_isLoaded == false)
		{
			_stringConfigs[WINDOW_TITLE] = fetchString(L, "WindowTitle", "Sprite Engine");
			_stringConfigs[LANGUAGE_LOCALIZATION] = fetchString(L, "Language", "en");

			_intergerConfigs[WINDOW_HEIGHT] = fetchInt(L, "WindowHeight", 600);
			_intergerConfigs[WINDOW_WIDTH] = fetchInt(L, "WindowWidth", 600);


			_intergerConfigs[B2_POSITION] = fetchInt(L, "B2Position", 8);
			_intergerConfigs[B2_VELOCITY] = fetchInt(L, "B2Velocity", 3);
			_floatConfigs[TIMESTEP] = fetchFloat(L, "TimeStep", 1 / 180.0f);



			//USER CONTROL IMPORT
			_intergerConfigs[INPUT_DEBOUNCE] = fetchInt(L, "Input_Debounce", 100);

			_intergerConfigs[P1_UP] = fetchInt(L, "PlayerOne_Up", sf::Keyboard::W);
			_intergerConfigs[P1_DOWN] = fetchInt(L, "PlayerOne_Down", sf::Keyboard::S);
			_intergerConfigs[P1_LEFT] = fetchInt(L, "PlayerOne_Left", sf::Keyboard::A);
			_intergerConfigs[P1_RIGHT] = fetchInt(L, "PlayerOne_Right", sf::Keyboard::D);
			_intergerConfigs[P1_JUMP] = fetchInt(L, "PlayerOne_Jump", sf::Keyboard::Space);
			_intergerConfigs[P1_FIRE] = fetchInt(L, "PlayerOne_Fire", sf::Keyboard::LShift);
			_intergerConfigs[P1_CROUCH] = fetchInt(L, "PlayerOne_Crouch", sf::Keyboard::C);
			_intergerConfigs[P1_STRAFE_LEFT] = fetchInt(L, "PlayerOne_Strafe_Left", sf::Keyboard::Q);
			_intergerConfigs[P1_STRAFE_RIGHT] = fetchInt(L, "PlayerOne_Strafe_Right", sf::Keyboard::E);


			_intergerConfigs[P2_UP] = fetchInt(L, "PlayerTwo_Up", sf::Keyboard::Up);
			_intergerConfigs[P2_DOWN] = fetchInt(L, "PlayerTwo_Down", sf::Keyboard::Down);
			_intergerConfigs[P2_LEFT] = fetchInt(L, "PlayerTwo_Left", sf::Keyboard::Left);
			_intergerConfigs[P2_RIGHT] = fetchInt(L, "PlayerTwo_Right", sf::Keyboard::Right);
			_intergerConfigs[P2_JUMP] = fetchInt(L, "PlayerTwo_Jump", sf::Keyboard::LControl);
			_intergerConfigs[P2_FIRE] = fetchInt(L, "PlayerTwo_Fire", sf::Keyboard::Return);
			_intergerConfigs[P2_CROUCH] = fetchInt(L, "PlayerTwo_Crouch", sf::Keyboard::LShift);
			_intergerConfigs[P2_STRAFE_LEFT] = fetchInt(L, "PlayerTwo_Strafe_Left", sf::Keyboard::Unknown);
			_intergerConfigs[P2_STRAFE_RIGHT] = fetchInt(L, "PlayerTwo_Strafe_Right", sf::Keyboard::Unknown);



			_floatConfigs[PIXEL_PER_METER] = fetchFloat(L, "PixelsPerMeter", 30.0f);

			_booleanConfigs[SHOW_FPS] = fetchBoolean(L, "ShowFps", false);

		}



		lua_close(L);

		_isLoaded = true;
		return true;
	}

	bool Config::reload()
	{
		if (_isLoaded == false) {
			return false;
		}
		
		return load();
	}
	
	std::string Config::fetchString(lua_State * state,const std::string & key, std::string defaultIValue)
	{
		lua_getglobal(state, key.c_str());

		if (lua_isstring(state, -1) == false) {
			return defaultIValue;
		}

		size_t len = lua_strlen(state, -1);
		std::string ret(lua_tostring(state, -1), len);
		lua_pop(state, 1);
		return ret;
	}
	int Config::fetchInt(lua_State * state,const std::string & key, int defaultIValue)
	{
		lua_getglobal(state, key.c_str());

		if (lua_isnumber(state, -1) == false) {
			return defaultIValue;
		}

		int32_t val = lua_tonumber(state, -1);
		lua_pop(state, 1);
		return val;
	}
	float Config::fetchFloat(lua_State * state,const std::string & key, float defaultIValue)
	{
		lua_getglobal(state, key.c_str());

		if (lua_isnumber(state, -1) == false) {
			return defaultIValue;
		}

		float val = lua_tonumber(state, -1);
		lua_pop(state, 1);
		return val;
	}

	bool Config::fetchBoolean(lua_State * state,const std::string & key, bool defaultIValue)
	{
		lua_getglobal(state, key.c_str());

		if (lua_isboolean(state, -1) == false) {
			return defaultIValue;
		}

		bool val = lua_toboolean(state, -1);
		lua_pop(state, 1);
		return val;
	}
}
