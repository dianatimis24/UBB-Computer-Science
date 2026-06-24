#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "CountryService.h"
#include "DynamicArray.h"

CountryService* createCountryService(CountryRepository* repository, UndoRedoRepository* undoRedoRepository, int typeOfUndoRedo) {
	CountryService* service = (CountryService*)malloc(sizeof(CountryService));
	service->repository = repository;
	service->undoRedoRepository = undoRedoRepository;
	service->typeOfUndoRedo = typeOfUndoRedo;
	return service;
}

void destroyCountryService(CountryService* service) {
	destroyCountryRepository(getRepository(service));
	destroyUndoRedoRepository(getUndoRedoRepository(service));
	free(service);
}

int getTypeOfUndoRedo(CountryService* service) {
	return service->typeOfUndoRedo;
}

CountryRepository* getRepository(CountryService* service) {
	return service->repository;
}

UndoRedoRepository* getUndoRedoRepository(CountryService* service) {
	return service->undoRedoRepository;
}

int addCountryService(CountryService* service, Country* country) {
	int indexOfExistingCountry = checkIfCountryIsInRepository(getRepository(service), country);
	if (indexOfExistingCountry == -1)
	{
		if (getTypeOfUndoRedo(service) == 1)
		{
			resetRedoOperations(getUndoRedoRepository(service));
			addUndoOperation(getUndoRedoRepository(service), createOperation(2, country, NULL));
		}
		else
		{
			resetRedoDynamicArray(getUndoRedoRepository(service));
			DynamicArray* dynamicArray = copyDynamicArrayOfCountries(getDynamicArray(getRepository(service)));
			addUndoDynamicArray(getUndoRedoRepository(service), dynamicArray);
		}
		addCountryRepository(getRepository(service), country);
		return 1;
	}
	return 0;
}

int deleteCountryService(CountryService* service, Country* country) {
	int indexOfExistingCountry = checkIfCountryIsInRepository(getRepository(service), country);
	if (indexOfExistingCountry == -1)
		return 0;
	
	if (getTypeOfUndoRedo(service) == 1)
	{
		resetRedoOperations(getUndoRedoRepository(service));
		addUndoOperation(getUndoRedoRepository(service), createOperation(1, country, NULL));
	}
	else
	{
		resetRedoDynamicArray(getUndoRedoRepository(service));
		DynamicArray* dynamicArray = copyDynamicArrayOfCountries(getDynamicArray(getRepository(service)));
		addUndoDynamicArray(getUndoRedoRepository(service), dynamicArray);
	}
	deleteCountryRepository(getRepository(service), indexOfExistingCountry);
	return 1;
}

int updateCountryService(CountryService* service, Country* country, Country* newCountry) {
	int indexOfExistingCountry = checkIfCountryIsInRepository(getRepository(service), country);
	destroyCountry(country);
	if (indexOfExistingCountry == -1)
	{
		destroyCountry(newCountry);
		return 0;
	}
	
	if (getTypeOfUndoRedo(service) == 1)
	{
		resetRedoOperations(getUndoRedoRepository(service));
		Country* countryFromRepository = getCountryFromRepository(getRepository(service), indexOfExistingCountry);
		addUndoOperation(getUndoRedoRepository(service), createOperation(3, newCountry, countryFromRepository));
	}
	else
	{
		resetRedoDynamicArray(getUndoRedoRepository(service));
		DynamicArray* dynamicArray = copyDynamicArrayOfCountries(getDynamicArray(getRepository(service)));
		addUndoDynamicArray(getUndoRedoRepository(service), dynamicArray);
	}
	updateCountryRepository(getRepository(service), indexOfExistingCountry, newCountry);
	return 1;
}

int undoRedoService(CountryService* service, DynamicArray* undoFromThisArray, DynamicArray* redoToThisArray) {
	if (getTypeOfUndoRedo(service) == 1)
	{
		if (getLengthOfDynamicArray(undoFromThisArray) == 0)
			return 0;
		Operation* operation = (Operation*)getElementOnPosition(undoFromThisArray, getLengthOfDynamicArray(undoFromThisArray) - 1);
		Operation* operationToBeAddedToRedo = NULL;

		if (getTypeOfOperation(operation) == 1)
		{
			addCountryRepository(getRepository(service), copyCountry(getCountry1(operation)));
			operationToBeAddedToRedo = createOperation(2, getCountry1(operation), NULL);
		}
		else if (getTypeOfOperation(operation) == 2)
		{
			deleteCountryRepository(getRepository(service), checkIfCountryIsInRepository(getRepository(service), getCountry1(operation)));
			operationToBeAddedToRedo = createOperation(1, getCountry1(operation), NULL);
		}
		else if (getTypeOfOperation(operation) == 3)
		{
			updateCountryRepository(getRepository(service), checkIfCountryIsInRepository(getRepository(service), getCountry1(operation)), copyCountry(getCountry2(operation)));
			operationToBeAddedToRedo = createOperation(3, getCountry2(operation), getCountry1(operation));
		}
		addElementToDynamicArray(redoToThisArray, operationToBeAddedToRedo);
		deleteElementFromDynamicArray(undoFromThisArray, getLengthOfDynamicArray(undoFromThisArray) - 1);
	}
	else if (getTypeOfUndoRedo(service) == 2)
	{
		if (getLengthOfDynamicArray(undoFromThisArray) == 0)
			return 0;
		DynamicArray* dynamicArray = (DynamicArray*)getElementOnPosition(undoFromThisArray, getLengthOfDynamicArray(undoFromThisArray) - 1);
		DynamicArray* dynamicArrayToBeAddedToRedo = copyDynamicArrayOfCountries(getDynamicArray(getRepository(service)));
		addElementToDynamicArray(redoToThisArray, dynamicArrayToBeAddedToRedo);
		DynamicArray* swap1;
		swap1 = getDynamicArray(getRepository(service));
		service->repository->dynamicArray = copyDynamicArrayOfCountries(dynamicArray);
		destroyDynamicArray(swap1);
		deleteElementFromDynamicArray(undoFromThisArray, getLengthOfDynamicArray(undoFromThisArray) - 1);
	}
	return 1;
}

