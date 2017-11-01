#ifndef __LUASERVER_H__
#define __LUASERVER_H__

class Server {
public:
	/*static int PrintMessage(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			API::Server::PrintMessage(CString::utf8ToUtf16(lua_tostring(L, 1)));
		}
		else
		{
			API::Log::Warning("PrintMessage requires arg (string message).");
		}
		lua_pop(L, args);
		return 0;
	}*/
};
#endif