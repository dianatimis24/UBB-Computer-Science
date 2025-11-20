#pragma once
#include "DynamicVector.h"
#include "Dog.h"
#include <iostream>
#include <string>

class Repository
{
private:
	DynamicVector<Dog> dogs;

public:
	/// Constructor
	Repository();

	/// Destructor
	~Repository();

	/// <summary>
	/// A function that adds a given dog to the DynamicVector<Dog>.
	/// </summary>
	/// <param name="dog">A reference to the dog we want to add</param>
	void addDog(const Dog& dog);

	/// <summary>
	/// A function that removes a given dog from the DynamicVector<Dog>.
	/// </summary>
	/// <param name="dog">A reference to the dog we want to remove</param>
	void removeDog(Dog& dog);

	/// <summary>
	/// A function that removes the dog from a given position in the DynamicVector<Dog>.
	/// </summary>
	/// <param name="position">The position from which we want to remove the dog</param>
	void removeDogByPosition(int position);

	/// <summary>
	/// A function that updates the dog from a given position in the DynamicVector<Dog> with a given dog.
	/// </summary>
	/// <param name="position">The position from which we want to update the dog</param>
	/// <param name="dog">A reference to the updated dog</param>
	void updateDog(int position, const Dog& dog);

	/// <summary>
	/// A function that checks if a given position is a valid position in the DynamicVector<Dog>.
	/// </summary>
	/// <param name="position">The position we want to check</param>
	/// <returns>treu if the position is valid/existent, false otherwise</returns>
	bool validatePosition(int position) const;

	/// A function that gets all the dogs and returns them as a DynamicVector<Dog>.
	DynamicVector<Dog> getDogs() const;

	/// A function that gets the number of dogs and returns it.
	int getDogsNumber() const;

	/// A function that returns the Dog from a given position in the DynamicVector<Dog>.
	Dog getDogByPosition(int position) const;

	/// A function that returns the position of a given Dog in the DynamicVector<Dog>.
	int returnPosition(Dog& dog) const;
};

