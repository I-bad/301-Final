#pragma once
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <LuaBridge\LuaBridge.h>

using namespace luabridge;

class LevelEditor
{
public:
	LevelEditor() {}
	~LevelEditor() {}

	//setup the lua file which we want to read.
	lua_State* setupLuaFile(const char* luaFileName); //init a lua file

	// luaFileRef - pass in lua file we want to use / luaStackHead - Head of stack we want to use / luaStackProperty - which property to read
	LuaRef getLuaStackProperty(lua_State* luaFileRef, const char* luaStackHead, const char* luaStackProperty);
};
