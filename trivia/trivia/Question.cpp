// Question.cpp
#include "Question.h"
#include <stdexcept>

Question::Question(const std::string& questionText,
    const std::vector<std::string>& possibleAnswers,
    int correctAnswerId)
    : m_question(questionText), m_possibleAnswers(possibleAnswers), m_correctAnswerId(correctAnswerId) {

    if (possibleAnswers.size() != 4) {
        throw std::invalid_argument("Exactly 4 possible answers are required");
    }
    if (correctAnswerId < 0 || correctAnswerId >= 4) {
        throw std::invalid_argument("Correct answer index must be between 0 and 3");
    }
}

std::string Question::getQuestion() const {
    return m_question;
}

std::vector<std::string> Question::getPossibleAnswers() const {
    return m_possibleAnswers;
}

int Question::getCorrectAnswerId() const {
    return m_correctAnswerId;
}
