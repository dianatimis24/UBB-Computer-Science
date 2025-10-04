#pragma once
#include <string>

class Question
{
private:
	int id, score;
	std::string text, correct;

public:
	Question(int id = 0, const std::string& text = "", const std::string& correct = "", int score = 0) : id{ id }, text{ text }, correct{ correct }, score{ score } {};
	~Question() {};
	int getId() { return this->id; };
	int getScore() { return this->score; };
	std::string getText() { return this->text; };
	std::string getCorrect() { return this->correct; };
	bool operator < (const Question& other) const {
		return this->id < other.id;
	};
};

