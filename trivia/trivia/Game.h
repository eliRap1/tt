#pragma once
#include "GameManager.h"
#include <string>
#include "LoggedUser.h"
#include "Question.h"
#include <map>
typedef struct GameData
{
	Question currentQuestion;
	unsigned int correctAnswersCount;
	unsigned int wrongAnswersCount;
	unsigned int averageAnswerTime;
}GameData;
class Game
{
private:
	std::vector<Question> m_questions;
	std::map < LoggedUser, GameData > m_players;
	int gameId;
public:
	Question getQuestionForUser(LoggedUser& user);
	void submitAnswer(LoggedUser& user, int answerId);
};

