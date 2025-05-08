#include "StatisticsManager.h"

std::vector<std::string> StatisticsManager::getHighScore() const
{
	return m_database->getHighScores();
}

std::vector<std::string> StatisticsManager::getUserStatistics(const std::string& username) const
{
	std::vector<std::string> stats;
	stats.push_back("Games Played: " + std::to_string(m_database->getNumOfPlayerGames(username)));
	stats.push_back("Correct Answers: " + std::to_string(m_database->getNumOfCorrectAnswers(username)));
	stats.push_back("Total Answers: " + std::to_string(m_database->getNumOfTotalAnswers(username)));
	stats.push_back("Average Answer Time: " + std::to_string(m_database->getPlayerAverageAnswerTime(username)));
	stats.push_back("Score: " + std::to_string(m_database->getPlayerScore(username)));
	return stats;
}
