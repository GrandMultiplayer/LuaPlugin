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
#include "sdk/APIPickup.h"
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
#include "LuaPickup.h"

int Pickup::Show(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Pickup* ent = luabridge::Userdata::get<Pickup>(L, 1, false);
		Player* player = luabridge::Userdata::get<Player>(L, 2, false);

		API::Pickup::Show(ent->entity, player->entity);

		player = nullptr;
		ent = nullptr;
	}
	else
	{
		API::Log::Warning("Pickup:Show requires args (Player player).");
	}
	lua_pop(L, args);
	return 0;
}

int Pickup::Hide(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Pickup* ent = luabridge::Userdata::get<Pickup>(L, 1, false);
		Player* player = luabridge::Userdata::get<Player>(L, 2, false);

		API::Pickup::Hide(ent->entity, player->entity);

		player = nullptr;
		ent = nullptr;
	}
	else
	{
		API::Log::Warning("Pickup:Hide requires args (Player player).");
	}
	lua_pop(L, args);
	return 0;
}