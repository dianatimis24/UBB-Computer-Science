#include "Utils.h"

void Utils::trimWhiteSpaces(std::string& stringToTrim)
{
    while (!stringToTrim.empty() && stringToTrim[0] == ' ')
        stringToTrim.erase(0, 1);
    while (!stringToTrim.empty() && stringToTrim[stringToTrim.size() - 1] == ' ')
        stringToTrim.erase(stringToTrim.size() - 1, 1);
}

std::vector<std::string> Utils::tokenizeString(std::string& stringToTokenize, char delimiter)
{
    std::vector<std::string> tokens;
    std::istringstream tokenStream(stringToTokenize);
    std::string token;
    while (getline(tokenStream, token, delimiter))
    {
        trimWhiteSpaces(token);
        tokens.push_back(token);
    }
    return tokens;
}