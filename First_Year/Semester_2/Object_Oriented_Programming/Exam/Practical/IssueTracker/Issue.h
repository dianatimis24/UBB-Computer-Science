#pragma once
#include <string>

class Issue
{
private:
	std::string description, status, reporter, solver;

public:
	Issue(const std::string& description = "", const std::string& status = "", const std::string& reporter = "", const std::string& solver = "") : description{description}, status{status}, reporter{reporter}, solver{solver} {}
	~Issue() {}
	std::string getDescription() { return this->description; }
	std::string getStatus() { return this->status; }
	std::string getReporter() { return this->reporter; }
	std::string getSolver() { return this->solver; }
	void setDescription(std::string d) { this->description = d; }
	void setStatus(std::string st) { this->status = st; }
	void setReposter(std::string r) { this->reporter = r; }
	void setSolver(std::string s) { this->solver = s; }
	bool operator < (const Issue& other) const {
		if (this->status == other.status)
			return this->description < other.description;
		return this->status < other.status;
	}
};

