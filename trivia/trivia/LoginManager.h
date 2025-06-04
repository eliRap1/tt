#pragma once
#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>
#include <iostream>
enum class SignUpStatus { Success, UserAlreadyExists, DbError };
enum class LoginStatus { Success, UserNotExist, WrongPassword, AlreadyLoggedIn, DbError };

class LoginManager
{
public:
	LoginManager(IDatabase* database);
    SignUpStatus signup(const std::string& username, const std::string& password, const std::string& email);
    LoginStatus login(const std::string& username, const std::string& password);
    void logout(const std::string& username);

private:
    IDatabase* m_database;
    std::vector<LoggedUser> m_loggedUsers;

    bool isLoggedIn(const std::string& username);
};
