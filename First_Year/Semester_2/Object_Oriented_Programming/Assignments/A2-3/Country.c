#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Country.h"

Country* createCountry(const char* name, const char* continent, const float population) {
	Country *country = (Country*)malloc(sizeof(Country));
	country->name = (char*)malloc(strlen(name) + 1);
	strcpy(country->name, name);
	country->continent = (char*)malloc(strlen(continent) + 1);
	strcpy(country->continent, continent);
	country->population = population;
	return country;
}

Country* copyCountry(Country* country) {
	return createCountry(getName(country), getContinent(country), getPopulation(country));
}

void destroyCountry(Country* country) {
	if (country) {
		if (getName(country))
			free(country->name);
		if (getContinent(country))
			free(country->continent);
		free(country);
	}
}

char* getName(Country* country) {
	return country->name;
}

char* getContinent(Country* country) {
	return country->continent;
}

float getPopulation(Country* country) {
	return country->population;
}

int countryContainsString(Country* country, char* string) {
	return (strstr(getName(country), string) != NULL);
}

int countryDoesNotContainString(Country* country, char* string) {
	return !(countryContainsString(country, string));
}

int compareCountries(Country* country1, Country* country2) {
	if (strcmp(getName(country1), getName(country2)) == 0)
		return 1;
	return 0;
}

int firstCountrySmallerPopulation(Country* country1, Country* country2) {
	return (getPopulation(country1) < getPopulation(country2));
}

int firstCountryGreaterPopulation(Country* country1, Country* country2) {
	return (getPopulation(country1) > getPopulation(country2));
}

int firstCountrySmallerName(Country* country1, Country* country2) {
	return strcmp(getName(country1), getName(country2)) < 0;
}

char* formatCountryAsString(Country* country) {
	char* string = (char*)malloc(sizeof(char) * 3000);
	sprintf(string, "%s %s %.3f", getName(country), getContinent(country), getPopulation(country));
	return string;
}
