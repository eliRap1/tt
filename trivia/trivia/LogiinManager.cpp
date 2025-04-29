#include "LoginManager.h"
LoginManager::LoginManager(SqliteDataBase* database)
    : m_database(database)
{
}
std::vector<LoggedUser>::iterator LoginManager::findLogged(const std::string& username)
{
    return std::find_if(m_loggedUsers.begin(), m_loggedUsers.end(),
        [&](const LoggedUser& user) {
            return user.getUsername() == username;
        });
}
SignupStatus LoginManager::signup(const std::string& username, const std::string& password, const std::string& email)
{
    if (m_database->userExists(username))
        return SignupStatus::UserAlreadyExists;

    if (!m_database->addUser(username, password, email))
        return SignupStatus::DbError;

    return SignupStatus::Success;
}
LoginStatus LoginManager::login(const std::string& username, const std::string& password)
{
    if (isLoggedIn(username))
        return LoginStatus::AlreadyLoggedIn;

    if (!m_database->userExists(username))
        return LoginStatus::UserNotExist;

    if (!m_database->isPasswordMatch(username, password))
        return LoginStatus::WrongPassword;

    m_loggedUsers.emplace_back(username);
    return LoginStatus::Success;
}
void LoginManager::logout(const std::string& username)
{
    auto it = findLogged(username);
    if (it != m_loggedUsers.end())
        m_loggedUsers.erase(it);
}
bool LoginManager::isLoggedIn(const std::string& username) const
{
    return std::any_of(m_loggedUsers.begin(), m_loggedUsers.end(),
        [&](const LoggedUser& user) {
            return user.getUsername() == username;
        });
}
