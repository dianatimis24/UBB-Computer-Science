#pragma once
#include "Country.h"

typedef struct
{
	/*
	** typeOfOperation: 1 - Add, 2 - Delete, 3 - Update
	** 1) Add: country1, country2 = NULL
	** 2) Delete: country1, country2 = NULL
	** 3) Update: country1, country2
	*/
	int typeOfOperation;
	Country *country1, *country2;
} Operation;

/// <summary>
/// A function that creates an operation between two given countries.
/// </summary>
/// <param name="typeOfOperation">the type of the operation: 1 for add, 2 for delete, 3 for update</param>
/// <param name="country1">the first country</param>
/// <param name="country2">the second country</param>
/// <returns>A pointer to the newly allocated operation</returns>
Operation* createOperation(int typeOfOperation, Country* country1, Country* country2);

/// <summary>
/// A functions that destroys an operation.
/// </summary>
/// <param name="operation">A pointer to the operation that is about to be destroyed</param>
void destroyOperation(Operation* operation);

/// <summary>
/// A function that returns the type of the operation.
/// </summary>
/// <param name="operation">A pointer to the operation</param>
/// <returns>The value of the typr of the operation: 1 for add, 2 for delete, 3 for update</returns>
int getTypeOfOperation(Operation* operation);

/// <summary>
/// A function that returns the first country involved in the operation.
/// </summary>
/// <param name="operation">A pointer to the operation</param>
/// <returns>A pointer to the first country</returns>
Country* getCountry1(Operation* operation);

/// <summary>
/// A function that returns the second country involved in the operation.
/// </summary>
/// <param name="operation">A pointer to the operation</param>
/// <returns>A pointer to the second country</returns>
Country* getCountry2(Operation* operation);