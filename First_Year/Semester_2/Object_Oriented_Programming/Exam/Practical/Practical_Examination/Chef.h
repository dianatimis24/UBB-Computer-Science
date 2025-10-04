#pragma once
#include <string>

class Chef
{
private:
	std::string name, speciality;

public:
	Chef(const std::string& name = "", const std::string& speciality = "") : name{ name }, speciality{ speciality } {}
	~Chef() {}
	std::string getName() { return this->name; }
	std::string getSpeciality() { return this->speciality; }
	void setName(std::string n) { this->name = n; }
	void setSpeciality(std::string s) { this->speciality = s; }
	std::string toString() { return this->name + "|" + this->speciality; }
};

