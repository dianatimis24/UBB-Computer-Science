#pragma once
#include "CountryService.h"

typedef struct {
	CountryService* service;
} UI;

/// <summary>
/// A function that creates a new ui with a given CountryService.
/// </summary>
/// <param name="service">A pointer to the given service</param>
/// <returns>A pointer to the newly allocated UI</returns>
UI* createUI(CountryService* service);

/// <summary>
/// A function that returns the service of the given UI.
/// </summary>
/// <param name="ui">A pointer to the given UI</param>
/// <returns>The service of the given UI</returns>
CountryService* getCountryService(UI* ui);

/// <summary>
/// A function that destroys a given UI.
/// </summary>
/// <param name="ui">A pointer to the UI that will be destroyed</param>
void destroyUI(UI* ui);

/// <summary>
/// A function that starts the UI in the main function.
/// </summary>
/// <param name="ui">A pointer to the UI</param>
void startUI(UI* ui);

/// <summary>
/// A function that adds a country, in the UI.
/// </summary>
/// <param name="ui">A pointer to the UI</param>
void addCountryUI(UI* ui);

/// <summary>
/// A function that deletes a country, in the UI.
/// </summary>
/// <param name="ui">A pointer to the UI</param>
void deleteCountryUI(UI* ui);

/// <summary>
/// A function that updates a country, in the UI.
/// </summary>
/// <param name="ui">A pointer to the UI</param>
void updateCountryUI(UI* ui);

/// <summary>
/// A function that performs the undo operation, in the UI.
/// </summary>
/// <param name="ui">A pointer to the UI</param>
void undoCountryUI(UI* ui);

/// <summary>
/// A function that performs the redo operation, in the UI.
/// </summary>
/// <param name="ui">A pointer to the UI</param>
void redoCountryUI(UI* ui);

/// <summary>
/// A function that prints the countries that contain (or do not contain, based on the user's choice) a given string.
/// </summary>
/// <param name="ui">A pointer to the UI</param>
void listCountriesUIBasedOnStringRequirement(UI* ui);

/// <summary>
/// A function that prints the countries that are from the same continent (which have a population greater than a number inserted by the user).
/// </summary>
/// <param name="ui">A pointer to the UI</param>
void listCountriesThatAreFromTheSameContinent(UI* ui);

void listCountriesFromAGivenContinentByName(UI* ui);