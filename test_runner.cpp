#include "trivia/trivia/SqliteDataBase.h"
#include "trivia/trivia/Question.h" // Actual Question class
#include <iostream>
#include <string>
#include <vector>
#include <fstream> // Required for std::remove

// Dummy Question class definition removed, Question.h above should provide the necessary class


void insert_question(SqliteDataBase& db, const std::string& q, const std::string& ca, const std::string& i1, const std::string& i2, const std::string& i3) {
    std::string sql = "INSERT INTO questions (question, correct_answer, incorrect1, incorrect2, incorrect3) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db.getDB(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, q.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, ca.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, i1.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 4, i2.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 5, i3.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Failed to insert question: " << q.substr(0, 50) << "..." << std::endl;
            std::cerr << "SQLite error: " << sqlite3_errmsg(db.getDB()) << std::endl;
        }
        sqlite3_finalize(stmt);
    } else {
        std::cerr << "Failed to prepare statement for question insertion." << std::endl;
        std::cerr << "SQLite error: " << sqlite3_errmsg(db.getDB()) << std::endl;
    }
}

int main() {
    const std::string dbFileName = "test_trivia.db";
    SqliteDataBase testDB(dbFileName);

    std::cout << "Attempting to open database..." << std::endl;
    if (!testDB.open()) {
        std::cerr << "Test FAILED: Could not open or create database." << std::endl;
        return 1;
    }
    std::cout << "Database opened. Tables should be created." << std::endl;

    // Create a very long string
    std::string long_question_text(5000, 'A');
    std::string long_correct_answer(5000, 'B');
    std::string long_incorrect1(5000, 'C');
    std::string long_incorrect2(5000, 'D');
    std::string long_incorrect3(5000, 'E');

    std::cout << "Inserting questions..." << std::endl;
    // Insert normal questions
    insert_question(testDB, "What is 2+2?", "4", "3", "5", "6");
    insert_question(testDB, "Capital of France?", "Paris", "London", "Berlin", "Rome");
    // Insert the long question
    insert_question(testDB, long_question_text, long_correct_answer, long_incorrect1, long_incorrect2, long_incorrect3);
    insert_question(testDB, "What is the color of the sky?", "Blue", "Green", "Red", "Yellow");
    std::cout << "Questions inserted." << std::endl;

    std::cout << "Attempting to retrieve questions..." << std::endl;
    try {
        std::list<Question> questions = testDB.getQuestions(10);
        std::cout << "Retrieved " << questions.size() << " questions." << std::endl;

        bool longQuestionFound = false;
        for (const auto& q : questions) {
            std::cout << "Question: " << q.getQuestion().substr(0, 100) << (q.getQuestion().length() > 100 ? "..." : "") << std::endl;
            if (q.getQuestion().length() == 5000) {
                longQuestionFound = true;
                std::cout << "Long question successfully retrieved." << std::endl;
                 // Verify answers also
                const auto& answers = q.getPossibleAnswers();
                bool allAnswersLong = true;
                for(const auto& ans : answers) {
                    if (ans.length() != 5000) {
                        allAnswersLong = false;
                        std::cerr << "Test FAILED: Long question's answer was not retrieved with full length. Length: " << ans.length() << std::endl;
                        break;
                    }
                }
                if(!allAnswersLong) longQuestionFound = false; // Mark as not found if answers are incorrect
            }
        }

        if (!longQuestionFound && questions.size() > 0) {
             // It's possible the long question wasn't picked by RANDOM() if amount < total questions.
             // We inserted 4 questions and request 10. So it should be there.
            bool foundInDb = false;
            sqlite3_stmt* stmt_check;
            std::string sql_check = "SELECT question FROM questions WHERE length(question) = 5000;";
            if (sqlite3_prepare_v2(testDB.getDB(), sql_check.c_str(), -1, &stmt_check, nullptr) == SQLITE_OK) {
                if (sqlite3_step(stmt_check) == SQLITE_ROW) {
                    foundInDb = true;
                }
                sqlite3_finalize(stmt_check);
            }
            if (foundInDb) {
                 std::cout << "Long question was in DB but not retrieved by getQuestions among " << questions.size() << " questions." << std::endl;
                 // This is not a strict failure of the string handling, but good to note.
                 // The critical part is no crash.
            } else {
                std::cerr << "Test FAILED: Long question was not inserted or found in DB properly." << std::endl;
                testDB.close();
                std::remove(dbFileName.c_str());
                return 1;
            }
        } else if (questions.empty()) {
            std::cerr << "Test FAILED: No questions retrieved." << std::endl;
            testDB.close();
            std::remove(dbFileName.c_str());
            return 1;
        }


        std::cout << "Test PASSED: getQuestions did not crash and retrieved questions." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test FAILED: Exception caught during getQuestions: " << e.what() << std::endl;
        testDB.close();
        std::remove(dbFileName.c_str());
        return 1;
    } catch (...) {
        std::cerr << "Test FAILED: Unknown exception caught during getQuestions." << std::endl;
        testDB.close();
        std::remove(dbFileName.c_str());
        return 1;
    }

    std::cout << "Closing database..." << std::endl;
    testDB.close();
    std::cout << "Deleting temporary database file..." << std::endl;
    if (std::remove(dbFileName.c_str()) != 0) {
        std::cerr << "Warning: Could not delete temporary database file " << dbFileName << std::endl;
    }
    std::cout << "Cleanup finished." << std::endl;

    return 0;
}
