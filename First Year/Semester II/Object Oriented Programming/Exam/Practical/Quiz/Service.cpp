#include "Service.h" 
#include <algorithm>

std::vector<Participant> Service::getParticipants()
{
	return this->repository->getParticipants();
}

std::vector<Question> Service::getQuestions()
{
	return this->repository->getQuestions();
}

std::vector<Question> Service::getQuestionsIncreasingId()
{
	std::vector<Question> questions = this->repository->getQuestions();;
	std::sort(questions.begin(), questions.end());
	return questions;
}

std::vector<Question> Service::getQuestionsDecreasingScore()
{
	std::vector<Question> questions = this->repository->getQuestions();;
	std::sort(questions.begin(), questions.end(), [](Question a, Question b) {
		return a.getScore() > b.getScore();
	});
	return questions;
}

void Service::addQuestion(int id, const std::string& text, const std::string& correct, int score)
{
	if (text == "")
		throw std::exception();
	bool another = false;
	for (auto q : this->repository->getQuestions())
		if (q.getId() == id)
		{
			another = true;
			break;
		}
	if (another)
		throw std::exception();

	Question question{ id, text, correct, score };
	this->repository->addQuestion(question);
}

void Service::changeScoreOfAParticipant(std::string name, int newScore)
{
	int index = 0;
	for (auto p : this->repository->getParticipants())
	{
		if (p.getName() == name)
			this->repository->changeScoreOfAParticipant(index, newScore);
		index++;
	}
}
