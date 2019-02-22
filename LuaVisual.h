#ifndef __LUAVISUAL_H__
#define __LUAVISUAL_H__

class Visual 
{
public:
	static int ShowMessageAboveMap(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 5)
		{
			API::Visual::ShowNotification(lua_tostring(L, 1), lua_tostring(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4), lua_tostring(L, 5), lua_tostring(L, 6));
		}
		else
		{
			API::Log::Warning("ShowNotification requires args (string message, string pic, int icontype, int color, string sender, string subject).");
		}
		lua_pop(L, args);
		return 0;
	}

	static int SendChatMessage(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			std::string message = lua_tostring(L, 1);

			API::Visual::SendChatMessage((wchar_t*)message.c_str());
		}
		else
		{
			API::Log::Warning("SendChatMessage requires args (string message).");
		}
		lua_pop(L, args);
		return 0;
	}

	static int ShowSubtitle(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 3)
		{
			API::Visual::ShowSubtitle(lua_tostring(L, 1), lua_tointeger(L,2), lua_toboolean(L,3));
		}
		else
		{
			API::Log::Warning("ShowSubtitle requires args (string message, int duration, bool shownow).");
		}
		lua_pop(L, args);
		return 0;
	}
};
#endif