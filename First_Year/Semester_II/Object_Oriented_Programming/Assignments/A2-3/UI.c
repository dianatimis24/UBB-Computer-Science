#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UI.h"

UI* createUI(CountryService* service) {
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->service = service;
	return ui;
}

CountryService* getCountryService(UI* ui) {
	return ui->service;
}

void destroyUI(UI* ui) {
	destroyCountryService(ui->service);
	free(ui);
}

void printMenu() {
    printf("Welcome! To perform an action, please enter the corresponding number: \n");
    printf("0. Exit the application. \n");
    printf("1. Add a new country. \n");
    printf("2. Delete a country. \n");
    printf("3. Update a country. \n");
    printf("4. List all available countries, based on a given string. \n");
    printf("5. List all available countries that are from a given continent and with a population smaller than a given number. \n");
    printf("6. Undo last performed operation. \n");
    printf("7. Redo last available operation. \n");
    printf("8. List all countries on a given continent, sorted ascending by country name. \n");
}

void startUI(UI* ui) {
    generateInitalEntries(getCountryService(ui));
    int command = -1;
    while (command != 0)
    {
        printMenu();
        printf("Number of undo operations available: %d, Number of redo operations available: %d \n", getLengthOfDynamicArray(getUndoOperations(getUndoRedoRepository(getCountryService(ui)))), getLengthOfDynamicArray(getRedoOperations(getUndoRedoRepository(getCountryService(ui)))));
        printf("Enter command: ");
        scanf_s("%d", &command);
        switch (command)
        {
        case 0:
            printf("Thank you for using our application!\n");
            break;
        case 1:
            addCountryUI(ui);
            break;
        case 2:
            deleteCountryUI(ui);
            break;
        case 3:
            updateCountryUI(ui);
            break;
        case 4:
            listCountriesUIBasedOnStringRequirement(ui);
            break;
        case 5:
            listCountriesThatAreFromTheSameContinent(ui);
            break;
        case 6:
            undoCountryUI(ui);
            break;
        case 7:
            redoCountryUI(ui);
            break;
        case 8:
            listCountriesFromAGivenContinentByName(ui);
            break;
        default:
            printf("Invalid command! Please try again! \n");
        }
    }
}

void addCountryUI(UI* ui) {
    char name[1001], continent[1001];
    float population;
    printf("Enter the name of the country: ");
    scanf_s("%s", name, 1001);
    printf("Enter the continent of the country: ");
    scanf_s("%s", continent, 1001);
    do {
        printf("Enter the population of the country (in millions). It must be a positive real number: ");
        scanf_s("%f", &population);
        if (population <= 0)
            printf("Invalid population! Try again \n");
    } while (population <= 0);
    
    Country* country = createCountry(name, continent, population);
    if (addCountryService(getCountryService(ui), country) == 1)
        printf("Country added successfully!\n");
    else {
        printf("Country already existing! It can not be added again!\n");
        destroyCountry(country);
    }
}

void deleteCountryUI(UI* ui) {
    char name[1001];
    printf("Enter the name of the country: ");
    scanf_s("%s", name, 1001);
    Country* temporaryCountry = createCountry(name, "", 0);
    if (deleteCountryService(getCountryService(ui), temporaryCountry) == 1)
        printf("Country deleted successfully!\n");
    else
        printf("Country does not exist!\n");
    destroyCountry(temporaryCountry);
}

void updateCountryUI(UI* ui) {
    char nameBefore[1001], nameAfter[1001], continentAfter[1001], name1[1001], name2[1001];
    float populationAfter, populationMigrating;
    int command = -1;
    while (command != 1 && command != 2) {
        printf("Enter the way in which you want to update a country:\n "
            "1. Update a country completely (changing its name, continent, populatio).\n "
            "2. Update only the population (migration to another country).\n");
        printf("Your option is: ");
        scanf_s("%d", &command);
        switch (command) {
        case 1:
            printf("Enter the name of the country you want to update: ");
            scanf_s("%s", nameBefore, 1001);
            printf("Enter the name of the new country: ");
            scanf_s("%s", nameAfter, 1001);
            printf("Enter the continent of the new country: ");
            scanf_s("%s", continentAfter, 1001);
            do {
                printf("Enter the new population of the country (in millions). It must be a positive real number: ");
                scanf_s("%f", &populationAfter);
                if (populationAfter <= 0)
                    printf("Invalid population! Try again \n");
            } while (populationAfter <= 0);

            Country* countryBefore = createCountry(nameBefore, "", 0), * countryAfter = createCountry(nameAfter, continentAfter, populationAfter);
            if (updateCountryService(getCountryService(ui), countryBefore, countryAfter) == 1)
                printf("Country updated completely successfully!\n");
            else
                printf("Country does not exist!\n");
            break;
        case 2:
            printf("Enter the name of the initial country: ");
            scanf_s("%s", name1, 1001);
            printf("Enter the name of the new country: ");
            scanf_s("%s", name2, 1001);
            printf("Enter migrating population (in millions): ");
            scanf_s("%f", &populationMigrating);
            DynamicArray* countries = getAllCountries(getCountryService(ui));
            if (getLengthOfDynamicArray(countries) == 0) {
                printf("There are no countries!\n");
                free(getElements(countries));
                free(countries);
                return;
            }

            Country* country1Before, * country2Before, * country1After, * country2After;
            for (int i = 0; i < getLengthOfDynamicArray(countries); i++) {
                if (compareCountries((Country*)getElementOnPosition(countries, i), createCountry(name1, "", 0)) == 1)
                    country1Before = copyCountry((Country*)getElementOnPosition(countries, i));
                if (compareCountries((Country*)getElementOnPosition(countries, i), createCountry(name2, "", 0)) == 1)
                    country2Before = copyCountry((Country*)getElementOnPosition(countries, i));
            }
            if (getPopulation(country1Before) - populationMigrating < 0)
                printf("Update failed!\n");
            else {
                country1After = createCountry(name1, getContinent(country1Before), getPopulation(country1Before) - populationMigrating);
                country2After = createCountry(name2, getContinent(country2Before), getPopulation(country2Before) + populationMigrating);
                if (updateCountryService(getCountryService(ui), country1Before, country1After) == 1 && updateCountryService(getCountryService(ui), country2Before, country2After) == 1)
                    printf("Countries updated successfully!\n");
                else
                    printf("Update failed!\n");
            }
            break;
        default:
            printf("Invalid command! Please try again!\n");
        }
    }
}

