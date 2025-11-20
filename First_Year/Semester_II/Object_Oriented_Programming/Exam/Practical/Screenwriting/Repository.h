#pragma once
#include "Writer.h"
#include "Idea.h"
#include <vector>
#include <fstream>

class Repository
{
private:
	std::vector<Writer> writers;
	std::vector<Idea> ideas;
	std::string wFile, iFile, acceptedFile;

public:
	Repository(const std::string& w, const std::string& i, const std::string& acc);
	~Repository();
	std::vector<Writer> getWriters();
	std::vector<Idea> getIdeas();
	void addIdea(Idea idea);
	void changeStatus(int index);
	void changeDescription(int index, std::string newDescr);
	void saveToFile();
	void saveIdeas();
	void loadWriters();
	void loadIdeas();
};

