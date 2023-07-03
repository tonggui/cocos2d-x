#include "lua_cocos2dx_quick_manual.hpp"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"


int lua_cocos2dx_Node_getCascadeBoundingBox(lua_State* tolua_S)
{
	int argc = 0;
	cocos2d::Node* cobj = nullptr;
	bool ok = true;

#if COCOS2D_DEBUG >= 1
	tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
	if (!tolua_isusertype(tolua_S, 1, "cc.Node", 0, &tolua_err)) goto tolua_lerror;
#endif

	cobj = (cocos2d::Node*)tolua_tousertype(tolua_S, 1, 0);

#if COCOS2D_DEBUG >= 1
	if (!cobj)
	{
		tolua_error(tolua_S, "invalid 'cobj' in function 'lua_cocos2dx_Node_getCascadeBoundingBox'", nullptr);
		return 0;
	}
#endif

	argc = lua_gettop(tolua_S) - 1;
	if (argc == 0)
	{
		if (!ok)
			return 0;
		cocos2d::Rect ret = utils::getCascadeBoundingBox(cobj);
		rect_to_luaval(tolua_S, ret);
		return 1;
	}
	CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCascadeBoundingBox", argc, 0);
	return 0;

#if COCOS2D_DEBUG >= 1
tolua_lerror:
	tolua_error(tolua_S, "#ferror in function 'lua_cocos2dx_Node_getCascadeBoundingBox'.", &tolua_err);
#endif

	return 0;
}

static void extendNode(lua_State* tolua_S)
{
	lua_pushstring(tolua_S, "cc.Node");
	lua_rawget(tolua_S, LUA_REGISTRYINDEX);
	if (lua_istable(tolua_S, -1))
	{
		lua_pushstring(tolua_S, "getCascadeBoundingBox");
		lua_pushcfunction(tolua_S, lua_cocos2dx_Node_getCascadeBoundingBox);
		lua_rawset(tolua_S, -3);
	}
	lua_pop(tolua_S, 1);
}

static int tolua_Cocos2d_Function_loadChunksFromZIP(lua_State* tolua_S)
{
	return LuaEngine::getInstance()->getLuaStack()->luaLoadChunksFromZIP(tolua_S);
}

static void extendFunctions(lua_State* tolua_S)
{
	tolua_module(tolua_S, "cc", 0);
	tolua_beginmodule(tolua_S, "cc");
	tolua_function(tolua_S, "LuaLoadChunksFromZIP", tolua_Cocos2d_Function_loadChunksFromZIP);
	tolua_endmodule(tolua_S);
}

int register_all_quick_manual(lua_State* tolua_S)
{
	if (nullptr == tolua_S)
		return 0;

	extendFunctions(tolua_S);
	extendNode(tolua_S);
	CCLOG("Quick-Cocos2d-x C++ support ready.");

	return 0;
}