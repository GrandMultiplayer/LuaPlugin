#ifndef __LUAMYSQL_H__
#define __LUAMYSQL_H__

class Mysql {
public:
	static int Connect(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 4)
		{
			std::string ip = lua_tostring(L, 1);
			std::string username = lua_tostring(L, 2);
			std::string password = lua_tostring(L, 3);
			std::string database = lua_tostring(L, 4);
			int port = 3306;
			if (args == 5)
			{
				port = lua_tointeger(L, 5);
			}

			lua_pop(L, args);

			if (mysql != nullptr) delete mysql;
			
			mysql = new MysqlConnection(ip, username, password, database, port);

			lua_pushboolean(L, mysql->WasConnectionSuccesful());
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Mysql:Connect requires arg (string ip, string username, string password, string database, optional[ int port ]).");
			lua_pushnil(L);
		}
		return 1;
	}

	static int Disconnect(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args >= 0)
		{
			delete mysql; //Destructor closes the connection.
		}
		else
		{
			API::Log::Warning("Mysql:Disconnect requires arg ().");
		}
		lua_pop(L, args);
		return 0;
	}

	static int Query(lua_State* L)
	{
		const int args = lua_gettop(L);
		if (args == 1)
		{
			std::string query = lua_tostring(L, 1);

			lua_pop(L, args);

			std::vector<std::map<std::string, MysqlConnection::QueryResult>> ret = mysql->Call(query);

			//Fething Rows and Collumns size.
			int rows = ret.size();

			//Calculating the size of the table
			int initialSize = 0;
			if (rows != 0) 
			{
				initialSize = rows * ret[0].size();
			}

			//Creating table
			lua_createtable(L, 0, initialSize);

			//Iterating through rows
			int i = 0;

			//for each(std::map<std::string, MysqlConnection::QueryResult> row in ret)
			for (std::map<std::string, MysqlConnection::QueryResult>& row : ret)
			{
				i++;

				//Creating another table
				lua_newtable(L);

				//for each(std::pair<std::string, MysqlConnection::QueryResult> collumn in row)
				for (std::pair<std::string, MysqlConnection::QueryResult> collumn : row)
				{
					//Pushing key and value and making table
					lua_pushstring(L, collumn.first.c_str());

					if (collumn.second.datatype == enum_field_types::MYSQL_TYPE_NULL)
					{
						lua_pushnil(L);
					}
					else
					{
						if (collumn.second.datatype == enum_field_types::MYSQL_TYPE_FLOAT ||
							collumn.second.datatype == enum_field_types::MYSQL_TYPE_DOUBLE)
						{
							lua_pushnumber(L, std::stod(collumn.second.data));
						}
						else if (collumn.second.datatype == enum_field_types::MYSQL_TYPE_TINY ||
							collumn.second.datatype == enum_field_types::MYSQL_TYPE_SHORT ||
							collumn.second.datatype == enum_field_types::MYSQL_TYPE_DECIMAL ||
							collumn.second.datatype == enum_field_types::MYSQL_TYPE_NEWDECIMAL ||
							collumn.second.datatype == enum_field_types::MYSQL_TYPE_LONG ||
							collumn.second.datatype == enum_field_types::MYSQL_TYPE_LONGLONG)
						{
							lua_pushinteger(L, std::stoll(collumn.second.data)); //stoll because lua_Integer = long long
						}
						else if (collumn.second.datatype == enum_field_types::MYSQL_TYPE_BIT)
						{
							lua_pushboolean(L, std::stoi(collumn.second.data));
						}
						else
						{
							lua_pushstring(L, collumn.second.data.c_str());
						}
						
						// look up if MYSQL_TYPE_TINY is just 1 & 0, if it is then should out to a boolean
					}

					lua_settable(L, -3);
				}

				//Pushing table to table
				lua_pushinteger(L, i);
				lua_insert(L, -2);
				lua_settable(L, -3);
			}
		}
		else
		{
			lua_pop(L, args);
			API::Log::Warning("Mysql:Query requires arg (string query).");
			lua_pushnil(L);
		}
		return 1;
	}
};
#endif