#include "stdafx.h"
#include "BaseLua.h"
#include "Tools.h"

le::BaseLua g_BaseLua;


std::map<std::string, le::LuaDataType> le::BaseLua::ClassTypes;
namespace le
{

#define registerEnum(value) { std::string enumName = #value; registerGlobalVariable(enumName.substr(enumName.find_last_of(':') + 1), value); };

	BaseLua::BaseLua()
	{
		_state = luaL_newstate();
        if(_state != NULL){
            luaL_openlibs(_state);
            registerFunctions();
        }
        else
        {
            std::cout << "Failed to assign memory" << std::endl;
        }
	}

	void BaseLua::setMetatable(lua_State* L, int32_t index, const std::string& name)
	{
		
		luaL_getmetatable(L, name.c_str());
		lua_setmetatable(L, index - 1);
	}

	BaseLua::~BaseLua()
	{
		if (_state) lua_close(_state);
	}


	int32_t BaseLua::loadFile(const std::string & file)
	{
		int ret = luaL_loadfile(_state, file.c_str());
		if (ret != 0) {
			reportError("LoadFile", popString(_state));
			return -1;
		}

		ret = protectedCall(_state, 0, 0);

		return 0;
	}


#pragma region Registering

	void BaseLua::registerClass(const std::string& className, const std::string& baseClass, lua_CFunction newFunction)
	{
		registerClass(_state, className, baseClass, newFunction);
	}
	void BaseLua::registerClass(lua_State * L , const std::string& className, const std::string& baseClass, lua_CFunction newFunction/* = nullptr*/)
	{
		// className = {}
		lua_newtable(L);
		lua_pushvalue(L, -1);
		lua_setglobal(L, className.c_str());
		int methods = lua_gettop(L);

		// methodsTable = {}
		lua_newtable(L);
		int methodsTable = lua_gettop(L);

		if (newFunction) {
			// className.__call = newFunction
			lua_pushcfunction(L, newFunction);
			lua_setfield(L, methodsTable, "__call");
		}

		uint32_t parents = 0;
		if (!baseClass.empty()) {
			lua_getglobal(L, baseClass.c_str());
			lua_rawgeti(L, -1, 'p');
			parents = (uint32_t)lua_tonumber(L, -1) + 1;
			lua_pop(L, 1);
			lua_setfield(L, methodsTable, "__index");
		}

		// setmetatable(className, methodsTable)
		lua_setmetatable(L, methods);

		// className.metatable = {}
		luaL_newmetatable(L, className.c_str());
		int metatable = lua_gettop(L);

		// className.metatable.__metatable = className
		lua_pushvalue(L, methods);
		lua_setfield(L, metatable, "__metatable");

		// className.metatable.__index = className
		lua_pushvalue(L, methods);
		lua_setfield(L, metatable, "__index");

		// className.metatable['h'] = hash
		lua_pushnumber(L, std::hash<std::string>()(className));
		lua_rawseti(L, metatable, 'h');

		// className.metatable['p'] = parents
		lua_pushnumber(L, parents);
		lua_rawseti(L, metatable, 'p');


		//std::map<std::string, LuaDataType>::iterator it = ClassTypes.find(className);
		//if (it != ClassTypes.end())
		//	lua_pushnumber(_state, it->second);
		//else
		//	lua_pushnumber(_state, LuaDataType::LuaData_Unknown);

		lua_rawseti(L, metatable, 't');

		// pop className, className.metatable
		lua_pop(L, 2);
	}

	void BaseLua::loadGlobal(lua_State * L)
	{
		if (luaL_dofile(L, "./Content/Lua/global.lua")==-1)
		{
			se::Tools::Print(std::string("[Error - BaseLua::loadGlobal] ") + lua_tostring(L, -1), false);
		}
	}

	void BaseLua::registerTable(const std::string& tableName)
	{
		// _G[tableName] = {}
		lua_newtable(_state);
		lua_setglobal(_state, tableName.c_str());
	}	
	
	void BaseLua::registerTable(lua_State* L, const std::string& tableName)
	{
		// _G[tableName] = {}
		lua_newtable(L);
		lua_setglobal(L, tableName.c_str());
	}

	void BaseLua::registerMethod(lua_State* L, const std::string& globalName, const std::string& methodName, lua_CFunction func)
	{
		// globalName.methodName = func
		lua_getglobal(L, globalName.c_str());
		lua_pushcfunction(L, func);
		lua_setfield(L, -2, methodName.c_str());

		// pop globalName
		lua_pop(L, 1);
	}

	void BaseLua::registerMethod(const std::string& globalName, const std::string& methodName, lua_CFunction func)
	{
		// globalName.methodName = func
		lua_getglobal(_state, globalName.c_str());
		lua_pushcfunction(_state, func);
		lua_setfield(_state, -2, methodName.c_str());

		// pop globalName
		lua_pop(_state, 1);
	}

	void BaseLua::registerMetaMethod(const std::string& className, const std::string& methodName, lua_CFunction func)
	{
		// className.metatable.methodName = func
		luaL_getmetatable(_state, className.c_str());
		lua_pushcfunction(_state, func);
		lua_setfield(_state, -2, methodName.c_str());

		// pop className.metatable
		lua_pop(_state, 1);
	}

	void BaseLua::registerGlobalVariable(const std::string& name, lua_Number value)
	{
		// _G[name] = value
		lua_pushnumber(_state, value);
		lua_setglobal(_state, name.c_str());
	}

	void BaseLua::registerGlobalBoolean(const std::string& name, bool value)
	{
		// _G[name] = value
		pushBoolean(_state, value);
		lua_setglobal(_state, name.c_str());
	}

