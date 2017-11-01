#ifndef __LUANPC_H__
#define __LUANPC_H__

struct NPC
{
	int entity;
	const int type = 3; // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)

	NPC()
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
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			std::string model = lua_tostring(L, 2);
			CVector3 poss;
			CVector3 rott;

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
			
			ent->entity = API::NPC::Create(model, poss, rott);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:Create requires args (sting model, position table{x = float, y = float, z = float}, rotation table{x = float, y = float, z = float}).");
		}
		lua_pop(L, args);
		return 0;
	}

	int Destroy(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
			API::Entity::Destroy(ent->entity);
			ent->entity = -1;
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:Destroy requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
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
			API::Log::Warning("NPC:GetPosition requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
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
			API::Log::Warning("NPC:SetPosition requires args (table{x = float, y = float, z = float}) OR (float x, float y, float z).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetRotation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
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
			API::Log::Warning("NPC:GetRotation requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetRotation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
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
			API::Log::Warning("NPC:SetRotation requires args (table{x = float, y = float, z = float}) OR (float x, float y, float z).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
			lua_pop(L, args);

			const float distance = API::Entity::GetViewDistance(ent->entity);

			lua_pushnumber(L, distance);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:GetViewDistance requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Entity::SetViewDistance(ent->entity, lua_tonumber(L, 2));
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetViewDistance requires args (float distance).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPedComponent(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			PedComponent comp = API::Entity::GetPedComponent(ent->entity, lua_tointeger(L, 2));
			lua_pop(L, args);

			lua_newtable(L);

			lua_pushinteger(L, comp.drawableid);
			lua_setfield(L, -2, "drawableid");

			lua_pushinteger(L, comp.paletteid);
			lua_setfield(L, -2, "paletteid");

			lua_pushinteger(L, comp.textureid);
			lua_setfield(L, -2, "textureid");

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:GetPedComponent requires args (int index).");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPedComponent(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 3)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
			const int index = lua_tointeger(L, 2);

			PedComponent comp;

			if (lua_istable(L, 3))
			{
				lua_getfield(L, 3, "drawableid");
				lua_rawgeti(L, 3, 1);
				comp.drawableid = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 3, "paletteid");
				lua_rawgeti(L, 3, 1);
				comp.paletteid = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 3, "textureid");
				lua_rawgeti(L, 3, 1);
				comp.textureid = lua_tonumber(L, -2);
				lua_pop(L, 1);
			}

			API::Entity::SetPedComponent(ent->entity, index, comp);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetPedComponent requires args (int componentid, table{drawableid = int, paletteid = int, textureid = int}).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPedHeadBlend(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
			lua_pop(L, args);

			PedHeadBlend blend = API::Entity::GetPedHeadBlend(ent->entity);

			lua_newtable(L);
			//table{shapefirst = int, shapesecond = int, shapethird = int, skinfirst = int, skinsecond = int, skinthird = int, shapemix = float, skinmix = float, thirdmix = float}
			lua_pushinteger(L, blend.shapeFirst);
			lua_setfield(L, -2, "shapefirst");

			lua_pushinteger(L, blend.shapeSecond);
			lua_setfield(L, -2, "shapesecond");

			lua_pushinteger(L, blend.shapeThird);
			lua_setfield(L, -2, "shapethird");

			lua_pushinteger(L, blend.skinFirst);
			lua_setfield(L, -2, "skinfirst");

			lua_pushinteger(L, blend.skinSecond);
			lua_setfield(L, -2, "skinsecond");

			lua_pushinteger(L, blend.skinThird);
			lua_setfield(L, -2, "skinthird");

			lua_pushnumber(L, blend.shapeMix);
			lua_setfield(L, -2, "shapemix");

			lua_pushnumber(L, blend.skinMix);
			lua_setfield(L, -2, "skinmix");

			lua_pushnumber(L, blend.thirdMix);
			lua_setfield(L, -2, "thirdmix");

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:GetPedHeadBlend requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPedHeadBlend(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 2)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			PedHeadBlend headblend;
			
			if (lua_istable(L, 2))
			{
				lua_getfield(L, 2, "shapefirst");
				lua_rawgeti(L, 2, 1);
				headblend.shapeFirst = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 2, "shapesecond");
				lua_rawgeti(L, 2, 1);
				headblend.shapeSecond = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 2, "shapethird");
				lua_rawgeti(L, 2, 1);
				headblend.shapeThird = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 2, "skinfirst");
				lua_rawgeti(L, 2, 1);
				headblend.skinFirst = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 2, "skinsecond");
				lua_rawgeti(L, 2, 1);
				headblend.skinSecond = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 2, "skinthird");
				lua_rawgeti(L, 2, 1);
				headblend.skinThird = lua_tonumber(L, -2);
				lua_pop(L, 1);
				
				lua_getfield(L, 2, "shapemix");
				lua_rawgeti(L, 2, 1);
				headblend.shapeMix = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 2, "skinmix");
				lua_rawgeti(L, 2, 1);
				headblend.skinMix = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 2, "thirdmix");
				lua_rawgeti(L, 2, 1);
				headblend.thirdMix = lua_tonumber(L, -2);
				lua_pop(L, 1);
			}

			API::Entity::SetPedHeadBlend(ent->entity, headblend);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetPedHeadBlend requires args (table{shapefirst = int, shapesecond = int, shapethird = int, skinfirst = int, skinsecond = int, skinthird = int, shapemix = float, skinmix = float, thirdmix = float}).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPedHeadOverlay(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			PedHeadOverlay overlay = API::Entity::GetPedHeadOverlay(ent->entity, lua_tointeger(L, 2));
			lua_pop(L, args);

			lua_newtable(L);
			//table{index = int, opacity = float, colortype = int, colorid = int, secondcolorid = int}
			lua_pushinteger(L, overlay.index);
			lua_setfield(L, -2, "index");

			lua_pushnumber(L, overlay.opacity);
			lua_setfield(L, -2, "shapesecond");

			lua_pushinteger(L, overlay.colorType);
			lua_setfield(L, -2, "colortype");

			lua_pushinteger(L, overlay.colorID);
			lua_setfield(L, -2, "colorid");

			lua_pushinteger(L, overlay.secondColorID);
			lua_setfield(L, -2, "secondcolorid");

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:GetPedHeadOverlay requires args (int overlayeid).");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPedHeadOverlay(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 2)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			const int overlayid = lua_tointeger(L, 2);

			PedHeadOverlay overlay;

			if (lua_istable(L, 3))
			{
				//table{index = int, opacity = float, colortype = int, colorid = int, secondcolorid = int}
				lua_getfield(L, 3, "index");
				lua_rawgeti(L, 3, 1);
				overlay.index = lua_tointeger(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 3, "opacity");
				lua_rawgeti(L, 3, 1);
				overlay.opacity = lua_tonumber(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 3, "colortype");
				lua_rawgeti(L, 3, 1);
				overlay.colorType = lua_tointeger(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 3, "colorid");
				lua_rawgeti(L, 3, 1);
				overlay.colorID = lua_tointeger(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 3, "secondcolorid");
				lua_rawgeti(L, 3, 1);
				overlay.secondColorID = lua_tointeger(L, -2);
				lua_pop(L, 1);

				
			}

			API::Entity::SetPedHeadOverlay(ent->entity, overlayid, overlay);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetPedHeadOverlay requires args (int overlayid, table{index = int, opacity = float, colortype = int, colorid = int, secondcolorid = int}).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPedProp(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			PedProp prop = API::Entity::GetPedProp(ent->entity, lua_tointeger(L, 2));
			lua_pop(L, args);

			lua_newtable(L);
			//table{drawableid = int, textureid = int}
			lua_pushinteger(L, prop.drawableid);
			lua_setfield(L, -2, "drawableid");

			lua_pushnumber(L, prop.textureid);
			lua_setfield(L, -2, "textureid");

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:GetPedProp requires args (int componentid).");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPedProp(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 2)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			const int componentid = lua_tointeger(L, 2);

			PedProp prop;

			if (lua_istable(L, 3))
			{
				//table{drawableid = int, textureid = int}
				lua_getfield(L, 3, "drawableid");
				lua_rawgeti(L, 3, 1);
				prop.drawableid = lua_tointeger(L, -2);
				lua_pop(L, 1);

				lua_getfield(L, 3, "textureid");
				lua_rawgeti(L, 3, 1);
				prop.textureid = lua_tointeger(L, -2);
				lua_pop(L, 1);
			}

			API::Entity::SetPedProp(ent->entity, componentid, prop);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetPedProp requires args (int componentid, table{drawableid = int, textureid = int}).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPedFaceFeature(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			float scale = API::Entity::GetPedFaceFeature(ent->entity, lua_tointeger(L, 2));
			lua_pop(L, args);

			lua_pushnumber(L, scale);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:GetPedFaceFeature requires args (int feature).");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPedFaceFeature(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 2)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Entity::SetPedFaceFeature(ent->entity, lua_tointeger(L, 2), lua_tonumber(L, 3));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetPedFaceFeature requires args (int feature, float scale).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetNametag(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
			lua_pop(L, args);

			lua_pushstring(L, API::Entity::GetNametag(ent->entity).c_str());

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:GetNametag requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetNametag(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Entity::SetNametag(ent->entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetNametag requires args (string nametag)");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsNametagVisible(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
			lua_pop(L, args);

			lua_pushboolean(L, API::Entity::IsNametagVisible(ent->entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:IsNametagVisible requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetNametagVisible(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Entity::SetNametagVisible(ent->entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetNametag requires args (bool visible)");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsHealthbarVisible(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
			lua_pop(L, args);

			lua_pushboolean(L, API::Entity::IsHealthbarVisible(ent->entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:IsHealthbarVisible requires no args.");
		}
		return 1;
	}

	int SetHealthbarVisible(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Entity::SetHealthbarVisible(ent->entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetHealthbarVisible requires args (bool visible)");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetNametagDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
			lua_pop(L, args);

			lua_pushnumber(L, API::Entity::GetNametagDistance(ent->entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:GetNametagDistance requires no args.");
		}
		return 1;
	}

	int SetNametagDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Entity::SetNametagDistance(ent->entity, lua_tonumber(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetNametagDistance requires args (float distance)");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetNametagColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);
			lua_pop(L, args);

			Color color = API::Entity::GetNametagColor(ent->entity);

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
			API::Log::Warning("NPC:GetNametagColor requires no args.");
		}
		return 1;
	}

	int SetNametagColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			Color color;

			lua_getfield(L, 2, "r");
			lua_rawgeti(L, 2, 1);
			color.Red = lua_tointeger(L, -2);
			lua_pop(L, 1);

			lua_getfield(L, 2, "g");
			lua_rawgeti(L, 2, 1);
			color.Green = lua_tointeger(L, -2);
			lua_pop(L, 1);

			lua_getfield(L, 2, "b");
			lua_rawgeti(L, 2, 1);
			color.Blue = lua_tointeger(L, -2);
			lua_pop(L, 1);

			lua_getfield(L, 2, "a");
			lua_rawgeti(L, 2, 1);
			color.Alpha = lua_tointeger(L, -2);
			lua_pop(L, 1);

			API::Entity::SetNametagColor(ent->entity, color);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetNametagColor requires args (table color)");
		}
		lua_pop(L, args);
		return 0;
	}

	int CreateBlip(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Blip::Create(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:CreateBlip requires no args.");
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
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Blip::ShowToAll(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:ShowBlipToAll requires arg ().");
		}
		lua_pop(L, args);
		return 0;
	}

	int HideBlipFromAll(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Blip::HideFromAll(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:HideBlipFromAll requires arg ().");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			const int color = API::Blip::GetColor(ent->entity);
			lua_pop(L, args);

			lua_pushinteger(L, color);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:GetBlipColor requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Blip::SetColor(ent->entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetBlipColor requires arg (int color).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipSprite(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			const int sprite = API::Blip::GetSprite(ent->entity);
			lua_pop(L, args);

			lua_pushinteger(L, sprite);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:GetBlipSprite requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipSprite(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Blip::SetSprite(ent->entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetBlipSprite requires arg (int sprite).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipText(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			const std::string text = API::Blip::GetText(ent->entity);
			lua_pop(L, args);

			lua_pushstring(L, text.c_str());

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:GetBlipText requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipText(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Blip::SetText(ent->entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetBlipText requires arg (string text).");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsBlipShortRanged(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			const bool state = API::Blip::IsShortRanged(ent->entity);
			lua_pop(L, args);

			lua_pushboolean(L, state);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:IsBlipShortRanged requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipShortRanged(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			NPC* ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Blip::SetShortRanged(ent->entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetBlipShortRanged requires arg (bool state).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetHealth(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC *ent = luabridge::Userdata::get<NPC>(L, 1, false);
			lua_pop(L, args);

			lua_pushinteger(L, API::Entity::GetHealth(ent->entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:GetHealth requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetHealth(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			NPC *ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Entity::SetHealth(ent->entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetHealth requires arg (int health).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetArmour(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC *ent = luabridge::Userdata::get<NPC>(L, 1, false);
			lua_pop(L, args);

			lua_pushinteger(L, API::Entity::GetArmour(ent->entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("NPC:GetArmour requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetArmour(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			NPC *ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Entity::SetArmour(ent->entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:SetArmour requires arg (int armour).");
		}
		lua_pop(L, args);
		return 0;
	}

	int Revive(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC *ent = luabridge::Userdata::get<NPC>(L, 1, false);

			API::Entity::Revive(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:Revive requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsAlive(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			NPC *ent = luabridge::Userdata::get<NPC>(L, 1, false);
			lua_pop(L, args);

			lua_pushboolean(L, API::Entity::IsAlive(ent->entity));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("NPC:IsAlive requires no args.");
		}
		return 1;
	}
};
#endif