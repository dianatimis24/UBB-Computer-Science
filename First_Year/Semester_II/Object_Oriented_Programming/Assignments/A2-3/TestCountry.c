#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "TestCountry.h"
#include "Country.h"

void testCountryCreateAndDelete()
{
	Country* country = createCountry("Romania", "Europe", 19.2);
	assert(country != NULL);
	assert(strcmp(getName(country), "Romania") == 0);
	assert(strcmp(getContinent(country), "Europe") == 0);
	assert(getPopulation(country) == (float)19.2);
	destroyCountry(country);
}

void testCountryCopy()
{
	Country* country = createCountry("Romania", "Europe", 19.2);
	Country* copy = copyCountry(country);
	assert(copy != NULL);
	assert(strcmp(getName(copy), "Romania") == 0);
	assert(strcmp(getContinent(copy), "Europe") == 0);
	assert(getPopulation(copy) == (float)19.2);
	destroyCountry(country);
	destroyCountry(copy);
}

void testCountryFormat()
{
	Country* country = createCountry("Romania", "Europe", 19.2);
	char* string = formatCountryAsString(country);
	assert(string != NULL);
	assert(strcmp(string, "Romania Europe 19.200") == 0);
	destroyCountry(country);
	free(string);
}

void testCountryComparisons()
{
	Country* country1 = createCountry("Romania", "Europe", 19.2);
	Country* country2 = createCountry("Slovakia", "Europe", 7.3);
	Country* country3 = createCountry("Romania", "Europe", 19.2);
	assert(compareCountries(country1, country2) == 0);
	assert(compareCountries(country2, country1) == 0);
	assert(compareCountries(country1, country3));
	assert(compareCountries(country3, country1));
	assert(countryContainsString(country1, "Ro") == 1);
	assert(countryContainsString(country1, "Slovakia") == 0);
	assert(countryDoesNotContainString(country1, "Ro") == 0);
	assert(countryDoesNotContainString(country1, "Slovakia") == 1);
	assert(firstCountryGreaterPopulation(country1, country2) == 1);
	assert(firstCountrySmallerPopulation(country1, country2) == 0);
	destroyCountry(country1);
	destroyCountry(country2);
	destroyCountry(country3);
}

void testCountryAll()
{
	testCountryCreateAndDelete();
	testCountryCopy();
	testCountryFormat();
	testCountryComparisons();
}