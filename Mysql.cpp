#include <string>
#include <iostream>
#include <vector>
#include <map>

//LibMysql
#include "Mysql/mysql.h"
#include "Mysql.h"

MysqlConnection::MysqlConnection(std::string host, std::string username, std::string password, std::string database, int port = 3306)
{
	this->host = host;
	this->username = username;
	this->password = password;
	this->database = database;
	this->port = port;

	Connect();
}

MysqlConnection::~MysqlConnection()
{
	if (connected) {
		mysql_close(connection);
		connection = nullptr;
	}
}

void MysqlConnection::PingServer()
{
	//If we should be connected
	if (connected) {
		if (mysql_ping(connection) != 0) {
			std::cout << "Server isn't connected to MySQL database!" << std::endl;;
			std::cout << "Trying to reconnect..." << std::endl;;
			Connect();
		}
	}
}

std::vector<std::map<std::string, MysqlConnection::QueryResult>> MysqlConnection::Call(std::string querry)
{
	if (connected) {
		mysql_query(connection, querry.c_str());
		MYSQL_RES* result = mysql_store_result(connection);
		if (result == NULL) {
			//Returns clear vector
			return std::vector<std::map<std::string, QueryResult>>();
		}

		//Fetching collumn names
		std::vector<std::string> collumnNames;
		std::vector<enum_field_types> allTypes;

		MYSQL_FIELD* field;
		while ((field = mysql_fetch_field(result))) { collumnNames.push_back(field->name); allTypes.push_back(field->type); }

		//Getting and allocating all needed data before data fetching
		std::vector<std::map<std::string, QueryResult>> ret;
		int num_fields = mysql_num_fields(result);

		//Fething data
		MYSQL_ROW row;
		while ((row = mysql_fetch_row(result))) {

			//Creating map for each row
			std::map<std::string, QueryResult> rowRep;
			for (int i = 0; i < num_fields; i++) {
				rowRep[collumnNames[i]].datatype = allTypes[i];

				if (row[i] == nullptr) {
					rowRep[collumnNames[i]].data = "";
				}
				else {
					rowRep[collumnNames[i]].data = row[i];
				}
			}
			ret.push_back(rowRep);

		}
		return ret;
	}

	//Returns clear vector
	return std::vector<std::map<std::string, QueryResult>>();
}

void MysqlConnection::Connect()
{
	connection = mysql_init(NULL);

	if (connection == NULL) {
		std::cout << "Failed to initialize mysql: " << mysql_error(connection) << std::endl;
		return;
	}


	if (mysql_real_connect(connection, host.c_str(), username.c_str(), password.c_str(), database.c_str(), port, NULL, NULL) == NULL) {
		std::cout << "Failed to connect to mysql database: " << mysql_error(connection) << std::endl;
		return;
	}

	connected = true;
}
