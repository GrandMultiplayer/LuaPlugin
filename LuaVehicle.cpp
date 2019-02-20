#include "sdk/GrandM.h"

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

std::unordered_map<std::string, luabridge::LuaRef> getKeyValueMap(const luabridge::LuaRef& table)
{
	using namespace luabridge;
	std::unordered_map<std::string, LuaRef> result;
	if (table.isNil()) { return result; }

	auto L = table.state();
	push(L, table); // push table

	lua_pushnil(L);  // push nil, so lua_next removes it from stack and puts (k, v) on stack

	while (lua_next(L, -2) != 0)
	{ // -2, because we have table at -1
		if (lua_isstring(L, -2))
		{ // only store stuff with string keys
			result.emplace(lua_tostring(L, -2), LuaRef::fromStack(L, -1));
		}
		lua_pop(L, 1); // remove value, keep key for lua_next
	}

	lua_pop(L, 1); // pop table
	return result;
}

int Vehicle::Create(lua_State* L)
{
	/*
	Arg 1: The pointer of the Object
	Arg 2+: The arguments entered
	*/
	const int args = lua_gettop(L);
	if (args == 4)
	{
		Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
		std::string model = lua_tostring(L, 2);
		CVector3 poss;
		CVector3 rott;

		if (lua_isuserdata(L, 3))
		{
			Vector3 *pos = luabridge::Userdata::get<Vector3>(L, 3, false);
			poss = { pos->coord[0], pos->coord[1], pos->coord[2] };
			pos = nullptr;
		}
		else if (lua_istable(L, 3))
		{
			// Table Vec3
			luabridge::LuaRef param = luabridge::LuaRef::fromStack(L, 3);

			for (auto& pair : getKeyValueMap(param))
			{
				auto& key = pair.first;
				auto& value = pair.second;

				if (key == "x")
				{
					if (value.isNumber())
					{
						poss.x = value.cast<float>();
					}
				}
				else if (key == "y")
				{
					if (value.isNumber())
					{
						poss.y = value.cast<float>();
					}
				}
				else if (key == "z")
				{
					if (value.isNumber())
					{
						poss.z = value.cast<float>();
					}
				}
			}
			// End Table Vec3

			/*lua_getfield(L, 3, "x");
			lua_rawgeti(L, 3, 1);
			poss.x = lua_tonumber(L, -2);
			lua_pop(L, 1);

			lua_getfield(L, 3, "y");
			lua_rawgeti(L, 3, 1);
			poss.y = lua_tonumber(L, -2);
			lua_pop(L, 1);

			lua_getfield(L, 3, "z");
			lua_rawgeti(L, 3, 1);
			poss.z = lua_tonumber(L, -2);
			lua_pop(L, 1);*/

		}

		if (lua_isuserdata(L, 4))
		{
			Vector3 *rot = luabridge::Userdata::get<Vector3>(L, 3, false);
			rott = { rot->coord[0], rot->coord[1], rot->coord[2] };
			rot = nullptr;
		}
		else if (lua_istable(L, 4))
		{
			lua_getfield(L, 4, "x");
			lua_rawgeti(L, 4, 1);
			rott.x = lua_tonumber(L, -2);
			lua_pop(L, 1);

			lua_getfield(L, 4, "y");
			lua_rawgeti(L, 4, 1);
			rott.y = lua_tonumber(L, -2);
			lua_pop(L, 1);

			lua_getfield(L, 4, "z");
			lua_rawgeti(L, 4, 1);
			rott.z = lua_tonumber(L, -2);
			lua_pop(L, 1);
		}

		Objects::Entity entity;

		if (lua_isnumber(L, 4))
			entity = API::Vehicle::Create(model.c_str(), poss, lua_tonumber(L, 4));
		else
			entity = API::Vehicle::Create(model.c_str(), poss, rott);

		ent->entity = entity.GetID();

		ent = nullptr;
	}
	else
	{
		API::Log::Warning("Vehicle:Create requires args (string model, table position{x = float, y = float, z = float}, [table rotation{x = float, y = float, z = float} OR float heading]).");
	}
	lua_pop(L, args);
	return 0;
}


