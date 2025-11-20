#pragma once
#include <vector>
#include "Question.h"
#include "Participant.h"
#include <fstream>

class Repository
{
private:
	std::vector<Participant> participants;
	std::vector<Question> questions;
	std::string pFile, qFile;

public:
	Repository(const std::string& p, const std::string& q);
	~Repository();
	std::vector<Participant> getParticipants();
	std::vector<Question> getQuestions();
	void addQuestion(const Question& quest);
	void changeScoreOfAParticipant(int index, int newScore);
	void loadQuestions();
	void loadParticipants();
	void saveQuestions();
	void saveParticipants();
};

