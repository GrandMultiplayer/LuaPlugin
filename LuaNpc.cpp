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
#include "LuaVehicle.h"
#include "LuaPlayer.h"
#include "LuaNpc.h"

int NPC::ShowBlip(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
		Player* player = luabridge::Userdata::get<Player>(L, 2, false);

		Objects::Entity entity;
		entity.SetID(ent->entity);
		entity.SetType(GrandM::EntityType::NPC);

		Objects::Entity pEntity;
		pEntity.SetID(player->entity);
		pEntity.SetType(GrandM::EntityType::Player);

		API::Blip::Show(entity, pEntity);

		ent = nullptr;
		player = nullptr;
	}
	else
	{
		API::Log::Warning("NPC:ShowBlip requires arg (Player player).");
	}
	lua_pop(L, args);
	return 0;
}

int NPC::HideBlip(lua_State* L)
{
	const int args = lua_gettop(L);
	if (args == 2)
	{
		NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
		Player* player = luabridge::Userdata::get<Player>(L, 2, false);

		Objects::Entity entity;
		entity.SetID(ent->entity);
		entity.SetType(GrandM::EntityType::NPC);

		Objects::Entity pEntity;
		pEntity.SetID(player->entity);
		pEntity.SetType(GrandM::EntityType::Player);

		API::Blip::Hide(entity, pEntity);

		ent = nullptr;
		player = nullptr;
	}
	else
	{
		API::Log::Warning("NPC:HideBlip requires arg (Player player).");
	}
	lua_pop(L, args);
	return 0;
}