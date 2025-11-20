#include "Service.h" 

std::vector<Writer> Service::getWriters()
{
	return this->repository->getWriters();
}

std::vector<Idea> Service::getIdeas()
{
	return this->repository->getIdeas();
}

void Service::addIdea(std::string description, std::string creator, int act)
{
	if (description == "" || act < 1 || act > 3)
		throw std::exception();
	for (auto i : this->repository->getIdeas())
		if (i.getAct() == act && i.getDescription() == description)
			throw std::exception();

	Idea idea(description, creator, act);
	this->repository->addIdea(idea);
}

void Service::changeStatus(int index)
{
	this->repository->changeStatus(index);
}

void Service::changeDescription(int index, std::string newDescr)
{
	this->repository->changeDescription(index, newDescr);
}

void Service::saveToFile()
{
	this->repository->saveToFile();
}

void Service::saveIdeas()
{
	this->repository->saveIdeas();
}
