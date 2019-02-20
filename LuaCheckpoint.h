#ifndef __LUACHECKPOINT_H__
#define __LUACHECKPOINT_H__

struct Checkpoint
{
	int entity;
	const int type = 4; // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)

	Checkpoint()
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
		if (args == 5)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			CVector3 poss;
			CVector3 pointt;

			// Position
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
			
			// Radius
			const float radius = lua_tonumber(L, 3);
			// Color
			Color col;
			if (lua_istable(L, 4))
			{
				lua_getfield(L, 4, "r");
				lua_rawgeti(L, 4, 1);
				col.Red = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 4, "g");
				lua_rawgeti(L, 4, 1);
				col.Green = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 4, "b");
				lua_rawgeti(L, 4, 1);
				col.Blue = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 4, "a");
				lua_rawgeti(L, 4, 1);
				col.Alpha = lua_tonumber(L, -2);
				lua_pop(L, 1);
			}
			// Reserved
			const int reserved = lua_tonumber(L, 5);

			Objects::Entity entity = API::Checkpoint::Create(poss, radius, col, reserved);
			ent->entity = entity.GetID();

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:Create requires args (position table{x = float, y = float, z = float}, float radius, table color{r = int, g = int, b = int, a = int}, int reserved).");
		}
		lua_pop(L, args);
		return 0;
	}

	int Destroy(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Entity::Destroy(entity);
			ent->entity = -1;
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:Destroy requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

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
			API::Log::Warning("Checkpoint:GetPosition requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
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
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Entity::SetPosition(entity, poss);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:SetPosition requires args (table{x = float, y = float, z = float}) OR (float x, float y, float z).");
		}
		lua_pop(L, args);
		return 0;
	}

	int Show(lua_State* L);
	int Hide(lua_State* L);

	int GetNearHeight(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			float height = API::Checkpoint::GetNearHeight(entity);
			
			lua_pushnumber(L, height);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Checkpoint:GetNearHeight requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetNearHeight(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Checkpoint::SetNearHeight(entity, lua_tonumber(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:SetNearHeight requires args (float height).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetFarHeight(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			float height = API::Checkpoint::GetFarHeight(entity);

			lua_pushnumber(L, height);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Checkpoint:GetFarHeight requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetFarHeight(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			const float height = lua_tonumber(L, 2);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Checkpoint::SetFarHeight(entity, height);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:SetFarHeight requires args (float height).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			const float distance = API::Entity::GetViewDistance(entity);

			lua_pushnumber(L, distance);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Checkpoint:GetViewDistance requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			const float distance = lua_tonumber(L, 2);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Entity::SetViewDistance(entity, distance);
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:SetViewDistance requires args (float distance).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPointTo(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			CVector3 pointTo = API::Checkpoint::GetPointTo(entity);

			lua_newtable(L);

			lua_pushinteger(L, pointTo.x);
			lua_setfield(L, -2, "x");

			lua_pushinteger(L, pointTo.y);
			lua_setfield(L, -2, "y");

			lua_pushinteger(L, pointTo.z);
			lua_setfield(L, -2, "z");


			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Checkpoint:GetPointTo requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int PointTo(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
			CVector3 pointTo;

			if (args == 2)
			{
				if (lua_istable(L, 2))
				{
					lua_getfield(L, 2, "x");
					lua_rawgeti(L, 2, 1);
					pointTo.x = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "y");
					lua_rawgeti(L, 2, 1);
					pointTo.y = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "z");
					lua_rawgeti(L, 2, 1);
					pointTo.z = lua_tonumber(L, -2);
					lua_pop(L, 1);
				}
			}
			else
			{
				pointTo.x = lua_tonumber(L, 2);
				pointTo.x = lua_tonumber(L, 3);
				pointTo.x = lua_tonumber(L, 4);
			}

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Checkpoint::PointTo(entity, pointTo);
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:PointTo requires args (table{x = float, y = float, z = float}).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetType(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);
			
			lua_pushinteger(L, API::Checkpoint::GetType(entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Checkpoint:GetType requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetType(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Checkpoint::SetType(entity, lua_tointeger(L, 2));
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:SetType requires args (int type).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			const Color color = API::Checkpoint::GetColor(entity);

			lua_newtable(L);

			lua_pushinteger(L, color.Red);
			lua_setfield(L, -2, "r");

			lua_pushinteger(L, color.Green);
			lua_setfield(L, -2, "g");

			lua_pushinteger(L, color.Blue);
			lua_setfield(L, -2, "b");

			lua_pushinteger(L, color.Alpha);
			lua_setfield(L, -2, "a");

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Checkpoint:GetColor requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 5)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
			Color color;

			color.Red = lua_tointeger(L, 2);
			color.Green = lua_tointeger(L, 3);
			color.Blue = lua_tointeger(L, 4);
			color.Alpha = lua_tointeger(L, 5);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Checkpoint::SetColor(entity, color);
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:SetColor requires args (int r, int g, int b, int a).");
		}
		lua_pop(L, args);
		return 0;
	}

	int CreateBlip(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Blip::Create(entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:CreateBlip requires no args.");
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
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Blip::ShowToAll(entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:ShowBlipToAll requires arg ().");
		}
		lua_pop(L, args);
		return 0;
	}

	int HideBlipFromAll(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Blip::HideFromAll(entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:HideBlipFromAll requires arg ().");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			const int color = API::Blip::GetColor(entity);

			lua_pushinteger(L, color);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Checkpoint:GetBlipColor requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Blip::SetColor(entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:SetBlipColor requires arg (int color).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipSprite(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			const int sprite = API::Blip::GetSprite(entity);
			lua_pop(L, args);

			lua_pushinteger(L, sprite);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Checkpoint:GetBlipSprite requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipSprite(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Blip::SetSprite(entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:SetBlipSprite requires arg (int sprite).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipText(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			const std::string text = API::Blip::GetText(entity);
			lua_pop(L, args);

			lua_pushstring(L, text.c_str());

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Checkpoint:GetBlipText requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipText(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Blip::SetText(entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:SetBlipText requires arg (string text).");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsBlipShortRanged(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			const bool state = API::Blip::IsShortRanged(entity);
			lua_pop(L, args);

			lua_pushboolean(L, state);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Checkpoint:IsBlipShortRanged requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipShortRanged(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Checkpoint* ent = luabridge::Userdata::get<Checkpoint>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Checkpoint);

			API::Blip::SetShortRanged(entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Checkpoint:SetBlipShortRanged requires arg (bool state).");
		}
		lua_pop(L, args);
		return 0;
	}
};

#endif