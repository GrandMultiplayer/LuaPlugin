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
#include "LuaBlip.h"

int Blip::Show(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);
		Player* player = luabridge::Userdata::get<Player>(L, 2, false);

		Objects::Entity entity;
		entity.SetID(ent->entity);
		entity.SetType(GrandM::EntityType::Blip);

		Objects::Entity pEntity;
		entity.SetID(player->entity);
		entity.SetType(GrandM::EntityType::Player);

		API::Blip::Show(entity, pEntity);

		ent = nullptr;
		player = nullptr;
	}
	else
	{
		API::Log::Warning("Blip:Show requires arg (Player player).");
	}
	lua_pop(L, args);
	return 0;
}

int Blip::Hide(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);
		Player* player = luabridge::Userdata::get<Player>(L, 2, false);

		Objects::Entity entity;
		entity.SetID(ent->entity);
		entity.SetType(GrandM::EntityType::Blip);

		Objects::Entity pEntity;
		entity.SetID(player->entity);
		entity.SetType(GrandM::EntityType::Player);

		API::Blip::Hide(entity, pEntity);

		ent = nullptr;
		player = nullptr;
	}
	else
	{
		API::Log::Warning("Blip:Hide requires arg (Player player).");
	}
	lua_pop(L, args);
	return 0;
}