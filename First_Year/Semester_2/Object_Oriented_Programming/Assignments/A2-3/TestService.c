#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "TestService.h"
#include "Country.h"
#include "CountryService.h"

void testStartService(int typeOfUndoRedo)
{
    CountryRepository* repository = createCountryRepository();
    UndoRedoRepository* undoRedoRepository = createUndoRedoRepository(typeOfUndoRedo);
    CountryService* service = createCountryService(repository, undoRedoRepository, typeOfUndoRedo);
    assert(getRepository(service) == repository);
    assert(getUndoRedoRepository(service) == undoRedoRepository);
    assert(getTypeOfUndoRedo(service) == typeOfUndoRedo);
    generateInitalEntries(service);
    assert(getCountryRepositoryLength(getRepository(service)) == 10);
    destroyCountryService(service);
}

void testPerformOperationsOnCountryService(int typeOfUndoRedo)
{
    CountryRepository* repository = createCountryRepository();
    UndoRedoRepository* undoRedoRepository = createUndoRedoRepository(typeOfUndoRedo);
    CountryService* service = createCountryService(repository, undoRedoRepository, typeOfUndoRedo);

    Country* country1 = createCountry("Romania", "Europe", 19.2);
    assert(addCountryService(service, country1) == 1);
    Country* country2 = createCountry("Romania", "Europe", 19.2);
    assert(addCountryService(service, country2) == 0);
    assert(getCountryRepositoryLength(getRepository(service)) == 1);
    
    Country* country3 = createCountry("Hungary", "Europe", 9.3);
    Country* country4 = createCountry("Japan", "Asia", 78.9);
    assert(updateCountryService(service, copyCountry(country2), copyCountry(country3)) == 1);
    assert(updateCountryService(service, country4, copyCountry(country3)) == 0);

    //assert(deleteCountryService(service, country4) == 0);
    assert(deleteCountryService(service, country3) == 1);
    
    country2 = createCountry("France", "Europe", 66.4);
    assert(addCountryService(service, country2) == 1);
    country3 = createCountry("Moroco", "Africa", 45.1);
    assert(addCountryService(service, country3) == 1);
    country4 = createCountry("Belgium", "Europe", 10.2);
    assert(addCountryService(service, country4) == 1);

    assert(getCountryRepositoryLength(getRepository(service)) == 3);

    int lengthOfUndoArray = getLengthOfDynamicArray(getUndoOperations(getUndoRedoRepository(service))), lengthOfRedoArray = getLengthOfDynamicArray(getRedoOperations(getUndoRedoRepository(service)));
    assert(lengthOfUndoArray == 6 && lengthOfRedoArray == 0);
    for (int i = 0; i < lengthOfUndoArray; ++i)
        assert(undoRedoService(service, getUndoOperations(getUndoRedoRepository(service)), getRedoOperations(getUndoRedoRepository(service))) == 1);

    lengthOfUndoArray = getLengthOfDynamicArray(getUndoOperations(getUndoRedoRepository(service))), lengthOfRedoArray = getLengthOfDynamicArray(getRedoOperations(getUndoRedoRepository(service)));
    assert(lengthOfUndoArray == 0 && lengthOfRedoArray == 6);
    for (int i = 0; i < lengthOfRedoArray; ++i)
        assert(undoRedoService(service, getRedoOperations(getUndoRedoRepository(service)), getUndoOperations(getUndoRedoRepository(service))) == 1);
    assert(getCountryRepositoryLength(getRepository(service)) == 3);

    OperationOfComparison operation = &countryContainsString;
    char string1[1001] = "\n";
    DynamicArray* countriesFiltered = getCountriesBasedOnFiltering(service, string1, operation);
    assert(getLengthOfDynamicArray(countriesFiltered) == 3);
    destroyDynamicArray(countriesFiltered);
    char string2[1001] = "r\n";
    countriesFiltered = getCountriesBasedOnFiltering(service, string2, operation);
    assert(getLengthOfDynamicArray(countriesFiltered) == 2);
    destroyDynamicArray(countriesFiltered);
    char string3[1001] = "r\n";
    operation = &countryDoesNotContainString;
    countriesFiltered = getCountriesBasedOnFiltering(service, string3, operation);
    assert(getLengthOfDynamicArray(countriesFiltered) == 1);
    destroyDynamicArray(countriesFiltered);

    OperationOfComparisonBetweenCountries operationComparisonCountries = &firstCountrySmallerPopulation;
    DynamicArray* countriesFilter = getCountriesFromAGivenContinent(service, "Europe", 9, operationComparisonCountries);
    assert(getLengthOfDynamicArray(countriesFilter) == 2);
    country2 = createCountry("France", "Europe", 66.4);
    country3 = createCountry("Moroco", "Africa", 45.1);
    country4 = createCountry("Belgium", "Europe", 10.2);
    assert(compareCountries((Country*)getElementOnPosition(countriesFilter, 0), country4));
    destroyDynamicArray(countriesFilter);

    operationComparisonCountries = &firstCountryGreaterPopulation;
    countriesFilter = getCountriesFromAGivenContinent(service, "Europe", 9, operationComparisonCountries);
    assert(getLengthOfDynamicArray(countriesFilter) == 2);
    assert(compareCountries((Country*)getElementOnPosition(countriesFilter, 0), country2));
    destroyDynamicArray(countriesFilter);
    destroyCountry(country2);
    destroyCountry(country3);
    destroyCountry(country4);
    destroyCountryService(service);
}

void testAllService()
{
    testStartService(1);
    testStartService(2);
    testPerformOperationsOnCountryService(1);
    testPerformOperationsOnCountryService(2);
}