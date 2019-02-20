#ifndef __LUAENTITY_H__
#define __LUAENTITY_H__

class Entity {
public:
	static int GetEntities(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			Objects::Entity * entities = API::Entity::GetEntities(lua_tointeger(L,1));
			lua_pop(L, args);

			const int arraySize = (int)(sizeof(entities) / sizeof(entities[0]));
			
			lua_createtable(L, arraySize, 0);

			for (unsigned int i = 0; i < arraySize; i++)
			{
				switch (entities[i].GetType()) // (Types are, Player = 0, NPC, Vehicle, Object, Checkpoint, Pickup, Blip)
				{
				case 0: {
					Player ent;
					ent.entity = entities[i].GetID();
					push(L, ent);
					break;
				}
				case 2: {
					Vehicle ent;
					ent.entity = entities[i].GetID();
					push(L, ent);
					break;
				}
				case 3: {
					Object ent;
					ent.entity = entities[i].GetID();
					push(L, ent);
					break;
				}
				case 1: {
					NPC ent;
					ent.entity = entities[i].GetID();
					push(L, ent);
					break;
				}
				case 4: {
					Checkpoint ent;
					ent.entity = entities[i].GetID();
					push(L, ent);
					break;
				}
				//5 is pickup.
				case 6: {
					Blip ent;
					ent.entity = entities[i].GetID();
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