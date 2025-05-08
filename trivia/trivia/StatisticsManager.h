#pragma once
#include "IDatabase.h"
#include <vector>
class StatisticsManager
{
private:
	IDatabase* m_database;
public:
	std::vector<std::string> getHighScore() const;
	std::vector<std::string> getUserStatistics(const std::string& username) const;
};

