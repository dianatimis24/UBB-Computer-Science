#pragma once
#include <string>

class Participant
{
private:
	std::string name;
	int score;

public:
	Participant(const std::string& name = "", int score = 0) : name{ name }, score{ score } {};
	~Participant() {};
	std::string getName() { return this->name; };
	int getScore() { return this->score; };
	void setName(const std::string& name) { this->name = name; };
	void setScore(int newScore) { this->score = newScore; };
};