	void BaseLua::registerGlobalMethod(const std::string& functionName, lua_CFunction func)
	{
		// _G[functionName] = func
		lua_pushcfunction(_state, func);
		lua_setglobal(_state, functionName.c_str());
	}

	void BaseLua::registerVariable(const std::string& tableName, const std::string& name, lua_Number value)
	{
		// tableName.name = value
		lua_getglobal(_state, tableName.c_str());
		setField(_state, name.c_str(), value);

		// pop tableName
		lua_pop(_state, 1);
	}

#pragma endregion

#pragma region Get/Sets

#pragma region Push

	void BaseLua::pushString(lua_State* L, const std::string& value)
	{
		lua_pushlstring(L, value.c_str(), value.length());
	}
	void BaseLua::pushCallback(lua_State* L, int32_t callback)
	{
		lua_rawgeti(L, LUA_REGISTRYINDEX, callback);
	}
	void BaseLua::pushBoolean(lua_State* L, bool value)
	{
		lua_pushboolean(L, value ? 1 : 0);
	}

	void BaseLua::pushPosition(lua_State* L, const sf::Vector2f& position)
	{
		lua_createtable(L, 0, 2);

		setField(L, "x", position.x);
		setField(L, "y", position.y);
		setMetatable(L, -1, "Position");
	}

#pragma endregion

#pragma region Pop

	std::string BaseLua::popString(lua_State* L)
	{
		if (lua_gettop(L) == 0) {
			return std::string();
		}

		std::string str(getString(L, -1));
		lua_pop(L, 1);
		return str;
	}

	int32_t BaseLua::popCallback(lua_State* L)
	{
		return luaL_ref(L, LUA_REGISTRYINDEX);
	}

#pragma endregion

#pragma region Get
	std::string BaseLua::getString(lua_State* L, int32_t arg)
	{
		size_t len;
		const char* c_str = lua_tolstring(L, arg, &len);
		if (!c_str || len == 0) {
			return std::string();
		}
		return std::string(c_str, len);
	}

	sf::Vector2f BaseLua::getPosition(lua_State* L, int32_t arg)
	{
		sf::Vector2f position;
		position.x = getField<float>(L, arg, "x");
		position.y = getField<float>(L, arg, "y");

		lua_pop(L, 2);
		return position;
	}


#pragma endregion

#pragma endregion

#pragma region Error handling
	int BaseLua::protectedCall(lua_State* L, int nargs, int nresults)
	{
		int error_index = lua_gettop(L) - nargs;
		lua_pushcfunction(L, luaErrorHandler);
		lua_insert(L, error_index);

		int ret = lua_pcall(L, nargs, nresults, error_index);
		lua_remove(L, error_index);
		return ret;
	}

	int BaseLua::luaErrorHandler(lua_State* L)
	{
		const std::string& errorMessage = popString(L);
		pushString(L, g_BaseLua.getStackTrace(errorMessage));
		se::Tools::Print(errorMessage, false);
		return 1;
	}

	void BaseLua::reportError(const char* function, const std::string& error_desc, bool stack_trace/* = false*/)
	{
		/*
		int32_t scriptId;
		int32_t callbackId;
		bool timerEvent;
		*/
		//Tools::Print(g_Locals.GetString("BaseLuaError"), false);

		if (function) {
			se::Tools::Print(function + std::string("()\n"), false);
		}

		if (stack_trace) {
			se::Tools::Print(g_BaseLua.getStackTrace(error_desc) + "\n", false);
		}
		else {
			se::Tools::Print(error_desc + "\n", false);
		}
	}

	std::string BaseLua::getStackTrace(const std::string& error_desc)
	{
		lua_getglobal(_state, "debug");
		if (!isTable(_state, -1)) {
			lua_pop(_state, 1);
			return error_desc;
		}

		lua_getfield(_state, -1, "traceback");
		if (!isFunction(_state, -1)) {
			lua_pop(_state, 2);
			return error_desc;
		}

		lua_replace(_state, -2);
		pushString(_state, error_desc);
		lua_call(_state, 1, 1);
		return popString(_state);
	}

#pragma endregion
	void BaseLua::printError(const std::string* variableName, const std::string* reason)
	{
		std::cout << "Error: can't get [" << variableName << "]. " << reason << std::endl;
	}

	void BaseLua::RunScript(std::string script, std::string entryPoint)
	{
		//Load script file
		loadFile(script.c_str());

		//Select the entry point
		lua_getglobal(_state, entryPoint.c_str());

		//Call it
		protectedCall(_state, 0, 0);

		//close the script file
		int n = lua_gettop(_state);
		lua_pop(_state, n);
	}

	void BaseLua::UpdateTime(std::string script, std::string entry, int32_t mSeconds)
	{
		//Load script file
		loadFile(script.c_str());

		//Select the entry point
		lua_getglobal(_state, entry.c_str());

		lua_pushinteger(_state, mSeconds);
		//Call it
		protectedCall(_state, 1, 0);

		//close the script file
		int n = lua_gettop(_state);
		lua_pop(_state, n);
	}


	int BaseLua::RunCommand(std::string script, std::string command, std::string params)
	{
		//Load script file
		loadFile(script.c_str());
		//lua_pcall(_state, 0, 0, 0);
		//Select the entry point
		lua_getglobal(_state, "RunCommand");

		pushString(_state, command);
		pushString(_state, params);
		//Call it
		protectedCall(_state, 2, 1);



		//close the script file
		int n = lua_gettop(_state);
		lua_pop(_state, n);



		return 0;
	}

}
