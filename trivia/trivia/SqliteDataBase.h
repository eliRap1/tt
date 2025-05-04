#pragma once
#include "IDatabase.h"
#include "sqlite3.h"

class SqliteDataBase : public IDatabase
{
public:
    SqliteDataBase(const std::string& dbFileName = "users.db");
    ~SqliteDataBase();

    bool open() override;
    bool close() override;

    bool doesUserExist(const std::string& username) override;
    bool doesPasswordMatch(const std::string& username, const std::string& password) override;
    bool addNewUser(const std::string& username, const std::string& password, const std::string& email) override;

private:
    sqlite3* db;
    std::string m_dbFileName;

    void createUsersTable();
};
