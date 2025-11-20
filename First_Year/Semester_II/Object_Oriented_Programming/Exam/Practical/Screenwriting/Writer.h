#pragma once
#include <string>

class Writer
{
private:
	std::string name, expertise;

public:
	Writer(const std::string& name = "", const std::string& expertise = "") : name{ name }, expertise{ expertise } {}
	~Writer() {}
	std::string getName() { return this->name; }
	std::string getExpertise() { return this->expertise; }
	void setName(std::string newName) { this->name = newName; }
	void setExpertise(std::string newExpertise) { this->expertise = newExpertise; }
};

