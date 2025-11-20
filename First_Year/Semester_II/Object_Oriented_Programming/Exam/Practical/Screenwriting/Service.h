#pragma once
#include "Repository.h"

class Service
{
private:
	Repository* repository;

public:
	Service(Repository* repository) : repository{ repository } {}
	~Service() {}
	std::vector<Writer> getWriters();
	std::vector<Idea> getIdeas();
	void addIdea(std::string description, std::string creator, int act);
	void changeStatus(int index);
	void changeDescription(int index, std::string newDescr);
	void saveToFile();
	void saveIdeas();
};

