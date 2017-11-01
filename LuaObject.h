#ifndef __LUAOBJECT_H__
#define __LUAOBJECT_H__

struct Object
{
	int entity;
	const int type = 2; // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)

	Object()
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
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);

			std::string model;
			int hash = -1;
			CVector3 poss;
			CVector3 rott;

			if (lua_isstring(L, 2))
				model = lua_tostring(L, 2);
			else
				hash = lua_tointeger(L, 2);

			if (lua_isuserdata(L, 3))
			{
				Vector3* pos = luabridge::Userdata::get<Vector3>(L, 3, false);
				poss = { pos->coord[0], pos->coord[1], pos->coord[2] };
				pos = nullptr;
			}
			else if (lua_istable(L, 3))
			{
				lua_getfield(L, 3, "x");
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
				lua_pop(L, 1);
			}

			if (lua_isuserdata(L, 4))
			{
				Vector3* rot = luabridge::Userdata::get<Vector3>(L, 4, false);
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

			bool dynamic = lua_toboolean(L, 5);
			
			if (lua_isnumber(L, 2))
				ent->entity = API::Object::Create(hash, poss, rott, dynamic);
			else
				ent->entity = API::Object::Create(model, poss, rott, dynamic);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:Create requires args (sting model, position table {x = float, y = float, z = float}, rotation table{x = float, y = float, z = float}, bool dynamic).");
		}
		lua_pop(L, args);
		return 0;
	}

	int Destroy(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);
			API::Entity::Destroy(ent->entity);
			ent->entity = -1;
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:Destroy requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);
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
			API::Log::Warning("Object:GetPosition requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);
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
			API::Log::Warning("Object:SetPosition requires args (table{x = float, y = float, z = float}) OR (float x, float y, float z).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetRotation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);
			lua_pop(L, args);

			CVector3 rot = API::Entity::GetRotation(ent->entity);
			/*Vec pos(poss.x, poss.y, poss.z);
			lua_pushlightuserdata(L, &pos);*/
			lua_newtable(L);

			lua_pushinteger(L, rot.x);
			lua_setfield(L, -2, "x");

			lua_pushinteger(L, rot.y);
			lua_setfield(L, -2, "y");

			lua_pushinteger(L, rot.z);
			lua_setfield(L, -2, "z");


			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Object:GetRotation requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetRotation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);
			CVector3 rott;

			if (args == 2)
			{
				if (lua_isuserdata(L, 2))
				{
					Vector3* rot = luabridge::Userdata::get<Vector3>(L, 2, false);
					rott = { rot->coord[0], rot->coord[1], rot->coord[2] };
					rot = nullptr;
				}
				else if (lua_istable(L, 2))
				{
					lua_getfield(L, 2, "x");
					lua_rawgeti(L, 2, 1);
					rott.x = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "y");
					lua_rawgeti(L, 2, 1);
					rott.y = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "z");
					lua_rawgeti(L, 2, 1);
					rott.z = lua_tonumber(L, -2);
					lua_pop(L, 1);
				}
			}
			else
			{
				rott.x = lua_tonumber(L, 2);
				rott.x = lua_tonumber(L, 3);
				rott.x = lua_tonumber(L, 4);
			}

			API::Entity::SetRotation(ent->entity, rott);
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:SetRotation requires args (table{x = float, y = float, z = float}) OR (float x, float y, float z).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);
			lua_pop(L, args);

			const float distance = API::Entity::GetViewDistance(ent->entity);

			lua_pushnumber(L, distance);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Object:GetViewDistance requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);

			const float distance = lua_tonumber(L, 2);

			API::Entity::SetViewDistance(ent->entity, distance);
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:SetViewDistance requires args (float distance).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetTextureVariation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);
			lua_pop(L, args);

			const int texture = API::Object::GetTextureVariation(ent->entity);

			lua_pushinteger(L, texture);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Object:GetTextureVariation requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetTextureVariation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);

			API::Object::SetTextureVariation(ent->entity, lua_tointeger(L, 2));
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:SetTextureVariation requires args (int texture).");
		}
		lua_pop(L, args);
		return 0;
	}

	int CreateBlip(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);

			API::Blip::Create(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:CreateBlip requires no args.");
			lua_pushnil(L);
		}
		lua_pop(L, args);
		return 0;
	}

	int ShowBlip(lua_State* L);
	int HideBlip(lua_State* L);

	int ShowBlipToAll(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);

			API::Blip::ShowToAll(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:ShowBlipToAll requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int HideBlipFromAll(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);

			API::Blip::HideFromAll(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:HideBlipFromAll requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);

			const int color = API::Blip::GetColor(ent->entity);
			lua_pop(L, args);

			lua_pushinteger(L, color);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:GetBlipColor requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);

			API::Blip::SetColor(ent->entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:SetBlipColor requires arg (int color).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipSprite(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);

			const int sprite = API::Blip::GetSprite(ent->entity);
			lua_pop(L, args);

			lua_pushinteger(L, sprite);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:GetBlipSprite requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipSprite(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);

			API::Blip::SetSprite(ent->entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:SetBlipSprite requires arg (int sprite).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipText(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);

			const std::string text = API::Blip::GetText(ent->entity);
			lua_pop(L, args);

			lua_pushstring(L, text.c_str());

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:GetBlipText requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipText(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);

			API::Blip::SetText(ent->entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:SetBlipText requires arg (string text).");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsBlipShortRanged(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);
			lua_pop(L, args);

			const bool state = API::Blip::IsShortRanged(ent->entity);

			lua_pushboolean(L, state);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Object:IsBlipShortRanged requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipShortRanged(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Object* ent = luabridge::Userdata::get<Object>(L, 1, false);

			API::Blip::SetShortRanged(ent->entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:SetBlipShortRanged requires arg (bool state).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetHealth(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object *ent = luabridge::Userdata::get<Object>(L, 1, false);
			lua_pop(L, args);

			lua_pushinteger(L, API::Entity::GetHealth(ent->entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Object:GetHealth requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetHealth(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Object *ent = luabridge::Userdata::get<Object>(L, 1, false);

			API::Entity::SetHealth(ent->entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:SetHealth requires arg (int health).");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsAlive(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Object *ent = luabridge::Userdata::get<Object>(L, 1, false);
			lua_pop(L, args);

			lua_pushboolean(L, API::Entity::IsAlive(ent->entity));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Object:IsAlive requires no args.");
		}
		return 1;
	}
};
#endif