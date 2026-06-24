#include "Service.h" 

std::vector<User> Service::getUsers()
{
	return this->repository->getUsers();
}

std::vector<Issue> Service::getIssues()
{
	return this->repository->getIssues();
}

void Service::addIssue(const std::string& description, const std::string& status, const std::string& reporter, const std::string& solver)
{
	if (description.empty())
		throw DescriptionException("Empty description!");
	if (this->repository->issueExists(description))
		throw DescriptionException("Already existing description!");
	Issue issue{ description, status, reporter, solver };
	this->repository->addIssue(issue);
	this->notify();
}

void Service::removeIssue(int index)
{
	if (0 > index || index >= this->repository->getIssues().size())
		throw InvalidPositionException("Invalid position!");
	this->repository->removeIssue(index);
	this->notify();
}

void Service::resolveIssue(int index, const std::string& solver)
{
	if (0 > index || index >= this->repository->getIssues().size())
		throw InvalidPositionException("Invalid position!");
	this->repository->resolveIssue(index, solver);
	this->notify();
}

bool Service::issueExists(const std::string& descr)
{
	return this->repository->issueExists(descr);
}
