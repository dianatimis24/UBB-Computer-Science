#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Utils
{
public:
	/// A function that erases the white spaces from the beginning and from the ending of a given string.
	void trimWhiteSpaces(std::string& stringToTrim);

	/// A function that divides a given string into several string, based on a given delimiter character.
	std::vector<std::string> tokenizeString(std::string& stringToTokenize, char delimiter);
};