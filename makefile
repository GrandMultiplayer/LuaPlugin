Lua: api.cpp
	make -C inc_lua linux
	g++  *.cpp sdk/*.cpp -o ../../bin/Linux/plugin/Lua.so -L../../API.Plugins/Lua/inc_lua -llua -ldl -shared -fPIC -std=c++11 
