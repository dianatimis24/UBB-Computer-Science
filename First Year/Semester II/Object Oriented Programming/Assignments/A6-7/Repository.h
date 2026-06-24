#pragma once
#include "Dog.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Repository
{
protected:
	std::vector<Dog> dogs;

public:
	/// Constructor
	Repository();

	/// Destructor
	virtual ~Repository();

	/// A function that loads the vector of dogs into the Repository.
	virtual void loadDogsIntoRepository();

	/// A function that saves the dogs from the Repository.
	virtual void saveDogs() ;

	/// <summary>
	/// A function that adds a given dog to the DynamicVector<Dog>.
	/// </summary>
	/// <param name="dog">A reference to the dog we want to add</param>
	virtual void addDog(const Dog& dog);

	/// <summary>
	/// A function that removes a given dog from the DynamicVector<Dog>.
	/// </summary>
	/// <param name="dog">A reference to the dog we want to remove</param>
	virtual void removeDog(Dog& dog);

	/// <summary>
	/// A function that removes the dog from a given position in the DynamicVector<Dog>.
	/// </summary>
	/// <param name="position">The position from which we want to remove the dog</param>
	virtual void removeDogByPosition(int position);

	/// <summary>
	/// A function that updates the dog from a given position in the DynamicVector<Dog> with a given dog.
	/// </summary>
	/// <param name="position">The position from which we want to update the dog</param>
	/// <param name="dog">A reference to the updated dog</param>
	virtual void updateDog(int position, const Dog& dog);

	/// <summary>
	/// A function that checks if a given position is a valid position in the DynamicVector<Dog>.
	/// </summary>
	/// <param name="position">The position we want to check</param>
	/// <returns>treu if the position is valid/existent, false otherwise</returns>
	bool validatePosition(int position) const;

	/// A function that gets all the dogs and returns them as a DynamicVector<Dog>.
	std::vector<Dog> getDogs() const;

	/// A function that gets the number of dogs and returns it.
	size_t getDogsNumber() const;

	/// A function that returns the Dog from a given position in the DynamicVector<Dog>.
	Dog getDogByPosition(int position) const;

	/// A function that returns the position of a given Dog in the DynamicVector<Dog>.
	int returnPosition(Dog& dog) const;
};

