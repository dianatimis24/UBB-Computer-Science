#include "TestDynamicArray.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void testDynamicArrayAll()
{
	DynamicArray* dynamicArray = createDynamicArray(1, destroyCountry);
	assert(dynamicArray);
	assert(getLengthOfDynamicArray(dynamicArray) == 0);
	assert(getCapacityOfDynamicArray(dynamicArray) == 1);

	Country* country = createCountry("Romania", "Europe", 19.2);
	addElementToDynamicArray(dynamicArray, country);
	assert(getLengthOfDynamicArray(dynamicArray) == 1);
	assert(getCapacityOfDynamicArray(dynamicArray) == 1);
	assert(compareCountries((Country*)getElementOnPosition(dynamicArray, 0), country));

	Country* country1 = createCountry("Hungary", "Europe", 9.4);
	addElementToDynamicArray(dynamicArray, country1);
	assert(compareCountries((Country*)getElementOnPosition(dynamicArray, 1), country1));
	assert(getLengthOfDynamicArray(dynamicArray) == 2);
	assert(getCapacityOfDynamicArray(dynamicArray) == 2);

	Country* country2 = createCountry("Japan", "Asia", 78.9);

	addElementToDynamicArray(dynamicArray, country2);

	assert(getLengthOfDynamicArray(dynamicArray) == 3);

	assert(getCapacityOfDynamicArray(dynamicArray) == 4);

	assert(!getElementOnPosition(dynamicArray, 3));
	assert(!getElementOnPosition(dynamicArray, -1));

	swapElementsOnDynamicArray(dynamicArray, 0, 2);

	assert(compareCountries((Country*)getElementOnPosition(dynamicArray, 0), country2));
	assert(compareCountries((Country*)getElementOnPosition(dynamicArray, 1), country1));
	assert(compareCountries((Country*)getElementOnPosition(dynamicArray, 2), country));
	deleteElementFromDynamicArray(dynamicArray, 2);
	assert(getLengthOfDynamicArray(dynamicArray) == 2);
	assert(getCapacityOfDynamicArray(dynamicArray) == 4);
	country2 = createCountry("Japan", "Asia", 78.9);
	updateElementOnPosition(dynamicArray, 0, country2);
	assert(compareCountries((Country*)getElementOnPosition(dynamicArray, 0), country2));
	destroyDynamicArray(dynamicArray);
}