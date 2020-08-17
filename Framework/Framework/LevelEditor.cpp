#include "LevelEditor.h"

//setup the lua file which we want to read.
lua_State* LevelEditor::setupLuaFile(const char* luaFileName) // this cuntion is the requisite preamble for reading in a certain lua file
{
	lua_State* F = luaL_newstate(); 
	luaL_dofile(F, luaFileName);
	luaL_openlibs(F);
	lua_pcall(F, 0, 0, 0);
	return F;
}

// luaFileRef - pass in lua file we want to use / luaStackHead - Head of stack we want to read / luaStackProperty - which property to read
LuaRef LevelEditor::getLuaStackProperty(lua_State* luaFileRef, const char* luaStackHead, const char* luaStackProperty) // the file "f", the first indetation, the value we read in
{
	LuaRef luaStackHeader = getGlobal(luaFileRef, luaStackHead); //get global funtion retuns lua refernce to header
	return luaStackHeader[luaStackProperty]; // returning the read in value
}
