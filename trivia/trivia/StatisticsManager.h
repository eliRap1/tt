#pragma once
#include "IDatabase.h"
#include <vector>
class StatisticsManager
{
private:
	IDatabase* m_database;
public:
	std::vector<std::string> getHighScore() const;
};

