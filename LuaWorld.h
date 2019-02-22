#ifndef __LUAWORLD_H__
#define __LUAWORLD_H__

class World {
public:
	static int GetTime(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 0)
		{
			int hour, minute, second;
			API::World::GetTime(&hour, &minute, &second);

			lua_pushinteger(L, hour);
			lua_pushinteger(L, minute);
			lua_pushinteger(L, second);
		}
		else
		{
			API::Log::Warning("GetTime requires no args.");
			lua_pushnil(L);
			lua_pushnil(L);
			lua_pushnil(L);
		}
		lua_pop(L, args);
		return 3;
	}

	static int SetTime(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 3)
		{
			API::World::SetTime(lua_tointeger(L, 1), lua_tointeger(L, 2), lua_tointeger(L, 3));
		}
		else
		{
			API::Log::Warning("SetTime requires args (int hour, int minute, int second).");
		}
		lua_pop(L, args);
		return 0;
	}

	static int GetWeather(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 0)
		{
			lua_pushstring(L, API::World::GetWeather());	
		}
		else
		{
			API::Log::Warning("GetWeather requires no args.");
			lua_pushnil(L);
		}
		lua_pop(L, args);
		return 1;
	}

	static int SetWeather(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			API::World::SetWeather(lua_tostring(L, 1));
		}
		else
		{
			API::Log::Warning("SetWeather requires args (string weather).");
		}
		lua_pop(L, args);
		return 0;
	}

	static int LoadIPL(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			API::World::LoadIPL(lua_tostring(L, 1));
		}
		else
		{
			API::Log::Warning("LoadIPL requires args (string ipl).");
		}
		lua_pop(L, args);
		return 0;
	}

	static int UnloadIPL(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			API::World::UnloadIPL(lua_tostring(L, 1));
		}
		else
		{
			API::Log::Warning("UnloadIPL requires args (string ipl).");
		}
		lua_pop(L, args);
		return 0;
	}

	static int IsBlackout(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 0)
		{
			lua_pop(L, args);
			lua_pushboolean(L, API::World::IsBlackout());
		}
		else
		{
			API::Log::Warning("IsBlackout requires no args.");
		}
		
		return 1;
	}

	static int SetBlackout(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			API::World::SetBlackout(lua_toboolean(L, 1));
		}
		else
		{
			API::Log::Warning("SetBlackout requires args (bool state).");
		}
		lua_pop(L, args);
		return 0;
	}

	static int IsGroundSnow(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 0)
		{
			lua_pop(L, args);
			lua_pushboolean(L, API::World::IsGroundSnow());
		}
		else
		{
			API::Log::Warning("IsGroundSnow requires no args.");
		}

		return 1;
	}

	static int SetGroundSnow(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			API::World::SetGroundSnow(lua_toboolean(L, 1));
		}
		else
		{
			API::Log::Warning("SetGroundSnow requires args (bool state).");
		}
		lua_pop(L, args);
		return 0;
	}

};
#endif