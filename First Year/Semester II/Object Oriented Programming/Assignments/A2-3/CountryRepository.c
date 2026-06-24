#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CountryRepository.h"

CountryRepository* createCountryRepository() {
	CountryRepository* repository = (CountryRepository*)malloc(sizeof(CountryRepository));
	repository->dynamicArray = createDynamicArray(10, destroyCountry);
	return repository;
}

void destroyCountryRepository(CountryRepository* repository) {
	destroyDynamicArray(getDynamicArray(repository));
	free(repository);
}

int getCountryRepositoryLength(CountryRepository* repository) {
	return getLengthOfDynamicArray(getDynamicArray(repository));
}

void addCountryRepository(CountryRepository* repository, Country* country) {
	addElementToDynamicArray(getDynamicArray(repository), country);
}

void deleteCountryRepository(CountryRepository* repository, int position) {
	deleteElementFromDynamicArray(getDynamicArray(repository), position);
}

void updateCountryRepository(CountryRepository* repository, int position, Country* country) {
	updateElementOnPosition(getDynamicArray(repository), position, country);
}

int checkIfCountryIsInRepository(CountryRepository* repository, Country* country) {
	DynamicArray* array = getDynamicArray(repository);
	for (int i = 0; i < array->length; i++) {
		Country* currentCountry = getCountryFromRepository(repository, i);
		if (currentCountry && compareCountries(currentCountry, country) == 1)
			return i;
	}
	return -1;
}

Country* getCountryFromRepository(CountryRepository* repository, int position) {
	return (Country*)(getElementOnPosition(getDynamicArray(repository), position));
}

void sortCountriesBasedOnCondition(CountryRepository* repository, OperationOfComparisonBetweenCountries operationOfComparisonBetweenCountries) {
	for (int i = 0; i < getCountryRepositoryLength(repository) - 1; i++) {
		for (int j = i + 1; j < getCountryRepositoryLength(repository); j++) {
			Country* country1 = (Country*)getElementOnPosition(getDynamicArray(repository), i);
			Country* country2 = (Country*)getElementOnPosition(getDynamicArray(repository), j);
			if (operationOfComparisonBetweenCountries(country2, country1) > 0)
				swapElementsOnDynamicArray(getDynamicArray(repository), i, j);
		}
	}
}

void sortCountriesBasedOnCondition_2(CountryRepository* repository, OperationOfComparisonBetweenCountries operationOfComparisonBetweenCountries) {
	int swapped = 0;
	for (int i = 0; i < getCountryRepositoryLength(repository) - 1; i++) {
		swapped = 0;
		for (int j = 0; j < getCountryRepositoryLength(repository) - i - 1; j++) {
			Country* country1 = (Country*)getElementOnPosition(getDynamicArray(repository), j);
			Country* country2 = (Country*)getElementOnPosition(getDynamicArray(repository), j + 1);
			if (operationOfComparisonBetweenCountries(country2, country1) > 0) {
				swapElementsOnDynamicArray(getDynamicArray(repository), j, j + 1);
				swapped = 1;
			}
		}
		if (swapped == 0)
			break;
	}
}

DynamicArray* getDynamicArray(CountryRepository* repository)
{
	return repository->dynamicArray;
}

CountryRepository* copyRepository(CountryRepository* repository)
{
	CountryRepository* newRepository = createCountryRepository();
	int length = getCountryRepositoryLength(repository);
	for (int i = 0; i < length; ++i)
	{
		Country* country = getCountryFromRepository(repository, i);
		addCountryRepository(newRepository, copyCountry(country));
	}
	newRepository->dynamicArray->length = length;
	return newRepository;
}

void setRepository(CountryRepository* repository, CountryRepository* anotherRepository)
{
	destroyCountryRepository(repository);
	repository = copyRepository(anotherRepository);
}