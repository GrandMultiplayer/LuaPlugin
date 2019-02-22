#ifndef __LUAVEHICLE_H__
#define __LUAVEHICLE_H__

struct Vehicle
{
	int entity;
	const int type = 1; // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)

	Vehicle()
	{
		entity = -1;
	}

	int Create(lua_State* L);

	int Destroy(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Entity::Destroy(entity);
			
			ent->entity = -1;
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle.Destroy requires no args");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

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
			API::Log::Warning("Vehicle.GetPosition requires no args");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			CVector3 poss;

			if (args == 2)
			{
				if (lua_isuserdata(L, 2))
				{
					Vector3 *pos = luabridge::Userdata::get<Vector3>(L, 2, false);
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
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Entity::SetPosition(entity, poss);
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle.SetPosition requires args ([table{x = float, y = float, z = float} OR (float x, float y, float z)]).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetRotation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			CVector3 rot = API::Entity::GetRotation(entity);
			
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
			API::Log::Warning("Vehicle.GetRotation requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetRotation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			CVector3 rott;

			if (args == 2)
			{
				if (lua_isuserdata(L, 2))
				{
					Vector3 *rot = luabridge::Userdata::get<Vector3>(L, 2, false);
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

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Entity::SetRotation(entity, rott);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle.SetRotation requires args ([table{x = float, y = float, z = float} OR (float x, float y, float z)]).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			const float distance = API::Entity::GetViewDistance(entity);

			lua_pushnumber(L, distance);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle.GetViewDistance requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Entity::SetViewDistance(entity, lua_tonumber(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle.SetViewDistance requires args (float distance).");
		}
		lua_pop(L, args);
		return 0;
	}
	
	int GetStandardColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			const int color = API::Vehicle::GetVehicleColor(entity, lua_tointeger(L, 2));
			lua_pop(L, args);

			lua_pushinteger(L, color);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:GetStandardColor requires args (int layer).");
			lua_pop(L, args);
			lua_pushnil(L);
		}
		return 1;
	}

	int GetStandardColorType(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			const int type = API::Vehicle::GetVehicleColorType(entity, lua_tointeger(L, 2));
			lua_pop(L, args);

			lua_pushinteger(L, type);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:GetStandardColorType requires args (int layer).");
			lua_pop(L, args);
			lua_pushnil(L);
		}
		return 1;
	}

	int GetCustomColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			const Color color = API::Vehicle::GetVehicleRGBColor(entity, lua_tointeger(L, 2));
			lua_pop(L, args);

			lua_newtable(L);

			lua_pushinteger(L, color.Red);
			lua_setfield(L, -2, "r");

			lua_pushinteger(L, color.Green);
			lua_setfield(L, -2, "g");

			lua_pushinteger(L, color.Blue);
			lua_setfield(L, -2, "b");

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:GetCustomColor requires args (int layer).");
			lua_pop(L, args);
			lua_pushnil(L);
		}
		return 1;
	}

	int SetStandardColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 4)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Vehicle::SetVehicleColor(entity, lua_tointeger(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4));
			
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetStandardColor requires args (int layer, int paintType, int color).");
		}
		lua_pop(L, args);
		return 0;
	}
	
	int SetCustomColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 5)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			Color color;

			lua_getfield(L, 3, "r");
			lua_rawgeti(L, 3, 1);
			color.Red = lua_tointeger(L, -2);
			lua_pop(L, 1);

			lua_getfield(L, 3, "g");
			lua_rawgeti(L, 3, 1);
			color.Green = lua_tointeger(L, -2);
			lua_pop(L, 1);

			lua_getfield(L, 3, "b");
			lua_rawgeti(L, 3, 1);
			color.Blue = lua_tointeger(L, -2);
			lua_pop(L, 1);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Vehicle::SetVehicleRGBColor(entity, lua_tointeger(L, 2), color);
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetCustomColor requires args (int layer, table color).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetNumberPlate(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushstring(L, API::Vehicle::GetNumberPlate(entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetNumberPlate requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetNumberPlate(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);
			
			API::Vehicle::SetNumberPlate(entity, lua_tostring(L,2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetNumberPlate requires args (string text).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetMod(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushinteger(L, API::Vehicle::GetMod(entity, lua_tointeger(L, 2)));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetMod requires args (int modType).");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetMod(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 3)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Vehicle::SetMod(entity, lua_tointeger(L, 2), lua_tointeger(L, 3));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetMod requires args (int modType, int modIndex).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetEngineState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushboolean(L, API::Vehicle::GetEngineState(entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetEngineState requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetEngineState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 3)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Vehicle::SetEngineState(entity, lua_toboolean(L, 2), lua_toboolean(L, 3));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetEngineState requires args (bool state, bool instant).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetDoorsLockState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushinteger(L, API::Vehicle::GetDoorsLockState(entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetDoorsLockState requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetDoorsLockState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Vehicle::SetDoorsLockState(entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetDoorsLockState requires args (int state).");
		}
		lua_pop(L, args);
		return 0;
	}

	int SetDoorsLockStateForPlayer(lua_State* L);

	int GetModel(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushstring(L, API::Vehicle::GetVehicleModel(entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetModel requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int GetNumberPlateStyle(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushinteger(L, API::Vehicle::GetNumberPlateStyle(entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetNumberPlateStyle requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetNumberPlateStyle(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);
			
			API::Vehicle::SetNumberPlateStyle(entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetNumberPlateStyle requires args (int style).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetExtra(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushboolean(L, API::Vehicle::GetExtra(entity, lua_tointeger(L,2)));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetExtra requires args (int extra(1-14)).");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetExtra(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 3)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Vehicle::SetExtra(entity, lua_tointeger(L, 2), lua_toboolean(L,3));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetExtra requires args (int extra(1-14), bool toggle).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetEngineHealth(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushnumber(L, API::Vehicle::GetEngineHealth(entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetEngineHealth requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetEngineHealth(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Vehicle::SetEngineHealth(entity, lua_tonumber(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetEngineHealth requires args (float health).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetFuelTankHealth(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushnumber(L, API::Vehicle::GetFuelTankHealth(entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetFuelTankHealth requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetFuelTankHealth(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Vehicle::SetFuelTankHealth(entity, lua_tonumber(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetFuelTankHealth requires args (float health).");
		}
		lua_pop(L, args);
		return 0;
	}

	int FixDeformation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Vehicle::FixDeformation(entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:FixDeformation requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetOccupant(lua_State* L);
	int GetOccupants(lua_State* L);

	int GetTaxiLightState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushboolean(L, API::Vehicle::GetTaxiLightState(entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetTaxiLightState requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetTaxiLightState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Vehicle::SetTaxiLightState(entity, lua_toboolean(L,2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetTaxiLightState requires args (bool state).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetIndicatorState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushboolean(L, API::Vehicle::GetIndicatorState(entity, lua_tonumber(L,2)));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetIndicatorState requires args (int turnlight).");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetIndicatorState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 3)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Vehicle::SetIndicatorState(entity, lua_tointeger(L,2), lua_toboolean(L, 3));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetIndicatorState requires args (int turnlight, bool state).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetInteriorLightState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushboolean(L, API::Vehicle::GetInteriorLightState(entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetInteriorLightState requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetInteriorLightState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Vehicle::SetInteriorLightState(entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetInteriorLightState requires args (bool state).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetSirenSoundState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushboolean(L, API::Vehicle::GetSirenSoundState(entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetSirenSoundState requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetSirenSoundState(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Vehicle::SetSirenSoundState(entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetSirenSoundState requires args (bool state).");
		}
		lua_pop(L, args);
		return 0;
	}

	int CreateBlip(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Blip::Create(entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:CreateBlip requires no args.");
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
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Blip::ShowToAll(entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:ShowBlipToAll requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int HideBlipFromAll(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Blip::HideFromAll(entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:HideBlipFromAll requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			const int color = API::Blip::GetColor(entity);

			lua_pushinteger(L, color);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetBlipColor requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Blip::SetColor(entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetBlipColor requires arg (int color).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipSprite(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			const int sprite = API::Blip::GetSprite(entity);

			lua_pushinteger(L, sprite);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetBlipSprite requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipSprite(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Blip::SetSprite(entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetBlipSprite requires arg (int sprite).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipText(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			const std::string text = API::Blip::GetText(entity);

			lua_pushstring(L, text.c_str());

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetBlipText requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipText(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Blip::SetText(entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetBlipText requires arg (string text).");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsBlipShortRanged(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			const bool state = API::Blip::IsShortRanged(entity);

			lua_pushboolean(L, state);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:IsBlipShortRanged requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipShortRanged(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Blip::SetShortRanged(entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetBlipShortRanged requires arg (bool state).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetHealth(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushinteger(L, API::Entity::GetHealth(entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Vehicle:GetHealth requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetHealth(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Entity::SetHealth(entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetHealth requires arg (int health).");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsAlive(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushboolean(L, API::Entity::IsAlive(entity));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:IsAlive requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int GetTowedVehicle(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			Objects::Entity vehicle = API::Vehicle::GetTowedVehicle(entity);

			if (vehicle.GetID() > -1)
			{
				Vehicle ent;
				ent.entity = vehicle.GetID();
				push(L, ent);
			}
			else
			{
				lua_pushnil(L);
			}
			
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:GetTowedVehicle requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetTowedVehicle(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			Vehicle *vehicle = luabridge::Userdata::get<Vehicle>(L, 2, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			Objects::Entity vEntity;
			entity.SetID(vehicle->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			API::Vehicle::SetTowedVehicle(entity, vEntity);

			ent = vehicle = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:SetTowedVehicle requires args (Vehicle).");
		}
		return 0;
	}

	int IsTowed(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Vehicle *ent = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			Objects::Entity entity;
			entity.SetID(ent->entity);
			entity.SetType(GrandM::EntityType::Vehicle);

			lua_pushboolean(L, API::Vehicle::IsTowed(entity));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Vehicle:IsTowed requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}
};
#endif