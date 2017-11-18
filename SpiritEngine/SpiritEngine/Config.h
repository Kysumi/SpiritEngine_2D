#ifndef SE_CONFIG_H
#define SE_CONFIG_H
#include "lua.hpp"
#include "Enums.h"

namespace se
{
	class Config
	{
	public:
		Config();
		~Config();

		static std::string getSetting(Config_String key);
		static int getSetting(Config_Int key);
		static float getSetting(Config_Float key);
		static bool getSetting(Config_Boolean key);
		static int getSetting(InputType key);


		static bool load();
		static bool reload();

	private:

		static std::string fetchString(lua_State * state,const std::string& key, std::string defaultIValue);
		static int fetchInt(lua_State * state,const std::string& key, int defaultIValue);
		static float fetchFloat(lua_State * state,const std::string& key, float defaultIValue);
		static bool fetchBoolean(lua_State * state,const std::string& key, bool defaultIValue);

		static bool _isLoaded;

		static std::string _stringConfigs[se::Config_String::LAST_STRING_CONFIG];
		static int32_t _intergerConfigs[se::InputType::LAST_INPUT];
		static float _floatConfigs[se::Config_Float::LAST_FLOAT_CONFIG];
		static bool _booleanConfigs[se::Config_Boolean::LAST_BOOLEAN_CONFIG];
	};

}
#endif //SE_CONFIG_H
