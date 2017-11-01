#ifndef __MYSQL_H__
#define __MYSQL_H__

class MysqlConnection {
public:
	struct QueryResult {
		std::string data;
		enum_field_types datatype;
	};

	MysqlConnection(std::string host, std::string username, std::string password, std::string database, int port);
	~MysqlConnection();

	void PingServer();

	std::vector<std::map<std::string, QueryResult>> Call(std::string querry);

	bool WasConnectionSuccesful() { return connected; }
private:
	void Connect();

	std::string host;
	std::string username;
	std::string password;
	std::string database;
	int port;

	MYSQL* connection = nullptr;
	bool connected = false;
};
extern MysqlConnection* mysql;

#endif