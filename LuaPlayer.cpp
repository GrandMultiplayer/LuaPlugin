#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <cstdint>
#include <vector>
#include <map>
#include <chrono>
#include <atomic>

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
#include "LuaVehicle.h"
#include "LuaNpc.h"
#include "LuaObject.h"
#include "LuaPlayer.h"

int Player::GetVehicle(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 1)
	{
		Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
		lua_pop(L, args);

		Vehicle veh;
		veh.entity = API::Player::GetVehicle(ent->entity);

		push(L, veh);

		ent = nullptr;
	}
	else
	{
		lua_pop(L, args);
		API::Log::Warning("Player:GetVehicle requires no args.");
		lua_pushnil(L);
	}
	return 1;
}

int Player::PutInVehicle(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 3)
	{
		Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
		Vehicle* veh = luabridge::Userdata::get<Vehicle>(L, 2, false);

		API::Player::PutInVehicle(ent->entity, veh->entity, lua_tointeger(L, 3));

		ent = nullptr;
		veh = nullptr;
	}
	else
	{
		API::Log::Warning("Player:PutInVehicle requires args (Vehicle vehicle, int seat).");
	}
	lua_pop(L, args);
	return 0;
}

int Player::ShowBlip(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
		Player* player = luabridge::Userdata::get<Player>(L, 2, false);

		API::Blip::Show(ent->entity, player->entity);

		ent = nullptr;
		player = nullptr;
	}
	else
	{
		API::Log::Warning("Player:ShowBlip requires arg (Player player).");
	}
	lua_pop(L, args);
	return 0;
}

int Player::HideBlip(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
		Player* player = luabridge::Userdata::get<Player>(L, 2, false);

		API::Blip::Hide(ent->entity, player->entity);

		ent = nullptr;
		player = nullptr;
	}
	else
	{
		API::Log::Warning("Player:HideBlip requires arg (Player player).");
	}
	lua_pop(L, args);
	return 0;
}

int Player::AttachCamera(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args >= 4)
	{
		Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

		//(Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)
		const int type = lua_tointeger(L, 2);
		CVector3 offset;

		if (args == 4)
		{
			if (lua_isuserdata(L, 4))
			{
				Vector3* pos = luabridge::Userdata::get<Vector3>(L, 4, false);
				offset = { pos->coord[0], pos->coord[1], pos->coord[2] };
				pos = nullptr;
			}
			else if (lua_istable(L, 4))
			{
				lua_getfield(L, 4, "x");
				lua_rawgeti(L, 4, 1);
				offset.x = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 4, "y");
				lua_rawgeti(L, 4, 1);
				offset.y = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 4, "z");
				lua_rawgeti(L, 4, 1);
				offset.z = lua_tonumber(L, -2);
				lua_pop(L, 1);
			}
		}
		else
		{
			offset.x = lua_tonumber(L, 4);
			offset.y = lua_tonumber(L, 5);
			offset.z = lua_tonumber(L, 6);
		}

		if (type == 0)
		{
			Player *entity = luabridge::Userdata::get<Player>(L, 3, false);
			API::Camera::Attach(ent->entity, entity->entity, offset);
			entity = nullptr;
		}
		else if (type == 1)
		{
			Vehicle *entity = luabridge::Userdata::get<Vehicle>(L, 3, false);
			API::Camera::Attach(ent->entity, entity->entity, offset);
			entity = nullptr;
		}
		else if (type == 2)
		{
			Object *entity = luabridge::Userdata::get<Object>(L, 3, false);
			API::Camera::Attach(ent->entity, entity->entity, offset);
			entity = nullptr;
		}
		else if (type == 3)
		{
			NPC *entity = luabridge::Userdata::get<NPC>(L, 3, false);
			API::Camera::Attach(ent->entity, entity->entity, offset);
			entity = nullptr;
		}
		else
		{
			API::Log::Warning("Player:AttachCamera can only be types 0 (Player), 1 (Vehicle), 2 (Object) or 3 (NPC).");
		}

		ent = nullptr;
	}
	else
	{
		API::Log::Warning("Player:AttachCamera requires args (type, entity, table{x = float, y = float, z = float} offset).");
	}

	lua_pop(L, args);
	return 0;
}