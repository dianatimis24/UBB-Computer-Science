#pragma once
#include <string>
#include <iostream>
#include <regex>
#include "Utils.h"
#include "DogValidator.h"

class Dog
{
private:
	std::string name, breed, photograph;
	int age;

public:
	/// Constructor with parameters
	Dog(const std::string& name = "", const std::string& breed = "", int age = 0, const std::string& photograph = "");

	/// Copy Constructor
	Dog(const Dog& dog);

	/// Destructor
	~Dog();

	/// Assignment Operator
	Dog& operator=(const Dog& dog);

	/// Equality Operator
	bool operator==(const Dog& dog) const;

	/// Operators
	friend std::ostream& operator<<(std::ostream& output, const Dog& dog);
	friend std::istream& operator>>(std::istream& input, Dog& dog);

	/// Getters for all the fields of the class Dog
	std::string getName() const;
	std::string getBreed() const;
	int getAge() const;
	std::string getPhotograph() const;

	/// Setters for all the fields of the class Dog
	void setName(const std::string& name);
	void setBreed(const std::string& breed);
	void setAge(int age);
	void setPhotograph(const std::string& photograph);

	/// A function that opens in the default browser the photograph of the dog from a given position in the repository.
	void openPhotographOfDogInBrowser();
};

