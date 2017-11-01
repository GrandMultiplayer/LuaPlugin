#ifndef __LUATIMER_H__
#define __LUATIMER_H__

struct Timer
{
	int TimerIndex;

	Timer()
	{
		TimerIndex = -1;
	}

	int Create(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 3)
		{
			Timer *t = luabridge::Userdata::get<Timer>(L, 1, false);
			
			if(t->TimerIndex == -1)
			{
				timer newTimer;

				if (!lua_isfunction(L, 2))
				{
					API::Log::Warning("Timer:Create arg 1 must be a function.");
					lua_pop(L, args);
					return 0;
				}

				lua_pushvalue(L, 2);
				newTimer.functionKey = luaL_ref(L, LUA_REGISTRYINDEX); //function 

				newTimer.tick = lua_tointeger(L, 3); //delay in ms
				newTimer.lastTick = std::chrono::system_clock::now();
				newTimer.used = true;

				if (args > 3)
				{
					for (unsigned int i = 4; i <= args; i++)
					{
						FuncArg arg = FuncArg();

						switch (lua_type(L, i))
						{
						case LUA_TBOOLEAN:
							arg.type = ArgType::TYPE_BOOLEAN;
							arg.boolean = lua_toboolean(L, i);
							break;
						case LUA_TSTRING:
							arg.type = ArgType::TYPE_STRING;
							arg.string = lua_tostring(L, i);
							break;
						case LUA_TNUMBER:
							arg.type = ArgType::TYPE_NUMBER;
							arg.number = lua_tonumber(L, i);
							break;
						default:
							int r = luaL_ref(L, LUA_REGISTRYINDEX);
							arg.type = ArgType::TYPE_OTHER;
							arg.other = r;
							break;
						}

						newTimer.args.push_back(arg);
					}
				}

				t->TimerIndex = timers.size();
				timers.push_back(newTimer);
			}
			else
			{
				API::Log::Warning("Timer:Create this timer is already created.");
			}

			t = nullptr;
		}
		else
		{
			API::Log::Warning("Timer:Create requires args (function, int delay/ms, optional[ARGS]...).");
		}
		lua_pop(L, args);
		return 0;
	}

	int Destroy(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Timer *t = luabridge::Userdata::get<Timer>(L, 1, false);

			timers[t->TimerIndex].used = false;
			timers[t->TimerIndex].functionKey = 0;
			timers[t->TimerIndex].args = std::vector<FuncArg>();
			timers[t->TimerIndex].tick = 0;
			timers[t->TimerIndex].lastTick = std::chrono::system_clock::now();
			
			t->TimerIndex = -1;

			t = nullptr;
		}
		else
		{
			API::Log::Warning("Timer:Destroy requires no args.");
		}
		lua_pop(L, args);
		return 0;
	}
};
#endif