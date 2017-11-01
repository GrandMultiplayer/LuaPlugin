#ifndef __LUAPICKUP_H__
#define __LUAPICKUP_H__

struct Pickup
{
	int entity;
	const int type = 6; // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5, Pickup = 6)

	Pickup()
	{
		entity = -1;
	}

	int Create(lua_State* L)
	{
		/*
		Arg 1: The pointer of the Object
		Arg 2+: The arguments entered
		*/
		const int args = lua_gettop(L);
		if (args == 4)
		{
			Pickup* ent = luabridge::Userdata::get<Pickup>(L, 1, false);

			std::string model;
			CVector3 poss;

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

			
			ent->entity = API::Pickup::Create(poss, luaL_optstring(L, 3, "prop_ld_health_pack"));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Pickup:Create requires args (position table {x = float, y = float, z = float}, string model).");
		}
		lua_pop(L, args);
		return 0;
	}

	int Destroy(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Pickup* ent = luabridge::Userdata::get<Pickup>(L, 1, false);
			API::Entity::Destroy(ent->entity);
			ent->entity = -1;
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Pickup:Destroy requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int ShowToAll(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Pickup* ent = luabridge::Userdata::get<Pickup>(L, 1, false);
			API::Pickup::ShowToAll(ent->entity);
			
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Pickup:ShowToAll requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int Show(lua_State* L);

	int HideFromAll(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Pickup* ent = luabridge::Userdata::get<Pickup>(L, 1, false);
			API::Pickup::HideFromAll(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Pickup:HideFromAll requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int Hide(lua_State* L);

	int GetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Pickup* ent = luabridge::Userdata::get<Pickup>(L, 1, false);
			lua_pop(L, args);

			CVector3 poss = API::Entity::GetPosition(ent->entity);
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
			API::Log::Warning("Pickup:GetPosition requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Pickup* ent = luabridge::Userdata::get<Pickup>(L, 1, false);
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

			API::Entity::SetPosition(ent->entity, poss);
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Pickup:SetPosition requires args (table{x = float, y = float, z = float}) OR (float x, float y, float z).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetModel(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Pickup* ent = luabridge::Userdata::get<Pickup>(L, 1, false);

			lua_pushstring(L, API::Pickup::GetModel(ent->entity).c_str());

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Pickup:GetModel requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int SetModel(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Pickup* ent = luabridge::Userdata::get<Pickup>(L, 1, false);

			API::Pickup::SetModel(ent->entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Pickup:SetModel requires args (string model).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetRespawnDelay(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Pickup* ent = luabridge::Userdata::get<Pickup>(L, 1, false);

			lua_pushinteger(L, API::Pickup::GetRespawnDelay(ent->entity));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Pickup:GetRespawnDelay requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int SetRespawnDelay(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Pickup* ent = luabridge::Userdata::get<Pickup>(L, 1, false);

			API::Pickup::SetRespawnDelay(ent->entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Pickup:SetRespawnDelay requires args (int time(MS)).");
		}
		lua_pop(L, args);
		return 0;
	}

};

#endif