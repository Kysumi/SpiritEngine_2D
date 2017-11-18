#ifndef SE_BASELUA_H
#define SE_BASELUA_H
#include <iostream>
#include <lua.hpp>


namespace le
{
	//# Ref: TheForgottenServer.
	class BaseLua
	{
	public:
		BaseLua();
		~BaseLua();
		void printError(const std::string* variableName, const std::string* reason);
		void RunScript(std::string script, std::string eventName);
		void UpdateTime(std::string script, std::string entry, int32_t mSeconds);
		int RunCommand(std::string script, std::string command, std::string params);

		static std::map<std::string, LuaDataType> ClassTypes;

		static void setMetatable(lua_State* L, int32_t index, const std::string& name);

		int32_t loadFile(const std::string& file);

		virtual void registerFunctions() {};

		inline static void setField(lua_State* L, const char* index, lua_Number value)
		{
			lua_pushnumber(L, value);
			lua_setfield(L, -2, index);
		}

		static void pushPosition(lua_State* L, const sf::Vector2f& position);
		static sf::Vector2f getPosition(lua_State* L, int32_t arg);



		inline static void setField(lua_State* L, const char* index, const std::string& value)
		{
			pushString(L, value);
			lua_setfield(L, -2, index);
		}

		void registerClass(const std::string& className, const std::string& baseClass, lua_CFunction newFunction = nullptr);
		void registerTable(const std::string& tableName);
		void registerMethod(const std::string& className, const std::string& methodName, lua_CFunction func);
		void registerMetaMethod(const std::string& className, const std::string& methodName, lua_CFunction func);
		void registerGlobalMethod(const std::string& functionName, lua_CFunction func);
		void registerVariable(const std::string& tableName, const std::string& name, lua_Number value);
		void registerGlobalVariable(const std::string& name, lua_Number value);
		void registerGlobalBoolean(const std::string& name, bool value);

		//Overloaded Registers to bypass main lua system

		void registerTable(lua_State* L, const std::string& tableName);
		void registerMethod(lua_State* L, const std::string& className, const std::string& methodName, lua_CFunction func);
		void registerClass(lua_State* L, const std::string& className, const std::string& baseClass, lua_CFunction newFunction = nullptr);

		void loadGlobal(lua_State* L);

		static int protectedCall(lua_State* L, int nargs, int nresults);
		static int luaErrorHandler(lua_State* L);

#pragma endregion

#pragma region Get/Sets

#pragma region Push
		static void pushString(lua_State* L, const std::string& value);
		static void pushCallback(lua_State* L, int32_t callback);
		static void pushBoolean(lua_State* L, bool value);

		// Userdata
		template<class T>
		static void pushUserdata(lua_State* L, T* value)
		{
			T** userdata = static_cast<T**>(lua_newuserdata(L, sizeof(T*)));
			*userdata = value;
		}
#pragma endregion

#pragma region Pop
		static std::string popString(lua_State* L);
		static int32_t popCallback(lua_State* L);
#pragma endregion

#pragma region Get
		template<typename T>
		inline static typename std::enable_if<std::is_enum<T>::value, T>::type
			getNumber(lua_State* L, int32_t arg)
		{
			return static_cast<T>(static_cast<int64_t>(lua_tonumber(L, arg)));
		}

		template<typename T>
		inline static typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, T>::type
			getNumber(lua_State* L, int32_t arg)
		{
			return static_cast<T>(lua_tonumber(L, arg));
		}

		template<typename T>
		static T getNumber(lua_State *L, int32_t arg, T defaultValue)
		{
			const auto parameters = lua_gettop(L);
			if (parameters == 0 || arg > parameters) {
				return defaultValue;
			}
			return getNumber<T>(L, arg);
		}

		static std::string getString(lua_State* L, int32_t arg);

		template<class T>
		static T* getUserdata(lua_State* L, int32_t arg)
		{
			T** userdata = getRawUserdata<T>(L, arg);
			if (!userdata) {
				return nullptr;
			}
			return *userdata;
		}
		template<class T>
		inline static T** getRawUserdata(lua_State* L, int32_t arg)
		{
			return reinterpret_cast<T**>(lua_touserdata(L, arg));
		}
		template<typename T>
		static T getField(lua_State* L, int32_t arg, const std::string& key)
		{
			lua_getfield(L, arg, key.c_str());
			return getNumber<T>(L, -1);
		}
#pragma endregion

#pragma endregion


		void reportError(const char* function, const std::string& error_desc, bool stack_trace = false/* = false*/);
		std::string getStackTrace(const std::string& error_desc);

		inline void clean() {
			int n = lua_gettop(_state);
			lua_pop(_state, n);
		}



		// Is -thanks ot
		inline static bool isNumber(lua_State* L, int32_t arg)
		{
			return lua_isnumber(L, arg) != 0;
		}
		inline static bool isString(lua_State* L, int32_t arg)
		{
			return lua_isstring(L, arg) != 0;
		}
		inline static bool isBoolean(lua_State* L, int32_t arg)
		{
			return lua_isboolean(L, arg);
		}
		inline static bool isTable(lua_State* L, int32_t arg)
		{
			return lua_istable(L, arg);
		}
		inline static bool isFunction(lua_State* L, int32_t arg)
		{
			return lua_isfunction(L, arg);
		}
		inline static bool isUserdata(lua_State* L, int32_t arg)
		{
			return lua_isuserdata(L, arg) != 0;
		}
	protected:
		lua_State * _state;
	private:
	};
}


extern le::BaseLua g_BaseLua;

#endif // !SE_BASELUA_H
