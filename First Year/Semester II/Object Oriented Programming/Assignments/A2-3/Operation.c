#include <stdlib.h>
#include <stdio.h>
#include "Operation.h"

Operation* createOperation(int typeOfOperation, Country* country1, Country* country2)
{
    Operation* operation = (Operation*)malloc(sizeof(Operation));
    operation->typeOfOperation = typeOfOperation;
    operation->country1 = createCountry(country1->name, country1->continent, country1->population);
    if (country2)
        operation->country2 = createCountry(country2->name, country2->continent, country2->population);
    else
        operation->country2 = NULL;
    return operation;
}

Country* getCountry1(Operation* operation)
{
    return operation->country1;
}

Country* getCountry2(Operation* operation)
{
    return operation->country2;
}

int getTypeOfOperation(Operation* operation)
{
    return operation->typeOfOperation;
}

void destroyOperation(Operation* operation)
{
    destroyCountry(getCountry1(operation));
    if (getCountry2(operation))
        destroyCountry(getCountry2(operation));
    free(operation);
}