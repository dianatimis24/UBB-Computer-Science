#include "Repository.h" 
#include <sstream>

Repository::Repository(const std::string& w, const std::string& i, const std::string& acc) : wFile{ w }, iFile{ i }, acceptedFile{ acc }
{
	this->loadWriters();
	this->loadIdeas();
}

Repository::~Repository()
{
	this->saveIdeas();
}

std::vector<Writer> Repository::getWriters()
{
	return this->writers;
}

std::vector<Idea> Repository::getIdeas()
{
	return this->ideas;
}

void Repository::addIdea(Idea idea)
{
	this->ideas.push_back(idea);
}

void Repository::changeStatus(int index)
{
	this->ideas[index].setStatus("accepted");
}

void Repository::changeDescription(int index, std::string newDescr)
{
	this->ideas[index].setDescription(newDescr);
}


void Repository::saveToFile()
{
	std::ofstream fout(this->acceptedFile);
	fout << "Act 1\n";
	for (auto i : this->ideas)
		if (i.getAct() == 1 && i.getStatus() == "accepted")
			fout << i.getDescription() << " (" << i.getCreator() << ")\n";
	fout << "Act 2\n";
	for (auto i : this->ideas)
		if (i.getAct() == 2 && i.getStatus() == "accepted")
			fout << i.getDescription() << " (" << i.getCreator() << ")\n";
	fout << "Act 3\n";
	for (auto i : this->ideas)
		if (i.getAct() == 3 && i.getStatus() == "accepted")
			fout << i.getDescription() << " (" << i.getCreator() << ")\n";
	fout.close();
}

void Repository::saveIdeas()
{
	std::ofstream fout(this->iFile);
	for (auto i : this->ideas)
		fout << i.getDescription() << "|" << i.getStatus() << "|" << i.getCreator() << "|" << std::to_string(i.getAct()) << "\n";
	fout.close();
}

void Repository::loadWriters()
{
	std::ifstream fin(this->wFile);
	const char delim = '|';
	std::string line, name, expertise;
	while (std::getline(fin, line))
	{
		std::istringstream iss(line);
		std::getline(iss, name, delim);
		std::getline(iss, expertise, delim);
		this->writers.emplace_back(name, expertise);
	}
	fin.close();
}

void Repository::loadIdeas()
{
	std::ifstream fin(this->iFile);
	const char delim = '|';
	std::string line, description, status, creator, act;
	while (std::getline(fin, line))
	{
		std::istringstream iss(line);
		std::getline(iss, description, delim);
		std::getline(iss, status, delim);
		std::getline(iss, creator, delim);
		std::getline(iss, act, delim);
		this->ideas.emplace_back(description, creator, std::stoi(act), status);
	}
	fin.close();
}
