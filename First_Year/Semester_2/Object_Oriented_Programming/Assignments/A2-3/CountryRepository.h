#pragma once
#include "Country.h"
#include "DynamicArray.h"

typedef struct {
	DynamicArray* dynamicArray;
} CountryRepository;

/// <summary>
/// A function that creates a new repository.
/// </summary>
/// <returns>A pointer to the newly allocated repository</returns>
CountryRepository* createCountryRepository();

/// <summary>
/// A function that desroys a given repository.
/// </summary>
/// <param name="repository">A pointer to the repository that is about to be destroyed</param>
void destroyCountryRepository(CountryRepository* repository);

/// <summary>
/// A function that returns the number of the countries in the repository.
/// </summary>
/// <param name="repository">A pointer to the repository</param>
/// <returns>The number of the countries in the repository</returns>
int getCountryRepositoryLength(CountryRepository* repository);

/// <summary>
/// A function that adds a country to the repository.
/// </summary>
/// <param name="repository">A pointer to the repository</param>
/// <param name="country">The country that will be added to the repository</param>
void addCountryRepository(CountryRepository* repository, Country* country);

/// <summary>
/// A function that deletes a country from the repository.
/// </summary>
/// <param name="repository">A pointer to the repository</param>
/// <param name="position">The country that will be deleted from the repository</param>
void deleteCountryRepository(CountryRepository* repository, int position);

/// <summary>
/// A function that updates a country from the repository.
/// </summary>
/// <param name="repository">A pointer to the repository</param>
/// <param name="position">The position in the repository of the country that will be updated.</param>
/// <param name="country">The values of the updated country</param>
void updateCountryRepository(CountryRepository* repository, int position, Country* country);

/// <summary>
/// A function that checks if a given country is in the repository.
/// </summary>
/// <param name="repository">A pointer to the repository</param>
/// <param name="country">The searched country</param>
/// <returns>1 if the country is in the repository, 0 otherwise</returns>
int checkIfCountryIsInRepository(CountryRepository* repository, Country* country);

/// <summary>
/// A function that gets the country from a given position in the repository.
/// </summary>
/// <param name="repository">A pointer to the repository</param>
/// <param name="position">The position of the wanted country</param>
/// <returns>A pointer to the wanted country</returns>
Country* getCountryFromRepository(CountryRepository* repository, int position);

/// <summary>
/// A function that sorts (using Exchange Sort) the countries from the repository, based on a comparision function.
/// </summary>
/// <param name="repository">A pointer to the repository</param>
/// <param name="operationOfComparisonBetweenCountries">The comparison operation</param>
void sortCountriesBasedOnCondition(CountryRepository* repository, OperationOfComparisonBetweenCountries operationOfComparisonBetweenCountries);

/// <summary>
/// A function that sorts (using Bubble Sort) the countries from the repository, based on a comparision function.
/// </summary>
/// <param name="repository">A pointer to the repository</param>
/// <param name="operationOfComparisonBetweenCountries">The comparison operation</param>
void sortCountriesBasedOnCondition_2(CountryRepository* repository, OperationOfComparisonBetweenCountries operationOfComparisonBetweenCountries);

/// <summary>
/// A function that returns the dynamic array of countries from the repository.
/// </summary>
/// <param name="repository">A pointer to the repository</param>
/// <returns>The dynamic array of countries</returns>
DynamicArray* getDynamicArray(CountryRepository* repository);

/// <summary>
/// A function that copies a repository.
/// </summary>
/// <param name="repository">A pointer to the repository</param>
/// <returns>A pointer to the copy of the initial repository</returns>
CountryRepository* copyRepository(CountryRepository* repository);

/// <summary>
/// A function that sets the content of the current repository with the content from another repository.
/// </summary>
/// <param name="repository">A pointer to the initial repository</param>
/// <param name="anotherRepository">A pointer to the another repository</param>
void setRepository(CountryRepository* repository, CountryRepository* anotherRepository);