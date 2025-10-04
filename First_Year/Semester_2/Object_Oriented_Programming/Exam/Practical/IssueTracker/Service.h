#pragma once
#include "Repository.h"
#include "Subject.h"
#include "Exceptions.h"

class Service : public Subject
{
private:
	Repository* repository;

public:
	Service(Repository* repository) : repository{ repository } {}
	~Service() {}
	std::vector<User> getUsers();
	std::vector<Issue> getIssues();
	void addIssue(const std::string& description, const std::string& status, const std::string& reporter, const std::string& solver);
	void removeIssue(int index);
	void resolveIssue(int index, const std::string& solver);
	bool issueExists(const std::string& descr);
};

