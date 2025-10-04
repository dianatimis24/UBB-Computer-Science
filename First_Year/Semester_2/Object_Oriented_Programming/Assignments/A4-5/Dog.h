#pragma once
#include <string>
#include <iostream>
#include <regex>

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

	/// Validator for the name of a dog - the name must be a non-empty string
	void validateName(const std::string& name);

	/// Validator for the breed of a dog - the breed must be a non-empty string
	void validateBreed(const std::string& breed);

	/// Validator for the age of a dog - the age must be a positive integer
	void validateAge(int age);

	/// Validator for the photograph of a dog - the photograph must be a non-empty string
	void validatePhotograph(const std::string& photograph);

	/// Validator for the current Dog
	void validateDog();
};

