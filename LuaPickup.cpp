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
#include "LuaPickup.h"

int Pickup::Show(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Pickup* ent = luabridge::Userdata::get<Pickup>(L, 1, false);
		Player* player = luabridge::Userdata::get<Player>(L, 2, false);

		Objects::Entity entity;
		entity.SetID(ent->entity);
		entity.SetType(GrandM::EntityType::Pickup);

		Objects::Entity pEntity;
		pEntity.SetID(player->entity);
		pEntity.SetType(GrandM::EntityType::Player);

		API::Pickup::Show(entity, pEntity);

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

		Objects::Entity entity;
		entity.SetID(ent->entity);
		entity.SetType(GrandM::EntityType::Pickup);

		Objects::Entity pEntity;
		pEntity.SetID(player->entity);
		pEntity.SetType(GrandM::EntityType::Player);

		API::Pickup::Hide(entity, pEntity);

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