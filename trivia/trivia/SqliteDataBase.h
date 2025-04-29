#pragma once
#include <string>
#include "sqlite3.h"

class SqliteDataBase 
{
public:
    SqliteDataBase(const std::string& dbFileName = "users.db");
    ~SqliteDataBase();

    bool userExists(const std::string& username);
    bool isPasswordMatch(const std::string& username, const std::string& password);
    bool addUser(const std::string& username, const std::string& password, const std::string& email);

private:
    sqlite3* db;

    void open(const std::string& dbFileName);
    void createUsersTable();
};
