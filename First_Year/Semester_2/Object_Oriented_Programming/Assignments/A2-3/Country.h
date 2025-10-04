#pragma once

typedef struct {
	char *name;
	char *continent;
	float population;
} Country;

typedef int (*OperationOfComparison)(Country*, char*);
typedef int (*OperationOfComparisonBetweenCountries)(Country*, Country*);

/// <summary>
/// A functions that creates a country with the given parameters.
/// </summary>
/// <param name="name">The name of the country</param>
/// <param name="continent">The continent of the country</param>
/// <param name="population">The population of the country</param>
/// <returns>A pointer to the newly allocated country</returns>
Country* createCountry(char* name, char* continent, float population);

/// <summary>
/// A function that copies a country.
/// </summary>
/// <param name="country">The initial country</param>
/// <returns>A pointer to the copy of the initial country</returns>
Country* copyCountry(Country* country);

/// <summary>
/// A functions that destroys a country.
/// </summary>
/// <param name="country">A pointer to the country that is about to be destroyed</param>
void destroyCountry(Country* country);

/// <summary>
/// A functions that return the name of the country.
/// </summary>
/// <param name="country">A pointer to the country</param>
/// <returns>The pointer to the string containing the name of the country</returns>
char* getName(Country* country);

/// <summary>
/// A functions that return the continent of the country.
/// </summary>
/// <param name="country">A pointer to the country</param>
/// <returns>The pointer to the string containing the continent of the country</returns>
char* getContinent(Country* country);

/// <summary>
/// A functions that return the population of the country.
/// </summary>
/// <param name="country">A pointer to the country</param>
/// <returns>The value of the population of the country</returns>
float getPopulation(Country* country);

/// <summary>
/// A function that checks is the name of the given country contains a given string.
/// </summary>
/// <param name="country">A pointer to the country</param>
/// <param name="string">A pointer to the string</param>
/// <returns>1 if the name of the country contains the given string, 0 otherwise</returns>
int countryContainsString(Country* country, char* string);

/// <summary>
/// A function that checks is the name of the given country contains a given string.
/// </summary>
/// <param name="country">A pointer to the country</param>
/// <param name="string">A pointer to the string</param>
/// <returns>0 if the name of the country contains the given string, 1 otherwise</returns>
int countryDoesNotContainString(Country* country, char* string);

/// <summary>
/// A function that compares two countries by their name.
/// </summary>
/// <param name="country1"></param>
/// <param name="country2"></param>
/// <returns>1 if the countries have the same name, 0 otherwise</returns>
int compareCountries(Country* country1, Country* country2);

/// <summary>
/// A function that checks if the first given country has a smaller population than the second one.
/// </summary>
/// <param name="country1">the first given country</param>
/// <param name="country2">the second given country</param>
/// <returns>1 if the first country has a smaller populationn, 0 otherwise</returns>
int firstCountrySmallerPopulation(Country* country1, Country* country2);

/// <summary>
/// A function that checks if the first given country has a greater population than the second one.
/// </summary>
/// <param name="country1">the first given country</param>
/// <param name="country2">the second given country</param>
/// <returns>1 if the first country has a greater populationn, 0 otherwise</returns>
int firstCountryGreaterPopulation(Country* country1, Country* country2);

int firstCountrySmallerName(Country* country1, Country* country2);

/// <summary>
/// A function that creates a string from a given country.
/// </summary>
/// <param name="country">the given country</param>
/// <returns>the string corresponding to that contry</returns>
char* formatCountryAsString(Country* country);