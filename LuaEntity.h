#ifndef __LUAENTITY_H__
#define __LUAENTITY_H__

class Entity {
public:
	static int GetEntities(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			std::vector<int> entities = API::Entity::GetEntities(lua_tointeger(L,1));
			lua_pop(L, args);
			
			lua_createtable(L, entities.size(), 0);

			for (unsigned int i = 0; i < entities.size(); i++)
			{
				const int type = API::Entity::GetType(entities[i]);
				switch (type) // (Types are, Player = 0, Vehicle = 1, Object = 2, NPC = 3, Checkpoint = 4, Blip = 5)
				{
				case 0: {
					Player ent;
					ent.entity = entities[i];
					push(L, ent);
					break;
				}
				case 1: {
					Vehicle ent;
					ent.entity = entities[i];
					push(L, ent);
					break;
				}
				case 2: {
					Object ent;
					ent.entity = entities[i];
					push(L, ent);
					break;
				}
				case 3: {
					NPC ent;
					ent.entity = entities[i];
					push(L, ent);
					break;
				}
				case 4: {
					Checkpoint ent;
					ent.entity = entities[i];
					push(L, ent);
					break;
				}
				case 5: {
					Blip ent;
					ent.entity = entities[i];
					push(L, ent);
					break;
				}
				default:
					lua_pushnil(L);
					break;
				}
				
				lua_rawseti(L, -2, i+1);
			}
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("GetEntities requires arg (int type).");
			lua_pushnil(L);
		}
		
		return 1;
	}
};
#endif