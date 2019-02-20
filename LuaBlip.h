#ifndef __LUABLIP_H__
#define __LUABLIP_H__

struct Blip 
{
	int entity;
	const int type = 5; // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)

	Blip()
	{
		entity = -1;
	}

	int Create(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);

			CVector3 pos = CVector3();

			if (lua_istable(L, 2))
			{
				lua_getfield(L, 2, "x");
				lua_rawgeti(L, 2, 1);
				pos.x = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 2, "y");
				lua_rawgeti(L, 2, 1);
				pos.y = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 2, "z");
				lua_rawgeti(L, 2, 1);
				pos.z = lua_tonumber(L, -2);
				lua_pop(L, 1);

			}

			Objects::Entity entity = API::Blip::Create(pos);

			ent->entity = entity.GetID();

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Blip:Create requires arg (table{x = float, y = float, z = float}).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Blip);

			CVector3 poss = API::Entity::GetPosition(entity);
			/*Vec pos(poss.x, poss.y, poss.z);
			lua_pushlightuserdata(L, &pos);*/
			lua_newtable(L);

			lua_pushinteger(L, poss.x);
			lua_setfield(L, -2, "x");

			lua_pushinteger(L, poss.y);
			lua_setfield(L, -2, "y");

			lua_pushinteger(L, poss.z);
			lua_setfield(L, -2, "z");


			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Blip:GetPosition requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);
			CVector3 poss;

			if (args == 2)
			{
				if (lua_isuserdata(L, 2))
				{
					Vector3* pos = luabridge::Userdata::get<Vector3>(L, 2, false);
					poss = { pos->coord[0], pos->coord[1], pos->coord[2] };
					pos = nullptr;
				}
				else if (lua_istable(L, 2))
				{
					lua_getfield(L, 2, "x");
					lua_rawgeti(L, 2, 1);
					poss.x = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "y");
					lua_rawgeti(L, 2, 1);
					poss.y = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "z");
					lua_rawgeti(L, 2, 1);
					poss.z = lua_tonumber(L, -2);
					lua_pop(L, 1);
				}
			}
			else
			{
				poss.x = lua_tonumber(L, 2);
				poss.x = lua_tonumber(L, 3);
				poss.x = lua_tonumber(L, 4);
			}

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Blip);

			API::Entity::SetPosition(entity, poss);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Blip:SetPosition requires args (table{x = float, y = float, z = float}) OR (float x, float y, float z).");
		}
		lua_pop(L, args);
		return 0;
	}

	int Show(lua_State* L);
	int Hide(lua_State* L);

	int ShowToAll(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Blip);

			API::Blip::ShowToAll(entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Blip:ShowToAll requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int HideFromAll(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Blip);

			API::Blip::HideFromAll(entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Blip:HideFromAll requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Blip);

			const int color = API::Blip::GetColor(entity);

			lua_pushinteger(L, color);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Blip:GetColor requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Blip);

			API::Blip::SetColor(entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Blip:SetColor requires arg (int color).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetSprite(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Blip);

			const int sprite = API::Blip::GetSprite(entity);

			lua_pushinteger(L, sprite);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Blip:GetSprite requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetSprite(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Blip);

			API::Blip::SetSprite(entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Blip:SetSprite requires arg (int sprite).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetText(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Blip);

			const std::string text = API::Blip::GetText(entity);

			lua_pushstring(L, text.c_str());

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Blip:GetText requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetText(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Blip);

			API::Blip::SetText(entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Blip:SetText requires arg (string text).");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsShortRanged(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Blip);

			const bool state = API::Blip::IsShortRanged(entity);

			lua_pushboolean(L, state);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Blip:IsShortRanged requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetShortRanged(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Blip* ent = luabridge::Userdata::get<Blip>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Blip);

			API::Blip::SetShortRanged(entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Blip:SetShortRanged requires arg (bool state).");
		}
		lua_pop(L, args);
		return 0;
	}
};
#endif