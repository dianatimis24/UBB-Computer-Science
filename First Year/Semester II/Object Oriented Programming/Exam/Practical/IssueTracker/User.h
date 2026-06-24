#pragma once
#include <string>

class User
{
private:
	std::string name, type;

public:
	User(const std::string& name = "", const std::string& type = "") : name{ name }, type{ type } {}
	~User() {}
	std::string getName() { return this->name; }
	std::string getType() { return this->type; }
};

