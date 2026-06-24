#include "Dog.h"
#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

Dog::Dog(const std::string& name, const std::string& breed, int age, const std::string& photograph) : name{ name }, breed{ breed }, age{ age }, photograph{ photograph } {}

Dog::Dog(const Dog& dog)
{
	this->name = dog.name;
	this->breed = dog.breed;
	this->age = dog.age;
	this->photograph = dog.photograph;
}

Dog::~Dog() {}

Dog& Dog::operator=(const Dog& dog)
{
	if (this == &dog)
		return *this;
	this->name = dog.name;
	this->breed = dog.breed;
	this->age = dog.age;
	this->photograph = dog.photograph;
	return *this;
}

bool Dog::operator==(const Dog& dog) const
{
	return this->name == dog.name && this->breed == dog.breed && this->age == dog.age;
}

std::string Dog::getName() const
{
	return this->name;
}

std::string Dog::getBreed() const
{
	return this->breed;
}

int Dog::getAge() const
{
	return this->age;
}

std::string Dog::getPhotograph() const
{
	return this->photograph;
}

void Dog::setName(const std::string& name)
{
	this->name = name;
}

void Dog::setBreed(const std::string& breed)
{
	this->breed = breed;
}

void Dog::setAge(int age)
{
	this->age = age;
}

void Dog::setPhotograph(const std::string& photograph)
{
	this->photograph = photograph;
}

void Dog::openPhotographOfDogInBrowser()
{
	std::string linkOfPhotograph = this->getPhotograph();
	const char* url = linkOfPhotograph.c_str();
	ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWNORMAL);
}

std::ostream& operator<<(std::ostream& output, const Dog& dog)
{
	output << dog.getName() << " | " << dog.getBreed() << " | " << dog.getAge() << " | " << dog.getPhotograph();
	return output;
}

std::istream& operator>>(std::istream& input, Dog& dog)
{
	Utils utilFunctionsToWorkWithStrings;

	std::string lineWithContentOfDog;
	std::getline(input, lineWithContentOfDog);

	std::vector<std::string> vectorWithTokens = utilFunctionsToWorkWithStrings.tokenizeString(lineWithContentOfDog, '|');

	int numberOfArguments = vectorWithTokens.size();
	if (numberOfArguments != 4)
		throw DogExceptions("The provided number of arguments is not ok! Expected 4 arguments, received " + std::to_string(numberOfArguments) + " arguments.");

	const std::string& name = vectorWithTokens[0], & breed = vectorWithTokens[1], & age = vectorWithTokens[2], & photograph = vectorWithTokens[3];

	DogValidator::validateDogIdentifiers(name, breed, age, photograph);

	dog.setName(name);
	dog.setBreed(breed);
	dog.setAge(std::stoi(age));
	dog.setPhotograph(photograph);

	return input;
}