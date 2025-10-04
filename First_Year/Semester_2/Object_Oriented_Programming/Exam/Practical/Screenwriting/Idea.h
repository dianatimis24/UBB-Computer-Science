#pragma once
#include <string>

class Idea
{
private:
	std::string description, status, creator;
	int act;

public:
	Idea(const std::string& description = "", const std::string& creator = "", int act = 0, const std::string& status = "proposed") : description{description}, creator{creator}, act{act}, status{ status } {}
	~Idea() {}
	std::string getDescription() { return this->description; }
	std::string getStatus() { return this->status; }
	std::string getCreator() { return this->creator; }
	int getAct() { return this->act; }
	void setDescription(std::string d) { this->description = d; }
	void setStatus(std::string s) { this->status = s; }
	void setCreator(std::string c) { this->creator = c; }
	void setAct(int a) { this->act = a; }
};

