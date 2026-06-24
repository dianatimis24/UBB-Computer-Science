#include "Dog.h"
#include <iostream>
#include <string>
#include <sstream>

Dog::Dog(const std::string& name, const std::string& breed, int age, const std::string& photograph) : name{name}, breed{breed}, age{age}, photograph{photograph} {}

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

void Dog::validateName(const std::string& name)
{
	if (name == "")
		throw std::invalid_argument("The name must be a non-empty string!");
}

void Dog::validateBreed(const std::string& breed)
{
	if (breed == "")
		throw std::invalid_argument("The breed must be a non-empty string!");
}

void Dog::validateAge(int age)
{
	if (age < 0)
		throw std::invalid_argument("The age must be a positive integer!");
}

void Dog::validatePhotograph(const std::string& photograph)
{
	const std::regex pattern("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
	if (!std::regex_match(photograph, pattern))
		throw std::invalid_argument("Invalid photograph link!");
}

void Dog::validateDog()
{
	validateName(this->name);
	validateBreed(this->breed);
	validateAge(this->age);
	validatePhotograph(this->photograph);
}

void Dog::setName(const std::string& name)
{
	this->validateName(name);
	this->name = name;
}

void Dog::setBreed(const std::string& breed)
{
	this->validateBreed(breed);
	this->breed = breed;
}

void Dog::setAge(int age)
{
	this->validateAge(age);
	this->age = age;
}

void Dog::setPhotograph(const std::string& photograph)
{
	this->validatePhotograph(photograph);
	this->photograph = photograph;
}