DynamicArray* getCountriesBasedOnFiltering(CountryService* service, char* string, OperationOfComparison operationOfComparison) {
	sortCountriesBasedOnCondition(getRepository(service), &firstCountrySmallerPopulation);
	string[strlen(string) - 1] = '\0';
	DynamicArray* dynamicArray = createDynamicArray(getLengthOfDynamicArray(getDynamicArray(getRepository(service))), destroyCountry);
	for (int i = 0; i < getCountryRepositoryLength(getRepository(service)); i++) {
		Country* country = getCountryFromRepository(getRepository(service), i);
		if (country && operationOfComparison(country, string))
			addElementToDynamicArray(dynamicArray, copyCountry(country));
	}
	return dynamicArray;
}

DynamicArray* getCountriesFromAGivenContinent(CountryService* service, char* string, float population, OperationOfComparisonBetweenCountries operationOfComparison) {
	sortCountriesBasedOnCondition(getRepository(service), operationOfComparison);
	DynamicArray* dynamicArray = createDynamicArray(getLengthOfDynamicArray(getDynamicArray(getRepository(service))), destroyCountry);
	for (int i = 0; i < getCountryRepositoryLength(getRepository(service)); ++i)
	{
		Country* country = getCountryFromRepository(getRepository(service), i);
		if (strlen(string) == 0 || (country && strcmp(getContinent(country), string) == 0 && getPopulation(country) > population))
			addElementToDynamicArray(dynamicArray, copyCountry(country));
	}
	return dynamicArray;
}

DynamicArray* getAllCountries(CountryService* service) {
	DynamicArray* dynamicArray = createDynamicArray(getLengthOfDynamicArray(getDynamicArray(getRepository(service))), destroyCountry);
	for (int i = 0; i < getCountryRepositoryLength(getRepository(service)); ++i)
	{
		Country* country = getCountryFromRepository(getRepository(service), i);
		addElementToDynamicArray(dynamicArray, copyCountry(country));
	}
	return dynamicArray;
}

DynamicArray* getCountriesFromAGivenContinent_2(CountryService* service, char* string, OperationOfComparisonBetweenCountries operationOfComparison) {
	sortCountriesBasedOnCondition(getRepository(service), operationOfComparison);
	DynamicArray* dynamicArray = createDynamicArray(getLengthOfDynamicArray(getDynamicArray(getRepository(service))), destroyCountry);
	for (int i = 0; i < getCountryRepositoryLength(getRepository(service)); ++i)
	{
		Country* country = getCountryFromRepository(getRepository(service), i);
		if (strlen(string) == 0 || (country && strcmp(getContinent(country), string) == 0))
			addElementToDynamicArray(dynamicArray, copyCountry(country));
	}
	return dynamicArray;
}

void generateInitalEntries(CountryService* service) {
	addCountryRepository(getRepository(service), createCountry("Germany", "Europe", 83.3));
	addCountryRepository(getRepository(service), createCountry("Mexico", "America", 128.9));
	addCountryRepository(getRepository(service), createCountry("Indonesia", "Asia", 273.5));
	addCountryRepository(getRepository(service), createCountry("Egypt", "Africa", 102.3));
	addCountryRepository(getRepository(service), createCountry("United Kingdom", "Europe", 67.9));
	addCountryRepository(getRepository(service), createCountry("Vietnam", "Asia", 97.3));
	addCountryRepository(getRepository(service), createCountry("Argentina", "America", 45.4));
	addCountryRepository(getRepository(service), createCountry("Kenya", "Africa", 53.8));
	addCountryRepository(getRepository(service), createCountry("Spain", "Europe", 46.9));
	addCountryRepository(getRepository(service), createCountry("Thailand", "Asia", 69.8));
}
