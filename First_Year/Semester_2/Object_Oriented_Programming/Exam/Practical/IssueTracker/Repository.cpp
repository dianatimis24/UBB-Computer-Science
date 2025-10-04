#include "Repository.h" 
#include <sstream>
#include <algorithm>

Repository::Repository(const std::string& u, const std::string& i) : uFile{ u }, iFile{ i }
{
	this->loadUsers();
	this->loadIssues();
}

Repository::~Repository()
{
	this->saveIssues();
}

void Repository::loadUsers()
{
	std::ifstream fin(this->uFile);
	const char delim = '|';
	std::string line, name, type;
	while (std::getline(fin, line))
	{
		std::istringstream iss(line);
		std::getline(iss, name, delim);
		std::getline(iss, type, delim);
		this->users.emplace_back(name, type);
	}
	fin.close();
}

void Repository::loadIssues()
{
	std::ifstream fin(this->iFile);
	const char delim = '|';
	std::string line, description, status, reporter, solver;
	while (std::getline(fin, line))
	{
		std::istringstream iss(line);
		std::getline(iss, description, delim);
		std::getline(iss, status, delim);
		std::getline(iss, reporter, delim);
		std::getline(iss, solver, delim);
		this->issues.emplace_back(description, status, reporter, solver);
	}
	std::sort(this->issues.begin(), this->issues.end());
	fin.close();
}

void Repository::saveIssues()
{
	std::ofstream fout(this->iFile);
	for (auto issue : this->issues)
		fout << issue.getDescription() << "|" << issue.getStatus() << "|" << issue.getReporter() << "|" << issue.getSolver() << "\n";
	fout.close();
}

std::vector<User> Repository::getUsers()
{
	return this->users;
}

std::vector<Issue> Repository::getIssues()
{
	return this->issues;
}

void Repository::addIssue(Issue issue)
{
	this->issues.push_back(issue);
}

void Repository::removeIssue(int index)
{
	this->issues.erase(this->issues.begin() + index);
}

void Repository::resolveIssue(int index, const std::string& solver)
{
	this->issues[index].setStatus("closed");
	this->issues[index].setSolver(solver);
}

bool Repository::issueExists(const std::string& descr)
{
	for (auto issue : this->issues)
		if (issue.getDescription() == descr)
			return true;
	return false;
}