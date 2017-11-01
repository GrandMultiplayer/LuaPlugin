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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			API::Entity::Destroy(veh->entity);
			veh->entity = -1;
			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			CVector3 poss = API::Entity::GetPosition(veh->entity);
			lua_pop(L, args);

			/*Vec pos(poss.x, poss.y, poss.z);
			lua_pushlightuserdata(L, &pos);*/
			lua_newtable(L);

			lua_pushinteger(L, poss.x);
			lua_setfield(L, -2, "x");

			lua_pushinteger(L, poss.y);
			lua_setfield(L, -2, "y");

			lua_pushinteger(L, poss.z);
			lua_setfield(L, -2, "z");


			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
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

			API::Entity::SetPosition(veh->entity, poss);
			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			CVector3 rot = API::Entity::GetRotation(veh->entity);
			lua_pop(L, args);
			/*Vec pos(poss.x, poss.y, poss.z);
			lua_pushlightuserdata(L, &pos);*/
			lua_newtable(L);

			lua_pushinteger(L, rot.x);
			lua_setfield(L, -2, "x");

			lua_pushinteger(L, rot.y);
			lua_setfield(L, -2, "y");

			lua_pushinteger(L, rot.z);
			lua_setfield(L, -2, "z");


			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
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

			API::Entity::SetRotation(veh->entity, rott);
			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			const float distance = API::Entity::GetViewDistance(veh->entity);
			lua_pop(L, args);

			lua_pushnumber(L, distance);

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			API::Entity::SetViewDistance(veh->entity, lua_tonumber(L, 2));
			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			const int color = API::Vehicle::GetColor(veh->entity, lua_tointeger(L, 2));
			lua_pop(L, args);

			lua_pushinteger(L, color);

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			const int type = API::Vehicle::GetColorType(veh->entity, lua_tointeger(L, 2));
			lua_pop(L, args);

			lua_pushinteger(L, type);

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			const Color color = API::Vehicle::GetCustomColor(veh->entity, lua_tointeger(L, 2));
			lua_pop(L, args);

			lua_newtable(L);

			lua_pushinteger(L, color.Red);
			lua_setfield(L, -2, "r");

			lua_pushinteger(L, color.Green);
			lua_setfield(L, -2, "g");

			lua_pushinteger(L, color.Blue);
			lua_setfield(L, -2, "b");

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			API::Vehicle::SetColor(veh->entity, lua_tointeger(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4));
			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
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

			API::Vehicle::SetColor(veh->entity, lua_tointeger(L, 2), color);
			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			lua_pushstring(L, API::Vehicle::GetNumberPlate(veh->entity).c_str());

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			
			API::Vehicle::SetNumberPlate(veh->entity, lua_tostring(L,2));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			lua_pushinteger(L, API::Vehicle::GetMod(veh->entity, lua_tointeger(L, 2)));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			API::Vehicle::SetMod(veh->entity, lua_tointeger(L, 2), lua_tointeger(L, 3));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			lua_pushboolean(L, API::Vehicle::GetEngineState(veh->entity));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			API::Vehicle::SetEngineState(veh->entity, lua_toboolean(L, 2), lua_toboolean(L, 3));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			lua_pushinteger(L, API::Vehicle::GetDoorsLockState(veh->entity));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			API::Vehicle::SetDoorsLockState(veh->entity, lua_tointeger(L, 2));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			lua_pushstring(L, API::Vehicle::GetModel(veh->entity).c_str());

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			lua_pushinteger(L, API::Vehicle::GetNumberPlateStyle(veh->entity));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			
			API::Vehicle::SetNumberPlateStyle(veh->entity, lua_tointeger(L, 2));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			lua_pushboolean(L, API::Vehicle::GetExtra(veh->entity, lua_tointeger(L,2)));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			API::Vehicle::SetExtra(veh->entity, lua_tointeger(L, 2), lua_toboolean(L,3));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			lua_pushnumber(L, API::Vehicle::GetEngineHealth(veh->entity));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			API::Vehicle::SetEngineHealth(veh->entity, lua_tonumber(L, 2));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			lua_pushnumber(L, API::Vehicle::GetFuelTankHealth(veh->entity));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			API::Vehicle::SetFuelTankHealth(veh->entity, lua_tonumber(L, 2));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			API::Vehicle::FixDeformation(veh->entity);

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			lua_pushboolean(L, API::Vehicle::GetTaxiLightState(veh->entity));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			API::Vehicle::SetTaxiLightState(veh->entity, lua_toboolean(L,2));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			lua_pushboolean(L, API::Vehicle::GetIndicatorState(veh->entity, lua_tonumber(L,2)));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			API::Vehicle::SetIndicatorState(veh->entity, lua_tointeger(L,2), lua_toboolean(L, 3));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			lua_pushboolean(L, API::Vehicle::GetInteriorLightState(veh->entity));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			API::Vehicle::SetInteriorLightState(veh->entity, lua_toboolean(L, 2));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			lua_pushboolean(L, API::Vehicle::GetSirenSoundState(veh->entity));

			veh = nullptr;
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
			Vehicle *veh = luabridge::Userdata::get<Vehicle>(L, 1, false);

			API::Vehicle::SetSirenSoundState(veh->entity, lua_toboolean(L, 2));

			veh = nullptr;
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

			API::Blip::Create(ent->entity);

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

			API::Blip::ShowToAll(ent->entity);

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

			API::Blip::HideFromAll(ent->entity);

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

			const int color = API::Blip::GetColor(ent->entity);
			lua_pop(L, args);

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

			API::Blip::SetColor(ent->entity, lua_tointeger(L, 2));

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

			const int sprite = API::Blip::GetSprite(ent->entity);
			lua_pop(L, args);

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

			API::Blip::SetSprite(ent->entity, lua_tointeger(L, 2));

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

			const std::string text = API::Blip::GetText(ent->entity);
			lua_pop(L, args);

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

			API::Blip::SetText(ent->entity, lua_tostring(L, 2));

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

			const bool state = API::Blip::IsShortRanged(ent->entity);
			lua_pop(L, args);

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

			API::Blip::SetShortRanged(ent->entity, lua_toboolean(L, 2));

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

			lua_pushinteger(L, API::Entity::GetHealth(ent->entity));

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

			API::Entity::SetHealth(ent->entity, lua_tointeger(L, 2));

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

			lua_pushboolean(L, API::Entity::IsAlive(ent->entity));

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

			const int vehicle = API::Vehicle::GetTowedVehicle(ent->entity);

			if (vehicle > -1)
			{
				Vehicle ent;
				ent.entity = vehicle;
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
			Vehicle *tow = luabridge::Userdata::get<Vehicle>(L, 1, false);
			Vehicle *vehicle = luabridge::Userdata::get<Vehicle>(L, 1, false);
			lua_pop(L, args);

			API::Vehicle::SetTowedVehicle(tow->entity, vehicle->entity);

			tow = vehicle = nullptr;
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

			lua_pushboolean(L, API::Vehicle::IsTowed(ent->entity));

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