#ifndef __LUAPLAYER_H__
#define __LUAPLAYER_H__

struct Player
{
	int entity;
	const int type = 0; // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)

	Player()
	{
		entity = -1;
	}

	int GetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
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
			API::Log::Warning("Player:GetPosition requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
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
				poss.y = lua_tonumber(L, 3);
				poss.z = lua_tonumber(L, 4);
			}

			API::Entity::SetPosition(ent->entity, poss);
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetPosition requires args ([table{x = float, y = float, z = float} OR (float x, float y, float z)]).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetRotation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
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
			API::Log::Warning("Player:GetRotation requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetRotation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2 || args == 4)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
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
			API::Log::Warning("Player:SetRotation requires args ([table{x = float, y = float, z = float} OR (float x, float y, float z)]).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			const float distance = API::Entity::GetViewDistance(ent->entity);

			lua_pushnumber(L, distance);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:GetViewDistance requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetViewDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Entity::SetViewDistance(ent->entity, lua_tonumber(L, 2));
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetViewDistance requires args (float distance).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPedComponent(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

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
			API::Log::Warning("Player:GetPedComponent requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPedComponent(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 3)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
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
			API::Log::Warning("Player:SetPedComponent requires args (int componentid, table{drawableid = int, paletteid = int, textureid = int}).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPedHeadBlend(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
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
			API::Log::Warning("Player:GetPedHeadBlend requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPedHeadBlend(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

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
			API::Log::Warning("Player:SetPedHeadBlend requires args table{shapefirst = int, shapesecond = int, shapethird = int, skinfirst = int, skinsecond = int, skinthird = int, shapemix = float, skinmix = float, thirdmix = float}.");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPedHeadOverlay(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

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
			API::Log::Warning("Player:GetPedHeadOverlay requires args (int overlayid).");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPedHeadOverlay(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 3)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

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
			API::Log::Warning("Player:SetPedHeadOverlay requires args (int overlayid, table{index = int, opacity = float, colortype = int, colorid = int, secondcolorid = int}).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPedProp(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

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
			API::Log::Warning("Player:GetPedProp requires args (int componentid).");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPedProp(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

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
			API::Log::Warning("Player:SetPedProp requires args (int componentid, table{drawableid = int, textureid = int}).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetPedFaceFeature(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			float scale = API::Entity::GetPedFaceFeature(ent->entity, lua_tointeger(L, 2));
			lua_pop(L, args);

			lua_pushnumber(L, scale);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:GetPedFaceFeature requires args (int feature).");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetPedFaceFeature(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 3)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Entity::SetPedFaceFeature(ent->entity, lua_tointeger(L, 2), lua_tonumber(L, 3));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:GetPedFaceFeature requires args (int feature, float scale).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetModel(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			std::string model = API::Player::GetModel(ent->entity);

			lua_pushstring(L, model.c_str());

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:GetModel requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetModel(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Player::SetModel(ent->entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetModel requires args (string model).");
		}
		lua_pop(L, args);
		return 0;
	}

	int ShowNotification(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 5)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			
			API::Visual::ShowNotificationToPlayer(ent->entity, lua_tostring(L, 2), lua_tostring(L, 3), lua_tointeger(L, 4), lua_tointeger(L, 5), lua_tostring(L, 6), lua_tostring(L, 7));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:ShowNotification requires args (string message, string pic, int icontype, int color, string sender, string subject).");
			lua_pushnil(L);
		}
		lua_pop(L, args);
		return 0;
	}

	int LoadIPL(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::World::LoadIPL(ent->entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:LoadIPL requires args (string ipl).");
		}
		lua_pop(L, args);
		return 0;
	}

	int UnloadIPL(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::World::UnloadIPL(ent->entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:UnloadIPL requires args (string ipl).");
		}
		lua_pop(L, args);
		return 0;
	}

	int SendChatMessage(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			API::Visual::SendChatMessageToPlayer(ent->entity, lua_tostring(L, 2));
			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SendChatMessage requires args (string message).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetUsername(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			lua_pushstring(L, API::Player::GetUsername(ent->entity).c_str());

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:GetUsername requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int ShowCursor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			 API::Visual::ShowCursor(ent->entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:ShowCursor requires args (bool show).");
		}
		lua_pop(L, args);
		return 0;
	}
	
	int LoadURL(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			std::string appcode = "";
			bool remote = false;

			if (lua_isstring(L, 3))
				appcode = lua_tostring(L, 3);

			if (lua_isboolean(L, 4))
				remote = lua_toboolean(L, 4);

			API::CEF::LoadURL(ent->entity, lua_tostring(L, 2), appcode, remote);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:LoadURL requires args (string url, OPTIONAL[string appcode = "", bool remote = false]).");
		}
		lua_pop(L, args);
		return 0;
	}
	
	int JavaScriptCall(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::CEF::JavaScriptCall(ent->entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:JavaScriptCall requires args (string call).");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsControllable(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			lua_pushboolean(L, API::Player::IsControllable(ent->entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:IsControllable requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetControllable(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			bool frozen = true;
			if (lua_isboolean(L, 3))
				frozen = lua_toboolean(L, 3);

			API::Player::SetControllable(ent->entity, lua_toboolean(L, 2), frozen);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetControllable requires args (bool disable, OPTIONAL[bool frozen = true]).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetIP(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			lua_pushstring(L, API::Player::GetIP(ent->entity).c_str());

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:GetIP requires args ().");
			lua_pushnil(L);
		}
		return 1;
	}

	int GetSecretKey(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			lua_pushstring(L, API::Player::GetSecretKey(ent->entity).c_str());

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:GetSecretKey requires args ().");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetUsername(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Player::SetUsername(ent->entity, lua_tostring(L,2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetUsername requires args (string name).");
		}
		lua_pop(L, args);
		return 0;
	}

	int Kick(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Player::Kick(ent->entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:Kick requires args (string reason).");
		}
		lua_pop(L, args);
		return 0;
	}

	int ShowSubtitle(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 4)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Visual::ShowSubtitleToPlayer(ent->entity, lua_tostring(L, 2), lua_tointeger(L, 3), lua_toboolean(L, 4));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:ShowSubtitle requires args (string message, int duration, bool shownow).");
		}
		lua_pop(L, args);
		return 0;
	}

	int PutInVehicle(lua_State* L);
	int GetVehicle(lua_State* L);

	int GetSeat(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			lua_pushinteger(L, API::Player::GetSeat(ent->entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:GetSeat requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int GiveWeapon(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			
			API::Player::GiveWeapon(ent->entity, lua_tostring(L, 2), luaL_optinteger(L, 3, 0));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:GiveWeapon requires args (string weapon, [int ammo = 0]).");
		}
		lua_pop(L, args);
		return 0;
	}

	int RemoveWeapon(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Player::RemoveWeapon(ent->entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:RemoveWeapon requires args (string weapon).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetNametag(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			lua_pushstring(L, API::Entity::GetNametag(ent->entity).c_str());

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:GetNametag requires no args.");
		}
		return 1;
	}

	int SetNametag(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Entity::SetNametag(ent->entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetNametag requires args (string nametag)");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsNametagVisible(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			lua_pushboolean(L, API::Entity::IsNametagVisible(ent->entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:IsNametagVisible requires no args.");
		}
		return 1;
	}

	int SetNametagVisible(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Entity::SetNametagVisible(ent->entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetNametagVisible requires args (bool visible)");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsHealthbarVisible(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			lua_pushboolean(L, API::Entity::IsHealthbarVisible(ent->entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:IsHealthbarVisible requires no args.");
		}
		return 1;
	}

	int SetHealthbarVisible(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Entity::SetHealthbarVisible(ent->entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetHealthbarVisible requires args (bool visible)");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetNametagDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			lua_pushnumber(L, API::Entity::GetNametagDistance(ent->entity));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:GetNametagDistance requires no args.");
		}
		return 1;
	}

	int SetNametagDistance(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Entity::SetNametagDistance(ent->entity, lua_tonumber(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetNametagDistance requires args (float distance)");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetNametagColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
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
			API::Log::Warning("Player:GetNametagColor requires no args.");
		}
		return 1;
	}

	int SetNametagColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

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
			API::Log::Warning("Player:SetNametagColor requires args (table color)");
		}
		lua_pop(L, args);
		return 0;
	}

	int CreateBlip(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Blip::Create(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:CreateBlip requires no args.");
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
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Blip::ShowToAll(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:ShowBlipToAll requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int HideBlipFromAll(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Blip::HideFromAll(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:HideBlipFromAll requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			const int color = API::Blip::GetColor(ent->entity);
			lua_pop(L, args);

			lua_pushinteger(L, color);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:GetBlipColor requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipColor(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Blip::SetColor(ent->entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetBlipColor requires arg (int color).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipSprite(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			const int sprite = API::Blip::GetSprite(ent->entity);
			lua_pop(L, args);

			lua_pushinteger(L, sprite);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:GetBlipSprite requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipSprite(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Blip::SetSprite(ent->entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetBlipSprite requires arg (int sprite).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetBlipText(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			const std::string text = API::Blip::GetText(ent->entity);
			lua_pop(L, args);

			lua_pushstring(L, text.c_str());

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:GetBlipText requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipText(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Blip::SetText(ent->entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetBlipText requires arg (string text).");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsBlipShortRanged(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			const bool state = API::Blip::IsShortRanged(ent->entity);
			lua_pop(L, args);

			lua_pushboolean(L, state);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:IsBlipShortRanged requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetBlipShortRanged(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Blip::SetShortRanged(ent->entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetBlipShortRanged requires arg (bool state).");
		}
		lua_pop(L, args);
		return 0;
	}

	int SetGroundSnow(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::World::SetGroundSnow(ent->entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetGroundSnow requires args (bool state).");
		}
		lua_pop(L, args);
		return 0;
	}

	int SetBlackout(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::World::SetBlackout(ent->entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetBlackout requires args (bool state).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetWeaponAmmo(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			int ammo, clipAmmo;
			API::Player::GetWeaponAmmo(ent->entity, lua_tostring(L, 2), &ammo, &clipAmmo);

			lua_pushinteger(L, ammo);
			lua_pushinteger(L, clipAmmo);

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			lua_pushnil(L);
			lua_pushnil(L);
			API::Log::Warning("Player:GetWeaponAmmo requires args (string weapon).");
		}
		return 2;
	}

	int SetWeaponAmmo(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 4)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Player::SetWeaponAmmo(ent->entity, lua_tostring(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetWeaponAmmo requires args (string weapon, int ammo, int clipAmmo).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetWeapons(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			std::vector<std::string> weapons = API::Player::GetWeapons(ent->entity);

			if (!weapons.empty())
			{
				lua_newtable(L);
				for (unsigned int i = 0; i < weapons.size(); i++)
				{
					lua_pushstring(L, weapons[i].c_str());
				}
			}
			else
			{
				lua_pushnil(L);
			}

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			lua_pushnil(L);
			API::Log::Warning("Player:GetWeapons requires no args.");
		}
		return 1;
	}

	int EquipWeapon(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 4)
		{
			Player* ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Player::EquipWeapon(ent->entity, lua_tostring(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:EquipWeapon requires args (string weapon).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetHealth(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			lua_pushinteger(L, API::Entity::GetHealth(ent->entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:GetHealth requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetHealth(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Entity::SetHealth(ent->entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetHealth requires arg (int health).");
		}
		lua_pop(L, args);
		return 0;
	}

	int GetArmour(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			lua_pushinteger(L, API::Entity::GetArmour(ent->entity));

			ent = nullptr;
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Player:GetArmour requires no args.");
			lua_pushnil(L);
		}
		return 1;
	}

	int SetArmour(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Entity::SetArmour(ent->entity, lua_tointeger(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetArmour requires arg (int armour).");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsHudHidden(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

			lua_pushboolean(L, API::Visual::IsHudHidden(ent->entity));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:IsHudHidden requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int DisplayHud(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Visual::DisplayHud(ent->entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:DisplayHud requires arg (bool show).");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsRadarHidden(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

			lua_pushboolean(L, API::Visual::IsRadarHidden(ent->entity));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:IsRadarHidden requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int DisplayRadar(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Visual::DisplayRadar(ent->entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:DisplayRadar requires arg (bool show).");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsCashHidden(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

			lua_pushboolean(L, API::Visual::IsCashHidden(ent->entity));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:IsCashHidden requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int DisplayCash(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Visual::DisplayCash(ent->entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:DisplayCash requires arg (bool show).");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsAmmoHidden(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

			lua_pushboolean(L, API::Visual::IsAmmoHidden(ent->entity));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:IsAmmoHidden requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int DisplayAmmo(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 2)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Visual::DisplayAmmo(ent->entity, lua_toboolean(L, 2));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:DisplayAmmo requires arg (bool show).");
		}
		lua_pop(L, args);
		return 0;
	}

	int Revive(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Entity::Revive(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:Revive requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}

	int IsAlive(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);
			lua_pop(L, args);

			lua_pushboolean(L, API::Entity::IsAlive(ent->entity));

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:IsAlive requires no args.");
		}
		return 1;
	}

	int SetCameraPosition(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 2)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);
			CVector3 position;

			if (args == 2)
			{
				if (lua_isuserdata(L, 2))
				{
					Vector3* pos = luabridge::Userdata::get<Vector3>(L, 2, false);
					position = { pos->coord[0], pos->coord[1], pos->coord[2] };
					pos = nullptr;
				}
				else if (lua_istable(L, 2))
				{
					lua_getfield(L, 2, "x");
					lua_rawgeti(L, 2, 1);
					position.x = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "y");
					lua_rawgeti(L, 2, 1);
					position.y = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "z");
					lua_rawgeti(L, 2, 1);
					position.z = lua_tonumber(L, -2);
					lua_pop(L, 1);
				}
			}
			else
			{
				position.x = lua_tonumber(L, 2);
				position.y = lua_tonumber(L, 3);
				position.z = lua_tonumber(L, 4);
			}

			API::Camera::SetPosition(ent->entity, position);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetCameraPosition requires args.");
		}

		lua_pop(L, args);
		return 0;
	}

	int SetCameraRotation(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 2)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);
			CVector3 rotation;

			if (args == 2)
			{
				if (lua_isuserdata(L, 2))
				{
					Vector3* pos = luabridge::Userdata::get<Vector3>(L, 2, false);
					rotation = { pos->coord[0], pos->coord[1], pos->coord[2] };
					pos = nullptr;
				}
				else if (lua_istable(L, 2))
				{
					lua_getfield(L, 2, "x");
					lua_rawgeti(L, 2, 1);
					rotation.x = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "y");
					lua_rawgeti(L, 2, 1);
					rotation.y = lua_tonumber(L, -2);
					lua_pop(L, 1);

					lua_getfield(L, 2, "z");
					lua_rawgeti(L, 2, 1);
					rotation.z = lua_tonumber(L, -2);
					lua_pop(L, 1);
				}
			}
			else
			{
				rotation.x = lua_tonumber(L, 2);
				rotation.y = lua_tonumber(L, 3);
				rotation.z = lua_tonumber(L, 4);
			}

			API::Camera::SetRotation(ent->entity, rotation);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:SetCameraRotation requires args.");
		}

		lua_pop(L, args);
		return 0;
	}

	int ResetCamera(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);
			
			API::Camera::Reset(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:ResetCamera requires no args.");
		}

		lua_pop(L, args);
		return 0;
	}

	int FirstPersonOnly(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Camera::FirstPersonOnly(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:FirstPersonOnly requires no args.");
		}

		lua_pop(L, args);
		return 0;
	}

	int ThirdPersonOnly(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Camera::ThirdPersonOnly(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:ThirdPersonOnly requires no args.");
		}

		lua_pop(L, args);
		return 0;
	}

	int AttachCamera(lua_State* L);

	int DetachCamera(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Player *ent = luabridge::Userdata::get<Player>(L, 1, false);

			API::Camera::Detach(ent->entity);

			ent = nullptr;
		}
		else
		{
			API::Log::Warning("Player:DetachCamera requires no args.");
		}

		lua_pop(L, args);
		return 0;
	}
};
#endif