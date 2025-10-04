#include "Repository.h" 
#include <sstream>

Repository::Repository(const std::string& p, const std::string& q) : pFile{ p }, qFile{ q }
{
	this->loadParticipants();
	this->loadQuestions();
}

Repository::~Repository()
{
	this->saveParticipants();
	this->saveQuestions();
}

std::vector<Participant> Repository::getParticipants()
{
	return this->participants;
}

std::vector<Question> Repository::getQuestions()
{
	return this->questions;
}

void Repository::addQuestion(const Question& quest)
{
	this->questions.push_back(quest);
	this->saveQuestions();
}

void Repository::changeScoreOfAParticipant(int index, int newScore)
{
	this->participants[index].setScore(newScore);
}

void Repository::loadQuestions()
{
	std::ifstream fin(this->qFile);
	const char delim = '|';
	std::string line, id, text, correct, score;
	while (std::getline(fin, line))
	{
		std::istringstream iss(line);
		std::getline(iss, id, delim);
		std::getline(iss, text, delim);
		std::getline(iss, correct, delim);
		std::getline(iss, score, delim);
		this->questions.emplace_back(std::stoi(id), text, correct, std::stoi(score));
	}
	fin.close();
}

void Repository::loadParticipants()
{
	std::ifstream fin(this->pFile);
	const char delim = '|';
	std::string line, name, score;
	while (std::getline(fin, line))
	{
		std::istringstream iss(line);
		std::getline(iss, name, delim);
		std::getline(iss, score, delim);
		this->participants.emplace_back(name, std::stoi(score));
	}
	fin.close();
}

void Repository::saveQuestions()
{
	std::ofstream fout(this->qFile);
	for (auto q : this->questions)
		fout << q.getId() << "|" << q.getText() << "|" << q.getCorrect() << "|" << q.getScore() << "\n";
	fout.close();
}

void Repository::saveParticipants()
{
	std::ofstream fout(this->pFile);
	for (auto p : this->participants)
		fout << p.getName() << "|" << p.getScore() << "\n";
	fout.close();
}