int Vehicle::GetOccupant(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

		Objects::Entity entity;
		entity.SetID(ent->entity);
		entity.SetType(GrandM::EntityType::Vehicle);

		Objects::Entity occupant = API::Vehicle::GetOccupant(entity, lua_tointeger(L, 2));
		lua_pop(L, args);

		switch (occupant.GetType())
		{
		case GrandM::Player:
		{
			Player ent;
			ent.entity = occupant.GetID();
			push(L, ent);
			break;
		}
		case GrandM::NPC:
		{
			NPC ent;
			ent.entity = occupant.GetID();
			push(L, ent);
			break;
		}
		default:
			lua_pushnil(L);
			break;
		}

		ent = nullptr;
	}
	else
	{
		lua_pop(L, args);
		API::Log::Warning("Vehicle:GetOccupant requires args (int seat).");
		lua_pushnil(L);
	}
	return 1;
}

int Vehicle::GetOccupants(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 1)
	{
		Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
		lua_pop(L, args);

		Objects::Entity entity;
		entity.SetID(ent->entity);
		entity.SetType(GrandM::EntityType::Vehicle);

		Objects::Entity * occupants = API::Vehicle::GetOccupants(entity);

		const int arraySize = (int)(sizeof(occupants) / sizeof(occupants[0]));

		lua_newtable(L);
		for (unsigned int i = 0; i < arraySize; i++)
		{
			switch (occupants[i].GetType())
			{
			case GrandM::Player: {
				Player ent;
				ent.entity = occupants[i].GetID();
				push(L, ent);
				break;
			}
			case GrandM::NPC: {
				NPC ent;
				ent.entity = occupants[i].GetID();
				push(L, ent);
				break;
			}
			default:
				lua_pushnil(L);
				break;
			}

			lua_rawseti(L, -2, i + 1);
		}

		ent = nullptr;
	}
	else
	{
		lua_pop(L, args);
		API::Log::Warning("Vehicle:GetOccupants requires no args.");
		lua_pushnil(L);
	}
	return 1;
}

int Vehicle::SetDoorsLockStateForPlayer(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
		Player *player = luabridge::Userdata::get<Player>(L, 2, false);

		Objects::Entity entity;
		entity.SetID(ent->entity);
		entity.SetType(GrandM::EntityType::Vehicle);

		Objects::Entity pEntity;
		entity.SetID(player->entity);
		entity.SetType(GrandM::EntityType::Player);

		API::Vehicle::SetDoorsLockStateForPlayer(entity, lua_tointeger(L, 2), pEntity);

		ent = nullptr;
		player = nullptr;
	}
	else
	{
		API::Log::Warning("Vehicle:SetDoorsLockStateForPlayer requires args (int state, Player player).");
	}
	lua_pop(L, args);
	return 0;
}

int Vehicle::ShowBlip(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
		Player *player = luabridge::Userdata::get<Player>(L, 2, false);

		Objects::Entity entity;
		entity.SetID(ent->entity);
		entity.SetType(GrandM::EntityType::Vehicle);

		Objects::Entity pEntity;
		entity.SetID(player->entity);
		entity.SetType(GrandM::EntityType::Player);

		API::Blip::Show(entity, pEntity);

		ent = nullptr;
		player = nullptr;
	}
	else
	{
		API::Log::Warning("Vehicle:ShowBlip requires arg (Player player).");
	}
	lua_pop(L, args);
	return 0;
}

int Vehicle::HideBlip(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
		Player *player = luabridge::Userdata::get<Player>(L, 2, false);

		Objects::Entity entity;
		entity.SetID(ent->entity);
		entity.SetType(GrandM::EntityType::Vehicle);

		Objects::Entity pEntity;
		entity.SetID(player->entity);
		entity.SetType(GrandM::EntityType::Player);

		API::Blip::Hide(entity, pEntity);

		ent = nullptr;
		player = nullptr;
	}
	else
	{
		API::Log::Warning("Vehicle:HideBlip requires arg (Player player).");
	}
	lua_pop(L, args);
	return 0;
}