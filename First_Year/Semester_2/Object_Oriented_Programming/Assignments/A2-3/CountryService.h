#pragma once
#include "CountryRepository.h"
#include "UndoRedoRepository.h"

typedef struct {
	CountryRepository* repository;
	UndoRedoRepository* undoRedoRepository;
	int typeOfUndoRedo;
} CountryService;

/// <summary>
/// A function that creates a service with the given parameters.
/// </summary>
/// <param name="repository">A pointer to the CountryRepository</param>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
/// <param name="typeOfUndoRedo">The type of the UndoRedo</param>
/// <returns>A pointer to the newly allocated CountryService</returns>
CountryService* createCountryService(CountryRepository* repository, UndoRedoRepository* undoRedoRepository, int typeOfUndoRedo);

/// <summary>
/// A function that destroys a given service.
/// </summary>
/// <param name="service">A pointer to the service that will be destroyed</param>
void destroyCountryService(CountryService* service);

/// <summary>
/// A function that adds a country, in the service.
/// </summary>
/// <param name="service">A pointer to the service</param>
/// <param name="country">A pointer to the country we want to add</param>
/// <returns>1 if the country was added, 0 otherwise</returns>
int addCountryService(CountryService* service, Country* country);

/// <summary>
/// A function that deletes a country, in the service.
/// </summary>
/// <param name="service">A pointer to the service</param>
/// <param name="country">A pointer to the country we want to delete</param>
/// <returns>1 if the country was deleted, 0 otherwise</returns>
int deleteCountryService(CountryService* service, Country* country);

/// <summary>
/// A function that updates a country with the the content of a given country.
/// </summary>
/// <param name="service">A pointer to the service</param>
/// <param name="country1">The country we want to update</param>
/// <param name="country2">The given country</param>
/// <returns>1 if the country was updated, 0 otherwise</returns>
int updateCountryService(CountryService* service, Country* country1, Country* country2);

/// <summary>
/// A function that performs the undo-redo operations in the current service.
/// </summary>
/// <param name="service">A pointer to the service</param>
/// <param name="undoFromThisArray">The dynamic array that contains the operations that can be undone</param>
/// <param name="redoToThisArray">The dynamic array that contains the operations that can be redone</param>
/// <returns>0 if there are no more operations to be undone, 1 otherwise</returns>
int undoRedoService(CountryService* service, DynamicArray* undoFromThisArray, DynamicArray* redoToThisArray);

/// <summary>
/// A function that returns the type of undo-redo.
/// </summary>
/// <param name="service">A pointer to the service</param>
/// <returns>The type of the undo-redo</returns>
int getTypeOfUndoRedo(CountryService* service);

/// <summary>
/// A function that returns the CountryRepository.
/// </summary>
/// <param name="service">A pointer to the service</param>
/// <returns>The repository of the countries</returns>
CountryRepository* getRepository(CountryService* service);

/// <summary>
/// A function that returns the UndoRedoRepository.
/// </summary>
/// <param name="service">A pointer to the service</param>
/// <returns>The UndoRedoRepository</returns>
UndoRedoRepository* getUndoRedoRepository(CountryService* service);

/// <summary>
/// A function that generates 10 initial entries (countries) and adds them to the CountryRepository.
/// </summary>
/// <param name="service">A pointer to the service</param>
void generateInitalEntries(CountryService* service);

/// <summary>
/// A function that returns a dynamic array containing the countries that contain (or do not contain) a given string.
/// </summary>
/// <param name="service">A pointer to the service</param>
/// <param name="string">The given string</param>
/// <param name="operationOfComparison">The operation that tells us if we consider the countries that contain the given string or the ones that do not contain it</param>
/// <returns>The dynamic array of requested countries</returns>
DynamicArray* getCountriesBasedOnFiltering(CountryService* service, char* string, OperationOfComparison operationOfComparison);

/// <summary>
/// A function that returns a dynamic array containing the countries that are from a given continent and have the population greater than a given number.
/// </summary>
/// <param name="service">A pointer to the service</param>
/// <param name="string">The continent</param>
/// <param name="population">The population</param>
/// <param name="operationOfComparison">The operation that tells us if we want the countries increasingly or decreasingly</param>
/// <returns>The dynamic array of requested countries</returns>
DynamicArray* getCountriesFromAGivenContinent(CountryService* service, char* string, float population, OperationOfComparisonBetweenCountries operationOfComparison);

/// <summary>
/// A function that returns a dynamic array containing all the countries.
/// </summary>
/// <param name="service">A pointer to the service</param>
/// <returns>The dynamic array of countries</returns>
DynamicArray* getAllCountries(CountryService* service);

DynamicArray* getCountriesFromAGivenContinent_2(CountryService* service, char* string, OperationOfComparisonBetweenCountries operationOfComparison);