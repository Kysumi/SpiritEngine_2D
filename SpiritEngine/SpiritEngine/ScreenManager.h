#ifndef SE_SCREENMANAGER_H
#define SE_SCREENMANAGER_H
#include "lua.hpp"

namespace se
{
	class ScreenManager
	{
	public:
		ScreenManager();
		~ScreenManager();



	private:
		lua_State * _state;
		bool _loaded = true;
	};

	extern ScreenManager g_ScreenManager;
}
#endif //SE_SCREENMANAGER_H
