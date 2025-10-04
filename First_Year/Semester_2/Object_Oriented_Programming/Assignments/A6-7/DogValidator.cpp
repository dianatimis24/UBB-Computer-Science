#include "DogValidator.h"

DogExceptions::DogExceptions(std::vector<std::invalid_argument> errors)
{
	this->errors = errors;
}

DogExceptions::DogExceptions(std::string error)
{
	this->errors.push_back(std::invalid_argument(error));
}

std::vector<std::invalid_argument> DogExceptions::returnErrors()
{
	return this->errors;
}

void DogValidator::validateName(const std::string& name)
{
	if (name.empty())
		throw std::invalid_argument("The name must be a non-empty string!");
}

void DogValidator::validateBreed(const std::string& breed)
{
	if (breed.empty())
		throw std::invalid_argument("The breed must be a non-empty string!");
}

void DogValidator::validateAge(const std::string& ageAsString)
{
	int ageAsInteger;
	try
	{
		ageAsInteger = std::stoi(ageAsString);
	}
	catch (const std::exception& error)
	{
		throw std::invalid_argument("The age must be an integer!");
	}

	if (ageAsInteger < 0)
		throw std::invalid_argument("The age must be a positive integer!");
}

void DogValidator::validatePhotograph(const std::string& photograph)
{
	const std::regex pattern("((http|https)://)(www.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");
	if (!std::regex_match(photograph, pattern))
		throw std::invalid_argument("Invalid photograph link!");
}

void DogValidator::validateDogIdentifiers(const std::string& name, const std::string& breed, const std::string& age, const std::string& photograph)
{
	std::vector<std::invalid_argument> errors;
	try
	{
		validateName(name);
	}
	catch (const std::invalid_argument& error)
	{
		errors.push_back(error);
	}

	try
	{
		validateBreed(breed);
	}
	catch (const std::invalid_argument& error)
	{
		errors.push_back(error);
	}

	try
	{
		validateAge(age);
	}
	catch (const std::invalid_argument& error)
	{
		errors.push_back(error);
	}

	try
	{
		validatePhotograph(photograph);
	}
	catch (const std::invalid_argument& error)
	{
		errors.push_back(error);
	}

	if (errors.size() > 0)
		throw DogExceptions(errors);
}