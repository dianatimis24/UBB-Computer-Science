#pragma once
#include "Country.h"

typedef void *TElem;
typedef void (*DestroyElementFunctionPointer)(TElem);

typedef struct {
	TElem* elements;
	int length, capacity;
	DestroyElementFunctionPointer destroyElementFunctionPointer;
} DynamicArray;

/// <summary>
/// A function that creates a dynamic array of TElem's with the given parameters.
/// </summary>
/// <param name="capacity">The maximum capacity of the dynamic array</param>
/// <param name="destroyElementFunctionPointer">The function that destroys a TElem</param>
/// <returns>A pointer to the newly created dynamic array</returns>
DynamicArray* createDynamicArray(int capacity, DestroyElementFunctionPointer destroyElementFunctionPointer);

/// <summary>
/// A function that resizes the dynamic array by multiplying its capacity with 2.
/// </summary>
/// <param name="dynamicArray">A pointer to the dynamic array</param>
void resizeDynamicArray(DynamicArray* dynamicArray);

/// <summary>
/// A function that destroys a given dynamic array.
/// </summary>
/// <param name="dynamicArray">A pointer to the dynamic array that will be destroyed</param>
void destroyDynamicArray(DynamicArray* dynamicArray);

/// <summary>
/// A function that sets the length of the dynamic array.
/// </summary>
/// <param name="dynamicArray">A pointer to the dynamic array</param>
/// <param name="length">The new length</param>
void setLengthOfDynamicArray(DynamicArray* dynamicArray, int length);

/// <summary>
/// A function that gets the element from a given positon in the dynamic array.
/// </summary>
/// <param name="dynamicArray">A pointer to the dynamic array</param>
/// <param name="position">The position</param>
/// <returns>The element from the given position</returns>
TElem* getElementOnPosition(DynamicArray* dynamicArray, int position);

/// <summary>
/// A function that gets all the elements from the dynamic array. 
/// </summary>
/// <param name="dynamicArray">A pointer to the dynamic array</param>
/// <returns>A pointer to the first element in the dynamic array</returns>
TElem* getElements(DynamicArray* dynamicArray);

/// <summary>
/// A function that adds a new element to the dynamic array.
/// </summary>
/// <param name="dynamicArray">A pointer to the dynamic array</param>
/// <param name="element">The newly added element</param>
void addElementToDynamicArray(DynamicArray* dynamicArray, TElem element);

/// <summary>
/// A function that removes an element from a given position in the dynamic array.
/// </summary>
/// <param name="dynamicArray">A pointer to the dynamic array</param>
/// <param name="position">The position from which we remove the element</param>
void deleteElementFromDynamicArray(DynamicArray* dynamicArray, int position);

/// <summary>
/// A function that updates the element from a given position in the dynamic array.
/// </summary>
/// <param name="dynamicArray">A pointer to the dynamic array</param>
/// <param name="position">The position of the element we want to update</param>
/// <param name="element">The new value of the updated element</param>
void updateElementOnPosition(DynamicArray* dynamicArray, int position, TElem element);

/// <summary>
/// A function that swaps two elements in the dynamic array.
/// </summary>
/// <param name="dynamicArray">A pointer to the dynamic array</param>
/// <param name="position1">The position of the first element</param>
/// <param name="position2">The position of the second element</param>
void swapElementsOnDynamicArray(DynamicArray* dynamicArray, int position1, int position2);

/// <summary>
/// A function that returns the length of the dynamic array.
/// </summary>
/// <param name="dynamicArray">A pointer to the dynamic array</param>
/// <returns>The length of the dynamic array</returns>
int getLengthOfDynamicArray(DynamicArray* dynamicArray);

/// <summary>
/// A function that returns the capacity of the dynamic array.
/// </summary>
/// <param name="dynamicArray">A pointer to the dynamic array</param>
/// <returns>The capacity of the dynamic array</returns>
int getCapacityOfDynamicArray(DynamicArray* dynamicArray);

/// <summary>
/// A function that returns the function that destroys a TElem.
/// </summary>
/// <param name="dynamicArray">A pointer to the dynamic array</param>
/// <returns>The function that destroys a TElem.</returns>
DestroyElementFunctionPointer getDestroyElementFunctionPointer(DynamicArray* dynamicArray);

/// <summary>
/// A function that copies a given dynamic array.
/// </summary>
/// <param name="dynamicArray">A pointer to the dynamic array</param>
/// <returns>A copy of the initial dynamic array</returns>
DynamicArray* copyDynamicArrayOfCountries(DynamicArray* dynamicArray);