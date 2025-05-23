#include "LoginManager.h"
#include <algorithm>

LoginManager::LoginManager(IDatabase* database) : m_database(database)
{
    if (!m_database->open())
        throw std::runtime_error("Cannot open database.");
	this->m_loggedUsers.clear();
}

SignUpStatus LoginManager::signup(const std::string& username, const std::string& password, const std::string& email)
{
    if (m_database->doesUserExist(username))
        return SignUpStatus::UserAlreadyExists;

    if (!m_database->addNewUser(username, password, email))
        return SignUpStatus::DbError;

    return SignUpStatus::Success;
}

LoginStatus LoginManager::login(const std::string& username, const std::string& password)
{
    if (isLoggedIn(username))
        return LoginStatus::AlreadyLoggedIn;

    if (!m_database->doesUserExist(username))
        return LoginStatus::UserNotExist;

    if (!m_database->doesPasswordMatch(username, password))
        return LoginStatus::WrongPassword;

    m_loggedUsers.emplace_back(username);
    return LoginStatus::Success;
}

void LoginManager::logout(const std::string& username)
{
	m_loggedUsers.erase(
		std::remove_if(m_loggedUsers.begin(), m_loggedUsers.end(),
			[&username](const LoggedUser& user) {
				return user.getUsername() == username;
			}),
		m_loggedUsers.end()
	);
}


bool LoginManager::isLoggedIn(const std::string& username)
{
    return std::any_of(m_loggedUsers.begin(), m_loggedUsers.end(),
        [&username](const LoggedUser& user) {
            return user.getUsername() == username;
        });
}
