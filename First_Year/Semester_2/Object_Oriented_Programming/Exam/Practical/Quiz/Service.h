#pragma once
#include "Subject.h"
#include "Repository.h"

class Service : public Subject
{
private:
	Repository* repository;

public:
	Service(Repository* repository) : repository{ repository } {};
	~Service() {};
	std::vector<Participant> getParticipants();
	std::vector<Question> getQuestions();
	std::vector<Question> getQuestionsIncreasingId();
	std::vector<Question> getQuestionsDecreasingScore();
	void addQuestion(int id, const std::string& text, const std::string& correct, int score);
	void changeScoreOfAParticipant(std::string name, int newScore);
};

