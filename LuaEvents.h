#ifndef __LUAEVENTS_H__
#define __LUAEVENTS_H__

class Events {
public:
	static int AddHandler(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 2)
		{
			Event newEvent;

			std::string eventString = lua_tostring(L, 1);
			
			for (unsigned int i = 0; i < eventString.size(); i++)
			{
				eventString[i] = tolower(eventString[i]);
			}

			bool validEvent = false;
			
			for (unsigned int i = 0; i < SizeOfArray(EventStrings); i++)
			{
				if (eventString.compare(EventStrings[i]) == 0) {
					newEvent.evt = eventString;
					validEvent = true;
					break;
				}
			}

			if (!validEvent)
			{
				std::stringstream str;
				str << "Event.AddHandler invalid event " << eventString;
				API::Log::Error(str.str().c_str());
				lua_pop(L, args);
				return 0;
			}

			//const int entity = lua_tointeger(L, 2);

			lua_pushvalue(L, 2);
			newEvent.functionKey = luaL_ref(L, LUA_REGISTRYINDEX); //function 

			events.push_back(newEvent);
		}
		else
		{
			API::Log::Warning("AddHandler requires args (string event, function handlerFunction).");
		}
		lua_pop(L, args);
		return 0;
	}
};
#endif