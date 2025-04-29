#pragma once
#include <vector>
#include <algorithm>
#include "LoggedUser.h"
#include "SqliteDataBase.h"

enum class SignupStatus {
    Success,
    UserAlreadyExists,
    DbError
};

enum class LoginStatus {
    Success,
    UserNotExist,
    WrongPassword,
    AlreadyLoggedIn,
    DbError
};

class LoginManager
{
public:
    LoginManager(SqliteDataBase* database);

    SignupStatus signup(const std::string& username,
        const std::string& password,
        const std::string& email);

    LoginStatus login(const std::string& username,
        const std::string& password);

    void logout(const std::string& username);
    bool isLoggedIn(const std::string& username) const;

private:
    SqliteDataBase* m_database;
    std::vector<LoggedUser> m_loggedUsers;

    std::vector<LoggedUser>::iterator findLogged(const std::string& username);
};