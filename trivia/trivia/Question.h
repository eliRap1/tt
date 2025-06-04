#pragma once
#include <string>
#include <vector>

class Question {
public:
    Question(const std::string& questionText,
        const std::vector<std::string>& possibleAnswers,
        int correctAnswerId);

    std::string getQuestion() const;
    std::vector<std::string> getPossibleAnswers() const;
    int getCorrectAnswerId() const;

private:
    std::string m_question;
    std::vector<std::string> m_possibleAnswers; // Should always contain 4 elements
    int m_correctAnswerId; // 0-based
};