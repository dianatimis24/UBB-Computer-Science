#pragma once
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "Dog.h"

class DogExceptions : public std::exception 
{
private:
	std::vector<std::invalid_argument> errors;

public:
	/// Constructors
	DogExceptions(std::vector<std::invalid_argument> errors);
	DogExceptions(std::string error);

	/// Getter
	std::vector<std::invalid_argument> returnErrors();
};

class DogValidator
{
public:
	/// Validator for the name of a dog - the name must be a non-empty string
	static void validateName(const std::string& name);

	/// Validator for the breed of a dog - the breed must be a non-empty string
	static void validateBreed(const std::string& breed);

	/// Validator for the age of a dog - the age must be a positive integer
	static void validateAge(const std::string& ageAsString);

	/// Validator for the photograph of a dog - the photograph must be a non-empty string
	static void validatePhotograph(const std::string& photograph);

	/// Validator for the identifiers of a Dog
	static void validateDogIdentifiers(const std::string& name, const std::string& breed, const std::string& age, const std::string& photograph);
};

