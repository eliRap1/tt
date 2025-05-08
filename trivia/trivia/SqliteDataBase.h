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

    int doesUserExist(const std::string& username) override;
    int doesPasswordMatch(const std::string& username, const std::string& password) override;
    int addNewUser(const std::string& username, const std::string& password, const std::string& email) override;
    float getPlayerAverageAnswerTime(const std::string& username);
    int getNumOfCorrectAnswers(const std::string& username);
    int getNumOfTotalAnswers(const std::string& username);
    int getNumOfPlayerGames(const std::string& username);

private:
	sqlite3* db;
	std::string m_dbFileName;

	void createTables();
};