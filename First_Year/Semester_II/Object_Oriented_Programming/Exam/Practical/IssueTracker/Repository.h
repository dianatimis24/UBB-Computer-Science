#pragma once
#include "User.h"
#include "Issue.h"
#include <vector>
#include <fstream>

class Repository
{
private:
	std::vector<User> users;
	std::vector<Issue> issues;
	std::string uFile, iFile;

public:
	Repository(const std::string& u, const std::string& i);
	~Repository();
	void loadUsers();
	void loadIssues();
	void saveIssues();
	std::vector<User> getUsers();
	std::vector<Issue> getIssues();
	void addIssue(Issue issue);
	void removeIssue(int index);
	void resolveIssue(int index, const std::string& solver);
	bool issueExists(const std::string& descr);
};

