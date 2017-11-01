#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <cstdint>
#include <vector>
#include <map>

#include "api.h"

// Math
#include "sdk/CVector2.h"
#include "sdk/CVector3.h"
#include "sdk/CVector4.h"
#include "sdk/Plane.h"
#include "sdk/Quaternion.h"
#include "sdk/util.h"

#include "sdk/CMaths.h"
#include "sdk/Structs.h"

// API Function Imports
#include "sdk/APICef.h"
#include "sdk/APIVisual.h"
#include "sdk/APIWorld.h"
#include "sdk/APIEntity.h"
#include "sdk/APICheckpoint.h"
#include "sdk/APINpc.h"
#include "sdk/APIObject.h"
#include "sdk/APIPlayer.h"
#include "sdk/APIServer.h"
#include "sdk/APIVehicle.h"
#include "sdk/APIBlip.h"
#include "sdk/APICamera.h"
#include "sdk/APILog.h"

extern "C" {
#include "inc_lua/lua.h"
#include "inc_lua/lualib.h"
#include "inc_lua/lauxlib.h"
}

#include "LuaBridge/LuaBridge.h"
#include "LuaBridge/RefCountedPtr.h"
#include "LuaBridge/RefCountedObject.h"

using namespace luabridge;

// API Lua Functions
#include "LuaVector3.h"
#include "LuaPlayer.h"
#include "LuaNpc.h"
#include "LuaVehicle.h"
#include "LuaCheckpoint.h"

int Checkpoint::Show(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
		Player* player = luabridge::Userdata::get<Player>(L, 2, false);

		API::Checkpoint::Show(ent->entity, player->entity);

		ent = nullptr;
		player = nullptr;
	}
	else
	{
		API::Log::Warning("Checkpoint:Show requires args (Player player).");
	}
	lua_pop(L, args);
	return 0;
}

int Checkpoint::Hide(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
		Player* player = luabridge::Userdata::get<Player>(L, 2, false);

		API::Checkpoint::Hide(ent->entity, player->entity);

		ent = nullptr;
		player = nullptr;
	}
	else
	{
		API::Log::Warning("Checkpoint:Hide requires args (Player player).");
	}
	lua_pop(L, args);
	return 0;
}

int Checkpoint::ShowBlip(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
		Player* player = luabridge::Userdata::get<Player>(L, 2, false);

		API::Blip::Show(ent->entity, player->entity);

		ent = nullptr;
		player = nullptr;
	}
	else
	{
		API::Log::Warning("Checkpoint:ShowBlip requires arg (Player player).");
	}
	lua_pop(L, args);
	return 0;
}

int Checkpoint::HideBlip(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
		Player* player = luabridge::Userdata::get<Player>(L, 2, false);

		API::Blip::Hide(ent->entity, player->entity);

		ent = nullptr;
		player = nullptr;
	}
	else
	{
		API::Log::Warning("Checkpoint:HideBlip requires arg (Player player).");
	}
	lua_pop(L, args);
	return 0;
}