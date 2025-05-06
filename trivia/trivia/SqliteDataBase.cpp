#include "SqliteDataBase.h"
#include <iostream>

SqliteDataBase::SqliteDataBase(const std::string& dbFileName)
    : db(nullptr), m_dbFileName(dbFileName) {}

SqliteDataBase::~SqliteDataBase()
{
    close();
}

bool SqliteDataBase::open()
{
    if (sqlite3_open(m_dbFileName.c_str(), &db) != SQLITE_OK)
    {
        std::cerr << "Error opening DB: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    createUsersTable();
    return true;
}

bool SqliteDataBase::close()
{
    if (db)
    {
        sqlite3_close(db);
        db = nullptr;
    }
    return true;
}

void SqliteDataBase::createUsersTable()
{
    const char* sql = R"(CREATE TABLE IF NOT EXISTS users (
                            username TEXT PRIMARY KEY,
                            password TEXT NOT NULL,
                            email TEXT NOT NULL);)";
    char* errMsg = nullptr;
    if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Create table error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

int SqliteDataBase::doesUserExist(const std::string& username)
{
    sqlite3_stmt* stmt;
    const char* sql = "SELECT username FROM users WHERE username = ?;";
    bool exists = false;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        exists = (sqlite3_step(stmt) == SQLITE_ROW);
    }

    sqlite3_finalize(stmt);
    return exists;
}

int SqliteDataBase::doesPasswordMatch(const std::string& username, const std::string& password)
{
    sqlite3_stmt* stmt;
    const char* sql = "SELECT password FROM users WHERE username = ?;";
    bool match = false;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            const char* dbPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            match = (password == dbPassword);
        }
    }

    sqlite3_finalize(stmt);
    return match;
}

int SqliteDataBase::addNewUser(const std::string& username, const std::string& password, const std::string& email)
{
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO users (username, password, email) VALUES (?, ?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, email.c_str(), -1, SQLITE_TRANSIENT);

        bool success = (sqlite3_step(stmt) == SQLITE_DONE);
        sqlite3_finalize(stmt);
        return success;
    }

    sqlite3_finalize(stmt);
    return false;
}

float SqliteDataBase::getPlayerAverageAnswerTime(const std::string& username) 
{
    const char* sql = "SELECT AVG(answer_time) FROM statistics WHERE username = ?;";
    sqlite3_stmt* stmt;
    float avg = 0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            avg = static_cast<float>(sqlite3_column_double(stmt, 0));
        }
        sqlite3_finalize(stmt);
    }
    return avg;
}

int SqliteDataBase::getNumOfCorrectAnswers(const std::string& username) 
{
    const char* sql = "SELECT COUNT(*) FROM statistics WHERE username = ? AND is_correct = 1;";
    sqlite3_stmt* stmt;
    int count = 0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) 
        {
            count = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    return count;
}

int SqliteDataBase::getNumOfTotalAnswers(const std::string& username) 
{
    const char* sql = "SELECT COUNT(*) FROM statistics WHERE username = ?;";
    sqlite3_stmt* stmt;
    int count = 0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) 
        {
            count = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    return count;
}

int SqliteDataBase::getNumOfPlayerGames(const std::string& username) 
{
    const char* sql = "SELECT COUNT(DISTINCT game_id) FROM statistics WHERE username = ?;";
    sqlite3_stmt* stmt;
    int count = 0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) 
        {
            count = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }
    return count;
}
