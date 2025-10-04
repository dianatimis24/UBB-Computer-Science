#pragma once
#include <string>
#include <exception>

class InvalidPositionException : public std::exception
{
private:
	std::string message;

public:
	InvalidPositionException();
	InvalidPositionException(const std::string& message);
	~InvalidPositionException() {}
	const char* what();
};

class DescriptionException : public std::exception
{
private:
	std::string message;

public:
	DescriptionException();
	DescriptionException(const std::string& message);
	~DescriptionException() {}
	const char* what();
};

