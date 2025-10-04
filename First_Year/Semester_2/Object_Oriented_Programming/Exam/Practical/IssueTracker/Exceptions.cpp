#include "Exceptions.h"

InvalidPositionException::InvalidPositionException() : std::exception()
{
	this->message = "";
}

InvalidPositionException::InvalidPositionException(const std::string& message)
{
	this->message = message;
}

const char* InvalidPositionException::what()
{
	return this->message.c_str();
}

DescriptionException::DescriptionException() : std::exception()
{
	this->message = "";
}

DescriptionException::DescriptionException(const std::string& message)
{
	this->message = message;
}

const char* DescriptionException::what()
{
	return this->message.c_str();
}