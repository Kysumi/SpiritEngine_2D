#ifndef SE_LOCALIZATION_H
#define SE_LOCALIZATION_H

namespace se
{
	class Localization
	{
	public:
		Localization();
		~Localization();

		static void load();
		static std::string getLocal(std::string key);
		static void reload();


	protected:
		lua_State * _state;
		bool _loaded;
		void loadStrings();
	private:
		std::map<std::string, std::string> _strings;


	};
	extern Localization g_Localization;
}

#endif // !SE_LOCALIZATION_H