void undoCountryUI(UI* ui) {
    CountryService* service = getCountryService(ui);
    UndoRedoRepository* undoRedoRepository = getUndoRedoRepository(service);
    DynamicArray* undoOperations = getUndoOperations(undoRedoRepository), * redoOperations = getRedoOperations(undoRedoRepository);
    if (undoRedoService(service, undoOperations, redoOperations))
        printf("Undo performed successfully!\n");
    else
        printf("No more undos available!\n");
}

void redoCountryUI(UI* ui) {
    CountryService* service = getCountryService(ui);
    UndoRedoRepository* undoRedoRepository = getUndoRedoRepository(service);
    DynamicArray* undoOperations = getUndoOperations(undoRedoRepository), * redoOperations = getRedoOperations(undoRedoRepository);
    if (undoRedoService(service, redoOperations, undoOperations))
        printf("Redo performed successfully!\n");
    else
        printf("No more redos available!\n");
}

void listCountriesUIBasedOnStringRequirement(UI* ui) {
    int command = -1;
    OperationOfComparison operation = &countryContainsString;
    while (command != 1 && command != 2) {
        printf("Enter command in which you want to search:\n "
            "1. Show the countries that CONTAIN the given string in their name.\n "
            "2. Show the countries that DO NOT CONTAIN the given string in their name.\n");
        printf("Your option is: ");
        scanf_s("%d", &command);
        switch (command) {
        case 1:
            operation = &countryContainsString;
            break;
        case 2:
            operation = &countryDoesNotContainString;
            break;
        default:
            printf("Invalid command! Please try again!\n");
        }
    }
    int character;
    while ((character = getchar()) != '\n' && character != EOF);
    char stringToSearchFor[1001];
    printf("Enter the string you want to search for. For displaying all the entities, just press enter: ");
    fgets(stringToSearchFor, 1001, stdin);
    DynamicArray* countries = getCountriesBasedOnFiltering(getCountryService(ui), stringToSearchFor, operation);
    if (getLengthOfDynamicArray(countries) == 0) {
        printf("There are no countries that satisfy your requirements!\n");
        free(getElements(countries));
        free(countries);
        return;
    }
    for (int i = 0; i < getLengthOfDynamicArray(countries); ++i) {
        char* countryAsString = formatCountryAsString((Country*)getElementOnPosition(countries, i));
        printf("%s \n", countryAsString);
        free(countryAsString);
    }
    destroyDynamicArray(countries);
}

void listCountriesThatAreFromTheSameContinent(UI* ui) {
    int character;
    while ((character = getchar()) != '\n' && character != EOF);
    char continent[1001];
    float population;
    printf("Enter the continent after which the command will be performed: ");
    fgets(continent, 1001, stdin);
    continent[strlen(continent) - 1] = '\0';
    printf("Enter the population after which the command will be performed: ");
    scanf_s("%f", &population);
    int command = -1;
    OperationOfComparisonBetweenCountries operation = &firstCountrySmallerPopulation;
    while (command != 1 && command != 2) {
        printf("In which way do you want the countries to be sorted?\n "
            "1. Increasing\n "
            "2. Decreasing\n");
        printf("Your option is: ");
        scanf_s("%d", &command);
        switch (command) {
        case 1:
            operation = &firstCountrySmallerPopulation;
            break;
        case 2:
            operation = &firstCountryGreaterPopulation;
            break;
        default:
            printf("Invalid command! Please try again!\n");
        }
    }
    DynamicArray* countries = getCountriesFromAGivenContinent(getCountryService(ui), continent, population, operation);

    if (getLengthOfDynamicArray(countries) == 0) {
        destroyDynamicArray(countries);
        printf("There are no countries that satisfy your requirements!\n");
        return;
    }
    for (int i = 0; i < getLengthOfDynamicArray(countries); ++i) {
        char* countryAsString = formatCountryAsString((Country*)getElementOnPosition(countries, i));
        printf("%s \n", countryAsString);
        free(countryAsString);
    }
    destroyDynamicArray(countries);
}

void listCountriesFromAGivenContinentByName(UI* ui) {
    int character;
    while ((character = getchar()) != '\n' && character != EOF);
    char continent[1001];
    float population;
    printf("Enter the continent after which the command will be performed: ");
    fgets(continent, 1001, stdin);
    continent[strlen(continent) - 1] = '\0';
    OperationOfComparisonBetweenCountries operation = &firstCountrySmallerName;
    DynamicArray* countries = getCountriesFromAGivenContinent_2(getCountryService(ui), continent, operation);

    if (getLengthOfDynamicArray(countries) == 0) {
        destroyDynamicArray(countries);
        printf("There are no countries that satisfy your requirements!\n");
        return;
    }
    for (int i = 0; i < getLengthOfDynamicArray(countries); ++i) {
        char* countryAsString = formatCountryAsString((Country*)getElementOnPosition(countries, i));
        printf("%s \n", countryAsString);
        free(countryAsString);
    }
    destroyDynamicArray(countries);
}