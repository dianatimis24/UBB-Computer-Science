#pragma once
#include "DynamicArray.h"
#include "Operation.h"
#include "CountryRepository.h"

typedef struct
{
	DynamicArray* undoOperations;
	DynamicArray* redoOperations;
} UndoRedoRepository;

/// <summary>
/// A function that creates an UndoRedoRepository with the given type of undo-redo.
/// </summary>
/// <param name="typeOfUndoRedo">The type of undo-redo</param>
/// <returns>A pointer to the newly allocated UndoRedoRepository</returns>
UndoRedoRepository* createUndoRedoRepository(int typeOfUndoRedo);

/// <summary>
/// A function that returns the last function that can be undone.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
/// <returns>The last function that can be undone</returns>
Operation* getUndoOperation(UndoRedoRepository* undoRedoRepository);

/// <summary>
/// A function that returns the last function that can be redone.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
/// <returns>The last function that can be redone</returns>
Operation* getRedoOperation(UndoRedoRepository* undoRedoRepository);

/// <summary>
/// A function that returns the dynamic array of the operations that can be undone.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
/// <returns>The dynamic array of the operations that can be undone</returns>
DynamicArray* getUndoDynamicArray(UndoRedoRepository* undoRedoRepository);

/// <summary>
/// A function that returns the dynamic array of the operations that can be redone.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
/// <returns>The dynamic array of the operations that can be redone</returns>
DynamicArray* getRedoDynamicArray(UndoRedoRepository* undoRedoRepository);

/// <summary>
/// A function that returns the dynamic array of the operations that can be undone.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
/// <returns>The dynamic array of the operations that can be undone</returns>
DynamicArray* getUndoOperations(UndoRedoRepository* undoRedoRepository);

/// <summary>
/// A function that returns the dynamic array of the operations that can be redone.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
/// <returns>The dynamic array of the operations that can be redone</returns>
DynamicArray* getRedoOperations(UndoRedoRepository* undoRedoRepository);

/// <summary>
/// A function that destroys the dynamic array of operations to be undone.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
void destroyUndoOperations(UndoRedoRepository* undoRedoRepository);

/// <summary>
/// A function that destroys the dynamic array of operations to be redone.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
void destroyRedoOperations(UndoRedoRepository* undoRedoRepository);

/// <summary>
/// A function that resets the dynamic array of operations to be redone.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
void resetRedoOperations(UndoRedoRepository* undoRedoRepository);

/// <summary>
/// A function that resets the dynamic array of operations to be undone.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
void resetRedoDynamicArray(UndoRedoRepository* undoRedoRepository);

/// <summary>
/// A functions that destroys a given UndoRedoRepository.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository that will be destroyed</param>
void destroyUndoRedoRepository(UndoRedoRepository* undoRedoRepository);

/// <summary>
/// A function that adds an operation to be undone in the dynamic array of undone operations.
/// </summary>
/// <param name=""></param>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
void addUndoOperation(UndoRedoRepository*, Operation* undoRedoRepository);

/// <summary>
/// A function that adds an operation to be undone in the dynamic array of redone operations.
/// </summary>
/// <param name=""></param>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
void addRedoOperation(UndoRedoRepository*, Operation* undoRedoRepository);

/// <summary>
/// A function that adds an operation to be undone in the dynamic array of undone operations.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
/// <param name="dynamicArray"></param>
void addUndoDynamicArray(UndoRedoRepository* undoRedoRepository, DynamicArray* dynamicArray);

/// <summary>
/// A function that adds an operation to be undone in the dynamic array of redone operations.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
/// <param name="dynamicArray"></param>
void addRedoDynamicArray(UndoRedoRepository* undoRedoRepository, DynamicArray* dynamicArray);

/// <summary>
/// A function that removes an operation from the dynamic array of operations to be undone.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
void removeUndoOperation(UndoRedoRepository* undoRedoRepository);

/// <summary>
/// A function that removes an operation from the dynamic array of operations to be redone.
/// </summary>
/// <param name="undoRedoRepository">A pointer to the UndoRedoRepository</param>
void removeRedoOperation(UndoRedoRepository* undoRedoRepository);